#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

HANDLE hProcess = 0;
DWORD UWC[20] = {0x0};
HANDLE hProcessUWC[20] = {0};

DWORD_PTR processAffinityMask = 1;

DWORD GetProcId(const wchar_t* procName, bool bUWC) //function to get process id
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	int index = 0;

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					if (!bUWC) {
						procId = procEntry.th32ProcessID;
						CloseHandle(hSnap);
						return procId;
					}
					else 
					{
						if(index < (sizeof(UWC) / sizeof(UWC[0])))
						procId = procEntry.th32ProcessID;
						UWC[index] = procId;
						index++;
					}
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
}

int main()
{
	try{
		DWORD procId = GetProcId(L"upc.exe", false);
		GetProcId(L"UplayWebCore.exe", true);

		if (procId)
		{
			std::cout << "Intercepted the Ubisoft Connect process!" << std::endl;
			int lengthUWC = sizeof(UWC)/sizeof(UWC[0]);
			for (int i = 0; i < lengthUWC; i++)
			{
				if (UWC[i] != 0) {
					std::cout << "Process ID: " << UWC[i] << std::endl;
					hProcessUWC[i] = OpenProcess(PROCESS_ALL_ACCESS, NULL, UWC[i]);
					std::cout << SetProcessAffinityMask(hProcessUWC[i], processAffinityMask);
					std::cout << SetPriorityClass(hProcessUWC[i], IDLE_PRIORITY_CLASS) << std::endl;
				}
			}
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
			std::cout << "Process ID: " << procId << std::endl;
			std::cout << SetProcessAffinityMask(hProcess, processAffinityMask);
			std::cout << SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS) << std::endl;
		}
		else
		{
			std::cout << "Process not found, press enter to exit\n";
			getchar();
			return 0;
		}
		std::cout << "\nPress enter to exit\n";
		getchar();
	}
	catch (const char* msg)
	{
		std::cout << "Error. Contact the developer for more help. Error text:" << std::endl;
		std::cout << msg << std::endl;
	}
}

