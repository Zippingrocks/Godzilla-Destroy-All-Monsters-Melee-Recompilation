#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define COBJMACROS
#include <d3d11.h>
#include <dxgi.h>

#include "recomp_types.h"

extern void d3d8_PresentFrame(void);
extern void d3d8_capture_backbuffer_bmp_public(const char *path);
extern ID3D11DeviceContext *d3d8_GetD3D11Context(void);
extern IDXGISwapChain *d3d8_GetSwapChain(void);
extern void d3d8_SubmitRGBAFrame(const void *pixels, UINT row_pitch,
                                 UINT slice_pitch);
extern void kelvin_init(void);
extern int kelvin_method(uint32_t subchannel, uint32_t method, uint32_t param);
extern void kelvin_end_frame(void);
extern void sub_00039500(void);
extern void sub_00039560(void);
extern void sub_000399F0(void);
extern void godzilla_pump_frontend_completion(void);
extern void godzilla_complete_startup_sequence(void);
extern void sub_000DBC30(void);
extern void sub_0009DA50(void);
extern void sub_0011D980(void);
extern void sub_000BAF10(void);
extern void sub_000C2B60(void);
extern void sub_000BB360(void);
extern void sub_000C1410(void);
extern void sub_000B8F40(void);
extern void sub_000665E0(void);
extern void sub_001B15C0(void);

#define eax g_eax
#define ebx g_ebx
#define ecx g_ecx
#define edx g_edx
#define esi g_esi
#define edi g_edi
#define esp g_esp

/* Constructor at 0x8B050 is a legitimate function entry reached through
 * the loader vtable, but it follows a neighboring function without being in
 * the original prologue-discovery table. */
void sub_0008B050(void)
{
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    PUSH32(esp, 0x0008B05Au); sub_0009DA50();
    edi = 0u;
    ebx = esi + 0x7F4u;
    MEM32(esi + 0x90u) = edi;
    MEM32(esi + 0x8Cu) = edi;
    ecx = ebx;
    MEM32(esi) = 0x001EEF84u;
    PUSH32(esp, 0x0008B07Bu); sub_0009DA50();
    MEM32(ebx + 0x90u) = edi;
    MEM32(ebx + 0x8Cu) = edi;
    ecx = esi + 0xAD0u;
    MEM32(ebx) = 0x001EEEDCu;
    PUSH32(esp, 0x0008B098u); sub_0011D980();
    MEM32(esi + 0xAE4u) = edi;
    MEM32(esi + 0xAE8u) = edi;
    MEM32(esi + 0xAECu) = edi;
    MEM32(esi + 0xAF8u) = edi;
    MEM32(esi + 0xAFCu) = edi;
    MEM32(esi + 0xB00u) = edi;
    MEM32(esi + 0xB04u) = edi;
    ecx = esi + 0x11DCu;
    MEM32(esi + 0xB9Cu) = edi;
    PUSH32(esp, 0x0008B0D3u); sub_000BAF10();
    ecx = esi + 0x18DCu;
    PUSH32(esp, 0x0008B0DEu); sub_000C2B60();
    ecx = esi + 0x5948u;
    PUSH32(esp, 0x0008B0E9u); sub_000BB360();
    ecx = esi + 0x595Cu;
    PUSH32(esp, 0x0008B0F4u); sub_000C1410();
    ecx = esi + 0x597Cu;
    PUSH32(esp, 0x0008B0FFu); sub_000B8F40();
    ebx = esi + 0x825Cu;
    PUSH32(esp, 1u);
    ecx = ebx;
    PUSH32(esp, 0x0008B10Eu); sub_000665E0();
    PUSH32(esp, 1u);
    ecx = ebx + 0x4Cu;
    PUSH32(esp, 0x0008B118u); sub_000665E0();
    MEM32(ebx + 0x2A0u) = edi;
    MEM32(ebx + 0x2A8u) = edi;
    MEM32(ebx + 0x2B0u) = edi;
    MEM32(esi + 0x8598u) = edi;
    MEM32(esi + 0x859Cu) = edi;
    MEM32(esi + 0x85A0u) = edi;
    MEM32(esi + 0x85A4u) = edi;
    MEM32(esi + 0x85A8u) = edi;
    MEM32(esi + 0x85ACu) = edi;
    MEM32(esi + 0x85B0u) = edi;
    MEM32(esi + 0x85B4u) = edi;
    eax = MEM32(esi + 0x64u) | 0x04000202u;
    MEM32(esi + 0x85C0u) = edi;
    MEM32(esi + 0x64u) = eax;
    POP32(esp, edi);
    eax = esi;
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 4u;
}

/* Tiny retail vtable thunks omitted by ordinary prologue discovery. */
void sub_000DE160(void)
{
    ecx = 0x004AD508u;
    sub_000DBC30();
}

void sub_000BB190(void)
{
    if (ecx != 0u) {
        sub_0008B050();
        return;
    }
    eax = 0u;
    esp += 4u;
}

#undef eax
#undef ebx
#undef ecx
#undef edx
#undef esi
#undef edi
#undef esp

static void godzilla_seed_mainmenu_movie_surface(uint32_t texture_address);

typedef struct {
    uint32_t subchannel;
    uint32_t method;
    uint32_t param;
} GODZILLA_KELVIN_METHOD;

/* MainMenu's retail XMV decoder normally emits one full-screen Kelvin draw
 * per decoded frame.  Until its MMX reconstruction path is lifted, remember
 * the exact draw block the title submitted during transition and resubmit
 * those same methods before each subsequent UI packet. */
static GODZILLA_KELVIN_METHOD godzilla_mainmenu_movie_block[4096];
static uint32_t godzilla_mainmenu_movie_block_count;
static uint32_t godzilla_mainmenu_movie_block_texture;
static uint32_t godzilla_host_frame;
volatile LONG godzilla_mainmenu_ready;

typedef struct {
    HANDLE read_pipe;
    HANDLE process;
    HANDLE thread;
    HANDLE reader_thread;
    HANDLE presenter_thread;
    CRITICAL_SECTION frame_lock;
    int frame_lock_initialized;
    uint8_t *frame;
    uint8_t *decode_frame;
    uint8_t *latest_frame;
    uint8_t *loop_frames;
    LONG loop_capacity;
    volatile LONG loop_frame_count;
    volatile LONG loop_complete;
    size_t received;
    ULONGLONG started_ms;
    uint32_t shown_frame;
    volatile LONG latest_generation;
    LONG uploaded_generation;
    volatile LONG eof;
    volatile LONG active;
    char name[32];
} GODZILLA_HOST_XMV;

static GODZILLA_HOST_XMV godzilla_host_xmv;
static int godzilla_host_xmv_pending_mainmenu;
static volatile LONG godzilla_host_startup_started;
static volatile LONG godzilla_host_xmv_skip_requested;
static volatile LONG godzilla_host_xmv_skip_release;
/* Natural EOF is a two-phase handoff.  Keep the final decoded frame alive
 * while the retail frontend consumes one completion edge, then release the
 * overlay on the following Present.  Closing the decoder first lets the
 * frontend's uninitialised render target replace the movie with black. */
static volatile LONG godzilla_host_xmv_eof_handoff;
static unsigned godzilla_input_command_sequence;
static volatile LONG godzilla_capture_sequence_pending;
volatile uint32_t godzilla_profile_confirm_pending;
volatile uint32_t godzilla_profile_accept_transition;

typedef struct {
    uint32_t dwPacketNumber;
    struct {
        uint16_t wButtons;
        uint8_t bAnalogButtons[8];
        int16_t sThumbLX, sThumbLY, sThumbRX, sThumbRY;
    } Gamepad;
} GODZILLA_XBOX_INPUT_STATE;

extern unsigned long xbox_InputGetState(unsigned long dwPort,
                                         GODZILLA_XBOX_INPUT_STATE *pState);

static DWORD WINAPI godzilla_host_xmv_reader(void *opaque)
{
    enum { WIDTH = 640, HEIGHT = 480, FRAME_BYTES = WIDTH * HEIGHT * 4 };
    GODZILLA_HOST_XMV *x = (GODZILLA_HOST_XMV *)opaque;

    while (InterlockedCompareExchange(&x->active, 0, 0)) {
        DWORD got = 0;
        if (!ReadFile(x->read_pipe, x->decode_frame + x->received,
                      (DWORD)(FRAME_BYTES - x->received), &got, NULL) ||
            !got)
            break;
        x->received += got;
        if (x->received == FRAME_BYTES) {
            LONG generation;
            ULONGLONG target_ms, now_ms;
            EnterCriticalSection(&x->frame_lock);
            memcpy(x->latest_frame, x->decode_frame, FRAME_BYTES);
            if (x->loop_frames && x->loop_frame_count < x->loop_capacity) {
                memcpy(x->loop_frames +
                           (size_t)x->loop_frame_count * FRAME_BYTES,
                       x->decode_frame, FRAME_BYTES);
                ++x->loop_frame_count;
            }
            generation = InterlockedIncrement(&x->latest_generation);
            LeaveCriticalSection(&x->frame_lock);
            x->received = 0;

            /* Back-pressure FFmpeg at the retail 30 Hz video rate.  Without
             * this, a background reader races through the entire movie and
             * the render thread only ever sees arbitrary future frames. */
            target_ms = x->started_ms +
                (((ULONGLONG)generation + 1ull) * 1000ull) / 30ull;
            now_ms = GetTickCount64();
            if (!getenv("GODZILLA_XMV_UNTHROTTLED") && target_ms > now_ms)
                Sleep((DWORD)(target_ms - now_ms));
        }
    }
    InterlockedExchange(&x->loop_complete, 1);
    InterlockedExchange(&x->eof, 1);
    return 0;
}

static DWORD WINAPI godzilla_host_xmv_presenter(void *opaque)
{
    enum { WIDTH = 640, HEIGHT = 480, FRAME_BYTES = WIDTH * HEIGHT * 4 };
    GODZILLA_HOST_XMV *x = (GODZILLA_HOST_XMV *)opaque;
    LARGE_INTEGER frequency, now;
    LONGLONG next_present, stats_start, period;
    unsigned presented = 0;
    LONG loop_index = 0;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&now);
    next_present = stats_start = now.QuadPart;
    period = frequency.QuadPart / 30;

    while (InterlockedCompareExchange(&x->active, 0, 0)) {
        LONG latest;
        int did_present = 0;
        QueryPerformanceCounter(&now);
        while (now.QuadPart < next_present &&
               InterlockedCompareExchange(&x->active, 0, 0)) {
            LONGLONG remaining = next_present - now.QuadPart;
            DWORD remaining_ms = (DWORD)((remaining * 1000) /
                                          frequency.QuadPart);
            Sleep(remaining_ms > 1u ? remaining_ms - 1u : 0u);
            QueryPerformanceCounter(&now);
        }
        if (!InterlockedCompareExchange(&x->active, 0, 0))
            break;

        latest = InterlockedCompareExchange(&x->latest_generation, 0, 0);
        if (InterlockedCompareExchange(&x->loop_complete, 0, 0) &&
            x->loop_frames && x->loop_frame_count > 0) {
            const LONG count = x->loop_frame_count;
            const uint8_t *loop_frame = x->loop_frames +
                (size_t)(loop_index++ % count) * FRAME_BYTES;
            d3d8_SubmitRGBAFrame(loop_frame, WIDTH * 4, FRAME_BYTES);
            did_present = 1;
        } else if (latest >= 0) {
            if (latest != x->uploaded_generation) {
                EnterCriticalSection(&x->frame_lock);
                memcpy(x->frame, x->latest_frame, FRAME_BYTES);
                x->uploaded_generation = latest;
                LeaveCriticalSection(&x->frame_lock);
            }
            d3d8_SubmitRGBAFrame(x->frame, WIDTH * 4, FRAME_BYTES);
            did_present = 1;
        }

        next_present += period;
        QueryPerformanceCounter(&now);
        if (now.QuadPart >= next_present) {
            const LONGLONG missed =
                (now.QuadPart - next_present) / period + 1;
            next_present += missed * period;
        }
        if (did_present && ++presented == 300u) {
            LONGLONG elapsed = now.QuadPart - stats_start;
            unsigned fps_milli = elapsed > 0
                ? (unsigned)(((uint64_t)presented * 1000u *
                              frequency.QuadPart) / (uint64_t)elapsed)
                : 0u;
            fprintf(stderr, "[XMV-CADENCE] frames=%u fps=%u.%03u\n",
                    presented, fps_milli / 1000u, fps_milli % 1000u);
            fflush(stderr);
            presented = 0;
            stats_start = now.QuadPart;
        }
    }
    return 0;
}

static void godzilla_host_xmv_close(void)
{
    GODZILLA_HOST_XMV *x = &godzilla_host_xmv;
    InterlockedExchange(&x->active, 0);
    if (x->read_pipe) {
        CloseHandle(x->read_pipe);
        x->read_pipe = NULL;
    }
    if (x->process) {
        if (WaitForSingleObject(x->process, 0) == WAIT_TIMEOUT)
            TerminateProcess(x->process, 0);
        CloseHandle(x->process);
    }
    if (x->reader_thread) {
        WaitForSingleObject(x->reader_thread, 1000);
        CloseHandle(x->reader_thread);
    }
    if (x->presenter_thread) {
        WaitForSingleObject(x->presenter_thread, 1000);
        CloseHandle(x->presenter_thread);
    }
    if (x->thread) CloseHandle(x->thread);
    if (x->frame_lock_initialized)
        DeleteCriticalSection(&x->frame_lock);
    free(x->frame);
    free(x->decode_frame);
    free(x->latest_frame);
    free(x->loop_frames);
    memset(x, 0, sizeof(*x));
}

void godzilla_host_xmv_end_mainmenu(void)
{
    if (_stricmp(godzilla_host_xmv.name, "MainMenu") != 0)
        return;
    godzilla_mainmenu_movie_block_count = 0u;
    godzilla_mainmenu_movie_block_texture = 0u;
    InterlockedExchange(&godzilla_mainmenu_ready, 0);
    godzilla_host_xmv_close();
    fprintf(stderr,
            "[HOST-XMV] released MainMenu movie surface for PlayerSelect\n");
    fflush(stderr);
}

