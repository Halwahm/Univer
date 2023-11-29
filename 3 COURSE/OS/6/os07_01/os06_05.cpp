#include <Windows.h>
#include <iostream>

using namespace std;


int main()
{
    PROCESS_INFORMATION pi1, pi2;
    DWORD pId = GetCurrentProcessId();
    LPCWSTR an1 = L"D:\\УНИВЕР\\OS\\6\\os07_01\\x64\\Debug\\os06_05A.exe";
    LPCWSTR an2 = L"D:\\УНИВЕР\\OS\\6\\os07_01\\x64\\Debug\\os06_05B.exe";
    HANDLE he = CreateEvent(NULL, FALSE, FALSE, L"smwEvent");
    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
        {
            cout << "--Process os06_04A created\n";
        }
        else
        {
            cout << "--Process os06_04A not created\n";
        }
    }
    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
        {
            cout << "--Process os06_03B created\n";
        }
        else
        {
            cout << "--Process os06_03B not created\n";
        }


        for (int i = 1; i <= 90; i++)
        {
            if (i == 15)
            {
                SetEvent(he);
            }
            cout << "PID = " << pId << ", Main Thread: " << i << endl;
            Sleep(100);

        }

        WaitForSingleObject(pi1.hProcess, INFINITE);
        WaitForSingleObject(pi2.hProcess, INFINITE);
        CloseHandle(he);
        CloseHandle(pi1.hProcess);
        CloseHandle(pi2.hProcess);

        return 0;
    }

}




















//HANDLE he = CreateEvent(NULL, FALSE, FALSE, L"smwEvent");
//
//lpEventAttributes: Этот параметр определяет атрибуты безопасности для события.Если вы не хотите использовать атрибуты 
// по умолчанию, вы передаете NULL.
//
//bManualReset : Этот параметр указывает, является ли событие ручным сбросом или автоматическим сбросом.Если 
// bManualReset равен TRUE, событие будет ручным сбросом, что означает, что оно останется установленным после вызова 
// SetEvent, пока не будет явно сброшено вызовом ResetEvent.Если bManualReset равен FALSE, событие будет автоматическим 
// сбросом, и оно автоматически сбросится после того, как один поток обработает установленное событие.
//
//bInitialState : Этот параметр указывает начальное состояние события.Если bInitialState равен TRUE, событие будет установлено сразу после создания.Если bInitialState равен FALSE, событие будет сброшено.
//
//lpName : Это имя события.Если вы хотите, чтобы событие имело имя, вы передаете его в этот параметр.В вашем случае, 
//L"smwEvent" - это имя события.


//SetEvent(he);
//Функция SetEvent используется для установки состояния события в "сигнальное".Когда событие установлено, любой поток, который ожидает это событие(с помощью функций, таких как WaitForSingleObject или WaitForMultipleObjects), будет разблокирован и сможет продолжить выполнение.