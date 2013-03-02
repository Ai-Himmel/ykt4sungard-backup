// TSmartOutThread.h: interface for the TSmartOutThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTOUTTHREAD_H__C6EDEDF5_901D_4276_A849_7F5FD1034A90__INCLUDED_)
#define AFX_TSMARTOUTTHREAD_H__C6EDEDF5_901D_4276_A849_7F5FD1034A90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SmartServer.h"
#include "TSmartPacket.h"

class TSmartServer;

//************************************************************************************
//*名称: TSmartOutThread
//*功能: 接受监控程序远程请求线程类
//************************************************************************************
class TSmartOutThread : public TThread
{
	struct TSOUTUser
	{
		char   szMD5[128]; //MD5加密串
		char   szHost[32]; //客户机名或IP地址
		int    nPort;      //客户机的通知端口
		long   nSID;       //SID唯一标识
		time_t tmCreate;   //登录创建时间
		DWORD  dwLastTick; //最后活动时间点
		SOCKADDR_IN sockAddr;
	};

	typedef long (*lpfnPacketFunc)(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);

	struct TSPacketFunc
	{
		char			*pText;
		char            *pCmd;
		lpfnPacketFunc  lpFunc;
	};

protected:
	TSmartServer* m_pServer;

	long    m_nMaxUser;         //最大用户数

	SOCKET	m_hNotifySocket;
	int     m_nPort;

	SOCKET  m_hServerSocket;
	TList   m_ClientList;
	TLock   m_ClientLock;

	static  long nKey;
	static  TSPacketFunc Function[256];

protected:
	void Run();
	void OnShutdown();
	void OnStart();

	void DestoryClient();
	void CloseOutSocket();
	long Recv(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut);
	long Send(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut);

	bool ReadRequestPacket(SOCKET hSocket, TSmartPacket& Packet);
	void Dispatch(SOCKET hSocket, SOCKADDR_IN *psockAddr, TSmartPacket& Packet);
	void Monitor();
	bool Wait(SOCKET hSocket, int nFlag=0, long nTimeOut=1000);
	void ProcessRequest(SOCKET hSocket,SOCKADDR_IN *psockAddr);
	bool CheckPacket(SOCKADDR_IN *psockAddr, TSmartPacket& Packet);

	bool AddUser(TSOUTUser *pUser);
	void DelUser(SOCKADDR *pSockAddr, long nSID);

public:
	TSmartOutThread();
	virtual ~TSmartOutThread();

	void Initialized(int nPort, TSmartServer *pServer);
	void Broadcast(TSSmartDoc *pDoc, void *pData, long nSize);
	void BroadcastEx(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize);
	void BroadShutdown();

	long RecvBuffer(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut);
	long SendBuffer(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut);

	static long GetKey();
	static char* GetMD5();

	static long OnLogin(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);
	static long OnLogout(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);
	static long OnShutdownServer(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);
	static long OnStartDevice(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);
	static long OnStopDevice(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);
	static long OnGetServerInfo(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);
	static long OnGetDeviceInfo(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread);

};

#endif // !defined(AFX_TSMARTOUTTHREAD_H__C6EDEDF5_901D_4276_A849_7F5FD1034A90__INCLUDED_)
