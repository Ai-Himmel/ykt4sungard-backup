// Interface.h : main header file for the INTERFACE DLL
//

#if !defined(AFX_INTERFACE_H__BF4A8385_4661_4117_BDA8_7DCBE8C08BAA__INCLUDED_)
#define AFX_INTERFACE_H__BF4A8385_4661_4117_BDA8_7DCBE8C08BAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "mytypes.h"								/* ���Ͷ���ͷ�ļ� */
#include "loadcf.h"									/* ��ȡ�����ļ� */
#include "cpack.h"									/* ���ṹͷ�ļ� */
#include "DRTPApi.h"
#include "..\..\include\common.h"

#define INIFILE   "Interface.ini"
#define ALLDEVICE "00000000"

//*******************************************************************************
//*����: TSSFTable
//*����: 0226 �շѻ�,0228 ���ػ�,0201 ��ֵ��,0232 �ϻ�������
//*      0230 �����,0234 �����(��ԡר��),0236 ����ʽ��ԡ�Ʒ���,0240 ��Ʊ��,
//*      0130 ���ʶ���,1055 �ֳֻ����Ʒѣ�
//*******************************************************************************
struct TSSFTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
	char    sCommVer[5];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[5];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//��Ƭ�ṹ����(ʮ������)
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�
	long    nTimes;				//����
	char    sWalletcode[3];		//Ǯ��
	long    nInMoney;           //�뿨���
	long    nOutMoney;          //�������
	char    sDealCode1[8];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};

//*******************************************************************************
//*����: TSJSBTable
//*����: 0121 ��ʱ��,5501 ����ͨ����
//*******************************************************************************
struct TSJSBTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
//	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
//	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sCommVer[5];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[5];		//����ͨ������ԭ��ʮ�����ƣ�
	
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//��Ƭ�ṹ����(ʮ������)
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	unsigned long    nCardID;			//IC�����׺Ż���ʾ����/���к�

	long    nInductorNo;        //��Ӧͷ���,����ģʽ5ʱ,����������Կ�׵��豸(0~15)
	long    nDutyFlag;          //��/�°��� 1�ϰ�/0��
	long    nTimerType;         //��������,����ģʽ5ʱ,���淿���
	long    nWorkMode;          //����ģʽ(1~4)
	long    nManagerCardNo;     //����Ա����(4byte)

	char    sDealCode1[8];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};


//*******************************************************************************
//*����: TSGSJTable
//*����: 0224 ��ʧ�� 
//*******************************************************************************
struct TSGSJTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
//	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
//	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sCommVer[5];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[5];		//����ͨ������ԭ��ʮ�����ƣ�	
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//���ʹ���
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�
    char    sPassword[17];      //�������루�޸�����Ϊ���ɸ������루6�����¸������루6������ʧΪ��8�ֽ�����,
	char    sDealCode1[8];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};

//*******************************************************************************
//*����: TSBZTable
//*����: 5301 ���ݷ�����(������¼), 1056 �ֳֻ�(�Ʒ�+����)
//*******************************************************************************
struct TSBZTable
{
	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
//	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
//	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sCommVer[5];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[5];		//����ͨ������ԭ��ʮ�����ƣ�	
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//��Ƭ�ṹ����(ʮ������)
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�
	long    nUserInvoice;       //��Ƭʹ����ˮ

	long    nTimes;             //IC��ʹ�ô���������Ǯ������Ϊ�գ�
	char    sWalletCode[3];     //����Ǯ�����룬��ӦǮ����ʶ�����
	long    nInMoney;           //�뿨ֵ���Է�Ϊ��λ
	long    nOutMoney;          //����ֵ���Է�Ϊ��λ
	long    nBatch;             //���κ�

	char    sInductorNo[9];     //��ӦͷID���,����ģʽ5ʱ,����������Կ�׵��豸(0~15)
	long    nDutyFlag;          //��/�°��� 1�ϰ�/0��
	long    nTimerType;         //��������,����ģʽ5ʱ,���淿���
	long    nWorkMode;          //����ģʽ(1~4)
	long    nManagerCardNo;     //����Ա����(4byte)
	char    sTicketEndDate[12]; //��Ʊ��ֹ����(������)

	char    sDealCode1[8];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;
};


