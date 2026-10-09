#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <dbghelp.h>

#include <xbox/xboxrecomp.h>
#include "recomp_funcs.h"

extern RECOMP_TLS uint32_t g_eax, g_ecx, g_edx, g_esp;
extern RECOMP_TLS uint32_t g_ebx, g_esi, g_edi, g_seh_ebp;
extern ptrdiff_t g_xbox_mem_offset;
extern void xbox_irq_enable_vblank(uint32_t vector);
extern int recomp_dispatch_init(void);
extern void godzilla_host_xmv_begin_sequence(void);

#define GODZILLA_ENTRY_POINT 0x0002A6D9u
#define GODZILLA_XBE_PATH "game_files\\default.xbe"
#define GODZILLA_GAME_DIR "game_files"
#define GODZILLA_TLS_VECTOR 0x0075E000u
#define GODZILLA_TLS_OBJECT 0x0075F000u
#define GODZILLA_CRT_LOCK10 0x0075F800u

#define GODZILLA_WINDOW_CLASS "GodzillaDAMMRecompWindow"
#define GODZILLA_WINDOW_TITLE "Godzilla: Destroy All Monsters Melee - Native Recompilation"

static HWND g_host_window;
static IDirect3D8 *g_host_d3d8;
static IDirect3DDevice8 *g_host_d3d_device;
static HANDLE g_host_window_ready;

static LRESULT CALLBACK godzilla_window_proc(HWND hwnd, UINT message,
                                              WPARAM wparam, LPARAM lparam)
{
    (void)wparam;
    (void)lparam;
    if (message == WM_CLOSE) {
        fprintf(stderr, "[HOST-WINDOW] WM_CLOSE hwnd=%p\n", (void *)hwnd);
        fflush(stderr);
        DestroyWindow(hwnd);
        return 0;
    }
    if (message == WM_DESTROY) {
        fprintf(stderr, "[HOST-WINDOW] WM_DESTROY hwnd=%p -> WM_QUIT\n",
                (void *)hwnd);
        fflush(stderr);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, message, wparam, lparam);
}

static DWORD WINAPI godzilla_window_thread(void *unused)
{
    WNDCLASSEXA window_class = {0};
    RECT rect = {0, 0, 640, 480};
    HINSTANCE instance = GetModuleHandleA(NULL);
    MSG msg;
    (void)unused;

    window_class.cbSize = sizeof(window_class);
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = godzilla_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    window_class.lpszClassName = GODZILLA_WINDOW_CLASS;
    if (!RegisterClassExA(&window_class) &&
        GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        fprintf(stderr, "Unable to register graphics window (error %lu).\n",
                GetLastError());
        SetEvent(g_host_window_ready);
        return 1;
    }

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    g_host_window = CreateWindowExA(
        0, GODZILLA_WINDOW_CLASS, GODZILLA_WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        NULL, NULL, instance, NULL);
    if (!g_host_window) {
        fprintf(stderr, "Unable to create graphics window (error %lu).\n",
                GetLastError());
        SetEvent(g_host_window_ready);
        return 2;
    }
    /* Do not expose an uninitialized black swapchain.  The D3D scanout path
     * reveals the window as soon as the first decoded or rendered frame has
     * been published. */
    ShowWindow(g_host_window, SW_HIDE);
    SetEvent(g_host_window_ready);

    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    fprintf(stderr, "[HOST-EXIT] window thread ended code=%llu\n",
            (unsigned long long)msg.wParam);
    fflush(stderr);
    ExitProcess((UINT)msg.wParam);
    return (DWORD)msg.wParam;
}

