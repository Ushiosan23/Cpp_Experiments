#include <Windows.h>
#include <Lmcons.h>
#include <iostream>
#include <thread>
#include <intrin.h>

double getAllPhysicMemory() {
	MEMORYSTATUSEX memoryStatus;
	memoryStatus.dwLength = sizeof(memoryStatus);
	
	GlobalMemoryStatusEx(&memoryStatus);
	return (float) memoryStatus.ullTotalPhys / pow(1024.0, 3);
}

TCHAR *getSystemName() {
	auto *uName = new TCHAR[UNLEN + 1];
	DWORD uSize = UNLEN + 1;
	
	GetUserName(uName, &uSize);
	return uName;
}

unsigned long getSystemLengthCores() {
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

//	return std::thread::hardware_concurrency();
	return sysInfo.dwNumberOfProcessors;
}

char *getCPUInfo() {
	int CPUInfo[4] = {-1};
	unsigned nextId;
	char *CPUInfoString = new char[0x40];
	
	__cpuid(CPUInfo, 0x80000000);
	nextId = CPUInfo[0];
	
	for (int i = 0x80000000; i <= nextId; ++i) {
		__cpuid(CPUInfo, i);
		
		// Interpret CPU brand string
		if (i == 0x80000002)
			memcpy(CPUInfoString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUInfoString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUInfoString + 32, CPUInfo, sizeof(CPUInfo));
	}
	
	return CPUInfoString;
}

int main() {
	std::cout << "Hello " << getSystemName() << "!" << std::endl;
	std::cout << "Ram memory: " << getAllPhysicMemory() << " GB" << std::endl;
	std::cout << "CPU cores: " << getSystemLengthCores() << std::endl;
	std::cout << "CPU info: " << getCPUInfo() << std::endl;
	std::cout << "Thread ID: " << GetCurrentThreadId() << std::endl;
	
	return 0;
}
