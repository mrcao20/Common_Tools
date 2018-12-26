// ---------------------------------------------------------------
// FlieNmae: 
//   SofInfo.h
// Remark:
//   ͨ����ȡע����ñ����Ѱ�װ�����Ϣ��
// ---------------------------------------------------------------
#pragma once
#include <vector>
#include <atlstr.h>

struct SoftInfo
{
	// �����
	CString m_strSoftName;
	// ����汾��
	CString m_strSoftVersion;
	// �����װĿ¼
	CString m_strInstallLocation;
	// �����������
	CString m_strPublisher;
	// ��������������·��
	CString m_strMainProPath;
	// ж��exe��������·��
	CString m_strUninstallPth;
};
class CSoftInfo
{
private:
	// �����Ѱ�װ���������װ��Ϣ
	std::vector<SoftInfo> m_SoftInfoArr;
	// ����ϵͳ������Ϣ
	std::vector<SoftInfo> m_SystemPatchesArr;
public:
	CSoftInfo();
	~CSoftInfo() {}

	// ��ȡһ���������������װ��Ϣ��Vector
	std::vector<SoftInfo> GetSoftInfo(void) const;
	// ��ȡ�����Ѱ�װ���������
	void GetSoftName(std::vector<LPCTSTR>& lpszSoftName);
	// ��ȡ�����Ѱ�װ��������汾��
	void GetSoftVersion(std::vector<LPCTSTR>& lpszSoftVersion);
	// ��ȡ�����Ѱ�װ���������װĿ¼
	void GetInstallLocation(std::vector<LPCTSTR>& lpszInstallLocation);
	// ��ȡ�����Ѱ�װ���������������
	void GetPublisher(std::vector<LPCTSTR>& lpszPublisher);
	// ��ȡ�����Ѱ�װ�����������������·��
	void GetMainProPath(std::vector<LPCTSTR>& lpszMainProPath);
	// ��ȡ�����Ѱ�װ�������ж�س�������·��
	void GetUninstallPth(std::vector<LPCTSTR>& lpszSoftName);
	// ��ȡһ������ϵͳ������Ϣ��Vector
	std::vector<SoftInfo> GetSystemPatchesInfo(void) const;
	// ��ȡ�����Ѱ�װϵͳ������
	void GetSystemPatchesName(std::vector<LPCTSTR>& lpszSoftName);
};