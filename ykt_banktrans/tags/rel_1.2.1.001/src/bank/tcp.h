#ifndef __TCP_INIT_H_
#define __TCP_INIT_H_

#ifdef WIN32
//#include <winsock.h>
#include <winsock2.h>
#else
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifndef AF_INET
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_IPX          6               /* IPX and SPX */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO          /* OSI is ISO */
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* AppleTalk */
#define AF_NETBIOS      17              /* NetBios-style addresses */
#define AF_VOICEVIEW    18              /* VoiceView */
#define AF_FIREFOX      19              /* FireFox */
#define AF_UNKNOWN1     20              /* Somebody is using this! */
#define AF_BAN          21              /* Banyan */

#define AF_MAX          22

#endif

#ifndef PF_INET
   #define PF_UNSPEC       AF_UNSPEC
   #define PF_UNIX         AF_UNIX
   #define PF_INET         AF_INET
   #define PF_IMPLINK      AF_IMPLINK
   #define PF_PUP          AF_PUP
   #define PF_CHAOS        AF_CHAOS
   #define PF_NS           AF_NS
   #define PF_IPX          AF_IPX
   #define PF_ISO          AF_ISO
   #define PF_OSI          AF_OSI
   #define PF_ECMA         AF_ECMA
   #define PF_DATAKIT      AF_DATAKIT
   #define PF_CCITT        AF_CCITT
   #define PF_SNA          AF_SNA
   #define PF_DECnet       AF_DECnet
   #define PF_DLI          AF_DLI
   #define PF_LAT          AF_LAT
   #define PF_HYLINK       AF_HYLINK
   #define PF_APPLETALK    AF_APPLETALK
   #define PF_VOICEVIEW    AF_VOICEVIEW
   #define PF_FIREFOX      AF_FIREFOX
   #define PF_UNKNOWN1     AF_UNKNOWN1
   #define PF_BAN          AF_BAN

   #define PF_MAX          AF_MAX
#endif

#ifndef SOCK_STREAM
/*
 * Types
 */
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */

#endif

//�ڷ�Windowsϵͳ������ʹ��close���ر�һ��socket������Windows�£�����ʹ��closesocket
//�������ͳһ��closesocket
#ifndef WIN32
#define closesocket close
#endif
/* ****** Updated by CHENYH at 2004-3-3 11:23:59 ****** 
#ifdef UNIX
#define closesocket close
#endif

#ifdef VOS
#define closesocket net_close
#endif
*/

//�ڷ�Windowsϵͳ������ʹ��ioctl������һ��socket������Windows�£�����ʹ��ioctlsocket
//�������ͳһ��ioctlsocket
#ifndef WIN32
#define ioctlsocket ioctl
#endif


/* ****** Updated by CHENYH at 2004-4-19 11:40:07 ****** 
#ifdef VOS
#define ioctlsocket net_ioctl
#endif
*/

//��Windows�£����е�socket�Ĵ����ȫ����WSA��ʼ�����ǽ���Ҫ����Щͳһ��Unix�ı�׼
#ifdef WIN32
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif

//��VOS�£����е�socket�Ĵ����ȫ����e$��ʼ�����ǽ���Ҫ����Щͳһ��Unix�ı�׼

#ifdef VOS
#define EINTR e$tcp_interrupted_operation
#define EWOULDBLOCK e$caller_must_wait
#endif


//��Windows�£�ʹ��h_error����ȡ�����socket���󣬶�������ϵͳ�£�ֱ��ʹ��errno��
//����ͬ���GET_LAST_SOCK_ERROR()
#ifdef WIN32
#define GET_LAST_SOCK_ERROR() h_errno
#else
#define GET_LAST_SOCK_ERROR() errno
#endif


