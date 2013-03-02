// TSmartDoc.cpp: implementation of the TSmartDoc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartDoc.h"
#include "TSmartServer.h"
#include "tool.h"
#define MAX_TIMEOUT_TRY   10


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TSmartDocObj::TSmartDocObj()
{
	m_bShare	= false;
	m_nBusNo	= 0 ;
	m_hShare = NULL ;
	m_nTotal = 0 ;
	m_nBusTask = 0 ;

	m_hExecute = CreateEvent(NULL, TRUE, TRUE, NULL);
	m_hEvent   = CreateEvent(NULL, TRUE, FALSE, NULL);

	SetIOStatus(IO_Status_Free);
	SetPause(false);

	m_nIndex = 0 ;

	m_bEnable = true;

	m_bOpen = false ;
	m_nRecvTimeOut = 0 ;

	m_pTaskObj = NULL ;
	m_pServer = NULL ;
	m_bShare = false ;

	m_nRealIndex = 0 ;
	m_pRealTaskObj = NULL ;

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_nTerminate = 0 ;

	ZeroMemory(&m_ReadOver, sizeof(m_ReadOver));
	ZeroMemory(&m_WriteOver, sizeof(m_WriteOver));

	ZeroMemory(m_sBuffer, sizeof(m_sBuffer));
	iStack=0;
}

TSmartDocObj::TSmartDocObj(const TSSmartDoc *pDoc)
{
	m_bShare	= false;
	m_nBusNo	= 0 ;
	m_hShare = NULL ;
	m_nTotal = 0 ;
	m_nBusTask = 0 ;

	m_hExecute = CreateEvent(NULL, TRUE, TRUE, NULL);
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	SetIOStatus(IO_Status_Free);
	SetPause(false);

	m_bOpen = false ;
	m_bEnable = true;

	m_nIndex = 0 ;

	m_pTaskObj= &m_CurTaskObj;
	m_pServer = NULL ;
	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;
	ZeroMemory(&m_ReadOver, sizeof(m_ReadOver));
	ZeroMemory(&m_WriteOver, sizeof(m_WriteOver));

	AssignBy(pDoc);

	m_nTerminate = 0 ;

	ZeroMemory(m_sBuffer, sizeof(m_sBuffer));
}

TSmartDocObj::~TSmartDocObj()
{
	DestoryStack();
	ClearChildDoc();
	CloseHandle(m_hExecute);
	CloseHandle(m_hEvent);
}

void TSmartDocObj::SetReadOver(OVERLAPPED *pOver)
{
	m_ReadOver.hEvent       = pOver->hEvent ;
	m_ReadOver.Internal     = pOver->Internal;
	m_ReadOver.InternalHigh = pOver->InternalHigh ;
	m_ReadOver.Offset       = pOver->Offset;
	m_ReadOver.OffsetHigh   = pOver->OffsetHigh;
}

void TSmartDocObj::SetWriteOver(OVERLAPPED *pOver)
{
	m_WriteOver.hEvent       = pOver->hEvent ;
	m_WriteOver.Internal     = pOver->Internal;
	m_WriteOver.InternalHigh = pOver->InternalHigh ;
	m_WriteOver.Offset       = pOver->Offset;
	m_WriteOver.OffsetHigh   = pOver->OffsetHigh;
}

//*=================================================================================
//*原型: void TSmartDocObj::SetFirstShare()
//*功能: 第一个总线设备初始化
//*参数: 无
//*返回: 无
//*说明: 初始化总线上的设备公用的变量及事件
//*=================================================================================
void TSmartDocObj::SetFirstShare()
{
	m_pBus = this;

	m_bShare    = true;
	m_nBusNo    = 0 ;		//本设备是总线上的第几个设备(0..255)
	m_nBusTask  = 0;
	m_nTotal    = 1;
	m_hShare = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetEvent(m_hShare);
}

//*=================================================================================
//*原型: void TSmartDocObj::SetShare(TSmaretDocObj& Obj)
//*功能: 设置总线设备信息
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::SetShare(TSmartDocObj& Obj)
{
	m_pBus   = &Obj;
	m_pBus->m_nTotal++;
	m_bShare = true;
	m_nBusNo = m_pBus->m_nTotal-1; //本设备是总线上的第几个设备(0..255)
}

void TSmartDocObj::GetInfo(long nAuthNo, TSDocInfo *pDocInfo)
{
	if( nAuthNo == 0 )
	{
		pDocInfo->m_nAuthID = m_nAuthID;
		pDocInfo->m_nChild = m_ChildDoc.GetCount();

		if( IsExecuted() )
			pDocInfo->m_nStatus = 1;
		else if( IsOpen() )
			pDocInfo->m_nStatus = 0;
		else if( !IsOpen() )
			pDocInfo->m_nStatus = 2;
		else
			pDocInfo->m_nStatus = 9;


		if( m_pTaskObj != NULL )
			strcpy(pDocInfo->m_szTaskCode, m_pTaskObj->szTaskName);
		else
			strcpy(pDocInfo->m_szTaskCode, "无任务!");

		for(long i=0; i< pDocInfo->m_nChild; i++)
		{
			pDocInfo->Child[i].m_nAuthID = m_nAuthID;

			if( IsExecuted() )
				pDocInfo->Child[i].m_nStatus = 1;
			else if( IsOpen() )
				pDocInfo->Child[i].m_nStatus = 0;
			else if( !IsOpen() )
				pDocInfo->Child[i].m_nStatus = 2;
			else
				pDocInfo->Child[i].m_nStatus = 9;

			if( m_pTaskObj != NULL )
				strcpy(pDocInfo->Child[i].m_szTaskCode, m_pTaskObj->szTaskName);
			else
				strcpy(pDocInfo->Child[i].m_szTaskCode, "无任务!");
		}
	}
	else
	{
		for(long i=0; i< m_ChildDoc.GetCount(); i++)
		{
			TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
			if( pSmartDoc != NULL )
			{
				if( pSmartDoc->m_nAuthID == nAuthNo )
				{
					pDocInfo->m_nAuthID = m_nAuthID;
					pDocInfo->m_nChild = 0;

					if( IsExecuted() )
						pDocInfo->m_nStatus = 1;
					else if( IsOpen() )
						pDocInfo->m_nStatus = 0;
					else if( !IsOpen() )
						pDocInfo->m_nStatus = 2;
					else
						pDocInfo->m_nStatus = 9;

					if( m_pTaskObj != NULL )
						strcpy(pDocInfo->m_szTaskCode, m_pTaskObj->szTaskName);
					else
						strcpy(pDocInfo->m_szTaskCode, "无任务!");
				}
			}
		}
	}
}

//*=================================================================================
//*原型: void TSmartDocObj::DestoryStack()
//*功能: 删除堆栈中的任务
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::DestoryStack()
{
	/*
	printf("准备删除STACK\n");
	TSTaskStack *pTaskStack = NULL;
	while( (pTaskStack = (TSTaskStack *)m_Stack.Pop()) )
	{
		printf("删除堆栈中的任务!!!!\n");
		delete pTaskStack ;
	}

	m_Stack.Release();
	*/
}

void TSmartDocObj::SetPause(bool bBool)
{
	m_PauseLock.Lock();
	m_bPause = bBool ;
	m_PauseLock.Unlock();
}

bool TSmartDocObj::GetPause()
{
	bool bRet;
	m_PauseLock.Lock();
	bRet = m_bPause;
	m_PauseLock.Unlock();
	return bRet;
}


//*=================================================================================
//*原型: void TSmartDocObj::Clear()
//*功能: 清除结构成员
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::Clear()
{
	m_nFlow      = 0;
	m_nCardID    = 0;
	m_nInMoney   = 0;
	m_nOutMoney  = 0;
	m_nDealCount = 0;
}

//*=================================================================================
//*原型: void TSmartDocObj::Release()
//*功能: 删除本设备
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::Release()
{
	if( IsOpen() )
		Close();

	delete this;
}

//*=================================================================================
//*原型: void TSmartDocObj::ClearChildDoc()
//*功能: 清除子设备
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::ClearChildDoc()
{
	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pDoc = (TSSmartDoc*)m_ChildDoc[i];
		if( pDoc != NULL )
		{
			delete pDoc;
		}
	}
	m_ChildDoc.Clear();
}

//*=================================================================================
//*原型: long TSmartDocObj::GetPriority()
//*功能: 得到当前任务的优先级
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::GetPriority()
{
	if( m_pTaskObj )
		return m_pTaskObj->pTask[m_nIndex].nPriority;

	return -1;
}

//*=================================================================================
//*原型: void TSmartDocObj::AddChildDoc(TSSmartDoc *pSmartDoc)
//*功能: 加入到子设备中
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::AddChildDoc(TSSmartDoc *pSmartDoc)
{
	pSmartDoc->m_bEnable = true ;
	m_ChildDoc.Add(pSmartDoc);

	ZeroMemory(&pSmartDoc->DeviceInfo, sizeof(TSDeviceInfo));
	ConvertToDevice(pSmartDoc, &pSmartDoc->DeviceInfo);
}

long TSmartDocObj::GetChildDocCount()
{
	return m_ChildDoc.GetCount();
}

bool TSmartDocObj::IsChildDoc(long nAuthID)
{
	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
		if( pSmartDoc != NULL )
		{
			if( pSmartDoc->m_nAuthID == nAuthID )
			{
				return true;
			}
		}
	}

	return false;
}

bool TSmartDocObj::Enable(long nAuthID, bool bEnable)
{
	if( m_nAuthID == nAuthID )
	{
		m_bEnable = bEnable;
		return true;
	}

	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
		if( pSmartDoc != NULL )
		{
			if( pSmartDoc->m_nAuthID == nAuthID )
			{
				pSmartDoc->m_bEnable = bEnable;
				return true;
			}
		}
	}
	return false;
}

//*=================================================================================
//*原型: void StopChildDoc(long nAuthID)
//*功能: 停用子设备
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::StopChildDoc(long nAuthID)
{
	SetChildDocStatus(nAuthID, 5);
}

//*=================================================================================
//*原型: void TSmartDocObj::SetChildDocStatus(long nStatus)
//*功能: 设置子设备状态
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::SetChildDocStatus(long nAuthID, long nStatus)
{

}

