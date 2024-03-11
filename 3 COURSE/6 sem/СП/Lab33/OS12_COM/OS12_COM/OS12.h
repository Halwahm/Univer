#pragma once
#include <objbase.h>
#include "IAdder.h"
#include "IMultiplier.h"

class OS12 : public IAdder, public IMultiplier
{
public:
	OS12();
	~OS12();

	// IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID, void **);
	virtual ULONG __stdcall AddRef(void);
	virtual ULONG __stdcall Release(void);

	// IAdder
	virtual HRESULT __stdcall Add(const double x, const double y, double& z);
	virtual HRESULT __stdcall Sub(const double x, const double y, double& z);

	// IMultiplier
	virtual HRESULT __stdcall Mul(const double x, const double y, double& z);
	virtual HRESULT __stdcall Div(const double x, const double y, double& z);

private:
	volatile ULONG m_Ref;
};
