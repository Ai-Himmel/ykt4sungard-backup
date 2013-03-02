// TSmartServer.h: interface for the TSmartServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTSERVER_H__0D1A5D7E_5745_4AC8_A436_14BF24174AFD__INCLUDED_)
#define AFX_TSMARTSERVER_H__0D1A5D7E_5745_4AC8_A436_14BF24174AFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TServer.h"
#include "TSmartOutThread.h"
#include "TDatabase.h"
#include "TSmartTask.h"
#include "TSmartModule.h"
#include "TSmartMonitor.h"
#include "TSmartProtocol.h"
#include "TSmartChannels.h"

const long MAX_FREE_TASK = 30 ;
const long MAX_BUSY_TASK = 10 ;

extern TLock    g_ExecLock;

//*------------------------------------------------------------------------------------
//*名称: TSmartServer
//*功能: 前置采集服务器
//*------------------------------------------------------------------------------------
class TSmartServer : public TServer 
{
protected:
	TSmartOutThread	  m_OutThread;
	TSmartProtocol	  m_SmartProtocol;
	TSmartMonitor     m_SmartMonitor;

	TList             m_DocList;
	TLock             m_DocLock;

	TList             m_TaskList;
	TLock             m_TaskLock;

	TList             m_FreeTaskList;
	TLock             m_FreeTaskLock;

	friend class TExportFunc;

public:
	TSmartModuleManager  m_SmartModule;
	TSServerInfo         m_SmartInfo;
	TSmartChannels		 m_Channels;
	long				 nTotalMemory;
	long				 nUseMemory;
	long				 nFreeMemory;
	TSmartTaskObj		m_CollDataTaskObj;
	long				m_nCollData_Tick;	//采集数据任务的间隔时间
	long				m_nNoTask_Tick;		//没有任务时的心跳间隔时间

public:
	virtual void OnServerStart() { }
	virtual void OnServerShutdown() { }

	virtual void OnNetError(TSmartDocObj *pObj, int nError);
	virtual void OnError(LPTSTR pszErrorText);
	virtual void OnDocError(TSmartDocObj *pObj, char *pszError);

protected:
	void InitInstance();
	void ExitInstance();
	void Run();
	virtual void Monitor();

	void InitSmartDocList();

	TSmartTaskObj* GetFreeTaskObj();
	void AddToFreeTaskList(TSmartTaskObj *pObj);
	bool ExecuteTask(TSmartTaskObj *pObj);

	void AddChildDoc(TSmartDocObj *pObj, TSSmartDoc *pSmartDoc, long nRecCount);
	TSmartDocObj* GetParentDoc(long nParent);

	long FindBusFromDocList(TSmartDocObj *pDoc);
	long FindBusFromDocArray(TSSmartDoc *pSmartDoc, long i, long nRecCount);

	friend class TSmartMonitor;

public:
	TSmartServer();
	virtual ~TSmartServer();

	long GetBusyTask();
	bool IsFullTask() ;
	long GetDocCount();

	BOOL AddSmartDoc(TSmartDocObj *pDocObj);
	BOOL DelSmartDoc(TSmartDocObj *pDocObj);
	BOOL StopSmartDoc(TSmartDocObj *pDocObj);
	BOOL StartSmartDoc(TSmartDocObj *pDocObj);

	TSmartDocObj* CreateSmartDoc(TSSmartDoc *pDoc);
	void AssignBusHandle(TSmartDocObj *pDoc);

	void NotifyTaskFinished(TSmartDocObj *pDocObj, TSmartTaskObj *pTaskObj, long nIndex);
	void FinishedTask(TSmartDocObj *pDocObj, TSmartTaskObj *pTaskObj, long nIndex);

	long SendRequest(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);
	long BroadData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);
	void BroadDataEx(char *pszBuffer, long nLength);
	void BroadcastPro(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize);
	long AddNewSmartDoc(long nParentID, long nPort, TSSmartDoc *pDoc);
	long DelSmartDoc(long nAuthID);

	long EnableDevice(long nAuthID, bool bEnable);
	long GetDeviceInfo(long nAuthID, TSDocInfo *pDocInfo);
	void SendInitData(SOCKET hSocket, SOCKADDR_IN *psockAddr);
	bool GetSysItemInfo(HQUERY	hQuery, 
								 char *pszPath, 
								 DWORD nType, 
								 PDH_FMT_COUNTERVALUE& fmtValue);
	bool GetMemoryInfo();
	bool ExecuteCollDataTask();
};

#endif // !defined(AFX_TSMARTSERVER_H__0D1A5D7E_5745_4AC8_A436_14BF24174AFD__INCLUDED_)
