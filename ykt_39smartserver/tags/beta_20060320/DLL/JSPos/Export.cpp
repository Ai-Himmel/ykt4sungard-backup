#include "stdafx.h"
#include "JSPos.h"
#include "ConfigDlg.h"

long TaskBufferProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskBufferProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskProc70(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskBufferProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//del by lina 20050314 long TaskProc71(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);



//add by lina 20050309  �ϴ�ʱ��
long TaskBufferProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
/////////////

//add by lina 20050316 ����ÿ���ۼ����ѽ������
long TaskBufferProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by lina 20050316 ��ʼ��LPORT�˿ڲ���
long TaskBufferProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by lina 20050316 �����ն˹���Ա����
long TaskBufferProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by lina 20050316 ��ȡ�˿ڲ���
long TaskBufferProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//add by dengjun 20050830 ��ʱ���㲥�´�������
long TaskBufferProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 ��ʱ���´�/ɾ��������
long TaskBufferProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 �ϴ���ʱ���汾
long TaskBufferProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 �´���ʱ���汾
long TaskBufferProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 �ϴ���ʱ���ڼ���
long TaskBufferProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 �´���ʱ���ڼ���
long TaskBufferProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 �ϴ���ʱ��ʱ���
long TaskBufferProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050830 �´���ʱ��ʱ���
long TaskBufferProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050831 �´���ʱ��ʱ���
long TaskBufferProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050831 �´���ʱ��������
long TaskBufferProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050901 �ɼ���ʱ����ʷ��ˮ
long TaskBufferProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050901 ��ʱ��������
long TaskBufferProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
//add by dengjun 20050926 �����豸�����������豸
long TaskBufferProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

long TaskBufferProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskBufferProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
long TaskProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);


//���ܳ������
static TaskFunction TaskFunc[] = 
{
	3,  "�ϴ�ʱ��",     TaskBufferProc03, TaskProc03,
	60, "�´���������", TaskBufferProc60, TaskProc60, 
	61, "�ϴ���������", TaskBufferProc61, TaskProc61, 
	62, "���ò�������", TaskBufferProc62, TaskProc62, 
	63, "��ȡ��������", TaskBufferProc63, TaskProc63, 	
	80, "����������",		 TaskBufferProc80, TaskProc80, 
	81, "У��������",		 TaskBufferProc81, TaskProc81, 
	101, "У��ʱ��",		 TaskBufferProc101, TaskProc101, 
	102, "�´���������޶�", TaskBufferProc102, TaskProc102, 
	103, "������",		 TaskBufferProc103, TaskProc103, 
	104, "�������ѱ�ż��汾",TaskBufferProc104, TaskProc104, 
	105, "�������ѿ�ݱ��", TaskBufferProc105, TaskProc105, 
	106, "���û���ID",		 TaskBufferProc106, TaskProc106, 
	107, "��������ʱ��β���", TaskBufferProc107, TaskProc107, 
	108, "����ע���",		 TaskBufferProc108, TaskProc108, 

	110, "����״̬����",	 TaskBufferProc110, TaskProc110, 
	111, "����״̬����",	 TaskBufferProc111, TaskProc111, 
	112, "�ӷ������״̬�ָ���������״̬", TaskBufferProc112, TaskProc112, 

	120, "�´����ѱ���",	 TaskBufferProc120, TaskProc120, 
	130, "����ǩ������",     TaskBufferProc130, TaskProc130, 
	131, "����ÿ���ۼ������޶�",TaskBufferProc131, TaskProc131,
	132, "��ʼ��LPORT�˿ڲ���",TaskBufferProc132, TaskProc132,
	133, "�����ն˹���Ա����",TaskBufferProc133, TaskProc133,
	134, "��ȡ�˿ڲ���",	TaskBufferProc134, TaskProc134,
	136, "��ʱ���´�/ɾ��������",	TaskBufferProc136, TaskProc136,	
	137, "�ϴ���ʱ���汾",			TaskBufferProc137, TaskProc137,	
	138, "�´���ʱ���汾",			TaskBufferProc138, TaskProc138,	
	139, "�ϴ���ʱ���ڼ���",		TaskBufferProc139, TaskProc139,	
	140, "�´���ʱ���ڼ���",		TaskBufferProc140, TaskProc140,	
	141, "�ϴ���ʱ��ʱ���",		TaskBufferProc141, TaskProc141,	
	142, "�´���ʱ��ʱ���",		TaskBufferProc142, TaskProc142,	
	143, "�Ž������ؿ���",			TaskBufferProc143, TaskProc143,	
	144, "�´���ʱ��������",		TaskBufferProc144, TaskProc144,	
	145, "�ɼ���ʱ����ʷ��ˮ",		TaskBufferProc145, TaskProc145,	
	146, "��ʱ��������",			TaskBufferProc146, TaskProc146,	
	147, "�����豸�����������豸",	TaskBufferProc147, TaskProc147,	
	148, "�´���������",			TaskBufferProc148, TaskProc148,	
	149, "�ϴ��������汾",			TaskBufferProc149, TaskProc149,	
	-1,  "", NULL, NULL 
};

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

	//֧��������
	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "03");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "60");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "61");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "62");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "63");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "80");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "81");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "100");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "101");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "102");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "103");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "104");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "105");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "106");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "107");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "108");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "110");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "111");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "112");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "120");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "130");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "131");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "132");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "133");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "134");
//	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "135"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "136"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "137"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "138"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "139"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "140"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "141"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "142"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "143"); //add by dengjun 20050830
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "144"); //add by dengjun 20050831
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "145"); //add by dengjun 20050831
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "146"); //add by dengjun 20050831
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "147"); //add by dengjun 20050926
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "148"); //add by dengjun 20050926
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "149"); //add by dengjun 20051115

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
	BroadMessage = pFunction->fnBroadMessage;
	BroadcastPro = pFunction->fnBroadcastPro;

	SendDataEx = pFunction->fnSendData;
	RecvDataEx = pFunction->fnRecvData;
	OutputRealData = pFunction->fnOutputRealData;
	GetParameter = pFunction->fnGetParam;
	ReportTaskResult = pFunction->fnReportTaskResult;

    TCHAR  szPath[MAX_PATH];
	GetCurPath(szPath);

	if( szPath[lstrlen(szPath)-1] == '\\' )
	{
		wsprintf(szDataLogPath,  "%s�ն�����", szPath);
		wsprintf(szOperPath,  "%s�豸��־", szPath);
	}
	else
	{
		wsprintf(szDataLogPath,  "%s\\�ն�����", szPath);
		wsprintf(szOperPath,  "%s\\�豸��־", szPath);
	}

	//CreateDirectory(szDataLogPath, NULL);
	CreateDirectory(szOperPath, NULL);

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
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "03");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "60");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "61");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "62");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "63");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "80");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "81");

	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "100");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "101");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "102");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "103");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "104");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "105");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "106");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "107");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "108");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "110");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "111");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "112");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "120");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "130");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "131");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "132");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "133");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "134");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "136"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "137"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "138"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "139"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "140"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "141"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "142"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "143"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "144"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "145"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "146"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "147"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "148"); //add by dengjun
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "149"); //add by dengjun

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

long GetMemoNumber(int nIndex, char *pszText)
{
	char  szText[256];
	int   k = 0;

	memset(szText, 0, sizeof(szText));
	for(int i=0; i<(int)strlen(pszText); i++)
	{
		if( szText[i] == ' ' )
		{
			if( k++ == nIndex ) 
				break;
		}
		else
		{
			szText[i] = pszText[i];
		}
	}
	return atoi(szText);
}

long GetMemoString(int nIndex, char *pszText, char *pszResult)
{
	char  szText[256];
	int   k = 0;

	memset(szText, 0, sizeof(szText));
	for(int i=0; i<(int)strlen(pszText); i++)
	{
		if( szText[i] == ' ' )
		{
			if( k++ == nIndex ) 
			{
				strcpy(pszResult,  szText);
				break;
			}
		}
	}
	return atoi(szText);
}


