///////////////////////////////////////////////////////////////////////////////////////////////////
// SmartServer Version4.0
// Copyright by ?-2004. 广州三九智慧电子信息产业公司
///////////////////////////////////////////////////////////////////////////////////////////////////
// 文件名称: TSmartServer.cpp
// 实现功能: 三九前置采集服务器主框架
// 程序编写: 张伟
// 版本变更: 2004.02 第一版
//           2004.05 第二版. 修改了设备读取的bug.
//           .................
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartServer.h"
#include "TSmartRegister.h"
#include "TExportFunc.h"

//*=================================================================================
//*原型: TSmartServer::TSmartServer()
//*功能: 前置采集服务器类
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
TSmartServer::TSmartServer()
{
	nSmartTimeOut = 0 ;
	ZeroMemory(SmartTimeOut, sizeof(SmartTimeOut));

	m_DocList.Clear();
	m_TaskList.Clear();

	gethostname(m_SmartInfo.szHostName, 128);
	strcpy(m_SmartInfo.szVersion, "1.0");

	m_SmartInfo.nWorkMode = 1 ;
	strcpy(m_SmartInfo.szDateTime, "");

	m_SmartInfo.nTick = 0;
	m_SmartInfo.nDevLevel1 = 0;
	m_SmartInfo.nDevLevel1Ack = 0;
	m_SmartInfo.nDevLevel2 = 0;
	m_SmartInfo.nDevLevel2Ack = 0;

	TCHAR  szDir[MAX_PATH];

	GetCurPath(szDir);
	wsprintf(szLogDir, "%s\\服务器日志", szDir);
	CreateDirectory(szLogDir, NULL);
}


//*=================================================================================
//*原型: TSmartServer::~TSmartServer()
//*功能: 前置采集服务器类
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
TSmartServer::~TSmartServer()
{

}

//*=================================================================================
//*原型: void TSmartServer::InitInstance()
//*功能: 初始化服务器
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::InitInstance()
{
	TSmartRegister  sr;
	sr.ReadParameter();

	m_OutThread.Initialized(sr.m_nPort, this);
	ReportLog("初始化本地网络接口线程成功!端口:%d", sr.m_nPort);

	try
	{
		m_Channels.Initialized(
			sr.m_szChannels,
			sr.m_szCenter,
			sr.m_nCenterPort,
			sr.m_nEncode, 
			sr.m_nChannelsNotify,
			this,
			sr.m_nFunc,
			sr.m_nServerNo);
	}
	catch(TException& e)
	{
		ReportLog("连接到金仁达中间层出错!",  e.GetText());
		throw TException( e.GetText());
	}

	ReportLog("初始化通道线程成功!端口:%d", sr.m_nPort);

	TExportFunc::pServer = this ;
	TExportFunc::FillAPI(&SmartFunction);

	m_SmartProtocol.Initialized(sr.m_szProtocol);
	ReportLog("初始化协议模块:%s成功!", sr.m_szProtocol);

	char szFileName[256];
	int  i = 0 ;

	m_SmartModule.Initialized();
	for(i=0; i< sr.m_nModule; i++)
	{
		try
		{
			if( sr.GetModule(szFileName, i+1) )
				m_SmartModule.AddModule(szFileName);
			ReportLog("系统装入模块:%s成功!", szFileName);
		}
		catch(TException& e)
		{
			ReportLog("系统装入模块:%s失败!原因:%s", szFileName, e.GetText());
		}
		catch(...)
		{
			ReportLog("系统装入模块:%s失败!原因:未知的错误!", szFileName);
		}
	}

	if( i <= 0 )
	{
		ReportLog("严重警告:系统没有装入任何业务模块文件! 系统将不能执行业务处理!");
	}

	m_SmartMonitor.Initialized(this);

	InitSmartDocList();
}