//*******************************************************************************
//*����: TSSetlment
//*����: ��������ԭʼƾ֤��
//*******************************************************************************
struct TSSetlment
{
	long    nAuthno;				//�ն˻����������������
	char    sMachineID[11];			//�ն��豸ID�ţ�Ψһʶ��,�������û�����
	char    sOrg_id[37];			//��������֯����
	long    nSettleInvoice;			//�ն˽�����ˮ��
	char    sSettleTime[24];		//����ʱ��
	char    sBeginDealtime[24];		//����Ŀ�ʼ����ʱ��
	long    nBeginInvoice;			//����Ŀ�ʼ������ˮ��
	char    sEndDealtime[24];		//����� ��������ʱ��
	long    nEndInvoice;			//����Ľ���������ˮ��
	long    nDealCount;				//�������ױ���
	long    nDealAmount;			//�������׽��
	long    nCancelCount;			//�������ױ���
	long    nCancelAmount;			//�������׽��
	long    nExcepCount;            //�쳣���ױ���
	long    nExcepACount;           //�쳣���׽��
	long    nOtherCount;			//�������ͽ��ױ���
	char    sOperatorID[5];			//�û�������
	long    nOuterkeeper;			//���ױ�־��0-���׳ɹ� 1-���ʳɹ� 2-���ʳɹ� 3-���ʴ� 4-���ʴ�
	char    sKeepingDate[24];		//��������ʱ��
	long    nBatchNo;				//��������
	long    nSettleType;			//�������ͣ���������Ա���� ����ϵͳ��ʱ�Զ����������ݽ�����ˮ��ϸ����
	char    sDealCode[8];			//�������ʹ����
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
};

//******************************************************************************
//*����: CLock
//*����: WIN32��������
//******************************************************************************
class CLock
{
protected:
	CRITICAL_SECTION   m_Lock;

public:
	CLock()
	{
		InitializeCriticalSection(&m_Lock);
	}

	virtual ~CLock()
	{
		DeleteCriticalSection(&m_Lock);
	}

	void Lock()
	{
		EnterCriticalSection(&m_Lock);
	}

	void Unlock()
	{
		LeaveCriticalSection(&m_Lock);
	}
};

//******************************************************************************
//*����: CTestData
//*����: ���Լ�¼��, ���ڼ�¼��������
//******************************************************************************
class CTestData
{
public:
	CTestData()
	{
		strcpy(m_szBeginTime, "");
		m_nBeginTick = 1 ;
		m_nTotal = 1 ;
		m_nSFCount = 1 ;
		m_nCZCount = 1 ;
		m_nJZCount = 1 ;
		m_nBZCount = 1 ;
		m_nCollect = 1 ;
		m_nSendTick = 1 ;
		m_nSendOK = 1 ;
		m_nSendER = 1 ;
		m_nSendOK1 = 1 ;
		m_nSendER1 = 1 ;
	}

public:
	char    m_szBeginTime[24];		//��ʼʱ��
	DWORD   m_nBeginTick;			//��ʼ��
	long	m_nTotal;				//�ܱ���
	long	m_nSFCount;				//�շѱ���
	long	m_nCZCount;				//��ֵ����
	long	m_nJZCount;				//���ʱ���
	long	m_nBZCount;				//��������

	long    m_nCollect;				//�ռ�ʱ��
	long	m_nSendTick;			//����/����ʱ��

	long    m_nSendOK;				//���ͳɹ�
	long	m_nSendER;				//����ʧ��

	long    m_nSendOK1;				//���ͳɹ�����
	long	m_nSendER1;				//����ʧ�ܱ���

	static CTestData& TestData()
	{
		static CTestData ta;
		return ta;
	}

	void SetDataTime()
	{
		SYSTEMTIME  SysTime;

		GetLocalTime(&SysTime);
		sprintf(m_szBeginTime, "%02d:%02d:%02d ", 
		SysTime.wHour, SysTime.wMinute, SysTime.wSecond);

		m_nBeginTick = GetTickCount();
	}

