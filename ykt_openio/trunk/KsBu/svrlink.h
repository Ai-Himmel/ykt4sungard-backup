// SvrLink.h: interface for the CSvrLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_)
#define AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_

#include "tcp.h"
#include "cxpack.h"
#include "bupub.h"
#include "comstru.h"

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#pragma message("dllimport")
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define END_FIELD -1

typedef struct
{
   int sno;  // 首次调用ExtCall保留的souceno
   int dno;  // 首次调用ExtCall保留的destno
   int fno;  // 首次调用ExtCall保留的funcno
   int bno;  // 首次调用ExtCall保留的batchno
   ST_PACKHEAD ahead;  // 应答返回的头数据保留用
} ST_PDKEEP;

#ifndef NOIPCS
#include "MsgQueue.h"
extern CMQFactory g_MQFactory;
#endif

class BUPUB_API CSvrLink  
{
public:
   int  bccBFuncNo;        // 连接的BCC注册的通讯功能号
   int  bccID;             // 连接的BCC编号>0
   int iThisProcID;        // 本BULink的编号
   
   bool bExit;             // 是否要退出...
   ST_PACKHEAD head;       // 当前使用的CPACK的头包括parmbit等
   ST_PDKEEP xcdata;       // 用于保留ExtCall和ExtCallNext的数据用

   unsigned int m_lastrcvtick;   // 上次从BCC收到消息时间点，请用tc2_tc1()进行判断
private:
#ifdef NOIPCS           // 为了bupub和外部数据之间的数据对齐，防止内外模块对NOIPCS的定义不同导致数据对齐不同，2008-8-20 9:44:56
   void *m_pMsgQueue;  // 2007-11-22 10:08:10 使用IPC消息交换数据
#else
   CMsgQueue *m_pMsgQueue;  // 2007-11-22 10:08:10 使用IPC消息交换数据
#endif
   
   unsigned char iGRFrame;     // 帧号
   unsigned int iLastReqType;  // 上次或本次调用的功能号
   int iLastRetCode;  // 上次处理结果的成功或失败，用于通知BCC
   ST_PACKHEAD reqhead;    // 请求包的头保留，以便在业务功能中检查字段等属性
   char eMsg[256];
   CTcpSocket linksock;    // 与调度中心的TCPIP连接
   short svr_hs1;          // 调度中心（short）1，用于判断是否与本业务单元主机的字序相同
   char buf[MAXMSG+sizeof(MSGHEAD)+50];     // 包括起始的消息头
   char iAnswerMode;       // 当前有效的应答模式，见AM_AUTO / AM_CONFIRM
   TRUSERID ruserid;       // 本请求提交的客户端ID
   
public:

   // 函数名: CheckBCCMsg
   // 编程  : 陈永华 2008-10-20 10:22:30
   // 描述  : 当采用正常BU处理的时候，千万别调用这个，这只有当采用异常的流程的时候，方要特殊调用这个，以处理BCC给BU的指令
   // 返回  : MSGBUF * : 返回NULL，表示当前没有BCC给的消息；否则返回MSGBUF *的指针，编程者要自行处理这些消息
   // 参数  : int timeout=0 : 毫秒计，表示要等待多少时间，0则表示检查一下，有则返回MSGBUF *，没有则也马上返回NULL
	MSGBUF * CheckBCCMsg(int timeout=0);

   // 函数名: SetCol
   // 编程  : 陈永华 2005-9-27 11:50:57
   // 描述  : 设置此后应答包中的有效字段
   // 返回  : int 返回被设置的有效字段个数
   // 参数  : TRUSERID *handle[IN]: 仅仅为了兼容，实际无效
   // 参数  : ...[IN]: 被设置的有效字段位图(编号)清单，以END_FIELD结束
	int SetCol(TRUSERID *handle,...);

   // 函数名: BCCMsgLogOut
   // 编程  : 陈永华 2005-9-27 19:31:25
   // 描述  : 由BCC集中输出本BU的文本日志信息
   // 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
   // 参数  : int logid[IN]：本日志的ID号
   // 参数  : char *pFormat[IN]：文本日志的格式定义
   // 参数  : ... [IN]：以pFormat定义的参数列表
	int BCCMsgLogOut(int logid, char *pFormat, ...);