long UnPassword(char *pszPass, char cFlag, unsigned char *pResult)
{
	typedef void (__stdcall *lpfnUserDes)(unsigned char *pIn, unsigned char *pOut, char cFlag);
    TCHAR  szPath[MAX_PATH];
	TCHAR  szFileName[MAX_PATH];
	lpfnUserDes  UserDes = NULL ;

	GetCurPath(szPath);
	wsprintf(szFileName, "%s\\smart_userdes.dll", szPath);

	HMODULE hInstance = LoadLibrary(szFileName);
	if( hInstance == NULL )
	{
		return RET_SYSERROR;
	}

	UserDes = (lpfnUserDes)GetProcAddress(hInstance, "Smart_UserDes");
	if( UserDes == NULL )
	{
		FreeLibrary(hInstance);
		return RET_SYSERROR;
	}

	unsigned char szInBuffer[16];

	ZeroMemory(szInBuffer, sizeof(szInBuffer));
	ZeroMemory(pResult, 16);

	if( cFlag == 'e' || cFlag == 'E' )
	{
		for(int i=0; i< (int)strlen(pszPass); i++)
			szInBuffer[i] = pszPass[i];
	    UserDes(szInBuffer, pResult, cFlag);
	}
	else
	{
		SVC_DSP_2_HEX((unsigned char*)pszPass, szInBuffer, 8);
	    UserDes(szInBuffer, pResult, cFlag);
	}

	FreeLibrary(hInstance);
	return RET_OK;
}

//�����ʶ��ձ�
int GetBaudRatecode(int nBaud)
{
	int nResult = 0 ;
	switch(nBaud)
	{
	case 19200: nResult=0 ; break;
    case 9600: nResult=1 ; break;
    case 600: nResult=2 ; break;
    case 1200: nResult=3 ; break;
    case 2400: nResult=4 ; break;
    case 4800: nResult=5 ; break;
    case 14400: nResult=6 ; break;
    case 57600: nResult=7 ; break;
	default:break;
	}
	return nResult;
}

int GetBaudRatecodeEx(int nBaud)
{
	int nResult = 19200 ;
	switch(nBaud)
	{
	case 0: nResult=19200 ; break;
    case 1: nResult=9600 ; break;
    case 2: nResult=600 ; break;
    case 3: nResult=1200; break;
    case 4: nResult=24004 ; break;
    case 5: nResult=48005 ; break;
    case 6: nResult=144006 ; break;
    case 7: nResult=57600 ; break;
	default:break;
	}
	return nResult;
}


unsigned char GetInt(unsigned char *pszString, int Len)
{
   char  sBuffer[8];

   memset(sBuffer, 0, sizeof(sBuffer));
   for(int i=0; i<Len&&i<8; i++)
   {
	   sBuffer[i] = pszString[i];
   }

   return (unsigned char)atoi(sBuffer);
}


void GetNowTime(char *pszDateTime, bool bBool)
{
	SYSTEMTIME   SysTime;

	ZeroMemory(&SysTime, sizeof(SysTime));
	GetLocalTime(&SysTime);

	if( !bBool )
	{
		sprintf(pszDateTime, "%02d%02d%02d%02d%02d%02d",
			SysTime.wYear, SysTime.wMonth, SysTime.wDay,
			SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
	}
	else
	{
		sprintf(pszDateTime, "%02d%02d%02d", 
			SysTime.wYear, SysTime.wMonth, SysTime.wDay);
	}

	return ;
}

long OpenQuery(long nDatabase, CString strSQL)
{
	long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		return RET_DBQUERYERROR;
	}

	if( MoveFirst(nRec) != RET_OK )
	{
		CloseRecHandle(nRec);
		return RET_DBQUERYERROR;
	}

	return nRec;
}


CString GetSmartCardSQL(CString strDate1, CString strDate2)
{
	CString strSQL;


	return strSQL;
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

char sBlockVersion[32];   //�����������°汾
char sBlockExpire[32];    //��������Ч��
int  nBlackExpire;
int  nBlackCount = 0 ;

long GetParam(long nDatabase)
{
	CString strSQL;

	memset(sBlockVersion, 0, sizeof(sBlockVersion));
	memset(sBlockExpire, 0, sizeof(sBlockExpire));

	nBlackExpire = 24 ;

	//�����������°汾
	strSQL = "select smt_content from smart_setup where smt_systemid = 93 and smt_param='StdBlackVer' ";
	long nRec = OpenQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		GetNowTime(sBlockVersion, false);
	}
	else
	{
		if( GetFieldStringValueEx(nRec, "smt_content", sBlockVersion) != RET_OK )
			GetNowTime(sBlockVersion, false);
		CloseRecHandle(nRec);
	}

	//��������Ч��
	strSQL = "select smt_content from smart_setup where smt_systemid = 85 and smt_param='Tx_Black_Yx' ";
	nRec = OpenQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		strcpy(sBlockExpire, "");
	}
	else
	{
		if( GetFieldStringValueEx(nRec, "smt_content", sBlockExpire) != RET_OK )
			strcpy(sBlockExpire, "");
		CloseRecHandle(nRec);
	}

	if( strlen(sBlockExpire) > 0 )
	{
		char   sDateTime[24];
		char   sTemp[32];

		memset(sTemp, 0, sizeof(sTemp));

		//��������Ч��Ϊÿ��Ĺ̶�ʱ��
		if( strlen(sBlockExpire) == 6 )
		{
			GetNowTime(sDateTime, true);

			nBlackExpire = -1;
			sprintf(sTemp, "%s%s", sDateTime, sBlockExpire);
			strcpy(sBlockExpire, sTemp);
		}
		//��������Ч��Ϊһ���̶�������ʱ��
		else if( strlen(sBlockExpire) >= 12 && strlen(sBlockExpire) <= 14 )
		{
			nBlackExpire = -1;

			if( strlen(sBlockExpire) == 14 )
			{
				strncpy(sTemp, &sBlockExpire[2], 12);
				strcpy(sBlockExpire, sTemp);
			}
		}
		//��������Ч����Сʱ����
		else
		{
			try
			{
				nBlackExpire = atoi(sBlockExpire);
			}
			catch(...)
			{
				nBlackExpire = 99999 ;
			}
		}
	}
	else
	{
		nBlackExpire = -1;
		strcpy(sBlockExpire, "990101010101");
	}

	return RET_OK;
}

//���غ�����
long DownCardID(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int n, long nRec, char* strLastVer, long nCardID)
{
	const int MaxBlacknum = 1;
	const int Maxwhitenum = 1;

	long nLastList;
	long nBlacknum=0, nWhitenum=0;
	char strFirstVer[32];
	char strBlackListVer[32];
	char strEndCode[64];

	unsigned char szWhiteBuffer[256];
	unsigned char szBlackBuffer[256];

	strcpy(strLastVer, "");

	if( MoveFirst(nRec) != RET_OK )
		return RET_SYSERROR;

    nLastList = nCardID;
	GetFieldStringValueEx(nRec, "smt_blacklistver", strFirstVer);

	while( IsEOF(nRec) != RET_OK )
	{
		nWhitenum = 0 ;
		nBlacknum = 0 ;

		GetFieldLongValueEx(nRec, "smt_cardID", &nCardID);
		GetFieldStringValueEx(nRec, "smt_blacklistver", strBlackListVer);
		GetFieldStringValueEx(nRec, "smt_EndCode", strEndCode);

        //����ϴ�У�Ժ�����ʧ�ܣ������ж����ͬ�����汾�ţ�����һ��У��ʧ�ܵ�������ʼ��
		if( nCardID < nLastList && !strcmp(strBlackListVer, strFirstVer) )
		{
			printf("Card ID is Error!\n");
			MoveNext(nRec);
			continue;
		}

		//������
		if( strEndCode[0] == '0' )
		{
			szWhiteBuffer[nWhitenum*3] = (nCardID/256/256)%256;
			szWhiteBuffer[nWhitenum*3+1] = (nCardID/256)%256;
			szWhiteBuffer[nWhitenum*3+2] = nCardID%256;
			nWhitenum++;
		}
		else
		{
			szBlackBuffer[nBlacknum*3] = (nCardID/256/256)%256;
			szBlackBuffer[nBlacknum*3+1] = (nCardID/256)%256;
			szBlackBuffer[nBlacknum*3+2] = nCardID%256;
			nBlacknum++;
		}

		MoveNext(nRec);

		//ÿ���´���ɾ�����60������
		if( nBlacknum == MaxBlacknum || nWhitenum == Maxwhitenum || 
			IsEOF(nRec) != RET_OK )
		{
			//�´�������
			if( nBlacknum )
			{
				nCardID = szBlackBuffer[0]*256*256+szBlackBuffer[1]*256+szBlackBuffer[2];
				bool bResult = false;

				for(long i=0; i<3; i++)
				{
					MakeBuf_DownBlackCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBlackBuffer);
					pBuffer->nTimeOut1 = 1000;
					pBuffer->nTimeOut2 = 1000;
					if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
					{
						long iResult = UnMakeDeviceBufferEx(pBuffer);
						if( iResult == RET_OK )
						{
							printf("Blacknum download is ok..............\n");
							bResult = true;
							break;
						}
						else
						{
							printf("Blacknum download is error...mark=%d...card:%d..\n", iResult, nCardID);
						}
					}
				}

				if( !bResult )
				{
					CloseRecHandle(nRec);
					return RET_SYSERROR;
				}
			}

			//ɾ��������
			if( nWhitenum )
			{
				printf("Loop..next ..nWhitenum......\n");

				nCardID = szWhiteBuffer[0]*256*256+szWhiteBuffer[1]*256+szWhiteBuffer[2];
				GetFieldStringValueEx(nRec, "smt_blacklistver", strBlackListVer);

	            //������»����Ͳ��ò��������
				if( strcmp(strBlackListVer, "000000000000") )
				{
					bool bResult = false;

					for(long i=0; i<3; i++)
					{
						MakeBuf_DelOneBlackCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szWhiteBuffer);
						pBuffer->nTimeOut1 = 1000;
						pBuffer->nTimeOut2 = 1000;
						if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
						{
							long iResult = UnMakeDeviceBufferEx(pBuffer);
							if( iResult == RET_OK )
							{
								printf("nWhitenum download is ok..............\n");
								bResult = true;
								break;
							}
							else
							{
								printf("Blacknum download is error...mark=%d...card:%d..\n", iResult, nCardID);
							}
						}
					}

					if( !bResult )
					{
						CloseRecHandle(nRec);
						return RET_SYSERROR;
					}
				}
			}
		}

		GetFieldStringValueEx(nRec, "smt_blacklistver", strLastVer);
	}

	return RET_OK;
}