//*=================================================================================
//*原型: void TSmartDocObj::AssignBy(const TSSmartDoc *pSmartDoc)
//*功能: 结构赋值
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::AssignBy(const TSSmartDoc *pSmartDoc)
{
	strcpy(m_szMacCode,  pSmartDoc->m_szMacCode );
	strcpy(m_szMacCard,  pSmartDoc->m_szMacCard );
	strcpy(m_szMacModle, pSmartDoc->m_szMacModle);
	strcpy(m_szMacType,  pSmartDoc->m_szMacType );
	strcpy(m_szOrgid,    pSmartDoc->m_szOrgid);

	m_nListMark = pSmartDoc->m_nListMark;
	m_nAuthID   = pSmartDoc->m_nAuthID;

	strcpy(m_szDeviceID, pSmartDoc->m_szDeviceID);
	strcpy(m_szRegister, pSmartDoc->m_szRegister);

	m_nMachineNo = pSmartDoc->m_nMachineNo ;

	strcpy(m_szVersion, pSmartDoc->m_szVersion);
	strcpy(m_szProgramver, pSmartDoc->m_szProgramver);
	strcpy(m_szPassword, pSmartDoc->m_szPassword);
	strcpy(m_szOprPasswd, pSmartDoc->m_szOprPasswd);

	m_nPwdswitch = pSmartDoc->m_nPwdswitch;
	m_nParentID = pSmartDoc->m_nParentID;
	m_nPortCount = pSmartDoc->m_nPortCount;
	m_nSMTPort = pSmartDoc->m_nSMTPort;

	strcpy(m_szPort, pSmartDoc->m_szPort);

	m_nBaudRate = pSmartDoc->m_nBaudRate;
	m_nConnType = pSmartDoc->m_nConnType;
	m_nCommMode = pSmartDoc->m_nCommMode;

	strcpy(m_szAddr, pSmartDoc->m_szAddr);

	m_nOnNet = pSmartDoc->m_nOnNet;
	m_nOnline = pSmartDoc->m_nOnline;
	m_nLevel = pSmartDoc->m_nLevel;

	strcpy(m_szLevelArray, pSmartDoc->m_szLevelArray);

	m_nStatus = pSmartDoc->m_nStatus;

	strcpy(m_szTableName, pSmartDoc->m_szTableName);

	m_wFlowNo = pSmartDoc->m_wFlowNo;
	m_wLastInvoiceNo = pSmartDoc->m_wLastInvoiceNo;
	strcpy(m_sLastDealTime, pSmartDoc->m_sLastDealTime);

	m_nBeginInvoice = pSmartDoc->m_nBeginInvoice;
	m_wSettleinvoice = pSmartDoc->m_wSettleinvoice;

	strcpy(m_sSettleTime, pSmartDoc->m_sSettleTime);

	m_wEndInvoice = pSmartDoc->m_wEndInvoice;

	strcpy(m_sBlackExpire, pSmartDoc->m_sBlackExpire);
	strcpy(m_sDownBlackTime, pSmartDoc->m_sDownBlackTime);

	m_nStartuse = pSmartDoc->m_nStartuse;
	m_nLostDeal = pSmartDoc->m_nLostDeal;
	m_nLostSettle = pSmartDoc->m_nLostSettle;

	strcpy(m_sBlackListVer, pSmartDoc->m_sBlackListVer);
	strcpy(m_sClockVer, pSmartDoc->m_sClockVer);
	strcpy(m_sNumberVer, pSmartDoc->m_sNumberVer);
	strcpy(m_sCommDateTime, pSmartDoc->m_sCommDateTime);

	strcpy(m_sWhiteList, pSmartDoc->m_sWhiteList);
	strcpy(m_sWorkMode, pSmartDoc->m_sWorkMode);
	m_nSwitch = pSmartDoc->m_nSwitch;
	strcpy(m_sBlockVer, pSmartDoc->m_sBlockVer);

	ZeroMemory(&m_DeviceInfo, sizeof(m_DeviceInfo));
	ConvertToDevice(this, &m_DeviceInfo);

	CopyMemory(&DeviceInfo, &m_DeviceInfo, sizeof(DeviceInfo));

	m_nFlow = pSmartDoc->m_nFlow;               //序号
	m_nCardID = pSmartDoc->m_nCardID;			//卡号
	m_nInMoney = pSmartDoc->m_nInMoney;         //入卡金额
	m_nOutMoney = pSmartDoc->m_nOutMoney;       //出卡金额
	m_nDealCount = pSmartDoc->m_nDealCount;		//交易笔数

	m_dwTryCount = pSmartDoc->m_dwTryCount ;
	m_dwSuccess = pSmartDoc->m_dwSuccess ;
	m_dwFaild = pSmartDoc->m_dwFaild ;
	m_dwLastTick = pSmartDoc->m_dwLastTick ;
	m_dwRecvTick = pSmartDoc->m_dwRecvTick ;
	m_dwMarkTick = pSmartDoc->m_dwMarkTick ;
	m_dwFileTick = pSmartDoc->m_dwFileTick ;
	m_dwDBTick = pSmartDoc->m_dwDBTick ;
	m_dwCollectTick = pSmartDoc->m_dwCollectTick ;

	m_nSignIn	= pSmartDoc->m_nSignIn ;
	strcpy(m_szSignInTime, pSmartDoc->m_szSignInTime);
	m_nDealLost	= pSmartDoc->m_nDealLost ;
	m_nJZLost	= pSmartDoc->m_nJZLost ;
	m_nInSuccess	= pSmartDoc->m_nInSuccess ;
	m_nInFaild	= pSmartDoc->m_nInFaild ;
	m_nInSuccessMoney	= pSmartDoc->m_nInSuccessMoney ;
	m_nInFaildMoney	= pSmartDoc->m_nInFaildMoney ;
	m_nCheckSuccess	= pSmartDoc->m_nCheckSuccess ;
	m_nCheckFaild	= pSmartDoc->m_nCheckFaild ;
	m_nCheckSuccessMoney	= pSmartDoc->m_nCheckSuccessMoney ;
	m_nCheckFaildMoney	= pSmartDoc->m_nCheckFaildMoney ;
	m_nBatchSuccess	= pSmartDoc->m_nBatchSuccess ;
	m_nBatchFaild	= pSmartDoc->m_nBatchFaild ;
	m_nBatchSuccessMoney	= pSmartDoc->m_nBatchSuccessMoney ;
	m_nBatchFaildMoney	= pSmartDoc->m_nBatchFaildMoney ;
	m_nDealNumber	= pSmartDoc->m_nDealNumber ;
	m_nTransMoney	= pSmartDoc->m_nTransMoney ;

	m_bEnable = pSmartDoc->m_bEnable;
}

//*=================================================================================
//*原型: bool TSmartDocObj::HaveHistoryTask()
//*功能: 是否有被中断的任务
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
bool TSmartDocObj::HaveHistoryTask()
{
	if(iStack)
		return false;
	else
		return true;
	//return m_Stack.IsEmpty();
}

//*=================================================================================
//*原型: void TSmartDocObj::Run()
//*功能: 执行各种任务
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::Run()
{
	while( !IsShutdown() )
	{
		DWORD dwResult = WaitForSingleObject(m_hEvent, 20);
		if( dwResult == WAIT_OBJECT_0 )
		{
			if( GetIOStatus() == IO_Status_Free )
			{
				SetIOStatus(IO_Status_Execute);
				auto_lock lock(m_ExecLock);
				TaskFinished(ExecuteTask(m_pTaskObj, m_nIndex));
			}
		}
	}
}

//*=================================================================================
//*原型: bool TSmartDocObj::AddToTaskStack(TSmartTaskObj *pObj, long nIndex)
//*功能: 加入一个任务到队列中
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
bool TSmartDocObj::AddToTaskStack(TSmartTaskObj *pObj, long nIndex)
{
	if(pObj->nRepeatTime!=0||pObj->nRepeatTimes!=0)
		return false;
	return false;
	printf("增加任务到任务队列中!!!!\n");
	TSTaskStack  *pTaskStack = new TSTaskStack;
	if( pTaskStack != NULL )
	{
		pTaskStack->pTaskObj = pObj ;
		pTaskStack->nIndex = nIndex;

		if( m_Stack.Push(pTaskStack) >= 0 )
		{
			return true;
		}
		else
		{
			delete pTaskStack;
		}
	}
	return false;
}

//*=================================================================================
//*原型: bool TSmartDocObj::Execute(TSmartTaskObj *pObj, long nIndex)
//*功能: 投递一个任
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
bool TSmartDocObj::Execute(TSmartTaskObj *pObj, long nIndex)
{
	static int iReal = 0 ;
	//防止重入
	ASSERT(pObj);
	auto_lock lock(m_EventLock);
	if( WaitForSingleObject(m_hExecute, 5) != WAIT_OBJECT_0 )
	{
	/*
		Sleep(100);
		if( WaitForSingleObject(m_hExecute, 50) != WAIT_OBJECT_0 )
		{
			//printf("投递任务时,服务忙..............................\n");
			return false;
		}	
		*/
			return false;
	}
	/*
	if( WaitForSingleObject(m_hExecute, 0) != WAIT_OBJECT_0 )
	{
		if( WaitForSingleObject(m_hExecute, 100) != WAIT_OBJECT_0 )
		{
			return false;
		}
		Pause();
	}
	*/
	ResetEvent(m_hExecute);
	if( GetIOStatus() == IO_Status_Free )
	{
		Reset();
		SetPause(false);
		memcpy(&m_CurTaskObj,pObj,sizeof(TSmartTaskObj));
		m_pTaskObj = &m_CurTaskObj;
		m_nIndex = nIndex ;

		if( !IsBus() )
			Sleep(100);
		if(SetEvent(m_hEvent)==0)
		{
			printf("设置设备线程启动事件失败................................");
			return false;
		}
		if( !iReal )
		{
			iReal = 1 ;
			m_nRealIndex   = nIndex ;
			m_pRealTaskObj = pObj ;
		}
		return true;
	}
	SetEvent(m_hExecute);
	return false;
}

//*=================================================================================
//*原型: void TSmartDocObj::OpenDevice()
//*功能: 重新打开一个设备
//*参数: 无
//*返回: 无
//*说明: 当设备通讯错误次数达MAX_TIMEOUT_TRY时, 或
//       设备被关闭了, 才重新打开
//*=================================================================================
void TSmartDocObj::OpenDevice()
{
	Close();

	Sleep(2000);

	m_nRecvTimeOut = 0 ;
	Open();

	if( IsBus() )
		m_pServer->AssignBusHandle(this);
}