   // 函数名: Error_Deal
   // 编程  : 陈永华 2005-9-27 11:45:17
   // 描述  : 将错误信息填写到vsmess，并一次性的返回给请求方
   // 返回  : int 0:成功；否则即为与BCC通讯出现问题，建议业务取消处理
   // 参数  : int retcode[IN]：返回码
   // 参数  : char *omsg [OUT]：最后输出到vsmess字段的信息串
   // 参数  : char *pFormat [IN]：错误信息的参数格式串，参考sprintf说明
   // 参数  : ... [IN]: pFormat格式定义的参数列表
	int Error_Deal(int retcode, char *omess, char *pFormat,...);

   // 函数名: GetRequestHead
   // 编程  : 陈永华 2005-9-27 11:43:11
   // 描述  : 将原始的请求包头复制到phead
   // 返回  : void 
   // 参数  : ST_PACKHEAD *phead[OUT]: 存放复制的包头
	void GetRequestHead(ST_PACKHEAD *phead);

   // 函数名: GetAnswerHead
   // 编程  : 陈永华 2005-9-27 11:42:29
   // 描述  : 将当前应答包头复制到phead
   // 返回  : void 
   // 参数  : ST_PACKHEAD *phead[OUT]: 存放复制的包头
	void GetAnswerHead(ST_PACKHEAD *phead);

   // 函数名: RATransfer
   // 编程  : 陈永华 2005-9-16 0:49:26
   // 描述  : 通过RA分析器得到目标点进行请求服务的转发
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : ST_CPACK *rpack[IN]: 请求包，当为NULL表示将提交给本BU的原始请求转发
   // 参数  : ST_PACK *pArrays=NULL[IN]: 请求包的后续记录
	int RATransfer(ST_CPACK *rpack=NULL, ST_PACK *pArrays=NULL);

   // 函数名: ExtTransfer
   // 编程  : 陈永华 2005-9-16 0:47:34
   // 描述  : 向目标应用服务器转发请求
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : int destno[IN]: 目标应用服务器连接的通讯平台节点号(BRANCH/YYBDM)
   // 参数  : int funcno[IN]: 目标应用服务器注册的通讯功能号
   // 参数  : ST_CPACK *rpack[IN]: 请求包，当为NULL表示将提交给本BU的原始请求转发
   // 参数  : ST_PACK *pArrays=NULL[IN]: 请求包的后续记录
	int ExtTransfer(unsigned short destno, unsigned short funcno, ST_CPACK *rpack=NULL, ST_PACK *pArrays=NULL);

   // 函数名: IntTransfer
   // 编程  : 陈永华 2005-9-15 23:56:24
   // 描述  : 将请求包转发给BCC下指定的BU组
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : char *szBUGroupID[IN]: 指定的BU组名称
   // 参数  : ST_CPACK *rpack[IN]: 请求包，当为NULL表示将提交给本BU的原始请求转发
   // 参数  : ST_PACK *pArrays=NULL[IN]: 请求包的后续记录
	int IntTransfer(char *szBUGroupID, ST_CPACK *rpack=NULL,ST_PACK *pArrays=NULL);

   // 函数名: RACallNext
   // 编程  : 陈永华 2005-9-16 0:12:39
   // 描述  : 向上次RACall的目标点取后续数据包，当上次收到的应答包的apack->head.nextflag==1
   // 返回  : int >=0: 表示成功收到应答包; 
   //             <0: 失败：
   //             -2: 等待应答数据超时，即自从向外发送了请求后，在waittime+1秒内没有接收到应答数据  
   //             -1: 其他各种通讯方面的错误
   // 参数  : int waittime[IN]: 应答数据等待超时时间，（秒）
   // 参数  : ST_CPACK *apack[OUT]: 应答包
   // 参数  : ST_PACK *pArrays[OUT]: 应答后续数据记录
	int RACallNext(int acktime, ST_CPACK *apack, ST_PACK *pArrays);

   // 函数名: RACall
   // 编程  : 陈永华 2005-9-16 0:11:29
   // 描述  : 通过RA分析器得到目标点进行内调或外调功能服务
   // 返回  : int >=0: 表示成功收到应答包; 
   //             <0: 失败：
   //             -2: 等待应答数据超时，即自从向外发送了请求后，在waittime+1秒内没有接收到应答数据  
   //             -1: 其他各种通讯方面的错误
   // 参数  : int acktime[IN]: 应答数据等待超时时间，（秒）
   // 参数  : ST_CPACK *rpack[IN]: 请求包
   // 参数  : ST_CPACK *apack[OUT]: 应答包
   // 参数  : ST_PACK *pArrays[OUT]: 应答后续数据记录
	int RACall(int acktime, ST_CPACK *rpack, ST_CPACK *apack, ST_PACK *pArrays);

