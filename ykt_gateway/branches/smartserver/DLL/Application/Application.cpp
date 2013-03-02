// Application.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Application.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "CheckClock.h"
#include "CollectionData.h"
#include "DownloadJZTime.h"
#include "HistoryData.h"
#include "JZHistoryData.h"
#include "SingInServer.h"
#include "UploadCLock.h"
#include "CheckBlackVersion.h"

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//
static TSResultMsg  ResultMsg[] = 
{
     RET_DATAVALUE_ERROR    ,"���ݳ��Ȳ���ֵ̫�����ڸ�ֵ,",
     RET_RECV_ERROR         ,"�������ݴ���·û�д򿪼�ͨѶ��",
     RET_SEND_ERROR         ,"�������ݴ���·û�д򿪼�ͨѶ��",
     RET_RECV_TIMEOUT       ,"�������ݳ�ʱ;",
     RET_ADDR_ERROR         ,"���ص�ַ��ƥ��",
     RET_TERME_NOANSWER     ,"�ն��޷�Ӧ",
     RET_COMMONU_ERROR      ,"���ڴ�/�رմ�",
     RET_DATALENGTH_ERROR   ,"�������ݳ��ȴ���",
     RET_DATACRC_ERROR      ,"����У���",
     RET_PARAMETER_ERROR1   ,"���������",
     RET_RECV_C1_TIMEOUT    ,"C1 Timeout",
     RET_RECV_C2_TIMEOUT    ,"C2 Timeout",
     RET_OK                 ,"�ɹ�",
     RET_NG                 ,"ʧ��/����/û������",
     RET_TIMEOUT            ,"��ʱ",
     RET_TERMINATE          ,"�жϲ���",
     RET_SYSERROR           ,"ϵͳ����",
     RET_DBBUSY             ,"���ݿ���Դ������",
     RET_DBQUERYERROR       ,"���ݿ��ѯ����",
     RET_DBEXECERROR        ,"���ݿ�DDL����",
     RET_NOTSUPPORT         ,"��֧�ֵ�Ӳ������",
     RET_VALIDPACKET        ,"�Ƿ������ݰ�",
     RET_VALIDMARK          ,"MARKֵ��",
     RET_VALIDMACNO         ,"���Ŵ�",
	 RET_TASKWHERE_ERROR    ,"�豸����������", 
     RET_CARD_INVALID       ,"1:�Ƿ���",
     RET_CLOCK_ERROR        ,"2:ʱ�Ӵ�",
     RET_MONEY_FORMAT_ERROR ,"3:Ǯ����ʽ��",
     RET_DATA_FULL          ,"4:������",
     RET_SEQNUM_ERROR       ,"5:��ˮ�Ŵ�",
     RET_PARAMETER_ERROR2   ,"7:���������",
     RET_COMMAND_ERROR      ,"8:�޴�����������޷���ʱʹ��",
     RET_REMARK_ERROR       ,"9:�ظ�����",
     RET_NO_RECORD          ,"10:�޼�¼������",
     RET_AUTHNO_ERROR       ,"11:��Ȩ�Ų���",
     RET_REQU_SIGNIN        ,"13:����ǩ��",
     RET_BLACKLIST_ERROR    ,"14:��������Ч�ڹ���",
     RET_CARD_MONEY_ENOUGH  ,"15:���ڽ���",
     RET_RECORD_NO_COLLECT  ,"17:���м�¼δ�ռ�",
     RET_CARD_DEGREE_ERROR  ,"18:��ʹ�ô�������",
     RET_CARD_EXPECT_ERROR  ,"19:��Ƭ�ѹ���Ч��",
     RET_CARD_MONEY_LARGE   ,"20:��Ƭ���̫��",
     RET_CARD_SEQOVER       ,"22:�ѽ��ʵĽ�����ˮ�ѱ�����(�޷�����)",
     RET_ACCREC_NOTUP       ,"23:���н��˼�¼δ�ϴ�",
     RET_NOT_AUTH           ,"24:�豸δ��Ȩ�޷�ǩ��",
	 RET_ERROR_AUTH         ,"25:��̨������ǩ��",
     RET_CONTINUE           ,"û�е�һ�������, ����ִ��",
     RET_BROADCAST          ,"�е�һ�������, ����Ҫ���豸�ķ�����Ϣ",
     RET_ERRORCALL          ,"���豸����ʧ�ܺ�, �Ե���ҵ��㴦��", 
};


