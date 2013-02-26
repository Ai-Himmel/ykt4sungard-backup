#ifndef _TCPSOCK_H_
#define _TCPSOCK_H_

#ifdef WIN32
#include <winsock2.h>
typedef int ssize_t;
#endif

#ifndef WIN32
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#else
#define socklen_t unsigned int
#endif 

void SockSetup();
void SockClean();
class TCPSockStream 
{
private:
	SOCKET sock_;
	int errno_;
	int do_connect(const char *host,int port);
	enum { READ_HANDLE = 1,WRITE_HANDLE };
	int do_handle_ready(int t,long timeout);
public:
	TCPSockStream();
	~TCPSockStream();
	TCPSockStream& operator=(const TCPSockStream &rhs);
	int connect(const char *host,int port,long timeout);
	int close();
	void setnonblocking(int block);
	int send_n(const unsigned char *buf,size_t len,long timeout);
	ssize_t recv_n(unsigned char *buf,size_t maxlen,long timeout);
	int handle_read_ready(long timeout);
	int handle_write_ready(long timeout);
	int get_last_error();
};


#endif //_TCPSOCK_H_
