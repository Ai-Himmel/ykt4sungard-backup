// TSmartOutThread.cpp: implementation of the TSmartOutThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartOutThread.h"
#include "TSmartRegister.h"
#include "TSmartServer.h"

const int MAX_REFRESH_TIME = 120 ;

long TSmartOutThread::nKey = 1000;

TSmartOutThread::TSPacketFunc TSmartOutThread::Function[256] = 
{
	"��¼", PACKET_CMD_LOGIN,  TSmartOutThread::OnLogin, 
	"ע��", PACKET_CMD_LOGOUT, TSmartOutThread::OnLogout,
	"ֹͣ", PACKET_CMD_SHUTDOWN, TSmartOutThread::OnShutdownServer,
	"�����豸", PACKET_CMD_STARTRUN, TSmartOutThread::OnStartDevice,
	"ֹͣ�豸", PACKET_CMD_STOPRUN, TSmartOutThread::OnStopDevice,
	"�õ���������Ϣ", PACKET_CMD_GETSERVERINFO, TSmartOutThread::OnGetServerInfo,
	"�õ��豸��Ϣ",   PACKET_CMD_GETDEVICEINFO, TSmartOutThread::OnGetDeviceInfo,
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TSmartOutThread::TSmartOutThread()
{
	m_pServer = NULL ;

	m_nMaxUser = 10 ;

	m_hNotifySocket = INVALID_SOCKET ;
	m_hServerSocket = INVALID_SOCKET ;

	m_ClientList.Clear();
}

TSmartOutThread::~TSmartOutThread()
{
	CloseOutSocket();
	DestoryClient();
}

//*=================================================================================
//*ԭ��: void TSmartOutThread::Initialized(TSmartServer& Server)
//*����: ��ʼ�����ݷַ��߳�
//*����: Server -- ������
//*����: ��
//*˵��: ��
//*=================================================================================
void TSmartOutThread::Initialized(int nPort, TSmartServer *pServer)
{
	m_pServer = pServer ;
	m_nPort = nPort ;

	//֪ͨ�˿�ʹ��UDP
	m_hNotifySocket = socket(AF_INET, SOCK_DGRAM, 0);
	if( m_hNotifySocket == INVALID_SOCKET )
	{
		throw TException("����UDP�׽���ʧ��!", (DWORD)WSAGetLastError());
	}

	//��������ʹ��TCP
	m_hServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if( m_hServerSocket == INVALID_SOCKET )
	{
		CloseOutSocket();
		throw TException("����TCP�׽���ʧ��!", (DWORD)WSAGetLastError());
	}

	int nAnsy = 1 ;
	if( ioctlsocket(m_hServerSocket, FIONBIO, (DWORD*)&nAnsy) == SOCKET_ERROR )
	{
		CloseOutSocket();
		throw TException("����TCP����ʧ��!", (DWORD)WSAGetLastError());
	}

	SOCKADDR_IN  sockAddr;

	ZeroMemory(&sockAddr, sizeof(sockAddr));

	sockAddr.sin_family = AF_INET ;
	sockAddr.sin_port = htons(nPort);
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if( bind(m_hServerSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR )
	{
		CloseOutSocket();
		throw TException("���ܰTCP��!", (DWORD)WSAGetLastError());
	}

	if( listen(m_hServerSocket, 5) == SOCKET_ERROR )
	{
		CloseOutSocket();
		throw TException("TCP����Listen!", (DWORD)WSAGetLastError());
	}
}

void TSmartOutThread::OnShutdown()
{
	TThread::OnShutdown();
}

void TSmartOutThread::OnStart()
{
	TThread::OnStart();

	//����ʼ��Ҫ��֪ͨ��Ϣ
	TSOUTUser *pUser = new TSOUTUser;

	ZeroMemory(pUser, sizeof(TSOUTUser));

	pUser->nPort = m_nPort + 1 ;
	pUser->nSID = 0 ;
	strcpy(pUser->szHost, "127.0.0.1");
	time(&pUser->tmCreate);
	pUser->dwLastTick = GetTickCount();

	pUser->sockAddr.sin_family = AF_INET ;
	pUser->sockAddr.sin_port = htons(pUser->nPort);
	pUser->sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	m_ClientList.Add(pUser);
}

//*=================================================================================
//*ԭ��: void TSmartOutThread::Broadcast(void *pData)
//*����: �ַ�����
//*����: pData -- Ҫ�ַ�������
//*����: ��
//*˵��: ����UDP�ַ�
//*=================================================================================
void TSmartOutThread::Broadcast(TSSmartDoc *pDoc, void *pData, long nSize)
{
	for(int i=0; i< m_ClientList.GetCount(); i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			sendto(m_hNotifySocket, (char*)pData, nSize, 0, (SOCKADDR*)&pUser->sockAddr, sizeof(pUser->sockAddr));
			pUser->dwLastTick = GetTickCount();
		}
	}


#ifdef __BROADCAST_OUT__
	TSmartPacket  Packet;
	long   nLength;
	char  *pBuffer;

	Packet.CreateNotify(0, pDoc, pData, nSize);

	pBuffer = Packet.GetBuffer();
	nLength = Packet.GetLength();

	ReportLog("�㲥Data:<%d> [%s]\n", nLength, pBuffer);

	//	m_ClientLock.Lock();
	for(int i=0; i< m_ClientList.GetCount(); i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			sendto(m_hNotifySocket, pBuffer, nLength, 0, (SOCKADDR*)&pUser->sockAddr, sizeof(pUser->sockAddr));
			pUser->dwLastTick = GetTickCount();
		}
	}
//	m_ClientLock.Unlock();
#endif 
}