//*=================================================================================
//*原型: void TSmartServer::InitSmartDocList()
//*功能: 初始化设备档案信息
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::InitSmartDocList()
{
	TSSmartDoc *pSmartDoc = NULL;
	long nRecCount = 0 ;
	
	m_DocList.Clear();

	try
	{
		pSmartDoc = new TSSmartDoc[MAX_SMART_DOC];
		if( pSmartDoc == NULL )
		{
			ReportLog("不能读入设备档案表!请检查数据库连接与业务层是否正确!");
			return ;
		}

		ZeroMemory(pSmartDoc, sizeof(TSSmartDoc)*MAX_SMART_DOC);

		if( !m_Channels.ReadSmartDoc(pSmartDoc, &nRecCount) )
		{
			delete [] pSmartDoc;
			ReportLog("不能读入设备档案表!请检查数据库连接与业务层是否正确!");
			return ;
		}

		if( nRecCount <= 0 )
		{
			delete [] pSmartDoc;
			ReportLog("警告: 没有任何设备档案信息!");
			return ;
		}
		printf("-----------设备档案信息----------\n");
		for(long mm=0;mm<nRecCount;mm++)
		{
			printf("授权号=%.8X\n",pSmartDoc[mm].m_nAuthID);
			printf("ID号=%s\n",pSmartDoc[mm].m_szDeviceID);
			printf("服务器端口总数=%d\n",pSmartDoc[mm].m_nPortCount);
			printf("服务器端口号=%d\n",pSmartDoc[mm].m_nSMTPort);
			printf("设备级联级数=%d\n",pSmartDoc[mm].m_nLevel);
			printf("设备级联参数=%s\n",pSmartDoc[mm].m_szLevelArray);
		}
		long  k = 0 ;
		for(long i=0; i<nRecCount; i++) 
		{
			TSmartDocObj *pObj = CreateSmartDoc(&pSmartDoc[i]);
			if( pObj != NULL )
			{
				printf("i= %d pObj->m_szDeviceID=%.8X\n",i,pObj->m_nAuthID);  
				pObj->SetServer(this);
				pObj->AssignBy(&pSmartDoc[i]);
				AddChildDoc(pObj, pSmartDoc, nRecCount);

				//没有父设备, 有可能是总线上的设备
				if( pObj->IsParent() )
				{
					long iIndex = FindBusFromDocList(pObj);
					if( iIndex >= 0 )
					{
						TSmartDocObj *pBus = (TSmartDocObj*)m_DocList.Get(iIndex);
						pObj->SetShare(*pBus);
					}
					else
					{
						iIndex = FindBusFromDocArray(pSmartDoc, i, nRecCount);
						if( iIndex >= 0 )
						{
							pObj->SetFirstShare();
						}
					}
				}

				try
				{
					pObj->Start();
					m_DocList.Add(pObj);
					k++;
				}
				catch(TException& e)
				{
					OnError((char*)e.GetText());
					delete pObj;
				}
			}
		}

		if( !k )
		{
			ReportLog("没有任务终端设备被加入!");
		}

		if( pSmartDoc != NULL )
		{
			delete [] pSmartDoc;
			pSmartDoc = NULL ;
		}
	}
	catch(...)
	{
		if( pSmartDoc != NULL )
			delete [] pSmartDoc;

		OnError("读入设备档案表异常! 请检查业务模块是否正确!");
	}
}

//*=================================================================================
//*原型: TSmartDocObj* CreateSmartDoc(TSSmartDoc *pDoc)
//*功能: 创建相关的设备档案信息
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
TSmartDocObj* TSmartServer::CreateSmartDoc(TSSmartDoc *pDoc)
{
	TSmartDocObj *pObj = NULL ;

	if( pDoc->m_nParentID > 0 )
		return NULL ;

	if( pDoc->m_nParentID == 0 && strcmp(pDoc->m_sClockVer, "") )
		return NULL;
	
	switch(pDoc->m_nCommMode)
	{
	case 1:	//串口
		pObj = new TCOMSmartDocObj;
		break;
	case 2: //MODEM
		pObj = new TModemSmartDocObj;
		break;
	case 3: //TCP/IP协议
		pObj = new TSocketSmartDocObj;
		break;
	default:
		printf("不支持的链路模式!!!..............\n");
		break;
	}

	return pObj;
}

//*=================================================================================
//*原型: void TSmartServer::AddChildDoc(TSmartDocObj *pObj, TSSmartDoc *pSmartDoc, long nRecCount)
//*功能: 加入子设备
//*参数: 略
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::AddChildDoc(TSmartDocObj *pObj, TSSmartDoc *pSmartDoc, long nRecCount)
{
	for(long i=0; i< nRecCount; i++)
	{
		if( pSmartDoc[i].m_nAuthID != pObj->m_nAuthID )
		{
			if( pSmartDoc[i].m_nParentID == pObj->m_nAuthID && pObj->GetChildDocCount() < 24 )
			{
				TSSmartDoc *pDoc = new TSSmartDoc;
				memcpy(pDoc, &pSmartDoc[i], sizeof(TSSmartDoc));
				pObj->AddChildDoc(pDoc);
			}
		}
	}
}

