#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    DWORD processId = GetCurrentProcessId();
    cout << "Current process ID: " << processId << '\n';

    long long timerDuration1 = -60 * 10000000;
    HANDLE timerHandle = CreateWaitableTimer(NULL, FALSE, L"os08_04");

    if (!SetWaitableTimer(timerHandle, (LARGE_INTEGER*)&timerDuration1, 60 * 1000, NULL, NULL, FALSE))
        throw "Error setting waitable timer";

    LPCWSTR exePath = L"D:\\УНИВЕР\\OS\\7\\x64\\Debug\\OS08_04x.exe";

    PROCESS_INFORMATION processInfo1, processInfo2;
    clock_t startTime = clock();
    processInfo1.dwThreadId = 1; processInfo2.dwThreadId = 2;

    {
        STARTUPINFO startupInfo;
        ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
        startupInfo.cb = sizeof(STARTUPINFO);
        if (CreateProcess(exePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo1)) {
            cout << "Created Process os08_04x #1\n";
        }
        else {
            cout << "Failed to create Process os08_04x #1\n";
        }
    }

    {
        STARTUPINFO startupInfo;
        ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
        startupInfo.cb = sizeof(STARTUPINFO);
        if (CreateProcess(exePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo2)) {
            cout << "Created Process os08_04x #2\n";
        }
        else {
            cout << "Failed to create Process os08_04x #2\n";
        }
    }

    WaitForSingleObject(processInfo1.hProcess, INFINITE);
    WaitForSingleObject(processInfo2.hProcess, INFINITE);

    CloseHandle(timerHandle);
    cout << "Time elapsed: " << clock() - startTime << " clocks\n";
    system("pause");
    return 0;
}