//У�Ժ���������Ч��
long CheckBlackExpire(long nDatabase, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, long n)
{
	char  sNow[24];
	char  sTemp[32];
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	char *pExpire = pDoc->m_sBlackExpire;

	GetNowTime(sNow, false);

	if( (strcmp(pExpire, "02070100") < 0 || strcmp(pExpire, sNow) > 0)
		&& strcmp(pExpire, "") )
	{
		return RET_OK;
	}

	memset(sTemp, 0, sizeof(sTemp));

	if( nBlackExpire == -1 )
	{
		strcpy(sTemp, sBlockExpire);
	}
	else
	{
		 char sDateTime[24];
	     SYSTEMTIME   SysTime;

	     ZeroMemory(&SysTime, sizeof(SysTime));
	     GetLocalTime(&SysTime);

	     sprintf(sDateTime, "%02d%02d%02d%02d%02d%02d",
		     SysTime.wYear, SysTime.wMonth, SysTime.wDay+nBlackExpire/24,
			 SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
		 sprintf(sTemp, "%s", sDateTime);
	}

	char sTmp[3];
	char sBuffer[32];

	memset(sBuffer, 0, sizeof(sBuffer));

	for(int i=0; i<6; i++)
	{
		memset(sTmp, 0, sizeof(sTmp));

		sTmp[0] = sTemp[i*2];
		sTmp[1] = sTemp[i*2+1]; 
		sBuffer[i] = atoi(sTmp);
	}

	bool bResult = false;

	for(i=0; i<3; i++)
	{
		MakeBuf_SetBlackUsefulLife(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, (unsigned char*)sBuffer);
		if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBufferEx(pBuffer) == RET_OK )
			{
				bResult = true;
				break;
			}
		}
	}

	if( !bResult )
	{
		return RET_SYSERROR;
	}

	//�޸����ݿ��еĺ�������Ч��
	CString strSQL;
	strSQL.Format("update smart_commrec set smt_blackexpire='%s' where smt_authno=%d ", sTemp, pDoc->m_nAuthID);
	ExecuteSQL(nDatabase, strSQL.GetBuffer(0));

	strcpy(pExpire, sTemp);

	return RET_OK;
}

//�´���������
long TaskBufferProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	BYTE Buffer[128],*pt=NULL;
	int	 nTmp=0;
	TSSystemParam *pHead;
	int  n = pDocEx->nPortNo;

	memset(Buffer, 0x00, sizeof Buffer );
	pHead = (TSSystemParam*)pTask->pData;
	nTmp=pHead->nParameter4;//����
	pt=(BYTE*)&nTmp;
	Buffer[0]=*(pt+2);
	Buffer[1]=*(pt+1);
	Buffer[2]=*(pt+0);
	nTmp=pHead->nParameter2;//���κ�
	Buffer[3]=*(pt+1);
	Buffer[4]=*(pt+0);
	nTmp=pHead->nParameter3; //���
	Buffer[5]=*(pt+0);
	Buffer[6]=*(pt+1);
	Buffer[7]=pHead->szParameter3[0];		
	MakeBuf_SetAssisList(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, Buffer);	
	return RET_OK;
}

//�´���������
long TaskProc60(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	TSResultData  data;	
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´���������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�´���������", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//�ϴ���������
long TaskBufferProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int Cardno=0;
	unsigned char *pt=NULL;
	int n = pDocEx->nPortNo ;
	
	Cardno=atol(pTask->szMemo);
	pt=(unsigned char*)&Cardno;
	pBuffer->pBuffer[0]=*(pt+2);
	pBuffer->pBuffer[1]=*(pt+1);
	pBuffer->pBuffer[2]=*(pt+0);
	return MakeBuf_GetAssisList(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	
}

//�ϴ���������
long TaskProc61(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	long n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ϴ���������", "");
		return nResult;
	}
	memcpy(pTask->szMemo,pBuffer->pBuffer,8);
	ReportLog(pDocEx, pTask, RET_OK, "�ϴ���������", "");
	return RET_OK;
}

//���ò�������
long TaskBufferProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;

	if( !strcmp(pTask->szMemo, "1") )
		pDocEx->pChildDoc[n]->m_nSwitch = 1 ;
	else
		pDocEx->pChildDoc[n]->m_nSwitch = 0 ;

	if( pDocEx->pChildDoc[n]->m_nSwitch )
	{
		ReportLog(pDocEx, pTask, RET_OK, "���ò������ؿ���", "");
		return MakeBuf_SetAssistState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0X00);
	}
	else
	{
		ReportLog(pDocEx, pTask, RET_OK, "���ò������عر�", "");
		return MakeBuf_SetAssistState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0XFF);
	}
}

//���ò�������
long TaskProc62(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "���ò�������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "���ò�������", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}

//��ȡ��������
long TaskBufferProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo;
	return MakeBuf_GetAssistState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//��ȡ��������
long TaskProc63(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "��ȡ��������", "");
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "��ȡ��������", "");

	return RET_OK;
}



