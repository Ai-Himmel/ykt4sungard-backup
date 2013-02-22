#include "tcp.h"
#include "stdafx.h"
#include "mypub.h"

#ifndef WIN32
#include <netinet/tcp.h>
#endif

/**
��Tcp����ĳ�ʼ��
*/
class  CTcpInit
{
public:
	/**���캯��
	*��Windowsϵͳ�µ�Tcp����ĳ�ʼ��
	*/
	CTcpInit();
   ~CTcpInit();
};


static CTcpInit _TCP_INIT;
CTcpInit::CTcpInit()
{
#ifdef WIN32
/* ****** Updated by CHENYH at 2004-2-8 18:59:57 ****** 
   WORD wVersionRequested=MAKEWORD(0,2);
	WSADATA initData;
	initData.wVersion=0;
	initData.wHighVersion=2;
	strcpy(initData.szDescription,"");
	strcpy(initData.szSystemStatus,"");
	initData.iMaxSockets=100;
	initData.lpVendorInfo=0;
	initData.lpVendorInfo="";
*/
   WORD wVerRequest = MAKEWORD(2,0);
   WSADATA dWSAData;
	if (WSAStartup(wVerRequest,&dWSAData)!=0)
		RAISE_RUNTIME_ERROR("Can not init socket");
#endif
}

CTcpInit::~CTcpInit()
{
#ifdef WIN32
   WSACleanup();
#endif
}

//////////////////////////////////////////////////////////////////////
// CTcpSocket Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpSocket::CTcpSocket()
{
   m_socket = INVALID_SOCKET;
   m_nAddressFamily = AF_INET;
   m_bConnected = false;
}

CTcpSocket::CTcpSocket(CTcpSocket &ts)
{
   m_socket = ts.m_socket;
   m_nAddressFamily = ts.m_nAddressFamily;
   m_bConnected = ts.m_bConnected;
}

CTcpSocket::~CTcpSocket()
{
   Close();
}

void CTcpSocket::Close()
{
   if (m_socket!=INVALID_SOCKET)
   {
      closesocket(m_socket);
      m_socket = INVALID_SOCKET;
      m_bConnected = false;
   }
}

