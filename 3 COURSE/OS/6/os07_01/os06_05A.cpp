#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"smwEvent");

	if (he == NULL)
	{
		cout << "os06_04A: Open error Event\n";
	}
	else
	{
		cout << "OS06_04A: Open Event\n";
	}

	WaitForSingleObject(he, INFINITE);
	for (int i = 1; i <= 90; i++)
	{
		SetEvent(he);
		Sleep(100);
		cout << "os06_04A: " << i << " PID: " << GetCurrentProcessId() << endl;
	}
	CloseHandle(he);
	system("pause");

	return 0;
}











//HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"smwEvent");
//
//
//EVENT_ALL_ACCESS: Устанавливает все возможные права доступа к объекту события.
//FALSE : Означает, что событие не создается заново, а открывается существующее.
//L"smwEvent" : Уникальное имя объекта события.