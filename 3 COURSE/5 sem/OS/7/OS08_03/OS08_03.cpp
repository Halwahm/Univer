#include <iostream>
#include <Windows.h>

using namespace std;

HANDLE printTimer = CreateWaitableTimer(NULL, FALSE, L"print");
HANDLE closeTimer = CreateWaitableTimer(NULL, FALSE, L"close");
bool shouldPrint = false, keepIterating = true;

HANDLE CreateThread(LPTHREAD_START_ROUTINE function)
{
    DWORD threadId = NULL;
    HANDLE thread = CreateThread(NULL, 0, function, NULL, 0, &threadId);

    if (thread == NULL)
    {
        throw "Error creating child thread";
    }

    return thread;
}

void CloseTimerWatcher()
{
    WaitForSingleObject(closeTimer, INFINITE);

    keepIterating = false;

    CloseHandle(closeTimer);
}

void PrintTimerWatcher()
{
    while(keepIterating)
    {
        WaitForSingleObject(printTimer, INFINITE);

        shouldPrint = true;
    }

    CloseHandle(printTimer);
}

int main()
{
    LPTHREAD_START_ROUTINE functions[] = { (LPTHREAD_START_ROUTINE)CloseTimerWatcher,
        (LPTHREAD_START_ROUTINE)PrintTimerWatcher };

    const int arraySize = sizeof(functions) / sizeof(LPTHREAD_START_ROUTINE);
    HANDLE threads[arraySize];

    LARGE_INTEGER closeTimeout;
    closeTimeout.QuadPart = -150000000LL;

    LARGE_INTEGER printTimeout;
    printTimeout.QuadPart = -30000000LL;

    clock_t currentTime, startTime = clock();

    unsigned long int iterations;

    for (iterations = 0; iterations < arraySize; iterations++)
        threads[iterations] = CreateThread(functions[iterations]);

    SetWaitableTimer(printTimer, &printTimeout, 3000, NULL, NULL, FALSE);
    SetWaitableTimer(closeTimer, &closeTimeout, 0, NULL, NULL, 0);

    for (iterations = 0; keepIterating; iterations++)
    {
        currentTime = ((clock() - startTime) / CLOCKS_PER_SEC);

        if (shouldPrint)
        {
            cout << "Current Time:  " << currentTime << "\tNumber of Iterations: " << iterations << '\n';
            shouldPrint = false;
        }
    }

    cout << "Final Iteration Count: " << iterations << '\n';

    for (iterations = 0; iterations < arraySize; iterations++)
        CloseHandle(threads[iterations]);

    system("pause");
    return 0;
}