static void godzilla_host_xmv_begin_name(const char *name)
{
    enum { WIDTH = 640, HEIGHT = 480, FRAME_BYTES = WIDTH * HEIGHT * 4 };
    SECURITY_ATTRIBUTES security = { sizeof(security), NULL, TRUE };
    STARTUPINFOA startup;
    PROCESS_INFORMATION process;
    HANDLE write_pipe = NULL, error_log = INVALID_HANDLE_VALUE;
    char host_root[MAX_PATH], movie[MAX_PATH * 2], ffmpeg[MAX_PATH * 2];
    char log_path[MAX_PATH * 2], command[4096], *slash;
    GODZILLA_HOST_XMV *x = &godzilla_host_xmv;

    godzilla_host_xmv_close();
    strncpy_s(x->name, sizeof(x->name), name, _TRUNCATE);
    x->name[sizeof(x->name) - 1] = 0;
    if (!x->name[0] || !GetModuleFileNameA(NULL, host_root, sizeof(host_root)))
        return;
    slash = strrchr(host_root, '\\');
    if (slash) *slash = 0;
    slash = strrchr(host_root, '\\');
    if (slash) *slash = 0;
    sprintf_s(ffmpeg, sizeof(ffmpeg), "%s\\tools\\bin\\ffmpeg.exe", host_root);
    sprintf_s(log_path, sizeof(log_path), "%s\\run-startup-ffmpeg.err.log", host_root);
    if (strcmp(x->name, "startup-sequence") == 0) {
        sprintf_s(command, sizeof(command),
                  "\"%s\" -nostdin -hide_banner -loglevel error "
                  "-threads 1 -filter_threads 1 "
                  "-i \"%s\\game_files\\shelldata\\atari.xmv\" "
                  "-i \"%s\\game_files\\shelldata\\toho.xmv\" "
                  "-i \"%s\\game_files\\shelldata\\pipeworks.xmv\" "
                  "-i \"%s\\game_files\\shelldata\\gzintro.xmv\" "
                  "-i \"%s\\game_files\\shelldata\\dolby.xmv\" "
                  "-filter_complex \"[0:v][1:v][2:v][3:v][4:v]"
                  "concat=n=5:v=1:a=0,scale=640:480,format=rgba[v]\" "
                  "-map \"[v]\" -an -sn -dn -f rawvideo pipe:1",
                  ffmpeg, host_root, host_root, host_root, host_root, host_root);
    } else {
        sprintf_s(movie, sizeof(movie), "%s\\game_files\\shelldata\\%s.xmv",
                  host_root, x->name);
        if (_stricmp(x->name, "MainMenu") == 0) {
            /* Retail's menu reel loops for as long as the frontend remains
             * active.  Keeping FFmpeg alive also lets the independent 30 Hz
             * scanout continue animating while guest bundle construction is
             * briefly busy during submenu entry/exit. */
            sprintf_s(command, sizeof(command),
                      "\"%s\" -nostdin -hide_banner -loglevel error "
                      "-threads 1 -filter_threads 1 "
                      "-i \"%s\" "
                      "-map 0:v:0 -an -sn -dn -vf scale=640:480 "
                      "-pix_fmt rgba -f rawvideo pipe:1", ffmpeg, movie);
        } else {
            sprintf_s(command, sizeof(command),
                      "\"%s\" -nostdin -hide_banner -loglevel error "
                      "-threads 1 -filter_threads 1 -i \"%s\" "
                      "-map 0:v:0 -an -sn -dn -vf scale=640:480 "
                      "-pix_fmt rgba -f rawvideo pipe:1", ffmpeg, movie);
        }
    }
    memset(&startup, 0, sizeof(startup));
    memset(&process, 0, sizeof(process));
    startup.cb = sizeof(startup);
    if (!CreatePipe(&x->read_pipe, &write_pipe, &security, 0) ||
        !SetHandleInformation(x->read_pipe, HANDLE_FLAG_INHERIT, 0))
        goto fail;
    error_log = CreateFileA(log_path, GENERIC_WRITE, FILE_SHARE_READ, &security,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (error_log == INVALID_HANDLE_VALUE) goto fail;
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = write_pipe;
    startup.hStdError = error_log;
    if (!CreateProcessA(NULL, command, NULL, NULL, TRUE, CREATE_NO_WINDOW,
                        NULL, host_root, &startup, &process))
        goto fail;
    CloseHandle(write_pipe); write_pipe = NULL;
    CloseHandle(error_log); error_log = INVALID_HANDLE_VALUE;
    x->process = process.hProcess;
    x->thread = process.hThread;
    SetPriorityClass(x->process, BELOW_NORMAL_PRIORITY_CLASS);
    x->frame = (uint8_t *)malloc(FRAME_BYTES);
    x->decode_frame = (uint8_t *)malloc(FRAME_BYTES);
    x->latest_frame = (uint8_t *)malloc(FRAME_BYTES);
    if (_stricmp(x->name, "MainMenu") == 0) {
        x->loop_capacity = 120;
        x->loop_frames = (uint8_t *)malloc(
            (size_t)x->loop_capacity * FRAME_BYTES);
    }
    if (!x->frame || !x->decode_frame || !x->latest_frame ||
        (x->loop_capacity && !x->loop_frames)) goto fail;
    InitializeCriticalSection(&x->frame_lock);
    x->frame_lock_initialized = 1;
    x->started_ms = GetTickCount64();
    x->shown_frame = UINT32_MAX;
    x->latest_generation = -1;
    x->uploaded_generation = -1;
    InterlockedExchange(&x->active, 1);
    InterlockedExchange(&godzilla_host_xmv_eof_handoff, 0);
    x->reader_thread = CreateThread(NULL, 0, godzilla_host_xmv_reader,
                                    x, 0, NULL);
    if (!x->reader_thread) goto fail;
    /* Startup movies own scanout and therefore use the independent presenter.
     * MainMenu.XMV is different: retail samples it as a texture underneath
     * the menu geometry.  Publishing it directly from this thread races the
     * completed guest frame and produces alternating movie/black scanout.
     * The Kelvin texture bridge below supplies MainMenu's decoded frames to
     * the retail draw instead. */
    if (_stricmp(x->name, "MainMenu") != 0) {
        x->presenter_thread = CreateThread(NULL, 0, godzilla_host_xmv_presenter,
                                          x, 0, NULL);
        if (!x->presenter_thread) goto fail;
        SetThreadPriority(x->presenter_thread, THREAD_PRIORITY_HIGHEST);
    }
    /* MainMenu's host-decoded movie is only requested after the retail
     * frontend has constructed its nine-entry menu.  Keep this as the
     * durable phase boundary for input shims; the scene callback's animation
     * phase can remain below eight during ordinary menu operation. */
    if (_stricmp(x->name, "MainMenu") == 0)
        InterlockedExchange(&godzilla_mainmenu_ready, 1);
    fprintf(stderr, "[HOST-XMV] playing real stream '%s' through PVIDEO bridge\n",
            x->name);
    fflush(stderr);
    return;
fail:
    if (write_pipe) CloseHandle(write_pipe);
    if (error_log != INVALID_HANDLE_VALUE) CloseHandle(error_log);
    godzilla_host_xmv_close();
}

void godzilla_host_xmv_begin(uint32_t name_va)
{
    char name[64];
    uint32_t i;
    for (i = 0; i + 1u < sizeof(name); ++i) {
        name[i] = (char)MEM8(name_va + i);
        if (name[i] == 0)
            break;
    }
    name[sizeof(name) - 1u] = 0;
    if (godzilla_host_xmv.active &&
        strcmp(godzilla_host_xmv.name, "startup-sequence") == 0 &&
        _stricmp(name, "MainMenu") == 0) {
        godzilla_host_xmv_pending_mainmenu = 1;
        return;
    }
    godzilla_host_xmv_begin_name(name);
}

void godzilla_host_xmv_begin_sequence(void)
{
    /* Host graphics can prime the retail reel while the guest finishes shell
     * construction.  The later recovered startup event must acknowledge the
     * same sequence rather than closing/restarting FFmpeg from frame zero. */
    if (InterlockedExchange(&godzilla_host_startup_started, 1))
        return;
    godzilla_host_xmv_begin_name("startup-sequence");
}

int godzilla_host_xmv_startup_active(void)
{
    return godzilla_host_xmv.active &&
           strcmp(godzilla_host_xmv.name, "startup-sequence") == 0;
}

int godzilla_host_xmv_startup_started(void)
{
    return InterlockedCompareExchange(&godzilla_host_startup_started, 0, 0) != 0;
}

static int godzilla_host_xmv_present(void)
{
    enum { WIDTH = 640, HEIGHT = 480, FRAME_BYTES = WIDTH * HEIGHT * 4 };
    GODZILLA_HOST_XMV *x = &godzilla_host_xmv;
    LONG latest;
    if (!x->active) return 0;
    /* A host-decoded one-shot movie can own presentation while the guest's
     * normal XInput call is not reached.  Poll the same controller backend
     * here and turn a Start edge into the retail movie-skip event.  MainMenu
     * is a looping background and must never be dismissed by this path. */
    if (_stricmp(x->name, "MainMenu") != 0) {
        static uint16_t previous_buttons;
        GODZILLA_XBOX_INPUT_STATE input;
        uint16_t buttons = 0;
        if (xbox_InputGetState(0u, &input) == 0u)
            buttons = input.Gamepad.wButtons;
        if ((buttons & 0x0010u) && !(previous_buttons & 0x0010u)) {
            InterlockedExchange(&godzilla_host_xmv_skip_requested, 1);
            InterlockedExchange(&godzilla_host_xmv_skip_release, 1);
            fprintf(stderr, "[HOST-XMV] retail startup skip input received\n");
        }
        previous_buttons = buttons;
    }
    /* The host decoder presents synchronously, so the retail update path may
     * not reach XInputGetState while startup movies are on screen.  Consume
     * the same one-shot Start record here and share its sequence with the
     * normal controller bridge; this preserves one press as one edge and
     * prevents a movie-skip Start from leaking into the later title screen. */
    {
        static unsigned overlay_sequence;
        const char *command_path = getenv("GODZILLA_INPUT_COMMAND_FILE");
        FILE *command = NULL;
        if (command_path && fopen_s(&command, command_path, "rb") == 0) {
            char line[64] = {0};
            char action[16] = {0};
            unsigned sequence = 0;
            if (fgets(line, sizeof(line), command) &&
                sscanf_s(line, "%u %15s", &sequence, action,
                         (unsigned)sizeof(action)) == 2 &&
                sequence != 0u &&
                sequence != overlay_sequence) {
                overlay_sequence = sequence;
                if (_stricmp(action, "start") == 0 &&
                    _stricmp(x->name, "MainMenu") != 0)
                    InterlockedExchange(&godzilla_host_xmv_skip_requested, 1);
                if (_stricmp(action, "capture") == 0)
                    InterlockedExchange(&godzilla_capture_sequence_pending,
                                        (LONG)sequence);
                fprintf(stderr, "[PARITY-INPUT] sequence=%u action=%s overlay=%s\n",
                        sequence, action, x->name);
            }
            fclose(command);
        }
    }
    if (InterlockedExchange(&godzilla_host_xmv_skip_requested, 0) &&
        _stricmp(x->name, "MainMenu") != 0) {
        char skipped_name[sizeof(x->name)];
        const int begin_mainmenu = godzilla_host_xmv_pending_mainmenu;
        strncpy_s(skipped_name, sizeof(skipped_name), x->name, _TRUNCATE);
        godzilla_host_xmv_pending_mainmenu = 0;
        godzilla_host_xmv_close();
        if (begin_mainmenu)
            godzilla_host_xmv_begin_name("MainMenu");
        fprintf(stderr, "[HOST-XMV] retail skip accepted for '%s'\n",
                skipped_name);
        fflush(stderr);
        return godzilla_host_xmv.active;
    }
    latest = InterlockedCompareExchange(&x->latest_generation, 0, 0);
    if (InterlockedCompareExchange(&x->eof, 0, 0) &&
        x->uploaded_generation ==
            InterlockedCompareExchange(&x->latest_generation, 0, 0)) {
        if (_stricmp(x->name, "MainMenu") == 0 &&
            x->loop_frame_count > 0)
            return 1;
        if (_stricmp(x->name, "startup-sequence") == 0) {
            LONG handoff = InterlockedCompareExchange(
                &godzilla_host_xmv_eof_handoff, 1, 0);
            if (handoff == 0) {
                fprintf(stderr,
                        "[HOST-XMV] startup EOF latched; waiting for frontend completion\n");
                fflush(stderr);
                godzilla_complete_startup_sequence();
                InterlockedExchange(&godzilla_host_xmv_eof_handoff, 2);
                return 1;
            }
            if (handoff == 1)
                return 1;
            fprintf(stderr,
                    "[HOST-XMV] frontend consumed startup completion; releasing final frame\n");
            fflush(stderr);
        }
        const int begin_mainmenu = godzilla_host_xmv_pending_mainmenu;
        godzilla_host_xmv_pending_mainmenu = 0;
        godzilla_host_xmv_close();
        if (begin_mainmenu) {
            godzilla_host_xmv_begin_name("MainMenu");
            return godzilla_host_xmv.active;
        }
        return 0;
    }
    return 1;
}

static int godzilla_trace_enabled(void)
{
    static int enabled = -1;
    if (enabled < 0)
        enabled = getenv("GODZILLA_TRACE_FRAME") != NULL;
    return enabled;
}

/* Queue completed guest frames and expose only the newest one on an exact
 * monotonic 30 Hz host schedule.  An empty slot leaves the swapchain front
 * buffer untouched instead of presenting a discard-mode backbuffer. */
static int godzilla_present_due_30hz(int completed_frame)
{
    static LARGE_INTEGER frequency;
    static LONGLONG next_present;
    static LONGLONG stats_start;
    static uint32_t pending;
    static uint32_t presented;
    LARGE_INTEGER now;
    LONGLONG period;

    if (!frequency.QuadPart)
        QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&now);
    period = frequency.QuadPart / 30;
    if (!next_present) {
        next_present = now.QuadPart;
        stats_start = now.QuadPart;
    }
    if (completed_frame)
        pending = 1u;
    if (!pending)
        return 0;

    /* A gate that merely returns early depends on the guest calling back at
     * exactly the next deadline.  Asset work makes those callbacks irregular
     * and measured output fell to 25.5 FPS.  Pace a completed frame here:
     * sleep for the coarse portion, then yield through the sub-millisecond
     * remainder so each scanout lands on the 33.333 ms host timeline. */
    while (now.QuadPart < next_present) {
        LONGLONG remaining = next_present - now.QuadPart;
        DWORD remaining_ms = (DWORD)((remaining * 1000) /
                                      frequency.QuadPart);
        if (remaining_ms > 1u)
            Sleep(remaining_ms - 1u);
        else
            Sleep(0);
        QueryPerformanceCounter(&now);
    }

    pending = 0u;
    next_present += period;
    /* Never burst several old frames after a debugger stop, decoder stall, or
     * slow asset load.  Drop timing debt and resume from the current clock. */
    if (now.QuadPart - next_present > period)
        next_present = now.QuadPart + period;
    if (++presented >= 300u) {
        LONGLONG elapsed = now.QuadPart - stats_start;
        unsigned fps_milli = elapsed > 0
            ? (unsigned)(((uint64_t)presented * 1000u * frequency.QuadPart) /
                         (uint64_t)elapsed)
            : 0u;
        fprintf(stderr,
                "[PRESENT-CADENCE] frames=%u fps=%u.%03u\n",
                presented, fps_milli / 1000u, fps_milli % 1000u);
        fflush(stderr);
        presented = 0u;
        stats_start = now.QuadPart;
    }
    return 1;
}

