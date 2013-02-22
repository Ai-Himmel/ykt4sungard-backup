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

//业务动态库入口
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

//实始化任务读写库
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

//释放任务读写库
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
//*原型: long ReadSmartTask(TSSmartTaskPlan *pTaskPlan, long nCycle)
//*功能: 读入任务
//*参数: 略
//*返回: 见返回值定义
//*说明: DLL导出.
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
//*原型: long ReadTSRTask(TSSmartTaskPlan *pTaskPlan)
//*功能: 读入经常性任务
//*参数: 略
//*返回: 见返回值定义
//*说明: DLL导出.
//*=================================================================================
extern "C" long __stdcall ReadTSRTask(TSSmartTaskPlan *pTaskPlan)
{
	return ReadSmartTask(pTaskPlan, 0);
}

//*=================================================================================
//*原型: long ReadTask(TSSmartTaskPlan *pTaskPlan)
//*功能: 读入一条任务
//*参数: 略
//*返回: 见返回值定义
//*说明: DLL导出.
//*=================================================================================
extern "C" long __stdcall ReadTask(TSSmartTaskPlan *pTaskPlan)
{
	return ReadSmartTask(pTaskPlan, 1);
}

//*=================================================================================
//*原型: long TaskReplace(TSSmartTaskPlan *pTaskPlan)
//*功能: 任务执行完毕后的处理
//*参数: 略
//*返回: 见返回值定义
//*说明: DLL导出.
//*=================================================================================
extern "C" long __stdcall TaskReplace(TSSmartTaskPlan *pTaskPlan)
{


	return RET_OK;
}

//*=================================================================================
//*原型: long GetTimeOutMap(TSSmartTimeOut **pBuffer, long *nCount)
//*功能: 得到超时的参数表
//*参数: 略
//*返回: 见返回值定义
//*说明: DLL导出.  从数据库中读出超时参数表
//*=================================================================================
extern "C" long __stdcall GetTimeOutMap(TSSmartTimeOut **pBuffer, long *nCount)
{


	return RET_OK;
}


//*=================================================================================
//*原型: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*功能: 初始化业务功能模块, 如装入数据/初始化数据
//*参数: 
//*      lpKeyBuffer, 授权字符串(保留)
//*      dwFlag, 业务功能的标志
//*返回: 
//*      RET_OK:  初始化成功
//*      RET_NG:  初始化失败
//*====================================================================================
extern "C" long __stdcall ReadSmartDocInfo(TSSmartDoc **pSmartDoc, long *nDocCount)
{
	return RET_OK;
}


//*=================================================================================
//*原型: long ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
//*功能: 释放设备档案信息
//*参数: 
//*      pSmartDoc -- 设备档案内存
//*返回: 
//*      =  RET_OK:  成功
//*      <> RET_OK:  失败
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
