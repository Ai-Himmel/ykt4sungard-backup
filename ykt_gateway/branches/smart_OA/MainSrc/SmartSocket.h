#ifndef __SMARTSOCKET_H_
#define __SMARTSOCKET_H_

#include "smartcommunicationdlg.h"
#include "TThread.h"
#include "data.h"

//*---------------------------------------------------------------------------
//*名称: CSocketSmart
//*功能: TCP/IP通讯类
//*---------------------------------------------------------------------------
class CSocketSmart : public CSmart
{

public:
	SOCKET   m_handle;
protected:
	bool  Create( int nAf, int nType, int nProtocol);	
	bool  Connect(char* pszAddress, int nPort);		
	bool  ReadFrom(char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut);
public:
	CSocketSmart();
	~CSocketSmart();
	bool Open();
	void Close();	
	bool ReConnect();	
	bool PostSend(char *lpBuffer, int nBufSize, long nTimeOut);
	bool PostRecv(char *lpBuffer, int nBufSize, long nTimeOut);    
	bool WaitRecv(int WaitTime);	
	bool RecvQueryData(byte *lpData, int*nlpDatalen,DWORD nTimeOut);
public:
	bool ServerInit();
	bool ServerRecv(char *pszBuffer, int nBufferSize, long nTimeOut,SOCKET *nNewHandle);	
	bool ServerSend(char *pszBuffer, int nBufferSize, long nTimeOut,SOCKET *nNewHandle);
	bool ClientRecv(char *pszBuffer, int nBufferSize, long nTimeOut);
	bool ClientSend(char *lpBuffer, int nBufSize, long nTimeOut);
};
#endif