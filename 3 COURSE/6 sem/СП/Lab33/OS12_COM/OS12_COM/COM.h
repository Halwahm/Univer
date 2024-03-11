#pragma once
#include <objbase.h>

HRESULT __stdcall DllCanUnloadNow();
HRESULT __stdcall DllGetClassObject(const CLSID&, const IID&, void **);