//*=================================================================================
//*ԭ��: void TSmartOutThread::Broadcast(void *pData)
//*����: �ַ�����
//*����: pData -- Ҫ�ַ�������
//*����: ��
//*˵��: ����UDP�ַ�
//*=================================================================================
void TSmartOutThread::BroadcastEx(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize)
{
#ifdef __BROADCAST_OUT__
	TSmartPacket  Packet;
	long   nLength;
	char  *pBuffer;

	Packet.Create(pszCmd, SERVER_SID);
	Packet.SetResult(RET_OK);
	Packet.AddItem((char*)pData, nSize);
	Packet.AddEnd();

	pBuffer = Packet.GetBuffer();
	nLength = Packet.GetLength();

	if( !strcmp(PACKET_CMD_1003, pszCmd) )
		ReportLog("�㲥:<%d> [%s]\n", nLength, pBuffer);

	for(int i=0; i< m_ClientList.GetCount(); i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			sendto(m_hNotifySocket, pBuffer, nLength, 0, (SOCKADDR*)&pUser->sockAddr, sizeof(pUser->sockAddr));
			pUser->dwLastTick = GetTickCount();
		}
	}
#endif
}

void TSmartOutThread::BroadShutdown()
{
	TSmartPacket  Packet;
	long   nLength;
	char  *pBuffer;

	Packet.Create(PACKET_CMD_SHUTDOWN, SERVER_SID);
	Packet.SetResult(RET_OK);
	Packet.AddEnd();

	pBuffer = Packet.GetBuffer();
	nLength = Packet.GetLength();

	for(int i=0; i< m_ClientList.GetCount(); i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			sendto(m_hNotifySocket, pBuffer, nLength, 0, (SOCKADDR*)&pUser->sockAddr, sizeof(pUser->sockAddr));
			pUser->dwLastTick = GetTickCount();
		}
	}
}


//*=================================================================================
//*ԭ��: bool WaitRead(long nTimeOut)
//*����: �ȴ����ͻ���
//*����: ��
//*����: ��
//*˵��: ��
//*=================================================================================
bool TSmartOutThread::Wait(SOCKET hSocket, int nFlag, long nTimeOut)
{
	timeval tm;
	fd_set  fdset;

	tm.tv_sec = nTimeOut/1000;
	tm.tv_usec = nTimeOut%1000;

	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);

	int nResult;

	if( !nFlag ) 
		nResult = select(0, &fdset, NULL, NULL, &tm);
	else
		nResult = select(0, NULL, &fdset, NULL, &tm);

	if( nResult >= 0 )
	{
		if( FD_ISSET(hSocket, &fdset) )
			return true;
	}
	else
	{
		Sleep(100);
	}

	return false;
}

