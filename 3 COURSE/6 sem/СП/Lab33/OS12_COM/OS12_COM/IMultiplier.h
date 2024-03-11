#pragma once
#include <objbase.h>

interface IMultiplier : IUnknown
{
	virtual HRESULT __stdcall Mul(const double, const double, double&) = 0;
	virtual HRESULT __stdcall Div(const double, const double, double&) = 0;
};