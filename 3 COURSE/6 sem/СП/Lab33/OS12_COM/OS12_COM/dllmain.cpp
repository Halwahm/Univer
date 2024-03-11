// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"

ULONG componentsQ = 0;
ULONG serverLocksQ = 0;

HMODULE hmodule;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		hmodule = hModule;
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