static CApplicationApp::TaskFunction TaskFunc[] = 
{
	1,  "�ռ�����",       TaskBufferProc01, TaskProc01, 
	2,  "У�Բ���",       TaskBufferProc02, TaskProc02, 
	3,  "�ϴ�ʱ��",       TaskBufferProc03, TaskProc03, 
	4,  "У�Ժ�����",     TaskBufferProc04, TaskProc04, 
	5,  "У��ʱ��",       TaskBufferProc05, TaskProc05, 
	6,  "�´�����",       TaskBufferProc06, TaskProc06, 
    8,  "�ϴ�����",       TaskBufferProc08, TaskProc08, 
    9,  "�ռ���ʷ����",   TaskBufferProc09, TaskProc09,  
	10,  "�´���Ȩ����",  TaskBufferProc10, TaskProc10, 
	11,  "�ռ���������",  TaskBufferProc11, TaskProc11, 
	12,  "�ն˻�ǩ��",    TaskBufferProc12, TaskProc12, 
	13,  "������",      TaskBufferProc13, TaskProc13, 
	14,  "�ն˻�����",    TaskBufferProc14, TaskProc14, 
	15,  "�ն˻���������",    TaskBufferProc15, TaskProc15, 
	16,  "�ռ���ʷ��������",  TaskBufferProc16, TaskProc16, 
	17,  "�ռ�������������",  TaskBufferProc17, TaskProc17, 
	18,  "�´���ʱ����ʱ��",  TaskBufferProc18, TaskProc18, 
	19,  "���������´�",  TaskBufferProc19, TaskProc19, 
	20,  "���������ϴ�",  TaskBufferProc20, TaskProc20, 
	21,  "ֹͣ����",      TaskBufferProc21, TaskProc21, 
	70,  "������У��",    TaskBufferProc70, TaskProc70, 
	71,  "����������Ч��", TaskBufferProc71, TaskProc71,	
	72,  "��ʱ�����������汾�´�", TaskBufferProc72, TaskProc72,	
	73,  "��ʱ���°���������", TaskBufferProc73, TaskProc73,	
	74,  "�������ͽ��˴�", TaskBufferProc74, TaskProc74,	
	75,  "�ϴ��豸״̬", TaskBufferProc75, TaskProc75,
	-1,  "", NULL, NULL 
};


void GetCurPath(LPTSTR pszDir)
{
	HANDLE  hHandle = GetCurrentProcess();
	GetModuleFileName(NULL, pszDir, MAX_PATH);
	for(int i=lstrlen(pszDir)-1; i>=0 ; i--)
	{
		if( pszDir[i] == '\\' )
		{
			pszDir[i] = 0;
			break;
		}
	}
}

//*=================================================================================
//*ԭ��: void GetResultMessage(long nRet, char *pszString)
//*����: �õ�����ֵ����Ϣ
//*����: ��
//*����: ��
//*˵��: ȫ�ֺ���. (����˳�����,Ч�ʷǳ���. �Ժ���ʱ�����Ż�.)
//*=================================================================================
void GetResultMessage(long nRet, char *pszString)
{
	for(long i=0; i< sizeof(ResultMsg)/sizeof(TSResultMsg); i++)
	{
		if( ResultMsg[i].nResult == nRet )
		{
			strcpy(pszString, ResultMsg[i].pszMessage);
			return;
		}
	}

	strcpy(pszString, "δ֪�Ĵ�����Ϣ����!");
}

