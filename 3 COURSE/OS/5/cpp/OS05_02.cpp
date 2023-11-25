#include <iostream>
#include <windows.h>
#include <process.h>

DWORD SwPriority(int i) {
    switch (i) {
    case 1: return BELOW_NORMAL_PRIORITY_CLASS;
    case 2: return HIGH_PRIORITY_CLASS;
    case 3: return NORMAL_PRIORITY_CLASS;
    case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
    case 5: return IDLE_PRIORITY_CLASS;
    case 6: return REALTIME_PRIORITY_CLASS;
    default: throw "No such priority class";
    }
}

int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        std::wcout << L"arg" << i << L": " << argv[i] << L"\n";
    }

    LPCWSTR an = L"..\\Debug\\OS05_02x.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi, pi1;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    unsigned long long mask;
    HANDLE hp = GetCurrentProcess();

    try {
        if (argc < 4) {
            throw "Not enough command line arguments";
        }

        DWORD pa = NULL, sa = NULL, icpu = -1;
        if (!GetProcessAffinityMask(hp, (PDWORD_PTR)&pa, (PDWORD_PTR)&sa)) throw "GetProcessAffinityMask";
        std::cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
        std::cout << " System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
        std::cout << std::dec << std::noshowbase << "\n\n";

        if (argv[1] != NULL)
        {
            unsigned long long mask;
            if (!strcmp(argv[1], "max"))
            {
                if (!SetProcessAffinityMask(hp, sa)) throw "SetProcessAffinityMask";
            }
            else {
                int mask = atoi(argv[1]);
                if (!SetProcessAffinityMask(hp, mask)) throw "SetProcessAffinityMask";
            }
            if (!GetProcessAffinityMask(hp, (PDWORD_PTR)&pa, (PDWORD_PTR)&sa)) throw "GetProcessAffinityMask";
            std::cout << " Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
            std::cout << " System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
            std::cout << std::dec << std::noshowbase;
        }
        //if (!GetProcessAffinityMask(hp, (PDWORD_PTR)&pa, (PDWORD_PTR)&sa)) throw "Process Affinity Mask";
        //std::wcout << L" Process Affinity Mask: " << std::showbase << std::hex << pa << L"\n";
        //std::wcout << L" System Affinity Mask: " << std::showbase << std::hex << sa << L"\n";
        //std::wcout << std::dec << std::noshowbase;

        if (!CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | SwPriority(atoi(argv[2])), NULL, NULL, &si, &pi))  throw "---Proc 1 wasn't created";
        if (!CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | SwPriority(atoi(argv[3])), NULL, NULL, &si, &pi1))  throw "---Proc 2 wasn't created";
    }
    catch (const std::exception& a)
    {
        std::wcout << L"Error: " << a.what() << L"\n";
    }
    catch (const char* msg)
    {
        std::wcout << L"Error: " << msg << L"\n";
    }
}

