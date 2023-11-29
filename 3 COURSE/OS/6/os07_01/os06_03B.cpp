#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"smwMutex");
	if (hm == NULL)
	{
		cout << "os06_03B: Open err Mutex\n";
	}
	else
	{
		cout << "OS06_03B: Open Mutex\n";
	}

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hm, INFINITE);
		}
		if (i == 60)
		{
			ReleaseMutex(hm);
		}
		Sleep(100);
		cout << "os06_03B: " << i << " PID: " << GetCurrentProcessId() << endl;


	}
	system("pause");
}