static size_t godzilla_decode_mainmenu_xmv(uint8_t *frames, size_t capacity,
                                           const char *host_root,
                                           const char *ffmpeg)
{
    SECURITY_ATTRIBUTES security = { sizeof(security), NULL, TRUE };
    STARTUPINFOA startup;
    PROCESS_INFORMATION process;
    HANDLE read_pipe = NULL, write_pipe = NULL, error_log = INVALID_HANDLE_VALUE;
    char command[4096], movie_path[MAX_PATH * 2], log_path[MAX_PATH * 2];
    size_t received = 0;
    BOOL started = FALSE;

    sprintf_s(movie_path, sizeof(movie_path),
              "%s\\game_files\\shelldata\\mainmenu.xmv", host_root);
    sprintf_s(log_path, sizeof(log_path),
              "%s\\run-mainmenu-ffmpeg.err.log", host_root);
    sprintf_s(command, sizeof(command),
              "\"%s\" -nostdin -hide_banner -loglevel error "
              "-i \"%s\" -map 0:v:0 -an -sn -dn -frames:v 90 "
              "-pix_fmt yuyv422 -f rawvideo pipe:1",
              ffmpeg, movie_path);

    memset(&startup, 0, sizeof(startup));
    memset(&process, 0, sizeof(process));
    startup.cb = sizeof(startup);
    if (!CreatePipe(&read_pipe, &write_pipe, &security, 0) ||
        !SetHandleInformation(read_pipe, HANDLE_FLAG_INHERIT, 0))
        goto cleanup;
    error_log = CreateFileA(log_path, GENERIC_WRITE, FILE_SHARE_READ, &security,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (error_log == INVALID_HANDLE_VALUE)
        goto cleanup;
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = write_pipe;
    startup.hStdError = error_log;
    started = CreateProcessA(NULL, command, NULL, NULL, TRUE, CREATE_NO_WINDOW,
                             NULL, host_root, &startup, &process);
    CloseHandle(write_pipe);
    write_pipe = NULL;
    CloseHandle(error_log);
    error_log = INVALID_HANDLE_VALUE;
    if (!started)
        goto cleanup;

    while (received < capacity) {
        DWORD chunk = 0;
        DWORD request = (DWORD)((capacity - received) > 0x00100000u
                                    ? 0x00100000u : (capacity - received));
        if (!ReadFile(read_pipe, frames + received, request, &chunk, NULL) ||
            chunk == 0)
            break;
        received += chunk;
    }
    CloseHandle(read_pipe);
    read_pipe = NULL;
    if (WaitForSingleObject(process.hProcess, 5000) == WAIT_TIMEOUT) {
        TerminateProcess(process.hProcess, 1);
        WaitForSingleObject(process.hProcess, 1000);
    }

cleanup:
    if (read_pipe) CloseHandle(read_pipe);
    if (write_pipe) CloseHandle(write_pipe);
    if (error_log != INVALID_HANDLE_VALUE) CloseHandle(error_log);
    if (started) {
        CloseHandle(process.hThread);
        CloseHandle(process.hProcess);
    }
    return received;
}

/* Feed the retail title's live D3D pushbuffer to the shared NV2A Kelvin
 * translator.  XDK 5233 stores the ring bounds at device +24/+28 and the
 * producer cursor at +0.  This is the same contract verified by the sibling
 * Save the Earth recomp; DAMM's device pointer is at 0x00134078. */
static uint32_t godzilla_pb_walk(uint32_t addr, uint32_t end,
                                 uint32_t *methods, uint32_t *draws,
                                 uint32_t *malformed, int dry)
{
    uint32_t ret_addr = 0, ret_end = 0, guard = 0, last_flip = 0;
    static uint32_t texture0_offset[8];
    static uint32_t texture0_format[8];
    static uint32_t texture0_control1[8];
    static uint32_t texture0_image_rect[8];
    static unsigned mainmenu_texture_trace;
    static GODZILLA_KELVIN_METHOD candidate_block[4096];
    static uint32_t candidate_count;
    static int candidate_is_movie;
    int retained_movie_replayed = 0;
    int in_call = 0;
    while (addr < end && guard++ < 4000000u) {
        uint32_t header = MEM32(addr);
        if (header == 0) { addr += 4; continue; }
        if ((header & 0xE0000003u) == 0x20000000u || (header & 3u) == 1u) {
            if (in_call) {
                addr = (header & 3u) == 1u ? (header & 0xFFFFFFFCu)
                                           : (header & 0x1FFFFFFCu);
                if (addr >= 0x04000000u) { ++*malformed; break; }
                end = addr + 0x01000000u;
                continue;
            }
            break;
        }
        if ((header & 3u) == 2u) {
            if (in_call || (header & 0xFFFFFFFCu) >= 0x04000000u) {
                ++*malformed;
                addr += 4;
                continue;
            }
            ret_addr = addr + 4;
            ret_end = end;
            in_call = 1;
            addr = header & 0xFFFFFFFCu;
            end = addr + 0x01000000u;
            continue;
        }
        if (header == 0x00020000u) {
            if (!in_call) { ++*malformed; addr += 4; continue; }
            in_call = 0;
            addr = ret_addr;
            end = ret_end;
            continue;
        }
        {
            uint32_t kind = header & 0xE0030003u;
            uint32_t count = (header >> 18) & 0x7FFu;
            uint32_t method = header & 0x1FFCu;
            uint32_t subchannel = (header >> 13) & 7u;
            int noninc;
            if (kind == 0x00000000u) noninc = 0;
            else if (kind == 0x40000000u) noninc = 1;
            else { ++*malformed; addr += 4; continue; }
            if (!count) { addr += 4; continue; }
            if (addr + 4u + 4u * count > end) { ++*malformed; break; }
            int flip = 0;
            for (uint32_t i = 0; i < count; ++i) {
                uint32_t m = noninc ? method : method + i * 4u;
                uint32_t param = MEM32(addr + 4u + i * 4u);
                if (m == 0x0130u) flip = 1;
                if (m == 0x1B00u)
                    texture0_offset[subchannel] = param;
                else if (m == 0x1B04u)
                    texture0_format[subchannel] = param;
                else if (m == 0x1B10u)
                    texture0_control1[subchannel] = param;
                else if (m == 0x1B1Cu)
                    texture0_image_rect[subchannel] = param;
                if (dry) continue;
                if (godzilla_host_xmv.active &&
                    _stricmp(godzilla_host_xmv.name, "MainMenu") == 0 &&
                    candidate_count <
                        (uint32_t)(sizeof(candidate_block) /
                                   sizeof(candidate_block[0]))) {
                    candidate_block[candidate_count].subchannel = subchannel;
                    candidate_block[candidate_count].method = m;
                    candidate_block[candidate_count].param = param;
                    ++candidate_count;
                }
                if (m == 0x17FCu && param != 0u &&
                    godzilla_host_xmv.active &&
                    _stricmp(godzilla_host_xmv.name, "MainMenu") == 0) {
                    uint32_t color = (texture0_format[subchannel] >> 8) & 0xFFu;
                    uint32_t width = texture0_image_rect[subchannel] >> 16;
                    uint32_t height = texture0_image_rect[subchannel] & 0xFFFFu;
                    if (mainmenu_texture_trace < 64u) {
                        fprintf(stderr,
                                "[MAINMENU-TEXTURE] #%u sub=%u offset=%08X "
                                "format=%08X control1=%08X rect=%08X %ux%u\n",
                                mainmenu_texture_trace, subchannel,
                                texture0_offset[subchannel],
                                texture0_format[subchannel],
                                texture0_control1[subchannel],
                                texture0_image_rect[subchannel], width, height);
                    }
                    ++mainmenu_texture_trace;
                    if ((color == 0x24u || color == 0x25u) &&
                        width == 640u && height == 480u) {
                        candidate_is_movie = 1;
                        godzilla_seed_mainmenu_movie_surface(
                            texture0_offset[subchannel]);
                    }
                }
                kelvin_method(subchannel, m, param);
                /* The ordinary frame clear is followed by UI state and draw
                 * commands.  Restore the missing retail XMV submission here:
                 * after the clear, but before those commands configure and
                 * draw PRESS START/menu glyphs over it. */
                if (!retained_movie_replayed && m == 0x1D94u &&
                    godzilla_mainmenu_movie_block_count != 0u &&
                    godzilla_host_xmv.active &&
                    _stricmp(godzilla_host_xmv.name, "MainMenu") == 0) {
                    godzilla_seed_mainmenu_movie_surface(
                        godzilla_mainmenu_movie_block_texture);
                    for (uint32_t j = 0;
                         j < godzilla_mainmenu_movie_block_count; ++j) {
                        kelvin_method(
                            godzilla_mainmenu_movie_block[j].subchannel,
                            godzilla_mainmenu_movie_block[j].method,
                            godzilla_mainmenu_movie_block[j].param);
                    }
                    retained_movie_replayed = 1;
                }
                if (m == 0x17FCu && param == 0u && candidate_count != 0u) {
                    if (candidate_is_movie) {
                        memcpy(godzilla_mainmenu_movie_block,
                               candidate_block,
                               candidate_count * sizeof(candidate_block[0]));
                        godzilla_mainmenu_movie_block_count = candidate_count;
                        godzilla_mainmenu_movie_block_texture =
                            texture0_offset[subchannel];
                        fprintf(stderr,
                                "[MAINMENU-XMV] retained retail movie draw "
                                "block methods=%u texture=%08X\n",
                                candidate_count,
                                godzilla_mainmenu_movie_block_texture);
                    }
                    candidate_count = 0u;
                    candidate_is_movie = 0;
                }
                if (m == 0x17FCu && param != 0) ++*draws;
                ++*methods;
            }
            addr += 4u + 4u * count;
            if (flip && !in_call) last_flip = addr;
        }
    }
    return last_flip;
}

static uint32_t godzilla_replay_pushbuffer(uint32_t start, uint32_t end,
                                           uint32_t frame, uint32_t *methods,
                                           uint32_t *draws, uint32_t *malformed)
{
    uint32_t m0 = 0, d0 = 0, b0 = 0;
    uint32_t cut = godzilla_pb_walk(start, end, &m0, &d0, &b0, 1);
    extern int g_kelvin_log_draws;
    static uint32_t prev_draws;

    /* The CPU can already have begun the next frame when this hook runs.
     * Present only through the last completed FLIP_STALL; otherwise the next
     * frame's clear erases the menu immediately before our host Present. */
    if (cut)
        end = cut;
    g_kelvin_log_draws =
        (godzilla_trace_enabled() &&
         ((frame <= 12u) ||
          (frame >= 200u && frame <= 204u) ||
          (prev_draws == 1u && frame <= 590u))) ||
        (godzilla_host_xmv.active &&
         _stricmp(godzilla_host_xmv.name, "MainMenu") == 0 &&
         frame >= 128u && (frame & (frame - 1u)) == 0u);
    godzilla_pb_walk(start, end, methods, draws, malformed, 0);
    kelvin_end_frame();
    g_kelvin_log_draws = 0;
    prev_draws = *draws;
    return end;
}

/* The retail WMV2/XMV decoder relies heavily on MMX reconstruction routines.
 * Those instructions are not lifted yet, so decode MainMenu.XMV live through
 * FFmpeg and feed each due YUY2 frame into the retail movie surface.  Unlike
 * the old frame cache, this reads the original XMV at runtime and paces it from
 * a monotonic 30 Hz movie clock.  The game's texture state, coordinates,
 * blending, menu geometry and presentation remain untouched.  This bridge can
 * be removed once the MMX instruction family lands. */
static void godzilla_seed_mainmenu_movie_surface(uint32_t texture_address)
{
    enum { FRAME_BYTES = 640 * 480 * 2, EXPECTED_FRAMES = 90 };
    static uint8_t *frames;
    static size_t frame_count;
    static ULONGLONG movie_start_ms;
    static uint32_t last_seed_frame = UINT32_MAX;
    static int attempted;

    /* MainMenu's WMV2 reconstruction still contains unlifted MMX, so feed the
     * original XMV frames into its genuine YUY2 texture regardless of whether
     * the optional startup-movie skip mode is enabled. */
    if (!(godzilla_host_xmv.active &&
          _stricmp(godzilla_host_xmv.name, "MainMenu") == 0))
        return;
    if (!attempted) {
        const char *ffmpeg = getenv("FFMPEG_PATH");
        char host_root[MAX_PATH];
        char default_ffmpeg[MAX_PATH * 2];
        char *slash;
        attempted = 1;
        if (!GetModuleFileNameA(NULL, host_root, sizeof(host_root)))
            host_root[0] = 0;
        slash = strrchr(host_root, '\\');
        if (slash)
            *slash = 0; /* bin */
        slash = strrchr(host_root, '\\');
        if (slash)
            *slash = 0; /* project root */
        if (!ffmpeg || !*ffmpeg) {
            sprintf_s(default_ffmpeg, sizeof(default_ffmpeg),
                      "%s\\tools\\bin\\ffmpeg.exe", host_root);
            ffmpeg = default_ffmpeg;
        }
        frames = (uint8_t *)malloc((size_t)EXPECTED_FRAMES * FRAME_BYTES);
        if (frames)
            frame_count = godzilla_decode_mainmenu_xmv(
                frames, (size_t)EXPECTED_FRAMES * FRAME_BYTES,
                host_root, ffmpeg) / FRAME_BYTES;
        if (frame_count != EXPECTED_FRAMES) {
            fprintf(stderr,
                    "[MAINMENU-XMV] runtime decode failed winerr=%lu ffmpeg='%s'\n",
                    (unsigned long)GetLastError(), ffmpeg);
            free(frames);
            frames = NULL;
        } else {
            movie_start_ms = GetTickCount64();
            fprintf(stderr,
                    "[MAINMENU-XMV] decoded %u runtime frames; 640x480 at 30fps\n",
                    (unsigned)frame_count);
        }
    }
    /* The same movie texture can be submitted by more than one draw in a
     * pushbuffer.  Advance once per presented game frame, not once per draw. */
    if (frames && last_seed_frame != godzilla_host_frame) {
        uint64_t due_frame =
            ((uint64_t)(GetTickCount64() - movie_start_ms) * 30u) / 1000u;
        size_t frame_index = (size_t)(due_frame % frame_count);
        memcpy((void *)XBOX_PTR(texture_address),
               frames + frame_index * FRAME_BYTES, FRAME_BYTES);
        last_seed_frame = godzilla_host_frame;
    }
}

void godzilla_d3d_frame_hook(void)
{
    static uint32_t frame;
    static uint32_t replay_cursor;
    static int initialized;
    int frame_updated = 0;
    int startup_overlay_active;
    uint32_t device = MEM32(0x00134078u);
    uint32_t methods = 0, draws = 0, malformed = 0;

    ++frame;
    godzilla_host_frame = frame;
    godzilla_pump_frontend_completion();
    /* Update the decoded XMV surface before replaying the frame's Kelvin
     * commands.  MainMenu.XMV is the retail animated background; the game
     * draws its 3D menu geometry over that movie in the same frame.  Returning
     * here used to skip the vertex-program uploads and menu draws for the
     * entire movie, after which the pushbuffer ring had already wrapped. */
    godzilla_host_xmv_present();
    /* The startup reel owns scanout, but the NV2A must still consume every
     * frontend pushbuffer behind it.  Deferring translation until movie EOF
     * loses the one-shot title-scene setup after the 2 MiB ring wraps; only
     * the repeating PRESS START quad survives and appears over black.  Replay
     * continuously, suppressing only guest presentation while the overlay is
     * visible. */
    startup_overlay_active = godzilla_host_xmv.active &&
        strcmp(godzilla_host_xmv.name, "startup-sequence") == 0;
    if (!getenv("GODZILLA_SKIP_MOVIES") &&
        !godzilla_host_xmv_startup_started() && frame < 200u)
        return;
    if (device >= 0x00010000u && device < 0x04000000u) {
        uint32_t pb_start = MEM32(device + 0x24u);
        uint32_t pb_end = MEM32(device + 0x28u);
        uint32_t pb_cursor = MEM32(device + 0x00u);
        if (pb_start >= 0x00010000u && pb_start < pb_end &&
            pb_end <= 0x04000000u && pb_cursor >= pb_start &&
            pb_cursor <= pb_end && pb_end - pb_start <= 0x00400000u) {
            if (!initialized) {
                kelvin_init();
                initialized = 1;
                /* Rebuild the persistent Kelvin state accumulated before the
                 * menu checkpoint (vertex program, combiners, textures and
                 * surface selection), then continue incrementally. */
                replay_cursor = pb_start;
                fprintf(stderr,
                        "[PB-ATTACH] frame=%u device=%08X ring=%08X-%08X "
                        "cursor=%08X\n",
                        frame, device, pb_start, pb_end, pb_cursor);
            }
            if (replay_cursor < pb_start || replay_cursor > pb_end ||
                pb_cursor < replay_cursor)
                replay_cursor = pb_start;
            if (godzilla_host_xmv.active &&
                _stricmp(godzilla_host_xmv.name, "MainMenu") == 0 &&
                (frame <= 16u || (frame & (frame - 1u)) == 0u)) {
                fprintf(stderr,
                        "[MAINMENU-PB] frame=%u replay=%08X cursor=%08X "
                        "ring=%08X-%08X delta=%u\n",
                        frame, replay_cursor, pb_cursor, pb_start, pb_end,
                        pb_cursor >= replay_cursor ?
                            pb_cursor - replay_cursor : 0u);
            }
            if (pb_cursor > replay_cursor) {
                frame_updated = 1;
                replay_cursor = godzilla_replay_pushbuffer(
                    replay_cursor, pb_cursor, frame,
                    &methods, &draws, &malformed);
            } else {
                kelvin_end_frame();
            }
            if (malformed || (godzilla_trace_enabled() &&
                (frame <= 208u || draws || (frame % 300u) == 0u))) {
                fprintf(stderr,
                        "[PB-LIVE] frame=%u device=%08X ring=%08X-%08X "
                        "cursor=%08X methods=%u draws=%u malformed=%u\n",
                        frame, device, pb_start, pb_end, pb_cursor,
                        methods, draws, malformed);
            }
        } else if (frame <= 8u || (frame % 300u) == 0u) {
            fprintf(stderr,
                    "[PB-WAIT] frame=%u device=%08X fields=%08X,%08X,%08X "
                    "put=%08X getptr=%08X\n",
                    frame, device, MEM32(device), pb_start, pb_end,
                    MEM32(device + 0x2Cu), MEM32(device + 0x30u));
        }
    }
    /* The retail frontend renders at 30 Hz while the emulated interrupt clock
     * ticks at 60 Hz.  The host swapchain uses DISCARD, so presenting again on
     * an empty tick exposes an undefined (usually black) backbuffer and makes
     * menus flash at the vblank rate.  Keep the last completed frame scanned
     * out until the guest submits another pushbuffer frame. */
    if (frame_updated) {
        LONG capture_sequence =
            InterlockedExchange(&godzilla_capture_sequence_pending, 0);
        if (capture_sequence > 0) {
            char capture_path[MAX_PATH];
            sprintf_s(capture_path, sizeof(capture_path),
                      "build-release\\parity_capture_%06ld.bmp",
                      capture_sequence);
            d3d8_capture_backbuffer_bmp_public(capture_path);
        }
    }
    if (!startup_overlay_active && godzilla_present_due_30hz(frame_updated))
        d3d8_PresentFrame();
}

typedef void (*recomp_func_t)(void);

extern void sub_000125E0(void);
extern void sub_00015C50(void);
extern void sub_0002FCD0(void);
extern void sub_000305B0(void);
extern void sub_00030600(void);
extern void sub_000306A0(void);
extern void sub_00033960(void);
extern void sub_0003EDA0(void);
extern void sub_0004F770(void);
extern void sub_00037B80(void);
extern void sub_000386A0(void);
extern void sub_0003EE90(void);
extern void sub_0003EDE0(void);
extern void sub_0003F320(void);
extern void sub_000688D0(void);
extern void sub_00068AE0(void);
extern void sub_00073870(void);
extern void sub_000BAF80(void);
extern void sub_000DA450(void);
extern void sub_000DE5C0(void);
extern void sub_000DFB60(void);
extern void sub_000E9DE0(void);
extern void sub_000E9DF0(void);
extern void sub_000E2390(void);
extern void sub_000EA980(void);
extern void sub_000EAC60(void);
extern void sub_000EF2F0(void);
extern void sub_000EF780(void);
extern void sub_000F0210(void);
extern void sub_000F2B40(void);
extern void sub_00102AE0(void);
extern void sub_0010C760(void);
extern void sub_0011EEF0(void);
extern void sub_001553F1(void);
extern void sub_00159E00(void);

/* Shared epilogue fragment of the title-screen selection callback.  The
 * detector splits the jump-table body at 0xE4820/0xE48C3, but 0xE48E7 is only
 * `pop esi; ret 8` and is therefore not independently liftable. */
void sub_000E48E7(void)
{
    POP32(g_esp, g_esi);
    g_esp += 12u;
}

/*
 * The Xbox title uses RDTSC as its high-resolution media clock and assumes
 * the retail CPU's 733,333,333 Hz rate.  The generic lifter currently leaves
 * RDTSC as a TODO, which made XMV time permanently reuse stale EDX:EAX and
 * froze the first startup movie on its first decoded frame.  Scale the host
 * wall-clock timestamp into the Xbox TSC domain.  TIME_UTC has sub-second
 * resolution on the supported runtimes; the fixed epoch is harmless because
 * all title users subtract a captured baseline.
 */
uint64_t godzilla_xbox_rdtsc(void)
{
    struct timespec now;
    const uint64_t xbox_hz = 733333333ull;

    if (timespec_get(&now, TIME_UTC) != TIME_UTC)
        return 1ull;

    return (uint64_t)now.tv_sec * xbox_hz +
           ((uint64_t)now.tv_nsec * xbox_hz) / 1000000000ull;
}

/*
 * The retail D3D vblank handlers sample bit 5 of the TV encoder status port
 * (0x80c0), invert it, and expose the result as the current video field.  Host
 * user mode cannot execute Xbox port I/O, so derive the same alternating field
 * from the title's vblank counter.  Returning the encoder bit instead of the
 * final field keeps the original shift/invert instructions in charge of the
 * observable result.
 */
uint8_t godzilla_xbox_video_port80c0(uint32_t vblank_count)
{
    return (vblank_count & 1u) ? 0x00u : 0x20u;
}

extern void sub_0010EFF1(void);
extern void sub_0010B610(void);
extern void sub_0010F0F2(void);
extern void sub_0010B520(void);
extern void sub_0010B550(void);
extern void sub_00111A8C(void);
extern void sub_00128B00(void);
extern void sub_0002E400(void);
extern void sub_00030F60(void);
extern void sub_000318D0(void);
extern void sub_00067870(void);
extern void sub_00071E20(void);
extern void sub_00066720(void);
extern void sub_00066BE0(void);
extern void sub_00071B30(void);
extern void sub_000EAC00(void);
extern void sub_000E9CD0(void);
extern void sub_000EA920(void);
extern void sub_000DFCD0(void);
extern void sub_000EAC20(void);
extern void sub_000DFB70(void);
extern void sub_000DFE70(void);
extern void sub_000DA490(void);
extern void sub_000E1330(void);
extern void sub_000DE660(void);
extern void sub_00100530(void);
extern void sub_001008D0(void);
extern void sub_00101F00(void);
extern void sub_00103270(void);
extern void sub_00103530(void);
extern void sub_001035D0(void);
extern void sub_0015CF52(void);
extern void sub_0015D0AB(void);
extern void sub_001D9B1C(void);
extern void sub_001D9C28(void);
extern void sub_001DA52D(void);
extern void sub_001DAEB2(void);
extern void sub_001DCF6C(void);

/*
 * Retail 0x0010F750 is the CRT memmove implementation.  Its hand-written x86
 * uses several embedded jump tables and jumps into the middle of copy blocks.
 * Treating those block addresses as ordinary recompiled function calls loses
 * the shared stack frame (and previously dispatched into table bytes).  Keep
 * the retail ABI, but perform the same overlap-safe operation directly.
 */
void sub_0010F750(void)
{
    const uint32_t dst = MEM32(g_esp + 4u);
    const uint32_t src = MEM32(g_esp + 8u);
    const uint32_t len = MEM32(g_esp + 12u);

    if (len != 0u && dst != src)
        memmove((void *)XBOX_PTR(dst), (const void *)XBOX_PTR(src), len);
    g_eax = dst;
    g_esp += 4u; /* ret; caller owns the three cdecl arguments */
}

/* Retail vtable event filter at 0x000392A0.  This entry was missed by the
 * function detector because it follows an aligned block without a symbol. */
void sub_000392A0(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t object = g_ecx;
    const uint32_t event = MEM32(entry_sp + 4u);
    const uint32_t saved_esi = g_esi;
    const uint32_t saved_edi = g_edi;

    if (++trace_count <= 16u) {
        fprintf(stderr, "[EVENT-392A0] #%u enter object=%08X event=%08X type=%u esp=%08X\n",
                trace_count, object, event, event ? MEM32(event) : 0u, entry_sp);
        fflush(stderr);
    }

    g_ecx = object;
    PUSH32(g_esp, event);
    PUSH32(g_esp, 0x000392AEu);
    sub_00037340();

    if (trace_count <= 16u) {
        fprintf(stderr, "[EVENT-392A0] #%u base-return eax=%08X esp=%08X\n",
                trace_count, g_eax, g_esp);
        fflush(stderr);
    }

    if (LO8(g_eax) != 0u) {
        switch (MEM32(event)) {
        case 1u:
            SET_LO8(g_eax, 1u);
            break;
        case 2u:
            g_eax = (MEM8(object + 0xBC0u) == 0u) ? 1u : 0u;
            break;
        case 3u:
            g_ecx = object;
            PUSH32(g_esp, 0x000392C4u);
            sub_00038FC0();
            SET_LO8(g_eax, 0u);
            break;
        default:
            SET_LO8(g_eax, 0u);
            break;
        }
    } else {
        SET_LO8(g_eax, 0u);
    }

    g_esi = saved_esi;
    g_edi = saved_edi;
    g_esp = entry_sp + 8u; /* ret 4 */
    if (trace_count <= 16u) {
        fprintf(stderr, "[EVENT-392A0] #%u exit eax=%08X esp=%08X\n",
                trace_count, g_eax, g_esp);
        fflush(stderr);
    }
}

/* Retail 0x000DEB70 is exactly `xor al, al; ret`. */
void sub_000DEB70(void)
{
    SET_LO8(g_eax, 0u);
    g_esp += 4u;
}

/* Retail menu event callback at 0x00038F20 (thiscall, ret 8). */
void sub_00038F20(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t object = g_ecx;
    const uint32_t event = MEM32(entry_sp + 4u);
    const uint32_t mode = MEM32(entry_sp + 8u);
    const uint32_t saved_esi = g_esi;
    const uint32_t saved_edi = g_edi;
    uint32_t item;

    if (++trace_count <= 32u) {
        fprintf(stderr, "[EVENT-38F20] #%u enter object=%08X event=%u mode=%u esp=%08X\n",
                trace_count, object, event, mode, entry_sp);
        fflush(stderr);
    }

    g_ecx = object;
    PUSH32(g_esp, event);
    PUSH32(g_esp, 0x00038F2Eu);
    sub_00038EB0();
    item = g_eax;

    if (trace_count <= 32u) {
        fprintf(stderr, "[EVENT-38F20] #%u item=%08X esp=%08X\n",
                trace_count, item, g_esp);
        fflush(stderr);
    }

    if (item != 0u && MEM8(item + 8u) == 0u) {
        if (MEM8(item + 0x18u) == 0u) {
            MEM8(item + 0x18u) = 1u;
        } else if (mode == 5u) {
            const uint32_t index = MEM32(item + 4u);
            const uint32_t table = MEM32(item + 0xCu);
            const uint32_t row = MEM32(table + index * 4u);
            MEM8(item + 8u) = 1u;
            g_ecx = object;
            PUSH32(g_esp, MEM32(row + 4u));
            PUSH32(g_esp, 0x00038F63u);
            sub_00038EF0();
        } else if (mode == 2u || mode == 1u) {
            const int32_t count = (int32_t)MEM32(item);
            const int32_t old_index = (int32_t)MEM32(item + 4u);
            int32_t index = old_index + (mode == 2u ? 1 : -1);
            int32_t direction = index > old_index ? 1 : -1;
            int32_t attempts;
            if (count > 0) {
                if (index < 0) index = 0;
                if (index >= count) index = count - 1;
                for (attempts = 0; attempts < count; ++attempts) {
                    const uint32_t table = MEM32(item + 0xCu);
                    const uint32_t row = MEM32(table + (uint32_t)index * 4u);
                    if (row != 0u && MEM8(row + 8u) == 0u)
                        break;
                    index += direction;
                    if (index < 0) {
                        index = 0;
                        direction = 1;
                    } else if (index >= count) {
                        index = count - 1;
                        direction = -1;
                    }
                }
                /* If every temporary slot is disabled, retain the old
                 * selection instead of reproducing the retail infinite loop. */
                if (attempts < count)
                    MEM32(item + 4u) = (uint32_t)index;
            }
        }
        MEM32(object + 0x154u) = event;
    }

    SET_LO8(g_eax, 1u);
    g_esi = saved_esi;
    g_edi = saved_edi;
    g_esp = entry_sp + 12u; /* ret 8 */
    if (trace_count <= 32u) {
        fprintf(stderr, "[EVENT-38F20] #%u exit eax=%08X esp=%08X\n",
                trace_count, g_eax, g_esp);
        fflush(stderr);
    }
}

static void godzilla_sub_0010F029_manual(void)
{
    PUSH32(g_esp, 0x0010F02Eu);
    sub_0010EFF1();
    PUSH32(g_esp, 0x0010F033u);
    sub_00111A8C();
    /* Original 0x0010F033 is FNCLEX; host FP exceptions stay masked. */
    g_esp += 4;
}

static void godzilla_d3d_1285_common(void)
{
    uint32_t texture = MEM32(g_esp + 8u);
    if (texture) {
        uint32_t kind = (uint32_t)MEM8(texture + 0xDu) - 0x2Au;
        if (kind <= 7u)
            g_eax |= ((kind & 2u) ? 0x10u : 0x20u);
    } else {
        uint8_t format = MEM8(g_edx + 0x00131B60u) & 0x3Cu;
        g_eax |= (format == 0x20u) ? 0x20u : 0x10u;
    }
    g_esp += 12u; /* ret 8 */
}

static void godzilla_sub_0012855D_manual(void)
{
    g_eax = 0x108u;
    godzilla_d3d_1285_common();
}

static void godzilla_sub_001285A5_manual(void)
{
    uint32_t format = MEM32(g_ecx + 0xCu);
    uint32_t packed = (((format & 0x00F00000u) | 0x2000u) >> 4) |
                      (format & 0x0F000000u);
    g_eax = 1u | packed;
    godzilla_d3d_1285_common();
}

static void godzilla_sub_0012865F_manual(void)
{
    uint32_t output = MEM32(g_esp + 8u);
    g_eax = output;
    MEM32(output) = 0x4B7FFFFFu;
    g_esp += 12u; /* ret 8 */
}

/* Thread entry embedded in the padding between sub_00071DA0 and
 * sub_00071E20.  The static function detector did not promote this tiny
 * address-taken routine, but sub_00071E20 passes 0x00071E10 directly to
 * PsCreateSystemThreadEx.  Let the worker execute the original wrapper
 * instead of treating the callback as an unresolved indirect call. */
void sub_00071E10(void)
{
    g_ecx = MEM32(g_esp + 4u);
    PUSH32(g_esp, 0x00071E19u);
    sub_00071B30();
    g_eax = 0u;
    g_esp += 8u; /* ret 4 */
}

/* Continuation for the computed jump at 0x00072536.  The original instruction
 * is `jmp dword ptr [eax*4 + 0x728A4]`; keeping the mapping explicit lets the
 * lifted parser continuations loop through the retail state table without
 * pretending this interior instruction is a normal call/return boundary. */
void sub_00072536(void)
{
    switch (g_eax) {
    case 0u:  sub_0007253D(); return;
    case 1u:  sub_000725B3(); return;
    case 2u:  sub_00072795(); return;
    case 3u:  sub_000727C5(); return;
    case 4u:  sub_000727F7(); return;
    case 5u:  sub_00072821(); return;
    case 6u:  sub_0007285E(); return;
    case 7u:  sub_0007261E(); return;
    case 8u:  sub_00072688(); return;
    case 9u:  sub_000726BC(); return;
    case 10u: sub_000726F2(); return;
    case 11u: sub_00072728(); return;
    case 12u: sub_0007288C(); return;
    case 13u: sub_00072897(); return;
    default:
        recomp_icall_fail_log(0x00072536u);
        return;
    }
}

void godzilla_constructor_marker(uint32_t va)
{
    fprintf(stderr, "[CTOR] enter=%08X esp=%08X\n", va, g_esp);
}

void godzilla_trace_tls_helper(uint32_t esp_value)
{
    static unsigned trace_count;
    uint32_t trace_vector;
    uint32_t trace_index;
    if (++trace_count > 8) return;
    trace_vector = MEM32(4);
    trace_index = MEM32(0x3C65F8);
    fprintf(stderr,
            "[TLS-HELPER] #%u fs4=%08X index=%08X slot=%08X arg=%08X esp=%08X\n",
            trace_count, trace_vector, trace_index,
            trace_vector ? MEM32(trace_vector + trace_index * 4) : 0,
            MEM32(esp_value + 4), esp_value);
}

void godzilla_repair_heap_lists(uint32_t heap_va)
{
    static uint32_t repaired_heap_va;
    unsigned i;
    if (!heap_va || heap_va == repaired_heap_va) return;
    for (i = 0; i < 128; ++i) {
        uint32_t head = heap_va + 0x180u + i * 8u;
        if (MEM32(head) == 0 && MEM32(head + 4u) == 0) {
            MEM32(head) = head;
            MEM32(head + 4u) = head;
        }
    }
    repaired_heap_va = heap_va;
    fprintf(stderr, "[HEAP-REPAIR] heap=%08X initialized zero list heads once\n",
            heap_va);
}

void godzilla_trace_heap_alloc_entry(uint32_t esp_value)
{
    static unsigned call_count;
    ++call_count;
    if (call_count <= 16 || (call_count & (call_count - 1u)) == 0) {
        fprintf(stderr,
                "[RTL-ALLOC] #%u ret=%08X heap=%08X flags=%08X size=%08X esp=%08X\n",
                call_count, MEM32(esp_value), MEM32(esp_value + 4u),
                MEM32(esp_value + 8u), MEM32(esp_value + 12u), esp_value);
    }
}

void godzilla_trace_malloc_entry(uint32_t esp_value)
{
    static unsigned call_count;
    ++call_count;
    if (call_count <= 16 || (call_count & (call_count - 1u)) == 0) {
        fprintf(stderr, "[MALLOC] #%u ret=%08X size=%08X esp=%08X\n",
                call_count, MEM32(esp_value), MEM32(esp_value + 4u), esp_value);
    }
}

enum {
    GODZILLA_BOOT_ALLOC_CAPACITY = 262144,
    GODZILLA_BOOT_FREE_QUARANTINE = 4096
};
static struct {
    uint32_t va;
    uint32_t size;
    uint32_t capacity;
    uint64_t freed_at;
    uint8_t live;
} g_godzilla_boot_allocations[GODZILLA_BOOT_ALLOC_CAPACITY];
static unsigned g_godzilla_boot_allocation_count;
static uint64_t g_godzilla_boot_free_epoch;
static SRWLOCK g_godzilla_boot_heap_lock = SRWLOCK_INIT;

uint32_t godzilla_bootstrap_heap_alloc(uint32_t flags, uint32_t size)
{
    static uint32_t next_va = 0x82000000u;
    static unsigned call_count;
    const uint32_t actual = size ? size : 1u;
    const uint32_t capacity = (actual + 15u) & ~15u;
    uint32_t result = 0;
    unsigned best = UINT_MAX;

    AcquireSRWLockExclusive(&g_godzilla_boot_heap_lock);
    for (unsigned i = 0; i < g_godzilla_boot_allocation_count; ++i) {
        if (!g_godzilla_boot_allocations[i].live &&
            g_godzilla_boot_allocations[i].freed_at &&
            g_godzilla_boot_free_epoch - g_godzilla_boot_allocations[i].freed_at >=
                GODZILLA_BOOT_FREE_QUARANTINE &&
            g_godzilla_boot_allocations[i].capacity >= capacity &&
            (best == UINT_MAX ||
             g_godzilla_boot_allocations[i].capacity <
                 g_godzilla_boot_allocations[best].capacity))
            best = i;
    }
    if (best != UINT_MAX) {
        result = g_godzilla_boot_allocations[best].va;
        g_godzilla_boot_allocations[best].size = actual;
        g_godzilla_boot_allocations[best].freed_at = 0;
        g_godzilla_boot_allocations[best].live = 1;
    } else if (g_godzilla_boot_allocation_count <
                   GODZILLA_BOOT_ALLOC_CAPACITY &&
               next_va + capacity >= next_va &&
               next_va + capacity <= 0x83F00000u) {
        unsigned i = g_godzilla_boot_allocation_count++;
        result = next_va;
        next_va += capacity;
        g_godzilla_boot_allocations[i].va = result;
        g_godzilla_boot_allocations[i].size = actual;
        g_godzilla_boot_allocations[i].capacity = capacity;
        g_godzilla_boot_allocations[i].freed_at = 0;
        g_godzilla_boot_allocations[i].live = 1;
    }
    if (result)
        memset(XBOX_PTR(result), 0, actual);
    ReleaseSRWLockExclusive(&g_godzilla_boot_heap_lock);

    if (++call_count <= 8)
        fprintf(stderr, "[BOOT-HEAP] #%u flags=%08X size=%08X result=%08X\n",
                call_count, flags, size, result);
    return result;
}

/* Allocation records live beside the bump allocator so CRT realloc can copy
 * only the valid prefix of an existing block. */
static uint32_t godzilla_bootstrap_heap_size(uint32_t va)
{
    uint32_t size = 0;
    AcquireSRWLockShared(&g_godzilla_boot_heap_lock);
    for (unsigned i = 0; i < g_godzilla_boot_allocation_count; ++i) {
        if (g_godzilla_boot_allocations[i].va == va &&
            g_godzilla_boot_allocations[i].live) {
            size = g_godzilla_boot_allocations[i].size;
            break;
        }
    }
    ReleaseSRWLockShared(&g_godzilla_boot_heap_lock);
    return size;
}

static void godzilla_bootstrap_heap_free(uint32_t va)
{
    AcquireSRWLockExclusive(&g_godzilla_boot_heap_lock);
    for (unsigned i = 0; i < g_godzilla_boot_allocation_count; ++i) {
        if (g_godzilla_boot_allocations[i].va == va &&
            g_godzilla_boot_allocations[i].live) {
            g_godzilla_boot_allocations[i].live = 0;
            g_godzilla_boot_allocations[i].freed_at =
                ++g_godzilla_boot_free_epoch;
            break;
        }
    }
    ReleaseSRWLockExclusive(&g_godzilla_boot_heap_lock);
}

void sub_0002BDBA(void)
{
    g_eax = godzilla_bootstrap_heap_alloc(MEM32(g_esp + 8u),
                                          MEM32(g_esp + 12u));
    g_esp += 16u; /* RtlAllocateHeap: ret 12 */
}

/* CRT per-thread error setter.  Late XOnline startup changes the TLS index to
 * -5 and clears fs:[4], but the title's TLS object remains valid at the fixed
 * bootstrap address provisioned by main.c. */
void sub_0002A795(void)
{
    g_eax = 0x0075F000u;
    g_ecx = MEM32(g_esp + 4u);
    MEM32(g_eax + 4u) = g_ecx;
    g_esp += 8u; /* ret 4 */
}

/* Matching CRT per-thread error getter. */
void sub_0002A76D(void)
{
    g_eax = MEM32(0x0075F000u + 4u);
    g_esp += 4u; /* ret */
}

/*
 * Xbox CRT realloc.  Its generated non-null path returns a guest stack address
 * and leaves ESP 48 bytes low.  All CRT malloc blocks currently come through
 * the bootstrap allocator above, so perform a tracked allocate/copy here.
 * Successful reallocations retire the old block through the quarantined
 * bootstrap free-list.  Its delayed reuse preserves object teardown ordering
 * while preventing the former one-way allocator from exhausting its window.
 */
void sub_0010FF6F(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t saved_ebx = g_ebx;
    const uint32_t saved_esi = g_esi;
    const uint32_t saved_edi = g_edi;
    const uint32_t old_va = MEM32(entry_sp + 4u);
    const uint32_t new_size = MEM32(entry_sp + 8u);
    const uint32_t old_size = godzilla_bootstrap_heap_size(old_va);
    uint32_t result = 0;

    if (!old_va) {
        result = godzilla_bootstrap_heap_alloc(0, new_size);
    } else if (new_size) {
        result = godzilla_bootstrap_heap_alloc(0, new_size);
        if (result && old_size) {
            const uint32_t copy_size = old_size < new_size ? old_size : new_size;
            memcpy((void *)XBOX_PTR(result),
                   (const void *)XBOX_PTR(old_va), copy_size);
            godzilla_bootstrap_heap_free(old_va);
        }
    } else if (old_size) {
        godzilla_bootstrap_heap_free(old_va);
    }

    ++trace_count;
    if (getenv("GODZILLA_TRACE_ALLOC") && trace_count <= 2u) {
        fprintf(stderr,
                "[FILE-MANAGER-GLOBALS] phase=crt-realloc dsound=%08X "
                "alloc=%08X alloc-size=%08X free=%08X\n",
                MEM32(0x001724F4u), MEM32(0x001E135Cu),
                MEM32(0x001E1380u), MEM32(0x001E1210u));
    }
    if (getenv("GODZILLA_TRACE_ALLOC") &&
        (trace_count <= 24u || !old_size)) {
        fprintf(stderr,
                "[CRT-REALLOC] #%u old=%08X old-size=%u new-size=%u "
                "result=%08X esp=%08X\n",
                trace_count, old_va, old_size, new_size, result, entry_sp);
    }

    g_eax = result;
    g_ebx = saved_ebx;
    g_esi = saved_esi;
    g_edi = saved_edi;
    g_esp = entry_sp + 4u; /* cdecl ret; caller removes two arguments */
}

/* Xbox D3D returns physical texture memory through either the cached
 * 0x80000000 alias or (for lock flag 0x40) the write-combined 0xF0000000
 * alias. Both name the same low 64 MB on hardware, while the recompilation
 * address space cannot create that hardware alias implicitly. Preserve the
 * original lock operation, then canonicalize those physical aliases. */
void sub_0012DF80(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t surface = MEM32(entry_sp + 4u);
    const uint32_t locked_rect = MEM32(entry_sp + 8u);
    const uint32_t rect = MEM32(entry_sp + 12u);
    const uint32_t flags = MEM32(entry_sp + 16u);

    PUSH32(g_esp, flags);
    PUSH32(g_esp, rect);
    PUSH32(g_esp, locked_rect);
    PUSH32(g_esp, 0u);
    PUSH32(g_esp, 0u);
    PUSH32(g_esp, surface);
    PUSH32(g_esp, 0x0012DF9Du);
    sub_00128B00();

    if (locked_rect) {
        const uint32_t tagged_bits = MEM32(locked_rect + 4u);
        const uint32_t tag = tagged_bits & 0xF0000000u;
        if ((tag == 0x80000000u || tag == 0xF0000000u) &&
            (tagged_bits & 0x0FFFFFFFu) < 0x04000000u) {
            const uint32_t canonical_bits = tagged_bits & 0x0FFFFFFFu;
            MEM32(locked_rect + 4u) = canonical_bits;
            ++trace_count;
            if (trace_count <= 16u) {
                fprintf(stderr,
                        "[D3D-LOCK] #%u surface=%08X flags=%08X "
                        "pBits=%08X->%08X pitch=%u\n",
                        trace_count, surface, flags, tagged_bits,
                        canonical_bits, MEM32(locked_rect));
            }
        }
    }

    g_esp = entry_sp + 20u; /* ret 16 */
}

/* XGSwizzleRect. The generated XDK MMX implementation depends on packed-MMX
 * state that the recompiler does not yet preserve and silently left the
 * title's normalization cubemap full of zeroes. Reproduce the Xbox Morton
 * layout directly, including the API's optional rectangle and point. */
static void godzilla_swizzle_masks(uint32_t width, uint32_t height,
                                   uint32_t *mask_x, uint32_t *mask_y)
{
    uint32_t x = 0, y = 0, bit = 1, mask_bit = 1;
    while (bit < width || bit < height) {
        if (bit < width)  { x |= mask_bit; mask_bit <<= 1; }
        if (bit < height) { y |= mask_bit; mask_bit <<= 1; }
        bit <<= 1;
    }
    *mask_x = x;
    *mask_y = y;
}

static uint32_t godzilla_swizzle_coord(uint32_t value, uint32_t mask)
{
    uint32_t result = 0, source_bit = 1;
    for (uint32_t dest_bit = 1; dest_bit && dest_bit <= mask; dest_bit <<= 1) {
        if (!(mask & dest_bit)) continue;
        if (value & source_bit) result |= dest_bit;
        source_bit <<= 1;
    }
    return result;
}

void sub_00153C8E(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t source_va = MEM32(entry_sp + 4u);
    uint32_t source_pitch = MEM32(entry_sp + 8u);
    const uint32_t rect_va = MEM32(entry_sp + 12u);
    const uint32_t dest_va = MEM32(entry_sp + 16u);
    const uint32_t width = MEM32(entry_sp + 20u);
    const uint32_t height = MEM32(entry_sp + 24u);
    const uint32_t point_va = MEM32(entry_sp + 28u);
    const uint32_t bpp = MEM32(entry_sp + 32u);
    uint32_t left = 0, top = 0, right = width, bottom = height;
    uint32_t dest_x = 0, dest_y = 0, mask_x, mask_y;

    if (rect_va) {
        left = MEM32(rect_va);
        top = MEM32(rect_va + 4u);
        right = MEM32(rect_va + 8u);
        bottom = MEM32(rect_va + 12u);
    }
    if (point_va) {
        dest_x = MEM32(point_va);
        dest_y = MEM32(point_va + 4u);
    }
    if (!source_pitch) source_pitch = (right - left) * bpp;

    ++trace_count;
    if (trace_count <= 16u)
        fprintf(stderr,
                "[XG-SWIZZLE] #%u src=%08X pitch=%u rect=%08X dst=%08X "
                "size=%ux%u point=%08X bpp=%u\n",
                trace_count, source_va, source_pitch, rect_va, dest_va,
                width, height, point_va, bpp);

    if (source_va && dest_va && width && height && bpp &&
        right >= left && bottom >= top) {
        const uint8_t *source = (const uint8_t *)XBOX_PTR(source_va);
        uint8_t *dest = (uint8_t *)XBOX_PTR(dest_va);
        godzilla_swizzle_masks(width, height, &mask_x, &mask_y);
        for (uint32_t y = top; y < bottom && dest_y + y - top < height; ++y) {
            const uint8_t *source_row = source + (size_t)y * source_pitch;
            const uint32_t sy = godzilla_swizzle_coord(dest_y + y - top, mask_y);
            for (uint32_t x = left; x < right && dest_x + x - left < width; ++x) {
                const uint32_t sx = godzilla_swizzle_coord(dest_x + x - left, mask_x);
                memcpy(dest + (size_t)(sx | sy) * bpp,
                       source_row + (size_t)x * bpp, bpp);
            }
        }
    }

    g_esp = entry_sp + 36u; /* ret 32 */
}

static int godzilla_is_canonical_object_pointer(uint32_t va)
{
    return (va >= 0x00010000u && va < 0x04000000u) ||
           (va >= 0x80000000u && va < 0x84000000u);
}

/* Assign a ref-counted resource into the state object's slot array.  During
 * menu bring-up one slot contains an unmapped garbage value; dereferencing
 * its +4 refcount crashes before the valid replacement can be installed.
 * Preserve normal release/addref behavior for canonical guest objects and
 * skip only an invalid stale ref. */
void sub_00109EC0(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t saved_esi = g_esi;
    const uint32_t saved_edi = g_edi;
    const uint32_t owner = g_ecx;
    const uint32_t replacement = MEM32(entry_sp + 4u);
    const uint32_t index = MEM32(entry_sp + 8u);
    const uint32_t slot = owner + 0x60u + index * 4u;
    const uint32_t previous = MEM32(slot);
    const int previous_valid =
        !previous || godzilla_is_canonical_object_pointer(previous);
    const int replacement_valid =
        !replacement || godzilla_is_canonical_object_pointer(replacement);

    ++trace_count;
    if (trace_count <= 24u || !previous_valid || !replacement_valid) {
        fprintf(stderr,
                "[RESOURCE-SLOT] #%u owner=%08X index=%u slot=%08X "
                "old=%08X(%s) new=%08X(%s) ret=%08X\n",
                trace_count, owner, index, slot, previous,
                previous_valid ? "valid" : "invalid", replacement,
                replacement_valid ? "valid" : "invalid", MEM32(entry_sp));
    }

    if (previous && previous_valid) {
        const uint32_t refs = MEM32(previous + 4u) - 1u;
        MEM32(previous + 4u) = refs;
        if (!refs) {
            g_ecx = previous;
            PUSH32(g_esp, 0x00109EDAu);
            sub_0002E400();
        }
    }

    MEM32(slot) = replacement_valid ? replacement : 0u;
    if (replacement && replacement_valid)
        MEM32(replacement + 4u) = MEM32(replacement + 4u) + 1u;
    MEM8(owner + 0x90u) = 1u;

    g_eax = replacement;
    g_esi = saved_esi;
    g_edi = saved_edi;
    g_esp = entry_sp + 12u; /* ret 8 */
}

/*
 * These two virtual methods are genuine XBE function starts referenced only
 * through vtables.  The function detector found their ABI/name records but
 * did not emit bodies or dispatch entries.  Leaving either unresolved is not
 * benign: sub_0002E400 has already pushed its saved EDI when it performs the
 * first call, while the generic unresolved-call recovery restores ESP to the
 * earlier checkpoint and thereby shifts the destructor's EBX/ESI/EDI pops.
 * Translate the original instructions here so the real destructor path and
 * its callee-saved-register contract execute intact.
 */
void sub_0010BA80(void)
{
    static RECOMP_TLS unsigned trace_count;

    PUSH32(g_esp, g_esi);
    g_esi = g_ecx;

    PUSH32(g_esp, 0x0010BA88u);
    sub_0010B610();

    ++trace_count;
    if (trace_count <= 16u) {
        fprintf(stderr,
                "[VTABLE-10BA80] #%u object=%08X delete=%u flags=%02X\n",
                trace_count, g_esi, MEM8(g_esp + 8u) & 1u,
                MEM8(g_esi + 8u));
    }

    if ((MEM8(g_esp + 8u) & 1u) && !(MEM8(g_esi + 8u) & 0x18u)) {
        PUSH32(g_esp, g_esi);
        PUSH32(g_esp, 0x0010BA9Bu);
        sub_0010F0F2();
        g_esp += 4u;
    }

    g_eax = g_esi;
    POP32(g_esp, g_esi);
    g_esp += 8u; /* ret 4 */
}

void sub_000123F0(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t parent = g_ecx;
    const uint32_t child = MEM32(parent + 0x14u);

    if (child) {
        const uint32_t vtable = MEM32(child);
        const uint32_t target = MEM32(vtable);

        ++trace_count;
        if (trace_count <= 16u) {
            fprintf(stderr,
                    "[VTABLE-123F0] #%u parent=%08X child=%08X target=%08X\n",
                    trace_count, parent, child, target);
        }

        PUSH32(g_esp, parent);
        g_ecx = child;
        PUSH32(g_esp, 0x000123FEu);
        {
            const uint32_t saved_ebx = g_ebx;
            const uint32_t saved_esi = g_esi;
            const uint32_t saved_edi = g_edi;
            const uint32_t saved_ebp = g_ebp;
            recomp_func_t fn = recomp_lookup_manual(target);
            if (!fn)
                fn = recomp_lookup(target);
            if (!fn)
                fn = recomp_lookup_kernel(target);
            if (fn) {
                fn();
                g_ebx = saved_ebx;
                g_esi = saved_esi;
                g_edi = saved_edi;
                g_ebp = saved_ebp;
            } else {
                recomp_icall_fail_log(target);
                g_esp = entry_sp;
                g_eax = 0u;
            }
        }
    }

    g_esp = entry_sp + 4u; /* ret */
}

/* Construct the global file/cache manager at 0x00417FA8.  The original x86
 * routine keeps its object pointer in callee-saved ESI across four calls.
 * During native translation one of those deeper paths currently returns with
 * ESI == -1, so the final object-field reads wrap into the low-memory guard.
 * Keep the original instruction order while enforcing the x86 callee-saved
 * contract at each boundary; the trace identifies the first violating call. */
void sub_00067C30(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t caller_esi = g_esi;
    const uint32_t object = g_ecx;
    const uint32_t first_arg = MEM32(entry_sp + 4u);
    const uint32_t second_arg = MEM32(entry_sp + 8u);
    uint32_t saved_slot;
    uint32_t packet;

    ++trace_count;
    if (trace_count <= 2u) {
        fprintf(stderr,
                "[FILE-MANAGER-GLOBALS] phase=entry dsound=%08X "
                "alloc=%08X alloc-size=%08X free=%08X\n",
                MEM32(0x001724F4u), MEM32(0x001E135Cu),
                MEM32(0x001E1380u), MEM32(0x001E1210u));
    }
    if (!godzilla_is_canonical_object_pointer(object)) {
        fprintf(stderr,
                "[FILE-MANAGER] #%u invalid-object=%08X ret=%08X esp=%08X\n",
                trace_count, object, MEM32(entry_sp), entry_sp);
        g_eax = 0u;
        g_esi = caller_esi;
        g_esp = entry_sp + 12u;
        return;
    }

    PUSH32(g_esp, g_esi);
    saved_slot = g_esp;
    g_esi = object;
    g_ecx = second_arg;
    PUSH32(g_esp, g_ecx);
    g_ecx = object;
    MEM32(object) = first_arg;
    PUSH32(g_esp, 0x00067C45u);
    sub_00067870();
    if (trace_count <= 2u)
        fprintf(stderr,
                "[FILE-MANAGER-GLOBALS] phase=67870 dsound=%08X "
                "alloc=%08X alloc-size=%08X free=%08X\n",
                MEM32(0x001724F4u), MEM32(0x001E135Cu),
                MEM32(0x001E1380u), MEM32(0x001E1210u));
    if (g_esp != saved_slot || g_esi != object) {
        fprintf(stderr,
                "[FILE-MANAGER] after=00067870 object=%08X esi=%08X "
                "esp=%08X expected=%08X eax=%08X\n",
                object, g_esi, g_esp, saved_slot, g_eax);
    }
    g_esp = saved_slot;
    g_esi = object;

    g_ecx = object + 0x34u;
    PUSH32(g_esp, 0x00067C4Du);
    sub_00071E20();
    if (trace_count <= 2u)
        fprintf(stderr,
                "[FILE-MANAGER-GLOBALS] phase=71E20-A dsound=%08X "
                "alloc=%08X alloc-size=%08X free=%08X\n",
                MEM32(0x001724F4u), MEM32(0x001E135Cu),
                MEM32(0x001E1380u), MEM32(0x001E1210u));
    if (g_esp != saved_slot || g_esi != object) {
        fprintf(stderr,
                "[FILE-MANAGER] after=00071E20-A object=%08X esi=%08X "
                "esp=%08X expected=%08X eax=%08X\n",
                object, g_esi, g_esp, saved_slot, g_eax);
    }
    g_esp = saved_slot;
    g_esi = object;

    g_ecx = object + 0x68u;
    PUSH32(g_esp, 0x00067C55u);
    sub_00071E20();
    if (trace_count <= 2u)
        fprintf(stderr,
                "[FILE-MANAGER-GLOBALS] phase=71E20-B dsound=%08X "
                "alloc=%08X alloc-size=%08X free=%08X\n",
                MEM32(0x001724F4u), MEM32(0x001E135Cu),
                MEM32(0x001E1380u), MEM32(0x001E1210u));
    if (g_esp != saved_slot || g_esi != object) {
        fprintf(stderr,
                "[FILE-MANAGER] after=00071E20-B object=%08X esi=%08X "
                "esp=%08X expected=%08X eax=%08X\n",
                object, g_esi, g_esp, saved_slot, g_eax);
    }
    g_esp = saved_slot;
    g_esi = object;

    g_ecx = object;
    PUSH32(g_esp, 0x00067C5Cu);
    sub_00066720();
    if (trace_count <= 2u)
        fprintf(stderr,
                "[FILE-MANAGER-GLOBALS] phase=66720 dsound=%08X "
                "alloc=%08X alloc-size=%08X free=%08X\n",
                MEM32(0x001724F4u), MEM32(0x001E135Cu),
                MEM32(0x001E1380u), MEM32(0x001E1210u));
    if (g_esp != saved_slot || g_esi != object) {
        fprintf(stderr,
                "[FILE-MANAGER] after=00066720 object=%08X esi=%08X "
                "esp=%08X expected=%08X eax=%08X\n",
                object, g_esi, g_esp, saved_slot, g_eax);
    }
    g_esp = saved_slot;
    g_esi = object;

    if (!(g_eax & 0xFFu)) {
        g_ecx = object;
        PUSH32(g_esp, 0x00067C67u);
        sub_00066BE0();
        if (trace_count <= 2u)
            fprintf(stderr,
                    "[FILE-MANAGER-GLOBALS] phase=66BE0 dsound=%08X "
                    "alloc=%08X alloc-size=%08X free=%08X\n",
                    MEM32(0x001724F4u), MEM32(0x001E135Cu),
                    MEM32(0x001E1380u), MEM32(0x001E1210u));
        if (g_esp != saved_slot || g_esi != object) {
            fprintf(stderr,
                    "[FILE-MANAGER] after=00066BE0 object=%08X esi=%08X "
                    "esp=%08X expected=%08X eax=%08X\n",
                    object, g_esi, g_esp, saved_slot, g_eax);
        }
        g_esp = saved_slot;
        g_esi = object;
    }

    packet = MEM32(object + 0x9Cu);
    if (trace_count <= 8u || !godzilla_is_canonical_object_pointer(packet)) {
        fprintf(stderr,
                "[FILE-MANAGER] #%u object=%08X packet=%08X handle=%08X "
                "caller-esi=%08X\n",
                trace_count, object, packet, MEM32(object + 8u), caller_esi);
    }

    MEM32(object + 0x18u) = MEM32(object + 8u);
    MEM32(object + 0x1Cu) = packet;
    if (godzilla_is_canonical_object_pointer(packet))
        g_eax = MEM32(packet + 0xCu);
    else
        g_eax = 0u;
    MEM32(object + 0x20u) = g_eax;
    MEM32(object + 0x2Cu) = 1u;

    g_esi = caller_esi;
    g_esp = entry_sp + 12u; /* ret 8 */
}

/* Intrusive-list unlink used by the menu resource teardown path.  Keep the
 * original behavior for canonical objects, but log and reject a poisoned
 * owner/node before MEM32 turns it into an opaque host access violation. */
void sub_000DD600(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t entry_sp = g_esp;
    const uint32_t owner = g_ecx;
    const uint32_t node = MEM32(entry_sp + 4u);
    const uint32_t return_va = MEM32(entry_sp);
    const uint32_t saved_edi = g_edi;
    uint32_t current;

    ++trace_count;
    if (trace_count <= 24u ||
        !godzilla_is_canonical_object_pointer(owner) ||
        (node && !godzilla_is_canonical_object_pointer(node))) {
        fprintf(stderr,
                "[LIST-REMOVE] #%u owner=%08X node=%08X ret=%08X esp=%08X\n",
                trace_count, owner, node, return_va, entry_sp);
    }

    if (!godzilla_is_canonical_object_pointer(owner) ||
        (node && !godzilla_is_canonical_object_pointer(node))) {
        g_eax = node;
        g_esp = entry_sp + 8u; /* diagnostic recovery: ret 4 */
        return;
    }

    current = MEM32(owner + 0x3Cu);
    while (current && current != node) {
        if (!godzilla_is_canonical_object_pointer(current)) {
            fprintf(stderr,
                    "[LIST-REMOVE] invalid-link owner=%08X link=%08X ret=%08X\n",
                    owner, current, return_va);
            g_eax = node;
            g_esp = entry_sp + 8u;
            return;
        }
        current = MEM32(current + 0x34u);
    }

    if (current == node && node) {
        const uint32_t next = MEM32(node + 0x38u);
        const uint32_t previous = MEM32(node + 0x34u);
        if (next)
            MEM32(next + 0x34u) = previous;
        if (previous)
            MEM32(previous + 0x38u) = next;
        if (node == MEM32(owner + 0x3Cu))
            MEM32(owner + 0x3Cu) = previous;
        if (node == MEM32(owner + 0x40u))
            MEM32(owner + 0x40u) = next;
        MEM32(node + 0x34u) = 0u;
        MEM32(node + 0x38u) = 0u;
        MEM32(node + 0x44u) = 0u;
    }

    g_eax = node;
    g_edi = saved_edi;
    g_esp = entry_sp + 8u; /* ret 4 */
}

/* RtlFreeHeap counterpart for the bootstrap allocator.  Do not feed these raw
 * blocks to the title's translated RTL_HEAP coalescer; retire them through the
 * matching quarantined block table.  XNET and DirectSound churn these buffers
 * every frame, so delayed reuse is required as well as eventual reclamation. */
void sub_0002C571(void)
{
    static RECOMP_TLS unsigned trace_count;
    const uint32_t heap = MEM32(g_esp + 4u);
    const uint32_t flags = MEM32(g_esp + 8u);
    const uint32_t allocation = MEM32(g_esp + 12u);
    const uint32_t allocation_size =
        godzilla_bootstrap_heap_size(allocation);

    ++trace_count;
    if (trace_count <= 24u || !allocation_size) {
        fprintf(stderr,
                "[CRT-FREE] #%u heap=%08X flags=%08X ptr=%08X size=%u "
                "released=%s\n",
                trace_count, heap, flags, allocation, allocation_size,
                allocation_size ? "yes" : "unknown");
    }

    if (allocation_size)
        godzilla_bootstrap_heap_free(allocation);

    g_eax = (g_eax & 0xFFFFFF00u) | 1u;
    g_esp += 16u; /* ret 12 */
}

/*
 * D3D's GPU-idle/fence wait.  The original polls NV2A status fields until the
 * hardware consumes the push buffer.  The native renderer consumes commands
 * synchronously, so the observable completion path is sufficient here.
 */
void sub_0012D75A(void)
{
    uint32_t device = MEM32(g_ecx);
    uint32_t completion = device + 0x3220u;
    uint32_t output = MEM32(g_esp + 4u);

    MEM32(output) = MEM32(completion);
    MEM32(completion) = 0;
    g_esp += 8u; /* ret 4 */
}

/*
 * DirectSound parameter update.  This path expects a live Xbox MCPX voice
 * state behind [ecx+0x14], but the menu-only native audio backend currently
 * exposes the hardware's inactive 0xFFFFFFFF sentinel there.  The original
 * routine dereferences that sentinel.  Treat the update as having no changed
 * parameters; callers already accept that result while audio is unavailable.
 */
void sub_0015C9BE(void)
{
    if (g_ecx)
        MEM32(g_ecx) = 0;
    g_esp += 8u; /* ret 4 */
}

/* Build an MCPX per-channel hardware table.  With no native MCPX voice format,
 * the channel count is zero and the Xbox routine divides by it before its own
 * zero check.  An all-zero table represents an inactive voice for menu boot. */
void sub_0015A5AF(void)
{
    uint32_t output = MEM32(g_esp + 4u);
    if (output)
        memset(XBOX_PTR(output), 0, 0x38u);
    g_esp += 8u; /* ret 4 */
}

/* Commit pending MCPX voice changes.  There is no live MCPX voice behind the
 * native menu-only audio backend, so acknowledge the commit without touching
 * the sentinel-derived voice pointer supplied by DirectSound. */
void sub_00154FF1(void)
{
    const uint32_t return_va = MEM32(g_esp);
    const uint32_t voice = MEM32(g_esp + 4u);

    /* sub_001559A9 walks an intrusive list through voice+0x14 after each
     * commit.  Without MCPX voice construction, its head contains a cycle
     * through guest stack/global scratch addresses rather than real voices;
     * none of those links can reach the owner's sentinel.  The menu-only
     * backend has no hardware state to commit, so terminate this exact known
     * walk through the caller's own sentinel after its first inactive entry. */
    if (return_va == 0x001559F7u && voice) {
        const uint32_t link = voice + 0x14u;
        const uint32_t next = MEM32(link);
        const uint32_t owner = MEM32(g_esp + 8u); /* caller's saved EDI */
        const uint32_t sentinel = owner + 0x10u;
        static unsigned walk_count;

        ++walk_count;
        if (walk_count <= 8u || (walk_count & (walk_count - 1u)) == 0u) {
            fprintf(stderr,
                    "[DSOUND-WALK] #%u voice=%08X link=%08X next=%08X sentinel=%08X\n",
                    walk_count, voice, link, next, sentinel);
            fflush(stderr);
        }
        if (next != sentinel) {
            fprintf(stderr,
                    "[DSOUND-WALK] terminated inactive list %08X -> %08X\n",
                    link, sentinel);
            fflush(stderr);
            MEM32(link) = sentinel;
        }
    }

    g_eax = 0;
    g_esp += 8u; /* ret 4 */
}

/* Commit every pending DirectSound voice in an intrusive MCPX list.  The
 * native menu backend intentionally has no hardware voices, and the list head
 * is populated from unmodelled MCPX scratch state, producing a cycle through
 * guest stacks instead of voice objects.  Software-side parameters were
 * already copied by the caller; acknowledge the hardware commit as complete. */
void sub_001559A9(void)
{
    g_eax = 0;
    g_esp += 8u; /* ret 4 */
}

/* MainMenu's tree walker reaches this adjustor thunk through vtable slot 3.
 * Preserve the original secondary-base adjustment and tail call into the
 * newly recovered body at 0x001035D0. */
/* Exact retail thunk at 0x000141E0: jmp 0x00033F40.  It is installed as an
 * event-listener callback during the profile-to-menu transition, so it must
 * preserve the caller's existing guest return address and stack verbatim. */
void sub_000141E0(void)
{
    sub_00033F40();
}

void sub_000FA450(void)
{
    if (g_ecx >= 4u)
        g_ecx -= MEM32(g_ecx - 4u);
    sub_001035D0();
}

/* Secondary-base thunks used by the MainMenu scene graph. */
void sub_000FA430(void)
{
    if (g_ecx >= 4u)
        g_ecx -= MEM32(g_ecx - 4u);
    MEM32(g_ecx - 8u) = MEM32(g_ecx - 8u) + 1u;
    g_esp += 8u; /* ret 4 */
}

void sub_000E07F0(void)
{
    if (g_ecx >= 4u)
        g_ecx -= MEM32(g_ecx - 4u);
    g_eax = 2u;
    g_esp += 4u;
}

void sub_000E0820(void)
{
    static unsigned s_pwk_submit_trace;
    uint32_t original_ecx, adjust, trace_interface, trace_base, trace_node;
    uint32_t device, before, after;
    original_ecx = g_ecx;
    adjust = original_ecx >= 4u ? MEM32(original_ecx - 4u) : 0u;
    if (g_ecx >= 4u)
        g_ecx -= adjust;
    trace_interface = g_ecx;
    trace_base = trace_interface - 0x78u;
    trace_node = MEM32(trace_interface + 8u);
    device = MEM32(0x00134078u);
    before = device ? MEM32(device) : 0;
    sub_000DE660();
    after = device ? MEM32(device) : 0;
    if (s_pwk_submit_trace < 96u) {
        fprintf(stderr,
                "[PWK-SUBMIT] n=%u entry_ecx=%08X adjust=%08X interface=%08X "
                "base=%08X node=%08X pb=%08X->%08X delta=%u "
                "state04=%08X 08=%08X 10=%08X 14=%08X 1C=%08X 20=%08X "
                "24=%08X 2C=%08X 30=%08X 34=%08X 3C=%08X 44=%08X "
                "48=%08X 4C=%08X 70=%08X "
                "nodewords=%08X,%08X,%08X,%08X n89=%02X "
                "render_count=%08X records=%08X refs=%08X r89=%02X arg=%08X\n",
                s_pwk_submit_trace, original_ecx, adjust, trace_interface,
                trace_base, trace_node,
                before, after, after - before,
                MEM32(trace_base + 4u), MEM32(trace_base + 8u),
                MEM32(trace_base + 16u), MEM32(trace_base + 20u),
                MEM32(trace_base + 28u), MEM32(trace_base + 32u),
                MEM32(trace_base + 36u), MEM32(trace_base + 44u),
                MEM32(trace_base + 48u), MEM32(trace_base + 52u),
                MEM32(trace_base + 60u), MEM32(trace_base + 68u),
                MEM32(trace_base + 72u), MEM32(trace_base + 76u),
                MEM32(trace_base + 112u),
                trace_node ? MEM32(trace_node) : 0,
                trace_node ? MEM32(trace_node + 4u) : 0,
                trace_node ? MEM32(trace_node + 8u) : 0,
                trace_node ? MEM32(trace_node + 12u) : 0,
                trace_node ? MEM8(trace_node + 0x89u) : 0,
                trace_node ? MEM32(MEM32(trace_node) + 0x4Cu) : 0,
                trace_node ? MEM32(MEM32(trace_node) + 0x50u) : 0,
                trace_node ? MEM32(MEM32(trace_node) + 0x54u) : 0,
                trace_node ? MEM8(MEM32(trace_node) + 0x89u) : 0,
                MEM32(g_esp + 4u));
    }
    ++s_pwk_submit_trace;
}

void sub_0009EAB0(void)
{
    SET_LO8(g_eax, 1u);
    g_esp += 4u;
}

void godzilla_trace_alloc_result(uint32_t value, uint32_t esp_value)
{
    static unsigned call_count;
    if (++call_count <= 8)
        fprintf(stderr, "[ALLOC-RESULT] #%u eax=%08X esp=%08X\n",
                call_count, value, esp_value);
}

void godzilla_trace_operator_new(uint32_t esp_value)
{
    static unsigned call_count;
    ++call_count;
    if (call_count <= 16 || (call_count & (call_count - 1u)) == 0)
        fprintf(stderr, "[OP-NEW] #%u ret=%08X size=%08X esp=%08X\n",
                call_count, MEM32(esp_value), MEM32(esp_value + 4u), esp_value);
}

void godzilla_trace_new_wrapper(uint32_t esp_value)
{
    static unsigned call_count;
    ++call_count;
    if (call_count <= 16 || (call_count & (call_count - 1u)) == 0)
        fprintf(stderr, "[NEW-WRAP] #%u ret=%08X size=%08X esp=%08X\n",
                call_count, MEM32(esp_value), MEM32(esp_value + 4u), esp_value);
}

/* The retail title talks directly to XAPI's USB/XID controller stack.  The
 * PC runtime has a real XInput/keyboard backend, but these statically-linked
 * entry points have to be bridged before the game can see it.  The addresses
 * below were matched against the same XAPI routines in Save the Earth and
 * verified in DAMM's XPP disassembly/call sites. */
#define GODZILLA_XAPI_GAMEPAD_TYPE 0x001D9974u
#define GODZILLA_XAPI_PAD_HANDLE   0x0C0DE000u

static void godzilla_xapi_return(uint32_t value, unsigned nargs)
{
    g_eax = value;
    g_esp += 4u + 4u * nargs;
}

int godzilla_xapi_hook(uint32_t va)
{
    static int insertion_reported;
    static unsigned devices_calls;
    static unsigned open_calls;
    static unsigned state_calls;
    uint32_t a0 = MEM32(g_esp + 4u);
    uint32_t a1 = MEM32(g_esp + 8u);
    uint32_t a2 = MEM32(g_esp + 12u);

    switch (va) {
    case 0x001DABE2u: /* DWORD XGetDevices(PXPP_DEVICE_TYPE) */
        if (++devices_calls <= 8u)
            fprintf(stderr, "[XAPI-INPUT] devices #%u type=%08X mask=%u\n",
                    devices_calls, a0,
                    a0 == GODZILLA_XAPI_GAMEPAD_TYPE ? 1u : 0u);
        godzilla_xapi_return(a0 == GODZILLA_XAPI_GAMEPAD_TYPE ? 1u : 0u, 1u);
        return 1;
    case 0x001DAC04u: /* BOOL XGetDeviceChanges(type, insertions, removals) */
        if (a0 == GODZILLA_XAPI_GAMEPAD_TYPE && !insertion_reported) {
            insertion_reported = 1;
            MEM32(a1) = 1u;
            MEM32(a2) = 0u;
            godzilla_xapi_return(1u, 3u);
        } else {
            if (a1) MEM32(a1) = 0u;
            if (a2) MEM32(a2) = 0u;
            godzilla_xapi_return(0u, 3u);
        }
        return 1;
    case 0x001DA8DCu: /* HANDLE XInputOpen(type, port, slot, params) */
        if (++open_calls <= 8u)
            fprintf(stderr,
                    "[XAPI-INPUT] open #%u type=%08X port=%u handle=%08X\n",
                    open_calls, a0, a1,
                    a0 == GODZILLA_XAPI_GAMEPAD_TYPE && a1 == 0u
                        ? GODZILLA_XAPI_PAD_HANDLE : 0u);
        godzilla_xapi_return(
            a0 == GODZILLA_XAPI_GAMEPAD_TYPE && a1 == 0u
                ? GODZILLA_XAPI_PAD_HANDLE : 0u,
            4u);
        return 1;
    case 0x001DA932u: /* VOID XInputClose(HANDLE) */
        godzilla_xapi_return(0u, 1u);
        return 1;
    case 0x001DA93Eu: { /* DWORD XInputGetCapabilities(HANDLE, caps) */
        unsigned i;
        if (a0 != GODZILLA_XAPI_PAD_HANDLE) {
            godzilla_xapi_return(1167u, 2u); /* ERROR_DEVICE_NOT_CONNECTED */
            return 1;
        }
        for (i = 0; i < 24u; ++i) MEM8(a1 + i) = 0u;
        MEM8(a1) = 1u;             /* XINPUT_DEVSUBTYPE_GC_GAMEPAD */
        MEM16(a1 + 2u) = 0x00FFu;
        for (i = 0; i < 8u; ++i) MEM8(a1 + 4u + i) = 0xFFu;
        for (i = 0; i < 4u; ++i) MEM16(a1 + 12u + 2u * i) = 0xFFFFu;
        godzilla_xapi_return(0u, 2u);
        return 1;
    }
    case 0x001DAB1Cu: { /* DWORD XInputGetState(HANDLE, state) */
        static unsigned navigation_test_polls;
        GODZILLA_XBOX_INPUT_STATE state;
        int suppress_start_release = 0;
        unsigned i;
        if (a0 != GODZILLA_XAPI_PAD_HANDLE ||
            xbox_InputGetState(0u, &state) != 0u) {
            godzilla_xapi_return(1167u, 2u);
            return 1;
        }
        /* Hidden parity runs must be reproducible even if a physical pad is
         * connected or a desktop key happens to be held.  Keep ordinary
         * visible launches untouched; this opt-in mode accepts only the
         * sequenced command-file edges injected below. */
        if (getenv("GODZILLA_PARITY_INPUT_ONLY"))
            memset(&state.Gamepad, 0, sizeof(state.Gamepad));
        /* A Start press used to skip the host-decoded movie must not also
         * activate the first frontend screen.  Hold it masked until the real
         * controller/keyboard backend observes the release edge. */
        if (InterlockedCompareExchange(&godzilla_host_xmv_skip_release, 0, 0)) {
            DWORD foreground_pid = 0;
            int enter_down;
            GetWindowThreadProcessId(GetForegroundWindow(), &foreground_pid);
            enter_down = foreground_pid == GetCurrentProcessId() &&
                         (GetAsyncKeyState(VK_RETURN) & 0x8000);
            suppress_start_release =
                (state.Gamepad.wButtons & 0x0010u) || enter_down;
            state.Gamepad.wButtons &= (uint16_t)~0x0010u;
            if (!suppress_start_release)
                InterlockedExchange(&godzilla_host_xmv_skip_release, 0);
        }
        /* The XMV player normally reports its terminal event through the
         * same frontend input/update boundary.  Host decoding has no guest
         * event object, so expose one Start-shaped completion edge only after
         * natural EOF.  The movie bridge retains its final frame until this
         * poll consumes the edge, preventing a black transition frame. */
        if (getenv("GODZILLA_NAVIGATION_TEST"))
            memset(&state.Gamepad, 0, sizeof(state.Gamepad));
        MEM32(a1) = state.dwPacketNumber;
        MEM16(a1 + 4u) = state.Gamepad.wButtons;
        for (i = 0; i < 8u; ++i)
            MEM8(a1 + 6u + i) = state.Gamepad.bAnalogButtons[i];
        MEM16(a1 + 14u) = (uint16_t)state.Gamepad.sThumbLX;
        MEM16(a1 + 16u) = (uint16_t)state.Gamepad.sThumbLY;
        MEM16(a1 + 18u) = (uint16_t)state.Gamepad.sThumbRX;
        MEM16(a1 + 20u) = (uint16_t)state.Gamepad.sThumbRY;
        /* Desktop-friendly menu controls.  MainMenu turns D-pad and stick
         * motion into separate commands, so emitting both for one host key
         * double-steps the selection.  Use the retail D-pad path for arrows
         * and the pressure-sensitive A/B path for accept/back. */
        {
            static unsigned previous_keyboard_mask;
            DWORD foreground_pid = 0;
            unsigned keyboard_mask = 0u;
            GetWindowThreadProcessId(GetForegroundWindow(), &foreground_pid);
            if (foreground_pid == GetCurrentProcessId()) {
                int up = (GetAsyncKeyState(VK_UP) & 0x8000) ||
                         (GetAsyncKeyState('W') & 0x8000);
                int down = (GetAsyncKeyState(VK_DOWN) & 0x8000) ||
                           (GetAsyncKeyState('S') & 0x8000);
                int left = (GetAsyncKeyState(VK_LEFT) & 0x8000) ||
                           (GetAsyncKeyState('A') & 0x8000);
                int right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
                            (GetAsyncKeyState('D') & 0x8000);
                if (up) keyboard_mask |= 0x01u;
                if (down) keyboard_mask |= 0x02u;
                if (left) keyboard_mask |= 0x04u;
                if (right) keyboard_mask |= 0x08u;
                if (!suppress_start_release &&
                    (GetAsyncKeyState(VK_RETURN) & 0x8000))
                    keyboard_mask |= 0x10u;
                if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
                    keyboard_mask |= 0x20u;
                /* The recovered retail callback consumes every nonzero poll,
                 * rather than applying its own key-repeat delay.  Convert host
                 * keyboard holds to Xbox button edges so one tap moves exactly
                 * one item and Enter cannot activate multiple screens. */
                keyboard_mask &= ~previous_keyboard_mask;
                if (keyboard_mask & 0x01u) {
                    state.Gamepad.wButtons |= 0x0001u;
                }
                if (keyboard_mask & 0x02u) {
                    state.Gamepad.wButtons |= 0x0002u;
                }
                if (keyboard_mask & 0x04u) {
                    state.Gamepad.wButtons |= 0x0004u;
                }
                if (keyboard_mask & 0x08u) {
                    state.Gamepad.wButtons |= 0x0008u;
                }
                if (keyboard_mask & 0x10u) {
                    state.Gamepad.bAnalogButtons[0] = 255;
                }
                if (keyboard_mask & 0x20u) {
                    state.Gamepad.bAnalogButtons[1] = 255;
                }
                previous_keyboard_mask =
                    ((GetAsyncKeyState(VK_UP) & 0x8000) ||
                     (GetAsyncKeyState('W') & 0x8000) ? 0x01u : 0u) |
                    ((GetAsyncKeyState(VK_DOWN) & 0x8000) ||
                     (GetAsyncKeyState('S') & 0x8000) ? 0x02u : 0u) |
                    ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||
                     (GetAsyncKeyState('A') & 0x8000) ? 0x04u : 0u) |
                    ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||
                     (GetAsyncKeyState('D') & 0x8000) ? 0x08u : 0u) |
                    ((GetAsyncKeyState(VK_RETURN) & 0x8000) ? 0x10u : 0u) |
                    ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) ? 0x20u : 0u);
            } else {
                previous_keyboard_mask = 0u;
            }
        }
        /* Deterministic parity input.  A test driver advances the sequence
         * number in this tiny command file; each new record becomes exactly
         * one retail controller edge at XInputGetState.  This uses the same
         * game boundary as the Xemu reference injector and never writes menu
         * state directly. */
        {
            static char parity_action[16];
            static int parity_action_pending;
            const char *command_path = getenv("GODZILLA_INPUT_COMMAND_FILE");
            FILE *command = NULL;
            if (command_path && fopen_s(&command, command_path, "rb") == 0) {
                char line[64] = {0};
                unsigned sequence = 0;
                char action[16] = {0};
                if (fgets(line, sizeof(line), command) &&
                    sscanf_s(line, "%u %15s", &sequence, action,
                             (unsigned)sizeof(action)) == 2 &&
                    sequence != 0u &&
                    sequence != godzilla_input_command_sequence) {
                    godzilla_input_command_sequence = sequence;
                    strncpy_s(parity_action, sizeof(parity_action), action,
                              _TRUNCATE);
                    /* Match the Xemu oracle injector exactly: expose the
                     * command to one XInputGetState call, then release it. */
                    parity_action_pending = 1;
                    if (_stricmp(action, "start") == 0) {
                        if (godzilla_host_xmv.active &&
                            _stricmp(godzilla_host_xmv.name,
                                     "MainMenu") != 0) {
                            InterlockedExchange(
                                &godzilla_host_xmv_skip_requested, 1);
                        }
                    } else if (_stricmp(action, "capture") == 0) {
                        InterlockedExchange(&godzilla_capture_sequence_pending,
                                            (LONG)sequence);
                        parity_action[0] = 0;
                        parity_action_pending = 0;
                    }
                    fprintf(stderr, "[PARITY-INPUT] sequence=%u action=%s\n",
                            sequence, action);
                }
                fclose(command);
            }
            if (parity_action_pending) {
                if (_stricmp(parity_action, "up") == 0)
                    state.Gamepad.wButtons |= 0x0001u;
                else if (_stricmp(parity_action, "down") == 0)
                    state.Gamepad.wButtons |= 0x0002u;
                else if (_stricmp(parity_action, "left") == 0)
                    state.Gamepad.wButtons |= 0x0004u;
                else if (_stricmp(parity_action, "right") == 0)
                    state.Gamepad.wButtons |= 0x0008u;
                else if (_stricmp(parity_action, "a") == 0)
                    state.Gamepad.bAnalogButtons[0] = 255u;
                else if (_stricmp(parity_action, "b") == 0)
                    state.Gamepad.bAnalogButtons[1] = 255u;
                else if (_stricmp(parity_action, "start") == 0)
                    state.Gamepad.wButtons |= 0x0010u;
                if (--parity_action_pending == 0)
                    parity_action[0] = 0;
            }
        }
        if (getenv("GODZILLA_NAVIGATION_TEST") && godzilla_mainmenu_ready) {
            ++navigation_test_polls;
            if (navigation_test_polls == 10u) {
                state.Gamepad.wButtons |= 0x0002u;
            } else if (navigation_test_polls == 18u) {
                state.Gamepad.bAnalogButtons[0] = 255u;
            }
        }
        /* Retail routes profile A through the profile presentation's input
         * context, which eventually calls sub_000DDE60 and raises the main
         * object's +0x98 completion byte.  Until the translated presentation
         * registers its missing 0x2C4850 input entry, preserve that exact
         * callback boundary: queue the commit only while the startup shell is
         * presenting state 8 with a live child.  The game routine still owns
         * save activation and the subsequent state transition. */
        {
        static int previous_profile_a;
        const int profile_a_down = state.Gamepad.bAnalogButtons[0] != 0u;
        const int profile_a_edge = profile_a_down && !previous_profile_a;
        previous_profile_a = profile_a_down;
        if (profile_a_edge) {
            fprintf(stderr,
                    "[PROFILE-A-EDGE] state=%08X child=%08X busy=%02X pending=%u\n",
                    MEM32(0x4AD508u + 0x154u),
                    MEM32(0x4AD508u + 0x158u),
                    MEM8(0x4AD508u + 0xFCu),
                    godzilla_profile_confirm_pending);
            fflush(stderr);
        }
        if (profile_a_edge && !godzilla_mainmenu_ready &&
            godzilla_profile_confirm_pending == 0u &&
            MEM32(0x4AD508u + 0x154u) == 8u &&
            MEM32(0x4AD508u + 0x158u) != 0u) {
            InterlockedExchange((volatile LONG *)&godzilla_profile_confirm_pending,
                                121);
            /* The missing profile input context would consume this edge.  Do
             * not also leak it to the outgoing startup presentation. */
            state.Gamepad.bAnalogButtons[0] = 0u;
        }
        }
        {
            static uint32_t synthesized_packet;
            static uint32_t previous_signature = UINT32_MAX;
            uint32_t signature = state.Gamepad.wButtons |
                ((uint32_t)state.Gamepad.bAnalogButtons[0] << 16) |
                ((uint32_t)state.Gamepad.bAnalogButtons[1] << 24);
            signature ^= (uint32_t)(uint16_t)state.Gamepad.sThumbLX * 0x45D9F3Bu;
            signature ^= (uint32_t)(uint16_t)state.Gamepad.sThumbLY * 0x119DE1F3u;
            if (synthesized_packet < state.dwPacketNumber)
                synthesized_packet = state.dwPacketNumber;
            if (signature != previous_signature) {
                previous_signature = signature;
                ++synthesized_packet;
            }
            state.dwPacketNumber = synthesized_packet;
        }
        MEM32(a1) = state.dwPacketNumber;
        MEM16(a1 + 4u) = state.Gamepad.wButtons;
        for (i = 0; i < 8u; ++i)
            MEM8(a1 + 6u + i) = state.Gamepad.bAnalogButtons[i];
        MEM16(a1 + 14u) = (uint16_t)state.Gamepad.sThumbLX;
        MEM16(a1 + 16u) = (uint16_t)state.Gamepad.sThumbLY;
        ++state_calls;
        if (state_calls <= 8u || state.Gamepad.wButtons != 0u ||
            state.Gamepad.bAnalogButtons[0] != 0u ||
            state.Gamepad.bAnalogButtons[1] != 0u) {
            fprintf(stderr,
                    "[XAPI-INPUT] state #%u digital=%04X a=%u b=%u packet=%u\n",
                    state_calls, state.Gamepad.wButtons,
                    state.Gamepad.bAnalogButtons[0],
                    state.Gamepad.bAnalogButtons[1], state.dwPacketNumber);
        }
        godzilla_xapi_return(0u, 2u);
        return 1;
    }
    case 0x001DAB88u: /* DWORD XInputSetState(HANDLE, feedback) */
        if (a1) MEM32(a1) = 0u;
        godzilla_xapi_return(a0 == GODZILLA_XAPI_PAD_HANDLE ? 0u : 1167u, 2u);
        return 1;
    }
    return 0;
}