   // 函数名: IntCallNext
   // 编程  : 陈永华 2005-9-16 0:09:25
   // 描述  : 向上次IntCall指定的BU组取后续数据包，当上次收到的应答包的apack->head.nextflag==1
   // 返回  : int ==0: 表示成功收到应答包; 
   //             <0: 失败：
   //             -2: 等待应答数据超时，即自从向外发送了请求后，在waittime+1秒内没有接收到应答数据  
   //             -1: 其他各种通讯方面的错误
   // 参数  : int waittime[IN]: 应答数据等待超时时间，（秒）
   // 参数  : ST_CPACK *apack[OUT]: 应答包
   // 参数  : ST_PACK *pArrays[OUT]: 应答后续数据记录
	int IntCallNext(int waittime, ST_CPACK *apack, ST_PACK *pArrays);

   // 函数名: IntCall
   // 编程  : 陈永华 2005-9-16 0:02:34
   // 描述  : 向另外一个指定BU组调用功能
   // 返回  : int ==0: 表示成功收到应答包; 
   //             <0: 失败：
   //             -2: 等待应答数据超时，即自从向外发送了请求后，在waittime+1秒内没有接收到应答数据  
   //             -1: 其他各种通讯方面的错误
   // 参数  : char *szBUGroupID[IN]: 指定的BU组名称
   // 参数  : int waittime[IN]: 应答数据等待超时时间，（秒）
   // 参数  : ST_CPACK *rpack[IN]: 请求包
   // 参数  : ST_CPACK *apack[OUT]: 应答包
   // 参数  : ST_PACK *pArrays[OUT]: 应答后续数据记录
	int IntCall(char *szBUGroupID, int waittime, ST_CPACK *rpack, ST_CPACK *apack, ST_PACK *pArrays);

   // 函数名: UpdateRegFunction
   // 编程  : 陈永华 2005-9-15 23:59:26
   // 描述  : 向BCC注册或变更本BU组提供的服务功能号
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : unsigned int reqtype[IN]: 功能号，即ST_PACKHEAD::RequestType
   // 参数  : char *rtname[IN]: 本功能的简单描述
   // 参数  : char *programmer[IN]: 本功能开发人员说明
   // 参数  : int priority=1[IN]: 本功能的优先级别[1,2,3]
   // 参数  : bool bstop=false[IN]: 本功能是否暂停服务
	int UpdateRegFunction(unsigned int reqtype,char *rtname,char *programmer,int priority=1,bool bstop=false);


   /* ****** Comment by CHENYH at 2005-7-6 20:45:17 ****** 
   以下为共享内存块操作函数：
   这部分的共享内存块实际上通过SMOpenBlock创建在与BU相连的BCC上
   的内存块，通过内存数据的交换达到一个BCC下各个BU能够访问和修改
   这些内存中的数据。达到数据共享的目的。
   在BCC上启动时候，实际上创建了100个可命名和定义长度的共享内存资源，
   为了控制其协调工作，这些共享内存资源中都包括了一个加锁器，以对数据
   进行独占式访问。
   对于一个BCC下挂接的所有BU，根据设计可以共同使用这100个资源，
   当然也就需要预先定义其使用方式和数据结构。
   这里的函数作为与业务无直接关系的架构部分，并不提出具体的定义，
   需要各类系统在建设具体的BU的时候作出相应的设计。
   *******************************************************/
   // 函数名: CSvrLink::SMInterlockedAdd
   // 编程  : 陈永华 2005-7-6 11:08:58
   // 描述  : 在共享内存块中指定的位置作为整数进行独占加法运算
   // 返回  : int 返回独占加法运算后的值。
   //          为0x80000000，可能属于系统或参数错误；
   //          为0x80000001，则可能属于参数错误；
   //          但不建议用这个作为判断
   // 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
   // 参数  : unsigned int offset：[IN] 数据的偏移位置
   // 参数  : int increment：[IN] 增量参数
	int SMInterlockedAdd(int smh,unsigned int offset,int increment=1);