//*=================================================================================
//*原型: void TSmartServer::ExitInstance()
//*功能: 退出服务器
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::ExitInstance()
{
	m_OutThread.BroadShutdown();
	m_Channels.Destroy();

	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			pObj->Shutdown();
		}
	}

	for(i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			try
			{
				pObj->WaitForQuit();
				delete pObj;
			}
			catch(...)
			{

			}
		}
	}

	m_DocList.Clear();

	m_SmartMonitor.Shutdown();
	m_OutThread.Shutdown();

	Sleep(500);

	m_SmartMonitor.WaitFor();
	m_OutThread.WaitFor();

	m_SmartModule.Destory();
	m_SmartProtocol.Destory();
}

//*=================================================================================
//*原型: void TSmartServer::Run()
//*功能: 服务器执行服务
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::Run()
{
	bool bReloadFlag = false;
	try
	{
		m_OutThread.Start();
		m_SmartMonitor.Start();

		TSmartTaskObj *pObj = NULL ;
		bool  bRet;
		DWORD nTick = GetTickCount();

		//执行任务
		while( !IsShutdown() )
		{
			if( GetDocCount() <= 0 )
			{
				ReportLog("没有设备档案信息! 服务器自动重新装入设备档案表!");
				InitSmartDocList();
				Sleep(1000);
				continue;
			}
			
			
			bRet = false ;
			pObj = new TSmartTaskObj;
			if( pObj != NULL )
			{
				pObj->Clear();
				
				if( m_Channels.GetSmartTaskPlan(pObj) )
				{
					
					ReportLog("选中任务: %s(%d), 执行次数:%d, 执行时长:%d, 设备数:%d.\n", 
						pObj->szTaskName, pObj->nTaskPlanID,  
						pObj->nRepeatTimes, pObj->nRepeatTime, pObj->nTask); 
				
					pObj->SetBeginTime();
					bRet = ExecuteTask(pObj) ;
				}
				else
				{
					bRet = false ;
				}
			}
			else
			{
				OnError("不能分配新的任务对象, 系统正忙!");
			}
			
			if( pObj != NULL && !bRet )
			{
				for(int j=0; j< pObj->nTask; j++)
				{
					TSResultData  data;
					ZeroMemory(&data, sizeof(data));

					strcpy(data.sMsg, "任务不能执行!");
					m_Channels.ReportTaskResult(&pObj->pTask[j], RET_SYSERROR, &data);
				}

				delete pObj;
				pObj = NULL ;
			}
			/*if(pObj != NULL && bRet)
			{
				delete pObj;
				pObj = NULL;
			}*/

			if( GetTickCount() - nTick > 400 )
			{
				
				m_Channels.SendTick();
				nTick = GetTickCount();

			}
			

			Sleep(100);
		}
		m_OutThread.Shutdown();
	}
	catch(TException& e)
	{
		ReportError(e.GetText());
		printf("------ e error ----\n");
		Shutdown();
	}
	catch(...)
	{
		ReportError("未知的错误导致服务器终止!");
//		printf("未知的错误导致服务器终止\n");
		Shutdown();
	}

	PostQuitMessage(0);
}

//是否有太多的任务
bool TSmartServer::IsFullTask()
{
	return GetBusyTask()>MAX_BUSY_TASK?true:false;
}

//得到当前正在运行的任务数
long TSmartServer::GetBusyTask()
{
	m_TaskLock.Lock();
	long nCount = m_TaskList.GetCount();
	m_TaskLock.Unlock();

	return nCount;
}

//*=================================================================================
//*原型: TSmartTaskObj* TSmartServer::GetFreeTaskObj()
//*功能: 得到一个空闲的任务内存块
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
TSmartTaskObj* TSmartServer::GetFreeTaskObj()
{
	m_FreeTaskLock.Lock();

	TSmartTaskObj *pObj = NULL ;

	if( m_FreeTaskList.GetCount() <= 0 )
	{
		pObj = new TSmartTaskObj;
		if( pObj == NULL )
			return NULL;
	}
	else
	{
		pObj = (TSmartTaskObj*)m_FreeTaskList[0];
		if( pObj != NULL )
			m_FreeTaskList.Remove(pObj);
	}

	m_FreeTaskLock.Unlock();

	return pObj;
}

