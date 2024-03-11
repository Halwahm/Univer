#pragma once
#include <objbase.h>

interface IAdder : IUnknown
{
	virtual HRESULT __stdcall Add(const double, const double, double&) = 0;
	virtual HRESULT __stdcall Sub(const double, const double, double&) = 0;
};