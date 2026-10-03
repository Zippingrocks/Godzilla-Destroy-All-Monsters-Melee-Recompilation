#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dbghelp.h>
#include <tlhelp32.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "dbghelp.lib")

static unsigned long long filetime_u64(FILETIME value)
{
    ULARGE_INTEGER result;
    result.LowPart = value.dwLowDateTime;
    result.HighPart = value.dwHighDateTime;
    return result.QuadPart;
}

int main(int argc, char **argv)
{
    DWORD pid;
    HANDLE process;
    HANDLE snapshot;
    THREADENTRY32 entry = { sizeof(entry) };
    uintptr_t image_base = 0;

    if (argc < 2) {
        fprintf(stderr, "usage: sample_thread_pcs <pid> [xbox-va ...]\n");
        return 2;
    }

    pid = (DWORD)strtoul(argv[1], NULL, 0);
    process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!process) {
        fprintf(stderr, "OpenProcess(%lu) failed: %lu\n", pid, GetLastError());
        return 1;
    }

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 module = { sizeof(module) };
        if (Module32First(snapshot, &module))
            image_base = (uintptr_t)module.modBaseAddr;
        CloseHandle(snapshot);
    }

    SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES);
    SymInitialize(process, NULL, TRUE);

    printf("pid=%lu image-base=%016" PRIXPTR "\n", pid, image_base);
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "CreateToolhelp32Snapshot failed: %lu\n", GetLastError());
        CloseHandle(process);
        return 1;
    }

    if (Thread32First(snapshot, &entry)) {
        do {
            HANDLE thread;
            CONTEXT context;
            FILETIME created, exited, kernel, user;
            char storage[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
            SYMBOL_INFO *symbol = (SYMBOL_INFO *)storage;
            DWORD64 displacement = 0;
            IMAGEHLP_LINE64 line = { sizeof(line) };
            DWORD line_displacement = 0;

            if (entry.th32OwnerProcessID != pid)
                continue;

            thread = OpenThread(THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME |
                                    THREAD_GET_CONTEXT,
                                FALSE, entry.th32ThreadID);
            if (!thread)
                continue;

            ZeroMemory(&context, sizeof(context));
            context.ContextFlags = CONTEXT_FULL;
            if (SuspendThread(thread) == (DWORD)-1) {
                CloseHandle(thread);
                continue;
            }

            if (!GetThreadContext(thread, &context)) {
                ResumeThread(thread);
                CloseHandle(thread);
                continue;
            }
            ZeroMemory(storage, sizeof(storage));
            symbol->SizeOfStruct = sizeof(*symbol);
            symbol->MaxNameLen = MAX_SYM_NAME;
            GetThreadTimes(thread, &created, &exited, &kernel, &user);

            printf("tid=%-6lu cpu100ns=%-14llu rip=%016llX rva=%08llX rsp=%016llX"
                   " rax=%016llX rcx=%016llX rdx=%016llX rbx=%016llX"
                   " rsi=%016llX rdi=%016llX rbp=%016llX",
                   entry.th32ThreadID,
                   filetime_u64(kernel) + filetime_u64(user),
                   (unsigned long long)context.Rip,
                   image_base ? (unsigned long long)(context.Rip - image_base) : 0,
                   (unsigned long long)context.Rsp,
                   (unsigned long long)context.Rax,
                   (unsigned long long)context.Rcx,
                   (unsigned long long)context.Rdx,
                   (unsigned long long)context.Rbx,
                   (unsigned long long)context.Rsi,
                   (unsigned long long)context.Rdi,
                   (unsigned long long)context.Rbp);
            if (SymFromAddr(process, context.Rip, &displacement, symbol))
                printf(" symbol=%s+0x%llX", symbol->Name,
                       (unsigned long long)displacement);
            if (SymGetLineFromAddr64(process, context.Rip, &line_displacement,
                                     &line))
                printf(" source=%s:%lu+0x%lX", line.FileName, line.LineNumber,
                       line_displacement);
            putchar('\n');

            {
                STACKFRAME64 frame;
                unsigned depth;
                ZeroMemory(&frame, sizeof(frame));
                frame.AddrPC.Offset = context.Rip;
                frame.AddrPC.Mode = AddrModeFlat;
                frame.AddrStack.Offset = context.Rsp;
                frame.AddrStack.Mode = AddrModeFlat;
                frame.AddrFrame.Offset = context.Rbp;
                frame.AddrFrame.Mode = AddrModeFlat;

                for (depth = 0; depth < 16; ++depth) {
                    DWORD64 caller;
                    if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread,
                                     &frame, &context, NULL,
                                     SymFunctionTableAccess64,
                                     SymGetModuleBase64, NULL))
                        break;
                    caller = frame.AddrPC.Offset;
                    if (!caller)
                        break;

                    ZeroMemory(storage, sizeof(storage));
                    symbol->SizeOfStruct = sizeof(*symbol);
                    symbol->MaxNameLen = MAX_SYM_NAME;
                    displacement = 0;
                    printf("  #%02u %016llX", depth + 1,
                           (unsigned long long)caller);
                    if (SymFromAddr(process, caller, &displacement, symbol))
                        printf(" %s+0x%llX", symbol->Name,
                               (unsigned long long)displacement);
                    putchar('\n');
                }
            }
            ResumeThread(thread);
            CloseHandle(thread);
        } while (Thread32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);

    if (argc > 2) {
        int argi;
        for (argi = 2; argi < argc; ++argi) {
            uint32_t xbox_va = (uint32_t)strtoul(argv[argi], NULL, 0);
            uint32_t words[64];
            SIZE_T got = 0;
            unsigned wi;
            uintptr_t native_addr = (uintptr_t)xbox_va + 0x10000u;
            ZeroMemory(words, sizeof(words));
            if (!ReadProcessMemory(process, (const void *)native_addr, words,
                                   sizeof(words), &got)) {
                printf("peek xbox=%08X native=%016" PRIXPTR " failed=%lu\n",
                       xbox_va, native_addr, GetLastError());
                continue;
            }
            printf("peek xbox=%08X native=%016" PRIXPTR " bytes=%llu\n",
                   xbox_va, native_addr, (unsigned long long)got);
            for (wi = 0; wi < got / sizeof(uint32_t); wi += 4) {
                printf("  %08X: %08X %08X %08X %08X\n",
                       xbox_va + wi * 4u,
                       words[wi], words[wi + 1], words[wi + 2], words[wi + 3]);
            }
        }
    }

    SymCleanup(process);
    CloseHandle(process);
    return 0;
}