int CTcpSocket::GetLastError(char *szMsgBuf, int MsgBLen)
{
   int errcode = GET_LAST_SOCK_ERROR();
   if (MsgBLen>0 && szMsgBuf!=NULL)
   {
      char msg[256];
      switch(errcode)
      {
#ifdef WIN32
      case WSAEINTR:
         sprintf(msg,"%d:Interrupted function call. ",errcode);
         break;
      case WSAEACCES:
         sprintf(msg,"%d:Permission denied. ",errcode);
         break;
      case WSAEFAULT:
         sprintf(msg,"%d:Bad address. ",errcode);
         break;
      case WSAEINVAL:
         sprintf(msg,"%d:Invalid argument. ",errcode);
         break;
      case WSAEMFILE:
         sprintf(msg,"%d:Too many open files. ",errcode);
         break;
      case WSAEWOULDBLOCK:
         sprintf(msg,"%d:Resource temporarily unavailable. ",errcode);
         break;
      case WSAEINPROGRESS:
         sprintf(msg,"%d:Operation now in progress. ",errcode);
         break;
      case WSAEALREADY:
         sprintf(msg,"%d:Operation already in progress. ",errcode);
         break;
      case WSAENOTSOCK:
         sprintf(msg,"%d:Socket operation on nonsocket. ",errcode);
         break;
      case WSAEDESTADDRREQ:
         sprintf(msg,"%d:Destination address required. ",errcode);
         break;
      case WSAEMSGSIZE:
         sprintf(msg,"%d:Message too long. ",errcode);
         break;
      case WSAEPROTOTYPE:
         sprintf(msg,"%d:Protocol wrong type for socket. ",errcode);
         break;
      case WSAENOPROTOOPT:
         sprintf(msg,"%d:Bad protocol option. ",errcode);
         break;
      case WSAEPROTONOSUPPORT:
         sprintf(msg,"%d:Protocol not supported. ",errcode);
         break;
      case WSAESOCKTNOSUPPORT:
         sprintf(msg,"%d:Socket type not supported. ",errcode);
         break;
      case WSAEOPNOTSUPP:
         sprintf(msg,"%d:Operation not supported. ",errcode);
         break;
      case WSAEPFNOSUPPORT:
         sprintf(msg,"%d:Protocol family not supported. ",errcode);
         break;
      case WSAEAFNOSUPPORT:
         sprintf(msg,"%d:Address family not supported by protocol family. ",errcode);
         break;
      case WSAEADDRINUSE:
         sprintf(msg,"%d:Address already in use. ",errcode);
         break;
      case WSAEADDRNOTAVAIL:
         sprintf(msg,"%d:Cannot assign requested address. ",errcode);
         break;
      case WSAENETDOWN:
         sprintf(msg,"%d:Network is down. ",errcode);
         break;
      case WSAENETUNREACH:
         sprintf(msg,"%d:Network is unreachable. ",errcode);
         break;
      case WSAENETRESET:
         sprintf(msg,"%d:Network dropped connection on reset. ",errcode);
         break;
      case WSAECONNABORTED:
         sprintf(msg,"%d:Software caused connection abort. ",errcode);
         break;
      case WSAECONNRESET:
         sprintf(msg,"%d:Connection reset by peer. ",errcode);
         break;
      case WSAENOBUFS:
         sprintf(msg,"%d:No buffer space available. ",errcode);
         break;
      case WSAEISCONN:
         sprintf(msg,"%d:Socket is already connected. ",errcode);
         break;
      case WSAENOTCONN:
         sprintf(msg,"%d:Socket is not connected. ",errcode);
         break;
      case WSAESHUTDOWN:
         sprintf(msg,"%d:Cannot send after socket shutdown. ",errcode);
         break;
      case WSAETIMEDOUT:
         sprintf(msg,"%d:Connection timed out. ",errcode);
         break;
      case WSAECONNREFUSED:
         sprintf(msg,"%d:Connection refused. ",errcode);
         break;
      case WSAEHOSTDOWN:
         sprintf(msg,"%d:Host is down. ",errcode);
         break;
      case WSAEHOSTUNREACH:
         sprintf(msg,"%d:No route to host. ",errcode);
         break;
      case WSAEPROCLIM:
         sprintf(msg,"%d:Too many processes. ",errcode);
         break;
      case WSASYSNOTREADY:
         sprintf(msg,"%d:Network subsystem is unavailable. ",errcode);
         break;
      case WSAVERNOTSUPPORTED:
         sprintf(msg,"%d:Winsock.dll version out of range. ",errcode);
         break;
      case WSANOTINITIALISED:
         sprintf(msg,"%d:Successful WSAStartup not yet performed. ",errcode);
         break;
      case WSAEDISCON:
         sprintf(msg,"%d:Graceful shutdown in progress. ",errcode);
         break;
      case WSATYPE_NOT_FOUND:
         sprintf(msg,"%d:Class type not found. ",errcode);
         break;
      case WSAHOST_NOT_FOUND:
         sprintf(msg,"%d:Host not found. ",errcode);
         break;
      case WSATRY_AGAIN:
         sprintf(msg,"%d:Nonauthoritative host not found. ",errcode);
         break;
      case WSANO_RECOVERY:
         sprintf(msg,"%d:This is a nonrecoverable error. ",errcode);
         break;
      case WSANO_DATA:
         sprintf(msg,"%d:Valid name, no data record of requested type. ",errcode);
         break;
      case WSA_INVALID_HANDLE:
         sprintf(msg,"%d:Specified event object handle is invalid. ",errcode);
         break;
      case WSA_INVALID_PARAMETER:
         sprintf(msg,"%d:One or more parameters are invalid. ",errcode);
         break;
      case WSA_IO_INCOMPLETE:
         sprintf(msg,"%d:Overlapped I/O event object not in signaled state. ",errcode);
         break;
      case WSA_IO_PENDING:
         sprintf(msg,"%d:",errcode);
         break;
      case WSA_NOT_ENOUGH_MEMORY:
         sprintf(msg,"%d:Insufficient memory available. ",errcode);
         break;
      case WSA_OPERATION_ABORTED:
         sprintf(msg,"%d:Overlapped operation aborted. ",errcode);
         break;
#ifdef WSAINVALIDPROCTABLE
      case WSAINVALIDPROCTABLE:
         sprintf(msg,"%d:Invalid procedure table from service provider. ",errcode);
         break;
#endif
#ifdef WSAINVALIDPROVIDER
      case WSAINVALIDPROVIDER:
         sprintf(msg,"%d:Invalid service provider version number. ",errcode);
         break;
#endif
#ifdef WSAPROVIDERFAILEDINIT
      case WSAPROVIDERFAILEDINIT:
         sprintf(msg,"%d:Unable to initialize a service provider. ",errcode);
         break;
#endif
      case WSASYSCALLFAILURE:
         sprintf(msg,"%d:System call failure. ",errcode);
         break;
#else
      case 1  :  sprintf(msg,"%d:Operation not permitted",errcode); break;
      case 2  :  sprintf(msg,"%d:No such file or directory",errcode); break;
      case 3  :  sprintf(msg,"%d:No such process",errcode); break;
      case 4  :  sprintf(msg,"%d:interrupted system call",errcode); break;
      case 5  :  sprintf(msg,"%d:I/O error",errcode); break;
      case 6  :  sprintf(msg,"%d:No such device or address",errcode); break;
      case 7  :  sprintf(msg,"%d:Arg list too long",errcode); break;
      case 8  :  sprintf(msg,"%d:Exec format error",errcode); break;
      case 9  :  sprintf(msg,"%d:Bad file descriptor",errcode); break;
      case 10 :  sprintf(msg,"%d:No child processes",errcode); break;
      case 11 :  sprintf(msg,"%d:Resource temporarily unavailable	",errcode); break;
      case 12 :  sprintf(msg,"%d:Not enough space",errcode); break;
      case 13 :  sprintf(msg,"%d:Permission denied",errcode); break;
      case 14 :  sprintf(msg,"%d:Bad address",errcode); break;
      case 15 :  sprintf(msg,"%d:Block device required",errcode); break;
      case 16 :  sprintf(msg,"%d:Resource busy",errcode); break;
      case 17 :  sprintf(msg,"%d:File exists",errcode); break;
      case 18 :  sprintf(msg,"%d:Improper link",errcode); break;
      case 19 :  sprintf(msg,"%d:No such device",errcode); break;
      case 20 :  sprintf(msg,"%d:Not a directory",errcode); break;
      case 21 :  sprintf(msg,"%d:Is a directory",errcode); break;
      case 22 :  sprintf(msg,"%d:Invalid argument",errcode); break;
      case 23 :  sprintf(msg,"%d:Too many open files in system",errcode); break;
      case 24 :  sprintf(msg,"%d:Too many open files",errcode); break;
      case 25 :  sprintf(msg,"%d:Inappropriate I/O control operation",errcode); break;
      case 26 :  sprintf(msg,"%d:Text file busy",errcode); break;
      case 27 :  sprintf(msg,"%d:File too large",errcode); break;
      case 28 :  sprintf(msg,"%d:No space left on device",errcode); break;
      case 29 :  sprintf(msg,"%d:Invalid seek",errcode); break;
      case 30 :  sprintf(msg,"%d:Read only file system",errcode); break;
      case 31 :  sprintf(msg,"%d:Too many links",errcode); break;
      case 32 :  sprintf(msg,"%d:Broken pipe",errcode); break;
      case 33 :  sprintf(msg,"%d:Domain error within math function",errcode); break;
      case 34 :  sprintf(msg,"%d:Result too large",errcode); break;
      case 35 :  sprintf(msg,"%d:No message of desired type",errcode); break;
      case 36 :  sprintf(msg,"%d:Identifier removed",errcode); break;
      case 37 :  sprintf(msg,"%d:Channel number out of range",errcode); break;
      case 38 :  sprintf(msg,"%d:Level 2 not synchronized",errcode); break;
      case 39 :  sprintf(msg,"%d:Level 3 halted",errcode); break;
      case 40 :  sprintf(msg,"%d:Level 3 reset",errcode); break;
      case 41 :  sprintf(msg,"%d:Link number out of range",errcode); break;
      case 42 :  sprintf(msg,"%d:Protocol driver not attached",errcode); break;
      case 43 :  sprintf(msg,"%d:No CSI structure available",errcode); break;
      case 44 :  sprintf(msg,"%d:Level 2 halted",errcode); break;
      case 45 :  sprintf(msg,"%d:Resource deadlock avoided",errcode); break;
      case 46 :  sprintf(msg,"%d:Device not ready",errcode); break;
      case 47 :  sprintf(msg,"%d:Write-protected media",errcode); break;
      case 48 :  sprintf(msg,"%d:Unformatted media",errcode); break;
      case 49 :  sprintf(msg,"%d:No locks available",errcode); break;
      case 50 :  sprintf(msg,"%d:no connectioncase case",errcode); break;
      case 52 :  sprintf(msg,"%d:no filesystemcase case",errcode); break;
      case 53 :  sprintf(msg,"%d:old, currently unused AIX errno",errcode); break; 
      case 54 :  sprintf(msg,"%d:Operation would block",errcode); break;
      case 55 :  sprintf(msg,"%d:Operation now in progress",errcode); break;
      case 56 :  sprintf(msg,"%d:Operation already in progress",errcode); break;
      case 57 :  sprintf(msg,"errno=%d:Socket operation on non-socket",errcode); break;
      case 58 :  sprintf(msg,"errno=%d:Destination address required",errcode); break;
      case 59 :  sprintf(msg,"errno=%d:Message too long",errcode); break;
      case 60 :  sprintf(msg,"errno=%d:Protocol wrong type for socket",errcode); break;
      case 61 :  sprintf(msg,"errno=%d:Protocol not available",errcode); break;
      case 62 :  sprintf(msg,"errno=%d:Protocol not supported",errcode); break;
      case 63 :  sprintf(msg,"errno=%d:Socket type not supported",errcode); break;
      case 64 :  sprintf(msg,"errno=%d:Operation not supported on socket",errcode); break;
      case 65 :  sprintf(msg,"errno=%d:Protocol family not supported",errcode); break;
      case 66 :  sprintf(msg,"errno=%d:Address family not supported by protocol family",errcode); break;
      case 67 :  sprintf(msg,"errno=%d:Address already in use",errcode); break;
      case 68 :  sprintf(msg,"errno=%d:Can't assign requested address",errcode); break;
         /* operational errors */
      case 69 :  sprintf(msg,"errno=%d:Network is down",errcode); break;
      case 70 :  sprintf(msg,"errno=%d:Network is unreachable",errcode); break;
      case 71 :  sprintf(msg,"errno=%d:Network dropped connection on reset",errcode); break;
      case 72 :  sprintf(msg,"errno=%d:Software caused connection abort",errcode); break;
      case 73 :  sprintf(msg,"errno=%d:Connection reset by peer",errcode); break;
      case 74 :  sprintf(msg,"errno=%d:No buffer space available",errcode); break;
      case 75 :  sprintf(msg,"errno=%d:Socket is already connected",errcode); break;
      case 76 :  sprintf(msg,"errno=%d:Socket is not connected",errcode); break;
      case 77 :  sprintf(msg,"errno=%d:Can't send after socket shutdown",errcode); break;
      case 78 :  sprintf(msg,"errno=%d:Connection timed out",errcode); break;
      case 79 :  sprintf(msg,"errno=%d:Connection refused",errcode); break;
      case 80 :  sprintf(msg,"errno=%d:Host is down",errcode); break;
      case 81 :  sprintf(msg,"errno=%d:No route to host",errcode); break;
      case 82	:  sprintf(msg,"%d:restart the system call",errcode); break;
      case 83	:  sprintf(msg,"%d:Too many processes",errcode); break;
      case 84	:  sprintf(msg,"%d:Too many users",errcode); break;
      case 85	:  sprintf(msg,"%d:Too many levels of symbolic links",errcode); break;
      case 86	:  sprintf(msg,"%d:File name too long",errcode); break;
      case 87	:  sprintf(msg,"%d:Directory not empty",errcode); break;
      case 88	:  sprintf(msg,"%d:Disc quota exceeded",errcode); break;
      case 89 :  sprintf(msg,"%d:Invalid file system control data ",errcode); break;
      case 93	:  sprintf(msg,"%d:Item is not local to host ",errcode); break;
      case 109 : sprintf(msg,"%d:Function not implemented  POSIX ",errcode); break;
      case 110 : sprintf(msg,"%d:media surface error ",errcode); break;
      case 111 : sprintf(msg,"%d:I/O completed, but needs relocation ",errcode); break;
      case 112 : sprintf(msg,"%d:no attribute found ",errcode); break;
      case 113 : sprintf(msg,"%d:security authentication denied ",errcode); break;
      case 114 : sprintf(msg,"%d:not a trusted program ",errcode); break; 
      case 115 : sprintf(msg,"%d:Too many references: can't splice ",errcode); break;
      case 116 : sprintf(msg,"%d:Invalid wide character ",errcode); break;
      case 117 : sprintf(msg,"%d:asynchronous i/o cancelled ",errcode); break;
      case 118 : sprintf(msg,"%d:temp out of streams resources ",errcode); break;
      case 119 : sprintf(msg,"%d:I_STR ioctl timed out ",errcode); break;
      case 120 : sprintf(msg,"%d:wrong message type at stream head ",errcode); break;
      case 121 : sprintf(msg,"%d:STREAMS protocol error ",errcode); break;
      case 122 : sprintf(msg,"%d:no message ready at stream head ",errcode); break;
      case 123 : sprintf(msg,"%d:fd is not a stream ",errcode); break;
      case 124 : sprintf(msg,"%d:POSIX threads unsupported value ",errcode); break;
      case 125 : sprintf(msg,"%d:multihop is not allowed ",errcode); break;
      case 126 : sprintf(msg,"%d:the link has been severed ",errcode); break;
      case 127 : sprintf(msg,"%d:value too large to be stored in data type ",errcode); break;
#endif
      default  : 
         sprintf(msg,"errno=%d:No error description",errcode); 
         break;
      }
      strncpy(szMsgBuf,msg,MsgBLen-1);
      szMsgBuf[MsgBLen-1]='\0';
   }
   return(errcode);
}

