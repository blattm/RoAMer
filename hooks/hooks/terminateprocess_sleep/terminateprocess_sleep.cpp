#include <windows.h>
#include "detours.h"

#define DEBUG 0

#if DEBUG
    #include <stdio.h>
#endif

static BOOL (WINAPI * TrueTerminateProcess)(HANDLE hProcess, UINT uExitCode) = TerminateProcess;

BOOL WINAPI TerminateProcessSleep(HANDLE hProcess, UINT uExitCode)
{
    hProcess;
    uExitCode;
    #if DEBUG
        printf("Intercepted Process termination");
    #endif
    //Sleep(0);
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
            printf("terminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Starting.\n");
            fflush(stdout);
        #endif

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueTerminateProcess, TerminateProcessSleep);
        error = DetourTransactionCommit();

        #if DEBUG
            if (error == NO_ERROR) {
                printf("terminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Detoured TerminateProcess().\n");
            }
            else {
                printf("terminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Error detouring TerminateProcess(): %ld\n", error);
            }
        #endif

    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueTerminateProcess, TerminateProcessSleep);
        error = DetourTransactionCommit();

        #if DEBUG
            printf("terminateprocess_sleep" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Removed TerminateProcess() (result=%ld).\n", error);
            fflush(stdout);
        #endif

    }
    return TRUE;
}
