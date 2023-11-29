#include <Windows.h>
#include <iostream>

using namespace std;


int main()
{
    PROCESS_INFORMATION pi1, pi2;
    DWORD pId = GetCurrentProcessId();
    LPCWSTR an1 = L"D:\\УНИВЕР\\OS\\6\\os07_01\\x64\\Debug\\os06_04A.exe";
    LPCWSTR an2 = L"D:\\УНИВЕР\\OS\\6\\os07_01\\x64\\Debug\\os06_04B.exe";
    HANDLE hs = CreateSemaphore(NULL, 2, 2, L"smwSem");
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
                cout << "os06_04: prevcount = " << prevcount << endl;
            }
            cout << "PID = " << pId << ", Main Thread: " << i << endl;
            Sleep(100);
        }

        WaitForSingleObject(pi1.hProcess, INFINITE);
        WaitForSingleObject(pi2.hProcess, INFINITE);
        CloseHandle(hs);
        CloseHandle(pi1.hProcess);
        CloseHandle(pi2.hProcess);

        return 0;
    }

}
























//HANDLE hs = CreateSemaphore(NULL, 2, 2, L"smwSem");
//NULL: Здесь передается указатель на атрибуты безопасности(в данном случае, используется значение по умолчанию).
//
//2 : Это начальное количество счетчиков семафора.В вашем случае семафор создается с начальным значением 2.
//
//2 : Это максимальное количество счетчиков семафора.В вашем случае максимальное значение также установлено в 2.
//
//L"smwSem" : Это уникальное имя семафора.Символ "L" перед строкой указывает, что это широкая строка(Unicode).

//Функция ReleaseSemaphore используется для увеличения счетчика семафора.Семафоры в программировании являются объектами 
//синхронизации, используемыми для ограничения доступа к ресурсам для нескольких потоков или процессов.

// ReleaseSemaphore(hs, 1, &prevcount);
// hSemaphore: Дескриптор семафора, который нужно увеличить.

// lReleaseCount : Количество увеличений счетчика семафора.

// lpPreviousCount : Указатель на переменную, в которую будет записано предыдущее значение счетчика семафора.Может быть NULL, если предыдущее значение не требуется.