   // 函数名: CSvrLink::SMRead
   // 编程  : 陈永华 2005-7-6 10:21:43
   // 描述  : 从指定共享内存空间中读取局部或全部的数据
   // 返回  : int -2/-1000:共享内存句柄错误； 
   //             -1:内存空间没有分配； 
   //              0:读取位置offset超过已经分配的空间  
   //             >0:读取数据长度（如果该值<指定的值，即即为结束）
   //             -20: 等待超时，BCC没有能够在1秒之内响应
   //             <-100: 属于各类错误：
   //             -101:被对方正常关闭；
   //             -110/-111:对方非标准MSG协议口或数据不同步；
   //             -102:因为链路错误而被关闭；
   //             -103:在接收数据的时候，出错而被关闭
   //             -1001: 长度过长，每次的长度length<=8180
   // 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
   // 参数  : void *rbuf：[OUT] 读取数据缓存
   // 参数  : unsigned int offset：[IN] 读取数据存放在共享内存块的偏移位置
   // 参数  : unsigned int rblen：[IN] 读取数据块长度，注意<8180
   // 参数  : bool bRLock: [IN] 是否需要加锁读
   int SMRead(int smh, void *rbuf, unsigned int offset,unsigned int rblen,bool bRLock=false);

   // 函数名: CSvrLink::SMWrite
   // 编程  : 陈永华 2005-7-4 20:13:07
   // 描述  : 写局部或全部数据到指定的共享内存块
   // 返回  : int -2/-1000:共享内存句柄错误； 
   //             -1:内存空间没有分配； 
   //              0:写入位置offset超过已经分配的空间  
   //             >0:写入数据长度（如果该值<指定的值，即即为结束）
   //             -20: 等待超时，BCC没有能够在1秒之内响应
   //             <-100: 属于各类错误：
   //             -101:被对方正常关闭；
   //             -110/-111:对方非标准MSG协议口或数据不同步；
   //             -102:因为链路错误而被关闭；
   //             -103:在接收数据的时候，出错而被关闭
   //             -1001: 长度过长，每次的长度length<=8180
   // 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
   // 参数  : void *wdata：[IN] 写覆盖的数据块
   // 参数  : unsigned int offset：[IN] 数据存放在共享内存块的偏移位置
   // 参数  : unsigned int length：[IN] 数据块长度，注意<8180
   // 参数  : bool bWLock: [IN] 是否需要加锁写
	int SMWrite(int smh,void *wdata,unsigned int offset,unsigned int length,bool bWLock=true);

   // 函数名: CSvrLink::SMOpenBlock
   // 编程  : 陈永华 2005-7-4 15:52:14
   // 描述  : 创建或打开一个命名共享内存块
   // 返回  : int 
   //          >=0: 成功，返回该共享内存的句柄号；
   //          -1: 共享内存块（句柄）已经用完了
   //          -2: 已经需要的共享内存块长度已经超过了BCC限定了
   //          -3: 要求的长度超过已经分配的共享内存长度
   //          -20: 等待超时，BCC没有能够在1秒之内响应
   //          <100: 属于各类错误，-101:被对方正常关闭；-110/-111:对方非标准MSG协议口或数据不同步；-102:因为链路错误而被关闭；-103:在接收数据的时候，出错而被关闭
   // 参数  : char *name : 共享内存块命名
   // 参数  : unsigned int length: 共享内存块的长度
	int SMOpenBlock(char *name,unsigned int length);
   /*******************************************************/