//*=================================================================================
//*原型: void TSmartServer::AddToFreeTaskList(TSmartTaskObj *pObj)
//*功能: 将一个任务对象加入到空闲的任务列表
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::AddToFreeTaskList(TSmartTaskObj *pObj) 
{
	m_TaskLock.Lock();
	m_TaskList.Remove(pObj);
	m_TaskLock.Unlock();

	m_FreeTaskLock.Lock();
	if( pObj != NULL )
	{
		if( m_FreeTaskList.GetCount() < MAX_FREE_TASK )
		{
			pObj->Clear();
			m_FreeTaskList.Add(pObj);
		}
		else
		{
			pObj->Release();
		}
	}
	m_FreeTaskLock.Unlock();
}

//*=================================================================================
//*原型: void TSmartServer::ExecuteTask(TSmartTaskObj *pObj)
//*功能: 对SmartTask进行分析并执行
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
bool TSmartServer::ExecuteTask(TSmartTaskObj *pTaskObj)
{
	bool bResult = false ;

	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			long iCount = pTaskObj->GetChildTaskCount(pObj);
			
			for(int t=0; t< iCount; t++)
			{
				long nIndex = pTaskObj->GetChildTask(pObj, t);
				if( nIndex >= 0 )
				{
					//正在执行
					//printf("!!!!!!!!!!!!!!!!!!!1正在执行!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					if( pObj->IsExecuted() )
					{
						if( pObj->GetPriority() < pTaskObj->GetPriority(nIndex) )
						{
							ReportLog("任务:%s(%d), 任务代码:%s, 设备:%d, 暂停原有任务!", 
								pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
								pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
							pObj->Pause();

							pTaskObj->SetBeginFlag(nIndex);
							if( !pObj->Execute(pTaskObj, nIndex) )
							{
								ReportLog("任务:%s(%d), 任务代码:%s, 设备:%d, 不能执行新的任务!", 
									pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
									pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
								pObj->DestoryStack();
						
							}
							else 
							{
								pObj->DestoryStack();
								printf("任务:%s(%d), 任务代码:%s, 设备:%d, 执行成功!\n", 
								pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
								pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
								bResult = true ;
							}
						}
						else
						{
							if( pObj->IsOpen() )
							{
								pTaskObj->SetBeginFlag(nIndex);
								printf("------------------------------------------\n");
								if( !pObj->AddToTaskStack(pTaskObj, nIndex) )
								{
									ReportLog("任务:%s(%d), 任务代码:%s, 设备:%d,  设备忙, 不能执行新的任务!", 
										pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
										pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
									pObj->DestoryStack();
								}
								else
								{
									bResult = true ;

									Sleep(50);
								}
							}
						} 
					}
					//没有执行
					else 
					{
						//printf("-----未执行----nIndex=%d---\n",nIndex);
						bResult = true ;
						pTaskObj->SetBeginFlag(nIndex);
						if( !pObj->Execute(pTaskObj, nIndex) )
						{
//							printf("------执行-----\n");
							Sleep(50);
							pObj->Execute(pTaskObj, nIndex);
						}
						//else
						//	printf("-----未执行-----\n");
					}
				}
			}//for
		}
	}//for
	m_DocLock.Unlock();

	return bResult;
}

//*=================================================================================
//*原型: BOOL TSmartServer::AddSmartDoc(TSmartDocObj *pDocObj)
//*功能: 加入一个设备
//*参数: pDocObj -- 设备信息
//*返回: 成功与否
//*说明: 前置采集服务器类
//*=================================================================================
BOOL TSmartServer::AddSmartDoc(TSmartDocObj *pDocObj)
{
	m_DocLock.Lock();
	m_DocList.Add(pDocObj);
	m_DocLock.Unlock();
	return TRUE;
}

//*=================================================================================
//*原型: BOOL TSmartServer::DelSmartDoc(TSmartDocObj *pDocObj)
//*功能: 删除一个设备
//*参数: pDocObj -- 设备信息
//*返回: 成功与否
//*说明: 前置采集服务器类
//*=================================================================================
BOOL TSmartServer::DelSmartDoc(TSmartDocObj *pDocObj)
{
	if( pDocObj->m_nParentID > 0 )
	{
		m_DocLock.Lock();
		m_DocList.Remove(pDocObj);
		m_DocLock.Unlock();

		pDocObj->Release();
	}
	else
	{

	}

	return TRUE;
}

long TSmartServer::GetDocCount()
{ 
	long i=m_DocList.GetCount();
	return i; 
}


//*=================================================================================
//*原型: BOOL TSmartServer::StopSmartDoc(TSmartDocObj *pDocObj)
//*功能: 停止一个设备
//*参数: pDocObj -- 设备信息
//*返回: 成功与否
//*说明: 前置采集服务器类
//*=================================================================================
BOOL TSmartServer::StopSmartDoc(TSmartDocObj *pDocObj)
{
//	return m_DriverPool.StopSmartDoc(pDocObj);
	return TRUE;
}


//*=================================================================================
//*原型: BOOL StartSmrtDoc(TSmartDocObj *pDocObj)
//*功能: 启动一个设备
//*参数: pDocObj -- 设备信息
//*返回: 成功与否
//*说明: 前置采集服务器类
//*=================================================================================
BOOL TSmartServer::StartSmartDoc(TSmartDocObj *pDocObj)
{
	try
	{
		pDocObj->Start();
	}
	catch(TException& e)
	{
		OnError((char*)e.GetText());
		return FALSE;
	}
	return TRUE;
}

void TSmartServer::FinishedTask(TSmartDocObj *pDocObj, TSmartTaskObj *pTaskObj, long nIndex)
{
	//公告任务完成
	printf("----公告任务完成!\n");
	m_Channels.ReportFinished(pTaskObj);
	pTaskObj->ReportFinished();
	delete pTaskObj;
}

//*=================================================================================
//*原型: void TSmartServer::Noti fyTaskFinished(TSmartDocObj *pDocObj)
//*功能: 通知端口上的当前任务结束
//*参数: pDocObj  -- 设备信息
//*      pTaskObj -- 任务信息
//*      nIndex   -- 终端对应的设备索引
//*返回: 成功与否
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::NotifyTaskFinished(TSmartDocObj *pDocObj, TSmartTaskObj *pTaskObj, long nIndex)
{
	//总的任务已结束
	if( pTaskObj->IsTaskFinished() )
	{
		AddToFreeTaskList(pTaskObj);
		return ;
	}

	//从头继续执行
	if( pTaskObj->IsContinue(nIndex) )
	{
		long nIndex = pTaskObj->GetMaxPriorityTask(pDocObj);
		if( pDocObj->GetIOStatus() == IO_Status_Free )
		{
			pDocObj->Execute(pTaskObj, nIndex);
		}
	}
	else
	{
		//有被中断的任务
		if( pDocObj->HaveHistoryTask() )
		{
			//继续执行
			pDocObj->Continue();
		}
	}
}

//*=================================================================================
//*原型: void TSmartServer::OnError(LPTSTR pszErrorText)
//*功能: 服务器运行错误
//*参数: pszErrorText   -- 错误信息
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::OnError(LPTSTR pszErrorText)
{

}

//*=================================================================================
//*原型: void TSmartServer::OnNetError(TSmartDocObj *pObj, int nError)
//*功能: 网络或网络协议错误
//*参数: pObj   -- 具体参数
//*      nError -- 错误代码
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::OnNetError(TSmartDocObj *pObj, int nError)
{


}

//*=================================================================================
//*原型: void TSmartServer::OnDocError(TSmartDocObj *pObj, char *pszError)
//*功能: 设备出错
//*参数: pObj   -- 具体参数
//*      pszError -- 错误
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::OnDocError(TSmartDocObj *pObj, char *pszError)
{
	char szText[512];

	sprintf(szText, "%d&%s", pObj->m_nAuthID, pszError);
	WriteLog(szText);
}

//*=================================================================================
//*原型: void TSmartServer::Monitor()
//*功能: 对服务器监控(业务层分配的数据库句柄)
//*参数: 无
//*返回: 无
//*说明: 前置采集服务器类
//*=================================================================================
void TSmartServer::Monitor()
{

}

//*=================================================================================
//*原型: long TSmartServer::SendRequest(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
//*功能: 发送并接收请求
//*参数: 无
//*返回: 无
//*说明: 服务器提供给外部的API
//*=================================================================================
long TSmartServer::SendRequest(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	if( pDoc == NULL )
		return RET_PARAMETER_ERROR1;

	TSmartDocObj *pObj = NULL ;

	if( pDoc->m_nParentID > 0 )
	{
		pObj = GetParentDoc(pDoc->m_nParentID);
	}
	else
	{
		pObj = (TSmartDocObj*)pDoc;
	}

	if( pObj == NULL )
		return RET_PARAMETER_ERROR1;

	//不允许API调用重入或没有在执行任务
	if( pObj->GetIOStatus() == IO_Status_ExecuteApi || 
		pObj->GetIOStatus() != IO_Status_ExecuteCall )
	{
		return RET_PARAMETER_ERROR1;
	}

	return pObj->SendRequest((TCmdBuffer*)pBuffer);
}

//*=================================================================================
//*原型: long TSmartServer::BroadData(long nAuthID, char *pszBuffer, long nBufSize)
//*功能: 广播数据--将采集的数据广播到监控终端机器
//*参数: 无
//*返回: 无
//*说明: 服务器提供给外部的API
//*=================================================================================
long TSmartServer::BroadData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	m_OutThread.Broadcast(pDoc, pBuffer->pBuffer, pBuffer->nCmdSize);
	return RET_OK;
}

void TSmartServer::BroadDataEx(char *pszBuffer, long nLength)
{
	m_OutThread.Broadcast(NULL, pszBuffer, nLength);
}

void TSmartServer::BroadcastPro(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize)
{
	m_OutThread.BroadcastEx(pszCmd, pDoc, pData, nSize);
}

TSmartDocObj* TSmartServer::GetParentDoc(long nParent)
{
//	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->m_nAuthID == nParent )
			{
				//m_DocLock.Unlock();
				return pObj;
			}
		}
	}
