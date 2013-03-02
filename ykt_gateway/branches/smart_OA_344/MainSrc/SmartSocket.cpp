#include "stdafx.h"
#include "SmartCommunication.h"
#include "SmartCommunicationDlg.h"
#include "Smart.h"
#include "readfile.h"
#include "SmartSocket.h"

CSocketSmart::CSocketSmart()
{
	m_handle=0;
	m_ReadOver.hEvent  = NULL;
	m_WriteOver.hEvent = NULL;	
	m_IpPar.bConnect   = false;
	m_ConnErrCnts = 0;
}

CSocketSmart::~CSocketSmart()
{
	Close();
}

/*=================================================================
* Function ID :  Create
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  
* Description :  创建SOCKET句柄
* Notice	  :  
*					
*=================================================================*/
bool CSocketSmart::Create( int nAf, int nType, int nProtocol)	
{			   
	m_handle = WSASocket(nAf, nType, nProtocol, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( m_handle == INVALID_SOCKET )
	{
		strcpy(m_szErrorText,"创建SOCKET失败(WSASocket)");
		return false;
	}
	int nFlag = 1; 
	if( ioctlsocket(m_handle, FIONBIO, (u_long*)&nFlag) == SOCKET_ERROR )
	{
		closesocket(m_handle);
		m_handle=NULL;
		strcpy(m_szErrorText,"创建SOCKET失败(ioctlsocket)");
		return false;
	}
	return true;
}

/*=================================================================
* Function ID :  Connect
* Input       :  char* pszAddress, int nPort
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  与服务器LPORT建立连接
* Notice	  :  
*					
*=================================================================*/
bool  CSocketSmart::Connect(char* pszAddress, int nPort)
{
	
#if 0
	struct sockaddr_in inAddr;
	int    ret=0;

	memset(&inAddr,0x00,sizeof inAddr);

	inAddr.sin_family = AF_INET;
	inAddr.sin_port   = htons(nPort);	
	inAddr.sin_addr.S_un.S_addr=inet_addr(pszAddress);
	if( (ret=connect(m_handle,(PSOCKADDR)&inAddr,sizeof(inAddr))) == SOCKET_ERROR )
	{			
		if( WSAGetLastError() !=WSAEWOULDBLOCK)//10035
		{		
			sprintf(m_szErrorText,"连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);		
			closesocket(m_handle);
			return false;
		}
	}	
	return true;
#else
	SOCKADDR_IN  sockAddr;
	
	memset(&sockAddr, 0x00,sizeof(sockAddr));	
	sockAddr.sin_family = AF_INET ;
	sockAddr.sin_port   = htons(nPort);	
	char* lpszAscii = (char*)pszAddress;
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
			sprintf(m_szErrorText,"连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);		
			//m_pDialog->AddString(m_szErrorText);
			return false;
		}
	}
	WSAEVENT hEvent = WSACreateEvent();
	if( hEvent == WSA_INVALID_EVENT )
	{
		sprintf(m_szErrorText,"1连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);		
		//m_pDialog->AddString(m_szErrorText);
		//Sleep(200);
		return false;
	}
	if( WSAEventSelect(m_handle, hEvent, FD_CONNECT|FD_CLOSE) == SOCKET_ERROR )
	{
		WSACloseEvent(hEvent);
		sprintf(m_szErrorText,"2连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);
		//m_pDialog->AddString(m_szErrorText);
		Sleep(200);
		return false;
	}
	DWORD dwResult = WSAConnect(m_handle, (SOCKADDR*)&sockAddr, sizeof(sockAddr), NULL, NULL, NULL, NULL);
	if( dwResult == SOCKET_ERROR )
	{
		dwResult = WSAGetLastError();
		if( dwResult != WSAEWOULDBLOCK )
		{
			WSAEventSelect(m_handle, hEvent, 0);
			WSACloseEvent(hEvent);
			sprintf(m_szErrorText,"3连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);		
			//m_pDialog->AddString(m_szErrorText);
			Sleep(200);
			return false;
		}		
		//等待事件发生
		DWORD dwRet = WSAWaitForMultipleEvents(1, &hEvent, TRUE, (DWORD)5000, FALSE);
		if( dwRet != WSA_WAIT_EVENT_0 )
		{
			WSAEventSelect(m_handle, hEvent, 0);
			WSACloseEvent(hEvent);			
			sprintf(m_szErrorText,"4连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);		
			//m_pDialog->AddString(m_szErrorText);
			Sleep(1000);
			return false;
		}
		
		//有事件发生
		WSANETWORKEVENTS   NetEvents;		
		ZeroMemory(&NetEvents, sizeof(NetEvents));		
		if( WSAEnumNetworkEvents(m_handle, hEvent, &NetEvents) == SOCKET_ERROR )
		{
			WSAEventSelect(m_handle, hEvent, 0);
			WSACloseEvent(hEvent);
			sprintf(m_szErrorText,"5连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);		
			//m_pDialog->AddString(m_szErrorText);
			Sleep(200);
			return false;
		}
		
		if( NetEvents.lNetworkEvents != FD_CONNECT || NetEvents.iErrorCode[FD_CONNECT_BIT] )
		{
			WSAEventSelect(m_handle, hEvent, 0);
			WSACloseEvent(hEvent);
			sprintf(m_szErrorText,"6连接服务器失败(%ld)![ip=%s,port=%ld]",WSAGetLastError(),pszAddress,nPort);		
			//m_pDialog->AddString(m_szErrorText);
			Sleep(200);
			return false;
		}			 
	}		
	WSAEventSelect(m_handle, hEvent, 0);
	WSACloseEvent(hEvent);	
	return true;
#endif

}

/*=================================================================
* Function ID :  Open
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  创建一个与服务器连接的客户端
* Notice	  :  
*					
*=================================================================*/
bool CSocketSmart::Open()
{			
	char msg[1024];
	
	memset(msg,			 0,sizeof msg);
	memset(m_szErrorText,0,sizeof m_szErrorText);
	
	m_IpPar.bConnect   = false;	
	if( !Create(AF_INET, SOCK_STREAM, 0) )	return false;
	Sleep(100);
	if( !Connect(m_IpPar.cIPAddress, m_IpPar.nPortNo) )
	{	
		Close();
		m_ConnErrCnts++;
		if(m_ConnErrCnts > 50)
		{
			sprintf(msg,"前置连接服务设备[ ID->%.8X IP->%s,Port->%ld ]失败,请确认网络是否正常!!", m_Data.HexToInt((BYTE*)m_regno,4), m_IpPar.cIPAddress, m_IpPar.nPortNo);		
			strcpy(m_szErrorText,msg);
			m_pDialog->AddString(m_szErrorText);
			m_ConnErrCnts = 0;
		}
		return false;
	}	
	m_ReadOver.hEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	
	sprintf(m_szErrorText,"前置连接服务设备[ ID->%.8X IP->%s,Port->%ld ]成功!", m_Data.HexToInt((BYTE*)m_regno,4), m_IpPar.cIPAddress, m_IpPar.nPortNo);
	m_pDialog->AddString(m_szErrorText);	
	m_IpPar.bConnect=true;	
	return true;
}

/*=================================================================
* Function ID :  PostSend
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  向服务端发送数据
* Notice	  :  pszBuffer 发送的数据   nBuffersize 发送的数据长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CSocketSmart::PostSend(char *pszBuffer, int nBufferSize, long nTimeOut)
{
	WSABUF  wsaBuf;
	DWORD   dwFlag = 0 ;
	DWORD   nret=0;

	ResetEvent(m_WriteOver.hEvent);	

	m_nWriteBytes = 0 ;	
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;	
	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;
	
	int nResult = WSASend(m_handle, &wsaBuf, 1, &m_nWriteBytes, 0, &m_WriteOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( (nret=WSAGetLastError()) != WSA_IO_PENDING )
		{			
			sprintf(m_szErrorText,"发送数据错误[%ld]!", WSAGetLastError());

			if( !ReConnect() )return false;			
			else return true;
		}
		else
		{
			Sleep(5);
			if( !WSAGetOverlappedResult(m_handle, &m_WriteOver, &m_nWriteBytes, TRUE, &dwFlag) )
			{				
				if( (nret=WSAGetLastError()) != WSA_IO_INCOMPLETE )
				{					
					sprintf(m_szErrorText,"发送数据错误,Send WSA_IO_INCOMPLETE,[%ld]!", WSAGetLastError());
					return false;					
				}
			}
		}
	}
	return true;
}

/*=================================================================
* Function ID :  PostRecv
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  从服务端接收数据
* Notice	  :  pszBuffer 保存接收的数据   nBuffersize 缓冲区长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CSocketSmart::PostRecv(char *pszBuffer, int nBufferSize, long nTimeOut)
{
	int		ret=0,nTry=0,i=0;
	int		nResult=0;
	DWORD	dwFlag =0 ;
	WSABUF  wsaBuf;
	
	memset(&wsaBuf, 0x00, sizeof wsaBuf);

	m_nReadBytes          = 0 ;	
	m_ReadOver.Offset     = 0 ;
	m_ReadOver.OffsetHigh = 0 ;
	wsaBuf.buf = (LPTSTR)pszBuffer;	
	wsaBuf.len = (DWORD)nBufferSize;		

	m_nReadBytes	=0;
	ResetEvent(m_ReadOver.hEvent);
	if(!WaitRecv(nTimeOut) ) return false;	
	nResult = WSARecv(m_handle, &wsaBuf, 1, &m_nReadBytes, &dwFlag, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{			
			sprintf(m_szErrorText,"接收数据错误[%ld]!", WSAGetLastError());
			//表示对方已经断开,直接返回错
			if( WSAGetLastError()==WSAECONNRESET )
			{				
				SMT_ReConnectServer();					
			}				
			return false;
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				sprintf(m_szErrorText,"接收数据超时1[%ld]!", WSAGetLastError());
				//表示对方已经断开,直接返回错
				if( WSAGetLastError()==WSAECONNRESET )
				{					
					SMT_ReConnectServer();					
				}				
				return false;
			}
			
			m_nReadBytes = 0 ;
			dwFlag       = 0 ;
			if( !WSAGetOverlappedResult(m_handle, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				if( WSAGetLastError() != WSA_IO_INCOMPLETE )				
				{
					//表示对方已经断开,直接返回错
					if( WSAGetLastError()==WSAECONNRESET )
					{
						SMT_ReConnectServer();				
					}					
					sprintf(m_szErrorText,"接收数据错误1[%ld]!", WSAGetLastError());
					return false;					
				}
			}
		}
	}
	//add by dengjun 20060815
	//表示一个数据都未接到，则等一下再接收数据
	if( m_nReadBytes ==0 )
	{		
		Sleep(3);
		ret=recv(m_handle,pszBuffer,nBufferSize,0);
		if( ret>0) m_nReadBytes+=ret;
	}	
	DWORD nRecvLen=7+(BYTE)pszBuffer[3];
	nTry=0;
	//当数据还未收完整时,则继续收
	if( m_nReadBytes < nRecvLen ) 
	{			
		while( true )
		{	
			nRecvLen= 7+(BYTE)pszBuffer[3];
			if( m_nReadBytes>0 ) 
			{
				if( 0xC2 !=(BYTE)pszBuffer[0] )
				{
					return false;
				}
			}
			//表示对方已经断开,直接返回错
			if( WSAGetLastError()==WSAECONNRESET )
			{
				SMT_ReConnectServer();
				return false;
			}
			if( nTry>=m_nWaitRecvTime ) 
			{
				sprintf(m_szErrorText,"接收数据超时2[%ld]!", WSAGetLastError());
				return false;
			}
			if( (ret=recv(m_handle,pszBuffer+m_nReadBytes,nBufferSize,0)) <= 0 )
			{
				nTry++;		
				if( m_nReadBytes >= nRecvLen ) 
				{
					m_nReadBytes=nRecvLen;
					return true; //收到完整的数据包
				}
				if( !memcmp(m_MacCode,MACHINE_TYPE_0121,2) )	Sleep(10);
				else  Sleep(3);
				continue;
			}			
			nTry++;
			m_nReadBytes+=ret;
			if( m_nReadBytes >= nRecvLen ) 
			{
				m_nReadBytes = nRecvLen;
				return true; //收到完整的数据包
			}
			if( !memcmp(m_MacCode,MACHINE_TYPE_0121,2) )	Sleep(10);
			else  Sleep(3);
		}
	}
	m_nReadBytes=7+(BYTE)pszBuffer[3];	
	return true;
}

/*=================================================================
* Function ID :  WaitRecv
* Input       :  int WaitTime
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  在WaitTime时间内,等待SOCKET端口是否有数据
* Notice	  :  
*			  :	 WaitTime 等待时间
*					
*=================================================================*/
bool CSocketSmart::WaitRecv(int WaitTime)
{		
	struct timeval  TimeOutVal;
	fd_set			readfds;	
	int				nResult=0;
	DWORD			nRet   =0;
	
	memset(m_szErrorText,0x00,sizeof m_szErrorText);
	memset(&TimeOutVal,  0x00,sizeof TimeOutVal);

	TimeOutVal.tv_sec =WaitTime/1000;
	TimeOutVal.tv_usec=WaitTime%1000;	
	FD_ZERO(&readfds);
	FD_SET(m_handle,&readfds);	

	if( (nResult=select(m_handle+1,&readfds,NULL,NULL,&TimeOutVal))<1 )
	{
		if( nResult == 0 )
		{
			//表示对方已经断开,直接返回错
			if( WSAGetLastError()==WSAECONNRESET )
			{
				SMT_ReConnectServer();
			}
		}
		else
		{
			sprintf(m_szErrorText,"等待接收数据时出错select!");
			SMT_ReConnectServer();
		}
		return false;
	}
	return true;	
}

/*=================================================================
* Function ID :  ReadFrom
* Input       :  char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  用于检测端口是否已经有规定长度的数据
* Notice	  :  
*			  :	 检测端口数据
*					
*=================================================================*/
bool CSocketSmart::ReadFrom(char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut)
{
	
	DWORD	dwFlag = MSG_PEEK ;
	WSABUF  wsaBuf;
	int nLen = sizeof(SOCKADDR_IN);
	
	m_nReadBytes		  = 0 ;
	m_ReadOver.Offset	  = 0 ;
	m_ReadOver.OffsetHigh = 0 ;	
	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;
	ResetEvent(m_ReadOver.hEvent);
	int nResult = WSARecvFrom(m_handle, &wsaBuf, 1, &m_nReadBytes, &dwFlag, (SOCKADDR*)psockAddr, &nLen, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			sprintf(m_szErrorText,"接收数据错误[%ld]!", WSAGetLastError());
			return false;
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				sprintf(m_szErrorText,"接收数据超时[%ld]!", WSAGetLastError());
				return false;
			}
			
			m_nReadBytes = 0 ;			
			if( !WSAGetOverlappedResult(m_handle, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				int nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{					
					sprintf(m_szErrorText,"接收数据错误[%ld]!", WSAGetLastError());
					return false;
				}
			}
		}
	}		
	return true;
}

/*=================================================================
* Function ID :  Close
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  关闭TCP/IP通讯端口,同时关闭相应事件
* Notice	  :  
*			  :	 WaitTime 等待时间
*					
*=================================================================*/
void CSocketSmart::Close()
{
	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);		
		m_ReadOver.hEvent = NULL ;
		Sleep(50);
	}	
	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
		Sleep(50);
	}	
	if( m_handle != NULL )
	{
		shutdown(m_handle, SB_BOTH);
		Sleep(100);
		closesocket(m_handle);		
		m_handle = NULL ;
		Sleep(100);
	}
	m_IpPar.bConnect= false;
}

/*=================================================================
* Function ID :  ReConnect
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  重新连接服务
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CSocketSmart::ReConnect()
{	
	Close();		
	if( !Open() )
	{
		
		sprintf(m_szErrorText,"重新连接服务失败[ %s, %ld ],请确认网络是否正常!!",m_IpPar.cIPAddress,m_IpPar.nPortNo);
		Sleep(2*(m_dwThreadID%1000));
		return false;
	}
	sprintf(m_szErrorText,"重新连接服务成功[ %s, %ld ]!!",m_IpPar.cIPAddress,m_IpPar.nPortNo);
	m_pDialog->AddString(m_szErrorText);
	return true;
}

/*=================================================================
* Function ID :  Server
* Input       :  void
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  void
* Description :  服务初始化
* Notice	  :  
*			  :	 
*					
*=================================================================*/
bool CSocketSmart::ServerInit()
{
	struct sockaddr_in Server;	
	char errmsg[1024];
	
	memset(errmsg, 0x00, sizeof errmsg);	
	memset(&Server, 0x00, sizeof(struct sockaddr_in));
	
	m_IpPar.bConnect=false;
	m_ReadOver.hEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	if( !Create(AF_INET, SOCK_STREAM, 0) )
	{
		Close();
		return false;
	}
	
	Server.sin_family		= AF_INET;
	Server.sin_port			= htons((unsigned short )m_IpPar.nPortNo);	
	Server.sin_addr.s_addr	= htonl(INADDR_ANY);


	char opt = SO_REUSEADDR;
	setsockopt(m_handle,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	if( bind(m_handle, (struct sockaddr *)&Server, sizeof(struct sockaddr)) < 0 )
	{		
		Close();
		return false;
	}
	if( listen(m_handle,5) < 0 )	
	{
		Close();
		return false;
	}	
	return true;
}

/*=================================================================
* Function ID :  ServerRecv
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  从服务端接收数据
* Notice	  :  pszBuffer 保存接收的数据   nBuffersize 缓冲区长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CSocketSmart::ServerRecv(char *pszBuffer, int nBufferSize, long nTimeOut,SOCKET *nNewHandle)
{
	int		ret=0;
	int		nResult=0;
	DWORD	dwFlag =0 ;
	WSABUF  wsaBuf;

	struct timeval TimeOutVal;
	fd_set readfds;
	SOCKADDR_IN sockAddr;		
	memset(&sockAddr,  0x00,sizeof(sockAddr));		
	memset(&TimeOutVal,0x00,sizeof TimeOutVal);
	
	TimeOutVal.tv_sec = nTimeOut/1000;
	TimeOutVal.tv_usec= nTimeOut%1000;	
	FD_ZERO(&readfds);
	FD_SET(m_handle,&readfds);
	if( (nResult=select(m_handle+1,&readfds,NULL,NULL,&TimeOutVal))<1 )
	{
		if( nResult == 0 )
		{			
			strcpy(m_szErrorText,"无客户端连接");
		}
		else
		{
			sprintf(m_szErrorText,"等待接收数据时出错select!");						
			m_pDialog->AddString(m_szErrorText);
			Close();
			Sleep(3000);
			ServerInit();
		}						
		return false;		
	}	
	struct sockaddr_in newaddr;	
	int newaddr_len = sizeof(struct sockaddr);
	memset(&newaddr, 0x00, sizeof(struct sockaddr_in));
	SOCKET newsocket=0;
	if( (newsocket=accept(m_handle,(struct sockaddr*)&newaddr,(int*)&newaddr_len)) < 0 )
	{
		closesocket(newsocket);
		return false;
	}
	*nNewHandle=newsocket;
	
	m_nReadBytes = 0 ;
	memset(&wsaBuf, 0x00, sizeof wsaBuf);	
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;
	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;	
	ResetEvent(m_ReadOver.hEvent);		
	nResult = WSARecv(newsocket, &wsaBuf, 1, &m_nReadBytes, &dwFlag, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			sprintf(m_szErrorText,"接收数据错误[%ld]!", WSAGetLastError());
			closesocket(newsocket);
			m_pDialog->AddString(m_szErrorText);
			return false;
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				sprintf(m_szErrorText,"接收数据超时1[%ld]!", WSAGetLastError());
				closesocket(newsocket);
				return false;				
			}
			
			m_nReadBytes = 0 ;
			dwFlag       = 0 ;
			if( !WSAGetOverlappedResult(newsocket, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				if( WSAGetLastError() != WSA_IO_INCOMPLETE )				
				{
					sprintf(m_szErrorText,"接收数据错误[%ld]!", WSAGetLastError());
					closesocket(newsocket);
					return false;					
				}
			}
		}
	}	
	return true;
}



/*=================================================================
* Function ID :  ClientSend
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  向服务端发送数据
* Notice	  :  pszBuffer 发送的数据   nBuffersize 发送的数据长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CSocketSmart::ClientSend(char *pszBuffer, int nBufferSize, long nTimeOut)
{
	WSABUF  wsaBuf;
	DWORD   dwFlag = 0 ;
		
	ResetEvent(m_WriteOver.hEvent);	
	m_nWriteBytes = 0 ;	
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;	
	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;
	
	int nResult = WSASend(m_handle, &wsaBuf, 1, &m_nWriteBytes, 0, &m_WriteOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{			
			sprintf(m_szErrorText,"发送数据错误[%ld]!", WSAGetLastError());
			return false;
		}
		else
		{
			if( !WSAGetOverlappedResult(m_handle, &m_WriteOver, &m_nWriteBytes, TRUE, &dwFlag) )
			{				
				if( WSAGetLastError() != WSA_IO_INCOMPLETE )
				{					
					sprintf(m_szErrorText,"发送数据错误,Send WSA_IO_INCOMPLETE,[%ld]!", WSAGetLastError());
					return false;					
				}
			}
		}
	}
	return true;
}
/*=================================================================
* Function ID :  ClientRecv
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  从服务端接收数据
* Notice	  :  pszBuffer 保存接收的数据   nBuffersize 缓冲区长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CSocketSmart::ClientRecv(char *pszBuffer, int nBufferSize, long nTimeOut)
{
	int		ret=0;
	int		nResult=0;
	DWORD	dwFlag =0 ;
	WSABUF  wsaBuf;
	
	memset(m_szErrorText,0x00,sizeof m_szErrorText);
	m_nReadBytes = 0 ;
	memset(&wsaBuf, 0x00, sizeof wsaBuf);	
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;
	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	ResetEvent(m_ReadOver.hEvent);	
	if(!WaitRecv(nTimeOut) ) 
	{
		return false;
	}		
	nResult = WSARecv(m_handle, &wsaBuf, 1, &m_nReadBytes, &dwFlag, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			sprintf(m_szErrorText,"接收数据错误[%ld]!", WSAGetLastError());
			return false;
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				sprintf(m_szErrorText,"接收数据超时1[%ld]!", WSAGetLastError());
				return false;				
			}
			
			m_nReadBytes = 0 ;
			dwFlag       = 0 ;
			if( !WSAGetOverlappedResult(m_handle, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				if( WSAGetLastError() != WSA_IO_INCOMPLETE )				
				{
					sprintf(m_szErrorText,"接收数据错误[%ld]!", WSAGetLastError());
					return false;					
				}
			}
		}
	}	
	return true;
}

/*=================================================================
* Function ID :  ServerSend
* Input       :  char *pszBuffer, int nBufferSize, long nTimeOut
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  向服务端发送数据
* Notice	  :  pszBuffer 发送的数据   nBuffersize 发送的数据长度 
*			  :	 nTimeOut 等待时间
*					
*=================================================================*/
bool CSocketSmart::ServerSend(char *pszBuffer, int nBufferSize, long nTimeOut,SOCKET *nNewHandle)
{
	WSABUF  wsaBuf;
	DWORD   dwFlag = 0 ;
		
	ResetEvent(m_WriteOver.hEvent);	
	m_nWriteBytes = 0 ;	
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;	
	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;
	
	int nResult = WSASend(*nNewHandle, &wsaBuf, 1, &m_nWriteBytes, 0, &m_WriteOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{			
			sprintf(m_szErrorText,"发送数据错误[%ld]!", WSAGetLastError());
			closesocket(*nNewHandle);

			if( !ReConnect() )return false;			
			else return true;
		}
		else
		{
			if( !WSAGetOverlappedResult(m_handle, &m_WriteOver, &m_nWriteBytes, TRUE, &dwFlag) )
			{				
				if( WSAGetLastError() != WSA_IO_INCOMPLETE )
				{					
					sprintf(m_szErrorText,"发送数据错误,Send WSA_IO_INCOMPLETE,[%ld]!", WSAGetLastError());
					closesocket(*nNewHandle);
					return false;					
				}
			}
		}
	}
	closesocket(*nNewHandle);
	return true;
}

/*=================================================================
* Function ID :  RecvQueryData
* Input       :  
* Output      :  void
* Author      :  
* Date        :  2006  2
* Return	  :  TRUE 成功  FALSE 失败
* Description :  
* Notice	  :  
*=================================================================*/
bool CSocketSmart::RecvQueryData(byte *lpData, int*nlpDatalen,DWORD nTimeOut)
{
	int  nRet=0;
	int  nLen=0;
	
	nLen=0;
	if(!WaitRecv(nTimeOut) )
	{
		Sleep(20);
		if( (nRet=recv(m_handle,(char*)lpData+nLen,(m_nTotalPos*3)-nLen,0))<0 )
		{
			return false;
		}
		nLen=nRet;		
	}
	if( nLen>=m_nTotalPos*3 )
	{
		*nlpDatalen=nLen;
		return true;
	}
	DWORD nStatus=0;
	DWORD nStartTime=GetTickCount();	
	while( GetTickCount()-nStartTime<(nTimeOut/4))
	{
		if( (nRet=recv(m_handle,(char*)lpData+nLen,(m_nTotalPos*3)-nLen,0))>0 )
		{
			nLen+=nRet;
		}
		if( nLen>=m_nTotalPos*3 )	break; //所有的设备均有状态回复
		nStatus=WSAGetLastError();
		if( nStatus!=WSA_WAIT_EVENT_0&&nStatus!=WSAEWOULDBLOCK) break; //接收数据时出错		
		if( nLen>=3&&(int)lpData[nLen-3]==(int)0xC2 )
		{
			//表示这个包的最大的机号的状态已经收到，表示该包的数据已经收完
			if( (int)lpData[nLen-2]==m_nMaxMacNo)
			{
				break;
			}
		}
		Sleep(5);
	}
	if( nLen>0 )
	{
		*nlpDatalen=nLen;
		return true;
	}
	return false;
}