   /* ****** Commented by CHENYH at 2005-7-6 20:34:21 ******/
   /* 下面三个函数是为了事务上考虑作的对共享内存块加锁和解锁方法
      由于这些函数是为事务处理上使用，常常并非需要共享内存的空间
      因此，这三个函数中的共享资源句柄可以不用SMOpenBlock来提供，
      在BCC上实际上启动的时候就创建了无空间和命名的资源，
      其句柄为0－99，当使用SMOpenBlock的时候是从0号开始使用的，
      句柄是递增的。所以，如果仅仅为了事务，建议直接从99号开始
      作为事务控制句柄，当然，因为没有使用SMOpenBlock也就没有具体的
      共享内存空间和命名。
   *******************************************************/
   // 函数名: CSvrLink::SMUnlock
   // 编程  : 陈永华 2005-7-6 20:28:47
   // 描述  : 对本BU加锁的共享内存块解锁
   // 返回  : int -2/-1000:共享内存句柄错误； 
   //             1: 解锁成功
   //             <-100: 属于各类错误：
   //                -101:被对方正常关闭；
   //                -110/-111:对方非标准MSG协议口或数据不同步；
   //                -102:因为链路错误而被关闭；
   //                -103:在接收数据的时候，出错而被关闭
   //                -1001: 长度过长，每次的长度length<=8180
   // 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
   //          注：由于目前为了整个系统稳定考虑，目前一个BU同时只能对一个
   //             共享内存块进行加锁，如果对一个试图加锁的时候，
   //             另外已经被加锁的会立即被释放
	int SMUnlock(int smh);

   // 函数名: CSvrLink::SMTryLock
   // 编程  : 陈永华 2005-7-6 20:25:17
   // 描述  : 试着对指定的内存块进行加锁，不阻塞，立即返回
   // 返回  : int -2/-1000:共享内存句柄错误； 
   //             0: 不能立即加锁，该资源被其他BU加锁着
   //             1: 加锁成功
   //             <-100: 属于各类错误：
   //                -101:被对方正常关闭；
   //                -110/-111:对方非标准MSG协议口或数据不同步；
   //                -102:因为链路错误而被关闭；
   //                -103:在接收数据的时候，出错而被关闭
   //                -1001: 长度过长，每次的长度length<=8180
   // 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
	int SMTryLock(int smh);

   // 函数名: CSvrLink::SMLock
   // 编程  : 陈永华 2005-7-6 16:07:57
   // 描述  : 对指定的共享内存块进行本BU占用加锁，阻塞模式，直到成功或失败
   // 返回  : int -2/-1000:共享内存句柄错误； 
   //             1: 加锁成功
   //             <-100: 属于各类错误：
   //                -101:被对方正常关闭；
   //                -110/-111:对方非标准MSG协议口或数据不同步；
   //                -102:因为链路错误而被关闭；
   //                -103:在接收数据的时候，出错而被关闭
   //                -1001: 长度过长，每次的长度length<=8180
   // 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
	int SMLock(int smh);
   /*******************************************************/

   // 函数名: SetCol
   // 编程  : 陈永华 2005-7-6 22:28:13
   // 描述  : 用于设置后续记录数据中的数据列（字段）为有效字段
   //         由于本函数并非直接被应用服务功能调用，因此，采用了
   //         整个位图方式进行，而不是用逐个字段设置。
   //         本函数隐含了两种方法：
   //         1. 在位图列表parmbits[32]中的所有位都为0的情况下，为清空所有位图；
   //         2. 在位图列表中有位为1的，则是增加有效位图。
   // 注意：在具体功能调用的时候，内部所有位图实际是空的，如果本类应用XPACK模式下，即可直接发送ST_SDPACK记录；
   //       如果需要发送ST_PACK记录，那么必须设置有效位图。
   // 返回  : int 有效位图个数，即本次调用的数据列个数
   // 参数  : TRUSERID * puserid: Reserve
   // 参数  : unsigned char *parmbits: 本次设置有效位图列表
	int SetCol(TRUSERID * puserid, unsigned char *parmbits);

   // 函数名: PutRow
   // 编程  : 陈永华 2005-9-16 0:28:11
   // 描述  : 向请求方提交应答数据记录
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : TRUSERID * handle[IN]: 请求方的句柄
   // 参数  : ST_PACK *pdata[IN]: 应答数据记录
   // 参数  : int retcode[IN]: 本次组包的返回码
   // 参数  : char *rtnMsg[IN]: 仅仅为了兼容，实际没有效果
	int PutRow(TRUSERID * handle,ST_PACK *pdata,int retcode,char *rtnMsg);
	int Err_Deal(char *emsg, int retcode);

