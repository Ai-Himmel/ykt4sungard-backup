#include "stdafx.h"
#include "tcpsock.h"



#ifdef WIN32
void SockSetup()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	WSAStartup( wVersionRequested, &wsaData );
}
void SockClean()
{
	WSACleanup();
}
#else
void SockSetup()
{
}
void SockClean()
{
}
#endif
//////////////////////////////////////////////////////////////////////////
// 
TCPSockStream::TCPSockStream():sock_(INVALID_SOCKET)
{
	//
}
TCPSockStream::~TCPSockStream()
{
	//
	close();
}
TCPSockStream& TCPSockStream::operator =(const TCPSockStream& rhs)
{
	this->sock_ = rhs.sock_;
	return *this;
}

int TCPSockStream::do_connect(const char *host,int port)
{
	int ret;
	struct sockaddr_in  serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr(host);
	serv.sin_port = htons(port);
//#ifdef WIN32
//	ret = WSAConnect(sock_,(const struct sockaddr*)&serv,(socklen_t)sizeof(serv),NULL,NULL,NULL,NULL);
//#else
	ret = ::connect(sock_,(const struct sockaddr*)&serv,(socklen_t)sizeof(serv));
//#endif
	
	return 0;
}

int TCPSockStream::do_handle_ready(int t,long timeout)
{
	int ret;
	struct timeval tv;
#ifdef WIN32
	FD_SET rd,wr,exp;
#else
	fd_set rd,wr,exp;
#endif
	FD_ZERO(&rd);
	FD_ZERO(&wr);
	FD_ZERO(&exp);
	if(READ_HANDLE & t)
		FD_SET(sock_,&rd);
	if(WRITE_HANDLE & t)
		FD_SET(sock_,&wr);

	if(timeout > 0)
	{
		tv.tv_sec = timeout / 1000;
		tv.tv_usec = (timeout % 1000) * 1000;
	}

	do 
	{
		if(timeout > 0)
			ret = select(1,&rd,&wr,&exp,&tv);
		else
			ret = select(1,&rd,&wr,&exp,NULL);
		if(ret==0)
		{
			return 1;
		}
		else if(ret == SOCKET_ERROR)
		{
#ifdef WIN32
			errno_ = WSAGetLastError();
#else
			errno_ = errno;
#endif
			return -1;
		}
		if(READ_HANDLE == t)
		{
			if(FD_ISSET(sock_,&rd))
				return 0;
		}
		else if(WRITE_HANDLE == t)
		{
			if(FD_ISSET(sock_,&wr))
				return 0;
		}
		return -1;
	}while(1);
}

int TCPSockStream::handle_read_ready(long timeout)
{
	return do_handle_ready(READ_HANDLE,timeout);
}
int TCPSockStream::handle_write_ready(long timeout)
{
	return do_handle_ready(WRITE_HANDLE,timeout);
}
int TCPSockStream::connect(const char *host,int port,long timeout)
{
	int ret;
	unsigned char buf[1];
	close();
#ifdef WIN32
	sock_ = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,0);
#else
	sock_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#endif 
	if(sock_ == INVALID_SOCKET)
		return -1;
	setnonblocking(1);
	ret = do_connect(host,port);
	if(ret)
		return -1;

	return send_n(buf,0,timeout);
}
int TCPSockStream::close()
{
	if(sock_ == INVALID_SOCKET)
		return 0;
#ifdef WIN32
	::shutdown(sock_,SD_BOTH);
	::closesocket(sock_);
#else
	::close(sock_);
#endif
	sock_ = INVALID_SOCKET;
	return 0;
}

void TCPSockStream::setnonblocking(int block)
{
#ifdef WIN32
	u_long v = block;
	::ioctlsocket(sock_,FIONBIO,&v);
#else
	int v;
	v = ::fcntl(sock_,F_GETFL,0);
	if(block)
		::fcntl(sock_,F_SETFL,v|O_NONBLOCK);
	else
		::fcntl(sock_,F_SETFL,v^O_NONBLOCK);
#endif 
}

int TCPSockStream::send_n(const unsigned char *buf,size_t len,long timeout)
{
	int ret;
	ssize_t r;
	size_t s;
	ret = handle_write_ready(timeout);
	if(ret>0) // timeout
		return 1;
	if(ret<0)
		return -1;
	s = 0;
	do 
	{
#ifdef WIN32
		r = send(sock_,(const char*)buf+s,len,0);
#else
		r = send(sock_,(const void*)(buf+s),len,0);
#endif
		if(r < 0) // send error
		{
			errno_ = get_last_error();
			return -1;
		}
		s += r;
		len-=r;
	} while(len>0);

	return 0;
}
ssize_t TCPSockStream::recv_n(unsigned char *buf,size_t maxlen,long timeout)
{
	int ret;
	ssize_t r;
	size_t s;
	s = 0;

	do 
	{
#ifdef WIN32
		r = recv(sock_,(char*)buf+s,maxlen,0);
#else
		r = recv(sock_,(void*)(buf+s),maxlen,0);
#endif
		if(r < 0||r == 0) // send error
		{
			if(r < 0)
			{

				ret = handle_read_ready(timeout);
				errno_ = get_last_error();
				if(ret>0) // timeout
					return -2;	
#ifdef WIN32
					if(errno_ != WSAEWOULDBLOCK)
#else
					//if(errno_ != WSAEWOULDBLOCK)
#endif
					{
						return -1;
					}
			}
			else if(r ==0)
			{
				return -1;
			}
		}
		if(r > 0)
		{
			s += r;
			maxlen-=r;
		}
		
	} while(maxlen>0);
	return s;
}

int TCPSockStream::get_last_error()
{
#ifdef WIN32
	errno_ = WSAGetLastError();
#else
	errno_ = errno;
#endif
	return errno_;
}