//����������
long TaskBufferProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSResultData  *pData = (TSResultData*)pHead->pData;

	int n = pDocEx->nPortNo ;
	unsigned char szBuffer[128];
	long nResult = RET_OK;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	memset(szBuffer, 0, sizeof(szBuffer));

	//�շѻ�ϵͳ������
	if( !strcmp(pDocEx->pChildDoc[n]->m_szMacCode, "0226") ) //�շѻ�
	{
		szBuffer[0] = (unsigned char)pData->nValue3;
		szBuffer[1] = (unsigned char)pData->nValue9;

		szBuffer[2] = ((pData->nValue4)/256)%256;
		szBuffer[3] = ((pData->nValue4))%256;

		SVC_DSP_2_HEX((unsigned char*)pData->sValue7, &szBuffer[4], 2);

		szBuffer[6] = (pData->nValue5)%256;
		szBuffer[7] = ((pData->nValue5)/256)%256;
		szBuffer[8] = ((pData->nValue5)/256/256)%256;

		szBuffer[9] = (pData->nValue8)%256;
		szBuffer[10] = ((pData->nValue8)/256)%256;
		szBuffer[11] = ((pData->nValue8)/256/256)%256;

		szBuffer[12] = (pData->nValue6)%256;
		szBuffer[13] = ((pData->nValue6)/256)%256;
		szBuffer[14] = ((pData->nValue6)/256/256)%256;

		szBuffer[15] = (pData->nValue7)%256;
		szBuffer[16] = ((pData->nValue7)/256)%256;
		szBuffer[17] = ((pData->nValue7)/256/256)%256;

		SVC_DSP_2_HEX((unsigned char*)pData->sValue8, &szBuffer[18], 1);

		szBuffer[19] = GetBaudRatecode(pData->nValue2);
		szBuffer[20] = atoi(pData->sValue6);

		SVC_DSP_2_HEX((unsigned char*)pData->sValue3, &szBuffer[21], 4);

		if( !strcmp(pData->sValue4, "") )
		{
			strcpy(pData->sValue4, "00000000");
		}

		SVC_DSP_2_HEX((unsigned char*)pData->sValue4, &szBuffer[25], 2);

		szBuffer[27] = atoi(pData->sValue5);

		if( szBuffer[27] == 0x65 )
			strcpy(pTask->szMemo, "65");
	}
	else
	{
		ReportLog(pDocEx, pTask, nResult, "��ʱ��ϵͳ������", "");
		strcpy(data.sMsg, "�˹����ݲ�֧��!");
		ReportTaskResult(pTask, RET_NG, &data);
	}

	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);

	MakeBuf_SetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBuffer);
 	pBuffer->nTimeOut1 = 1000 ;
	pBuffer->nTimeOut2 = 2000 ;

	return RET_ERRORCALL;
}

//����������
long TaskProc80(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSResultData  *pData = (TSResultData*)pHead->pData;
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( pBuffer == NULL )
	{
		ReportLog(pDocEx, pTask, RET_TERME_NOANSWER, "����������", "");
		GetResultMessage(RET_TERME_NOANSWER, data.sMsg);
		ReportTaskResult(pTask, RET_TERME_NOANSWER, &data);

		return RET_TERME_NOANSWER;
	}
	
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "����������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	printf("-------����������.........\n");

	//65�࿨���������µ����뷽��ʹ��
	if( !strcmp(pDocEx->pChildDoc[n]->m_szMacCode, "0121") )
	{
		long iResult = RET_SYSERROR;
		char szPass[128];

		memset(szPass, 0, sizeof(szPass));
		unsigned char szBuffer[32];
		unsigned char szID[32];
		memset(szBuffer, 0, sizeof(szBuffer));

		SVC_DSP_2_HEX((unsigned char*)szPass, szBuffer, 9);
		SVC_DSP_2_HEX((unsigned char*)pDocEx->pChildDoc[n]->m_szDeviceID, szID, 4);

		SmartEncrypt(1, szID, szBuffer);
		MakeBuf_SetWorkingKey(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, (unsigned char*)szBuffer, 1);

		for(int i=0; i< 3; i++)
		{
			pBuffer->nTimeOut1 = 500 ;
			pBuffer->nTimeOut1 = 1000 ;
			if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
			{
				iResult = UnMakeDeviceBufferEx(pBuffer);
				if( iResult == RET_OK )
				{
					break;
				}
			}
			else
			{
				Sleep(2000);
			}
		}

		if( iResult != RET_OK )
		{
			ReportLog(pDocEx, pTask, iResult, "����������", "���ü�ʱ����Կʧ��");
			return iResult;
		}
		else
		{
			ReportLog(pDocEx, pTask, iResult, "����������", "���ü�ʱ����Կ�ɹ�!");
		}
	}

	//65�࿨���������µ����뷽��ʹ��
	if( !strcmp(pTask->szMemo, "65") )
	{
		//strSQL = "select smt_content from smart_setup where smt_systemid='93' and upper(smt_param)='DWMM1' ";
		unsigned char szBuffer[32];
		char  szPass[32];
		memset(szBuffer, 0, sizeof(szBuffer));

		TSSystemParam  Parameter;

		ZeroMemory(&Parameter, sizeof(Parameter));
		GetParameter(0, &Parameter);

		strcpy(szPass, Parameter.szParameter3);

		UnPassword(szPass, 'd', szBuffer);

		int k = atoi((char*)szBuffer);
		szBuffer[0] = k%256;
		szBuffer[1] = (k/256)%256;

		MakeBuf_SetV10Password(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBuffer);

		for(int i=0; i< 3; i++)
		{
			pBuffer->nTimeOut1 = 500 ;
			pBuffer->nTimeOut1 = 1000 ;
			if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
			{
				long iResult = UnMakeDeviceBufferEx(pBuffer);
				if( iResult == RET_OK )
				{
					ReportLog(pDocEx, pTask, iResult, "����������", "");
					return iResult;
				}
			}
			else
			{
				Sleep(2000);
			}
		}

		ReportLog(pDocEx, pTask, nResult, "����������", "����V10����˾����ʧ��");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "�շѻ�ϵͳ������", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}

//У��������
long TaskBufferProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_GetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//У��������
long TaskProc81(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "У��������", "");

		ReportLog(pDocEx, pTask, nResult, "�շѻ�ϵͳ������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	

	//�շѻ�ϵͳ������
	if( strcmp(pDocEx->pChildDoc[n]->m_szMacCode, "0121") )
	{
		unsigned char *pHardBuffer = pBuffer->pBuffer+4;
		TSResultData  data;

		ZeroMemory(&data, sizeof(data));

		strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID);
		SVC_HEX_2_DSP(&pHardBuffer[0], (unsigned char*)data.sValue2, 4); //��Ȩ��
		data.nValue1 = pHardBuffer[4]; //����		
		data.nValue3 = pHardBuffer[5]; //���뿪��(��ʼ��Ϊ0x00)
		data.nValue9 = pHardBuffer[6]; //�շѷ�ʽ
		data.nValue4 = pHardBuffer[7]*256+pHardBuffer[8]; //��Ƭ���ʹ�ô���
		sprintf(data.sValue7, "%.2X%.2X", pHardBuffer[9], pHardBuffer[10]); // �������ѿ����
		data.nValue5 = pHardBuffer[11]+pHardBuffer[12]*256+pHardBuffer[13]*65536; //Ǯ���������޶�
		data.nValue8 = pHardBuffer[14]+pHardBuffer[15]*256+pHardBuffer[16]*65536; //ÿ�δ�ȡ���޶�
		data.nValue6 = pHardBuffer[17]+pHardBuffer[18]*256+pHardBuffer[19]*65536; //Ǯ���������޶�
		data.nValue7 = pHardBuffer[20]+pHardBuffer[21]*256+pHardBuffer[22]*65536; //��ȡ�ֵ��
		sprintf(data.sValue8, "%.2X", pHardBuffer[23]);  //��������
		data.nValue2 = GetBaudRatecodeEx(pHardBuffer[24]); //ͨ�Ų�����
		sprintf(data.sValue6, "%d", pHardBuffer[25]);   //Ǯ������
		SVC_HEX_2_DSP(&pHardBuffer[26], (unsigned char*)data.sValue3, 4); //����������Կǰ�ĸ��ֽ�
		sprintf(data.sValue4, "%.2X%.2X", pHardBuffer[30], pHardBuffer[31]);   //Ǯ������
		sprintf(data.sValue5, "%d", pHardBuffer[32]);

		ReportLog(pDocEx, pTask, RET_OK, "�շѻ�ϵͳ������", "");
		GetResultMessage(RET_OK, data.sMsg);
		ReportTaskResult(pTask, RET_OK, &data);
	}
	else
	{
		ReportLog(pDocEx, pTask, nResult, "��ʱ��ϵͳ������", "");
		strcpy(data.sMsg, "�˹����ݲ�֧��!");
		ReportTaskResult(pTask, RET_NG, &data);
	}

	return RET_OK;
}