//*=================================================================================
//*ԭ��: long Recv(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut)
//*����: ����һ������
//*����: ��
//*����: ���յĳ���
//*˵��: TCP����(������)
//*=================================================================================
long TSmartOutThread::Recv(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut)
{
	if( Wait(hSocket, 0, 1000) )
	{
		long nLen = (long)recv(hSocket, pszBuffer, nBufSize, 0);
		if( nLen <= 0 )
		{
			if( WSAGetLastError() != WSAEWOULDBLOCK )
			{
				return RET_SYSERROR;
			}
			else
			{
				nLen = RET_TIMEOUT;

				if( Wait(hSocket, 0, nTimeOut) )
				{
					nLen = (long)recv(hSocket, pszBuffer, nBufSize, 0);
				}
			}
		}
		return nLen;
	}
	return RET_SYSERROR;
}

//*=================================================================================
//*ԭ��: long Send(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut)
//*����: ����һ������
//*����: ��
//*����: ���͵ĳ���
//*˵��: TCP����(������)
//*=================================================================================
long TSmartOutThread::Send(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut)
{
	if( Wait(hSocket, 1, 0) )
	{
		long nLen = (long)send(hSocket, pszBuffer, nBufSize, 0);
		if( nLen <= 0 )
		{
			if( WSAGetLastError() != WSAEWOULDBLOCK )
			{
				return RET_SYSERROR;
			}
			else
			{
				nLen = RET_TIMEOUT;

				if( Wait(hSocket, 1, nTimeOut) )
				{
					nLen = (long)send(hSocket, pszBuffer, nBufSize, 0);
				}
			}
		}
		return nLen;
	}
	return RET_SYSERROR;
}

//*=================================================================================
//*ԭ��: long RecvBuffer(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut)
//*����: ������һ������, ��ֱ����ʱ
//*����: ��
//*����: ���͵ĳ���
//*˵��: TCP����(������)
//*=================================================================================
long TSmartOutThread::RecvBuffer(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut)
{
	long nTotalLength = 0 ;
	long nBlock = 0 ;
	long nLength = 0 ;
	DWORD dwTick = GetTickCount();

	while( nBufSize > 0 )
	{
		if( nBufSize > 8192 ) 
			nBlock = 8192 ;
		else
			nBlock = nBufSize ;

		nLength = Recv(hSocket, pszBuffer+nTotalLength, nBlock, nTimeOut);
		if( nLength > 0 )
		{
			nTotalLength += nLength ;
			nBufSize -= nLength ;
		}
		else if( nLength == 0 )
		{
			break;
		}

		if( GetTickCount() - dwTick > (DWORD)nTimeOut )
			break;
	}

	return nTotalLength;
}

long TSmartOutThread::SendBuffer(SOCKET hSocket, char *pszBuffer, long nBufSize, long nTimeOut)
{
	long nTotalLength = 0 ;
	long nBlock = 0 ;
	long nLength = 0 ;
	DWORD dwTick = GetTickCount();

	while( nBufSize > 0 )
	{
		if( nBufSize > 8192 ) 
			nBlock = 8192 ;
		else
			nBlock = nBufSize ;

		nLength = Send(hSocket, pszBuffer+nTotalLength, nBlock, nTimeOut);
		if( nLength > 0 )
		{
			nTotalLength += nLength ;
			nBufSize -= nLength ;
		}
		else if( nLength == 0 )
		{
			break;
		}

		if( GetTickCount() - dwTick > (DWORD)nTimeOut )
			break;
	}

	return nTotalLength;
}

//*=================================================================================
//*ԭ��: void TSmartOutThread::Run()
//*����: ����ͻ��˵�����, ��������Ӧ
//*����: ��
//*����: ��
//*˵��: 
//*=================================================================================
void TSmartOutThread::Run()
{
	SOCKET       hClient;
	SOCKADDR_IN  sockAddr;
	int nLen = sizeof(sockAddr);
	int nBlockMode = 1 ;

	DWORD dwTick = GetTickCount();

	while( !IsShutdown() )
	{
		if( Wait(m_hServerSocket, 0, 1000) )
		{
			ZeroMemory(&sockAddr, sizeof(sockAddr));

			hClient = accept(m_hServerSocket, (SOCKADDR*)&sockAddr, &nLen);
			if( hClient != INVALID_SOCKET )
			{	
				if( ioctlsocket(hClient, FIONBIO, (DWORD*)&nBlockMode) != SOCKET_ERROR )
				{
					ProcessRequest(hClient, &sockAddr);
				}
				shutdown(hClient, SB_BOTH);
				closesocket(hClient);
				hClient = INVALID_SOCKET;
			}
		}

		if( GetTickCount() - dwTick > 10000 )
		{
			Monitor();
			dwTick = GetTickCount();
		}
	}

	CloseOutSocket();
}