//	m_DocLock.Unlock();

	return NULL;
}

//*=================================================================================
//*原型: long AddNewSmartDoc(long nParentID, long nPort, TSSmartDoc *pDoc)
//*功能: 新增加一台设备, 用于终端机签到
//*参数: 无
//*返回: 无
//*说明: 服务器提供给外部的API
//*=================================================================================
long TSmartServer::AddNewSmartDoc(long nParentID, long nPort, TSSmartDoc *pDoc)
{
	bool bResult = false ;

	m_DocLock.Lock();

	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->m_nAuthID == nParentID )
			{
				//不存在于内存中的子设备
				if( !pObj->IsChildDoc(pDoc->m_nAuthID) )
				{
					TSSmartDoc *pNewDoc = new TSSmartDoc;
					memcpy(pNewDoc, pDoc, sizeof(TSSmartDoc));
					pObj->AddChildDoc(pNewDoc);
				}
				bResult = true;
				break;
			}
		}
	}
	m_DocLock.Unlock();

	return bResult?RET_OK:RET_NG;
}

//*=================================================================================
//*原型: long DelSmartDoc(long nAuthID)
//*功能: 删除一台设备
//*参数: 无
//*返回: 无
//*说明: 服务器提供给外部的API
//*=================================================================================
long TSmartServer::DelSmartDoc(long nAuthID)
{
	return RET_OK;
}