//У��ʱ��
long TaskBufferProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//У��ʱ��
long TaskProc101(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];

	CString strTime = pTask->szMemo;

	CTime  tm(2000+atoi(strTime.Left(2).GetBuffer(0)), 
			atoi(strTime.Mid(2,2).GetBuffer(0)), 
			atoi(strTime.Mid(4,2).GetBuffer(0)), 
			atoi(strTime.Mid(6,2).GetBuffer(0)), 
			atoi(strTime.Mid(8,2).GetBuffer(0)), 
			atoi(strTime.Mid(10,2).GetBuffer(0)));

	unsigned char Buffer[32];
	memset(Buffer, 0, sizeof(Buffer));

	Buffer[0] = tm.GetYear()-2000;
	Buffer[1] = tm.GetMonth();
	Buffer[2] = tm.GetDay();
	Buffer[3] = tm.GetHour();
	Buffer[4] = tm.GetMinute();
	Buffer[5] = tm.GetSecond();
	Buffer[6] = tm.GetDayOfWeek();

	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	MakeBuf_SetClock(&pDoc->DeviceInfo, pBuffer, Buffer);
	if( SendRequest(pDoc, pBuffer) != RET_OK )
	{
		GetResultMessage(RET_SEND_ERROR, data.sMsg);
		ReportTaskResult(pTask, RET_SEND_ERROR, &data);

		ReportLog(pDoc, pTask, RET_SEND_ERROR, "У��ʱ��", "");
		return RET_SEND_ERROR;
	}

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult == RET_OK )
	{
		GetResultMessage(RET_OK, data.sMsg);
		ReportTaskResult(pTask, RET_OK, &data);

		ReportLog(pDoc, pTask, RET_OK, "У��ʱ��", "У��ʱ�ӳɹ�!");
		return RET_OK;
	}
	else
	{
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		ReportLog(pDoc, pTask, nResult, "У��ʱ��", "");
		return nResult;
	}
}

//�´���������޶�
long TaskBufferProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo;
	long nValue = 10000;
	//modified by lina
	
	/*
	try
	{
		long nValue = atoi(pTask->szMemo);
	}
	catch(...)
	{

	}*/
	
	nValue = atoi(pTask->szMemo);
	if(nValue < 0)
		nValue = 10000;


	//if( nValue < 0 )
	//	nValue = 36000 ;

	unsigned char sMoney[32];
	memset(sMoney, 0, sizeof(sMoney));

	sMoney[0] = nValue%256;
	sMoney[1] = (nValue/256)%256;
	sMoney[2] = (nValue/256/256)%256;

	return MakeBuf_SetLargeConsumeMoney(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, sMoney);
}
	
//�´���������޶��
long TaskProc102(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´���������޶�", "");

		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "�´���������޶�", "");

	return RET_OK;
}

//������
long TaskBufferProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	MakeBuf_CollectData(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
	return RET_ERRORCALL;
}

long ToDec(long nHex)
{
	return (nHex/16*10) + (nHex%16);
}
	
//������
long TaskProc103(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//�������ѱ�ż��汾
long TaskBufferProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}

//�������ѱ�ż��汾
long TaskProc104(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	int *pArray = (int*)pHead->pData;

	if( strcmp(pDoc->m_sWorkMode, "2") )
	{
		ReportLog(pDocEx, pTask, RET_TASKWHERE_ERROR, "�������ѱ�ż��汾", "�ն˻����Ǳ��ģʽ!");

		GetResultMessage(RET_TASKWHERE_ERROR, data.sMsg);
		ReportTaskResult(pTask, RET_TASKWHERE_ERROR, &data);

		return RET_TASKWHERE_ERROR;
	}

	unsigned char sArray[100][3];
	int  i=0, iCount = 0 ;
	long nValue = 0 ;

	//��������, ��ʽ������շѻ�ʱ��θ�ʽ 
	memset(sArray, 0, sizeof(sArray));

	while( iCount < pHead->nCount )
	{
		nValue = pArray[iCount];

		sArray[i][0] = nValue%256;
		sArray[i][1] = (nValue/256)%256;
		sArray[i++][2] = (nValue/256/256)%256;

		if( i >= 50 || iCount >= pHead->nCount-1 )
		{
			if( iCount <= 50 )
				MakeBuf_SetSFJConsumeNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0, i, &sArray[0][0]);
			else
				MakeBuf_SetSFJConsumeNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 1, i, &sArray[0][0]);

			nValue = RET_SYSERROR;
			for(int k=0; k<3; k++)
			{
				if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
				{
					nValue = UnMakeDeviceBufferEx(pBuffer);
					if( nValue == RET_OK )
					{
						break;
					}
				}
			}

			if( nValue != RET_OK )
			{
				ReportLog(pDocEx, pTask, nValue, "�������ѱ�ż��汾", "�����������ѱ��!");
				GetResultMessage(nValue, data.sMsg);
				ReportTaskResult(pTask, nValue, &data);
				return nValue;
			}
			i=0; 
			memset(sArray, 0, sizeof(sArray));
		}
		iCount++;
	}

	unsigned char sValue[64];
	unsigned char sBuffer[16];

	char szTmp[8];

	memset(sValue, 0, sizeof(sValue));
	memset(sBuffer, 0, sizeof(sBuffer));

	strcpy((char*)sValue, pHead->szValue);

	printf("�����������ѱ�ż��汾, �汾 = %s\n", sValue);

	if( strlen((char*)sValue) < 12 ) 
	{
		ReportLog(pDocEx, pTask, RET_DBQUERYERROR, "�������ѱ�ż��汾", "��Smart_commrec�е����ѱ�ż��汾�ֶ����ݲ���ȷ!");

		GetResultMessage(RET_VALIDPACKET, data.sMsg);
		ReportTaskResult(pTask, RET_VALIDPACKET, &data);

		return RET_DBQUERYERROR;
	}

	memset(szTmp, 0, sizeof(szTmp));

	szTmp[0] = sValue[0]; szTmp[1] = sValue[1]; 
	sBuffer[0] = atoi(szTmp);

	szTmp[0] = sValue[2]; szTmp[1] = sValue[3]; 
	sBuffer[1] = atoi(szTmp);

	szTmp[0] = sValue[4]; szTmp[1] = sValue[5]; 
	sBuffer[2] = atoi(szTmp);

	szTmp[0] = sValue[6]; szTmp[1] = sValue[7]; 
	sBuffer[3] = atoi(szTmp);

	szTmp[0] = sValue[8]; szTmp[1] = sValue[9]; 
	sBuffer[4] = atoi(szTmp);

	szTmp[0] = sValue[10]; szTmp[1] = sValue[11]; 
	sBuffer[5] = atoi(szTmp);

	Sleep(1000);

	MakeBuf_SetSFJComsumeVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, sBuffer);
	for(int k=0; k<3; k++)
	{
		if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
		{
			nValue = UnMakeDeviceBufferEx(pBuffer);
			if( nValue == RET_OK )
			{
				break;
			}
		}
	}

	ReportLog(pDocEx, pTask, nValue, "�������ѱ�ż��汾", "");

	GetResultMessage(nValue, data.sMsg);
	ReportTaskResult(pTask, nValue, &data);

	return nValue;
}

//�������ѿ�ݱ��
long TaskBufferProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	printf("--------�������ѿ�ݱ��-------------------\n");
	//TSResultData  data;
	//ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	//TSAttachData *pHead = (TSAttachData*)pTask->pData;
	//int *pArray = (int*)pHead->pData;

	/*if( strcmp(pDoc->m_sWorkMode, "2") )
	{
		ReportLog(pDocEx, pTask, RET_TASKWHERE_ERROR, "�������ѿ�ݱ��", "�ն˻����Ǳ��ģʽ!");

		GetResultMessage(RET_TASKWHERE_ERROR, data.sMsg);
		ReportTaskResult(pTask, RET_TASKWHERE_ERROR, &data);

		return RET_TASKWHERE_ERROR;
	}*/
	printf("���ݲ���pTask->szMemo=%s\n", pTask->szMemo);
	char temp[256];
	sprintf(temp,"");
	temp[0] = pTask->szMemo[0];
	temp[1] = pTask->szMemo[1];
	int i,j,k;
	unsigned char sArray[100][3];
	long nValue;
	memset(sArray, 0, sizeof(sArray));
	
	i = atoi(temp); 
	printf("��ݷ�ʽ������=%d\n",i);
	
	for(j=0;j<i;j++)
	{
		sprintf(temp,"");
		for(k=0;k<4;k++)
		{
			temp[k] = pTask->szMemo[2+j*4+k];
		}
		nValue = atoi(temp);
		printf("nValue = %d\n",nValue);
		sArray[j][0] = nValue%256;
		sArray[j][1] = (nValue/256)%256;
		sArray[j][2] = (nValue/256/256)%256;
	}

