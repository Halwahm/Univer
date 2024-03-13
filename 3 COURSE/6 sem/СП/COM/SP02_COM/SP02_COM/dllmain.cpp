    #include "pch.h"
    #include <fstream>
    #include <Windows.h>
    #include <iostream>
    #include <combaseapi.h>
    #include "MathFactory.h"

    using namespace std;

    HMODULE hmodule;

    static const CLSID CLSID_CA =
    { 0x02fe8a5e, 0x281b, 0x4e3a, { 0x8f, 0x87, 0x6c, 0x54, 0x4d, 0xed, 0xa9, 0x94 } };

    const WCHAR* FNAME = L"SmwCA.dll";
    const WCHAR* VerInd = L"Smw.CA";
    const WCHAR* ProgId = L"Smw.CA.1";

    BOOL APIENTRY DllMain(
        HMODULE hModule,
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

    HRESULT __declspec(dllexport) DllInstall(bool b, PCWSTR s)
    {
        return S_OK;
    }

    HRESULT __declspec(dllexport) DllRegisterServer() {
        return RegisterServer(hmodule, CLSID_CA, FNAME, VerInd, ProgId);
    }

    HRESULT __declspec(dllexport) DllUnregisterServer() {
        return UnregisterServer(CLSID_CA, VerInd, ProgId);
    }


    STDAPI DllCanUnloadNow()
    {
        return S_OK;
    }

    STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, LPVOID* ppv) {
        HRESULT rc = E_UNEXPECTED;
        MathFactory* pF;
        if (clsid != CLSID_CA) 
            rc = CLASS_E_CLASSNOTAVAILABLE;
        else if ((pF = new MathFactory()) == NULL) 
            rc = E_OUTOFMEMORY;
        else {
            rc = pF->QueryInterface(iid, ppv);
            pF->Release();
        }

        return rc;
    }