long TSmartServer::EnableDevice(long nAuthID, bool bEnable)
{
	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->Enable(nAuthID, bEnable) ) 
			{
				break;
			}
		}
	}

	m_DocLock.Unlock();

	return RET_OK;
}

long TSmartServer::GetDeviceInfo(long nAuthID, TSDocInfo *pDocInfo)
{
	bool bFound = false;

	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->m_nAuthID == nAuthID )
			{
				pObj->GetInfo(0, pDocInfo);
				bFound = true;
				break;
			}
			else if( pObj->IsChildDoc(nAuthID) )
			{
				pObj->GetInfo(nAuthID, pDocInfo);
				bFound = true;
				break;
			}
		}
	}
	m_DocLock.Unlock();

	if( !bFound )
	{
		pDocInfo->m_nAuthID = nAuthID;
		pDocInfo->m_nChild = 0;
		pDocInfo->m_nStatus = 2;
		strcpy(pDocInfo->m_szTaskCode, "未加载!");
	}

	return RET_OK;
}

void TSmartServer::SendInitData(SOCKET hSocket, SOCKADDR_IN *psockAddr)
{
	TSmartPacket Packet;
	char *pBuffer = NULL ;
	long  nLength = 0 ;
	char  szTemp[256];

	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			sprintf(szTemp, "%d&%d&%d&%s&%d&%d&%d", 
				pObj->m_nAuthID, pObj->m_nDealCount, pObj->m_nFlow, 
				pObj->m_sLastDealTime, pObj->m_nCardID, pObj->m_nInMoney, 
				pObj->m_nOutMoney);

			Packet.Create(PACKET_CMD_1002, SERVER_SID);
			Packet.SetResult(RET_OK);
			Packet.AddItem((char*)szTemp, strlen(szTemp));
			Packet.AddEnd();

			pBuffer = Packet.GetBuffer();
			nLength = Packet.GetLength();

			sendto(hSocket, pBuffer, nLength, 0, (SOCKADDR*)psockAddr, sizeof(SOCKADDR_IN));

			//子设备发任务包
			for(int k=0; k< pObj->m_ChildDoc.GetCount(); k++)
			{
				TSSmartDoc *pSmartDoc = (TSSmartDoc *)pObj->m_ChildDoc[k];
				if( pSmartDoc != NULL )
				{
					sprintf(szTemp, "%d&%d&%d&%s&%d&%d&%d", 
						pSmartDoc->m_nAuthID, pSmartDoc->m_nDealCount, pSmartDoc->m_nFlow, 
						pSmartDoc->m_sLastDealTime, pSmartDoc->m_nCardID, pSmartDoc->m_nInMoney, 
						pSmartDoc->m_nOutMoney);

					Packet.Create(PACKET_CMD_1002, SERVER_SID);
					Packet.SetResult(RET_OK);
					Packet.AddItem((char*)szTemp, strlen(szTemp));
					Packet.AddEnd();

					pBuffer = Packet.GetBuffer();
					nLength = Packet.GetLength();

					sendto(hSocket, pBuffer, nLength, 0, (SOCKADDR*)psockAddr, sizeof(SOCKADDR_IN));
				}
			}
		}
	}
}