	void AddTotal(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nTotal, nValue);
	}

	void AddSFCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nSFCount, nValue);
	}

	void AddCZCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nCZCount, nValue);
	}

	void AddJZCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nJZCount, nValue);
	}

	void AddBZCount(long nValue)
	{
		InterlockedExchangeAdd((LONG*)&m_nBZCount, nValue);
	}

	void AddCollect(long nValue)
	{
		InterlockedExchange((LONG*)&m_nCollect, 0);
		InterlockedExchangeAdd((LONG*)&m_nCollect, GetTickCount()-m_nBeginTick);
	}

	void AddSendTick(long nFlag, long nValue)
	{
		InterlockedExchange((LONG*)&m_nSendTick, 0);
		InterlockedExchangeAdd((LONG*)&m_nSendTick, GetTickCount()-m_nBeginTick-m_nCollect);

		InterlockedExchangeAdd((LONG*)&m_nSendOK, nValue);

		if( nFlag )
		{
			InterlockedExchangeAdd((LONG*)&m_nSendOK1, 1);
		}
		else
		{
			InterlockedExchangeAdd((LONG*)&m_nSendER1, 1);
		}
	}

	void Write()
	{
		FILE *fp = NULL ;
		if( (fp=fopen("���ܲ��Լ�¼.log", "a+")) != NULL )
		{
			TCHAR  szLog[1024];
			TCHAR  szText[884];

			SYSTEMTIME  SysTime;
			GetLocalTime(&SysTime);

			sprintf(szText, "[��ʼʱ��:%s, �ķ�ʱ��(����):%06d, �����ܱ���:%05d, ����:%05d, ��ֵ:%05d, ����:%05d, ����:%05d, "
				"�����ܺ�ʱ:%05d,�����ܺ�ʱ:%05d, ����ɹ�����:%05d, ����ʧ�ܱ���:%05d, "
				"����ƽ��ÿ���:%05d, ���浥�ʺķ�(����):%05d, �ۺ�����ƽ��ÿ���:%05d]..\n", 
				m_szBeginTime, GetTickCount()-m_nBeginTick, m_nTotal, m_nSFCount, m_nCZCount, m_nJZCount, m_nBZCount, 
				m_nCollect,	m_nSendTick, m_nSendOK1, m_nSendER1, 
				0, (m_nSendOK)/(m_nSendOK1+m_nSendER1), m_nTotal/((GetTickCount()-m_nBeginTick)/1000));
			
			sprintf(szLog, "%04d-%02d-%02d %02d:%02d:%02d   %s", SysTime.wYear,  SysTime.wMonth, SysTime.wDay,
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond, szText);

			fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
			fclose(fp);
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
// CInterfaceApp
// See Interface.cpp for the implementation of this class
//
class CInterfaceApp : public CWinApp
{

protected:
	bool FillTask(char *pDeviceID, TSSmartTaskPlan *pTaskPlan, unsigned int nRequest, ST_PACK *pPacket);
	bool CheckSmartRegister();
	bool FillSmartDoc(ST_PACK *pPacket);
	bool PacketToSmartDoc(ST_PACK *pPacket);
	void SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count);
	void SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count);

public:

	long ConvertDealData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertIdentifyData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertStateData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertAssisData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertDealData1(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertDealData2(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertGSJData(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);
	long ConvertError(int nType, TSSmartTask *pTask, TSSmartDoc *pDoc, ST_CPACK *pPacket, unsigned char *ucRawData, int nDataLen);

	long ReportResult(TSSmartTask *pTask, long iResult, TSResultData *pData);
	long AnswerResultError(int iFunc, int iMsg, int iResult, char *pszMsg);
	long AnswerSmartDocSuccess(int iFunction, int iMsg, int iResult, char *pszDeviceID);
	long AnswerResult(int iFunction, int iMsg, int iResult, char *pszMsg);

	long SignOutDoc(TSSmartDoc *pDoc);
	long SignInDoc(TSSmartDoc *pDoc);
	long SmartSignOut();
	long SmartSignIn();
	long SmartRegister();

	bool MakeFirstTaskPlan(TSSmartTaskPlan *pTaskPlan, ST_CPACK *pPacket, ST_PACK *pArray, int nRow);
	bool MakeNextTaskPlan(TSSmartTaskPlan *pTaskPlan, ST_CPACK *pPacket, ST_PACK *pArray, int nRow);
	long DownloadBlackList(TSSmartDoc *pDoc, int nType, char *pszFileName);
	long OutputResultBlackCard(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard);
	long SendDeviceStatus(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard);
	long ReadGSCardInfo(int nflag, TSGSJRecord *pRecord);

	TSSmartDoc* CheckDeviceID(char *pDeviceID);
	bool CheckSmartDocValid(TSSmartDoc *pDoc);
	bool CheckSmartDocValid(TSSmartDoc *pDoc, long k, long i);

public:
	CInterfaceApp();
	TSAttachData	m_SAttachData;
	TSBlackCard		m_SBlackCard;
	TSSmartDoc		m_SSmartDoc;
	TSSystemParam	m_SSystemParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CInterfaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
void SetValue(ST_PACKHEAD *head, ST_PACK *pack,int ids,long data);
void SetValue(ST_PACKHEAD *head, ST_PACK *pack,int ids,char *data);
long GetValue(long iValue);
bool IsValidDateTime(unsigned char *pDateTime);
void GetCurDateTime(char *pszDateTime);
void GetCurDateTimeEx(char *pszDateTime);
long ConvertID(char *pHexID);
void WriteLog(const char *format, ...);
void WriteTickLog(const char *format, ...);
void DebugPrint(const char *format, ...);
bool CheckSmartDocValid(TSSmartDoc *pDoc);
void GetCurPath(LPTSTR pszDir);
/////////////////////////////////////////////////////////////////////////////
extern CInterfaceApp theApp;

extern int  iMServerNo;
extern int  iMFunc;

extern int  iServerNo;
extern int  iFunc;
extern long iSmartKey;
extern char sSmartKey[48];
extern TSSmartDoc *gpSmartDoc;
extern long gnDocCount;
extern int  gTick;
extern TSSystemParam  GlobalParam;
extern CLock  OutLock;
extern CLock  InLock;
extern bool bSmartSign;
extern CTestData  TestData;
extern char  szLogPath[256];
extern char  szINIFile[256];
extern int   nReload;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACE_H__BF4A8385_4661_4117_BDA8_7DCBE8C08BAA__INCLUDED_)
