// DRTPRouter.h: interface for the CDrtpRouter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRTPROUTER_H__D446F7AD_BB7F_4907_BE94_9A07D3FF9B26__INCLUDED_)
#define AFX_DRTPROUTER_H__D446F7AD_BB7F_4907_BE94_9A07D3FF9B26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mutex.h"

#ifdef DRTP_V3
typedef HANDLE CLI_HANDLE;
#elif defined DRTP_V3X
#include "tcp.h"
typedef CTcpSocket CLI_HANDLE;
#define MAXROUTERCOUNT  6  /*路由级数*/
/* 以下代码是用来字节对齐使用的 */
#ifdef WIN32
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
//#pragma pack(push,1)
#else
#ifdef HP_UX
#define __PACKED__
#pragma pack 1
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif
#endif

/*潘卫东 更改日期:2000.6.12 */
typedef struct _SYS_HEAD   /*网络数据包头 Ver=2 */
{
	unsigned char     Ver;	/*网络数据包版本号,从1开始,4.0版本号为1*/
	/*5.0系统版本号为2 */ 
	unsigned char     MessageType;   	/*消息类型，区分系统和应用消息 */
	/*应用功能注册	1 */
	/*应用功能注销 	2 */
	/*查询网关状态 	3 */
	/*查询网关日志	4 */
	/*用户请求连接目的网关 	5 */
	/*用户连接目的网关结果 	6 */
	/*申请会话密钥 7	 发送Public Key */
	/*返回会话密钥 8	Session Key 经Public Key加密后的密文 */
	/*更改会话密钥 9 新的会话密钥的加密用上次会话密钥 */
	/*10 */
	/*11 */
	unsigned char     CompressFlag;	/*压缩标记，数据内容USER_BLOCK */
	/*0-  数据没有压缩 */
	/*1-  数据压缩	   */
	unsigned char     RouterIndex;	/*数据包经过路由的序号，发送的数据包每经过一个*/
	/*路由就加一，返回的数据包每经过一个路由就减一。*/
	/*路由最多经过6级，超过作为费包处理 */
	unsigned char	   RouterDesignate;/*路由指定标记 */
	/*0是不指定，按功能号搜索 */
	/*1指定功能，按上次搜索路径到达目的地 */
	unsigned char	   FunctionPriority;/*功能号优先级,0为缺省，非0为用户自定义 */
	/*1为优先级高于标准 */
	/*2为标准优先级		*/
	/*3为优先级低于标准	*/
	unsigned short 	Function; 	    /*主功能号，应用向路由只注册主功能号 */
	/*子功能号由应用负责管理	*/
	/*如交易类为1，实时查询为2，查询历史为3 */
	/*	unsigned short    SourceNo; */
	unsigned short    DestNo;/*目的网关编号（营业部代码） */
	unsigned short    UserDataSize;   /*数据报头接着的应用数据USER_BLOCK长度 */
	unsigned short    UserDataRealSize;/*应用数据的真实长度，数据加解密或压缩前的长度 */
	unsigned short 	RouterIn[MAXROUTERCOUNT];	/*路由信息表入路径 */
	unsigned short    RouterOut[MAXROUTERCOUNT];  /*路由信息表出路径 */
	int	 			   LastConnectTime;/*时间标记,有效数据包的时间应该比CONNECT的时间大 */
	/*客户CONNECT时更新,单位为*/
	unsigned int      CRC;           /*数据包头SYS_HEAD的32位crc值 */
} __PACKED__ SYS_HEAD;

#ifdef WIN32
#pragma pack(pop)
#else
#ifdef __GNUC__
#else
#ifdef HP_UX
#pragma pack 0
#else
#pragma options align=reset
#endif
#endif
#endif
#undef __PACKED__

#else
typedef int CLI_HANDLE;
#endif

#define MAXIPLENGTH 64

class CDrtpClient  
{
public:
   time_t m_lasttime;   // 上次通过本连接进行有效的收发数据的时间点，time(NULL)
   CMUTEX m_mutex;
   CLI_HANDLE m_handle;
#ifdef DRTP_V3X
	int sendpack(SYS_HEAD *pHead,void *senddata,int senddatalen);
#endif
   
public:
	bool Broad(int destno, int funcno, char *sbuf, int sblen, char *errmsg);
	int Receive(char *rbuf, int rbsize,char *errmsg,int waittime);
	void Close();
	bool Send(int destno,int funcno,char *sbuf, int sblen, char *errmsg);
	bool Connect(char *ip, int port, char *errmsg);
	bool IsOpenning();
	CDrtpClient();
	virtual ~CDrtpClient();

};

typedef std::list<CDrtpClient *> CLILIST;

class CDrtpRouter  
{
public:
   char m_IP[MAXIPLENGTH];
   int  m_port;

private:
   CLILIST m_CliList;

public:
	int Broad(int branchno, int funcno, char *sbuf, int sblen, char *errmsg);
	int CLISendReceive(int branchno, int funcno,int timeout, char *sbuf, int sblen, char *rbuf, int rbsize, char *errmsg);
	CDrtpRouter();
	virtual ~CDrtpRouter();

};


#endif // !defined(AFX_DRTPROUTER_H__D446F7AD_BB7F_4907_BE94_9A07D3FF9B26__INCLUDED_)
