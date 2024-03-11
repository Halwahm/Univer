#include "pch.h"
#include "COM.h"
#include "INTERFACE.h"
#include "CFactory.h"

extern ULONG serverLocksQ;
extern ULONG componentsQ;

STDAPI DllCanUnloadNow()
{
	HRESULT rc = E_UNEXPECTED;
	if ((serverLocksQ == 0) && (componentsQ == 0)) rc = S_OK;
	else rc = S_FALSE;

	return rc;
}

STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void **ppv)
{
	CFactory* pF;
	HRESULT rc = E_UNEXPECTED;	
	if (clsid != CLSID_OS12) rc = CLASS_E_CLASSNOTAVAILABLE;
	else if ((pF = new CFactory()) == NULL) rc = E_OUTOFMEMORY;
	else
	{
		rc = pF->QueryInterface(iid, ppv);
		pF->Release();
	}

	return rc;
}