//*=================================================================================
//*ԭ��: void ProcessRequest(SOCKET hSocket)
//*����: ����ͻ���������
//*����: ��
//*����: ��
//*˵��: �ȶ����ͷ, �ٶ�������, Ȼ���ٴ�������
//*=================================================================================
void TSmartOutThread::ProcessRequest(SOCKET hSocket, SOCKADDR_IN *psockAddr)
{
	TSmartPacket Packet;

	try
	{
		if( ReadRequestPacket(hSocket, Packet) )
		{
			if( CheckPacket(psockAddr, Packet) )
			{
				Dispatch(hSocket, psockAddr, Packet);
			}
		}
	}
	catch(TException& e)
	{
		WriteLog(e.GetText());
	}
	catch(...)
	{
		WriteLog("�ͻ������߳���δ֪�쳣!");
	}
}

//*=================================================================================
//*ԭ��: bool CheckPacket(TSmartPacket& Packet)
//*����: ����Ƿ�Ϊ�Ϸ����û���
//*����: ��
//*����: ��
//*˵��: �򵥵���֤�ֶ�
//*=================================================================================
bool TSmartOutThread::CheckPacket(SOCKADDR_IN *psockAddr, TSmartPacket& Packet)
{
	char *pCmd = Packet.GetCmd();

	if( !_strcmpi(pCmd, PACKET_CMD_LOGIN) ) 
		return true;

	long nSID = Packet.GetSID();

	m_ClientLock.Lock();
	for(int i=0; i< m_ClientList.GetCount(); i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			if( pUser->nSID == nSID ) 
			{
				char szHost[32];
				strcpy(szHost, inet_ntoa(psockAddr->sin_addr));

				if( !strcmp(szHost, pUser->szHost) )
				{
					m_ClientLock.Unlock();
					return true;
				}
			}
		}
	}
	m_ClientLock.Unlock();

	return false;
}

//*=================================================================================
//*ԭ��: void Monitor()
//*����: �ͻ�����
//*����: ��
//*����: ��
//*˵��: ����ͻ���5���Ӳ��, ����Ͽ�����, Ҫ�����µ�¼
//*=================================================================================
void TSmartOutThread::Monitor()
{
	DWORD  dwTimeOut = 1000*60*2;

	m_ClientLock.Lock();
	for(int i=0; i< m_ClientList.GetCount(); i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			if( GetTickCount() - pUser->dwLastTick > dwTimeOut )
			{
				m_ClientList.Remove(pUser);
				delete pUser;
				i--;
			}
		}
	}
	m_ClientLock.Unlock();
}

//*=================================================================================
//*ԭ��: bool ReadRequestPacket(TSmartPacket& Packet)
//*����: ����һ�������
//*����: ��
//*����: ��
//*˵��: ��
//*=================================================================================
bool TSmartOutThread::ReadRequestPacket(SOCKET hSocket, TSmartPacket& Packet)
{
	//�����ͷ����
	long nLength = sizeof(TSSmartPacket);
	long nRecvLen = RecvBuffer(hSocket, Packet.GetBuffer(), nLength, 1000);

	TSSmartPacket *pPacket = (TSSmartPacket*)Packet.GetBuffer();

	if( nRecvLen != nLength )
	{
//		ReportLog("��ͷ���Ȳ���! ��������ݰ����Ϸ�!");
		return false;
	}

	nLength = Packet.GetDataLength() + 1 ;
	if( nLength > 0 )
	{
		if( RecvBuffer(hSocket, Packet.GetDataBuffer(), nLength, 1000) != nLength )
		{
//			printf("���ܽ��հ��ڵ�����!\n");
			DebugPrint("���ܽ��հ��ڵ�����!");
			return false;
		}

		nRecvLen+=nLength;
	}

	ReportLog("�������ݰ�:[%s]\n", Packet.m_Buffer);

	if( !Packet.IsValid(nRecvLen) )
	{
//		printf("��ͷУ���!��������ݰ����Ϸ�!\n");
		DebugPrint("��������ݰ����Ϸ�!");
		return false;
	}

	return true;
}