static BOOL init_host_graphics(void)
{
    D3DPRESENT_PARAMETERS present = {0};
    HANDLE window_thread;
    HRESULT hr;

    g_host_window_ready = CreateEventA(NULL, TRUE, FALSE, NULL);
    if (!g_host_window_ready) return FALSE;
    window_thread = CreateThread(NULL, 0, godzilla_window_thread, NULL, 0, NULL);
    if (!window_thread) {
        CloseHandle(g_host_window_ready);
        g_host_window_ready = NULL;
        return FALSE;
    }
    if (WaitForSingleObject(g_host_window_ready, 10000) != WAIT_OBJECT_0) {
        fprintf(stderr, "Timed out creating host graphics window.\n");
        CloseHandle(window_thread);
        CloseHandle(g_host_window_ready);
        g_host_window_ready = NULL;
        return FALSE;
    }
    CloseHandle(window_thread);
    CloseHandle(g_host_window_ready);
    g_host_window_ready = NULL;
    if (!g_host_window) return FALSE;

    g_host_d3d8 = xbox_Direct3DCreate8(0);
    if (!g_host_d3d8) return FALSE;
    present.BackBufferWidth = 640;
    present.BackBufferHeight = 480;
    present.BackBufferFormat = D3DFMT_X8R8G8B8;
    present.BackBufferCount = 1;
    present.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present.hDeviceWindow = g_host_window;
    present.Windowed = TRUE;
    present.EnableAutoDepthStencil = TRUE;
    present.AutoDepthStencilFormat = D3DFMT_D24S8;
    hr = g_host_d3d8->lpVtbl->CreateDevice(
        g_host_d3d8, 0, 0, g_host_window, 0, &present, &g_host_d3d_device);
    if (FAILED(hr)) {
        fprintf(stderr, "Unable to create host D3D device (0x%08lX).\n", hr);
        return FALSE;
    }
    return TRUE;
}

static BOOL read_file(const char *path, void **data_out, size_t *size_out)
{
    FILE *f = fopen(path, "rb");
    long size;
    void *data;
    if (!f) return FALSE;
    if (fseek(f, 0, SEEK_END) != 0 || (size = ftell(f)) <= 0 ||
        fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return FALSE;
    }
    data = malloc((size_t)size);
    if (!data || fread(data, 1, (size_t)size, f) != (size_t)size) {
        free(data);
        fclose(f);
        return FALSE;
    }
    fclose(f);
    *data_out = data;
    *size_out = (size_t)size;
    return TRUE;
}

static LONG CALLBACK crash_handler(PEXCEPTION_POINTERS ep)
{
    const EXCEPTION_RECORD *er = ep->ExceptionRecord;
    uintptr_t image_base = (uintptr_t)GetModuleHandleW(NULL);
    uintptr_t rip = (uintptr_t)ep->ContextRecord->Rip;
    char symbol_storage[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
    SYMBOL_INFO *symbol = (SYMBOL_INFO *)symbol_storage;
    DWORD64 displacement = 0;
    if (er->ExceptionCode == EXCEPTION_BREAKPOINT) {
        fprintf(stderr, "[HOST-BREAKPOINT] continuing at image-rva=0x%llX\n",
                (unsigned long long)(rip - image_base));
        ep->ContextRecord->Rip = rip + 1;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    fprintf(stderr, "\n[HOST-CRASH] code=0x%08lX rip=0x%016llX image-rva=0x%llX",
            er->ExceptionCode,
            (unsigned long long)rip,
            (unsigned long long)(rip - image_base));
    if (er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && er->NumberParameters >= 2) {
        fprintf(stderr, " access=%s address=0x%016llX",
                er->ExceptionInformation[0] ? "write" : "read",
                (unsigned long long)er->ExceptionInformation[1]);
    }
    fprintf(stderr,
            "\n[XBOX-REGS] eax=%08X ecx=%08X edx=%08X ebx=%08X"
            " esi=%08X edi=%08X esp=%08X ebp=%08X\n",
            g_eax, g_ecx, g_edx, g_ebx, g_esi, g_edi, g_esp, g_seh_ebp);
    fprintf(stderr,
            "[HOST-REGS] rax=%016llX rcx=%016llX rdx=%016llX rbx=%016llX"
            " rsi=%016llX rdi=%016llX\n",
            (unsigned long long)ep->ContextRecord->Rax,
            (unsigned long long)ep->ContextRecord->Rcx,
            (unsigned long long)ep->ContextRecord->Rdx,
            (unsigned long long)ep->ContextRecord->Rbx,
            (unsigned long long)ep->ContextRecord->Rsi,
            (unsigned long long)ep->ContextRecord->Rdi);
    if (g_seh_ebp >= 0x40u) {
        const uint32_t frame_va = g_seh_ebp - 0x40u;
        const uint32_t *frame =
            (const uint32_t *)((uintptr_t)frame_va +
                               (uintptr_t)g_xbox_mem_offset);
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery(frame, &mbi, sizeof(mbi)) == sizeof(mbi) &&
            mbi.State == MEM_COMMIT &&
            !(mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))) {
            unsigned i;
            fprintf(stderr, "[XBOX-FRAME] base=%08X", frame_va);
            for (i = 0; i < 40u; ++i) {
                if ((i & 7u) == 0u)
                    fprintf(stderr, "\n  +%02X:", i * 4u);
                fprintf(stderr, " %08X", frame[i]);
            }
            fprintf(stderr, "\n");
        }
    }
    memset(symbol_storage, 0, sizeof(symbol_storage));
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = MAX_SYM_NAME;
    if (SymInitialize(GetCurrentProcess(), NULL, TRUE) &&
        SymFromAddr(GetCurrentProcess(), (DWORD64)rip, &displacement, symbol)) {
        fprintf(stderr, "[HOST-SYMBOL] %s+0x%llX\n", symbol->Name,
                (unsigned long long)displacement);
    }
    fflush(stderr);
    return EXCEPTION_CONTINUE_SEARCH;
}