/*	unsigned char sArray[100][3];
	//int  i=0;
	long nValue;

	//��������, ��ʽ������շѻ�ʱ��θ�ʽ 
	memset(sArray, 0, sizeof(sArray));
	while( i < 100 && i< pHead->nCount  )
	{
		nValue = pArray[i];

		sArray[i][0] = nValue%256;
		sArray[i][1] = (nValue/256)%256;
		sArray[i][2] = (nValue/256/256)%256;

		i++;
	}
	*/
	return MakeBuf_SetSFJFastNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, i, &sArray[0][0]);
}
	
//�������ѿ�ݱ��
long TaskProc105(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�������ѿ�ݱ��", "");

		GetResultMessage(nResult, data.sMsg);
		printf(" ------���������ѿ�ݱ��ʧ��-----\n");
		ReportTaskResult(pTask, nResult, &data);
		
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "�������ѿ�ݱ��", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	printf("------���������ѿ�ݱ�ųɹ�-----\n");
	return RET_OK;
}

//���û���ID
long TaskBufferProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	return RET_OK;
}
	
//���û���ID����
long TaskProc106(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);

	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "���û���ID", "");
		return nResult;
	}

	strcpy(pDocEx->pChildDoc[n]->m_szDeviceID, pTask->szMemo);

	ReportLog(pDocEx, pTask, RET_OK, "����ID��", "");

	return RET_OK;
}

//��������ʱ��β���
long TaskBufferProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo;
	TSSmartDoc *pDoc = pDocEx->pChildDoc[n];
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSXFTimePara *pPara = (TSXFTimePara*)pHead->pData;

	unsigned char sArray[320][10];
	int  i=0;
	long nValue;
	unsigned char sValue[64];
	char sTmp[16];
	long nTry = 0 ;

	//��������, ��ʽ������շѻ�ʱ��θ�ʽ 
	memset(sArray, 0, sizeof(sArray));
	while( i< pHead->nCount && i < 16 )
	{
		memset(sTmp, 0, sizeof(sTmp));

		strcpy((char*)sValue, pPara[i].szBeginTime);
		sTmp[0] = sValue[0]; sTmp[1] = sValue[1];
		sArray[i][0] = atoi(sTmp);

		sTmp[0] = sValue[3]; sTmp[1] = sValue[4];
		sArray[i][1] = atoi(sTmp);

		strcpy((char*)sValue, pPara[i].szEndTime);
		sTmp[0] = sValue[0]; sTmp[1] = sValue[1];
		sArray[i][2] = atoi(sTmp);

		sTmp[0] = sValue[3]; sTmp[1] = sValue[4];
		sArray[i][3] = atoi(sTmp);

		strcpy((char*)sValue, pPara[i].szClass);
		int nBin = GetBinaryValue((char*)sValue);
		sArray[i][4] = (nBin/256)%256;
		sArray[i][5] = nBin%256;


		nValue = pPara[i].nMoney;
		sArray[i][6] = nValue%256;
		sArray[i][7] = (nValue/256)%256;
		sArray[i][8] = (nValue/256/256)%256;

		nValue = pPara[i].nTimes;
		sArray[i][9] = (unsigned char)nValue ;
		if( nTry < nValue )
			nTry = nValue ;

		i++;
	}

	return MakeBuf_SetSFJ_TimePhase(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,i, nTry, &sArray[0][0]);
}
	
//��������ʱ��β���
long TaskProc107(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int n = pDocEx->nPortNo;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "��������ʱ��β���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	ReportLog(pDocEx, pTask, RET_OK, "��������ʱ��β���", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}


//����ע���
long TaskBufferProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_CONTINUE;
}
	
//����ע���
long TaskProc108(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//����״̬����
long TaskBufferProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_SetFireState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//����״̬����
long TaskProc110(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "���÷���״̬", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "����״̬����", "");

	return RET_OK;
}

//����״̬����
long TaskBufferProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_SetTheftState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//����״̬����
long TaskProc111(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;

	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "���÷���״̬", "");

		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "����״̬����", "");

	return RET_OK;
}

//�ӷ������״̬�ָ���������״̬
long TaskBufferProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_SetNormalState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//�ӷ������״̬�ָ���������״̬
long TaskProc112(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ָ���������״̬", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	ReportLog(pDocEx, pTask, RET_OK, "�ָ���������״̬", "");

	return RET_OK;
}

//�´����ѱ���
long TaskBufferProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	unsigned char *pt=NULL;
	int n = pDocEx->nPortNo ;
	TSAttachData *pHead = (TSAttachData*)pTask->pData ;

	pt = (unsigned char*)&pHead->nValue ;
	unsigned char nClass = *(pt+0);
	pt = (unsigned char*)&pHead->nCount ;
	unsigned char nRate  = *(pt+0);
	MakeBuf_SetIncFeeRate(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, nClass, nRate);
	printf("�´����ѱ���:<<<<<<<<<<����: %ld, ����:%ld.........\n", nClass, nRate);	
	return RET_OK;
}

//�´����ѱ���
long TaskProc120(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int n = pDocEx->nPortNo ;

	TSAttachData *pHead = (TSAttachData*)pTask->pData ;

	int nClass = pHead->nValue ;
	int nRate  = pHead->nCount ;

	data.nValue1 = nClass ;
	data.nValue2 = nRate ;

	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´����ѱ���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}

	GetResultMessage(nResult, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	ReportLog(pDocEx, pTask, RET_OK, "�´����ѱ���", NULL);

	return RET_OK;
}

//����ǩ������
long TaskBufferProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;

	if( !strcmp(pTask->szMemo, "1") )
		pDocEx->pChildDoc[n]->m_nSwitch = 1 ;
	else
		pDocEx->pChildDoc[n]->m_nSwitch = 0 ;

//	if( pDocEx->pChildDoc[n]->m_nSwitch ==1 )
//	{
//		ReportLog(pDocEx, pTask, RET_OK, "����ǩ�����ؿ���", "");
//		return MakeBuf_SetComsumeFlag(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0);
//	}
//	else
//	{
		ReportLog(pDocEx, pTask, RET_OK, "����ǩ�����عر�", "");
		return MakeBuf_SetComsumeFlag(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, 0);
//	}
}

//����ǩ������
long TaskProc130(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		printf("----����%.8Xǩ��ʧ��,����Ϊ%d\n",pDocEx->pChildDoc[n]->m_nAuthID,
			nResult);

		ReportLog(pDocEx, pTask, nResult, "����ǩ������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	printf("----����%.8Xǩ�˳ɹ�\n",pDocEx->pChildDoc[n]->m_nAuthID);	
	ReportLog(pDocEx, pTask, RET_OK, "����ǩ������", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}


//�ϴ�ʱ��
long TaskBufferProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;	
	MakeBuf_GetClock(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	   
	return RET_OK;
}

//�ϴ��豸ʱ��
long TaskProc03(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ϴ��豸ʱ��", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)data.sValue1,6);
	//SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)pTask->szMemo,6);

	ReportLog(pDocEx, pTask, RET_OK, "�ϴ��豸ʱ��", "");	
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//����ÿ���ۼ����ѽ��
long TaskBufferProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	int  nMoney = atoi(pTask->szMemo);
	unsigned char ucBuffer[4];
	if(nMoney <= 0)
		nMoney = 3000;
	ucBuffer[0] = nMoney%256;
	ucBuffer[1] = nMoney/256;
	ucBuffer[2] = nMoney/256/256;
	ucBuffer[3] = nMoney/256/256/256;
	MakeBuf_SetDayLargeComsumeMoney(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,ucBuffer);
	return RET_OK;
}

//����ÿ���ۼ����ѽ��
long TaskProc131(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "����ÿ���ۼ������޶�", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "����ÿ���ۼ������޶�", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//��ʼ��LPORT�˿ڲ���
long TaskBufferProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	int  nMoney = atoi(pTask->szMemo);
	long nResult;

	for(long k=0; k<3; k++)
	{
		MakeBuf_ClearPortData(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, nMoney);
		if( SendRequest(pDocEx->pChildDoc[n], pBuffer) == RET_OK )
		{
			if( (nResult=UnMakeDeviceBufferEx(pBuffer)) == RET_OK )
				break;
			else
				Sleep(1000);
		}
	}
	Sleep(1000);
	
	MakeBuf_SetPortToFactorySetting(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,nMoney);
	
	return RET_OK;
}

//��ʼ��LPORT�˿ڲ���
long TaskProc132(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "��ʼ��LPORT�˿ڲ���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "��ʼ��LPORT�˿ڲ���", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//�����ն˹���Ա����
long TaskBufferProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	unsigned char ucPassword[3];
	SVC_DSP_2_HEX((unsigned char *)pTask->szMemo,ucPassword,3); 
	MakeBuf_SetManagePassword(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,ucPassword);
	return RET_OK;
}

//�����ն˹���Ա����
long TaskProc133(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�����ն˹���Ա����", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�����ն˹���Ա����", "");

	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//��ȡ�˿ڲ���
long TaskBufferProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	
	MakeBuf_GetPortPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,atoi(pTask->szMemo));
	return RET_OK;
}

