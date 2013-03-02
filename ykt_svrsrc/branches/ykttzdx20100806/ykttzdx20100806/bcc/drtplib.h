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

#ifdef __cplusplus
extern "C" {
#endif

/*
初始化通讯平台环境
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
*/
BOOL DrtpInit(long *errcode,char *errormessage);

/*
设置SOCKS5代理服务器
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
ip:代理服务器地址
port:代理服务器端口
*/
BOOL DrtpSetProxy(long proxytype,char *ip,long port,char *user,char *pwd,long *errcode,char *errormessage);

/*
建立和通讯平台的连接
成功时返回大于0的连接句柄,否则返回-1,在失败时,errcode中是错误代码,errormessage中是错误信息
ip:通讯平台地址
port:通讯平台端口
*/
long DrtpConnect(char *ip,long port,long *errcode,char *errormessage,long handle=-1);

/*
重新连接通讯平台
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
handle:通讯平台连接句柄
*/
BOOL DrtpReConnect(long handle,long *errcode,char *errormessage);

/*
在通讯平台注册服务号
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
function:服务号
handle:通讯平台连接句柄,handle=-1,是在所有连接上注册服务号
*/
BOOL DrtpAddFunction(long function,long *errcode,char *errormessage,long handle=0);

/*
取消在通讯平台上的服务号
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
function:服务号
handle:通讯平台连接句柄,handle=-1,是在所有连接上取消服务号
*/
BOOL DrtpDelFunction(long function,long *errcode,char *errormessage,long handle=0);

/*
禁止连接在通讯平台上的服务
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
handle:通讯平台连接句柄,handle=-1,是在所有连接上禁止服务
*/
BOOL DrtpBlind(long *errcode,char *errormessage,long handle=-1);

/*
激活连接在通讯平台上的服务
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
handle:通讯平台连接句柄,handle=-1,是在所有连接上激活服务
*/
BOOL DrtpLight(long *errcode,char *errormessage,long handle=-1);

/*
检查连接上是否有数据,
成功时返回大于0的连接句柄,否则返回-1,在失败时,errcode中是错误代码,errormessage中是错误信息
handle:通讯平台连接句柄
*/
long DrtpCheckMessage(long *errcode,char *errormessage,long handle);

/*
以通讯平台编号和功能号发送数据
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
primary:数据的优先级,可为1,2,3,4,5
branchno:通讯平台编号(是通讯平台的别名编号)
function:服务号
message:发送的数据
messagelen:发送的数据的长度
handle:通讯平台连接句柄
hook:保留的标记
ackmode:确认模式,0--不需要确认,1--接入的通讯平台返回确认,2--终点的通讯平台返回确认,
				3--应用服务器返回确认
*/
BOOL DrtpPostMessage(long primary,long branchno,long function,char *message,
					 long messagelen,long *errcode,char *errormessage,
					 long handle,long hook=0,long ackmode=0);

/*
发送数据到固定的通讯平台服务节点,
这个固定的节点，或者是通过DrtpAttach获得的，或者是上一个收到的数据的发送节点
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
primary:数据的优先级,可为1,2,3,4,5
message:发送的数据
messagelen:发送的数据的长度
drtphandle:通讯平台通讯上下文,由DrtpReadMessage或DrtpAttachServer得到
hook:保留的标记
ackmode:确认模式,0--不需要确认,1--接入的通讯平台返回确认,2--终点的通讯平台返回确认,
				3--应用服务器返回确认
*/
BOOL DrtpSendMessage(char *message,long messagelen,long *errcode,
					 char *errormessage,TAG_DRTPHANDLE *drtphandle,long hook=0,
					 long ackmode=0,long primary=-1);

/*
以通讯平台编号和功能号转发数据
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
primary:数据的优先级,可为1,2,3,4,5
branchno:通讯平台编号(是通讯平台的别名编号)
function:服务号
message:发送的数据
messagelen:发送的数据的长度
drtphandle:通讯平台通讯上下文,由DrtpReadMessage或DrtpAttachServer得到
hook:保留的标记
ackmode:确认模式,0--不需要确认,1--接入的通讯平台返回确认,2--终点的通讯平台返回确认,
				3--应用服务器返回确认
*/
BOOL DrtpTransMessage(long branchno,long function,char *message,
					  long messagelen,long *errcode,char *errormessage,
					  TAG_DRTPHANDLE *drtphandle,long hook=0,long ackmode=0,long primary=-1);

/*
读取特定连接上的数据
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
message:用以接受数据的buffer
messagebufsize:接受数据的buffer的长度
messagelen:读取到的数据的长度
timeout:读操作的超时时间(单位是毫秒)，-1为无限制
handle:通讯平台连接句柄
drtphandle:通讯平台通讯上下文,有调用者分配
hook:发送数据无法到达时返回的标记
*/
BOOL DrtpReadMessage(char *message,long messagebufsize,long* messagelen,
					 long handle,TAG_DRTPHANDLE *drtphandle,
					 long *errcode,char *errormessage,long timeout=-1);

/*
绑定连接到特定的服务
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
branchno:通讯平台编号(是通讯平台的别名编号)
function:服务号
handle:通讯平台连接句柄
drtphandle:通讯平台通讯上下文,有调用者分配
*/
BOOL DrtpAttachServer(long branchno,long function,long handle,
					  TAG_DRTPHANDLE *drtphandle,
					  long *errcode,char *errormessage);

/*
检查通讯平台的连接
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
handle:通讯平台连接句柄
*/
BOOL DrtpPing(long handle,long *errcode,char *errormessage);

/*
查询通讯平台的内部信息
当hi=0 and low=0时，查询连接所在的通讯平台的信息,
否则就是(hi,low)对应的通讯平台的信息
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
hi:通讯平台节点编号高4位
low:通讯平台节点编号低4位
cmd:查询操作的指令(1,2,3,4,5,6,7)
handle:通讯平台连接句柄
*/
BOOL DrtpQueryRequest(long hi,long low,long cmd,long *errcode,char *errormessage,long handle);

/*
获取查询通讯平台操作的结果
成功时返回 >= 0,否则返回-1,在失败时,errcode中是错误代码,errormessage中是错误信息,返回0,表示后面没有记录
message:用以接受数据的buffer
messagebufsize:接受数据的buffer的长度
messagelen:读取到的数据的长度
timeout:读操作的超时时间(单位是毫秒)，-1为无限制
handle:通讯平台连接句柄
*/
long DrtpQueryResult(char* message,long messagesize,long *messagelen,long *errcode,char *errormessage,long handle,long timeout=-1);

/*
获取hook
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
drtphandle:通讯平台通讯上下文,由DrtpReadMessage或DrtpAttachServer得到
hook:保留大标记
*/
BOOL DrtpGetHook(long handle,long *hook,long *errcode,char *errormessage);

/*
获取通讯平台连接的通讯上下文
成功时返回TRUE,否则返回FALSE,在失败时,errcode中是错误代码,errormessage中是错误信息
drtphandle:通讯平台通讯上下文,有调用者分配
handle:通讯平台连接句柄
*/
BOOL DrtpGetHandle(long handle,TAG_DRTPHANDLE *drtphandle,long *errcode,char *errormessage);

/*
关闭通讯平台的连接
handle:通讯平台连接句柄，handle=-1为关闭所有连接
flag:当连接全部关掉后是否释放通讯平台环境
*/
void DrtpClose(long handle=-1,bool flag=false);

/*
释放通讯平台环境
*/
void DrtpExit();

/*内部使用的涵数*/
long DrtpListen(long port,long *errcode,char* errormessage,bool local=false);
long DrtpAccept(long handle,long *errcode,char *errormessage);
BOOL DrtpCheckSSL(long handle,long crypto,long *errcode,char *errormessage);
BOOL DrtpIsLogined(long handle);
void DrtpSetLogined(long handle,char *user,char *pwd);
BOOL DrtpGetUserPwd(long handle,char *user,char *pwd);
long DrtpNewHandle();
void DrtpDelHandle(long handle);

#ifdef __cplusplus
}
#endif

#endif