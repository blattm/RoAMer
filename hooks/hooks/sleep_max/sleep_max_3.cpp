#include <windows.h>
#include "detours.h"

#define DEBUG 0

#if DEBUG
    #include <stdio.h>
#endif

static DWORD (WINAPI * TrueSleepEx)(DWORD dwMilliseconds, BOOL bAlertable) = SleepEx;
static void (WINAPI * TrueSleep)(DWORD dwMilliseconds) = Sleep;

DWORD WINAPI SleepExMax3(DWORD dwMilliseconds, BOOL bAlertable)
{
    DWORD timeToSleep = min(dwMilliseconds,3000);
    #if DEBUG
        printf("Requested Time: %ld. Sleep Time: %ld", dwMilliseconds, timeToSleep);
    #endif
    return TrueSleepEx(timeToSleep, bAlertable);
}

void WINAPI SleepMax3(DWORD dwMilliseconds)
{
    DWORD timeToSleep = min(dwMilliseconds,3000);
    #if DEBUG
        printf("Requested Time: %ld. Sleep Time: %ld", dwMilliseconds, timeToSleep);
    #endif
    TrueSleep(timeToSleep);
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
            printf("sleep_max_3" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Starting.\n");
            fflush(stdout);
        #endif

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueSleepEx, SleepExMax3);
        DetourAttach(&(PVOID&)TrueSleep, SleepMax3);
        error = DetourTransactionCommit();

        #if DEBUG
            if (error == NO_ERROR) {
                printf("sleep_max_3" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Detoured SleepEx() and Sleep().\n");
            }
            else {
                printf("sleep_max_3" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                    " Error detouring SleepEx() and Sleep(): %ld\n", error);
            }
        #endif

    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueSleepEx, SleepExMax3);
        DetourDetach(&(PVOID&)TrueSleep, SleepMax3);
        error = DetourTransactionCommit();

        #if DEBUG
            printf("sleep_max_3" DETOURS_STRINGIFY(DETOURS_BITS) ".dll:"
                " Removed SleepEx() and Sleep() (result=%ld).\n", error);
            fflush(stdout);
        #endif

    }
    return TRUE;
}