	int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg);
	int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg,unsigned char nextflag);


   // 函数名: SetMaxRow
   // 编程  : 陈永华 2005-9-16 0:35:42
   // 描述  : 设置最大组包记录数 [1,100]
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : int maxrows[IN]: 最大组包记录数 [1,100]
	int SetMaxRow(int maxrows);

	int SetAnswerMode(char iAnswerMode);
	bool CheckProcCancel();

   // 以下功能能够支持通用架构下(只有用cpack.dat，而无明确的ST_PACK结构的情况下使用)
   // Added by CHENYH on 2006-3-5 23:28:26  因为在通用工具中或架构部件下，不能明确定义ST_PACK的结构
	int ExtCallNext(int acktime, char *abuf, int &alen);
	int ExtCall(int sourceno, int destno, int funcno, int batchno, int acktime, void *rdata, int rdlen, char *abuf, int &alen);
   int PushData(int sourceno, int destno, int funcno, int batchno, char pushmode, int acktime, void  *pdata, int pdlen);
	int PushDataEx(TPUSHDEST *pushdests, int pdcount, void *pdata, int pdlen, char pushmode, int acktime);
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //////////////////////////////////////////////////////////////////////////
   // 而以下函数则只能被明确了cpack.dat和ST_PACK的特定项目下使用的
   // ----------------------------------------------------------------------
   // 函数名: ExtCallNext
   // 编程  : 陈永华 2005-9-16 0:18:38
   // 描述  : 向上次ExtCall的目标点取后续数据包，当上次收到的应答包的apack->head.nextflag==1
   // 返回  : int >=0: 表示成功收到应答包; 
   //             <0: 失败：
   //             -2: 等待应答数据超时，即自从向外发送了请求后，在waittime+1秒内没有接收到应答数据  
   //             -1: 其他各种通讯方面的错误
   // 参数  : int acktime[IN]: 应答数据等待超时时间，（秒）
   // 参数  : ST_CPACK *apack[OUT]: 应答包
   // 参数  : ST_PACK *pArrays[OUT]: 应答后续数据记录
	int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays);

   // 函数名: ExtCall
   // 编程  : 陈永华 2005-9-16 0:14:20
   // 描述  : 向指定的应用服务器调用请求服务
   // 返回  : int >=0: 表示成功收到应答包; 
   //             <0: 失败：
   //             -2: 等待应答数据超时，即自从向外发送了请求后，在waittime+1秒内没有接收到应答数据  
   //             -1: 其他各种通讯方面的错误
   // 参数  : int sourceno[IN]: 通过哪个通讯平台（编号）发送外调功能请求
   // 参数  : int destno[IN]: 目标应用服务器连接的通讯平台节点号(BRANCH/YYBDM)
   // 参数  : int funcno[IN]: 目标应用服务器注册的通讯功能号
   // 参数  : int batchno[IN]: 该目标点的接收批次号
   // 参数  : int acktime[IN]: 应答数据等待超时时间，（秒）
   // 参数  : ST_CPACK *rpack[IN]: 请求包
   // 参数  : ST_CPACK *apack[OUT]: 应答包
   // 参数  : ST_PACK *pArrays[OUT]: 应答后续数据记录
	int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays);


   // 函数名: PushDataEx
   // 编程  : 陈永华 2005-9-16 0:25:40
   // 描述  : 向多个目标点发送推送消息包
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : TPUSHDEST *pushdests[IN]: 目标点列表
   // 参数  : int pdcount[IN]: 目标点个数
   // 参数  : ST_CPACK *ppack[IN]: 消息包
   // 参数  : char pushmode[IN]: 推送模式
   // 参数  : int acktime[IN]: 当为模式1的时候，本消息的有效时间（即多长时间内重复发送，否则取消）
   int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime,ST_PACK *pArray=NULL);

   // 函数名: PushData
   // 编程  : 陈永华 2005-9-16 0:21:07
   // 描述  : 向指定的目标点发送推送消息数据
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : int sourceno[IN]: 通过哪个通讯平台（编号）发送推送消息
   // 参数  : int destno[IN]: 目标应用服务器连接的通讯平台节点号(BRANCH/YYBDM)
   // 参数  : int funcno[IN]: 目标应用服务器注册的通讯功能号
   // 参数  : int batchno[IN]: 该目标点的接收批次号
   // 参数  : int acktime[IN]: 应答数据等待超时时间，（秒）
   // 参数  : ST_CPACK *ppack[IN]: 消息包
   // 参数  : char pushmode[IN]: 推送模式
   // 参数  : int acktime[IN]: 当为模式1的时候，本消息的有效时间（即多长时间内重复发送，否则取消）
	int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime,ST_PACK *pArray=NULL);
   //////////////////////////////////////////////////////////////////////////
   
	int ResetAnswerData();
	void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount);
   
	int SetAnswerTimeout(unsigned int atimeout);
	int SetBUError(int errcode,char *szErrMsg);

   // 函数名: BCCLogOut
   // 编程  : 陈永华 2005-9-27 12:06:12
   // 描述  : 提供BU，将需要记录的日志信息统一输出到BCC的各个日志文件中
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : char logtype[IN]: 本次日志的类型，参见下列数据
            //#define LT_MSG   'C'     文字日志
            //#define LT_CPACK 'P'     CPACK打包数据日志
            //#define LT_UDATA 'U'     用户自行定义数据日志
   // 参数  : int logid[IN]: 本日志的信息编号
   // 参数  : int textlen[IN]: 信息数据的长度
   // 参数  : char *text[IN]: 信息数据内存
   // 参数  : int datalen=0[IN]: 数据日志的长度
   // 参数  : void *data=NULL[IN]: 数据长度
	int BCCLogOut(char logtype,int logid,int textlen,char *text,int datalen=0,void *data=NULL);
   
	int PushRowEx(TPUSHDEST *pushdests,int pdcount,ST_PACK *pack,char pushmode,int batchno,int acktime);
	int PushRow(int sourceno,int destno,int funcno,ST_PACK *pack,char pushmode,int batchno,int acktime);

   // 函数名: PutRowData
   // 编程  : 陈永华 2005-9-27 12:10:43
   // 描述  : 根据前面调用SetCol指定的有效字段，输出一条记录给请求方
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : ST_PACK *pdata[IN]: 输出的ST_PACK/ST_SDPACK记录
   int PutRowData(ST_PACK *pdata);


   // 函数名: CheckLink
   // 编程  : 陈永华 2005-9-27 12:14:48
   // 描述  : 通过发送空命令方式检查与BCC连接是否正常
   // 返回  : bool true:表示连接正常；false:表示连接断开
	bool CheckLink();

   // 函数名: LinkOK
   // 编程  : 陈永华 2005-9-27 12:13:25
   // 描述  : 简单检查与BCC连接状态
   // 返回  : bool true:表示连接正常；false:表示连接断开
	bool LinkOK();
   
	int Processing(ST_BUNIT *pBUnit);
	void Close();
	int ToLink(ST_BUNIT *pBUnit);
	CSvrLink();
	virtual ~CSvrLink();