//*=================================================================================
//*原型: void ExecuteTask(TSmartTaskObj *pObj, long nIndex)
//*功能: 执行一个任务
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::AddOrUpdateDoc(TSmartTaskObj *pObj,long nIndex)
{

#if 0
	struct TSSmartDoc *Doc=NULL;
	TList  m_list;
	Doc = (struct TSSmartDoc*)pObj->pTask[nIndex].pData;

	if( pObj->pTask[nIndex].szMemo[0]=='0' ) //参数无效
	{
		return RET_OK;
	}
	m_list.Add((void*)Doc);
	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
		if( pSmartDoc != NULL )
		{
			if( (pSmartDoc->m_nSMTPort == Doc->m_nSMTPort) && (pSmartDoc->m_nParentID == Doc->m_nParentID) )
			{
			     m_ChildDoc.Delete(i);
				m_ChildDoc.Insert(i,(void*)Doc);
				return RET_OK;
			}
		}
	}

	for(i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
		if( pSmartDoc != NULL )
		{
			if( pSmartDoc->m_nParentID == Doc->m_nParentID )
			{
				m_ChildDoc.Add((void*)Doc);
				m_nTotal++;
				return RET_OK;
			}
		}
	}
	pObj->szMemo[0]='0';
#endif
	return RET_OK;

}

//*=================================================================================
//*原型: void ExecuteTask(TSmartTaskObj *pObj, long nIndex)
//*功能: 执行一个任务
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::ExecuteTask(TSmartTaskObj *pObj, long nIndex)
{
	TSSmartDocEx  DocEx;
	int  nRet =  RET_OK ;
	bool bBroad = false;
	char	errmsg[1024];
	BYTE	authid[18];

	memset(authid, 0x00, sizeof authid);
	memset(errmsg, 0x00, sizeof errmsg);
	memset(&DocEx, 0x00,sizeof DocEx);

	try
	{
		//生成设备级别档案
		nRet=CreateDocArray(&DocEx);
		if(nRet)
		{
			//printf("CreateDocArray err\n");
			return nRet;
		}
		char  strText[1024];
		memset(strText, 0x00, sizeof strText);
		if( strcmp(m_pTaskObj->pTask[m_nIndex].szTaskCode, "01") && nRet == RET_OK )
		{
			sprintf(strText, "设备%08X被分派执行任务. 任务代码:%s.", DocEx.pChildDoc[DocEx.nPortNo]->m_nAuthID, pObj->pTask[nIndex].szTaskCode);
			WriteLog(strText);
		}

		WaitBusResource();

		if( IsBus() && !strcmp(m_szMacCode, "0224") )
		{
			Sleep(1000);
		}

		static int iTick = 0 ;
		pObj->SetBeginFlag(nIndex);
		if( !IsOpen() )
		{
			m_nRecvTimeOut = 0 ;
			OpenDevice();
		}
		else if( m_nRecvTimeOut >= MAX_TIMEOUT_TRY )
		{
			m_nRecvTimeOut = 0 ;
			OpenDevice();
		}

		//LPort签到
		if( !strcmp(m_szMacCode, "5301") )
		{
			m_nSignIn = 1 ;
		}
		m_nTerminate  = 0 ;		
 		DocEx.pChildDoc[DocEx.nPortNo]->m_nTerminate = 0 ;
		//生成第一个命令缓冲区
		nRet = RSCreateTaskBuffer(&DocEx, &pObj->pTask[m_nIndex], &m_CmdBuffer);
		long  nCreateResult = nRet;
		if( nRet != RET_OK && nRet != RET_ERRORCALL )
		{
			if( nRet == RET_CONTINUE )
			{
				return ProcessRequest(true, &m_CmdBuffer);
			}
			else if( nRet == RET_BROADCAST )
			{
				bBroad = true;
			}
			else
			{
				char  sBuffer[256];
				char  sText[512];
				GetResultMessage(nRet, sBuffer);
				sprintf(sText, "任务不能执行!错误代码:%d. 错误消息:%s", nRet, sBuffer);
				return nRet;
			}
		}

		long nSleep = 0;
		long nTry   = 0;
		if( DocEx.pChildDoc[DocEx.nPortNo]->m_nLevel > 0 )
		{
			nSleep = (DocEx.pChildDoc[DocEx.nPortNo]->m_nLevel)*180 ;
		}

		while( nTry++ < 3 )
		{
			if( bBroad )
			{
				m_CmdBuffer.m_nCmdType = SMART_CMD_SEND;
				nRet = SendRecv(&m_CmdBuffer, nSleep);
				break;
			}
			else
			{
				m_CmdBuffer.m_nCmdType = SMART_CMD_SENDRECV;
				nRet = SendRecv(&m_CmdBuffer, nSleep);
			}
			if( nRet != RET_RECV_TIMEOUT    &&
				nRet != RET_RECV_C1_TIMEOUT &&
				nRet != RET_RECV_C2_TIMEOUT )
				break;
			else
			{
				m_nRecvTimeOut++;
			}
		}

		if( nRet == RET_OK )
		{
			return ProcessRequest(bBroad, &m_CmdBuffer);
		}
		else
		{
			if( bBroad )
			{
				return ProcessRequest(bBroad, &m_CmdBuffer);
			}
			else if( nCreateResult == RET_ERRORCALL )
			{
				return ProcessRequest(true, NULL);
			}
			else
				return nRet;
		}
	}
	catch(TException& e)
	{
		
		sprintf(errmsg,"----(TException)执行任务失败 %s,[LPORT=%.8X::任务名:%s::任务代码%s::线程ID=%ld]",(char*)e.GetText(),m_nAuthID,pObj->szTaskName,pObj->pTask[nIndex].szTaskCode,(DWORD)this->m_hThread);
		m_pServer->OnDocError(this,errmsg);
		WriteTaskLog(errmsg);
		Sleep(1000);
		return RET_SYSERROR; //update by dengjun 20051126
	}
	catch(...)
	{
		sprintf(errmsg,"----(...)执行任务失败 [LPORT=%.8X::任务名:%s::任务代码%s::线程ID=%ld]",m_nAuthID,pObj->szTaskName,pObj->pTask[nIndex].szTaskCode,(DWORD)this->m_hThread);
		m_pServer->OnDocError(this, errmsg);
		WriteTaskLog(errmsg);
		Sleep(1000);
		return RET_SYSERROR;  //update by dengjun 20051126
	}
	return RET_OK;
}


//*=================================================================================
//*原型: long SendRecv(TCmdBuffer *pCmdBuffer, long nSleep)
//*功能: 发送与接收一个命令包
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::SendRecv(TCmdBuffer *pCmdBuffer, long nSleep)
{
	long nResult = SendCmdBuffer(pCmdBuffer);
	if( nResult == RET_OK )
	{
		//如果没有接收操作, 则任务完成
		if( m_CmdBuffer.m_nCmdType == SMART_CMD_SEND )
		{
			return RET_OK;
		}

		if( nSleep < 100 )  Sleep(100);
		else				Sleep(nSleep);

		pCmdBuffer->ZeroInBuffer();

		nResult = RecvCmdBuffer(pCmdBuffer);
		if( nResult == RET_OK )
		{
			Sleep(80);
			return RET_OK;
		}
	}
	return nResult;
}

void TSmartDocObj::WaitBusResource()
{
	if( !IsBus() )
		return ;

	while( !IsShutdown() )
	{
		//等待总线上另一个设备执行完毕
		if( WaitForSingleObject(m_pBus->m_hShare, 2000) == WAIT_OBJECT_0 )
		{
			m_pBus->LockBus();
			//轮到本设备执行
			if( m_pBus->m_nBusTask == m_nBusNo )
			{
				ResetEvent(m_pBus->m_hShare);
				m_pBus->UnLockBus();
				break;
			}
			m_pBus->UnLockBus();
		}
		//add by zhm
		else
		{
			printf("Wait %d Bus Timeout!\n",m_pBus);
		}
	}
}

void TSmartDocObj::FreeBusResource()
{
	if( !IsBus() )
		return ;

	m_pBus->LockBus();
	m_pBus->m_nBusTask++;
	if( m_pBus->m_nBusTask >= m_pBus->m_nTotal )
		m_pBus->m_nBusTask = 0 ;

	SetEvent(m_pBus->m_hShare);
	m_pBus->UnLockBus();
}


void TSmartDocObj::LockBus()
{
	m_BusLock.Lock();
}

void TSmartDocObj::UnLockBus()
{
	m_BusLock.Unlock();
}

//*=================================================================================
//*原型: void TaskFinished(long nResult)
//*功能: 单个任务行完毕后的处理
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::TaskFinished(long nResult)
{
	SetIOStatus(IO_Status_Finished);
	ResetEvent(m_hEvent);
//	if (!m_pTaskObj)
//		return;
	m_pTaskObj->SetTaskResult(m_nIndex, nResult, m_nTerminate);

	//将本任务压入任务stack
	if( m_nTerminate == 2 )
	{
//		ReportLog("将本任务压入任务stack!\n");
		Pause();
		FreeBusResource();
		return ;
	}

	m_nTerminate = 0 ;

	//总的任务已结束
	if( m_pTaskObj->IsTaskFinished() )
	{
		ReportLog("任务:%s (%ld) 已经结束!", m_pTaskObj->szTaskName, m_pTaskObj->nTaskPlanID);
		printf("任务:%s (%ld) 已经结束!", m_pTaskObj->szTaskName, m_pTaskObj->nTaskPlanID);
		m_pServer->FinishedTask(this, m_pTaskObj, m_nIndex);
	}

	//从头继续执行
	if( m_pTaskObj->IsContinue(m_nIndex) && !GetPause() )
	{
		long nIndex = m_pTaskObj->GetNextTask(this);

		SetEvent(m_hExecute);
		SetIOStatus(IO_Status_Free);

		if( nIndex >= 0 && !GetPause() )
		{
			FreeBusResource();
			m_nIndex = nIndex ;
			Execute(m_pTaskObj, nIndex);
		}
		else
		{
			if( !HaveHistoryTask() )
			{
				FreeBusResource();
				Continue();
			}
			else
			{
				FreeBusResource();
				SetIOStatus(IO_Status_Free);
				SetEvent(m_hExecute);

			//	if( m_pRealTaskObj && m_nRealIndex >= 0 )
			//		Execute(m_pRealTaskObj, m_nRealIndex);
			}
		}
	}
	else
	{
		//有被中断的任务
		bool bHave = HaveHistoryTask();
		bool bPex = GetPause();

		if( !bHave )
		{
			//继续执行
			FreeBusResource();
			Continue();
		}
		else
		{
			SetIOStatus(IO_Status_Free);
			SetEvent(m_hExecute);
			FreeBusResource();

		//	if( m_pRealTaskObj && m_nRealIndex >= 0 )
		//		Execute(m_pRealTaskObj, m_nRealIndex);
		}
	}
}

