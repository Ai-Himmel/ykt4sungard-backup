// Task.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Task.h"

lpfnGetDBHandle	            GetDBHandle = NULL ;
lpfnFreeDBHandle            FreeDBHandle = NULL ;
lpfnExecuteQuery			ExecuteQuery = NULL ;
lpfnCloseRecHandle			CloseRecHandle = NULL ;
lpfnIsOpen					IsOpen = NULL ;
lpfnIsBOF					IsBOF = NULL ;
lpfnIsEOF					IsEOF = NULL ;
lpfnMoveFirst				MoveFirst = NULL ;
lpfnMoveLast				MoveLast = NULL ;
lpfnMoveNext				MoveNext = NULL ;
lpfnMovePrev				MovePrev = NULL ;
lpfnGetFieldCount			GetFieldCount = NULL ;
lpfnGetRecordCount			GetRecordCount = NULL ;
lpfnGetFieldName			GetFieldName = NULL ;
lpfnGetFieldStringValue		GetFieldStringValue = NULL ;
lpfnGetFieldStringValueEx	GetFieldStringValueEx = NULL ;
lpfnGetFieldLongValue		GetFieldLongValue = NULL ;
lpfnGetFieldLongValueEx		GetFieldLongValueEx = NULL ;
lpfnGetFieldFloatValue		GetFieldFloatValue = NULL ;
lpfnGetFieldFloatValueEx	GetFieldFloatValueEx = NULL ;
lpfnGetFieldDoubleValue		GetFieldDoubleValue = NULL ;
lpfnGetFieldDoubleValueEx	GetFieldDoubleValueEx = NULL ;
lpfnLocate					Locate = NULL ;
lpfnExecuteSQL				ExecuteSQL = NULL ;
lpfnSendRequest             SendRequest = NULL ;
lpfnBroadData               BroadData = NULL ;

//ҵ��̬�����
BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//ʵʼ�������д��
extern "C" long __stdcall InitTaskDLL(TSSmartFunction *pFunction)
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

	return RET_OK;
}

//�ͷ������д��
extern "C" long __stdcall DestoryTaskDLL()
{
	return RET_OK;
}

long UpdateTaskStatus(long  nDatabase, long nTaskPlanID, long nStatus)
{
	char  sSQL[256];

	return ExecuteSQL(nDatabase, sSQL);
}


//*=================================================================================
//*ԭ��: long ReadSmartTask(TSSmartTaskPlan *pTaskPlan, long nCycle)
//*����: ��������
//*����: ��
//*����: ������ֵ����
//*˵��: DLL����.
//*=================================================================================
long ReadSmartTask(TSSmartTaskPlan *pTaskPlan, long nCycle)
{


	return RET_OK;
}

extern "C" long __stdcall UpdateTask(TSSmartTaskPlan *pTaskPlan)
{
	long nDatabase = GetDBHandle(DATABASE_TASK);
	if( nDatabase <= 0 )
	{
		printf("GetDBHandle() Faild! (%d)\n", nDatabase);
		return nDatabase;
	}

	long nRet = UpdateTaskStatus(nDatabase, pTaskPlan->nTaskPlanID, 0);

	FreeDBHandle(nDatabase);

	return nRet;
}

//*=================================================================================
//*ԭ��: long ReadTSRTask(TSSmartTaskPlan *pTaskPlan)
//*����: ���뾭��������
//*����: ��
//*����: ������ֵ����
//*˵��: DLL����.
//*=================================================================================
extern "C" long __stdcall ReadTSRTask(TSSmartTaskPlan *pTaskPlan)
{
	return ReadSmartTask(pTaskPlan, 0);
}

//*=================================================================================
//*ԭ��: long ReadTask(TSSmartTaskPlan *pTaskPlan)
//*����: ����һ������
//*����: ��
//*����: ������ֵ����
//*˵��: DLL����.
//*=================================================================================
extern "C" long __stdcall ReadTask(TSSmartTaskPlan *pTaskPlan)
{
	return ReadSmartTask(pTaskPlan, 1);
}

//*=================================================================================
//*ԭ��: long TaskReplace(TSSmartTaskPlan *pTaskPlan)
//*����: ����ִ����Ϻ�Ĵ���
//*����: ��
//*����: ������ֵ����
//*˵��: DLL����.
//*=================================================================================
extern "C" long __stdcall TaskReplace(TSSmartTaskPlan *pTaskPlan)
{


	return RET_OK;
}

//*=================================================================================
//*ԭ��: long GetTimeOutMap(TSSmartTimeOut **pBuffer, long *nCount)
//*����: �õ���ʱ�Ĳ�����
//*����: ��
//*����: ������ֵ����
//*˵��: DLL����.  �����ݿ��ж�����ʱ������
//*=================================================================================
extern "C" long __stdcall GetTimeOutMap(TSSmartTimeOut **pBuffer, long *nCount)
{


	return RET_OK;
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
	return RET_OK;
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