//*=============================================================================================
//*ԭ��: void ReportLog(TSSmartDocEx *pDocEx, const char *format, ...)
//*����: ��־��Ϣ����
//*����: 
//*      pDoc  -- �豸��Ϣ
//*      pTask -- �豸����
//*      
//*����: 
//*      ��
//*=============================================================================================
void ReportLog(TSSmartDoc *pDoc, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString)
{
	TCHAR	szFileName[MAX_PATH],szTemp[MAX_PATH];
	SYSTEMTIME  SysTime;
	TCHAR   szLog[4096];
	TCHAR   szText[1024];

	GetLocalTime(&SysTime);

	if( nRet == RET_OK )
	{
		wsprintf(szLog, "%02d:%02d:%02d [��Ȩ��<%d> ������<%s> �˿ں�<%s> ����ƻ�<%d> ����<%s>] [ִ�н��(%d):�ɹ�!] %s\n", 
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			pDoc==NULL?0:pDoc->m_nAuthID, pDoc==NULL?"":pDoc->m_szAddr, pDoc==NULL?"":pDoc->m_szPort, 
			pTask==NULL?0:pTask->nTaskPlanID, 
			pszTask, nRet, pszString);
	}
	else
	{
		TCHAR  szTemp[256];

		memset(szTemp, 0, sizeof(szTemp));
		GetResultMessage(nRet, szTemp);

		wsprintf(szLog, "%02d:%02d:%02d [��Ȩ��<%d> ������<%s> �˿ں�<%s> ����ƻ�<%d> ����<%s>] [ִ�н��(%d):ʧ��! ������Ϣ:%s] %s\n", 
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
			pDoc==NULL?0:pDoc->m_nAuthID, pDoc==NULL?"":pDoc->m_szAddr, 
			pDoc==NULL?"":pDoc->m_szPort, pTask==NULL?0:pTask->nTaskPlanID, 
			pszTask, nRet, szTemp, pszString);

		if( pDoc && pTask )
		{
			char szTmp[32];
			GetCurDateTime(szTmp);

			wsprintf(szText, "%d&%s&%s&%d&%s", pDoc->m_nAuthID, pTask->szTaskCode,
				szTmp, nRet, pszString);
			//BroadcastPro(PACKET_CMD_1003, pDoc, szText, lstrlen(szText));
		}
	}
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);

	wsprintf(szFileName, "%s\\%s.log", 
		szTemp, pDoc==NULL?"all":pDoc->m_szDeviceID);

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);
	}
}

void ReportLog(TSSmartDocEx *pDocEx, TSSmartTask *pTask, long nRet, char *pszTask, char *pszString)
{
	ReportLog(pDocEx->pChildDoc[pDocEx->nPortNo], pTask, nRet, pszTask, pszString);
}

void ReportLog(long nRet, char *pszTask, char *pszString)
{
	TCHAR	szFileName[MAX_PATH];
	SYSTEMTIME  SysTime;
	TCHAR   szTemp[MAX_PATH];
	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);
	/*wsprintf(szFileName, "%s\\%s_%04d%02d%02d.log", 
		szErrorLogPath, "ERROR", 
		SysTime.wYear, SysTime.wMonth, SysTime.wDay);*/
	wsprintf(szFileName, "%s\\%s.log", 
		szTemp, "ERROR");

	FILE *fp = NULL ;
	if( (fp=fopen(szFileName, "a+")) != NULL )
	{
		TCHAR  szLog[4096];
		if( nRet == RET_OK )
		{
			wsprintf(szLog, "%02d:%02d:%02d [����<%s>] [ִ�н��(%d):�ɹ�!] %s\n", 
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
				pszTask, nRet, pszString);
		}
		else
		{
			TCHAR  szTemp[256];

			memset(szTemp, 0, sizeof(szTemp));
			GetResultMessage(nRet, szTemp);

			wsprintf(szLog, "%02d:%02d:%02d [����<%s>] [ִ�н��(%d):ʧ��! ������Ϣ:%s] %s\n", 
				SysTime.wHour, SysTime.wMinute, SysTime.wSecond,
				pszTask, nRet, szTemp, pszString);
		}

		fwrite(szLog, lstrlen(szLog), sizeof(TCHAR), fp);
		fclose(fp);

		//BroadMessage(szLog, lstrlen(szLog));
	}
}


/////////////////////////////////////////////////////////////////////////////
// CApplicationApp
BEGIN_MESSAGE_MAP(CApplicationApp, CWinApp)
	//{{AFX_MSG_MAP(CApplicationApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApplicationApp construction
