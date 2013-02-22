/*
ver 2.0
		DRTPAPPDLL_API WORD App_GetVer();
		DRTPAPPDLL_API int App_Init(int QueueLen = 20 , int ErrorMode = 0 , void *lp = NULL);
		DRTPAPPDLL_API bool App_Connect(int index , LPSTR ServerIp , short ServerPort , WORD FunctionCount , void *func , int EncryptMode = 0);
		DRTPAPPDLL_API bool App_Recv(int index);
		DRTPAPPDLL_API bool App_ReConnect(int index , int ReConnectDelay = 1);
		DRTPAPPDLL_API int App_Pop(APPHANDLE *handle , LPSTR Data , int len);
		DRTPAPPDLL_API bool App_Send(APPHANDLE *handle , LPSTR Data , int len);
		DRTPAPPDLL_API void App_Close(int index,APPHANDLE *handle = NULL);
		DRTPAPPDLL_API void App_GetLastError(LPSTR error);
ver 2.01
		DRTPAPPDLL_API bool App_RecvDone(LPSTR ServerIp , short ServerPort , WORD FunctionCount , WORD *func);
ver 2.02
		DRTPAPPDLL_API int App_Pop2(APPHANDLE *handle , LPSTR Data , int len);
		DRTPAPPDLL_API bool App_Send2(APPHANDLE *handle , LPSTR Data , int len ,int ColNum , int flag);
ver 2.03
		DRTPAPPDLL_API bool App_Transmit(APPHANDLE *handle , LPSTR Data , int len , int DestNo , WORD MainFunc);
		DRTPAPPDLL_API void App_SetLogFileName(char *filename)
		DRTPAPPDLL_API void App_GetUserHandle(APPHANDLE *handle , char *UserHandle)
*/

#ifndef _DRTPAPPDLL_H
#define _DRTPAPPDLL_H

#if defined(WIN32)
	#ifdef DRTPAPPDLL_EXPORTS
		#define DRTPAPPDLL_API __declspec(dllexport)
	#else
		#define DRTPAPPDLL_API __declspec(dllimport)
	#endif
#else
	#define DRTPAPPDLL_API
	#include "mytypes.h"
	#include <stdlib.h>
#endif

#if !defined(GETLOW)
#define GETDRTPLOW(ver) ((BYTE)(ver>>8)&0xff)
#endif
#if !defined(GETHIGH)
#define GETDRTPHIGH(ver) ((BYTE)ver&0xff)
#endif
#if !defined(MAKEDRTPVER)
#define MAKEDRTPVER(high,low) ((WORD)high|(WORD)low<<8)
#endif

#ifndef DRTPAPPVER
#define DRTPAPPVER		MAKEDRTPVER(2,3)
#endif

#define APPENOREPORT	0
#define APPEPRINTF		1
#define APPEWRITEBUF	2
#define APPEMSGDLG		3

#define USER_MESSAGE_RESULT		2	//返回结果集，返回应答数据
#define USER_MESSAGE_REPORT		5	//返回报告消息，返回错误信息
#define USER_MESSAGE_ENDPACK	12	//结束包，在所有数据发送完之后，必须发送结束包，该包无数据，len=0

struct APPHANDLE
{
	char buf[64];
};

//得到版本号
DRTPAPPDLL_API WORD App_GetVer();

//初始化接收数据socket，设置接收队列长度，并得到一个连接索引index，
//通过该索引与网关通讯,(设置报错方式,暂未实现)
//返回-1表示失败
DRTPAPPDLL_API int App_Init(int QueueLen = 20 , int ErrorMode = 0 , void *lp = NULL);

//根据index连接网关，交换密钥，注册功能号
//index是App_Init返回的连接索引
//连接失败返回false;
DRTPAPPDLL_API bool App_Connect(int index , LPSTR ServerIp , short ServerPort , WORD FunctionCount , void *func , int EncryptMode = 0);

//根据连接索引index从网关上接收一个数据包，并将接收到的数据填入接收队列
//如果没有接收到数据则阻塞接收，出错返回<0，成功则返回0
//返回-2需要重新连接，否则不需要
DRTPAPPDLL_API int iApp_Recv(int index);

//根据连接索引index从网关上接收一个数据包，并将接收到的数据填入接收队列
//如果没有接收到数据则阻塞接收，出错返回false，成功则返回true
DRTPAPPDLL_API bool App_Recv(int index);

