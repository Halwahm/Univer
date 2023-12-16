#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"smwSem");
	if (hs == NULL)
	{
		cout << "os06_04B: Open error Semaphore\n";
	}
	else
	{
		cout << "OS06_04B: Open Semaphore\n";
	}

	LONG prevcount = 0;
	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hs, INFINITE);
		}
		if (i == 60)
		{
			ReleaseSemaphore(hs, 1, &prevcount);
			cout << "os06_04B: prevcount = " << prevcount << endl;
		}
		Sleep(100);
		cout << "os06_04B: " << i << " PID: " << GetCurrentProcessId() << endl;
	}
	CloseHandle(hs);
	system("pause");

	return 0;
}