/* Vtable-only size query used when cloning the menu attachment packet.  The
 * original body is exactly `mov eax, 0x8000; ret`; it was not promoted to a
 * function because no direct call targets it. */
static void godzilla_sub_0003B560_manual(void)
{
    g_eax = 0x8000u;
    g_esp += 4u;
}

recomp_func_t recomp_lookup_manual(uint32_t xbox_va)
{
    if (xbox_va == 0x000392A0u)
        return sub_000392A0;
    if (xbox_va == 0x000DEB70u)
        return sub_000DEB70;
    if (xbox_va == 0x00038F20u)
        return sub_00038F20;
    /* These exact vtable/callback bodies live in recomp_vtable_generated.c,
     * outside the original recompiler's seeded dispatch table.  Register
     * them here so retail virtual calls execute instead of silently returning
     * zero through the safe-miss path. */
    if (xbox_va == 0x000125E0u)
        return sub_000125E0;
    if (xbox_va == 0x00015C50u)
        return sub_00015C50;
    if (xbox_va == 0x0002FCD0u)
        return sub_0002FCD0;
    if (xbox_va == 0x000305B0u)
        return sub_000305B0;
    if (xbox_va == 0x00030600u)
        return sub_00030600;
    if (xbox_va == 0x000306A0u)
        return sub_000306A0;
    if (xbox_va == 0x00033960u)
        return sub_00033960;
    if (xbox_va == 0x0003EDA0u)
        return sub_0003EDA0;
    if (xbox_va == 0x0004F770u)
        return sub_0004F770;
    if (xbox_va == 0x00037B80u)
        return sub_00037B80;
    if (xbox_va == 0x000386A0u)
        return sub_000386A0;
    if (xbox_va == 0x00039500u)
        return sub_00039500;
    if (xbox_va == 0x00039560u)
        return sub_00039560;
    if (xbox_va == 0x000399F0u)
        return sub_000399F0;
    if (xbox_va == 0x0003B560u)
        return godzilla_sub_0003B560_manual;
    if (xbox_va == 0x0003EE90u)
        return sub_0003EE90;
    if (xbox_va == 0x0003EDE0u)
        return sub_0003EDE0;
    /* Asynchronous archive-worker callback chain.  The state-machine tail
     * continuation at 0x7261E is now recovered and present in the generated
     * dispatch table, so these callbacks can execute with their retail ABI. */
    if (xbox_va == 0x000688D0u)
        return sub_000688D0;
    if (xbox_va == 0x00068AE0u)
        return sub_00068AE0;
    if (xbox_va == 0x00073870u)
        return sub_00073870;
    if (xbox_va == 0x000BAF80u)
        return sub_000BAF80;
    if (xbox_va == 0x000DA450u)
        return sub_000DA450;
    if (xbox_va == 0x000DE5C0u)
        return sub_000DE5C0;
    if (xbox_va == 0x000DFB60u)
        return sub_000DFB60;
    if (xbox_va == 0x000E2390u)
        return sub_000E2390;
    if (xbox_va == 0x000E9DE0u)
        return sub_000E9DE0;
    if (xbox_va == 0x000E9DF0u)
        return sub_000E9DF0;
    if (xbox_va == 0x000EA980u)
        return sub_000EA980;
    if (xbox_va == 0x000EAC60u)
        return sub_000EAC60;
    if (xbox_va == 0x000EF2F0u)
        return sub_000EF2F0;
    if (xbox_va == 0x000EF780u)
        return sub_000EF780;
    if (xbox_va == 0x000F0210u)
        return sub_000F0210;
    if (xbox_va == 0x000F2B40u)
        return sub_000F2B40;
    if (xbox_va == 0x0009EAB0u)
        return sub_0009EAB0;
    if (xbox_va == 0x000E07F0u)
        return sub_000E07F0;
    if (xbox_va == 0x000E0820u)
        return sub_000E0820;
    if (xbox_va == 0x000FA430u)
        return sub_000FA430;
    if (xbox_va == 0x000FA450u)
        return sub_000FA450;
    if (xbox_va == 0x00100530u)
        return sub_00100530;
    if (xbox_va == 0x001008D0u)
        return sub_001008D0;
    if (xbox_va == 0x00101F00u)
        return sub_00101F00;
    if (xbox_va == 0x00102AE0u)
        return sub_00102AE0;
    if (xbox_va == 0x00103270u)
        return sub_00103270;
    if (xbox_va == 0x00103530u)
        return sub_00103530;
    if (xbox_va == 0x0010C760u)
        return sub_0010C760;
    /* 0x11EEF0 is an interior XMV teardown callback, not a standalone ABI
     * entry.  Dispatching it as a normal function corrupts its caller. */
    if (xbox_va == 0x001553F1u)
        return sub_001553F1;
    if (xbox_va == 0x00159E00u)
        return sub_00159E00;
    if (xbox_va == 0x0010F029u)
        return godzilla_sub_0010F029_manual;
    if (xbox_va == 0x0012855Du)
        return godzilla_sub_0012855D_manual;
    if (xbox_va == 0x001285A5u)
        return godzilla_sub_001285A5_manual;
    if (xbox_va == 0x0012865Fu)
        return godzilla_sub_0012865F_manual;
    if (xbox_va == 0x0015C9BEu)
        return sub_0015C9BE;
    if (xbox_va == 0x0015A5AFu)
        return sub_0015A5AF;
    if (xbox_va == 0x00154FF1u)
        return sub_00154FF1;
    if (xbox_va == 0x001559A9u)
        return sub_001559A9;
    /* Worker-thread and static-initializer callbacks can run before the flat
     * dispatch table has been constructed.  Keep their exact retail bodies
     * reachable through the always-available manual resolver as well. */
    if (xbox_va == 0x0015CF52u)
        return sub_0015CF52;
    if (xbox_va == 0x0015D0ABu)
        return sub_0015D0AB;
    if (xbox_va == 0x001B15C0u)
        return sub_001B15C0;
    if (xbox_va == 0x001D9B1Cu)
        return sub_001D9B1C;
    if (xbox_va == 0x001D9C28u)
        return sub_001D9C28;
    if (xbox_va == 0x001DA52Du)
        return sub_001DA52D;
    if (xbox_va == 0x001DAEB2u)
        return sub_001DAEB2;
    if (xbox_va == 0x001DCF6Cu)
        return sub_001DCF6C;
    if (xbox_va == 0x0010FF6Fu)
        return sub_0010FF6F;
    if (xbox_va == 0x0002C571u)
        return sub_0002C571;
    if (xbox_va == 0x0012DF80u)
        return sub_0012DF80;
    if (xbox_va == 0x00109EC0u)
        return sub_00109EC0;
    if (xbox_va == 0x000123F0u)
        return sub_000123F0;
    if (xbox_va == 0x0010BA80u)
        return sub_0010BA80;
    if (xbox_va == 0x0010B520u)
        return sub_0010B520;
    if (xbox_va == 0x0010B550u)
        return sub_0010B550;
    if (xbox_va == 0x00030F60u)
        return sub_00030F60;
    if (xbox_va == 0x000318D0u)
        return sub_000318D0;
    if (xbox_va == 0x00067C30u)
        return sub_00067C30;
    if (xbox_va == 0x00071E10u)
        return sub_00071E10;
    if (xbox_va == 0x000EAC00u)
        return sub_000EAC00;
    if (xbox_va == 0x000E9CD0u)
        return sub_000E9CD0;
    if (xbox_va == 0x000EA920u)
        return sub_000EA920;
    if (xbox_va == 0x000DFCD0u)
        return sub_000DFCD0;
    if (xbox_va == 0x000EAC20u)
        return sub_000EAC20;
    if (xbox_va == 0x000DFB70u)
        return sub_000DFB70;
    if (xbox_va == 0x000DA490u)
        return sub_000DA490;
    if (xbox_va == 0x000E1330u)
        return sub_000E1330;
    if (xbox_va == 0x000DD600u)
        return sub_000DD600;
    if (xbox_va == 0x000DFE70u)
        return sub_000DFE70;
    return NULL;
}