//*=================================================================================
//*ԭ��: void Dispatch(TSmartPacket& Packet)
//*����: �ַ��ͻ�����
//*����: ��
//*����: ��
//*˵��: ��
//*=================================================================================
void TSmartOutThread::Dispatch(SOCKET hSocket, SOCKADDR_IN *psockAddr, TSmartPacket& Packet)
{
	long i=0; 
	while(true)
	{
		if( !strcmp(Function[i].pText, "") || 
			!strcmp(Function[i].pCmd, "") || 
			Function[i].lpFunc == NULL )
		{
			break;
		}

		if( !_strcmpi(Function[i].pCmd, Packet.GetCmd()) ) 
		{ 
			try
			{
				Function[i].lpFunc(hSocket, psockAddr, &Packet, m_pServer, this);
			}
			catch(TException& e)
			{
				WriteLog(e.GetText());
			}
			catch(...)
			{
				WriteLog("ִ���������ʱ�����쳣,�������!");
			}
			break;
		}
		i++;
	}
}

//*=================================================================================
//*ԭ��: void TSmartOutThread::CloseOutSocket()
//*����: ǿ�ƹر�socket
//*����: ��
//*����: ��
//*˵��: ��
//*=================================================================================
void TSmartOutThread::CloseOutSocket()
{
	if( m_hNotifySocket != INVALID_SOCKET )
	{
		shutdown(m_hNotifySocket, SB_BOTH);
		closesocket(m_hNotifySocket);
		m_hNotifySocket = INVALID_SOCKET;
	}

	if( m_hServerSocket != INVALID_SOCKET )
	{
		shutdown(m_hServerSocket, SB_BOTH);
		closesocket(m_hServerSocket);
		m_hServerSocket = INVALID_SOCKET;
	}
}

//*=================================================================================
//*ԭ��: void DestoryClient()
//*����: ɾ�����еĿͻ�����Ϣ
//*����: ��
//*����: ��
//*˵��: ��
//*=================================================================================
void TSmartOutThread::DestoryClient()
{
	m_ClientLock.Lock();

	long nCount = m_ClientList.GetCount();

	for(int i=0; i< nCount; i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			delete pUser;
		}
	}
	m_ClientList.Clear();

	m_ClientLock.Unlock();
}

bool TSmartOutThread::AddUser(TSOUTUser *pUser)
{
	m_ClientLock.Lock();
	if( m_ClientList.GetCount() > 10 )
	{
		m_ClientLock.Unlock();
		return false;
	}
	else
	{
		m_ClientList.Add(pUser);
		m_ClientLock.Unlock();
		return true;
	}
}

void TSmartOutThread::DelUser(SOCKADDR *pSockAddr, long nSID)
{
	m_ClientLock.Lock();
	for(long i=0; i< m_ClientList.GetCount(); i++)
	{
		TSOUTUser *pUser = (TSOUTUser*)m_ClientList[i];
		if( pUser != NULL )
		{
			
			m_ClientList.Remove(pUser);
			delete pUser;
			break;
		}
	}
	m_ClientLock.Unlock();
}

long TSmartOutThread::GetKey()
{
	return InterlockedIncrement(&TSmartOutThread::nKey);
}

//
char* TSmartOutThread::GetMD5()
{
	return "";
}

