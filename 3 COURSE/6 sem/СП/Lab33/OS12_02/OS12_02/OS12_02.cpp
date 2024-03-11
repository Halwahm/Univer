#include <iostream>
#include <objbase.h>  
#include <INITGUID.H>
#include "Interfaces.h"

using namespace std;

int main()
{
	IAdder* pIAdder = NULL;
	IMultiplier* pIMultiplier = NULL;
	IUnknown* pIUnknown = NULL;

	char ErrdBuf[512] = "";

	try
	{ 
		CoInitialize(NULL);

		HRESULT hr = CoCreateInstance(CLSID_OS12, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);

		if (SUCCEEDED(hr))
		{
			cout << "CoCreateInstance succeded" << endl;

			if (SUCCEEDED(pIUnknown->QueryInterface(IID_IAdder, (void**)&pIAdder)))
			{
				double z = 0.0;

				if (!SUCCEEDED(pIAdder->Add(7.0, 9.0, z)))
				{
					strcpy(ErrdBuf, "Error on IAdder::Add"); 
					throw("Error on IAdder::Add");
				}
				else cout << "IAdder::Add = " << z << endl;
		
				if (!SUCCEEDED(pIAdder->Sub(2.0, 3.0, z)))
				{
					strcpy(ErrdBuf, "Error on IAdder::Sub");
					throw("Error on IAdder::Sub");
				}
				else cout << "IAdder::Sub = " << z << endl;
			} 
			else
			{
				strcpy(ErrdBuf, "Error QueryInterface IID_IAdder");
				throw("Error QueryInterface IID_IAdder");
			}

			if (SUCCEEDED(pIUnknown->QueryInterface(IID_IMultiplier, (void**)&pIMultiplier)))
			{
				double z = 0.0;

				if (!SUCCEEDED(pIMultiplier->Mul(80.0, 2.0, z)))
				{
					strcpy(ErrdBuf, "Error on IMultiplier::Mul");
					throw("Error on IMultiplier::Mul");
				}
				else cout << "IMultiplier::Mul = " << z << endl;
			
				if (!SUCCEEDED(pIMultiplier->Div(45.0, 5.0, z)))
				{
					strcpy(ErrdBuf, "Error on IMultiplier::Div");
					throw("Error on IMultiplier::Div");
				}
				else cout << "IMultiplier::Div = " << z << endl;
			}
			else
			{
				strcpy(ErrdBuf, "Error QueryInterface IID_IMultiplier");
				throw("Error QueryInterface IID_IMultiplier");
			}

		}
		else
		{
			strcpy(ErrdBuf, "CoCreateInstance failed");
			throw("CoCreateInstance failed");
		}

	}
	catch (...)
	{
		cout << ErrdBuf << endl;
		cout << "Error code: " << GetLastError() << endl;
	}

	pIAdder->Release();
	pIMultiplier->Release();
	pIUnknown->Release();
	CoFreeUnusedLibraries();

	system("pause");
	return 0;
}

