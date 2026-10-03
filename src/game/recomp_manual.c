#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "recomp_types.h"

extern void d3d8_PresentFrame(void);
extern void kelvin_init(void);
extern int kelvin_method(uint32_t subchannel, uint32_t method, uint32_t param);
extern void kelvin_end_frame(void);
extern void sub_00039500(void);
extern void sub_00039560(void);
extern void sub_000399F0(void);

static void godzilla_seed_mainmenu_movie_surface(void);
static uint32_t godzilla_host_frame;

static int godzilla_trace_enabled(void)
{
    static int enabled = -1;
    if (enabled < 0)
        enabled = getenv("GODZILLA_TRACE_FRAME") != NULL;
    return enabled;
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
                if (dry) continue;
                if (m == 0x17FCu && param != 0u &&
                    texture0_offset[subchannel] == 0x01991480u)
                    godzilla_seed_mainmenu_movie_surface();
                kelvin_method(subchannel, m, param);
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
    g_kelvin_log_draws = godzilla_trace_enabled() &&
                         ((frame <= 12u) ||
                          (frame >= 200u && frame <= 204u) ||
                          (prev_draws == 1u && frame <= 590u));
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
static void godzilla_seed_mainmenu_movie_surface(void)
{
    enum { FRAME_BYTES = 640 * 480 * 2, EXPECTED_FRAMES = 90 };
    static uint8_t *frames;
    static size_t frame_count;
    static ULONGLONG movie_start_ms;
    static uint32_t last_seed_frame = UINT32_MAX;
    static int attempted;

    if (!getenv("GODZILLA_SKIP_MOVIES"))
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
        memcpy((void *)XBOX_PTR(0x01991480u),
               frames + frame_index * FRAME_BYTES, FRAME_BYTES);
        last_seed_frame = godzilla_host_frame;
    }
}

void godzilla_d3d_frame_hook(void)
{
    static uint32_t frame;
    static uint32_t replay_cursor;
    static int initialized;
    uint32_t device = MEM32(0x00134078u);
    uint32_t methods = 0, draws = 0, malformed = 0;

    ++frame;
    godzilla_host_frame = frame;
    /* XMV uses NV2A overlay/video commands which are not Kelvin 3D methods.
     * Replaying those through the 3D translator can interpret video payloads
     * as texture state.  The startup state is known to have reached the menu
     * by frame 1024; attach there and consume only subsequent menu commands. */
    if (!getenv("GODZILLA_SKIP_MOVIES") && frame < 200u)
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
            if (pb_cursor > replay_cursor)
                replay_cursor = godzilla_replay_pushbuffer(
                    replay_cursor, pb_cursor, frame,
                    &methods, &draws, &malformed);
            else
                kelvin_end_frame();
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
    d3d8_PresentFrame();
}

typedef void (*recomp_func_t)(void);

extern void sub_000125E0(void);
extern void sub_00030600(void);
extern void sub_000306A0(void);
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

extern void xbox_HeapFree(uint32_t xbox_va);

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

enum { GODZILLA_BOOT_ALLOC_CAPACITY = 16384 };
static struct {
    uint32_t va;
    uint32_t size;
} g_godzilla_boot_allocations[GODZILLA_BOOT_ALLOC_CAPACITY];
static unsigned g_godzilla_boot_allocation_count;

uint32_t godzilla_bootstrap_heap_alloc(uint32_t flags, uint32_t size)
{
    static uint32_t next_va = 0x82000000u;
    static unsigned call_count;
    uint32_t actual = size ? size : 1u;
    uint32_t result = (next_va + 15u) & ~15u;
    uint32_t end = result + ((actual + 15u) & ~15u);
    if (end < result || end > 0x83F00000u)
        return 0;
    next_va = end;
    if (flags & 8u)
        memset(XBOX_PTR(result), 0, actual);
    if (g_godzilla_boot_allocation_count < GODZILLA_BOOT_ALLOC_CAPACITY) {
        g_godzilla_boot_allocations[g_godzilla_boot_allocation_count].va = result;
        g_godzilla_boot_allocations[g_godzilla_boot_allocation_count].size = actual;
        ++g_godzilla_boot_allocation_count;
    }
    if (++call_count <= 8)
        fprintf(stderr, "[BOOT-HEAP] #%u flags=%08X size=%08X result=%08X\n",
                call_count, flags, size, result);
    return result;
}

/* Allocation records live beside the bump allocator so CRT realloc can copy
 * only the valid prefix of an existing block. */
static uint32_t godzilla_bootstrap_heap_size(uint32_t va)
{
    unsigned i;
    for (i = g_godzilla_boot_allocation_count; i > 0; --i) {
        if (g_godzilla_boot_allocations[i - 1u].va == va)
            return g_godzilla_boot_allocations[i - 1u].size;
    }
    return 0;
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
 * The bump allocator intentionally does not reclaim the old block; menu boot
 * has ample contiguous-window headroom and retaining it is safer than passing
 * a host-incompatible Xbox heap header to the translated free path.
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
        }
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

/* Xbox D3D tags pBits with 0xF0000000 for lock flag 0x40 because that
 * address range aliases the same physical RAM on hardware.  Preserve the
 * original lock operation, then canonicalize only that returned CPU pointer
 * for our guest memory layout. */
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
        if ((tagged_bits & 0xF0000000u) == 0xF0000000u) {
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
 * blocks to the title's translated RTL_HEAP coalescer; they are allocations
 * from xbox_HeapAlloc and must go directly back to that allocator's block
 * table.  XNET and DirectSound both churn these buffers every frame. */
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
        xbox_HeapFree(allocation);

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
    if (g_ecx >= 4u)
        g_ecx -= MEM32(g_ecx - 4u);
    if (s_pwk_submit_trace < 96u) {
        fprintf(stderr,
                "[PWK-SUBMIT] n=%u object=%08X node=%08X interface=%08X arg=%08X\n",
                s_pwk_submit_trace, g_ecx, MEM32(g_ecx + 8u), g_ecx + 0x78u,
                MEM32(g_esp + 4u));
    }
    ++s_pwk_submit_trace;
    sub_000DE660();
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
    /* These exact vtable/callback bodies live in recomp_vtable_generated.c,
     * outside the original recompiler's seeded dispatch table.  Register
     * them here so retail virtual calls execute instead of silently returning
     * zero through the safe-miss path. */
    if (xbox_va == 0x000125E0u)
        return sub_000125E0;
    if (xbox_va == 0x00030600u)
        return sub_00030600;
    if (xbox_va == 0x000306A0u)
        return sub_000306A0;
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
    /* The 0x3F320/0x688D0/0x68AE0/0x73870 callback chain belongs to the
     * asynchronous sound archive worker.  Its downstream 0x7261E target is
     * not yet a valid recovered entry, so keep this unrelated worker inert
     * while bringing up the front end. */
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
    /* 0x10C760 starts the retail sound-stream worker.  Keep it on the safe
     * miss path until its downstream callback table is recovered; enabling
     * it early lets that worker execute an unresolved 0x7261E callback. */
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