// IPPROTO_TCP: ��AIX�£��ڽ���socket��ʱ��Ϊ0; ��Windows�£���Ϊ6
#ifndef IPPROTO_TCP
#define IPPROTO_TCP 0
#endif

bool CTcpSocket::Create(int addressfamily,int type)
{
   Close();
   //m_socket = socket(m_nAddressFamily,type,IPPROTO_TCP);
   m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#ifdef WIN32
   if (m_socket==INVALID_SOCKET)
#else
   if (m_socket<0)
#endif
   {
      m_socket = INVALID_SOCKET;
      return(false);
   }
   // 20040417�����ñ�socketΪBLOCKģʽ
#ifdef FIONBIO   // Ϊ���ܹ���SunOS�±��룬SunOSû�ж���FIONBIO
#ifdef WIN32
   unsigned long bmode=0;
#else
   int bmode=0;
#endif
   ioctlsocket(m_socket,FIONBIO,&bmode);
#endif
#ifdef WIN32
   char on=1;
#else
   int on=1;
#endif
   setsockopt(m_socket,IPPROTO_TCP,TCP_NODELAY,&on,sizeof(on));
   return(true);
}

// 2006-3-10 15:56:29 ˵��Ҫ����һ���ܹ���������һ��IP��ֱַ�Ӱ󶨣��ƺ�Ϊ��Ҫ�ܹ���һ��ָ������������
bool CTcpSocket::Listen(short iPort,char *ip)
{
   if (m_socket==INVALID_SOCKET)
      return(false);
   sockaddr_in addr;
   memset( &addr, 0, sizeof addr);
   addr.sin_family = m_nAddressFamily;
   addr.sin_port = htons(iPort);   

   if (ip!=NULL)
   {
      unsigned int inaddr=inet_addr(ip);
      if (inaddr != INADDR_NONE)
      {
         memcpy(&(addr.sin_addr),&inaddr,sizeof(inaddr));
      }
   }

#ifndef WIN32
   int flag=1;
   //addr.sin_addr.s_addr = htonl(INADDR_ANY);
   setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
#endif
   if (bind(m_socket, (struct sockaddr*)&addr, sizeof(addr))<0)
   {
      Close();
      return(false);
   }
   if (listen(m_socket,5))
   {
      Close();
      return(false);
   }
   return(true);
}

