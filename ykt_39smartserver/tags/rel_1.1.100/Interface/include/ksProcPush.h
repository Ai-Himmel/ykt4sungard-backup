
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSPROCPUSH_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSPROCPUSH_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef __KSPROCPUSH_H
#define __KSPROCPUSH_H

#ifdef KSPROCPUSH_EXPORTS
#define KSPROCPUSH_API __declspec(dllexport)
#else
#define KSPROCPUSH_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksProcPushd.lib")
#pragma message("Automatically Linking ksProcPushd.dll")
#else
#pragma comment(lib,"../lib/ksProcPush.lib")
#pragma message("Automatically Linking ksProcPush.dll")
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
//功能：推送数据处理函数
//参数说明：
//recvpack[输入]:接收到的数据缓冲(ST_CPACK格式)
//ackpack[输出]:如果需要应答包的话，应答数据的缓冲(ST_CPACK格式)
//pAckFlag[输出]:需要应答包标记，	0：不需要应答包
//									1：需要应答包
//pCtlFlag[输出]:控制消息标记，		0：不是控制消息
//									1：是控制消息
//szMsg[输出]:信息输出
//返回值：
//0 成功 
//-1 失败，接收到的数据非推送类数据
//其他 失败，可以通过szMsg知道失败原因
int KSPROCPUSH_API WINAPI ProcPush_ProcPushData(char *recvpack,char* ackpack,int *pAckFlag,int *pCtlFlag,char *szMsg);

//功能：初始化数据函数
//参数说明：
//nBatch[输入]:会话批次号
//返回值：
//0 成功 
//其他 失败
int KSPROCPUSH_API WINAPI ProcPush_Init(int nBatch);

//功能：初始化资源函数
//参数说明：
//返回值：
//0 成功 
//其他 失败
int KSPROCPUSH_API WINAPI ProcPush_InitRes();

//功能：释放资源函数
//参数说明：
//返回值：
//0 成功 
//其他 失败
void KSPROCPUSH_API WINAPI ProcPush_FreeRes();

//功能：设置控制消息函数
//参数说明：
//nCount[输入]:控制消息个数
//ControlReq[输入]:控制消息数组
//返回值：
//0 成功 
//其他 失败
int KSPROCPUSH_API WINAPI ProcPush_SetControlReqTypes(int nCount,unsigned int *ControlReq);

//功能：判断是否为有效推送数据函数
//参数说明：
//recvpack[输入]:接收到的数据缓冲(ST_CPACK格式)
//返回值：
//0 有效数据 
//其他 无效数据
int KSPROCPUSH_API WINAPI ProcPush_CheckValidPushData(char* recvpack);

#ifdef __cplusplus
}
#endif

#endif