//*=================================================================================
//*ԭ��: long OnLogin(....)
//*����: �������¼
//*����: ��
//*����: ������ֵ��
//*˵��: ��
//*=================================================================================
long TSmartOutThread::OnLogin(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread)
{
	char  szUser[64];
	char  szPass[32];
	int   nPort;

	memset(szUser, 0, sizeof(szUser));
	memset(szPass, 0, sizeof(szPass));

	if( !pPacket->GetItem(0, nPort) || !pPacket->GetItem(1, szUser) )
		return RET_NG;

	if( pPacket->GetItemCount() > 2 )
		pPacket->GetItem(2, szPass);

	TSOUTUser *pUser = new TSOUTUser;

	pUser->nPort = nPort;
	pUser->dwLastTick = GetTickCount();
	pUser->nSID  = TSmartOutThread::GetKey();

	time(&pUser->tmCreate);

	memcpy(&pUser->sockAddr, psockAddr, sizeof(SOCKADDR_IN));

	pUser->sockAddr.sin_family = AF_INET ;
	pUser->sockAddr.sin_port = htons(nPort);
	strcpy(pUser->szHost, "");
	strcpy(pUser->szMD5, TSmartOutThread::GetMD5());

	strcpy(pUser->szHost, inet_ntoa(psockAddr->sin_addr));

	TSmartPacket  Packet;

	Packet.Create(PACKET_CMD_LOGIN, pUser->nSID);
	Packet.SetResult(RET_OK);
	Packet.AddItem(pUser->nSID);
	Packet.AddItem(pUser->szMD5,strlen(pUser->szMD5));
	Packet.AddEnd();

	char *pBuffer = Packet.GetBuffer();
	long nLength = Packet.GetLength();

	ReportLog("���Ͱ�, ����%d: <%s>\n", nLength, pBuffer);

	if( pThread->SendBuffer(hClient, pBuffer, nLength, 1000) != nLength ) 
	{
		delete pUser;
		ReportLog("���͵�¼��Ӧ����!");
		return RET_SYSERROR;
	}
	else
	{
		pThread->AddUser(pUser);
		pServer->SendInitData(pThread->m_hNotifySocket, &pUser->sockAddr);
	}

	return RET_OK;
}

//*=================================================================================
//*ԭ��: long OnLogout(....)
//*����: �����ע��
//*����: ��
//*����: ������ֵ��
//*˵��: ��
//*=================================================================================
long TSmartOutThread::OnLogout(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread)
{
	long nSID = pPacket->GetSID();
	pThread->DelUser(NULL, nSID);
	return RET_OK;
}

//*=================================================================================
//*ԭ��: long OnShutdownServer(....)
//*����: ������Shutdown
//*����: ��
//*����: ������ֵ��
//*˵��: ��
//*=================================================================================
long TSmartOutThread::OnShutdownServer(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread)
{
	pServer->EndService("SMARTSERVER");

	TSmartPacket  Packet;

	Packet.Create(PACKET_CMD_SHUTDOWN, pPacket->GetSID());
	Packet.SetResult(RET_OK);
	Packet.AddEnd();

	char *pBuffer = Packet.GetBuffer();
	long nLength = Packet.GetLength();

	if( pThread->SendBuffer(hClient, pBuffer, nLength, 1000) != nLength ) 
		return RET_SYSERROR;

	return RET_OK;
}

//*=================================================================================
//*ԭ��: long OnStartDevice(....)
//*����: �����豸
//*����: ��
//*����: ������ֵ��
//*˵��: ��
//*=================================================================================
long TSmartOutThread::OnStartDevice(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread)
{
	long nCount = pPacket->GetItemCount();
	for(long i=0; i< nCount; i++)
	{
		long nAuthID = 0 ;
		if( pPacket->GetItem(i, nAuthID) && nAuthID > 0 )
		{
			pServer->EnableDevice(nAuthID,true);
		}
	}

	TSmartPacket  Packet;

	Packet.Create(PACKET_CMD_STARTRUN, pPacket->GetSID());
	Packet.SetResult(RET_OK);
	Packet.AddEnd();

	char *pBuffer = Packet.GetBuffer();
	long nLength = Packet.GetLength();

	if( pThread->SendBuffer(hClient, pBuffer, nLength, 1000) != nLength ) 
		return RET_SYSERROR;

	return RET_OK;
}

//*=================================================================================
//*ԭ��: long OnStopDevice(....)
//*����: ֹͣ�豸
//*����: ��
//*����: ������ֵ��
//*˵��: ��
//*=================================================================================
long TSmartOutThread::OnStopDevice(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread)
{
	long nCount = pPacket->GetItemCount();
	for(long i=0; i< nCount; i++)
	{
		long nAuthID = 0 ;
		if( pPacket->GetItem(i, nAuthID) && nAuthID > 0 )
		{
			pServer->EnableDevice(nAuthID,false);
		}
	}

	TSmartPacket  Packet;

	Packet.Create(PACKET_CMD_STOPRUN, pPacket->GetSID());
	Packet.SetResult(RET_OK);
	Packet.AddEnd();

	char *pBuffer = Packet.GetBuffer();
	long nLength = Packet.GetLength();

	if( pThread->SendBuffer(hClient, pBuffer, nLength, 1000) != nLength ) 
		return RET_SYSERROR;

	return RET_OK;
}

