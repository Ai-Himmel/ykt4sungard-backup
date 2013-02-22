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
#pragma comment ( lib , "Pdh.lib" )
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
	nTotalMemory=0;
	nUseMemory=0;
	nFreeMemory=0;

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
bool TSmartServer::GetSysItemInfo(HQUERY	hQuery, 
								 char *pszPath, 
								 DWORD nType, 
								 PDH_FMT_COUNTERVALUE& fmtValue)
{
	DWORD dwType;
	HCOUNTER  hCounter ;
	if( PdhAddCounter(hQuery, pszPath, 0, &hCounter) != ERROR_SUCCESS )
		return false;

	if( PdhCollectQueryData(hQuery) != ERROR_SUCCESS )
		return false;

	if( PdhGetFormattedCounterValue(hCounter, nType, &dwType, &fmtValue) != ERROR_SUCCESS )
		return false;

	return true;
}

bool TSmartServer::GetMemoryInfo()
{
	HQUERY          hQuery;
	PDH_STATUS      pdhStatus;
	PDH_FMT_COUNTERVALUE  fmtValue;
	CHAR           szPathBuffer[MAX_PATH] = {'\0'};
	// Open the query object.
	pdhStatus = PdhOpenQuery (0, 0, &hQuery);
	if(pdhStatus!=ERROR_SUCCESS)
		return false;
	strcpy(szPathBuffer,"\\Memory\\Commit Limit"); 
	if(!GetSysItemInfo(hQuery, szPathBuffer, PDH_FMT_LONG,fmtValue))
		return false;
	nTotalMemory=fmtValue.longValue/1024;
	strcpy(szPathBuffer,"\\Memory\\Committed Bytes"); 
	if(!GetSysItemInfo(hQuery, szPathBuffer, PDH_FMT_LONG,fmtValue))
		return false;
	nUseMemory=fmtValue.longValue/1024;
	strcpy(szPathBuffer,"\\Memory\\Available Bytes"); 
	if(!GetSysItemInfo(hQuery, szPathBuffer, PDH_FMT_LONG,fmtValue))
		return false;
	nFreeMemory=fmtValue.longValue/1024;

	/*
\\Processor(_Total)\\% Processor Time CPU使用率
\\System\\Processes 当前系统进程数
\\System\\Threads 当前系统线程数
\\Memory\\Commit Limit 总共内存数K (包括虚拟内存)
\\Memory\\Committed Bytes 已用内存数K (包括虚拟内存)
\\TCP\\Connections Active 系统中已建立的 TCP连接个数
其它Object Items 可以利用PdhEnumObjects()和PdhEnumObjectItems()得到
反正我只要用到上面的东东:)
*/
	// Close the query.
	pdhStatus = PdhCloseQuery (hQuery);
	return true;
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
	m_nCollData_Tick=sr.m_nCollData_Tick;
	m_nNoTask_Tick=sr.m_nNoTask_Tick;

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
		ReportLog("连接到金仕达中间层出错!",  e.GetText());
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
			printf("授权号			= %.8X\n",pSmartDoc[mm].m_nAuthID);
			printf("ID号			= %s\n",pSmartDoc[mm].m_szDeviceID);
			printf("服务器端口总数	= %d\n",pSmartDoc[mm].m_nPortCount);
			printf("服务器端口号	= %d\n",pSmartDoc[mm].m_nSMTPort);
			printf("设备级联级数	= %d\n",pSmartDoc[mm].m_nLevel);
			printf("设备级联参数	= %s\n",pSmartDoc[mm].m_szLevelArray);
			Sleep(50);
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

		//如果没有获取到系统的设备档案数据,则始终向金仕达发获取档案的任务.
		while(1 )
		{
			if( GetDocCount() <= 0 )
			{
				ReportLog("没有设备档案信息! 服务器自动重新装入设备档案表!");
				InitSmartDocList();
				Sleep(4000);				
			}
			else
			{
				break;
			}
		}

		bool  bRet=false;
		long  nNoTaskTick=0,nTick=0,nCollDataTick=0;
		
		m_CollDataTaskObj.nTaskPlanID  = 100 ;
		strcpy(m_CollDataTaskObj.szTaskName, "收数");
		m_CollDataTaskObj.nTaskCycle   = 1 ;
		GetCurDateTime(m_CollDataTaskObj.szBeginTime);
		m_CollDataTaskObj.nRepeatTime  = 0 ;                 //持续多长时间（分钟）
		m_CollDataTaskObj.nRepeatTimes = 0;                //重复次数

		int  k = 0;
		long i = 0 ;
		for(i=0; i< m_DocList.GetCount(); i++)
		{
			TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
			if(!pObj->m_nParentID)
			{
				m_CollDataTaskObj.pTask[k].nTaskID     = i + 100 ;
				m_CollDataTaskObj.pTask[k].nTaskPlanID = 01;
				m_CollDataTaskObj.pTask[k].nAuthID     = pObj->m_nAuthID ;
				strcpy(m_CollDataTaskObj.pTask[k].szTaskCode, "01");
				strcpy(m_CollDataTaskObj.pTask[k].szName, "实时收数");
				strcpy(m_CollDataTaskObj.pTask[k].szType, "01");
				m_CollDataTaskObj.pTask[k].nPriority = 0 ;
				m_CollDataTaskObj.nTask++;  //设备总数量
				k++;
			}
		}
		m_CollDataTaskObj.SetBeginTime();
		ExecuteTask(&m_CollDataTaskObj);
		//执行任务
		static TSmartTaskObj curObj;
		BOOL bNoTask=FALSE;
		int ret=-1;
		nCollDataTick = GetTickCount();
		while( !IsShutdown() )
		{	
				bRet = false;
				//如果后台没有任务要处理，则开始采集数据任务
				while(bNoTask)
				{
					ExecuteCollDataTask();
					nTick = GetTickCount();
					nCollDataTick = nTick;
					//如果采集数据时间超过了2秒钟，则跳出，开始向后台请求新的任务
					if(nTick-nNoTaskTick>=m_nNoTask_Tick)//2秒
					{
						break;
					}
					Sleep(1000);
				}
				nTick=GetTickCount();
				//如果距离上次采集数据的时间已经超过了5秒钟，则再发起一次采集数据的任务
				if(nTick-nCollDataTick>=m_nCollData_Tick)
				{
					nCollDataTick = nTick;
					ExecuteCollDataTask();
				}
				//发送心跳请求包
				ret=m_Channels.SendTick();
				if(ret!=RET_OK)
				{
					continue;
				}
				ZeroMemory(&curObj, sizeof(curObj));
				curObj.Clear();
				ret=m_Channels.GetSmartTaskPlan(&curObj);
				switch(ret)
				{	
					case RET_OK:
						ReportLog("选中任务: %s(%d), 执行次数:%d, 执行时长:%d, 设备数:%d.\n",curObj.szTaskName, curObj.nTaskPlanID,curObj.nRepeatTimes, curObj.nRepeatTime, curObj.nTask); 
						curObj.SetBeginTime();
						bRet = ExecuteTask(&curObj);
						if(!bRet)
						{
							for(int j=0; j< curObj.nTask; j++)
							{
								TSResultData  data;
								ZeroMemory(&data, sizeof(data));
								strcpy(data.sMsg, "任务执行失败[可能终端正忙]!");
								m_Channels.ReportTaskResult(&curObj.pTask[j], RET_TERME_NOANSWER, &data);
							}
						}
						bNoTask=FALSE;
						break;
					case RET_NOTASK:
						ReportLog("金仕达没有任务下达"); 
						nNoTaskTick = GetTickCount();
						bNoTask=TRUE;
						break;
					default:
						ReportLog("向金仕达请求任务失败"); 
						bNoTask=FALSE;
						break;
				}
			/*
			if(!GetMemoryInfo())
			{
				ReportError("获取系统内存信息失败,请关闭前置程序,重新启动!");				
			}
			printf("TotalMemory %dK,UseMemory %dK,FreeMemory %dK\n",nTotalMemory,nUseMemory,nFreeMemory);	
			if(nFreeMemory/1024<10)
			{
				ReportError("可用内存小于10M，请关闭一些其它无用的程序");				
			}
			*/
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
	return;
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
			if(pObj->m_hThread==NULL) pObj->Start();
			long iCount = pTaskObj->GetChildTaskCount(pObj);
			for(int t=0; t< iCount; t++)
			{
				long nIndex = pTaskObj->GetChildTask(pObj, t);
				if( nIndex >= 0 )
				{				
					if( pObj->IsExecuted() )
					{
						//if( pObj->GetPriority() < pTaskObj->GetPriority(nIndex) )
						//{
							ReportLog("任务:%s(%d), 任务代码:%s, 设备:%d, 准备暂停原有任务!",pTaskObj->szTaskName, pTaskObj->nTaskPlanID, pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
							pObj->Pause();							
							pTaskObj->SetBeginFlag(nIndex);
							if( !pObj->Execute(pTaskObj, nIndex) )
							{	
								//2005-12-20 wenjian comment begin
								//任务执行不成功,则再执行一次
								//050930 
								/*
								Sleep(500);
								if( !pObj->Execute(pTaskObj, nIndex) )
								{
									ReportLog("任务:%s(%d), 任务代码:%s, 设备:%d, 任务第二次执行失败!",pTaskObj->szTaskName, pTaskObj->nTaskPlanID, pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
								}
								else //051014 by dengjun
								{
									printf("任务:%s(%d), 任务代码:%s, 设备:%d, 任务第二次执行成功!\n", 
									pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
									pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
									bResult = true ;
								}
								*/
								bResult = false;
								ReportLog("任务:%s(%d), 任务代码:%s, 设备:%d, 任务执行失败!",pTaskObj->szTaskName, pTaskObj->nTaskPlanID, pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
								//2005-12-20 wenjian comment end
							}
							else 
							{								
								printf("任务:%s(%d), 任务代码:%s, 设备:%d, 任务首次执行成功!\n", 
								pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
								pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
								bResult = true ;
							}
						//}
						/*
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
									//pObj->DestoryStack();
								}
								else
								{
									bResult = true ;

									Sleep(50);
								}
								
							}
						} 
						*/
					}
					//没有执行
					else 
					{			
						pTaskObj->SetBeginFlag(nIndex);
						if( !pObj->Execute(pTaskObj, nIndex) )
						{	
							bResult = false;
							ReportLog("任务:%s(%d), 任务代码:%s, 设备:%d, 任务执行失败!",pTaskObj->szTaskName, pTaskObj->nTaskPlanID, pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
						}
						else 
						{								
							printf("任务:%s(%d), 任务代码:%s, 设备:%d, 任务执行成功!\n", 
							pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
							pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
							bResult = true ;
						}
					}
				}
			}//for
		}
	}//for
	m_DocLock.Unlock();
	return bResult;
}


bool TSmartServer::ExecuteCollDataTask()
{
	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if(pObj->m_hThread==NULL)
				pObj->Start();
			pObj->Execute(&m_CollDataTaskObj,0);
		}
	}//for
	m_DocLock.Unlock();
	return true;
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
	return;
	m_Channels.ReportFinished(pTaskObj);
	pTaskObj->ReportFinished();
	pTaskObj->Clear();
	//memset(pTaskObj,0,sizeof(TSmartTaskObj));
//	delete pTaskObj;
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
	return ;
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
	char szText[1024];

	memset(szText, 0x00, sizeof szText);
	
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
