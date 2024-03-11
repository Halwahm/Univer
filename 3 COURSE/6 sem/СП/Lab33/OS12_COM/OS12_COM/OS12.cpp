#include "pch.h"
#include <objbase.h>
#include <INITGUID.H>
#include "INTERFACE.h"
#include "OS12.h"

extern ULONG componentsQ;

OS12::OS12()
{
	m_Ref = 1;
	InterlockedIncrement((LONG*)&componentsQ);
}

OS12::~OS12()
{
	InterlockedDecrement((LONG*)&componentsQ);
}

HRESULT __stdcall OS12::QueryInterface(REFIID riid, void **ppv)
{
	HRESULT rc = S_OK;

	*ppv = NULL;
	if (riid == IID_IUnknown) *ppv = (IAdder*)this;
	else if (riid == IID_IAdder) *ppv = (IAdder*)this;
	else if (riid == IID_IMultiplier) *ppv = (IMultiplier*)this;
	else rc = E_NOINTERFACE;

	if (rc == S_OK) this->AddRef();

	return rc;
}

ULONG __stdcall OS12::AddRef(void)
{
	InterlockedIncrement((LONG*)&(this->m_Ref));
	return this->m_Ref;
}

ULONG __stdcall OS12::Release(void)
{
	ULONG rc = this->m_Ref;
	if ((rc = InterlockedDecrement((LONG*)&(this->m_Ref))) == 0) delete this;

	return rc;
}
HRESULT __stdcall OS12::Add(const double x, const double y, double& z)
{
	z = x + y;
	return S_OK;
}

HRESULT __stdcall OS12::Sub(const double x, const double y, double& z)
{
	z = x - y;
	return S_OK;
}

HRESULT __stdcall OS12::Mul(const double x, const double y, double& z)
{
	z = x * y;
	return S_OK;
}

HRESULT __stdcall OS12::Div(const double x, const double y, double& z)
{
	z = x / y;
	return S_OK;
}






