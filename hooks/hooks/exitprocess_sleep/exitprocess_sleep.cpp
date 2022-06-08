#include <windows.h>
#include "detours.h"

#define DEBUG 0

#if DEBUG
    #include <stdio.h>
#endif

static void (WINAPI * TrueExitProcess)(UINT uExitCode) = ExitProcess;

void WINAPI ExitProcessSleep(UINT uExitCode)
{
    uExitCode;
    #if DEBUG
        printf("Intercepted ExitProcess");
    #endif
    Sleep(0xFFFFFFFF);
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
            printf("exitprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Starting.\n");
            fflush(stdout);
        #endif

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueExitProcess, ExitProcessSleep);
        error = DetourTransactionCommit();

        #if DEBUG
            if (error == NO_ERROR) {
                printf("exitprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Detoured ExitProcess().\n");
            }
            else {
                printf("exitprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Error detouring ExitProcess(): %ld\n", error);
            }
        #endif

    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueExitProcess, ExitProcessSleep);
        error = DetourTransactionCommit();

        #if DEBUG
            printf("exitprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Removed ExitProcess() (result=%ld).\n", error);
            fflush(stdout);
        #endif

    }
    return TRUE;
}