CApplicationApp::CApplicationApp()
{
	TCHAR szPath[MAX_PATH];

	GetCurPath(szPath);

	if( szPath[lstrlen(szPath)-1] == '\\' )
	{
		wsprintf(szErrorLogPath, "%�豸��־", szPath);
		wsprintf(szDataLogPath,  "%s�ն�����", szPath);
		wsprintf(szTempPath,  "%stemp", szPath);
	}
	else
	{
		wsprintf(szErrorLogPath, "%s\\�豸��־", szPath);
		wsprintf(szDataLogPath,  "%s\\�ն�����", szPath);
		wsprintf(szTempPath,  "%s\\temp", szPath);
	}

	CreateDirectory(szErrorLogPath, NULL);
	CreateDirectory(szTempPath, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CApplicationApp object
CApplicationApp theApp;

//*----------------------------------------------------------------------------
//*����: long CAppLayerApp::ImportFunc(TSSmartFunction *pFunction)
//*����: ��ʼ��ȫ�ֺ���
//*����: pFunction -- ����ָ������
//*����: ��ϵͳ����ֵ˵��
//*˵��: ZhangWei. 2004.03
//*----------------------------------------------------------------------------
long CApplicationApp::ImportFunc(TSSmartFunction *pFunction)
{
	if( pFunction == NULL )
		return RET_NG;

	GetDBHandle = pFunction->fnGetDBHandle;
	FreeDBHandle = pFunction->fnFreeDBHandle;
	ExecuteQuery = pFunction->fnExecuteQuery;
	CloseRecHandle = pFunction->fnCloseRecHandle;
	IsOpen = pFunction->fnIsOpen;
	IsBOF = pFunction->fnIsBOF;
	IsEOF = pFunction->fnIsEOF;
	MoveFirst = pFunction->fnMoveFirst;
	MoveLast = pFunction->fnMoveLast;
	MoveNext = pFunction->fnMoveNext;
	MovePrev = pFunction->fnMovePrev;
	GetFieldCount = pFunction->fnGetFieldCount;
	GetRecordCount = pFunction->fnGetRecordCount;
	GetFieldName = pFunction->fnGetFieldName;
	GetFieldStringValue = pFunction->fnGetFieldStringValue;
	GetFieldStringValueEx = pFunction->fnGetFieldStringValueEx;
	GetFieldLongValue = pFunction->fnGetFieldLongValue;
	GetFieldLongValueEx = pFunction->fnGetFieldLongValueEx;
	GetFieldFloatValue = pFunction->fnGetFieldFloatValue;
	GetFieldFloatValueEx = pFunction->fnGetFieldFloatValueEx;
	GetFieldDoubleValue = pFunction->fnGetFieldDoubleValue;
	GetFieldDoubleValueEx = pFunction->fnGetFieldDoubleValueEx;
	Locate = pFunction->fnLocate;
	ExecuteSQL = pFunction->fnExecuteSQL;
	SendRequest = pFunction->fnSendRequest;
	BroadData = pFunction->fnBroadData;
	AddNewSmartDoc = pFunction->fnAddNewSmartDoc;
	DelSmartDoc = pFunction->fnDelSmartDoc;
	BroadMessage = pFunction->fnBroadMessage;
	BroadcastPro = pFunction->fnBroadcastPro;
	SendDataEx = pFunction->fnSendData;
	RecvDataEx = pFunction->fnRecvData;
	OutputRealData = pFunction->fnOutputRealData;
	GetParameter = pFunction->fnGetParam;
	ReportTaskResult = pFunction->fnReportTaskResult;
	ReadCardGSInfo =  pFunction->fnReadCardGSInfo;

	OutputBlackCard =  pFunction->fnOutputBlackCard;
	DownloadBlackCard =  pFunction->fnDownloadBlackCard;

	SignIn = pFunction->fnSignIn;
	SignOut = pFunction->fnSignOut;

	return RET_OK;
}

//*----------------------------------------------------------------------------
//*����: long CApplicationApp::ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
//*����: ����豸�����ڴ�
//*����: pSmartDoc -- �豸��Ϣ����
//*����: ��ϵͳ����ֵ˵��
//*˵��: ZhangWei. 2004.03
//*----------------------------------------------------------------------------
long CApplicationApp::ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
{
	try
	{
		if( pSmartDoc != NULL )
			delete [] pSmartDoc;
	}
	catch(...)
	{
		return RET_SYSERROR;
	}
	return RET_OK;
}

//*----------------------------------------------------------------------------
//*����: long CAppLayerApp::ReadSmartDoc(TSSmartDoc **pSmartDoc, long *nDocCount)
//*����: �����ڴ��е��豸������Ϣ
//*����: pSmartDoc -- �豸��Ϣ����
//*      nDocCount -- ��¼��
//*����: ��ϵͳ����ֵ˵��
//*˵��: ZhangWei. 2004.03
//*----------------------------------------------------------------------------
long CApplicationApp::ReadSmartDoc(TSSmartDoc **pSmartDoc, long *nDocCount)
{
	return RET_OK;
}

//*=================================================================================
//*����: ������һ������ʱ����, ��ʱ����������������
//*����: 
//*       pSmartDoc:     �ն���Ϣ
//*       pDocArray:     �ն˼�������
//*       nArrayLength:  ��������
//*       pSmartBuffer:  ���ص���Ϣ
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
long CApplicationApp::CreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long nRet = RET_NG ;
	long i=0; 

	while( TaskFunc[i].nTaskID > 0 )
	{
		if( TaskFunc[i].nTaskID == atoi(pTask->szTaskCode) )
		{
			nRet = TaskFunc[i].fnTaskBufferProc(pDocEx, pTask, pBuffer);
			break;
		}
		i++;
	}
	return nRet;
}

//*=================================================================================
//*����: ���ն˽������ݺ�Ĵ���(ʵ�ֽ��, ����SQL��)
//*����: 
//*      �������˵��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
long CApplicationApp::SmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long nRet = RET_NG ;
	long i=0; 

 	while( TaskFunc[i].nTaskID > 0 )
	{		
		if( TaskFunc[i].nTaskID == atoi(pTask->szTaskCode) )
		{			
			nRet = TaskFunc[i].fnTaskProc(pDocEx, pTask, pBuffer);
			break;
		}
		i++;
	}
	return nRet;
}


