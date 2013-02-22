#ifndef DRTPAPI_DLL_HEADER_1
#define DRTPAPI_DLL_HEADER_1


#if !defined(WIN32)
	#define __stdcall
	#include "mytypes.h"
#endif

//////////////////网络事件掩码////////////////////////////
#define DRTP_READ		1
#define DRTP_WRITE		2
#define DRTP_EXCEPT		4
//////////////////////////////////////////////////////////
extern "C" BOOL __stdcall DRTPInitialize();
/*
	功能：初始化。
	参数：无。
	返回值：如果初始化成功，返回TRUE，否则返回FALSE。
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" BOOL __stdcall DRTPUninitialize();
/*
	功能：释放资源
	参数：无。
	返回值：如果取消初始化成功，返回TRUE，否则返回FALSE
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" int __stdcall DRTPGetHost (char*  strIP,WORD* pwPort,WORD wGatewayNo=0,WORD wBroadcastPort=1976,DWORD dwTimeout=5000);
/*
	功能：查找相应编号的路由通讯服务器的IP和端口号
	参数：
		strIP[OUT]:保存路由通讯服务器的IP,由用户分配该空间
		pwPort[OUT]:保存路由通讯服务器的端口号,由用户分配该空间
		wGatewayNo[IN]:被查询的路由通讯服务器的编号
		wBroadcastPort[IN]:广播端口号
		dwTimeout[IN]:超时
	返回值：找到则返回相应的路由通讯服务器编码，否则返回-1
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" HANDLE __stdcall DRTPConnect (LPCTSTR strIP,WORD wPort,WORD Encode);
/*
	功能：建立与路由通讯服务器的连接
	参数：
		strIP[IN]:路由通讯服务器的IP地址
		wpPort[IN]:路由通讯服务器的端口号
		Encode[IN]:加密方式
	返回值：如果连接成功，返回新建连接的句柄，否则返回NULL。
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" BOOL __stdcall DRTPClose (HANDLE hConnection);
/*
	功能：关闭与路由通讯服务器的连接
	参数：
		hConnection[IN]:由DRTPConnect返回的HANDLE
	返回值：如果关闭成功，返回TRUE，否则返回FALSE。
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" BOOL __stdcall DRTPSend (HANDLE hConnection,WORD wDestNo,WORD wFunction, char * pSendData,int iLen,BYTE byFunctionPriority,bool Designed=false);
/*
	功能：发送请求\应答数据
	参数：
		hConnection[in]：连接句柄。调用DRTPConnect时返回。
		dwDestNo [in]：接收方代码。如果调用者为服务端则忽略本参数。
		dwMainFunction [in]：接收方主功能号。如果调用者为服务端则忽略本参数。
		pSendData [in]：发送缓冲区。
		iLen[in]：待发送的字节数。
		ByFunctionPriority[in]：功能号优先级。
								//1为优先级高于标准
								//2为标准优先级
								//3为优先级低于标准
		Designed[IN]:指定路由标记
								//true为指定路由
								//false为非指定路由
	返回值：如果发送成功，返回TRUE，否则返回FALSE。
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" int __stdcall DRTPReceive(HANDLE hConnection,char * recvBuffer,int iBufferSize,DWORD dwTimeout= 0);
/*
	功能：接收数据。
	参数：
		hConnection[in]：连接句柄。调用DRTPConnect时返回。
		recvBuffer [out]：接收缓冲区，最小4096字节。
		iBufferSize[in]：接收缓冲区字节数。
		dwTimeout [in]：接收超时。如果为0，则为阻塞方式。
	返回值：
		接收成功，返回接收到的字节数；
		接收超时，否则0；
		接收失败，返回-1
		路由通讯服务器返回信息，返回值为 -4，可以用DRTPGetLastError()来取得
		相应的信息（字符串）

	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" BOOL __stdcall DRTPCheckNetState (HANDLE hConnection,DWORD dwTimeout=2000);
/*
	功能：检查网络连接状态。
	参数：
		hConnection[in]：连接句柄。调用DRTPConnect时返回。
		dwTimeout[in]：检测超时（毫秒）。0为Block方式。
	返回值：如果连接正常，返回值大于0，否则值小于0，如果检测超时，返回0。
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" BOOL __stdcall DRTPCheckDataArrived (HANDLE hConnection,DWORD dwTimeout=0);
/*
	功能：检查特定连接上是否有数据尚未接收。
	参数：
		hConnection[in]：连接句柄。调用DRTPConnect时返回。
		dwTimeout[in]：检测时间（毫秒）。0为Block方式。
	返回值：如果有未接收数据，返回TRUE，否则返回FALSE。 
	修改者：吴舸 20010404
	修改原因：规范编码
*/
extern "C" int __stdcall DRTPGetLastError(HANDLE hConnection,char* ErrorMsgBuffer,int iMsgBufferSize);
/*
	功能：返回特定连接上的错误信息。
	参数：
		hConnection[in]：连接句柄。调用DRTPConnect时返回。
		ErrorMsgBuffer[in]:保存错误信息的缓冲区
		iMsgBufferSize[in]:缓冲区的长度
	返回值：成功返回1，失败返回0
	修改者：吴舸 20010404
	修改原因：规范编码
*/


extern "C" int __stdcall DRTPCloseSocket(HANDLE hConnection);
/*
	功能：关闭SOCKET连接
	参数：
		hConnection[in]：连接句柄。调用DRTPConnect时返回。
	返回值：成功返回1，失败返回0
*/



#endif