//*=================================================================================
//*原型: long SendCmdBuffer(TCmdBuffer *pCmdBuffer)
//*功能: 发送指令
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::SendCmdBuffer(TCmdBuffer *pCmdBuffer)
{
/*
// dengjunTest
BYTE ucSndData[256];
Tool  cTool;
memset(ucSndData,0x00,sizeof ucSndData);
cTool.BcdToAsc(m_CmdBuffer.pBuffer,m_CmdBuffer.nCmdSize,ucSndData);
printf("发送数据--------->%s",(char*)ucSndData);	
*/

	WaitingWrite(pCmdBuffer->nTimeOut1);	
	if( PostSend((char*)m_CmdBuffer.pBuffer, m_CmdBuffer.nCmdSize, 1000) == m_CmdBuffer.nCmdSize )
	{
		return RET_OK;
	}
	else  //Add by dengjun 20051128 数据发送不出去,一般来说,连接已经有问题,则重连,
		  //这样可以防止前置与LPORT有时无法连上
	{
		OpenDevice();
		m_nRecvTimeOut=0;
		return RET_SEND_ERROR;
	}
}

//*=================================================================================
//*原型: long TSmartDocObj::RecvCmdBuffer(TCmdBuffer *pCmdBuffer)
//*功能: 接收返回的数据包
//*参数: 略
//*返回: 无
//*说明: 终端机基类c
//*=================================================================================
long TSmartDocObj::RecvCmdBuffer(TCmdBuffer *pCmdBuffer)
{
	long   nRecvLen = 1 ;
	long   nRet = RET_OK ;
	DWORD  len=0;
	int    nlen=0;
	
	pCmdBuffer->m_nRecvBytes = 0;
	pCmdBuffer->ZeroInBuffer();
	Sleep(150);
	if(WaitRecv(m_sBuffer,1,4000) <= 0)
	{
		ReportLog("接收终端%.8X数据超时,未接到任何数据\n",m_nAuthID); //add by lina 20050314
		return RET_RECV_TIMEOUT;
	} 
	
	//读包头起始符
	pCmdBuffer->m_nTick1 = GetTickCount();
	while( true  )
	{
		if( pCmdBuffer->IsTimeOutC1() )
		{
			ReportLog("接收%.8X 起始符超时",m_nAuthID);
			return RET_RECV_C1_TIMEOUT;
		}		
		m_nReadBytes = 0 ;
		memset(m_sBuffer, 0, sizeof(m_sBuffer));

		if( PostRecv(m_sBuffer, nRecvLen, 50) > 0 )
		{
			memcpy(pCmdBuffer->m_pRetBuffer, m_sBuffer, m_nReadBytes);
			pCmdBuffer->m_nRecvBytes = m_nReadBytes;

			if( pCmdBuffer->IsValidHead() )
			{
				break;
			}
		}
	}

	//读包头
	nRecvLen = SmartProtocol.nLenOffset - pCmdBuffer->m_nRecvBytes + 1 ;
	if( nRecvLen > 0 )
	{
		pCmdBuffer->m_nTick2 = GetTickCount();

		while( nRecvLen > 0 )
		{
			m_nReadBytes = 0 ;
			memset(m_sBuffer, 0, sizeof(m_sBuffer));

			if( pCmdBuffer->IsTimeOutC2() )
			{
				ReportLog("----未收到%.8X的数据包!!!!",m_nAuthID);
				Sleep(100);
				return RET_RECV_C2_TIMEOUT;
			}

			if( PostRecv(m_sBuffer, nRecvLen, 500) > 0 )
			{
				memcpy(pCmdBuffer->m_pRetBuffer+pCmdBuffer->m_nRecvBytes, m_sBuffer, m_nReadBytes);
				pCmdBuffer->m_nRecvBytes += m_nReadBytes;
				nRecvLen -= m_nReadBytes ;
			}
		}
	}

	//包长度非法
	nRecvLen  = pCmdBuffer->GetPackSize() - (pCmdBuffer->m_nRecvBytes - 4 ) + 3 ;
	if( nRecvLen <= 0 )
	{
		ReportLog("----未收到%.8X的数据包!!!!",m_nAuthID);
		Sleep(100);
		return RET_DATALENGTH_ERROR;
	}

	//读数据
	pCmdBuffer->m_nTick2 = GetTickCount();
	while( nRecvLen > 0 )
	{
		m_nReadBytes = 0 ;
		memset(m_sBuffer, 0, sizeof(m_sBuffer));

		if( pCmdBuffer->IsTimeOutC2() )
		{
			ReportLog("接收%.8XC2----超时\n",m_nAuthID);
			Sleep(100);
			return RET_RECV_C2_TIMEOUT;
		}

		if( PostRecv(m_sBuffer, nRecvLen, 500) > 0 )
		{
			memcpy(pCmdBuffer->m_pRetBuffer+pCmdBuffer->m_nRecvBytes, m_sBuffer, m_nReadBytes);
			pCmdBuffer->m_nRecvBytes += m_nReadBytes;
			nRecvLen -= m_nReadBytes ;
		}
	}	

	printf("收到%.8X完整数据包\n",m_nAuthID);
	return RET_OK;
}

//*=================================================================================
//*原型: long TSmartDocObj::ProcessRequest(TCmdBuffer *pCmdBuffer)
//*功能: 处理请求
//*参数: 无
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::ProcessRequest(bool bBroad, TCmdBuffer *pCmdBuffer)
{
	char errmsg[1024];
	BYTE authid[18];

	memset(errmsg, 0x00, sizeof errmsg);
	memset(authid, 0x00, sizeof authid);

	if( !bBroad )
	{
		pCmdBuffer->CopyOut(pCmdBuffer->m_nRecvBytes);

		if( !pCmdBuffer->CheckInPacket() )
		{
			ReportLog("发送终端的数据包无效.................................\n");
			return RET_DATACRC_ERROR;
		}
	}

	//add by dengjun 0923
	if (!m_pTaskObj)
	{
		ReportLog(".............................................任务无效%ld\n",RET_TASKISVAILD);
		return RET_TASKISVAILD;
	}
	if( !pCmdBuffer) 
	{
		ReportLog("接收到的数据包无效%ld\n",RET_VALIDPACKET);
		return RET_VALIDPACKET;
	}
	long nRet = RET_OK ;
	int ret;
	TSSmartDocEx  DocEx;
	memset(&DocEx,0x00,sizeof DocEx);
	ret=CreateDocArray(&DocEx);
	if(ret)
	{
		ReportLog("...............................CreateDocArray err!\n");
		return -1;
	}

	try
	{
		char strRet[256] = "成功";
		char strText[1024];

		memset(strText,0x00,sizeof strText);
		SetIOStatus(IO_Status_ExecuteCall);
		ASSERT(m_pTaskObj);
		long nRet = RSSmartTaskProcess(&DocEx, &m_pTaskObj->pTask[m_nIndex], pCmdBuffer);
		if( nRet != RET_NG )
		{
			GetResultMessage(nRet, strRet);
			sprintf(strText, "%ld %s %s %ld %s",
				DocEx.pChildDoc[DocEx.nPortNo]->m_nAuthID,
				m_pTaskObj->pTask[m_nIndex].szTaskCode,
				m_pTaskObj->pTask[m_nIndex].szRunTime,
				nRet,
				strRet);
			char szLog[1024];
			sprintf(szLog, "设备:%08X, 执行任务<任务:%s(%d), 任务代码:%s>返回! 返回结果(%d):%s",
				m_nAuthID, m_pTaskObj->szTaskName, m_pTaskObj->nTaskPlanID,
				m_pTaskObj->pTask[m_nIndex].szTaskCode, nRet, strRet);
			WriteLog(szLog);
		}
		else
		{
			Sleep(50);
		}
		m_nTerminate = DocEx.pChildDoc[DocEx.nPortNo]->m_nTerminate ;
	}
	catch(TException& e)
	{
		sprintf(errmsg,"----(ProcessRequest(TException))业务层处理数据失败![LPORT=%.8X::任务名:%s::任务代码%s::线程ID=%ld]",m_nAuthID,m_pTaskObj->szTaskName,m_pTaskObj->pTask[m_nIndex].szTaskCode,(DWORD)this->m_hThread);
		WriteTaskLog(errmsg);
		WriteTaskLog((char*)e.GetText());
		ReportLog(errmsg);
	}
	catch(...)
	{
		sprintf(errmsg,"----(ProcessRequest(...))业务层处理数据失败![LPORT=%.8X::任务名:%s::任务代码%s::线程ID=%ld,DocEx.nPortNo=%ld,nRet=%ld]",m_nAuthID,m_pTaskObj->szTaskName,m_pTaskObj->pTask[m_nIndex].szTaskCode,(DWORD)this->m_hThread,DocEx.nPortNo,nRet);
		WriteTaskLog(errmsg);
		ReportLog(errmsg);	
	}
	return nRet;
}

//*=================================================================================
//*原型: void TSmartDocObj::Pause()
//*功能: 将当前设备正在执行的任务中断, 并保存到stack中
//*参数: 无
//*返回: 无
//*说明: 暂停任务的执行
//*=================================================================================
void TSmartDocObj::Pause()
{
	long l;
	SetPause(true);
	ResetEvent(m_hEvent);
//	printf("------等待任务执行完毕 m_nTerminate= %d\n",m_nTerminate);
	//等待任务执行完毕
	//为保证系统健状性, 只能优雅地等待本次任务结束
	if( m_nTerminate == 2 )
	{

		m_nTerminate = 0 ;
		SetIOStatus(IO_Status_Free);
	}
	else
	{
		//每隔100毫秒检测任务是否结束,
		l = 0;
		while( IsExecuted() )
		{
			//每隔50毫秒检测任务是否结束,
			//printf("如果有运行时间特长的任务, 则需等待很久....\n");
			Sleep(100);
			l = l+1;
			if(l == 20)
			{
				Reset();
			}
		}
		if( l == 20 )
		{
			ReportLog("原有任务已经被停下,开始执行新的任务\n");
		}
		else
		{
			ReportLog("原有任务已经执行成功,新的任务开始执行\n");
		}
	}

	//将当前任务入栈
	if( m_pTaskObj != NULL )
	{
		m_pTaskObj->pTask[m_nIndex].nTerminate = 0 ;
		m_nTerminate = 0 ;
/*
		TSTaskStack  *pTaskStack = new TSTaskStack;
		pTaskStack->pTaskObj = m_pTaskObj ;
		pTaskStack->nIndex = m_nIndex;
		if( m_Stack.Push(pTaskStack) < 0 )
		{
			delete pTaskStack;
			WriteLog("任务入栈失败!");
		}
*/
		if(m_pTaskObj->nRepeatTime==0&&m_pTaskObj->nRepeatTimes==0)
			iStack++;
	}

//	m_pTaskObj = NULL ;
	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;
	m_nIndex = 0 ;

	SetEvent(m_hExecute);
	SetPause(false);
	SetIOStatus(IO_Status_Free);
}