//*=================================================================================
//*ԭ��: long OnGetServerInfo(....)
//*����: �õ���������Ϣ
//*����: ��
//*����: ������ֵ��
//*˵��: ��
//*=================================================================================
long TSmartOutThread::OnGetServerInfo(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread)
{
	TSmartPacket  Packet;

	Packet.Create(PACKET_CMD_GETSERVERINFO, pPacket->GetSID());
	Packet.SetResult(RET_OK);
	pServer->m_SmartInfo.nTick = GetTickCount() - pServer->m_SmartInfo.nTick;
	Packet.AddItem(pServer->m_SmartInfo.szHostName, strlen(pServer->m_SmartInfo.szHostName));
	Packet.AddItem(pServer->m_SmartInfo.szVersion, strlen(pServer->m_SmartInfo.szVersion));
	Packet.AddItem(pServer->m_SmartInfo.nWorkMode);
	Packet.AddItem(pServer->m_SmartInfo.szDateTime, strlen(pServer->m_SmartInfo.szDateTime));
	Packet.AddItem(pServer->m_SmartInfo.nTick);
	Packet.AddItem(pServer->m_SmartInfo.nDevLevel1);
	Packet.AddItem(pServer->m_SmartInfo.nDevLevel1Ack);
	Packet.AddItem(pServer->m_SmartInfo.nDevLevel2);
	Packet.AddItem(pServer->m_SmartInfo.nDevLevel2Ack);
	Packet.AddEnd();

	char *pBuffer = Packet.GetBuffer();
	long nLength = Packet.GetLength();

	if( pThread->SendBuffer(hClient, pBuffer, nLength, 1000) != nLength ) 
		return RET_SYSERROR;

	return RET_OK;
}

//*=================================================================================
//*ԭ��: long OnGetDeviceInfo(....)
//*����: �õ��豸��Ϣ
//*����: ��
//*����: ������ֵ��
//*˵��: ��
//*=================================================================================
long TSmartOutThread::OnGetDeviceInfo(SOCKET hClient, SOCKADDR_IN *psockAddr, TSmartPacket *pPacket, TSmartServer* pServer, TSmartOutThread *pThread)
{
	TSmartPacket  Packet;

	Packet.Create(PACKET_CMD_STARTRUN, pPacket->GetSID());

	long nCount = pPacket->GetItemCount();
	if( pPacket->GetItemCount() < 1 )
	{
		Packet.SetResult(RET_SYSERROR);
		Packet.AddEnd();
	}
	else
	{
		long nAuthID = 0 ;
		if( pPacket->GetItem(0, nAuthID) && nAuthID > 0 )
		{
			TSDocInfo  Info;

			ZeroMemory(&Info, sizeof(Info));

			pServer->GetDeviceInfo(nAuthID, &Info);

			Packet.AddItem(Info.m_nAuthID);
			Packet.AddItem(Info.m_nChild);
			Packet.AddItem(Info.m_nStatus);
			Packet.AddItem(Info.m_szTaskCode, strlen(Info.m_szTaskCode));

			for(long i=0; i< Info.m_nChild; i++)
			{
				Packet.AddItem(Info.Child[i].m_nAuthID);
				Packet.AddItem(Info.Child[i].m_nStatus);
				Packet.AddItem(Info.Child[i].m_szTaskCode, strlen(Info.Child[i].m_szTaskCode));
			}
			Packet.AddEnd();
		}
		else
		{
			Packet.SetResult(RET_SYSERROR);
			Packet.AddEnd();
		}
	}

	char *pBuffer = Packet.GetBuffer();
	long nLength = Packet.GetLength();

	if( pThread->SendBuffer(hClient, pBuffer, nLength, 1000) != nLength ) 
		return RET_SYSERROR;

	return RET_OK;
}
