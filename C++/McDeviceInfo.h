#pragma once
#include <string>

class McDeviceInfo {

public:
	McDeviceInfo();
	~McDeviceInfo();

	std::string getCpuId();	// ��ȡcpu���к�
	std::string getVolumeInfo(char *rootPathName = "C:\\");	// ��ȡָ���̷����кţ�Ĭ��ΪC��

private:
	void getCpuId(unsigned int *CPUInfo, unsigned int InfoType);
	void getCpuIdex(unsigned int *CPUInfo, unsigned int InfoType, unsigned int ECXValue);

};