//*=================================================================================
//*原型: void TSmartDocObj::Continue()
//*功能: 继续执行一个任务
//*参数: 无
//*返回: 无
//*说明: 从本设备堆栈中得到暂停的任务, 并且执行
//*=================================================================================
void TSmartDocObj::Continue()
{

//	TSTaskStack *pTaskStack = (TSTaskStack *)m_Stack.Pop();
//	if( pTaskStack != NULL )
	TSmartServer *pServer = (TSmartServer*)GetServer();
	if(iStack)
	{
		iStack--;
		SetIOStatus(IO_Status_Free);
		m_pTaskObj=&m_CurTaskObj;
		m_nIndex = m_nRealIndex;
//		delete pTaskStack ;

		SetEvent(m_hExecute);
		ASSERT(m_pTaskObj);
		Execute(m_pTaskObj, m_nIndex);
	}
	else
	{
//		m_pTaskObj = NULL ;
		m_nIndex = 0 ;
		SetIOStatus(IO_Status_Free);
		SetEvent(m_hExecute);
	}
}

//*=================================================================================
//*原型: void TSmartDocObj::ConvertToDevice(TSSmartDoc *pDoc, TSDeviceInfo *pDeviceInfo)
//*功能: 将设备档案结构转为设备打包信息结构
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::ConvertToDevice(TSSmartDoc *pDoc, TSDeviceInfo *pDeviceInfo)
{
	ZeroMemory(pDeviceInfo, sizeof(TSDeviceInfo));

	pDeviceInfo->nAuthID = pDoc->m_nAuthID;          //机器授权号
	pDeviceInfo->nHardware= atoi(pDoc->m_szMacCode); //硬件类型

	strcpy(pDeviceInfo->sVersion, pDoc->m_szVersion); //硬件版本号

	strcpy(pDeviceInfo->sRegNo, pDoc->m_szRegister);

	pDeviceInfo->nAddr = pDoc->m_nMachineNo ;   //机器机号(0-255) 0表示广播通讯
	pDeviceInfo->nNetPar = 0;                   //网络结构: 直连, 星形, 总线
	pDeviceInfo->nLevel = pDoc->m_nLevel;		//终端设备所连接的数据服务器的级别数

	memcpy(pDeviceInfo->sLevelArray, pDoc->m_szLevelArray, sizeof(pDeviceInfo->sLevelArray));//级联级别

	pDeviceInfo->nTotalNo = pDoc->m_nPortCount;   //终端机总数量
	pDeviceInfo->nPort = pDoc->m_nSMTPort;        //星型当前通讯端口 总线当前通讯机数组编号
	pDeviceInfo->nNoReponseTime = 0;        //终端无反应次数
}

void TSmartDocObj::Start()
{
	TThread::Start();
}

//*=================================================================================
//*原型: void TSmartDocObj::CreateDocArray(TSSmartDocEx *pDocEx)
//*功能: 创建DocArray结构
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
int TSmartDocObj::CreateDocArray(TSSmartDocEx *pDocEx)
{
	//printf("pDocEx->nChildDoc == %d\n",m_ChildDoc.GetCount());
//	TSmartServer *pServer = (TSmartServer*)GetServer();
	if(m_pTaskObj==NULL)
		m_pTaskObj=&m_CurTaskObj;
	ASSERT(m_pTaskObj);
	ASSERT(pDocEx);
	if( m_pTaskObj->pTask[m_nIndex].nAuthID == m_nAuthID )
	{
		pDocEx->nPortNo = 0 ;
		pDocEx->nNetPar = 1 ;
		/*if(m_ChildDoc.GetCount() == 0)
		{
			pDocEx->nChildDoc = 1;
			m_ChildDoc.Add(pDocEx);
		}
		else*/
			//pDocEx->nChildDoc+=1;
		pDocEx->nChildDoc = m_ChildDoc.GetCount()+1;

		//printf("m_pTaskObj->pTask[m_nIndex].nAuthID == %X  pDocEx->nChildDoc = %d \n",m_nAuthID,pDocEx->nChildDoc);
		pDocEx->pDeviceInfo = &m_DeviceInfo;
		pDocEx->pChildDoc[0] = this ;

		for(long i=1; i<= m_ChildDoc.GetCount(); i++)
			pDocEx->pChildDoc[i] = (TSSmartDoc*)m_ChildDoc[i-1];
		return 0;
	}
	else
	{
		for(long i=0; i< m_ChildDoc.GetCount(); i++)
		{
			TSSmartDoc *pDoc = (TSSmartDoc*)m_ChildDoc[i] ;
			ASSERT(pDoc);
			if( pDoc && pDoc->m_nAuthID == m_pTaskObj->pTask[m_nIndex].nAuthID )
			{
				pDocEx->nPortNo = 0 ;
				pDocEx->nNetPar = 1 ;
				pDocEx->nChildDoc = 1;
				pDocEx->pDeviceInfo = &pDoc->DeviceInfo;
				pDocEx->pChildDoc[0] = pDoc ;
				return 0;
			}
		}
	}
	return 1;
}

//*=================================================================================
//*原型: void TSmartDocObj::SetOpenFlag(bool bBool)
//*功能: 设备设备打开的状态
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::SetOpenFlag(bool bBool)
{
	m_bOpen = bBool ;
}

//*=================================================================================
//*原型: long SendRequest(TSCmdBuffer *pCmdBuffer)
//*功能: 发送单笔的请求
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::SendRequest(TCmdBuffer *pCmdBuffer)
{
/*	if( GetPause() )
		return RET_TERMINATE;*/

	if( GetIOStatus() != IO_Status_ExecuteCall )
	{
		return RET_PARAMETER_ERROR1;
	}

	SetIOStatus(IO_Status_ExecuteApi);
	long nResult = SendCmdBuffer(pCmdBuffer);
	if( nResult != RET_OK )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return nResult ;
	}

	nResult = RecvCmdBuffer(pCmdBuffer);
	if( nResult != RET_OK )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return nResult ;
	}

/*	if( GetPause() )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return RET_TERMINATE;
	}
*/
	pCmdBuffer->CopyOut(pCmdBuffer->m_nRecvBytes);
	SetIOStatus(IO_Status_ExecuteCall);

	return RET_OK;
}


long TSmartDocObj::DebugSendRequest(TCmdBuffer *pCmdBuffer)
{
/*	if( GetPause() )
		return RET_TERMINATE;*/

//	if( GetIOStatus() != IO_Status_ExecuteCall )
//		return RET_PARAMETER_ERROR1;

	SetIOStatus(IO_Status_ExecuteApi);

	long nResult = SendCmdBuffer(pCmdBuffer);
	if( nResult != RET_OK )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return nResult ;
	}

	nResult = RecvCmdBuffer(pCmdBuffer);
	if( nResult != RET_OK )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return nResult ;
	}

/*	if( GetPause() )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return RET_TERMINATE;
	}
*/
	pCmdBuffer->CopyOut(pCmdBuffer->m_nRecvBytes);
	SetIOStatus(IO_Status_ExecuteCall);

	return RET_OK;
}
//*=================================================================================
//*原型: long TSmartDocObj::GetIOStatus()
//*功能: 得到设备的当前状态
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
long TSmartDocObj::GetIOStatus()
{
	m_StatusLock.Lock();
	long n = m_IOStatus;
	m_StatusLock.Unlock();

	return n ;
}

//*=================================================================================
//*原型: void TSmartDocObj::SetIOStatus(long nStatus)
//*功能: 设置设备的当前状态
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
void TSmartDocObj::SetIOStatus(long nStatus)
{
	m_StatusLock.Lock();
	m_IOStatus = nStatus ;
	m_StatusLock.Unlock();
}

//*=================================================================================
//*原型: bool TSmartDocObj::IsExecuted()
//*功能: 是否有忙的状态
//*参数: 略
//*返回: 无
//*说明: 终端机基类
//*=================================================================================
bool TSmartDocObj::IsExecuted()
{
	if( GetIOStatus() == IO_Status_Execute ||
		GetIOStatus() == IO_Status_ExecuteCall ||
		GetIOStatus() == IO_Status_ExecuteApi ||
		GetIOStatus() == IO_Status_Finished )
	{
		return true;
	}

	return false;
}

bool TSmartDocObj::IsWaitExecute()
{
	if( GetIOStatus() == IO_Status_ExecuteCall ||
		GetIOStatus() == IO_Status_ExecuteApi )
		return true;
	return false;
}

bool TSmartDocObj::IsBus() const
{
	return m_bShare;
}

//是否打开
bool TSmartDocObj::IsOpen() const
{
	return m_bOpen;
}