int main(void)
{
    static char stdout_buffer[64 * 1024];
    static char stderr_buffer[64 * 1024];
    void *xbe_data = NULL;
    size_t xbe_size = 0;
    char save_dir[MAX_PATH];
    int result = 1;

    /* The bridge is intentionally very chatty during bring-up.  Batch log
     * writes so redirected runs do not spend most of startup in NtWriteFile;
     * the crash handler flushes stderr before the process terminates. */
    setvbuf(stdout, stdout_buffer, _IOFBF, sizeof(stdout_buffer));
    setvbuf(stderr, stderr_buffer, _IOFBF, sizeof(stderr_buffer));
    AddVectoredExceptionHandler(1, crash_handler);

    printf("Godzilla: Destroy All Monsters Melee native bring-up\n");
    printf("XBE entry point: 0x%08X\n", GODZILLA_ENTRY_POINT);
    if (!read_file(GODZILLA_XBE_PATH, &xbe_data, &xbe_size)) {
        fprintf(stderr, "Unable to read %s (run from the Work directory).\n",
                GODZILLA_XBE_PATH);
        return 2;
    }
    printf("Loaded %zu-byte XBE.\n", xbe_size);

    if (!xbox_MemoryLayoutInit(xbe_data, xbe_size)) {
        fprintf(stderr, "Xbox memory initialization failed.\n");
        goto cleanup;
    }
    g_xbox_mem_offset = xbox_GetMemoryOffset();
    printf("Xbox memory ready; host offset=%lld.\n",
           (long long)g_xbox_mem_offset);

    xbox_kernel_init();
    xbox_kernel_ignore_quick_reboot(TRUE);
    /* Keep title data and Z: cache files beside the native bring-up build.
     * Besides making runs reproducible and self-contained, this guarantees
     * that the recompiled title can create cache_status.bin when the host is
     * running with a workspace-scoped filesystem token. */
    if (GetCurrentDirectoryA((DWORD)sizeof(save_dir), save_dir) > 0) {
        strcat_s(save_dir, sizeof(save_dir), "\\SaveData\\GodzillaDAMM");
        xbox_path_init(GODZILLA_GAME_DIR, save_dir);
    } else {
        xbox_path_init(GODZILLA_GAME_DIR, "SaveData\\GodzillaDAMM");
    }
    xbox_kernel_bridge_init();
    /* Build the flat indirect-call table before creating the host window.
     * Besides speeding vtable-heavy startup, this records the window-owning
     * thread used by the dispatch heartbeat to keep Windows messages flowing
     * throughout synchronous asset loading. */
    if (!recomp_dispatch_init())
        fprintf(stderr, "Flat recomp dispatch unavailable; using search fallback.\n");
    if (!init_host_graphics()) {
        fprintf(stderr, "Host graphics initialization failed.\n");
        goto cleanup;
    }
    /* Begin decoding the real retail startup reel as soon as the display is
     * available.  Guest shell initialization continues underneath it; when
     * the recovered movie event arrives it joins this already-running stream
     * instead of making the player sit through a black startup window. */
    if (!getenv("GODZILLA_SKIP_MOVIES"))
        godzilla_host_xmv_begin_sequence();
    /* This XDK build connects the NV2A interrupt at vector 3.  The retail D3D
     * ISR increments the vblank count used both for presentation pacing and
     * the XMV playback clock. */
    xbox_irq_enable_vblank(3u);
    /* This XDK build keeps DMA_PUT in the D3D device at +0x2C and a pointer
     * to its DMA_GET shadow at +0x30.  Let the NV2A acknowledgement worker
     * model asynchronous command consumption so the title's submit wait can
     * make the same forward progress it does on Xbox hardware. */
    xbox_Nv2aConfigureDmaProgress(0x00134078u, 0x2Cu, 0x30u);
    g_esp = XBOX_STACK_TOP;

    /* XDK 5233 uses fs:[4] as the base of the per-thread TLS slot vector.
     * Keep that vector outside the active stack so ordinary pushes cannot
     * overwrite slot zero.  The XBE TLS index at 0x003C65F8 starts at zero. */
    {
        uint32_t tls_index = MEM32(0x003C65F8u);
        MEM32(0x04u) = GODZILLA_TLS_VECTOR;
        MEM32(GODZILLA_TLS_VECTOR + tls_index * 4u) = GODZILLA_TLS_OBJECT;
        /* XOnline changes this title's CRT/TLS selector to -5 during startup. */
        MEM32(GODZILLA_TLS_VECTOR - 5u * 4u) = GODZILLA_TLS_OBJECT;
        MEM32(GODZILLA_TLS_OBJECT) = 0;
        MEM32(GODZILLA_TLS_OBJECT + 4u) = 0;
        printf("Godzilla TLS vector %08X slot %u -> %08X.\n",
               GODZILLA_TLS_VECTOR, tls_index, GODZILLA_TLS_OBJECT);
    }

    /* These two CRT constructors require XDK per-thread locale/heap structures
     * not yet modeled by xboxrecomp (including fs:[0x28]+0x12C).  Bypass the
     * CRT-only initialization while bringing up the title's main-menu path. */
    MEM32(0x0020E684u) = 0;
    MEM32(0x0020E688u) = 0;

    /* The skipped CRT initializer normally creates lock 10 before locale
     * startup.  Without it, its lazy initializer tries to acquire the same
     * missing lock and recursively invokes operator new forever. */
    memset(XBOX_PTR(GODZILLA_CRT_LOCK10), 0, 0x40u);
    MEM32(0x002BFDC8u + 10u * 8u) = GODZILLA_CRT_LOCK10;
    MEM32(0x002BFDC8u + 10u * 8u + 4u) = 1u;

    printf("Entering original game code at 0x%08X (esp=%08X).\n",
           GODZILLA_ENTRY_POINT, g_esp);
    xbe_entry_point();
    printf("Original entry point returned (eax=%08X).\n", g_eax);
    result = 0;

    xbox_kernel_shutdown();
    xbox_MemoryLayoutShutdown();
cleanup:
    fprintf(stderr, "[HOST-EXIT] main returning result=%d eax=%08X\n",
            result, g_eax);
    fflush(stderr);
    free(xbe_data);
    return result;
}
