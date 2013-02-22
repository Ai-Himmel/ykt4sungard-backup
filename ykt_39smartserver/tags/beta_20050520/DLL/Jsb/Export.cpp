
#include "stdafx.h"
#include "Jsb.h"
#include "ConfigDlg.h"

long TaskBufferProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long DownloadWhiteCardBefore(long nDatabase, long nflag, TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

static TSResultMsg  ResultMsg[] = 
{
     RET_DATAVALUE_ERROR    ,"���ݳ��Ȳ���ֵ̫�����ڸ�ֵ,",
     RET_RECV_ERROR         ,"�������ݴ�����û�д򿪼�ͨѶ��",
     RET_SEND_ERROR         ,"�������ݴ�����û�д򿪼�ͨѶ��",
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
     RET_CONTINUE           ,"û�е�һ�������, ����ִ��",
     RET_BROADCAST          ,"�е�һ�������, ����Ҫ���豸�ķ�����Ϣ",
     RET_ERRORCALL          ,"���豸����ʧ�ܺ�, �Ե���ҵ��㴦��", 
};

//���ܳ������
static TaskFunction TaskFunc[] = 
{
	50, "�´�������", TaskBufferProc50, TaskProc50, 
	52, "�´�ɾ��������", TaskBufferProc52, TaskProc52,  //ok
	53, "�´��������汾", TaskBufferProc53, TaskProc53,  //ok
	54, "�´��ڼ���", TaskBufferProc54, TaskProc54, 
	55, "�´�ʱ���", TaskBufferProc55, TaskProc55, 
	-1,  "", NULL, NULL 
};

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

//����ת��
int GetBinaryValue(char *pszString)
{
	char  szNew[256];
	int nValue = 0 ;
	int nLen = strlen(pszString);

	memset(szNew, 0, sizeof(szNew));
	for(int i=nLen-1; i>=0; i--)
		szNew[nLen-i-1] = pszString[i];

	for(i=0; i<nLen; i++)
	{
		if( szNew[i] != '0' )
			nValue = nValue + (int)pow(2, nLen-1-i);
	}

	return nValue;
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
	TCHAR  szLog[4096];
	TCHAR  szText[1024];

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
			BroadcastPro(PACKET_CMD_1003, pDoc, szText, lstrlen(szText));
		}
	}
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);

	wsprintf(szFileName, "%s\\%s.log",szTemp, pDoc==NULL?"all":pDoc->m_szDeviceID);

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
	TCHAR	szFileName[MAX_PATH],szTemp[MAX_PATH];
	SYSTEMTIME  SysTime;

	GetLocalTime(&SysTime);
	wsprintf(szTemp,"%s\\%04d%02d%2d",szErrorLogPath,SysTime.wYear,SysTime.wMonth,
		SysTime.wDay);
	CreateDirectory(szTemp,NULL);

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

//		BroadMessage(szLog, lstrlen(szLog));
	}
}

//�����Ƿ�ɹ�
long UnMakeDeviceBufferEx(TSCmdBuffer *pBuffer)
{
	long nResult = UnMakeDeviceBuffer(pBuffer);
	if( nResult == RET_OK )
	{
		int nMark = pBuffer->pBuffer[2];
		if( nMark != 0x00 )
			nResult = nMark; 
		else
			nResult = RET_OK;
	}
	return nResult;
}

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
//*ԭ��: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*����: ��ʼ��ҵ����ģ��, ��װ������/��ʼ������
//*����: 
//*      lpKeyBuffer, ��Ȩ�ַ���(����)
//*      dwFlag, ҵ���ܵı�־
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*====================================================================================
extern "C" long __stdcall ReadSmartDocInfo(TSSmartDoc **pSmartDoc, long *nDocCount)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return RET_NG;
}

//*=================================================================================
//*ԭ��: long ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
//*����: �ͷ��豸������Ϣ
//*����: 
//*      pSmartDoc -- �豸�����ڴ�
//*����: 
//*      =  RET_OK:  �ɹ�
//*      <> RET_OK:  ʧ��
//*====================================================================================
extern "C" long __stdcall ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return RET_NG;
}

//*=================================================================================
//*ԭ��: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*����: ��ʼ��ҵ����ģ��, ��װ������/��ʼ������
//*����: 
//*      pFunction, �����������API��ַ
//*      pSupport,  ���ر�DLL֧�ֵ��������񼰻���
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall InitModuleDLL(TSSmartFunction *pFunction, TSSmartSupport *pSupport)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//֧�����л���
    pSupport->nMacCount = 0 ;
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5301");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0201");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0226");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0228");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0230");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0232");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0234");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0240");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0130");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0140");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0121");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0224");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0236");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1055");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5501");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1056");

	//֧��������
	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "50");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "51");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "52");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "53");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "54");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "55");

	//�������ṩ��API
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
	BroadcastPro = pFunction->fnBroadcastPro;

    TCHAR  szPath[MAX_PATH];

	GetCurPath(szPath);

	if( szPath[lstrlen(szPath)-1] == '\\' )
	{
		wsprintf(szErrorLogPath, "%s�豸��־", szPath);
	}
	else
	{
		wsprintf(szErrorLogPath, "%s\\�豸��־", szPath);
	}

	CreateDirectory(szErrorLogPath, NULL);

	return RET_OK;
}

//*=================================================================================
//*����: ���ҵ����ģ��, �˳�DLLʱ����
//*����: 
//*      ��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall DestoryModuleDLL()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

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
extern "C" long __stdcall CreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

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
extern "C" long __stdcall SmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{ 
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

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

//*=================================================================================
//*����: ҵ�����֧�ֵ���Ϣ
//*����: 
//*      ��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall DLLSupportInfo(TSSmartSupport *pSupport)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    pSupport->nMacCount = 0 ;
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5301");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0201");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0226");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0228");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0230");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0232");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0234");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0240");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0130");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0140");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0121");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0224");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0236");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1055");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5501");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1056");

	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "50");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "51");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "52");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "53");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "54");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "55");

	return RET_OK;
}

//*=================================================================================
//*����: ҵ������ý���(����û��ʹ��)
//*����: 
//*      ��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall DLLSetup()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CConfigDlg  dlg;
	dlg.DoModal();

	return RET_OK;
}

//�´�������
long TaskBufferProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	CString strTemp, strSQL;
	int n = pDocEx->nPortNo;

	//ָ�����´��İ�����, ����´�����������
	if( strcmp(pDocEx->pChildDoc[n]->m_sWhiteList, "") )
	{
		return MakeBuf_DownWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 
			2,(unsigned char*)pDocEx->pChildDoc[n]->m_sWhiteList);
	}

	strcpy(pDocEx->pChildDoc[n]->m_sWhiteList, "");



	return RET_OK;
}

//�´�������
long TaskProc50(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

//�´�ɾ��������
long TaskBufferProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}
	
//�´�ɾ��������
long TaskProc52(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

//�´��������汾
long TaskBufferProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

//�´��������汾
long TaskProc53(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	return RET_OK;
}


//�´��ڼ���
long TaskBufferProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//�´��ڼ���
long TaskProc54(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	return RET_OK;
}

//�´�ʱ���
long TaskBufferProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//�´�ʱ���
long TaskProc55(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	return RET_OK;
}

long DownloadWhiteCardBefore(long nDatabase, long nflag, TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{


	return RET_OK;
}