//*=================================================================================
//*原型: bool TSocketSmartDocObj::Reset()
//*功能: 复位链路
//*参数: 略
//*返回: 无
//*说明: 套接字设备
//*=================================================================================
void TSmartDocObj::Reset()
{
	SetIOStatus(IO_Status_Free);

//	m_pTaskObj = NULL ;
	m_pTaskObj=&m_CurTaskObj;
	m_nIndex = 0 ;

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_ReadOver.Internal = 0 ;
	m_ReadOver.InternalHigh = 0 ;
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;
	ResetEvent(m_ReadOver.hEvent);

	m_WriteOver.Internal = 0 ;
	m_WriteOver.InternalHigh = 0 ;
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	ResetEvent(m_WriteOver.hEvent);

	m_CmdBuffer.ZeroBuffer();

	ResetEvent(m_hEvent);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
///以下为Socket操作
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
TSocketSmartDocObj::TSocketSmartDocObj()
{
	m_hSocket = NULL;
}

TSocketSmartDocObj::~TSocketSmartDocObj()
{

}

//*=================================================================================
//*原型: void TSocketSmartDocObj::Create(int nAf, int nType, int nProtocol)
//*功能: 创建SOCKET
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
void TSocketSmartDocObj::Create(int nAf, int nType, int nProtocol)
{
	m_hSocket = WSASocket(nAf, nType, nProtocol, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( m_hSocket == INVALID_SOCKET )
	{
		throw TException("创建套接字错误!", WSAGetLastError());
	}

	int nFlag = 1;
	if( ioctlsocket(m_hSocket, FIONBIO, (u_long*)&nFlag) == SOCKET_ERROR )
	{
		closesocket(m_hSocket);
		throw TException("设置套接字为属性错误!", WSAGetLastError());
	}

	return ;
}

//*=================================================================================
//*原型: void TSocketSmartDocObj::Create(int nAf, int nType, int nProtocol)
//*功能: 得到一个常驻型的任务
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
void TSocketSmartDocObj::Bind(char *pszAddress, int nPort)
{
	SOCKADDR_IN  sockAddr;

	ZeroMemory(&sockAddr, sizeof(sockAddr));

	sockAddr.sin_family = AF_INET ;
	sockAddr.sin_port = htons(nPort);

	LPSTR lpszAscii = (LPSTR)pszAddress;
	if (lpszAscii == NULL)
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
	{
		DWORD lResult = inet_addr(lpszAscii);
		if (lResult == INADDR_NONE)
		{
			throw TException("网络地址或机器名称错误!", WSAEINVAL);
		}
		sockAddr.sin_addr.s_addr = lResult;
	}

	if( bind(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR )
	{
		throw TException("绑定套接字错误!", WSAGetLastError());
	}
}

void TSocketSmartDocObj::Listen(int nQueue)
{
	if( listen(m_hSocket, nQueue) == SOCKET_ERROR )
	{
		throw TException("Listen套接字错误!", WSAGetLastError());
	}
}

//*=================================================================================
//*原型: bool TSocketSmartDocObj::Connect(char* pszAddress, int nPort, long dwTimeOut)
//*功能: 连接到服务器
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
void TSocketSmartDocObj::Connect(char* pszAddress, int nPort, long dwTimeOut)
{
	SOCKADDR_IN  sockAddr;
	TCHAR  szErrorText[256];


	sprintf(szErrorText, "尝试连接到服务器(%s:%d)", pszAddress, nPort);

	ZeroMemory(&sockAddr, sizeof(sockAddr));

	sockAddr.sin_family = AF_INET ;
	sockAddr.sin_port = htons(nPort);

	LPSTR lpszAscii = (LPSTR)pszAddress;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);

	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			throw TException("网络地址或机器名称错误!", WSAEINVAL);
		}
	}

	WSAEVENT hEvent = WSACreateEvent();
	if( hEvent == WSA_INVALID_EVENT )
	{
		throw TException(szErrorText, WSAGetLastError());
	}

	if( WSAEventSelect(m_hSocket, hEvent, FD_CONNECT|FD_CLOSE) == SOCKET_ERROR )
	{
		WSACloseEvent(hEvent);
		throw TException(szErrorText, WSAGetLastError());
	}

	DWORD dwResult = WSAConnect(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr), NULL, NULL, NULL, NULL);
	if( dwResult == SOCKET_ERROR )
	{
		dwResult = WSAGetLastError();
		if( dwResult != WSAEWOULDBLOCK )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);
			Sleep(500);
			throw TException(szErrorText, dwResult );
		}

		//等待事件发生
		DWORD dwRet = WSAWaitForMultipleEvents(1, &hEvent, TRUE, (DWORD)dwTimeOut, FALSE);
		if( dwRet != WSA_WAIT_EVENT_0 )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);

			if( dwRet != WSA_WAIT_TIMEOUT )
				throw TException(szErrorText, WSAGetLastError());
			else
			{
				throw TException(szErrorText, WSA_WAIT_TIMEOUT);
			}
		}

		//有事件发生
		WSANETWORKEVENTS   NetEvents;

		ZeroMemory(&NetEvents, sizeof(NetEvents));
		if( WSAEnumNetworkEvents(m_hSocket, hEvent, &NetEvents) == SOCKET_ERROR )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);
			throw TException(szErrorText, WSAGetLastError());
		}

		if( NetEvents.lNetworkEvents != FD_CONNECT || NetEvents.iErrorCode[FD_CONNECT_BIT] )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);
			throw TException(szErrorText, NetEvents.iErrorCode[FD_CONNECT_BIT]);
		}
	}
	WSAEventSelect(m_hSocket, hEvent, 0);
	WSACloseEvent(hEvent);
}

//*=================================================================================
//*原型: bool TSocketSmartDocObj::Connect(char* pszAddress, int nPort, long dwTimeOut)
//*功能: 重叠写
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TSocketSmartDocObj::Write(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	WSABUF  wsaBuf;
	DWORD   dwFlag = 0 ;
	m_nWriteBytes = 0 ;

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset     = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	int nResult = WSASend(m_hSocket, &wsaBuf, 1, &m_nWriteBytes, 0, &m_WriteOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			//printf("Send WSA_IO_PENDING.................\n");
			//throw TException("发送数据错误!", WSAGetLastError());
			//Update by dengjun  20060320
			//在PostSend函数中判断,一般出现数据发送失败,网络已经断开,需要重新连接
			Sleep(300);
			return RET_SYSERROR;
		}
		else
		{
			if( !WSAGetOverlappedResult(m_hSocket, &m_WriteOver, &m_nWriteBytes, TRUE, &dwFlag) )
			{
				int nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					//printf("Send WSA_IO_INCOMPLETE.................\n");
					//throw TException("发送数据错误!", nLastError);
					//在PostSend函数中判断,一般出现数据发送失败,网络已经断开,需要重新连接
					Sleep(300);
					return RET_SYSERROR;					
				}
			}
		}
	}
	return (long)m_nWriteBytes;
}

void TSocketSmartDocObj::ReadEmptyBuffer()
{

}

//*=================================================================================
//*原型: long TSocketSmartDocObj::Read(char* pszBuffer, long dwBufferSize)
//*功能: 重叠读
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TSocketSmartDocObj::Read(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	DWORD	dwFlag = 0 ;
	WSABUF  wsaBuf;

	m_nReadBytes = 0 ;

	Sleep(20);
	ResetEvent(m_ReadOver.hEvent);
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	int nResult = WSARecv(m_hSocket, &wsaBuf, 1, &m_nReadBytes, &dwFlag, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			throw TException("接收数据错误!", WSAGetLastError());
		}
		else
		{
			Sleep(20);
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nReadBytes = 0 ;
			dwFlag = 0 ;			
			if( !WSAGetOverlappedResult(m_hSocket, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				int nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					throw TException("等待接收数据错误!", nLastError);
				}
			}
		}
	}
	return (long)m_nReadBytes;
}

//*=================================================================================
//*原型: long WriteTo(char *pszBuffer, long nBufferSize, const SOCKADDR_IN *psockAddr, long nTimeOut)
//*功能: 重叠写(UDP)
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TSocketSmartDocObj::WriteTo(char *pszBuffer, long nBufferSize, const SOCKADDR_IN *psockAddr, long nTimeOut)
{
	DWORD   dwBytes = 0 ;
	WSABUF  wsaBuf;
	int nLen = sizeof(SOCKADDR_IN);

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	int nResult = WSASendTo(m_hSocket, &wsaBuf, 1, &dwBytes, 0, (SOCKADDR*)psockAddr, nLen, &m_WriteOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			throw TException("发送数据错误!", WSAGetLastError());
		}
		else
		{
			dwBytes = 0 ;
			if( !WSAGetOverlappedResult(m_hSocket, &m_WriteOver, &dwBytes, TRUE, NULL) )
			{
				int  nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					throw TException("发送数据错误!", WSAGetLastError());
				}
			}
		}
	}

	return (long)dwBytes;
}

//*=================================================================================
//*原型: long ReadFrom(char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut)
//*功能: 重叠写(UDP)
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TSocketSmartDocObj::ReadFrom(char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut)
{
	DWORD	dwFlag = MSG_PEEK ;
	WSABUF  wsaBuf;
	int nLen = sizeof(SOCKADDR_IN);
	
	m_nReadBytes = 0 ;
	
	ResetEvent(m_ReadOver.hEvent);
	
	m_ReadOver.Offset	  = 0 ;
	m_ReadOver.OffsetHigh = 0 ;
	
	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;
	
	int nResult = WSARecvFrom(m_hSocket, &wsaBuf, 1, &m_nReadBytes, &dwFlag, (SOCKADDR*)psockAddr, &nLen, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			throw TException("接收数据错误!", WSAGetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}
			
			m_nReadBytes = 0 ;
			//dwFlag = 0 ;
			if( !WSAGetOverlappedResult(m_hSocket, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				int nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					//					Close();
					throw TException("接收数据错误!", nLastError);
				}
			}
		}
	}	
	return (long)m_nReadBytes;
}

//*=================================================================================
//*原型: bool TSocketSmartDocObj::Open()
//*功能: 打开通讯链路
//*参数: 略
//*返回: 无
//*说明: 套接字设备
//*=================================================================================
void TSocketSmartDocObj::Open()
{
	char errmsg[1024];

	memset(errmsg, 0x00, sizeof errmsg);

	m_bOpen = false;
	m_ReadOver.hEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	Create(AF_INET, SOCK_STREAM, 0);
	Connect(m_szAddr, atol(m_szPort), 1000);
	m_bOpen = true ;

	sprintf(errmsg,"TSocketSmartDocObj终端设备%s打开成功! 地址:%s, 端口:%s\n", m_szDeviceID, m_szAddr, m_szPort);
	ReportLog(errmsg);
	WriteTaskLog(errmsg);
}

//*=================================================================================
//*原型: void TSocketSmartDocObj::Close()
//*功能: 强制关闭链路
//*参数: 略
//*返回: 无
//*说明: 无
//*=================================================================================
void TSocketSmartDocObj::Close()
{
	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);
		m_ReadOver.hEvent = NULL ;
	}

	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
	}

	if( m_hSocket != NULL )
	{
		shutdown(m_hSocket, SB_BOTH);
		closesocket(m_hSocket);

		m_hSocket = NULL ;
	}

	m_bOpen = false ;
}


//*=================================================================================
//*原型: long TSocketSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
//*功能: 投递发送请求
//*参数: 略
//*返回: 无
//*说明: 套接字设备
//*=================================================================================
long TSocketSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
{
	return Write(lpBuffer, nBufSize, nTimeOut);
}

