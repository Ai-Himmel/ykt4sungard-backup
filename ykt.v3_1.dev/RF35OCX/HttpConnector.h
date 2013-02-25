#ifndef _HTTPCONNECTOR_H_
#define _HTTPCONNECTOR_H_

#pragma once

#include "cstring.h"

#ifdef WIN32
#include <WinSock.h>
#endif // WIN32

#include <string>
#include <map>
#include <exception>

#ifdef _USE_SSL
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif // _USE_SSL

namespace cutil 
{

#ifdef WIN32
#define _CLOSE_SOCKET(sd) closesocket((sd))
#else
#define _CLOSE_SOCKET(sd) close((sd))
#endif

//! TCP socket 连接
class TCPSocket
{
protected:
#ifdef WIN32
	int _sock; //< socket 连接
#else
	int _sock; //< socket 连接
#endif
	bool _bConnected;
public:
	//! default constructor
	TCPSocket():_sock(-1),_bConnected(false){}
	virtual ~TCPSocket() { }
	//! 连接远程服务器
	/*!
	 * 连接远程服务器
	 * \param host 主机名
	 * \param port 主机端口
	 * \return 连接成功返回 0, 失败返回 -1
	 */
	virtual int Connect(const char* host,int port)
	{
		Close();
		struct sockaddr_in sa;
		struct hostent * he;

		_sock = socket(AF_INET,SOCK_STREAM,0);
		if(!UNLIKELY(_sock))
		{
			return -1;
		}
		if((he = gethostbyname(host)) == NULL)
		{
			_CLOSE_SOCKET(_sock);
			_sock = -1;
			return -1;
		}
		memset(&sa,0,sizeof(sa));
		sa.sin_family = AF_INET;
		memcpy(&sa.sin_addr,(struct sockaddr *)he->h_addr,sizeof(sa.sin_addr));
		sa.sin_port = htons((u_short)port);
		if(connect(_sock,(struct sockaddr*)&sa,sizeof(sa)))
		{
			_CLOSE_SOCKET(_sock);
			_sock = -1;
			return -1;
		}
		_bConnected = true;
		return 0;
	}
	//! 关闭远程连接
	/*!
	 * \return 成功返回 0 ,失败返回 -1
	 */
	virtual int Close()
	{
		if(IsConnected())
		{
			_CLOSE_SOCKET(_sock);
			_sock = -1;
			_bConnected = false;
		}
		return 0;
	}
	//! 当前的连接状态
	bool IsConnected() const {return _bConnected;}
	//! 发送数据
	/*!
	 * \param buf 要发送的内容
	 * \param bufLen buf的长度
	 * \return 返回发送成功的字节数,失败返回 -1
	 */
	virtual int Write(const void *buf,int bufLen)
	{
#ifdef WIN32
		return send(_sock,(const char*)buf,bufLen,0);
#else
		return write(_sock,buf,bufLen);
#endif
	}
	//! 接收数据
	/*!
	 * \param buf 接收数据的buf
	 * \param maxLen 最大接收数据buf的长度
	 * \return 返回实现接收到的数据的长度,失败返回 -1
	 */
	virtual int Read(void * buf,int maxLen)
	{
#ifdef WIN32
		return recv(_sock,(char*)buf,maxLen,0);
#else
		return read(_sock,buf,maxLen);
#endif
	}
};

#ifdef _USE_SSL
//! SSL TCP socket
class SSLTCPSocket : public TCPSocket
{
private:
	SSL_CTX* _ctx;
	SSL*     _ssl;
	X509*    _server_cert;
	SSL_METHOD* _meth;
	//! 删除 SSL 资源
	void Reset()
	{
		if(_server_cert)
		{
			X509_free(_server_cert);
			_server_cert = NULL;
		}
		if(_meth)
		{
			//
			_meth = NULL;
		}
		if(_ssl)
		{
			SSL_free(_ssl);
			_ssl = NULL;
		}
		if(_ctx)
		{
			SSL_CTX_free(_ctx);
			_ctx = NULL;
		}
	}
	//! 初始化 SSL 连接
	/*!
	 * \return 成功返回 0 ,失败返回 -1
	 */
	int DoSSLConnect()
	{
		char * str;
		SSL_library_init();
		// SSLeay_add_all_algorithms();
		SSL_load_error_strings();
		SSLeay_add_ssl_algorithms();
		_meth = SSLv23_client_method();
		if(NULL == _meth)
		{
			return -1;
		}
		_ctx = SSL_CTX_new(_meth);
		if(NULL == _ctx)
		{
			return -1;
		}
		_ssl = SSL_new(_ctx);
		if(NULL == _ssl)
		{
			return -1;
		}
		if(!SSL_set_fd(_ssl,_sock))
		{
			return -2;
		}
		SSL_set_connect_state(_ssl);
		if(SSL_connect(_ssl) == -1)
		{
			char errbuff[1024];
			unsigned long curerr = 0;
			memset(errbuff, 0, sizeof(errbuff));
			while ( 0 != (curerr = ERR_get_error()))
			{
				AfxMessageBox(ERR_error_string(curerr, errbuff));
			}
			return -2;
		}
		SSL_get_cipher(_ssl);
		_server_cert = SSL_get_peer_certificate(_ssl);
		str = X509_NAME_oneline(X509_get_subject_name(_server_cert),0,0);
		if(NULL == str)
		{
			return -1;
		}
		OPENSSL_free(str);
		str = X509_NAME_oneline(X509_get_issuer_name(_server_cert),0,0);
		if(NULL == str)
		{
			return -1;
		}
		OPENSSL_free(str);
		X509_free(_server_cert);
		_server_cert = NULL;
		return 0;
	}
public:
	//! default constructor
	SSLTCPSocket():_ctx(NULL),_ssl(NULL),_server_cert(NULL),_meth(NULL){}
	virtual ~SSLTCPSocket() {}
	//! 连接远程服务器
	/*!
	 * 连接远程服务器
	 * \param host 主机名
	 * \param port 主机端口
	 * \return 连接成功返回 0, 失败返回 -1
	 */
	virtual int Connect(const char* host,int port)
	{
		if(TCPSocket::Connect(host,port))
		{
			Close();
			return -1;
		}
		if(DoSSLConnect())
		{
			Close();
			return -1;
		}
		_bConnected = true;
		return 0;
	}
	//! 关闭远程连接
	/*!
	 * \return 成功返回 0 ,失败返回 -1
	 */
	virtual int Close()
	{
		if(IsConnected())
		{
			SSL_shutdown(_ssl);
			TCPSocket::Close();
			Reset();
			_bConnected = false;
		}
		return 0;
	}
	//! 发送数据
	/*!
	 * \param buf 要发送的内容
	 * \param bufLen buf的长度
	 * \return 返回发送成功的字节数,失败返回 -1
	 */
	int Write(const void *buf,int bufLen)
	{
		return SSL_write(_ssl,buf,bufLen);
	}
	//! 接收数据
	/*!
	 * \param buf 接收数据的buf
	 * \param maxLen 最大接收数据buf的长度
	 * \return 返回实现接收到的数据的长度,失败返回 -1
	 */
	int Read(void * buf,int maxLen)
	{
		return SSL_read(_ssl,buf,maxLen);
	}
};
#endif // _USE_SSL

//! Socket 连接句柄的封装
/*!
 * 标准的 TCP Socket 连接
 */
template<class Socket>
class TCPHandler
{
private:
	myString _host;
	int _port;
	Socket _sock;
public:
	TCPHandler(){}
	int Connect(const myString& host,int port)
	{
		_host = host;
		_port = port;
		return _sock.Connect(T2A(host.c_str()),port);
	}
	int Close()
	{
		if(_sock.IsConnected())
		{
			return _sock.Close();
		}
		return 0;
	}
	//! 发送数据
	/*!
	 * \param buf 要发送的数据,宽字符长度不能超过512个字符,双字符长度可以是任意长度
	 * \return 发送成功返回发送的字符数,失败返回 -1
	 */
	int Write(const myString& buf)
	{
		if(_sock.IsConnected())
		{
			USES_CONVERSION;
#ifdef UNICODE
			assert(buf.length() < CONVERSION_BUF_LEN);
#endif
			char * ansiBuf = T2A(buf.c_str());
			int ansiLen = strlen(ansiBuf);
			int pos = 0;
			int sendlen = 0;
			do 
			{
				sendlen = _sock.Write(ansiBuf+pos,ansiLen-pos);
				if(sendlen == -1)
					return -1;
				pos += sendlen;
				if(pos >= ansiLen)
					return pos;
			} while(true);
		}
		return -1;
	}
	//! 发送数据
	/*!
	 * \param buf 数据缓存
	 * \param buflen 缓存长度, 字节数 (in char)
	 * \return 成功返回发送的数据长度,失败返回 -1
	 */
	int Write(const void* buf,int buflen)
	{
		if(_sock.IsConnected())
		{
			int pos = 0;
			int sendlen = 0;
			do 
			{
				sendlen = _sock.Write(buf,buflen-pos);
				if(sendlen == -1)
					return -1;
				pos += sendlen;
				if(pos >= buflen)
					return pos;
			} while(true);
		}
		return -1;
	}
	//! 接收数据
	/*!
	 * \param 保存读取的数据的 Buf
	 * \return 成功返回 buf 的长度,失败返回 -1
	 */
	int Read(myString& buf)
	{
		if(_sock.IsConnected())
		{
			// 为最大传输单元设置
			char tmp[1024] = "";
			int readlen = 0;
			USES_CONVERSION;
			while (true)
			{
				readlen = _sock.Read(tmp,sizeof(tmp)-1);
				if(readlen <= 0)
					break;
				tmp[readlen] = '\0';
				TCHAR * tBuf = A2T(tmp);
				buf.append(tBuf);
			}
			return buf.length();
		}
		return -1;
	}
	//! 接收数据
	/*!
	 * \param buf 接收数据的缓存
	 * \param maxLen 缓存最大长度
	 * \return 成功返回读取的长度,失败返回 -1
	 */
	int Read(void * buf,int maxLen)
	{
		if(_sock.IsConnected())
		{
			int readlen = 0;
			int pos = 0;
			while (true)
			{
				readlen = _sock.Read((char*)buf+pos,maxLen - pos);
				if(readlen <= 0)
					break;
				pos += readlen;
				if(pos >= maxLen)
					break;
			}
			return pos;
		}
		return 0;
	}
};

class cURL;
//! Http 连接类
/*!
 * \param Socket 使用的TCP SOCKET
 */
template <
class Socket
>
class CHttpConnector
{
private:
	typedef TCPHandler<Socket> HttpSocket;
	typedef std::map<myString,myString> HttpHeader;
	
public:
	typedef enum {hcPost,hcGet} HTTPMethod;
private:
	HttpSocket _conn;	//< 连接的 Socket
	myString _server;	//< 服务器
	int _port;			//< 端口
	int Connect()
	{
		return _conn.Connect(_server,_port);
	}
	int Close()
	{
		return _conn.Close();
	}
	myString _buffer;
	myString _responseText;
	int _bufpos;
	HttpHeader _header;
	myString GetMethodCmd(HTTPMethod method)
	{
			switch(method)
			{
			case hcGet :
				return _T("GET ");
			case hcPost:
				return _T("POST ");
			default:
				throw std::exception(_T("method does not support!"));
			}
	}
	void FormatPostHeader(const cURL& url,myStringbuf & content)
	{
		content<<GetMethodCmd(hcGet).c_str()<<url.GetFullRequest()
			<<_T(" HTTP/1.1\r\n")<<_T("Host: ")<<_server<<_T(":")<<_port
			<<_T("\r\nAccept: */*\r\n")<<_T("Accept-Encoding: * \r\n")
			<<_T("Content-type: application/x-www-form-urlencoded\r\n");
		myStringbuf data;
		cURL::req_rec::const_iterator i = url.GetRequestRecord().begin();
		for(;i != url.GetRequestRecord().end();++i)
		{
			data<<(*i).first<<_T(":")<<(*i).second<<_T("\r\n");
		}
		content<<_T("Content-length: ")<<data.str().size()<<_T("\r\n\r\n");
		content<<data.str();
	}
	void FormatGetHeader(const cURL& url,myStringbuf & content)
	{
		content<<GetMethodCmd(hcPost).c_str()<<url.GetFullRequest()
			<<_T(" HTTP/1.1\r\n")<<_T("Host: ")<<_server<<_T(":")<<_port
			<<_T("\r\nAccept: */*\r\n")<<_T("Accept-Encoding: * \r\n\r\n");
	}
public:
	CHttpConnector(const TCHAR* server,int port)
		:_server(server),_port(port)
	{
		// 
	}
	CHttpConnector(const CHttpConnector& rhl)
	{
		_server = rhl._server;
		_port = rhl._port;
	}
	CHttpConnector& operator = (const CHttpConnector& rhl)
	{
		_server = rhl._server;
		_port = rhl._port;
		return *this;
	}
	virtual ~CHttpConnector(void)
	{
		_conn.Close();
	}
	int PostRequest(const cURL& url,HTTPMethod method = hcGet)
	{
		int ret; 
		myStringbuf content;
		
		if(hcGet == method)
		{
			FormatGetHeader(url,content);
		}
		else
		{
			FormatPostHeader(url,content);
		}
		ret = Connect();
		if(ret)
		{
			return ret;
		}
		ret = SendToServer(content.str());
		if(-1 == ret)
		{
			return -1;
		}
		if(RecvResponse())
		{
			return -1;
		}
		// 保存返回状态字符串
		_responseText = ReadLine();
		// 处理返回HTTP头信息
		ProcessHeader();
		Close();
		return 0;
	}
	const myString & GetBuffer() const
	{

	}
	int GetReturnCode()
	{
		if(_responseText.length() == 0)
			return -1;
		size_t p = _responseText.find(_T(' '));
		if(p > 0)
		{
			return _ttoi(_responseText.substr(p+1).c_str()); 
		}
		return -1;
	}
private:
	// 发送内容
	int SendToServer(const myString& content)
	{
		std::string buf = TS2AS(content);
		return _conn.Write(buf.c_str(),buf.length());
	}
	// 接收应答
	int RecvResponse()
	{
		char buf[1460+1];
		int recvlen;
		ResetHeader();
		do 
		{
			recvlen = _conn.Read(buf,sizeof(buf)-1);
			if(recvlen == 0 || recvlen == WSAECONNRESET)
			{
				return 0;
			}
			if(SOCKET_ERROR == recvlen)
			{
				throw std::exception(_T("接收数据失败"));
			}
			buf[recvlen] = '\0';
			_buffer.append(AS2TS(buf));
		} while(1);
		return -1;
	}
	void ProcessHeader()
	{
		myString line;
		size_t pos;
		do {
			line = ReadLine();
			if(line.length() == 0)
				break;
			pos = line.find(_T(':'));
			if(pos < 0)
				continue;
			//将 Header 保存到 map 中
			_header[line.substr(0,pos)] = line.substr(pos+1);
		} while(1);
	}
	inline void ResetHeader()
	{
		_buffer = _T("");
		_bufpos = 0;
		_header.clear();
	}
	myString ReadLine()
	{
		int start = _bufpos;
		int end;
		while(_bufpos < (int)_buffer.length())
		{
			if(_buffer[_bufpos] == _T('\r') && _buffer[_bufpos+1] == _T('\n'))
			{
				end = _bufpos;
				_bufpos+=2;
				return _buffer.substr(start,end-start);
			}
			_bufpos++;
		}
		return _buffer.substr(start);
	}
};

class cURL
{
public:
	typedef std::map<myString,myString> req_rec;
private:
	myString _server;
	int _port;
	myString _request;
	myString _fullRequest;
	req_rec _requestRec;
	bool _bSSL;
	void Reset()
	{
		_server = _T("");
		_port = 0;
		_request = _T("");
		_fullRequest = _T("");
		_bSSL = false;
		_requestRec.clear();
	}
public:
	cURL(){}
	cURL(const myString& url):_server(_T("")),_port(0),
		_request(_T("")),_fullRequest(_T("")),_bSSL(false)
	{
		ParseURL(url);
	}
	cURL(const cURL& rhl)
	{
		_server = rhl._server;
		_port = rhl._port;
		_request = rhl._request;
		_fullRequest = rhl._fullRequest;
		_bSSL = rhl._bSSL;
		_requestRec = rhl._requestRec;
	}
	cURL & operator = (const cURL& rhl)
	{
		_server = rhl._server;
		_port = rhl._port;
		_request = rhl._request;
		_fullRequest = rhl._fullRequest;
		_requestRec = rhl._requestRec;
		_bSSL = rhl._bSSL;
		return *this;
	}
	~cURL()
	{
		//
	}
	myString GetServer() const{  return _server; }
	int GetPort() const{ return _port; }
	bool IsSSL() const {return _bSSL; }
	myString GetRequest() const {return _request; }
	myString GetFullRequest() const {return _fullRequest; }
	myString operator[](const myString& param)
	{
		if(_requestRec.find(param) != _requestRec.end())
		{
			return _requestRec[param];
		}
		return _T("");
	}
	const req_rec & GetRequestRecord() const { return _requestRec; }
	int ParseURL(const myString& url)
	{
		Reset();
		int i,j;
		_fullRequest = url;
		int startPos = url.find(_T("http://"));
		if(startPos == myString::npos)
		{
			startPos = url.find(_T("https://"));
			if(startPos == myString::npos)
				return -1;
			_bSSL = true;
			startPos = _tcslen(_T("https://"));
		}
		else
		{
			startPos = _tcslen(_T("http://"));
		}
		_port = 80;
		if(_bSSL)
		{
			_port = 443;
		}
		i = url.find(_T(":"),startPos);
		j = url.find(_T("/"),startPos);
		// 如果在 : 之后有 / ,或者 : 之后没有 /
		if( (i > 0 && i < j) || (i > 0 && j == myString::npos))
		{
			i++;
			if(j > 0)
			{
				_port = _ttoi(url.substr(i,j - i).c_str());
			}
			else
			{
				_port = _ttoi(url.substr(i).c_str());
			}
			if(_port <= 0)
				return -1;
			_server = url.substr(startPos,i-startPos-1);

			if(j == myString::npos)
			{
				// : 之后没有 / 分析完成
				_request = _T("/");
				// _fullRequest = _request;
				return 0;
			}
			// 从端口之后开始分析
			startPos = j+1;
		}
		else if(j > 0)
		{
			// 没有指定端口
			_server = url.substr(startPos,j-startPos);
			startPos = j+1;
		}
		else
		{
			// 没有端口,也没有 / 号
			_server = url.substr(startPos);
			_request = _T("/");
			// _fullRequest = _request;
			return 0;
		}
		// _fullRequest = url.substr(startPos);
		i = url.find(_T("?"),startPos);
		if(i > 0)
		{
			//有参数
			_request = url.substr(startPos,i-startPos);
			startPos = i+1;
			while(startPos < url.length())
			{
				i = url.find(_T("="),startPos);
				if(i > startPos)
				{
					myString param = url.substr(startPos,i-startPos);
					j = url.find(_T("&"),i);
					myString paramVal = _T("");
					if(j > i)
					{
						paramVal = url.substr(i+1,j-i-1);
					}
					else
					{
						paramVal = url.substr(i+1);
					}
					_requestRec[param] = paramVal;
					// 没有更多的参数了
					if(j == myString::npos)
					{
						return 0;
					}
					startPos = j + 1;
				}
				else
					break;
			}
			if(startPos < url.length())
			{
				myString param = url.substr(startPos);
				_requestRec[param] = _T("");
			}
		}
		else
		{
			// 没有参数
			_request = url.substr(startPos);
			return 0;
		}
		
		return 0;
	}
};
}

#endif // _HTTPCONNECTOR_H_