//*=================================================================================
//*原型: long TSmartServer::FindBusFromDocArray(TSSmartDoc *pSmartDoc, long i, long nRecCount)
//*功能: 从未加入的档案表中查找相同的总线设置
//*参数: 无
//*返回: 无
//*说明: 服务器提供给外部的API
//*=================================================================================
long TSmartServer::FindBusFromDocArray(TSSmartDoc *pSmartDoc, long i, long nRecCount)
{
	for(long k=i+1; k< nRecCount; k++)
	{
		if( !strcmp(pSmartDoc[i].m_szAddr, pSmartDoc[k].m_szAddr) && 
			!strcmp(pSmartDoc[i].m_szPort, pSmartDoc[k].m_szAddr) )
		{
			return k;
		}
	}

	return -1;
}

//*=================================================================================
//*原型: long TSmartServer::FindBusFromDocList(TSmartDocObj *pDoc)
//*功能: 从已加入的档案表中查找相同的总线设置
//*参数: 无
//*返回: 无
//*说明: 服务器提供给外部的API
//*=================================================================================
long TSmartServer::FindBusFromDocList(TSmartDocObj *pDoc)
{
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pBus = (TSmartDocObj*)m_DocList.Get(i);
		if( pBus != NULL )
		{
			if( !strcmp(pBus->m_szAddr, pDoc->m_szAddr) && 
				!strcmp(pBus->m_szPort, pDoc->m_szAddr) )
			{
				return i;
			}
		}
	}

	return -1;
}

void TSmartServer::AssignBusHandle(TSmartDocObj *pDoc)
{
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pBus = (TSmartDocObj*)m_DocList.Get(i);
		if( pBus != NULL && pDoc != pBus )
		{
			if( !strcmp(pBus->m_szAddr, pDoc->m_szAddr) && 
				!strcmp(pBus->m_szPort, pDoc->m_szAddr) && 
				pBus->m_nCommMode == pDoc->m_nCommMode )
			{
				pBus->SetHandle(pDoc->GetHandle());
				pBus->SetReadOver(&pDoc->m_ReadOver);
				pBus->SetWriteOver(&pDoc->m_WriteOver);
			}
		}
	}
}