//*=================================================================================
//*原型: long TSocketSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*功能: 投递接收请求
//*参数: 略
//*返回: 无
//*说明: 套接字设备
//*=================================================================================
long TSocketSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	long nRet = Read(lpBuffer, nBufSize, nTimeOut);
	if( nRet == RET_TIMEOUT )
	{
		if( WSAGetLastError() == 997 )
		{
			Sleep(50);
			return WaitingRead(nTimeOut);
		}
	}
	return nRet;
}

//*=================================================================================
//*原型: long TSocketSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*功能: 投递接收请求
//*参数: 略
//*返回: 无
//*说明: 套接字设备
//*=================================================================================
long TSocketSmartDocObj::WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
#if 0
	struct timeval TimeOutVal;
	fd_set readfds;
	SOCKADDR_IN sockAddr;	
	int    nResult=0;
	BYTE   str[20];
	
	memset(&sockAddr,  0x00,sizeof(sockAddr));		
	memset(str,		   0x00,sizeof str);
	memset(&TimeOutVal,0x00,sizeof TimeOutVal);
	
	TimeOutVal.tv_sec=nTimeOut/1000;
	TimeOutVal.tv_usec=nTimeOut%1000;
	FD_ZERO(&readfds);
	FD_SET(m_hSocket,&readfds);
	if( (nResult=select(m_hSocket+1,&readfds,NULL,NULL,&TimeOutVal))<0 )
	{	
		return RET_SERVER_NOANSWER; //在规定时间内LPORT或直连设备未响应
	}	
	Sleep(15);
	return RET_OK;
#else
	long ret;
	SOCKADDR_IN sockAddr;	
	ZeroMemory(&sockAddr, sizeof(sockAddr));
	ret = ReadFrom(lpBuffer, nBufSize, &sockAddr, nTimeOut);
	return ret;
#endif
	
}

//等待写
long TSocketSmartDocObj::WaitingWrite(DWORD dwTimeOut)
{
	return RET_OK;
}

