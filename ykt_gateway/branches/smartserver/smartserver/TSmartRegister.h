// TSmartRegister.h: interface for the TSmartRegister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTREGISTER_H__18559704_303A_46A8_9C19_DFDE871011A4__INCLUDED_)
#define AFX_TSMARTREGISTER_H__18559704_303A_46A8_9C19_DFDE871011A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//************************************************************************************
//*����: TSmartRegister  
//*����: ����������
//************************************************************************************
class TSmartRegister  
{
public:
	TCHAR   strServerINI[MAX_PATH];

	int     m_nPort;
	long    m_nMaxDev;
	char    m_szTaskDLL[MAX_PATH];

	int     m_nModule;
	int     m_nMonitor;
	
	char    m_szProtocol[MAX_PATH];

	//����ӿ�ͨ��
	char    m_szChannels[MAX_PATH];
	char    m_szCenter[128];
	int     m_nCenterPort;
	int     m_nEncode;
	int     m_nChannelsNotify;
	int		m_nFunc;
	int		m_nServerNo;
	long	m_nCollData_Tick;	//�ɼ���������ļ��ʱ��
	long	m_nNoTask_Tick;		//û������ʱ���������ʱ��

public:
	TSmartRegister();
	virtual ~TSmartRegister();

	void Reset();
	void ReadParameter();

	bool GetModule(char *pszFileName, int nIndex);
	bool GetMonitor(char *pHost, char *pUser, char *pPass);
};

#endif // !defined(AFX_TSMARTREGISTER_H__18559704_303A_46A8_9C19_DFDE871011A4__INCLUDED_)