//重连网关，连接失败时延时ReConnectDelay秒后重试，直到连接成功
//如果 ReConnectDelay <= 0 则连接失败后不重试，以false返回
DRTPAPPDLL_API bool App_ReConnect(int index , int ReConnectDelay = 1);

//从接收队列中取数据，APPHANDLE由函数调用者分配内存，
//连接信息被保存到该内存块中，在发送完全部数据之前，该内存不能释放
//返回值 <= 0 表示出错，否则表示取到的数据长度
DRTPAPPDLL_API int App_Pop(APPHANDLE *handle , LPSTR Data , int len , DWORD TimeOut = 0);

//向网关发送数据，handle必须是Pop函数返回的句柄
DRTPAPPDLL_API bool App_Send(APPHANDLE *handle , LPSTR Data , int len);

//关闭与网关的连接,如果handle不为NULL则关闭句柄上的连接，否则关闭index指定的连接
DRTPAPPDLL_API void App_Close(int index,APPHANDLE *handle = NULL);

DRTPAPPDLL_API void App_GetLastError(LPSTR error);

///////////////////////////////////////////////////////////////////////
//DRTPAPPDLL ver 2.01

//使用缺省参数创建接收线程，实现了App_Init,App_Connect,App_Recv和App_ReConnect的功能
//ServerIp 网关地址,ServerPort 连接端口号,FunctionCount 主功能号数目,func 功能号数组
//该函数创建了一个单独的线程负责数据的接收
DRTPAPPDLL_API bool App_RecvDone(LPSTR ServerIp , short ServerPort , WORD FunctionCount , WORD *func);

///////////////////////////////////////////////////////////////////////
//DRTPAPPDLL ver 2.02

//从接收队列中取数据，APPHANDLE由函数调用者分配内存，
//连接信息被保存到该内存块中，在发送完全部数据之前，该内存不能释放
//返回值 <= 0 表示出错，否则表示取到的数据长度
//注意：返回的数据Data中不包括应用头，是一串用|分隔的字符串，而App_Pop返回数据中包括应用头
DRTPAPPDLL_API int App_Pop2(APPHANDLE *handle , LPSTR Data , int len , DWORD TimeOut = 0);

//向网关发送数据，handle必须是Pop函数返回的句柄
//注意，发送数据Data不包括应用头，是一串用|分隔的字符串，而App_Send发送数据包括应用头
//ColNum 表示发送的字段数目，即|分隔的字符串数目，如：发送 A|123|11 则ColNum = 3
//flag 参数表示发送数据的类型，有以下几种:
//		USER_MESSAGE_RESULT		返回结果集，返回应答数据
//		USER_MESSAGE_REPORT		返回报告消息，返回错误信息
//		USER_MESSAGE_ENDPACK	结束包，在所有数据发送完之后，必须发送结束包，该包无数据，len=0
DRTPAPPDLL_API bool App_Send2(APPHANDLE *handle , LPSTR Data , int len ,int ColNum , int flag);

///////////////////////////////////////////////////////////////////////
//DRTPAPPDLL ver 2.03

//向另外一个应用转发请求数据包
//DestNo 转发数据的目的营业部代码
//其它参数与App_Send相同
//该函数可满足将本地应用无法处理的请求发往其它应用的需要
DRTPAPPDLL_API bool App_Transmit(APPHANDLE *handle , LPSTR Data , int len , int DestNo, WORD MainFunc = 0);

//设置记录错误日志的文件名
//如不调用该函数，缺省的日志文件名是可执行文件所在目录下的liblog.txt文件
//如果filename参数不带路径，则自动添加可执行文件所在的目录
DRTPAPPDLL_API void App_SetLogFileName(char *filename);

//得到客户端标志
//UserHandle缓冲区的长度为64字节，由函数调用者提供
DRTPAPPDLL_API void App_GetUserHandle(APPHANDLE *handle , char *UserHandle);


// 函数名: App_GetConnectIndex
// 编程  : 陈永华 2002-5-26 11:14:07
// 描述  : 根据APPHANDLE 取得使用的Index(由App_Init()返回的索引号)
// 返回  : DRTPAPPDLL_API int 
// 参数  : APPHANDLE *handle
DRTPAPPDLL_API int App_GetConnectIndex(APPHANDLE *handle);

#endif