//等待读
long TSocketSmartDocObj::WaitingRead(DWORD dwTimeOut)
{
	if( WaitForSingleObject(m_ReadOver.hEvent, dwTimeOut) != WAIT_OBJECT_0 )
	{
		return RET_NG;
	}

	DWORD dwFlag = 0 ;
	if( !WSAGetOverlappedResult(m_hSocket, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
	{
		int nError = WSAGetLastError();
		return RET_NG;
	}

	return (long)m_nReadBytes;
}

TCOMSmartDocObj::TCOMSmartDocObj()
{
	m_hHandle = INVALID_HANDLE_VALUE;
}

TCOMSmartDocObj::~TCOMSmartDocObj()
{
	Close();
}


//*=================================================================================
//*原型: void TCOMSmartDocObj::ClearComm(DWORD dwMask)
//*功能: 清除事件
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::ClearComm(DWORD dwMask)
{
	if( !PurgeComm(m_hHandle, dwMask) )
		throw TException("PurgeComm()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::SetEventMask(DWORD dwMask)
//*功能: 设置事件
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::SetEventMask(DWORD dwMask)
{
	if( !SetCommMask(m_hHandle, dwMask) )
		throw TException("SetCommMask()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
//*功能: 设置超时时间
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
{
	COMMTIMEOUTS   CommTimeOut;

	ZeroMemory(&CommTimeOut, sizeof(CommTimeOut));

	CommTimeOut.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOut.ReadTotalTimeoutConstant = 0;
    CommTimeOut.ReadTotalTimeoutMultiplier = 0 ;

	CommTimeOut.WriteTotalTimeoutMultiplier = 5;
	CommTimeOut.WriteTotalTimeoutConstant = 50;

	if( !SetCommTimeouts(m_hHandle, &CommTimeOut) )
		throw TException("SetCommTimeouts()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::GetEventMask(DWORD& dwMask)
//*功能: 得到串口属性掩码
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::GetEventMask(DWORD& dwMask)
{
	if( !GetCommMask(m_hHandle, &dwMask) )
		throw TException("GetCommMask()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
//*功能: 设置串口属性
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
{
	TCHAR  szDCB[64];
	DCB    dcb;

	ZeroMemory(&dcb, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	wsprintf(szDCB, "baud=%d parity=%c data=%d stop=%d", nBaud, cParity, nDataBit, nStopBit);

	if( !BuildCommDCB(szDCB, &dcb) )
		throw TException("BuildCommDCB()出错!", GetLastError());

	if( !SetCommState(m_hHandle, &dcb) )
		throw TException("SetCommState()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::GetState(DCB *pDCB)
//*功能: 得到串口状态(DCB)
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::GetState(DCB *pDCB)
{
	if( !GetCommState(m_hHandle, pDCB) )
	{
		throw TException("调用GetCommState()出错!", GetLastError());
	}
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::ClearError()
//*功能: 清除串口错误
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::ClearError()
{
	if( !PurgeComm(m_hHandle, PURGE_TXCLEAR|PURGE_RXCLEAR) )
	{
		throw TException("PurgeComm()出错!", GetLastError());
	}
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::Open()
//*功能: 打开串口设备
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::Open()
{
	TCHAR  szFileName[MAX_PATH];

	m_bOpen = false;

	wsprintf(szFileName, "%s", m_szPort);
	m_hHandle = CreateFile(
					szFileName,
					GENERIC_READ|GENERIC_WRITE,
					0,
					0,
					OPEN_EXISTING,
					FILE_FLAG_OVERLAPPED,
					0);
	if( m_hHandle == INVALID_HANDLE_VALUE )
	{
		throw TException("打开COM口失败!", GetLastError());
	}

	SetState(m_nBaudRate, 'N', 8, 1);

//	EscapeCommFunction(m_hHandle, SETDTR);

//	SetEventMask(EV_RXCHAR);

//	SetupComm(m_hHandle, 1024, 1024);

//	ClearComm(PURGE_TXABORT);
//	ClearComm(PURGE_RXABORT);
//	ClearComm(PURGE_TXCLEAR);
//	ClearComm(PURGE_RXCLEAR);

	SetTimeOut(1000, 0);

	m_ReadOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_ReadOver.Internal = 0 ;
	m_ReadOver.InternalHigh = 0 ;
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	ResetEvent(m_ReadOver.hEvent);

	m_WriteOver.Internal = 0 ;
	m_WriteOver.InternalHigh = 0 ;
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	ResetEvent(m_WriteOver.hEvent);

	m_bOpen = true;

	ReportLog("终端设备%d打开成功! 地址:%s, 端口:%s\n", m_nAuthID, m_szAddr, m_szPort);
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::Close()
//*功能: 关闭串口设备
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TCOMSmartDocObj::Close()
{
	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);
		m_ReadOver.hEvent = NULL ;
	}

	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
	}

	if( m_hHandle != INVALID_HANDLE_VALUE )
	{
		ClearError();
		ClearCommBreak(m_hHandle);
		CloseHandle(m_hHandle);
		m_hHandle = INVALID_HANDLE_VALUE;
	}

	m_bOpen = false ;
}

//*=================================================================================
//*原型: bool TCOMSmartDocObj::Reset()
//*功能: 复位串口设备
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
bool TCOMSmartDocObj::Reset()
{
    try
	{
		Close();
		Open();
	}
	catch(TException& e)
	{
		WriteLog(e.GetText());
		Close();
		return false;
	}

	return true;
}

//*=================================================================================
//*原型: long TCOMSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
//*功能: 发数据
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
long TCOMSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
{
	return Write(lpBuffer, nBufSize, nTimeOut);
}

//*=================================================================================
//*原型: long TCOMSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*功能: 收数据
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
long TCOMSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	long nRet = Read(lpBuffer, nBufSize, nTimeOut);
	if( nRet == RET_TIMEOUT )
	{
		if( WSAGetLastError() == 997 )
		{
			return WaitingRead(nTimeOut);
		}
	}
	return nRet;
}

long TCOMSmartDocObj::WaitingWrite(DWORD dwTimeOut)
{
//leep(dwTimeOut);
	return RET_OK;
}

long TCOMSmartDocObj::WaitingRead(DWORD dwTimeOut)
{
	if( IsBus() )
		dwTimeOut += 200 ;
	else
		dwTimeOut += 10 ;

	if( WaitForSingleObject(m_ReadOver.hEvent, dwTimeOut) != WAIT_OBJECT_0 )
		return RET_NG;

	if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
	{
		int nError = WSAGetLastError();
		return RET_NG;
	}

	return (long)m_nReadBytes;
}

long TCOMSmartDocObj::WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	if( nTimeOut < 500 )
		Sleep(nTimeOut+10);
	else
		Sleep(nTimeOut/2);

	return nTimeOut;
}

//*=================================================================================
//*原型: long Write(char *pszBuffer, long nBufferSize, long nTimeOut)
//*功能: 重叠写
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TCOMSmartDocObj::Write(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	m_nWriteBytes = 0 ;

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	DWORD nResult = WriteFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nWriteBytes, &m_WriteOver);
	if( !m_nWriteBytes )
	{
		if( GetLastError() != ERROR_IO_PENDING )
		{
			throw TException("向串口写数据错误!", GetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_WriteOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nWriteBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_WriteOver, &m_nWriteBytes, TRUE) )
			{
				DWORD dwLastError = GetLastError() ;
				if( dwLastError != ERROR_IO_INCOMPLETE )
				{
					throw TException("向串口写数据错误!", dwLastError);
				}
			}
		}
	}

	return (long)m_nWriteBytes;
}

//*=================================================================================
//*原型: long Read(char *pszBuffer, long nBufferSize, long nTimeOut)
//*功能: 重叠读
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TCOMSmartDocObj::Read(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	ResetEvent(m_ReadOver.hEvent);

//	DWORD dwMask;
//	COMSTAT  comstat;
//	ClearCommError(m_hHandle, &dwMask, &comstat);

	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	m_nReadBytes = 0 ;

	DWORD nResult = ReadFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nReadBytes, &m_ReadOver);
	if( !nResult )
	{
		if( GetLastError() != WSA_IO_PENDING )
		{
			throw TException("接收数据错误!", WSAGetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nReadBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
			{
				DWORD nLastError = GetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					printf("com wait read WSA_IO_INCOMPLETE........\n");
					throw TException("等待接收数据错误!", nLastError);
				}
			}
		}
	}

	return (long)m_nReadBytes;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
///以下为Modem操作
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
TModemSmartDocObj::TModemSmartDocObj()
{
	m_hHandle = INVALID_HANDLE_VALUE;
}

TModemSmartDocObj::~TModemSmartDocObj()
{
	Close();
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::ClearComm(DWORD dwMask)
//*功能: 清除事件
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::ClearComm(DWORD dwMask)
{
	if( !PurgeComm(m_hHandle, dwMask) )
		throw TException("PurgeComm()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::SetEventMask(DWORD dwMask)
//*功能: 设置事件
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::SetEventMask(DWORD dwMask)
{
	if( !SetCommMask(m_hHandle, dwMask) )
		throw TException("SetCommMask()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
//*功能: 设置超时时间
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
{
	COMMTIMEOUTS   CommTimeOut;

	ZeroMemory(&CommTimeOut, sizeof(CommTimeOut));

	CommTimeOut.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOut.ReadTotalTimeoutConstant = 0;
    CommTimeOut.ReadTotalTimeoutMultiplier = 0 ;

	CommTimeOut.WriteTotalTimeoutMultiplier = 5;
	CommTimeOut.WriteTotalTimeoutConstant = 50;

	if( !SetCommTimeouts(m_hHandle, &CommTimeOut) )
		throw TException("SetCommTimeouts()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::GetEventMask(DWORD& dwMask)
//*功能: 得到串口属性掩码
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::GetEventMask(DWORD& dwMask)
{
	if( !GetCommMask(m_hHandle, &dwMask) )
		throw TException("GetCommMask()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
//*功能: 设置串口属性
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
{
	TCHAR  szDCB[128];
	DCB    dcb;

	ZeroMemory(&dcb, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);

	GetState(&dcb);

	wsprintf(szDCB, "baud=%d parity=%c data=%d stop=%d", nBaud, cParity, nDataBit, nStopBit);
	if( !BuildCommDCB(szDCB, &dcb) )
		throw TException("BuildCommDCB()出错!", GetLastError());

	if( !SetCommState(m_hHandle, &dcb) )
		throw TException("SetCommState()出错!", GetLastError());
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::GetState(DCB *pDCB)
//*功能: 得到串口状态(DCB)
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::GetState(DCB *pDCB)
{
	if( !GetCommState(m_hHandle, pDCB) )
	{
		throw TException("调用GetCommState()出错!", GetLastError());
	}
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::ClearError()
//*功能: 清除串口错误
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::ClearError()
{
	if( !PurgeComm(m_hHandle, PURGE_TXCLEAR|PURGE_RXCLEAR) )
	{
		throw TException("PurgeComm()出错!", GetLastError());
	}
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::Open()
//*功能: 打开串口设备
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::Open()
{
	TCHAR  szFileName[MAX_PATH];

	Close();

	m_bOpen = false;

	wsprintf(szFileName, "%s", m_szPort);
	m_hHandle = CreateFile(
					szFileName,
					GENERIC_READ|GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_FLAG_OVERLAPPED|FILE_ATTRIBUTE_NORMAL,
					NULL);
	if( m_hHandle == INVALID_HANDLE_VALUE )
	{
		throw TException("打开COM口失败!", GetLastError());
	}

	SetState(m_nBaudRate, 'N', 8, 1);

	EscapeCommFunction(m_hHandle, SETDTR);

	SetEventMask(EV_RXCHAR);

	SetupComm(m_hHandle, 1024, 1024);

	ClearComm(PURGE_TXABORT);
	ClearComm(PURGE_RXABORT);
	ClearComm(PURGE_TXCLEAR);
	ClearComm(PURGE_RXCLEAR);

	SetTimeOut(1000, 0);

	m_ReadOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_ReadOver.Internal = 0 ;
	m_ReadOver.InternalHigh = 0 ;
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	ResetEvent(m_ReadOver.hEvent);

	m_WriteOver.Internal = 0 ;
	m_WriteOver.InternalHigh = 0 ;
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	ResetEvent(m_WriteOver.hEvent);

	DialCall();

	m_bOpen = true;

	ReportLog("终端设备%d打开成功! 拨号服务器号码:%s, 端口:%s\n", m_nAuthID, m_szAddr, m_szPort);
}

//*=================================================================================
//*原型: void DialCall()
//*功能: 拨号
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::DialCall()
{
	char  szCmdText[256];

	memset(szCmdText, 0, sizeof(szCmdText));
	strcpy(szCmdText, "ATZ \r");
	if( PostSend(szCmdText, strlen(szCmdText), 1000L) <= 0 )
		throw TException("不能复位Modem! 串口上可能没有Modem设备!");

	Sleep(1000);
	memset(szCmdText, 0, sizeof(szCmdText));
	if( PostRecv(szCmdText, 256, 3000) <= 0 )
		throw TException("不能复位Modem! 串口上可能没有Modem设备!");

	if( FindString(szCmdText, "OK") < 0 )
	{
		;
	}

	memset(szCmdText, 0, sizeof(szCmdText));
	sprintf(szCmdText, "ATDT %s\r", m_szAddr);
	if( PostSend(szCmdText, strlen(szCmdText), 1000L) <= 0 )
		throw TException("不能对Modem拨号! 串口上可能没有Modem设备!");

	Sleep(2000);

	int nRead = 256;
	int iTick=0;
	while( iTick++ < 12 )
	{
		memset(szCmdText, 0, sizeof(szCmdText));
		long nResult = PostRecv(szCmdText, nRead, 3000);
		if( nResult > 0 )
		{
			if( FindString(szCmdText, "CONN") >= 0 )
			{
				return ;
			}
		}
		else if( nResult != RET_TIMEOUT )
		{
			Sleep(3000);
		}
	}

	if( iTick > 12 )
	{
		throw TException("线路不通或对方拨号服务器无反应!");
	}
}

//*=================================================================================
//*原型: void Hangup()
//*功能: 挂断
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::Hangup()
{
	char  szCmdText[256];

	memset(szCmdText, 0, sizeof(szCmdText));

	strcpy(szCmdText, "+++");
	if( PostSend(szCmdText, strlen(szCmdText), 1000L) <= 0 )
		throw TException("不能写数据到Modem! 串口故障!");

	Sleep(2000);

	int nRead = 2 ;
	memset(szCmdText, 0, sizeof(szCmdText));
	if( PostRecv(szCmdText, nRead, 5000) >= nRead )
	{
		if( _strnicmp(szCmdText, "OK", 2) )
		{
			throw TException("Modem不能挂机!");
		}
	}
	else
	{
		throw TException("Modem无反应!");
	}

	strcpy(szCmdText, "ATH\r");
	PostSend(szCmdText, strlen(szCmdText), 1000L);
	Sleep(1000);
}

//*=================================================================================
//*原型: void TCOMSmartDocObj::Close()
//*功能: 关闭串口设备
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
void TModemSmartDocObj::Close()
{
	if( m_hHandle != INVALID_HANDLE_VALUE )
	{
		try
		{
			Hangup();
		}
		catch(...)
		{

		}

		EscapeCommFunction(m_hHandle, CLRDTR);

		ClearCommBreak(m_hHandle);
		CloseHandle(m_hHandle);
		m_hHandle = INVALID_HANDLE_VALUE;
	}

	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);
		m_ReadOver.hEvent = NULL ;
	}

	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
	}

	m_bOpen = false ;
}

//*=================================================================================
//*原型: bool TCOMSmartDocObj::Reset()
//*功能: 复位串口设备
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
bool TModemSmartDocObj::Reset()
{
   try
   {
	   Close();
	   Open();
   }
   catch(TException& e)
   {
	   WriteLog(e.GetText());
	   Close();
	   return false;
   }
   return true;
}

//*=================================================================================
//*原型: long TCOMSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
//*功能: 发数据
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
long TModemSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
{
	return Write(lpBuffer, nBufSize, nTimeOut);
}

//*=================================================================================
//*原型: long TCOMSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*功能: 收数据
//*参数: 略
//*返回: 无
//*说明: 串口设备
//*=================================================================================
long TModemSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	long nRet = Read(lpBuffer, nBufSize, nTimeOut);
	if( nRet == RET_TIMEOUT )
	{
		if( WSAGetLastError() == 997 )
		{
			return WaitingRead(nTimeOut);
		}
	}
	return nRet;
}

long TModemSmartDocObj::WaitingWrite(DWORD dwTimeOut)
{
	return RET_OK;
}

long TModemSmartDocObj::WaitingRead(DWORD dwTimeOut)
{
	if( WaitForSingleObject(m_ReadOver.hEvent, dwTimeOut+300) != WAIT_OBJECT_0 )
		return RET_NG;

	if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
	{
		int nError = WSAGetLastError();
		return RET_NG;
	}

	return (long)m_nReadBytes;
}

//*=================================================================================
//*原型: long Write(char *pszBuffer, long nBufferSize, long nTimeOut)
//*功能: 重叠写
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TModemSmartDocObj::Write(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	m_nWriteBytes = 0 ;

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset     = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	DWORD nResult = WriteFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nWriteBytes, &m_WriteOver);
	if( !m_nWriteBytes )
	{
		if( GetLastError() != ERROR_IO_PENDING )
		{
			throw TException("向串口写数据错误!", GetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_WriteOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nWriteBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_WriteOver, &m_nWriteBytes, TRUE) )
			{
				DWORD dwLastError = GetLastError() ;
				if( dwLastError != ERROR_IO_INCOMPLETE )
				{
					throw TException("向串口写数据错误!", dwLastError);
				}
			}
		}
	}

	return (long)m_nWriteBytes;
}

//*=================================================================================
//*原型: long Read(char *pszBuffer, long nBufferSize, long nTimeOut)
//*功能: 重叠读
//*参数: 略
//*返回: 无
//*说明: 套接字通讯封装(基于重叠模型)
//*=================================================================================
long TModemSmartDocObj::Read(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	ResetEvent(m_ReadOver.hEvent);

	DWORD dwMask;
	COMSTAT  comstat;
	ClearCommError(m_hHandle, &dwMask, &comstat);
	nBufferSize = min(nBufferSize, (long)comstat.cbInQue);

	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	m_nReadBytes = 0 ;

	DWORD nResult = ReadFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nReadBytes, &m_ReadOver);
	if( !nResult )
	{
		if( GetLastError() != WSA_IO_PENDING )
		{
			throw TException("接收数据错误!", WSAGetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nReadBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
			{
				DWORD nLastError = GetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					printf("com wait read WSA_IO_INCOMPLETE........\n");
					throw TException("等待接收数据错误!", nLastError);
				}
			}
		}
	}

	return (long)m_nReadBytes;
}

long TModemSmartDocObj::WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	if( nTimeOut < 500 )
		Sleep(nTimeOut+10);
	else
		Sleep(nTimeOut/2);

	return nTimeOut;
}

