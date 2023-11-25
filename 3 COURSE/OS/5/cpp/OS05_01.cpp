#include <Windows.h>
#include <iostream>

void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);
    std::cout << " --- Current PID = " << GetCurrentProcessId() << " \n";
    switch (prty)
    {
    case IDLE_PRIORITY_CLASS: std::cout << " ----+ Priority of process = IDLE_PRIORITY_CLASS \n"; break;
    case BELOW_NORMAL_PRIORITY_CLASS: std::cout << " ----+ Priority of process = BELOW_NORMAL_PRIORITY_CLASS \n"; break;
    case NORMAL_PRIORITY_CLASS: std::cout << " ----+ Priority of process = NORMAL_PRIORITY_CLASS \n"; break;
    case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << " ----+ Priority of process = ABOVE_NORMAL_PRIORITY_CLASS \n"; break;
    case HIGH_PRIORITY_CLASS: std::cout << " ----+ Priority of process = HIGH_PRIORITY_CLASS \n"; break;
    case REALTIME_PRIORITY_CLASS: std::cout << " ----+ Priority of process = REALTIME_PRIORITY_CLASS \n"; break;
    default: std::cout << " ----+ Priority of process = ? \n"; break;
    }
    return;
}

void printThreadPrty(HANDLE h)
{
    DWORD icpu = SetThreadIdealProcessor(h, MAXIMUM_PROCESSORS);
    DWORD prty = GetThreadPriority(h);
    std::cout << " --- Current Thread ID = " << GetCurrentThreadId() << "\n";
    std::cout << " ----+ priority = " << prty << " \n";
    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST: std::cout << " ----+ Priority of thread     = THREAD_PRIORITY_LOWEST \n"; break;
    case THREAD_PRIORITY_BELOW_NORMAL: std::cout << " ----+ Priority of thread = THREAD_PRIORITY_BELOW_NORMAL \n"; break;
    case THREAD_PRIORITY_NORMAL: std::cout << " ----+ Priority of thread = THREAD_PRIORITY_NORMAL \n"; break;
    case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << " ----+ Priority of thread = THREAD_PRIORITY_ABOVE_NORMAL \n"; break;
    case THREAD_PRIORITY_HIGHEST: std::cout << " ----+ Priority of thread = THREAD_PRIORITY_HIGHEST \n"; break;
    case THREAD_PRIORITY_IDLE: std::cout << " ----+ Priority of thread = THREAD_PRIORITY_IDLE \n"; break;
    case THREAD_PRIORITY_TIME_CRITICAL: std::cout << " ----+ Priority of thread = THREAD_PRIORITY_TIME_CRITICAL \n"; break;
    default: std::cout << " ----+ Priority of thread = ? \n"; break;
    }
    std::cout << " ----+ Processor = " << icpu << " \n";
    return;
}

std::string toBinary(int n)
{
    std::string r;
    while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
    return r;
}
int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();


    printProcessPrty(hp);
    printThreadPrty(ht);

    try
    {
        {
            DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
            if (!GetProcessAffinityMask(hp, &pa, &sa)) throw "GetProcessAffinityMask";
            int countProcessors = 0;
            DWORD_PTR mask = 1;
            for (int i = 0; i < sizeof(DWORD_PTR); ++i)
            {
                if (pa & mask) 
                    countProcessors++;
                mask <<= 1; 
            }
            std::cout << " Process Affinity Mask: " << toBinary(pa) << "\n";
            std::cout << " System Affinity Mask: " << toBinary(sa) << "\n";
            std::cout << " Number of Processors available to the process: " << countProcessors << "\n";
        }
    }
    catch (char* msg) { std::cout << "Error " << msg << "\n"; }
    return 0;
}