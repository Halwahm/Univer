#include "pch.h"
#include "Windows.h"
#include "INSTALL.h"
#include <iostream>
#include <assert.h>
#include "INTERFACE.h"
#include <olectl.h>   //только ради SELFREG_E_CLASS

extern HMODULE hmodule;

HRESULT __stdcall DllInstall(char* s)
{
	return S_OK;
}

HRESULT __stdcall DllRegisterServer(char* s)
{
	WCHAR szModule[512];
	DWORD dwResult = GetModuleFileName(hmodule, szModule, sizeof(szModule) / sizeof(WCHAR));
	HKEY hOS12;

	if (RegCreateKey(HKEY_CLASSES_ROOT, L"CLSID\\{3B9617F5-2CD4-4E45-A35B-8BC9B369E076}",
		&hOS12) != ERROR_SUCCESS)
		return SELFREG_E_CLASS;

	if (RegSetValue(hOS12,
		L"InprocServer32",
		REG_SZ,
		szModule, sizeof(szModule) / sizeof(WCHAR)) != ERROR_SUCCESS)
		return SELFREG_E_CLASS;

	if (RegSetValue(hOS12,
		NULL,
		REG_SZ,
		L"OS12_COM implementation",
		lstrlen(L"OS12_COM implementation")) != ERROR_SUCCESS)
		return SELFREG_E_CLASS;

	RegCloseKey(hOS12);

	return S_OK;
}

HRESULT __stdcall DllUnregisterServer(char* s)
{
	RegDeleteKey(HKEY_CLASSES_ROOT, L"CLSID\\{3B9617F5-2CD4-4E45-A35B-8BC9B369E076}\\InprocServer32");
	RegDeleteKey(HKEY_CLASSES_ROOT, L"CLSID\\{3B9617F5-2CD4-4E45-A35B-8BC9B369E076}");

	return S_OK;
}