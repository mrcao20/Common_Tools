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
	DWORD volumeSerialNumber;	// ���к�
	char volumeName[256];	// �̷���
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
#if _MSC_VER >= 1400 //VC2005��֧��__cpuid  
	__cpuid((int*)(void*)CPUInfo, (int)(InfoType));
#else //����ʹ��getcpuidex  
	getCpuIdex(CPUInfo, InfoType, 0);
#endif  
#endif  
}

void McDeviceInfo::getCpuIdex(unsigned int *CPUInfo, unsigned int InfoType, unsigned int ECXValue){

#if defined(_MSC_VER) // MSVC  
#if defined(_WIN64) // 64λ�²�֧���������. 1600: VS2010, ��˵VC2008 SP1֮���֧��__cpuidex.  
	__cpuidex((int*)(void*)CPUInfo, (int)InfoType, (int)ECXValue);
#else  
	if (NULL == CPUInfo)
		return;
	_asm {
		// load. ��ȡ�������Ĵ���.  
		mov edi, CPUInfo;
		mov eax, InfoType;
		mov ecx, ECXValue;
		// CPUID  
		cpuid;
		// save. ���Ĵ������浽CPUInfo  
		mov[edi], eax;
		mov[edi + 4], ebx;
		mov[edi + 8], ecx;
		mov[edi + 12], edx;
	}
#endif  
#endif  
}
