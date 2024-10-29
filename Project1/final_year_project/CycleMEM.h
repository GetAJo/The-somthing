#include "Shared.h"
#pragma once
SIZE_T cycleProcess(DWORD pross, int target) {
    HANDLE hpross = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pross);
    if (hpross == NULL) {
        std::cout << "THE process cant open / dont exist" << std::endl;
        exit(0);
    }
    MEMORY_BASIC_INFORMATION mem_b_i;
    SIZE_T address = 0; // starting adress of the process given

    std::cout << "Searching for value: " << target << " in process memory...\n";

    while (VirtualQueryEx(hpross, (LPCVOID)address, &mem_b_i, sizeof(mem_b_i))) {
        //check if the mem its commided and accsesable
        if (mem_b_i.State == MEM_COMMIT && (mem_b_i.Protect & (PAGE_READWRITE | PAGE_READONLY | PAGE_EXECUTE_READ))) {
            //buffer alocation
            std::vector<BYTE> buffer(mem_b_i.RegionSize);
            SIZE_T bytesread;

            if (ReadProcessMemory(hpross, mem_b_i.BaseAddress, buffer.data(), mem_b_i.RegionSize, &bytesread)) {
                //cycle thrue the addresses and look for intigers
                for (SIZE_T i = 0; i <= bytesread - sizeof(int); i += sizeof(int)) {
                    int* pINT = reinterpret_cast<int*>(&buffer[i]);

                    if (*pINT == target) {
                        return (SIZE_T)mem_b_i.BaseAddress; //the mem adress its not hex
                    }
                }

            }

        }
        address += mem_b_i.RegionSize;
    }
    CloseHandle(hpross);
    return (SIZE_T)1;
}