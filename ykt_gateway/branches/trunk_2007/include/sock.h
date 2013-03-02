#ifndef _KSG_SOCKET_H_
#define _KSG_SOCKET_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <list>
#include <algorithm>
#include <cassert>
#include <boost/functional.hpp>
#include "ksgexception.h"

#ifdef WIN32
#include <WinSock2.h>
#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

class SocketBase
{
protected:
	int _sock;
	virtual void NewSocket() = 0;
public:
	SocketBase():_sock(-1)
	{
		NewSocket();
	}
	virtual ~SocketBase()
	{}
	virtual void Close() throw();
	inline bool IsValidate() const
	{
		return (_sock != -1);
	}
	int GetSock() const { return _sock; }
	int SetSocketOption(int level,int optname,const char* optvalue,int valuelen);
};

class TCPSocket : public SocketBase
{
protected:
	virtual void NewSocket();
public:
	TCPSocket():SocketBase()
	{}
	virtual ~TCPSocket()
	{}
	int Read(void * buf,int maxlen);
	int Write(void* buf,int buflen);
	//! 判断可以读写
	/*
	\param timeout 超时等待时间，单位为毫秒
	*/
	int Select(int timeout);
	//void Accept(
};

class UDPSocket : public SocketBase
{
protected:
	virtual void NewSocket();
public:
	UDPSocket():SocketBase()
	{}
	virtual ~UDPSocket()
	{}
	int SendTo(const std::string& ip,int port,void* buf,int buflen);
	int RecvFrom(std::string& fromIp,int* port,void* buf,int maxlen);
};

template<class Connector>
class ServerSocket
{
private:
	typedef std::list<Connector*> CnntListType;
	CnntListType _cnntList;
protected:
	void DoAccept();
	inline void CloseEachConnector(Connector* conn)
	{
		conn->Close();
	}
	inline void ListenAtPort(int port,Connector* conn)
	{
		if(conn->IsValidate())
		{
			struct sockaddr_in addr;
			memset(&addr,0,sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			if(bind(conn->GetSock(),reinterpret_cast<struct sockaddr*>(&addr),sizeof(addr)))
			{
				// bind error 
				throw CannotListenException();
			}
			if(listen(conn->GetSock(),1))
			{
				// listen error
				throw CannotListenException();
			}
		}
	}
public:
	int Listen(int port)
	{
		assert(port > 0 && port < 65535);
		try
		{
			std::for_each(_cnntList.begin(),_cnntList.end(),
				boost::bind(&ServerSocket::ListenAtPort,this,port,_1));
			return 0;
		}
		catch(...)
		{
			return -1;
		}
	}
	void Close()
	{
		std::for_each(_cnntList.begin(),_cnntList.end(),
			boost::bind(&ServerSocket::CloseEachConnector,this,_1));
	}
	void AddConnector(Connector* conn)
	{
		_cnntList.push_back(conn);
	}
	
};

template<class Connector>
class ClientSocket
{
private:
	
public:
	int Connect(const std::string& ip,int port)
	{

	}
};

#endif // _KSG_SOCKET_H_

