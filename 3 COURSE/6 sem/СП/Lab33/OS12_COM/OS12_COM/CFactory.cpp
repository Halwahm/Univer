#include "pch.h"
#include <objbase.h>
#include "CFactory.h"
#include "OS12.h"

extern ULONG serverLocksQ;

CFactory::CFactory() 
{
	m_Ref = 1;
}
CFactory::~CFactory() 
{
}

HRESULT __stdcall CFactory::QueryInterface(REFIID riid, void** ppv)
{
	HRESULT rc = S_OK;

	*ppv = NULL;
	if (riid == IID_IUnknown) *ppv = (IUnknown*)this;
	else if (riid == IID_IClassFactory) *ppv = (IClassFactory*)this;
	else rc = E_NOINTERFACE;

	if (rc == S_OK) this->AddRef();

	return rc;
}

ULONG __stdcall CFactory::AddRef(void)
{
	InterlockedIncrement((LONG*)&(this->m_Ref));

	return this->m_Ref;
}

ULONG __stdcall CFactory::Release(void)
{
	ULONG rc = this->m_Ref;

	if ((rc = InterlockedDecrement((LONG*)&(this->m_Ref))) == 0) delete this;

	return rc;
}

HRESULT __stdcall CFactory::CreateInstance(IUnknown* pUO, const IID& id, void **ppv)
{
	HRESULT rc = E_UNEXPECTED;

	OS12* pOS12;
	if (pUO != NULL) rc = CLASS_E_NOAGGREGATION;
	else if ((pOS12 = new OS12()) == NULL) rc = E_OUTOFMEMORY;
	else
	{
		rc = pOS12->QueryInterface(id, ppv);
		pOS12->Release();
	}

	return rc;
}

HRESULT __stdcall CFactory::LockServer(BOOL b)
{
	HRESULT rc = S_OK;

	if (b) InterlockedIncrement((LONG*)&(serverLocksQ)); // атомарное изменение
	else InterlockedDecrement((LONG*)&(serverLocksQ));

	return rc;
}
