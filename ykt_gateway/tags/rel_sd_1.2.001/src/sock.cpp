#include "stdafx.h"
#include "sock.h"
#ifdef WIN32
#include <WinSock2.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

/////////////////////////////////////////////////////////////////////
// SocketBase
int SocketBase::SetSocketOption(int level, int optname,
								 const char *optvalue, int valuelen)
{
#ifdef WIN32

	return setsockopt(_sock,level,optname,optvalue,valuelen);

#else

	return setsockopt(_sock,level,optname,reinterpret_cast<const void*>(optvalue),
		static_cast(socklen_t) valuelen);

#endif
}

void SocketBase::Close() throw()
{
	if(IsValidate())
	{
		try
		{
#ifdef WIN32
			closesocket(_sock);
#else
			close(_sock);
#endif
		}
		catch(...)
		{
			// do nothing
		}
	}
}

///////////////////////////////////////////////////////////////////////
// TCPSocket
void TCPSocket::NewSocket()
{
#ifdef WIN32
	_sock = (int)socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#else
	_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#endif 
}

int TCPSocket::Read(void *buf, int maxlen)
{
	int readlen = 0;
	int recvBytes = 0;
	do
	{
#ifdef WIN32
		recvBytes = recv(_sock,reinterpret_cast<char*>(buf)+readlen,maxlen-readlen,0);
		if(0 == recvBytes || WSAECONNRESET == recvBytes)
		{
			break;
		}
		readlen += recvBytes;
#else
		recvBytes = read(_sock,reinterpret_cast<char*>(buf)+readlen,maxlen-readlen);
		if(-1 == recvBytes)
		{
			if(errno == EINTR)
				continue;
			break;
		}
		readlen += recvBytes;
#endif
	}while(1);
	return readlen;
}

int TCPSocket::Write(void* buf,int buflen)
{
	int sendBytes = 0;
	int writelen = 0;
	while(writelen < buflen)
	{
#ifdef WIN32
		sendBytes = send(_sock,reinterpret_cast<char*>(buf)+writelen,buflen-writelen,0);
		if(SOCKET_ERROR == sendBytes)
		{
			break;
		}
		writelen += sendBytes;
#else
		sendBytes = write(_sock,reinterpret_cast<char*>(buf)+writelen,buflen-writelen);
		if(-1 == sendBytes)
		{
			if(EINTR == errno)
				continue;
			break;
		}
		writelen += sendBytes;
#endif
	}
	return writelen;
}
