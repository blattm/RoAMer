#include <windows.h>
#include "detours.h"

#define DEBUG 0

#if DEBUG
    #include <stdio.h>
#endif

static BOOL (WINAPI * TrueZwTerminateProcess)(HANDLE hProcess, NTSTATUS ExitStatus) = (BOOL (WINAPI *)(HANDLE, NTSTATUS))GetProcAddress(GetModuleHandleA("ntdll.dll"),"ZwTerminateProcess");

BOOL WINAPI ZwTerminateProcessSleep(HANDLE hProcess, NTSTATUS ExitStatus)
{
    hProcess;
    ExitStatus;
    #if DEBUG
        printf("Intercepted Process termination");
    #endif
    Sleep(0xFFFFCAFE);
    return true;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    LONG error;
    (void)hinst;
    (void)reserved;

    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();

        #if DEBUG
            printf("zwterminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Starting.\n");
            fflush(stdout);
        #endif

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueZwTerminateProcess, ZwTerminateProcessSleep);
        error = DetourTransactionCommit();

        #if DEBUG
            if (error == NO_ERROR) {
                printf("zwterminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Detoured ZwTerminateProcess().\n");
            }
            else {
                printf("zwterminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Error detouring ZwTerminateProcess(): %ld\n", error);
            }
        #endif

    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueZwTerminateProcess, ZwTerminateProcessSleep);
        error = DetourTransactionCommit();

        #if DEBUG
            printf("zwterminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Removed ZwTerminateProcess() (result=%ld).\n", error);
            fflush(stdout);
        #endif

    }
    return TRUE;
}
