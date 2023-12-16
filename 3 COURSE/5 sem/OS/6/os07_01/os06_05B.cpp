#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"smwEvent");

	if (he == NULL)
	{
		cout << "os06_04B: Open error Event\n";
	}
	else
	{
		cout << "OS06_04B: Open Event\n";
	}

	WaitForSingleObject(he, INFINITE);
	for (int i = 1; i <= 90; i++)
	{
		SetEvent(he);
		Sleep(100);
		cout << "os06_04B: " << i << " PID: " << GetCurrentProcessId() << endl;
	}
	CloseHandle(he);
	system("pause");

	return 0;
}
