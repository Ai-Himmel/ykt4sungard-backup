/* ------------------------------------------------------------------------- */
/*
drtplib.h

创建日期：	2003/9/13
作者：		qzh
版本信息：	V4.0.1
功能：      通讯平台接口函数
*/
/* ------------------------------------------------------------------------- */
#ifndef __DRTPLIB_H__
#define __DRTPLIB_H__

#include "mytypes.h"

#define PROXY_SOCK5        3

typedef struct tag_drtphandle
{
	char buf[28];
}TAG_DRTPHANDLE;

typedef struct tag_drtphandle_ext
{
	char buf[32];
}TAG_DRTPHANDLE_EXT;

#ifdef __cplusplus
extern "C" {
#endif

// 函数名: DrtpInit
// 编程  : qianzhenghua 2005-01-24 12:12:35
// 描述  : 初始化通讯平台环境
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int *errcode *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpInit(int *errcode,char *errormessage);

// 函数名: DrtpSetProxy
// 编程  : qianzhenghua 2005-01-24 12:13:30
// 描述  : 设置SOCKS5代理服务器
// 返回  : BOOL 
// 参数  : int proxytype 代理服务器类型，目前只支持SOCK5，输入参数
// 参数  : char *ip 代理服务器地址，输入参数
// 参数  : int port 代理服务器端口，输入参数
// 参数  : char *user 代理服务器用户，输入参数
// 参数  : char *pwd 代理服务器用户密码，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpSetProxy(int proxytype,char *ip,int port,char *user,char *pwd,int *errcode,char *errormessage);

// 函数名: DrtpConnect
// 编程  : qianzhenghua 2005-01-24 12:15:31
// 描述  : 建立和通讯平台的连接
// 返回  : int 成功时返回大于0的连接句柄，-1表示发生错误
// 参数  : char *ip 通讯平台地址，输入参数
// 参数  : int port 通讯平台端口，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=-1 外部提供的SOCK连接，-1表示使用内部的SOCK连接，输入参数
int DrtpConnect(char *ip,int port,int *errcode,char *errormessage,int handle=-1);

// 函数名: DrtpReConnect
// 编程  : qianzhenghua 2005-01-24 12:18:03
// 描述  : 重新连接通讯平台
// 返回  : BOOL BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpReConnect(int handle,int *errcode,char *errormessage);

// 函数名: DrtpAddFunction
// 编程  : qianzhenghua 2005-01-24 12:19:07
// 描述  : 在通讯平台注册服务号
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int function 服务号，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=0 通讯平台连接句柄，输入参数，-1表示给所有连接注册服务号
BOOL DrtpAddFunction(int function,int *errcode,char *errormessage,int handle=0);

// 函数名: DrtpDelFunction
// 编程  : qianzhenghua 2005-01-24 12:20:51
// 描述  : 取消连接上的服务号
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int function 服务号，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=0 通讯平台连接句柄,-1是在所有连接上取消服务号，输入参数
BOOL DrtpDelFunction(int function,int *errcode,char *errormessage,int handle=0);

// 函数名: DrtpBlind
// 编程  : qianzhenghua 2005-01-24 12:23:15
// 描述  : 禁止连接上的服务号
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=-1 通讯平台连接句柄,-1是在所有连接上禁止服务号，输入参数
BOOL DrtpBlind(int *errcode,char *errormessage,int handle=-1);

// 函数名: DrtpLight
// 编程  : qianzhenghua 2005-01-24 12:24:43
// 描述  : 激活连接上的服务号
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=-1 通讯平台连接句柄,-1是在所有连接上激活服务号，输入参数
BOOL DrtpLight(int *errcode,char *errormessage,int handle=-1);

// 函数名: DrtpCheckMessage
// 编程  : qianzhenghua 2005-01-24 12:25:42
// 描述  : 检查通讯平台连接上是否有数据
// 返回  : int 返回有数据的连接句柄，-1表示发生了错误
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=-1 通讯平台连接句柄,-1是在所有连接上检查,输入参数
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
int DrtpCheckMessage(int *errcode,char *errormessage,int handle=-1,int timeout=-1);

// 函数名: DrtpCheckSlotMessage
// 编程  : qianzhenghua 2005-01-24 12:25:42
// 描述  : 检查slot连接上是否有数据
// 返回  : int 返回有数据的Slot连接句柄，-1表示发生了错误
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=-1 Slot连接句柄,-1是在所有Slot连接上检查,输入参数
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
int DrtpCheckSlotMessage(int *errcode,char *errormessage,int handle=-1,int timeout=-1);

// 函数名: DrtpCheckAllMessage
// 编程  : qianzhenghua 2005-01-24 12:25:42
// 描述  : 检查连接上是否有数据
// 返回  : int 返回有数据的连接句柄，-1表示发生了错误
// 参数  : int *type 连接的类型，1为通讯平台连接，2为SLOT连接，输出参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=-1 连接句柄,-1是在所有连接上检查,输入参数
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
int DrtpCheckAllMessage(int *type,int *errcode,char *errormessage,int handle=-1,int timeout=-1);

// 函数名: DrtpPostMessage
// 编程  : qianzhenghua 2005-01-24 12:29:08
// 描述  : 以通讯平台编号和功能号发送数据
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int primary 优先级，1到5，1为最高，输入参数
// 参数  : int branchno 通讯平台节点代码，输入参数
// 参数  : int function 服务号，输入参数
// 参数  : char *message 消息数据，最大为8000，输入参数
// 参数  : int messagelen 消息数据长度，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle 通讯平台连接句柄,输入参数
// 参数  : int hook=0 保留的标记，输入参数
// 参数  : int ackmode=0 确认模式,输入参数，0--不需要确认,1--接入的通讯平台返回确认,2--终点的通讯平台返回确认,3--应用服务器返回确认
// 参数  : int zip=2 压缩方式，输入参数，0：不压缩，1：压缩，2：由通讯平台指定压缩
BOOL DrtpPostMessage(int primary,int branchno,int function,char *message,int messagelen,
					 int *errcode,char *errormessage,int handle,int hook=0,
					 int ackmode=0,int zip=2);

// 函数名: DrtpPostAllMessage
// 编程  : qianzhenghua 2005-06-18 12:29:08
// 描述  : 以通讯平台编号和功能号广播数据
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int primary 优先级，1到5，1为最高，输入参数
// 参数  : int branchno 通讯平台节点代码，输入参数
// 参数  : int function 服务号，输入参数
// 参数  : char *message 消息数据，最大为8000，输入参数
// 参数  : int messagelen 消息数据长度，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle 通讯平台连接句柄,输入参数
// 参数  : int hook=0 保留的标记，输入参数
// 参数  : int zip=2 压缩方式，输入参数，0：不压缩，1：压缩，2：由通讯平台指定压缩
BOOL DrtpPostAllMessage(int primary,int branchno,int function,char *message,int messagelen,
					 int *errcode,char *errormessage,int handle,int hook=0,int zip=2);

// 函数名: DrtpSendMessage
// 编程  : qianzhenghua 2005-01-24 12:33:03
// 描述  : 发送数据到固定的通讯平台服务节点
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : char *message 消息数据，最大为8000，输入参数
// 参数  : int messagelen 消息数据长度，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : TAG_DRTPHANDLE *drtphandle 通讯平台通讯上下文,输入参数，由DrtpReadMessage或DrtpAttachServer得到
// 参数  : int handle=-1 通讯平台连接句柄,输入参数，-1为使用drtphandle中的连接句柄
// 参数  : int hook=0 保留的标记，输入参数
// 参数  : int ackmode=0 确认模式,输入参数，0--不需要确认,1--接入的通讯平台返回确认,2--终点的通讯平台返回确认,3--应用服务器返回确认
// 参数  : int primary=-1 优先级，1到5，1为最高，输入参数，-1表示使用drtphandle中的优先级
// 参数  : int zip=2 压缩方式，输入参数，0：不压缩，1：压缩，2：由通讯平台指定压缩
BOOL DrtpSendMessage(char *message,int messagelen,int *errcode,char *errormessage,
					 TAG_DRTPHANDLE *drtphandle,int handle=-1,int hook=0,int ackmode=0,
					 int primary=-1,int zip=2);

// 函数名: DrtpTransMessage
// 编程  : qianzhenghua 2005-01-24 12:36:19
// 描述  : 以通讯平台编号和功能号转发数据
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int branchno 通讯平台节点代码，输入参数
// 参数  : int function 服务号，输入参数
// 参数  : char *message 消息数据，最大为8000，输入参数
// 参数  : int messagelen 消息数据长度，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : TAG_DRTPHANDLE *drtphandle *drtphandle 通讯平台通讯上下文,输入参数，由DrtpReadMessage或DrtpAttachServer得到
// 参数  : int handle=-1 通讯平台连接句柄,输入参数，-1为使用drtphandle中的连接句柄
// 参数  : int hook=0 保留的标记，输入参数
// 参数  : int ackmode=0 确认模式,输入参数，0--不需要确认,1--接入的通讯平台返回确认,2--终点的通讯平台返回确认,3--应用服务器返回确认
// 参数  : int primary=-1 优先级，1到5，1为最高，输入参数，-1表示使用drtphandle中的优先级
// 参数  : int zip=2 压缩方式，输入参数，0：不压缩，1：压缩，2：由通讯平台指定压缩
BOOL DrtpTransMessage(int branchno,int function,char *message,int messagelen,
					  int *errcode,char *errormessage,TAG_DRTPHANDLE *drtphandle,
					  int handle=-1,int hook=0,int ackmode=0,int primary=-1,int zip=2);

// 函数名: DrtpReadMessage
// 编程  : qianzhenghua 2005-01-24 12:39:13
// 描述  : 读取特定连接上的数据
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : char *message 消息缓冲区，需要8192的长度，输入参数
// 参数  : int messagebufsize 消息缓冲区的长度，输入参数
// 参数  : int* messagelen 消息的长度，输出参数
// 参数  : int handle 通讯平台连接，输入参数
// 参数  : TAG_DRTPHANDLE *drtphandle 输出的通讯平台通讯上下文，需要在外部分配，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
BOOL DrtpReadMessage(char *message,int messagebufsize,int* messagelen,int handle,
					 TAG_DRTPHANDLE *drtphandle,int *errcode,char *errormessage,
					 int timeout=-1);

// 函数名: DrtpReadMessageExt
// 编程  : qianzhenghua 2005-01-24 12:39:13
// 描述  : 读取特定连接上的数据
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : char *message 消息缓冲区，需要8192的长度，输入参数
// 参数  : int messagebufsize 消息缓冲区的长度，输入参数
// 参数  : int* messagelen 消息的长度，输出参数
// 参数  : int handle 通讯平台连接，输入参数
// 参数  : TAG_DRTPHANDLE_EXT *drtphandle 输出的通讯平台通讯上下文，需要在外部分配，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
BOOL DrtpReadMessageExt(char *message,int messagebufsize,int* messagelen,int handle,
					 TAG_DRTPHANDLE_EXT *drtphandle,int *errcode,char *errormessage,
					 int timeout=-1);

// 函数名: DrtpAttachServer
// 编程  : qianzhenghua 2005-01-24 12:43:01
// 描述  : 绑定连接到特定的服务
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int branchno 通讯平等节点代码，输入参数
// 参数  : int function 通讯平台服务号，输入参数
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : TAG_DRTPHANDLE *drtphandle 输出的通讯平台通讯上下文，需要在外部分配，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpAttachServer(int branchno,int function,int handle,TAG_DRTPHANDLE *drtphandle,
					  int *errcode,char *errormessage);

// 函数名: DrtpPing
// 编程  : qianzhenghua 2005-01-24 12:44:47
// 描述  : 检查通讯平台的连接
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpPing(int handle,int *errcode,char *errormessage);

// 函数名: DrtpQueryRequest
// 编程  : qianzhenghua 2005-01-24 12:45:41
// 描述  : 查询通讯平台的内部信息，当hi=0 and low=0时，查询连接所在的通讯平台的信息
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int hi 内部节点编号高4字节，输入参数
// 参数  : int low 内部节点编号低4字节，输入参数
// 参数  : int cmd 查询命令字,输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle 通讯平台连接句柄，输入参数
BOOL DrtpQueryRequest(int hi,int low,int cmd,int *errcode,char *errormessage,int handle);

// 函数名: DrtpQueryResult
// 编程  : qianzhenghua 2005-01-24 12:48:21
// 描述  : 获取查询通讯平台操作的结果
// 返回  : int 返回大于0表示还后续数据，0表示没有后续数据，-1为发生了错误
// 参数  : char* message 存放查询结果的缓冲区，需要8192字节，输入参数
// 参数  : int messagesize 存放查询结果的缓冲区的长度，输入参数
// 参数  : int *messagelen 查询结果的长度，输出参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
int DrtpQueryResult(char* message,int messagesize,int *messagelen,int *errcode,char *errormessage,int handle,int timeout=-1);

// 函数名: DrtpGetHook
// 编程  : qianzhenghua 2005-01-24 12:50:53
// 描述  : 获取hook
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : int *hook 输出参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage  失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpGetHook(int handle,int *hook,int *errcode,char *errormessage);

// 函数名: DrtpGetHandle
// 编程  : qianzhenghua 2005-01-24 12:53:34
// 描述  : 获取通讯平台连接的通讯上下文
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : TAG_DRTPHANDLE *drtphandle 通讯平台通讯上下文,有调用者分配，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpGetHandle(int handle,TAG_DRTPHANDLE *drtphandle,int *errcode,char *errormessage);

// 函数名: DrtpClose
// 编程  : qianzhenghua 2005-01-24 12:55:04
// 描述  : 关闭通讯平台的连接
// 返回  : void 
// 参数  : int handle=-1 通讯平台连接句柄，handle=-1为关闭所有连接，输入参数
// 参数  : bool flag=false 当连接全部关掉后是否释放通讯平台环境，false为不释放，输入参数
void DrtpClose(int handle=-1,bool flag=false);

// 函数名: DrtpExit
// 编程  : qianzhenghua 2005-01-24 12:55:51
// 描述  : 释放通讯平台环境
// 返回  : void 
void DrtpExit();

/*内部使用的涵数*/
int DrtpListen(int port,int *errcode,char* errormessage);
int DrtpAccept(int handle,int *errcode,char *errormessage);
BOOL DrtpCheckSSL(int handle,int crypto,int *errcode,char *errormessage);
BOOL DrtpIsLogined(int handle);
void DrtpSetLogined(int handle,char *user,char *pwd);
BOOL DrtpGetUserPwd(int handle,char *user,char *pwd);
BOOL DrtpSetLocation(int handle,int location,int windowsize);
BOOL DrtpGetLocation(int handle,int *location,int *windowsize);
int DrtpNewHandle();
void DrtpDelHandle(int handle);
int DrtpPeerHandle(TAG_DRTPHANDLE *drtphandle);


// 函数名: DrtpAddSlot
// 编程  : qianzhenghua 2005-02-05 11:14:41
// 描述  : 在通讯平台上注册通讯槽
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int slot 通讯槽号，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int handle=0 通讯平台连接句柄，输入参数，-1表示给所有连接注册通讯槽
BOOL DrtpAddSlot(int slot,int *errcode,char *errormessage,int handle=0);

// 函数名: DrtpGetSlotHandle
// 编程  : qianzhenghua 2005-02-05 11:18:33
// 描述  : 获取通讯槽上新建立的连接
// 返回  : int 成功时返回连接序号，返回-1表示发生了错误
// 参数  : int handle 通讯平台连接，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
int DrtpGetSlotHandle(int handle,int *errcode,char *errormessage,int timeout=-1);

// 函数名: DrtpSlotSendMessage
// 编程  : qianzhenghua 2005-02-05 11:22:59
// 描述  : 使用通讯槽发送数据
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : char *message 消息数据，最大为8000，输入参数
// 参数  : int messagelen 消息数据长度，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int slothandle 通讯槽连接句柄，输入参数
// 参数  : int zip=2 压缩方式，输入参数，0：不压缩，1：压缩，2：由通讯平台指定压缩
BOOL DrtpSlotSendMessage(char *message,int messagelen,int *errcode,char *errormessage,
						 int slothandle,int zip=2);

// 函数名: DrtpSlotReadMessage
// 编程  : qianzhenghua 2005-02-05 11:25:39
// 描述  : 使用通讯槽接受数据
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : char *message 消息缓冲区，需要8192的长度，输入参数
// 参数  : int messagebufsize 消息缓冲区的长度，输入参数
// 参数  : int* messagelen 消息的长度，输出参数
// 参数  : int handle 通讯槽连接句柄，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
BOOL DrtpSlotReadMessage(char *message,int messagebufsize,int* messagelen,int handle,
						 int *errcode,char *errormessage,int timeout=-1);

// 函数名: DrtpLinkSlot
// 编程  : qianzhenghua 2005-02-05 12:43:55
// 描述  : 创建到通讯槽的连接
// 返回  : int 成功时返回连接序号，返回-1表示发生了错误
// 参数  : char *ip 通讯平台ip地址，输入参数
// 参数  : int port 通讯平台端口，输入参数
// 参数  : int branchno  通讯平台节点代码，输入参数
// 参数  : int slot 通讯槽号，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : int timeout=-1 等待数据的超时，单位为毫秒，-1为无限等待，输入参数
int DrtpLinkSlot(char *ip,int port,int branchno,int slot,int *errcode,
				 char *errormessage,int timeout=-1);

// 函数名: DrtpCloseConnect
// 编程  : 钱正话 2005-5-8 17:48:09
// 描述  : 关闭特定的连接
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : int x 目标节点编号高位,输入参数,0表示接入节点
// 参数  : int y 目标节点编号低位,输入参数,0表示接入节点
// 参数  : int connectno 连接号,输入参数
// 参数  : int timestamp 连接时间,输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpCloseConnect(int handle,int x,int y,int connectno,int timestamp,int *errcode,char *errormessage);

// 函数名: DrtpCheckConnect
// 编程  : 钱正话 2005-5-8 17:48:09
// 描述  : 检测特定的连接
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int handle 通讯平台连接句柄，输入参数
// 参数  : int x 目标节点编号高位,输入参数,0表示接入节点
// 参数  : int y 目标节点编号低位,输入参数,0表示接入节点
// 参数  : int connectno 连接号,输入参数
// 参数  : int timestamp 连接时间,输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpCheckConnect(int handle,int x,int y,int connectno,int timestamp,int *errcode,char *errormessage);

// 函数名: DrtpGetConnectInfo
// 编程  : 钱正话 2005-5-8 17:54:05
// 描述  : 从drtphandle中获取源连接信息
// 返回  : void 
// 参数  : TAG_DRTPHANDLE *drtphandle DrtpReadMessage的返回,为输入参数
// 参数  : int *x 目标节点编号高位,输出参数
// 参数  : int *y 目标节点编号低位,输出参数
// 参数  : int *connectno 连接号,输出参数
// 参数  : int *timestamp 连接时间,输出参数
void DrtpGetConnectInfo(TAG_DRTPHANDLE *drtphandle,int *x,int *y,int *connectno,int *timestamp);


// 函数名: DrtpGetVersion
// 编程  : 钱正华 2005-6-18 9:12:55
// 描述  : 获得接口的版本
// 返回  : void 
// 参数  : char *version 输出参数，需要50个字节的空间
void DrtpGetVersion(char *version);


// 函数名: DrtpGetHandleInfo
// 编程  : 钱正华 2005-9-6 16:41:13
// 描述  : 获取连接的内部信息
// 返回  : BOOL handle存在返回TRUE,否则返回FALSE
// 参数  : int handle 通讯平台连接，输入参数
// 参数  : int *branchno 连接的通讯平台节点号,输出参数
// 参数  : int *hi 连接的通讯平台节点内部编号高位,输出参数
// 参数  : int *low 连接的通讯平台节点内部编号低位,输出参数
// 参数  : int *socketno 连接的socket,输出参数
// 参数  : int *timestamp 连接的建立时间序号,输出参数
BOOL DrtpGetHandleInfo(int handle,int *branchno,int *hi,int *low,int *socketno,int *timestamp);

// 函数名: DrtpSetBusy
// 编程  : 钱正华 2006-4-11 9:30:11
// 描述  : 设置连接的忙碌标志
// 返回  : BOOL 成功返回TRUE,失败返回FALSE
// 参数  : int handle 通讯平台连接，输入参数,-1表示设置所有的连接
// 参数  : int busy	忙碌，属输入参数，大于等于0，单位为秒
// 参数  : int multi 倍率，属输入参数，大于1
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpSetBusy(int handle,int busy,int multi,int *errcode,char *errormessage);

// 函数名: DrtpSetBusyExt
// 编程  : 钱正华 2006-4-11 9:30:11
// 描述  : 设置连接的忙碌标志
// 返回  : BOOL 成功返回TRUE,失败返回FALSE
// 参数  : int handle 通讯平台连接，输入参数,-1表示设置所有的连接
// 参数  : int x 目标节点编号高位,输入参数,0表示接入节点
// 参数  : int y 目标节点编号低位,输入参数,0表示接入节点
// 参数  : int connectno 连接号,输入参数
// 参数  : int timestamp 连接时间,输入参数
// 参数  : int busy	忙碌，属输入参数，大于等于0，单位为秒
// 参数  : int multi 倍率，属输入参数，大于1
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
BOOL DrtpSetBusyExt(int handle,int x,int y,int connectno,int timestamp,int busy,int multi,int *errcode,char *errormessage);

#define CERTIFY_BEFORE		1	
//处理将需要认证的资料给对方
#define CERTIFY_AFTER		2
//处理对方给出的认证资料


// 函数名: CertifyHandle
// 编程  : 钱正华 2006-4-17 15:25:26
// 描述  : 外挂的处理函数
// 返回  : BOOL 通过返回TRUE,否则返回FALSE
// 参数  : char *certifydata	认证的数据，可以是证书或其他
// 参数  : int  *certifydatalength	数据的长度
typedef BOOL (* CertifyHandle)(char *certifydata,int *certifydatalength);


// 函数名: DrtpSetCertifyHandle
// 编程  : 钱正华 2006-4-17 15:21:06
// 描述  : 设置认证处理接口
// 返回  : void 
// 参数  : int type 处理类型,输入参数，只能是CERTIFY_BEFORE或CERTIFY_AFTER
// 参数  : CertifyHandle fhandle 处理函数，输入参数
void DrtpSetCertifyHandle(int type,CertifyHandle fhandle);

// 函数名: DrtpCertifyOk
// 编程  : 钱正华 2006-4-17 15:21:06
// 描述  : 认证通过的响应
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : char *certifyblock 待认证数据，最大为8000，输入参数
// 参数  : int certifyblocklen 待认证数据长度，输入参数
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : TAG_DRTPHANDLE *drtphandle 通讯平台通讯上下文,输入参数，由DrtpReadMessage或DrtpAttachServer得到
// 参数  : int handle=-1 通讯平台连接句柄,输入参数，-1为使用drtphandle中的连接句柄
BOOL DrtpCertifyOk(char *certifyblock,int certifyblocklen,int *errcode,char *errormessage,
					 TAG_DRTPHANDLE *drtphandle,int handle=-1);

// 函数名: DrtpCertifyFail
// 编程  : 钱正华 2006-4-17 15:21:06
// 描述  : 认证通过的响应
// 返回  : BOOL 成功时返回TRUE,否则返回FALSE
// 参数  : int reasoncode 失败返回的代码
// 参数  : char *reasonmsg 失败返回的描述，输入参数，长度最大为300
// 参数  : int *errcode 失败时返回的错误编码，为输出参数
// 参数  : char *errormessage 失败时返回的错误描述，为输出参数,长度为300
// 参数  : TAG_DRTPHANDLE *drtphandle 通讯平台通讯上下文,输入参数，由DrtpReadMessage或DrtpAttachServer得到
// 参数  : int handle=-1 通讯平台连接句柄,输入参数，-1为使用drtphandle中的连接句柄
BOOL DrtpCertifyFail(int reasoncode,char *reasonmsg,int *errcode,char *errormessage,
					 TAG_DRTPHANDLE *drtphandle,int handle=-1);
#ifdef __cplusplus
}
#endif

#endif