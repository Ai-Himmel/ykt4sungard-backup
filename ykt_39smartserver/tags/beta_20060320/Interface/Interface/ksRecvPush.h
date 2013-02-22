
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSRECVPUSH_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSRECVPUSH_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef __KSRECVPUSH_H
#define __KSRECVPUSH_H

#ifdef KSRECVPUSH_EXPORTS
#define KSRECVPUSH_API __declspec(dllexport)
#else
#define KSRECVPUSH_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksRecvPushd.lib")
#pragma message("Automatically Linking ksRecvPushd.dll")
#else
#pragma comment(lib,"../lib/ksRecvPush.lib")
#pragma message("Automatically Linking ksRecvPush.dll")
#endif
#endif

#include "ksProcPush.h"

#ifndef NOTIMSGINFO
#define NOTIMSGINFO
#define MAXMSGLEN 255
typedef struct
{
	int nLevel;
	char strMsg[MAXMSGLEN];
}ST_NOTIMSG;
#endif

#ifdef __cplusplus
extern "C" {
#endif
//功能：初始化函数
//参数说明：
//nBatch:会话批次号
//hCallerWnd:调用者的句柄
//nPushMessage:推送数据到达通知消息
//nNotiMessage:dll内部通知消息
//nReadPushMethod:推送数据读取方式 1-发送nPushMessage消息，接收者调用RecvPush_GetMultiPushPack获得数据
//								   2-不发送消息，接收者主动调用RecvPush_RecvPushPack获得数据
//nReadMsgMethod:内部消息读取方式  1-发送nNotiMessage消息，接收者调用RecvPush_GetMultiMsgPack获得数据
//								   2-不发送消息，接收者主动调用RecvPush_RecvMsgPack获得数据
//nMaxPushQueLen:系统内部保留的最大推送数据队列长度
//nMaxMsgQueLen:系统内部保留的最大内部消息队列长度
//返回值：
//0 成功 
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_Initialize(int nBatch,HWND hCallerWnd=NULL,int nPushMessage=0,
								 int nNotiMessage=0,int nReadPushMethod=2,int nReadMsgMethod=2,
								 int nMaxPushQueLen=1000,int nMaxMsgQueLen=1000);

//功能：开始接收函数
//参数说明:
//strDrtpAddr:通讯平台ip地址
//nDrtpPort:通讯平台端口号
//nMainFunc:主功能号
//返回值：
//0 成功 
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_Start(char* strDrtpAddr,int nDrtpPort,int nMainFunc);

//功能：停止接收函数
//返回值：
//0 成功 
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_Stop();

//功能：释放资源函数
//返回值：
//0 成功 
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_Uninitialize();

//功能：读取指定条数的推送数据（用于读取方式1）,数据以cpack方式存放
//参数说明：
//buf:推送数据缓冲，不得小于cpack长度
//nBufSize:缓冲区的大小
//nPackCount:希望读取的数据个数
//返回值：
//>0，真正获得的推送数据个数
//=0，当前没有推送数据
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_GetMultiPushPack(char* buf,int nBufSize,int nPackCount);

//功能：读取指定条数的内部消息数据（用于读取方式1）,数据以ST_NOTIMSG方式存放
//参数说明：
//buf:推送数据缓冲，不得小于ST_NOTIMSG长度
//nBufSize:缓冲区的大小
//nPackCount:希望读取的数据个数
//返回值：
//>0，真正获得的内部消息数据个数
//=0，当前没有内部消息数据
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_GetMultiMsgPack(char* buf,int nBufSize,int nPackCount);

//功能：读取一条推送数据（用于读取方式2），数据以CPACK方式存放
//参数说明：
//buf:缓冲区，不得小于cpack长度
//nBufSize:缓冲区的大小
//nTimeOut:超时时间，以毫秒为单位，不得小于100ms,如果为0，则阻塞接收
//返回值：
//0，超时
//1，读取成功
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_RecvPushPack(char* buf,int nBufSize,int nTimeOut);

//功能：读取一条内部消息数据（用于读取方式2），数据以ST_NOTIMSG方式存放
//参数说明：
//buf:缓冲区，不得小于ST_NOTIMSG长度
//nBufSize:缓冲区的大小
//nTimeOut:超时时间，以毫秒为单位，不得小于100ms,如果为0，则阻塞接收
//返回值：
//0，超时
//1，读取成功
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_RecvMsgPack(char* buf,int nBufSize,int nTimeOut);

//功能：查看内部消息队列缓冲区大小
//返回值：
//>=0，队列缓冲区大小
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_GetMsgQueLen();

//功能：查看推送队列缓冲区大小
//返回值：
//>=0，队列缓冲区大小
//-1 失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_GetPushQueLen();

//功能：得到总的丢弃包个数
//返回值：
//>=0 ,丢弃包个数
int KSRECVPUSH_API WINAPI RecvPush_GetThrowPackCount();

//功能：得到错误代码错误信息
//参数说明：
//pErrorCode:错误代码
//strMsg:错误描述
void KSRECVPUSH_API WINAPI RecvPush_GetLastError(int *pErrorCode,char* strMsg);

//功能：设置控制信息的requesttype数组
//参数说明：
//nCount:ControlReq数组中的元素个数
//ControlReq:控制信息的requesttype数组
//返回值：
//=0 ,设置成功
//<0 ,失败，可以通过调用RecvPush_GetLastError得到内部失败代码和失败原因
int KSRECVPUSH_API WINAPI RecvPush_SetControlReqTypes(int nCount,unsigned int *ControlReq);
#ifdef __cplusplus
}
#endif

#endif