private:
	int SendMsgQ(short msgtype, unsigned short msglen, void *msgbuf);
	int SendMsgT(short msgtype, unsigned short msglen, void *msgbuf);
	int RecvMsgQ(int timeout);
	int RecvMsgT(int timeout);
   // 函数名: CSvrLink::SetTRUserID
   // 编程  : 陈永华 2005-8-2 11:25:04
   // 描述  : 设置更改应答数据接收方，表示后续PutRow等数据都要发送给指定方
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : TRUSERID *ruserid : 指定的应答数据接收方
	int SetTRUserID(TRUSERID *ruserid);

	int SMLockCmd(int smh, short lockmode);
	int DataDone(int retcode,char *szMsg);
	int CallBPFunction(MSGBUF *pmb);

   // 函数名: CSvrLink::SendMsg
   // 编程  : 陈永华 2004-2-10 21:08:11
   // 描述  : 以MSG格式发送消息数据给调度中心
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : short msgtype ：IN 发送的消息类型
   // 参数  : unsigned short msglen ：IN 消息体数据长度
   // 参数  : void *msgbuf ： IN 消息数据缓存
	int SendMsg(short msgtype,unsigned short msglen=0,void *msgbuf=NULL);

   // 函数名: CSvrLink::RecvMsg
   // 编程  : 陈永华 2004-2-10 22:40:18
   // 描述  : 按照MSG协议接收数据
   // 返回  : int -1:被对方正常关闭；-10:输入的nDesignedSize<=0；-11:对方非标准MSG协议口或数据不同步；-2:因为链路错误而被关闭；0:超时；-3:在接收数据的时候，出错而被关闭
   // 参数  : int timeout
	int RecvMsg(int timeout=3000);

	MSGBUF * GetRecvMsg();


};

#undef BUPUB_API

#endif // !defined(AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_)