void recomp_icall_fail_log(uint32_t va)
{
    typedef struct icall_miss_counter {
        uint32_t va;
        uint32_t count;
    } icall_miss_counter;
    static RECOMP_TLS icall_miss_counter misses[256];
    const uint32_t hash = (va ^ (va >> 7) ^ (va >> 13)) & 255u;
    icall_miss_counter *slot = NULL;
    unsigned probe;
    for (probe = 0; probe < 256u; ++probe) {
        icall_miss_counter *candidate = &misses[(hash + probe) & 255u];
        if (candidate->va == va || candidate->va == 0u) {
            slot = candidate;
            break;
        }
    }
    if (!slot)
        slot = &misses[hash];
    if (slot->va != va) {
        slot->va = va;
        slot->count = 0u;
    }
    ++slot->count;
    if (slot->count > 4u && (slot->count & (slot->count - 1u)) != 0u)
        return;
    fprintf(stderr,
            "[ICALL-MISS] target=%08X count=%u total=%llu esp=%08X ret=%08X\n",
            va, slot->count, (unsigned long long)g_icall_count, g_esp,
            g_esp ? MEM32(g_esp) : 0);
    fflush(stderr);
}

void recomp_trace_enter(const char *name, uint32_t va)
{
    fprintf(stderr, "[TRACE+] %08X %s esp=%08X\n", va, name, g_esp);
}

void recomp_trace_exit(const char *name, uint32_t va)
{
    fprintf(stderr, "[TRACE-] %08X %s esp=%08X\n", va, name, g_esp);
}

void recomp_trace_esp(const char *name, const char *tag)
{
    fprintf(stderr, "[TRACE-ESP] %s %s esp=%08X\n", name, tag, g_esp);
}