#ifndef INADDR_NONE
#define INADDR_NONE (in_addr_t)-1
#endif
bool CTcpSocket::ConnectTcp(char *host, short port)
{
   unsigned int inaddr;  
   struct hostent *ht;
   struct sockaddr_in addr;

   Close();
   if(!Create()) return false;
   memset( &addr,0, sizeof(addr) );
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   
   inaddr = inet_addr(host);
   if (inaddr != INADDR_NONE ) 
   {
      memcpy ((char *)&addr.sin_addr,(char *)&inaddr,sizeof (inaddr));
   } 
   else
   {
      if (( ht = gethostbyname(host)) == NULL ) 
      {
         Close ();
         return false;
      }
      memcpy ((char *)&addr.sin_addr,ht->h_addr, ht->h_length);
   }
   
   int e;
   e = connect(m_socket, (struct sockaddr*)&addr, sizeof (addr));
   if (e<0) 
   {
      char emsg[256];
      e = GetLastError(emsg);
      Close ();
      return false;
   }
   m_bConnected = true;
   return true;
}



bool CTcpSocket::Accept(CTcpSocket &sock, char *remote)
{
   int tempsocket;
   struct sockaddr_in addr;
   addr.sin_family=m_nAddressFamily;
   SOCKADDRLEN addrlen = sizeof(addr);
   tempsocket = accept( m_socket, (struct sockaddr*)&addr, &addrlen);
   if(tempsocket < 0)
   {
      return false;
   }
   sock.Attach(tempsocket,m_nAddressFamily);
   if (remote!=NULL)
      strcpy(remote,inet_ntoa(addr.sin_addr));
   //sock.m_bConnected = true;
   return(true);
}

