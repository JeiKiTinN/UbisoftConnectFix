#include <iostream>
#include <vector>
#include <windows.h>
#include <TlHelp32.h>
#include <stdexcept>

std::vector<DWORD> GetProcIds(const std::wstring& procName) {
	std::vector<DWORD> procIds;

    // Create a snapshot of all processes in the system
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Failed to create process snapshot");

	PROCESSENTRY32 procEntry{};
	procEntry.dwSize = sizeof(procEntry); // Set the size of the structure for WinAPI to work correctly (check tagPROCESSENTRY32W for more info)


    // Iterate over all processes in the snapshot
	if (Process32First(hSnap, &procEntry)) {
		do {

            // Compare the process name with the given one (case is not taken into account)
			if (!_wcsicmp(procEntry.szExeFile, procName.c_str()))
				procIds.push_back(procEntry.th32ProcessID);
		} while (Process32Next(hSnap, &procEntry));
	}
	CloseHandle(hSnap);
	return procIds;
}

int main()
{
    try {
        std::vector<DWORD> upcProcId = GetProcIds(L"upc.exe");

        if (upcProcId.empty()) {
            throw std::runtime_error("Failed to find upc.exe process");
        }

        std::vector<DWORD> uwcProcIds = GetProcIds(L"UplayWebCore.exe");

        std::cout << "Intercepted the Ubisoft Connect process (upc.exe)!" << std::endl;
        std::cout << "Process ID: " << upcProcId[0] << std::endl;


        // Set the affinity mask (here we use only the first processor)
        DWORD_PTR processAffinityMask = 1; 

        for (DWORD id : uwcProcIds) {
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
            if (!hProcess) {
                std::cerr << "Failed to open process with ID: " << id << std::endl;
                continue;
            }

            // Trying to set the affinity mask for the process
            if (!SetProcessAffinityMask(hProcess, processAffinityMask))
                std::cerr << "Failed to set affinity for process " << id << std::endl;
            if (!SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS))
                std::cerr << "Failed to set priority for process " << id << std::endl;

            std::cout << "Configured process with ID: " << id << std::endl;
            CloseHandle(hProcess); 
        }

       
        HANDLE hUpcProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, upcProcId[0]);
        if (!hUpcProcess)
            throw std::runtime_error("Failed to open upc.exe process");

        if (!SetProcessAffinityMask(hUpcProcess, processAffinityMask))
            std::cerr << "Failed to set affinity for upc.exe" << std::endl;
        if (!SetPriorityClass(hUpcProcess, IDLE_PRIORITY_CLASS))
            std::cerr << "Failed to set priority for upc.exe" << std::endl;

        CloseHandle(hUpcProcess);

        std::cout << "\nPress enter to exit\n";
        std::cin.get();
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}

