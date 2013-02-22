// SystemInfo.h: interface for the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFO_H__B4EDCBCE_5054_4A0A_96FE_2F9D433BEDAE__INCLUDED_)
#define AFX_SYSTEMINFO_H__B4EDCBCE_5054_4A0A_96FE_2F9D433BEDAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int HOSTNAME_LEN = 256 ;
const int IP_ADDRESS_LEN = 32 ;
const int MAC_ADDRESS_LEN = 64;

//******************************************************************************
//*����: CSystemInfo
//*����: �õ�ϵͳ��Ϣ
//******************************************************************************
class CSystemInfo  
{
public:
	char	szHostName[256];		//������
	char	szMAC[MAC_ADDRESS_LEN];	//��һ��������MAC��ַ
	char	szIP[32];				//��һ��������IP��ַ
	long	nCPU;					//CPUʹ����
	long	nDiskTotalSpace;		//�����ܿռ�
	long	nDiskFreeSpace;			//����ʣ��ռ�
	long	nProcessNumber;			//��ǰϵͳ������
	long	nThreadNumber;			//��ǰϵͳ�߳���
	long	nMemoryTotal;			//�ܹ��ڴ���K (���������ڴ�)
	long	nUserMemory;			//�����ڴ���K (���������ڴ�)
	long	nTCPNumber;				//ϵͳ���ѽ����� TCP���Ӹ���

	int		nNetCardNumber;			//��������

protected:
	bool GetSysItemInfo(HQUERY	hQuery, char *pszPath, DWORD nType, PDH_FMT_COUNTERVALUE& fmtValue);

public:
	CSystemInfo();
	virtual ~CSystemInfo();

	void Clear();
	void GetNetcardInfo();
	void GetWinSystemInfo();
};

#endif // !defined(AFX_SYSTEMINFO_H__B4EDCBCE_5054_4A0A_96FE_2F9D433BEDAE__INCLUDED_)
