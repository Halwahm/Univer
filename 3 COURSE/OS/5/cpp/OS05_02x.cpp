#include <iostream>
#include <windows.h>
#include <process.h>

int main()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    HANDLE h = GetCurrentProcess();
    HANDLE hp = GetCurrentThread();
    DWORD prth = GetPriorityClass(h);
    DWORD icpu = SetThreadIdealProcessor(hp, MAXIMUM_PROCESSORS);

    DWORD start_time = GetTickCount(); 

    for (int i = 0; i < 1000000; i++) {
        if (i % 1000 == 0) {
            std::cout << "\n# " << i << "\nProcess: " << pid << "\nThread: " << tid;
            std::cout << "\nPriority proc: " << prth;
            switch (prth) {
            case IDLE_PRIORITY_CLASS:  std::cout << " --> IDLE_PRIORITY_CLASS"; break;
            case BELOW_NORMAL_PRIORITY_CLASS: std::cout << " --> BELOW_NORMAL_PRIORITY_CLASS"; break;
            case NORMAL_PRIORITY_CLASS: std::cout << " --> NORMAL_PRIORITY_CLASS"; break;
            case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << " --> ABOVE_NORMAL_PRIORITY_CLASS"; break;
            case HIGH_PRIORITY_CLASS: std::cout << " --> HIGH_PRIORITY_CLASS"; break;
            case REALTIME_PRIORITY_CLASS: std::cout << " --> REALTIME_PRIORITY_CLASS"; break;
            default: std::cout << "error"; break;
            }
            std::cout << "\nProcessor: " << icpu << "\n-><-><-><->-<-><-><-><-><-><-><-";
            Sleep(200);
        }
    }

    DWORD end_time = GetTickCount(); 
    std::cout << "\nElapsed time: " << (end_time - start_time) << " ms" << std::endl; 

    system("pause");
}