long TaskProc134(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "��ȡ�˿ڲ���", "");

		ReportLog(pDocEx, pTask, nResult, "��ȡ�˿ڲ���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}

	for(int i=0; i< pBuffer->nCmdSize; i++) 
	{
		printf("%02X ", pBuffer->pBuffer[i]);
	}
	printf("\n");

	//��ȡ�˿ڲ���
	
		unsigned char *pHardBuffer = pBuffer->pBuffer+4;
	//	TSResultData  data;

		ZeroMemory(&data, sizeof(data));
		sprintf(data.sValue1,"%.2X%.2X%.2X%.2X",pHardBuffer[0],pHardBuffer[1],pHardBuffer[2],pHardBuffer[3]); //ID��
		data.nValue1 = pHardBuffer[4];//����
		sprintf(data.sValue2,"%.2X%.2X",pHardBuffer[5],pHardBuffer[6]);//����
		sprintf(data.sValue3,"%.2X%.2X%.2X%.2X",pHardBuffer[7],pHardBuffer[8],pHardBuffer[9],pHardBuffer[10]);//����汾
		sprintf(data.sValue4,"%.2X%.2X%.2X%.2X",pHardBuffer[11],
			                                     pHardBuffer[12],
												 pHardBuffer[13],
												 pHardBuffer[14]);//ע���

		ReportLog(pDocEx, pTask, RET_OK, "��ȡ�˿ڲ���", "");
		GetResultMessage(RET_OK, data.sMsg);
		ReportTaskResult(pTask, RET_OK, &data);
	

	return RET_OK;
}


/**************************dengjun 20050830********************/

#if 1
//�㲥�´�������
long TaskBufferProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)     
{
	int ret=0;
	if(pTask==NULL)	   return -1;
	if(pDocEx==NULL)   return -1;
	if(pBuffer==NULL)  return -1;
	
	int n = pDocEx->nPortNo ;
	printf("------�㲥�������ɹ�------\n");		
	unsigned char buffer[80];
	unsigned char version[6];
	bool bResult= false; 

	memset(buffer, 0, sizeof(buffer));

	memcpy(buffer,pTask->szMemo,3);
	memcpy(version,pTask->szMemo+3,6);	
   TSSmartDoc *pDoc = pDocEx->pChildDoc[0];
	pBuffer->nBufferSize = MakeBuf_BoardWhiteNo(pBuffer->pBuffer, (unsigned char*)version, buffer);			
	ret=SendRequest(pDoc, pBuffer);
	memset(buffer, 0, sizeof(buffer));
	SVC_HEX_2_DSP((unsigned char*)pBuffer->pBuffer,buffer,pBuffer->nBufferSize);
	ReportLog(pDocEx, pTask, RET_OK, "�㲥�������ɹ�", "");	
	return RET_OK;
}

#endif

//�㲥�´�������
long TaskProc135(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{	
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�㲥�´�������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�㲥�´�������", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);

	return RET_OK;
}


//�´�/ɾ��������
long TaskBufferProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	BYTE  CardNo[6],*pt=NULL;
	int	  count=0,flag=0;
	unsigned long  cardno=0;
	long		ret=0;

	int n = pDocEx->nPortNo ;

	memset(CardNo, 0x00, sizeof CardNo );
	
	TSAttachData *pHead = (TSAttachData*)pTask->pData ;
	count=pHead->nCount;  //����
	flag = pHead->nValue;  //��ʶ
	cardno = atol(pHead->szValue);
	pt = (BYTE*)&cardno;
	CardNo[0]= *(pt+2);
	CardNo[1]= *(pt+1);
	CardNo[2]= *(pt+0);

	if( flag == 0 ) //�´�һ��������
	{		
		ret =MakeBuf_DownWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,10,(BYTE*)CardNo);	
	}
	else if( flag == 1 ) //ɾ��һ��������
	{
		ret =MakeBuf_DelWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, CardNo);	
	}
	else if( flag == 2 ) //ɾ�����а�����
	{
		ret =MakeBuf_DelAllWhiteCardNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
	}
	printf("�´���ɾ��������");

	return ret;	
}

//�´�/ɾ��������
long TaskProc136(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´�/ɾ��������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}	
	ReportLog(pDocEx, pTask, RET_OK, "�´�/ɾ��������", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930113
//�´���ʱ���������汾
long TaskBufferProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	BYTE   date1[12];

	memset(date1, 0x00, sizeof date1 );
	SVC_DSP_2_HEX((BYTE*)pTask->szMemo,date1,6);	
	return MakeBuf_SetWhiteVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,date1);
}

//�´���ʱ���������汾
long TaskProc138(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	int		n = pDocEx->nPortNo ;
	long	nResult=0;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´���ʱ���������汾", "");

		ReportLog(pDocEx, pTask, nResult, "�´���ʱ���������汾", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}	
	strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID); //�豸ID	
	ReportLog(pDocEx, pTask, RET_OK, "�´���ʱ���������汾", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}




//930114
//�ϴ���ʱ���������汾
long TaskBufferProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;	
	return MakeBuf_GetWhiteVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	
}

//�ϴ���ʱ���������汾
long TaskProc137(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	int		n = pDocEx->nPortNo ;
	long	nResult=0;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ϴ���ʱ���������汾", "");

		ReportLog(pDocEx, pTask, nResult, "�ϴ���ʱ���������汾", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}	
	strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID); //�豸ID	
	unsigned char *pHardBuffer = pBuffer->pBuffer+4;
	ReportLog(pDocEx, pTask, RET_OK, "�ϴ���ʱ���������汾", "");
	GetResultMessage(RET_OK, data.sMsg);
	SVC_HEX_2_DSP(pHardBuffer,(BYTE*)data.ssValue1,6);	
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}



//930110
//�ϴ���ʱ���ڼ���
long TaskBufferProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;	
	MakeBuf_GetMode3Holiday(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);		
	return RET_OK;
}

//�ϴ���ʱ���ڼ���
long TaskProc139(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	TSResultData  data;
	memset(&data, 0x00, sizeof(TSResultData));
	
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;	
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ϴ���ʱ���ڼ���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	//������	
	data.nValue1=pHardBuffer[0];
	memcpy(data.ssValue1,pHardBuffer+1,data.nValue1*2);	
	ReportLog(pDocEx, pTask, RET_OK, "�ϴ���ʱ���ڼ���", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);	
	return RET_OK;
}

//930109
//�´���ʱ���ڼ���
long TaskBufferProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int No=0;
	BYTE Buffer[240];
	memset(Buffer, 0x00, sizeof Buffer );
	TSAttachData *pHead =(TSAttachData*)pTask->pData;
	int  n = pDocEx->nPortNo;	
	No = pHead->nCount;
	memcpy(Buffer,pHead->szValue,No*2);
	MakeBuf_SetMode3Holiday(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,No,Buffer);	
	printf("count=%ld   %02ld%02ld%02ld%02ld%02ld\n",No,Buffer[0],Buffer[1],Buffer[2],Buffer[3],Buffer[4]);
	return RET_OK;
}

//�´���ʱ���ڼ���
long TaskProc140(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	
	ZeroMemory(&data, sizeof(data));	

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´���ʱ���ڼ���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�´���ʱ���ڼ���", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930106
//�ϴ���ʱ��ʱ���
long TaskBufferProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int WeekInfo=0;
	WeekInfo = atol(pTask->szMemo);
	int  n = pDocEx->nPortNo;	
	MakeBuf_GetMode3TimePhaseInfo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,WeekInfo);		
	return RET_OK;
}