bool CTcpSocket::Attach(int socket, int addressfamily)
{
   Close();
   m_socket = socket;
   m_nAddressFamily = addressfamily;
   m_bConnected = true;
   return(true);
}

bool CTcpSocket::GetPeerName(char *peername, unsigned short &peerport)
{
   struct sockaddr_in addr;
   SOCKADDRLEN addresslen = sizeof(addr);
   if (getpeername(m_socket,(struct sockaddr *)&addr,&addresslen))
   {
      return(false);
   }

/* ****** Updated by CHENYH at 2004-2-9 17:29:41 ****** 
   if (addresslen==sizeof(struct sockaddr_in))
   {
*/
      struct sockaddr_in *psaddr = (struct sockaddr_in *) &addr;
      peerport = ntohs(psaddr->sin_port);
      strcpy(peername,inet_ntoa(psaddr->sin_addr));
/* ****** Updated by CHENYH at 2004-2-9 17:29:44 ****** 
   }
*/
   return(true);
}


// ������: CTcpSocket::Recv
// ���  : ������ 2004-2-10 21:15:05
// ����  : ͨ������·��������
// ����  : int >0:���յ������ݳ��ȣ���nDesignedSize��-1:���Է������رգ�-10:�����nDesignedSize<=0��-2:��Ϊ��·��������رգ�0:��ʱ��-3:�ڽ������ݵ�ʱ�򣬳�������ر�
// ����  : char *vptr ���������ݵĻ���
// ����  : int nDesignedSize �� ָ���������ݵĳ���
// ����  : int timeout : �ȴ��������ݵĳ�ʱʱ�䣬�����
int CTcpSocket::Recv(char *vptr, int nDesignedSize, int timeout)
{
	if(m_socket==INVALID_SOCKET) return -1;
   int result;
	int RecvLen = 0;
	int ii;

   if(nDesignedSize<=0) return -10;

   /* ****** Updated by CHENYH at 2005-5-13 16:57:26 ****** 
   ����һ�μ���Ƶ������ѭ���У��Է�ֹ�Է����͵����ݳ���
   ���㣨��������Э����󣬳�Ϊһֱ���յȴ�״̬��
   ���ⷢ���ڣ��빤���������Խӵ�ʱ�򣬶Է����ܱ�ע����ȷ�����ݳ��ȵİ�ͷ��������Ϊû����00xx��ͷ�����ֽ�
   ���ȱ�ʾ��ֱ����xx��ʼ�ĳ��ȣ�������ݰ����Ȳ��㣬��������������ǰ�û�ʼ�մ��ڵȴ�������������״̬����ˣ�
   ����ͽ����ݽ��յȴ��ļ���Ƶ�ѭ���У��Լ�ʱ��鵽�Է�����Э�顣2005-6-1 9:55:07 CYH����˵��
   result = CheckDataArrived(timeout);
   if (result<=0)
      return(result); // -1:closed,-2:error & closed, 0:timeout, 1:have data received at the socket
   *******************************************************/

	while(RecvLen<nDesignedSize)
	{

      /* ****** Updated by CHENYH at 2005-5-13 17:00:05 ****** */
      result = CheckDataArrived(timeout);
      if (result<=0)
         return(result); // -1:closed,-2:error & closed, 0:timeout, 1:have data received at the socket
      /* ***************************************************** */

      ii=(nDesignedSize-RecvLen);
      result=recv(m_socket,vptr+RecvLen,ii,0);
		
      char szmsg[512];
      if (result<0 && GetLastError(szmsg,511)==EWOULDBLOCK)
      {
         // ��Ҫ���뵽����״̬..., �Ǿ͵ȴ�����
      }
		else if(result<=0) 
		{
         // ==0 : be gracefully closed by remote
         //printf("Recv:%d errno:%d - %s\n",result,GetLastError(NULL,0),szmsg);

			Close();
			RecvLen=-3;
			break;
		}
		else
      {
			RecvLen+=result;
      }
	}
	return RecvLen;
}


