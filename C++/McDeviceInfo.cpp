#include "McDeviceInfo.h"
#include <intrin.h>
#include <Windows.h>
//#include <qbytearray.h>

McDeviceInfo::McDeviceInfo(){
}

McDeviceInfo::~McDeviceInfo(){
}

std::string McDeviceInfo::getCpuId() {
	char cpuId[32] = "";
	int dwBuf[4];
	getCpuId((unsigned int *)dwBuf, 1);
	sprintf(cpuId, "%08X", dwBuf[3]);
	sprintf(cpuId + 8, "%08X", dwBuf[0]);
	return std::string(cpuId);
}

std::string McDeviceInfo::getVolumeInfo(char *rootPathName) {
	DWORD volumeSerialNumber;	// 序列号
	char volumeName[256];	// 盘符名
	GetVolumeInformationA("c:\\ ", volumeName, 12, &volumeSerialNumber, NULL, NULL, NULL, 10);

	//return QByteArray::number((quint32)volumeSerialNumber, 16).toStdString();
	char temp[100];
	sprintf_s(temp, 100, "%x", volumeSerialNumber);
	return std::string(temp);
}

void McDeviceInfo::getCpuId(unsigned int *CPUInfo, unsigned int InfoType){

#if defined(__GNUC__)// GCC  
	__cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)// MSVC  
#if _MSC_VER >= 1400 //VC2005才支持__cpuid  
	__cpuid((int*)(void*)CPUInfo, (int)(InfoType));
#else //其他使用getcpuidex  
	getCpuIdex(CPUInfo, InfoType, 0);
#endif  
#endif  
}

void McDeviceInfo::getCpuIdex(unsigned int *CPUInfo, unsigned int InfoType, unsigned int ECXValue){

#if defined(_MSC_VER) // MSVC  
#if defined(_WIN64) // 64位下不支持内联汇编. 1600: VS2010, 据说VC2008 SP1之后才支持__cpuidex.  
	__cpuidex((int*)(void*)CPUInfo, (int)InfoType, (int)ECXValue);
#else  
	if (NULL == CPUInfo)
		return;
	_asm {
		// load. 读取参数到寄存器.  
		mov edi, CPUInfo;
		mov eax, InfoType;
		mov ecx, ECXValue;
		// CPUID  
		cpuid;
		// save. 将寄存器保存到CPUInfo  
		mov[edi], eax;
		mov[edi + 4], ebx;
		mov[edi + 8], ecx;
		mov[edi + 12], edx;
	}
#endif  
#endif  
}