//�ϴ���ʱ��ʱ���
long TaskProc141(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	int		count=0;
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;

	ZeroMemory(&data, sizeof(data));
	count = (int)pHardBuffer[0];

	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ϴ���ʱ��ʱ���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	//ʱ�����
	data.nValue1 = pHardBuffer[0];	
	memcpy(data.ssValue1,pHardBuffer+1,data.nValue1*8);
	ReportLog(pDocEx, pTask, RET_OK, "�ϴ���ʱ��ʱ���", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);	
	return RET_OK;
}


//930105
//�´���ʱ��ʱ���
long TaskBufferProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int WeekInfo=0;
	int No=0;
	BYTE Buffer[128];
	TSAttachData *pHead;

	memset(Buffer, 0x00, sizeof Buffer );
	pHead = (TSAttachData*)pTask->pData;
	WeekInfo = pHead->nCount;		//����
	No		 = pHead->nValue;		//ʱ�������
	memcpy(Buffer,pHead->szValue,No*8);	
	int  n = pDocEx->nPortNo;	
	MakeBuf_SetMode3TimePhaseInfo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,WeekInfo,No,Buffer);	
	return RET_OK;
}

//�´���ʱ��ʱ���
long TaskProc142(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´���ʱ��ʱ���", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�´���ʱ��ʱ���", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930120
//�Ž������ؿ���
long TaskBufferProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int flag = 0;	
	int  n = pDocEx->nPortNo;		

	flag = atol(pTask->szMemo);
	if( flag == 1 )
	{
		MakeBuf_SetFireState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);/// ���ܣ�����Ϊ����״̬
	}
	else if( flag == 2 )
	{
	
		MakeBuf_SetTheftState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);/// ���ܣ�����Ϊ����״̬
	}	
	else if( flag == 3 )
	{
		MakeBuf_SetNormalState(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);/// ���ܣ��ָ�����
	}
	return RET_OK;
}

//�Ž������ؿ���
long TaskProc143(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�Ž�����", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�Ž�����", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930103
//���ü�ʱ��������
long TaskBufferProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	unsigned char szBuffer[128];
	long nResult = RET_OK;
	TSResultData  data;

	memset(&data,    0x00, sizeof(data)    );
	memset(szBuffer, 0x00, sizeof(szBuffer));
	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);
	memcpy(szBuffer,pTask->szMemo,28);
	MakeBuf_SetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, szBuffer);	
 	pBuffer->nTimeOut1 = 1000 ;
	pBuffer->nTimeOut2 = 2000 ;
	return RET_ERRORCALL;
}

//���ü�ʱ��������
long TaskProc144(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;
	TSAttachData *pHead = (TSAttachData*)pTask->pData;
	TSResultData  *pData = (TSResultData*)pHead->pData;
	TSResultData  data;

	memset(&data, 0, sizeof(data));

	if( pBuffer == NULL )
	{
		ReportLog(pDocEx, pTask, RET_TERME_NOANSWER, "���ü�ʱ��������", "");
		GetResultMessage(RET_TERME_NOANSWER, data.sMsg);
		ReportTaskResult(pTask, RET_TERME_NOANSWER, &data);
		return RET_TERME_NOANSWER;
	}
	
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "���ü�ʱ��������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "���ü�ʱ��������", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//930102
//�ɼ���ʱ����ʷ��ˮ
long TaskBufferProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{	
	int  n = pDocEx->nPortNo;			
	unsigned char SerialNo[5],*pt=NULL;
	unsigned long  serial=0;
	memset(SerialNo, 0x00, sizeof SerialNo );

	serial = atol(pTask->szMemo);
	pt=(unsigned char*)&serial;
	SerialNo[0]=*(pt+1);
	SerialNo[1]=*(pt+0);
	MakeBuf_CollectDataBySerialNo(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer,SerialNo);
	return RET_OK;
}

////�ɼ���ʱ����ʷ��ˮ
long TaskProc145(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	

	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ɼ���ʱ����ʷ��ˮ", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�ɼ���ʱ����ʷ��ˮ", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer+4,(int)pBuffer->pBuffer[3]);
	data.nValue1=(int)pBuffer->pBuffer[3];
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//930104
//�ϴ���ʱ��������
long TaskBufferProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int n = pDocEx->nPortNo ;
	return MakeBuf_GetMainPar(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);
}

//�ϴ�930104������
long TaskProc146(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{

	int		n = pDocEx->nPortNo ;
	long	nResult=0;
	TSResultData  data;

	memset(&data, 0, sizeof(data));
	nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ϴ���ʱ��������", "");

		ReportLog(pDocEx, pTask, nResult, "�ϴ���ʱ��������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);

		return nResult;
	}
	unsigned char *pHardBuffer = pBuffer->pBuffer+4;

	strcpy(data.sValue1, pDocEx->pChildDoc[n]->m_szDeviceID); //�豸ID		
	memcpy(data.ssValue1,pHardBuffer,33);	//������
	ReportLog(pDocEx, pTask, RET_OK, "�ϴ���ʱ��������", "");
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}



//930021
//�޸�POS����������POS
long TaskBufferProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	return RET_OK;
}

//�޸�POS����������POS
long TaskProc147(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;	
	ZeroMemory(&data, sizeof(data));
	if( pTask->szMemo[0] == '0' )
	{
		ReportLog(pDocEx, pTask, RET_PARAMETER_ERROR2, "�޸�POS����������POS", "");
		GetResultMessage(RET_PARAMETER_ERROR2, data.sMsg);
		memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
		data.nValue1 = pBuffer->nBufferSize;
		ReportTaskResult(pTask, RET_PARAMETER_ERROR2, &data);
		return RET_PARAMETER_ERROR2;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�޸�POS����������POS", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}


//�´���������
long TaskBufferProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{	
	BYTE Buffer[128],*pt=NULL;
	int	 nTmp=0;
	TSSystemParam *pHead;
	int  n = pDocEx->nPortNo;

	memset(Buffer, 0x00, sizeof Buffer );
	pHead = (TSSystemParam*)pTask->pData;
	nTmp=pHead->nParameter4;//����
	pt=(BYTE*)&nTmp;
	Buffer[0]=*(pt+2);
	Buffer[1]=*(pt+1);
	Buffer[2]=*(pt+0);
	nTmp=pHead->nParameter2;//���κ�
	Buffer[3]=*(pt+1);
	Buffer[4]=*(pt+0);
	nTmp=pHead->nParameter3; //���
	Buffer[5]=*(pt+0);
	Buffer[6]=*(pt+1);
	SVC_DSP_2_HEX((BYTE*)pHead->szParameter2,&Buffer[7], 1);
	MakeBuf_SetAssisList(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer, Buffer);	
	return RET_OK;
}


//�´���������
long TaskProc148(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	
	TSResultData  data;	
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�´���������", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	ReportLog(pDocEx, pTask, RET_OK, "�´���������", "");
	GetResultMessage(RET_OK, data.sMsg);
	memcpy(data.ssValue1,pBuffer->pBuffer,pBuffer->nBufferSize);
	data.nValue1 = pBuffer->nBufferSize;
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}

//�ϴ��������汾
long TaskBufferProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int  n = pDocEx->nPortNo;		
	MakeBuf_GetBlackVersion(&pDocEx->pChildDoc[n]->DeviceInfo, pBuffer);	   
	return RET_OK;
}

//�ϴ��������汾
long TaskProc149(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	TSResultData  data;
	unsigned char *pHardBuffer = pBuffer->pBuffer + 4;
	
	ZeroMemory(&data, sizeof(data));
	int  n = pDocEx->nPortNo;
	long nResult = UnMakeDeviceBufferEx(pBuffer);
	if( nResult != RET_OK ) 
	{
		ReportLog(pDocEx, pTask, nResult, "�ϴ��������汾", "");
		GetResultMessage(nResult, data.sMsg);
		ReportTaskResult(pTask, nResult, &data);
		return nResult;
	}
	SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)data.sValue1,6);
	SVC_HEX_2_DSP(&pHardBuffer[0],(unsigned char *)pTask->szMemo,6);
	
	ReportLog(pDocEx, pTask, RET_OK, "�ϴ��������汾", "");	
	GetResultMessage(RET_OK, data.sMsg);
	ReportTaskResult(pTask, RET_OK, &data);
	return RET_OK;
}