// ������: CTcpSocket::Send
// ���  : ������ 2004-2-10 21:31:05
// ����  : ͨ������·��������
// ����  : int -1:��·û���������������رգ�-2:��������ʱ��������رգ�>0: ����ָ���������ݳɹ���Ӧ��==nDesignedSize
// ����  : char *ptr :��Ҫ�������ݵĻ���
// ����  : int nDesignedSize ���������ݵ�ָ������
int CTcpSocket::Send(char *ptr, int nDesignedSize)
{
	if(m_socket==INVALID_SOCKET) return -1;
	if(nDesignedSize==0) return 0;
	int nleft=nDesignedSize;
   int nwriten;
	int idx=0;
	while(nleft>0)
	{
		nwriten=send(m_socket,ptr+idx,nleft,0);
		if(nwriten <= 0) 
		{
			Close();
			return -2;
		}
		nleft-=nwriten;
		idx+=nwriten;
	}
	return (nDesignedSize - nleft);
}

bool CTcpSocket::IsFree()
{
   return (m_socket==INVALID_SOCKET);
}


// ������: CTcpSocket::CheckDataArrived
// ���  : ������ 2004-2-10 21:40:02
// ����  : �����һ��ʱ���ڸ��������Ƿ������ݱ����յ�
// ����  : int -1:�˿ڴ��ڱ��ر�״̬��-2:�ڵȴ��������ݵ�ʱ�����0:��ָ����ʱ���û�����ݿɱ����գ�1:�����ݿɱ�����
// ����  : int timeout ���ȴ�ʱ�䣬�����
int CTcpSocket::CheckDataArrived(int timeout)
{
   int result=0;
   if (m_socket==INVALID_SOCKET) 
      return(-1);
   if (timeout>=0)
//   if (timeout>0)
   {
		fd_set rset;
		struct timeval tv;
		FD_ZERO(&rset);
		FD_SET(m_socket, &rset);
		tv.tv_sec = timeout/1000;
		tv.tv_usec = (timeout%1000)*1000;
		result=(select(m_socket+1, &rset, NULL, NULL, &tv));
      if (result<0)
      {
         Close();
         return(-2);
      }
      if (result==0)
      {
         // timeout:
         return(0);
      }
   }
   return(1);
}

bool CTcpSocket::IsConnected()
{
   return(m_bConnected);
}
