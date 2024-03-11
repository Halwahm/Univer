#include "pch.h"
#include "framework.h"
#include <objbase.h>  
#include "OS12.h"
#include "Interfaces.h"

IAdder* pIAdder = NULL;
IMultiplier* pIMultiplier = NULL;

using namespace std;

char ErrdBuf[512] = "";

OS12HANDLE OS12::Init()
{
	IUnknown* pIUnknown = NULL;

	try
	{
		CoInitialize(NULL);

		HRESULT hr = CoCreateInstance(CLSID_OS12, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
		
		switch (hr)
		{
			case S_OK:
			{
				break;
			}
			case REGDB_E_CLASSNOTREG:
			{
				strcpy(ErrdBuf, "CoCreateInstance returned with code REGDB_E_CLASSNOTREG");
				throw REGDB_E_CLASSNOTREG;

				break;
			}
			case CLASS_E_NOAGGREGATION:
			{
				strcpy(ErrdBuf, "CoCreateInstance returned with code CLASS_E_NOAGGREGATION");
				throw CLASS_E_NOAGGREGATION;

				break;
			}
			case E_NOINTERFACE:
			{
				strcpy(ErrdBuf, "CoCreateInstance returned with code E_NOINTERFACE");
				throw E_NOINTERFACE;

				break;
			}
			case E_POINTER:
			{
				strcpy(ErrdBuf, "CoCreateInstance returned with code E_POINTER");
				throw E_POINTER;

				break;
			}
			default: break;
		}


	}
	catch (...)
	{
		cout << ErrdBuf << endl;
		cout << "Error code: " << GetLastError() << endl;
		return NULL;
	}

	return pIUnknown;
}

void OS12::Dispose(OS12HANDLE h)
{
	try
	{ 
		((IUnknown*)h)->Release();
		CoFreeUnusedLibraries();
	}
	catch (...)
	{
		cout << "Dispose() exception occured with error code: " << GetLastError() << endl;
	}
}

double OS12::Adder::Add(OS12HANDLE h, double x, double y)
{
	double z = 0.0;

	try
	{
		HRESULT hr = ((IUnknown*)h)->QueryInterface(IID_IAdder, (void**)&pIAdder);

		switch (hr)
		{
			case S_OK:
			{
				if (!SUCCEEDED(pIAdder->Add(x, y, z)))
				{
					strcpy(ErrdBuf, "Error on IAdder::Add");
					pIAdder->Release();
					throw("Error on IAdder::Add");
				}

				break;
			}
			case E_NOINTERFACE:
			{
				strcpy(ErrdBuf, "QueryInterface returned with code E_NOINTERFACE");
				pIAdder->Release();
				throw E_NOINTERFACE;

				break;
			}
			case E_POINTER:
			{
				strcpy(ErrdBuf, "QueryInterface returned with code E_POINTER");
				pIAdder->Release();
				throw E_POINTER;

				break;
			}
			default: break;

		}

	}
	catch (...)
	{
		cout << ErrdBuf << endl;
		cout << "Error code: " << GetLastError() << endl;
	}

	return z;
}

double OS12::Adder::Sub(OS12HANDLE h, double x, double y)
{
	double z = 0.0;

	try
	{
		HRESULT hr = ((IUnknown*)h)->QueryInterface(IID_IAdder, (void**)&pIAdder);

		switch (hr)
		{
		case S_OK:
		{
			if (!SUCCEEDED(pIAdder->Sub(x, y, z)))
			{
				strcpy(ErrdBuf, "Error on IAdder::Sub");
				pIAdder->Release();
				throw("Error on IAdder::Sub");
			}

			break;
		}
		case E_NOINTERFACE:
		{
			strcpy(ErrdBuf, "QueryInterface returned with code E_NOINTERFACE");
			pIAdder->Release();
			throw E_NOINTERFACE;

			break;
		}
		case E_POINTER:
		{
			strcpy(ErrdBuf, "QueryInterface returned with code E_POINTER");
			pIAdder->Release();
			throw E_POINTER;

			break;
		}
		default: break;

		}

	}
	catch (...)
	{
		cout << ErrdBuf << endl;
		cout << "Error code: " << GetLastError() << endl;
	}

	return z;
}

double OS12::Multiplier::Mul(OS12HANDLE h, double x, double y)
{
	double z = 0.0;

	try
	{
		HRESULT hr = ((IUnknown*)h)->QueryInterface(IID_IMultiplier, (void**)&pIMultiplier);

		switch (hr)
		{
		case S_OK:
		{
			if (!SUCCEEDED(pIMultiplier->Mul(x, y, z)))
			{
				strcpy(ErrdBuf, "Error on IMultiplier::Mul");
				pIMultiplier->Release();
				throw("Error on IMultiplier::Mul");
			}

			break;
		}
		case E_NOINTERFACE:
		{
			strcpy(ErrdBuf, "QueryInterface returned with code E_NOINTERFACE");
			pIMultiplier->Release();
			throw E_NOINTERFACE;

			break;
		}
		case E_POINTER:
		{
			strcpy(ErrdBuf, "QueryInterface returned with code E_POINTER");
			pIMultiplier->Release();
			throw E_POINTER;

			break;
		}
		default: break;

		}

		
	}
	catch (...)
	{
		cout << ErrdBuf << endl;
		cout << "Error code: " << GetLastError() << endl;
	}

	return z;
}

double OS12::Multiplier::Div(OS12HANDLE h, double x, double y)
{
	double z = 0.0;

	try
	{
		if (y == 0)
		{
			strcpy(ErrdBuf, "Incoming parameter is failure - division by zero may be occured");
			throw overflow_error("Divide by zero exception");
		}

		HRESULT hr = ((IUnknown*)h)->QueryInterface(IID_IMultiplier, (void**)&pIMultiplier);

		switch (hr)
		{
		case S_OK:
		{
			if (!SUCCEEDED(pIMultiplier->Div(x, y, z)))
			{
				strcpy(ErrdBuf, "Error on IMultiplier::Div");
				pIMultiplier->Release();
				throw("Error on IMultiplier::Div");
			}

			break;
		}
		case E_NOINTERFACE:
		{
			strcpy(ErrdBuf, "QueryInterface returned with code E_NOINTERFACE");
			pIMultiplier->Release();
			throw E_NOINTERFACE;

			break;
		}
		case E_POINTER:
		{
			strcpy(ErrdBuf, "QueryInterface returned with code E_POINTER");
			pIMultiplier->Release();
			throw E_POINTER;

			break;
		}
		default: break;

		}

	
	}
	catch (const overflow_error& err)
	{
		SetLastError(ERROR_ARITHMETIC_OVERFLOW);
		cout << err.what() << endl;
		cout << "Error code: " << GetLastError() << endl;
	}
	catch (...)
	{
		cout << ErrdBuf << endl;
		cout << "Error code: " << GetLastError() << endl;
	}

	return z;
}