#include "CycleMEM.h"
#include "Shared.h"
#include <sstream>

std::string toHexString(SIZE_T value) {
	std::stringstream a;
	a << "0x" << std::hex << value;  // Convert to hex and add "0x" prefix
	return a.str();                  // Return as a string
}

int main(DWORD process, int target) {
	SIZE_T a;
	a = cycleProcess(process,target);
	memTarhet = toHexString(a);
	return 0;
}
