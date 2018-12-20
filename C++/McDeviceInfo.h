#pragma once
#include <string>

class McDeviceInfo {

public:
	McDeviceInfo();
	~McDeviceInfo();

	std::string getCpuId();	// 获取cpu序列号
	std::string getVolumeInfo(char *rootPathName = "C:\\");	// 获取指定盘符序列号，默认为C盘

private:
	void getCpuId(unsigned int *CPUInfo, unsigned int InfoType);
	void getCpuIdex(unsigned int *CPUInfo, unsigned int InfoType, unsigned int ECXValue);

};