//�ռ�����
long TaskBufferProc01(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;

	InterlockedIncrement((LONG*)&gTryCount);
	if( gTryCount <= 1 )
	{
		gTick = GetTickCount() ;
	}
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc02(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}


long TaskBufferProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CUploadClock  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}

long TaskBufferProc04(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc05(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckClock  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc06(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc07(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc08(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc09(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CHistoryData Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc10(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc11(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc12(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CSingInServer  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc13(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc14(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc15(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc16(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CJZHistoryData  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc17(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc18(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CDownloadJZTime  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}
	
long TaskBufferProc19(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc20(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskBufferProc21(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}


long TaskBufferProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  Data;
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}

long TaskBufferProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//��ʱ�����������汾�´�
long TaskBufferProc72(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//��ʱ���������´�����
long TaskBufferProc73(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//����
long TaskBufferProc74(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}



//�ϴ��豸״̬
long TaskBufferProc75(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;	
	InterlockedIncrement((LONG*)&gTryCount);

	if( gTryCount <= 1 )
	{
		gTick = GetTickCount() ;
	}
	return Data.CreateBuffer(pDocEx, pTask, pBuffer);
}

//�ռ����ݴ���
long TaskProc01(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
//У�Բ���
long TaskProc02(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//�ϴ�ʱ��	
long TaskProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CUploadClock  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}

//У�Ժ�����	
long TaskProc04(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//У��ʱ��	
long TaskProc05(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckClock  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}

//�´�����	
long TaskProc06(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//�ϴ�����	
long TaskProc07(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc08(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//��ʷ�����ռ�	
long TaskProc09(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CHistoryData   History;
	return History.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc10(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc11(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

long TaskProc12(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CSingInServer  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc13(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc14(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc15(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc16(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CJZHistoryData Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc17(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc18(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CDownloadJZTime  Data;
	return Data.ProcessRequest(pDocEx, pTask, pBuffer);
}
	
long TaskProc19(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc20(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}
	
long TaskProc21(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_NG;
}

//�������´�
long TaskProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  Check;
	return Check.ProcessData(pDocEx,pTask,pBuffer);
}

//������У��
long TaskProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  Check;
	return Check.ProcessCheck(pDocEx,pTask,pBuffer);
}

//��ʱ�����������汾�´�
long TaskProc72(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  DataVer;
	return DataVer.ProcessDataJSB(pDocEx,pTask,pBuffer);
}

//��ʱ������������
long TaskProc73(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  DataTask;
	return DataTask.ProcessDataJSBTask(pDocEx,pTask,pBuffer);
}

//����
long TaskProc74(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCheckBlackVersion  DataVer;	
	return DataVer.ProcessDataTick(pDocEx,pTask,pBuffer);
}

//�ϴ��豸״̬
long TaskProc75(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CCollectionData  Data;
	return Data.ProcessStatusRequest(pDocEx, pTask, pBuffer);
}

BOOL CApplicationApp::InitInstance() 
{
	InitializeCriticalSection(&Lock);
	InitializeCriticalSection(&DebugLock);
	
	return CWinApp::InitInstance();
}

int CApplicationApp::ExitInstance() 
{
	DeleteCriticalSection(&Lock);
	DeleteCriticalSection(&DebugLock);

	return CWinApp::ExitInstance();
}