/* ****** Updated by CHENYH at 2004-4-14 10:31:52 ****** 
#ifdef WIN32
#define SOCKADDRLEN int
#else
#define SOCKADDRLEN socklen_t
#endif
*/
//�ڴ���sockaddrʱ��ʹ�õı�ʾ���ȵ����Ͳ�ͬ gyd 20020605 �� UNIX��ΪLINUX
#if defined(LINUX) || defined(SUNOS) || defined(AIX)
#define SOCKADDRLEN	socklen_t
#endif
#ifndef SOCKADDRLEN
#define SOCKADDRLEN int
#endif
/* ****** Updated by CHENYH at 2004-6-10 19:24:00 ****** 
#ifdef HP_UX
#define SOCKADDRLEN	int
#endif
#ifdef WIN32
#define SOCKADDRLEN	int
#endif
*/

#ifndef INVALID_SOCKET
#define	INVALID_SOCKET	(-1)
#endif

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif

class BUPUB_API CTcpSocket  
{
private:
#ifdef WIN32
   SOCKET m_socket;
#else
   int m_socket;
#endif
	int m_nAddressFamily;
   bool m_bConnected;   // 2005-11-7 12:29:20 CHENYH Ϊ�˱�ע���˿��Ƿ����ӳɹ�

public:
	bool IsConnected();
   // ������: CTcpSocket::CheckDataArrived
   // ���  : ������ 2004-2-10 21:40:02
   // ����  : �����һ��ʱ���ڸ��������Ƿ������ݱ����յ�
   // ����  : int -1:�˿ڴ��ڱ��ر�״̬��-2:�ڵȴ��������ݵ�ʱ�����0:��ָ����ʱ���û�����ݿɱ����գ�1:�����ݿɱ�����
   // ����  : int timeout ���ȴ�ʱ�䣬�����
	int CheckDataArrived(int timeout);
   
	bool IsFree();

   // ������: CTcpSocket::Send
   // ���  : ������ 2004-2-10 21:31:05
   // ����  : ͨ������·��������
   // ����  : int -1:��·û���������������رգ�-2:��������ʱ��������رգ�>=0: ����ָ���������ݳɹ���Ӧ��==nDesignedSize
   // ����  : char *ptr :��Ҫ�������ݵĻ���
   // ����  : int nDesignedSize ���������ݵ�ָ������
   int Send(char *ptr, int nDesignedSize); // ͨ������·�������� ����  : int -1:��·û���������������رգ�-2:��������ʱ��������رգ�>=0: ����ָ���������ݳɹ���Ӧ��==nDesignedSize

   // ������: CTcpSocket::Recv
   // ���  : ������ 2004-2-10 21:15:05
   // ����  : ͨ������·��������
   // ����  : int >0:���յ������ݳ��ȣ���nDesignedSize��-1:���Է������رգ�-10:�����nDesignedSize<=0��-2:��Ϊ��·��������رգ�0:��ʱ��-3:�ڽ������ݵ�ʱ�򣬳�������ر�
   // ����  : char *vptr ���������ݵĻ���
   // ����  : int nDesignedSize �� ָ���������ݵĳ���
   // ����  : int timeout : �ȴ��������ݵĳ�ʱʱ�䣬�����
	int Recv(char *vptr, int nDesignedSize, int init_timeout=0);  // ͨ������·�������� ����  : int -1:���Է������رգ�-10:�����nDesignedSize<=0��-2:��Ϊ��·��������رգ�0:��ʱ��-3:�ڽ������ݵ�ʱ�򣬳�������ر�
	bool GetPeerName(char *peername,unsigned short &peerport);
	bool Attach(int socket,int addressfamily);
	bool Accept(CTcpSocket &sock, char *remote=NULL);
	bool ConnectTcp(char* host, short port);
/* ****** Updated by CHENYH at 2006-3-10 15:50:33 ****** 
	bool Listen(short iPort);
*******************************************************/
	bool Listen(short iPort,char *ip=NULL);
	bool Create(int addressfamily=AF_INET,int type=SOCK_STREAM);
	int GetLastError(char *szMsgBuf,int MsgBLen=256);
	void Close();
	CTcpSocket();
	CTcpSocket(CTcpSocket &ts);
	virtual ~CTcpSocket();

};

#undef BUPUB_API

#endif
