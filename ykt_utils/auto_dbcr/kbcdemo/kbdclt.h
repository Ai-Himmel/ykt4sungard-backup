/********************************************************************
	created:	2006/12/29
	created:	29:12:2006   11:17
	filename: 	D:\proj\ksbass\bcclink\kbdclt\kbdclt.h
	file path:	D:\proj\ksbass\bcclink\kbdclt
	file base:	kbdclt
	file ext:	h
	author:		CHENYH
	
	purpose:	根据证券接口部要求，为了能够给第三方提供用于和KSMBASS架构以客户方式进行通讯，而创建的接口库。
         本客户端接口只能处理单类的应用服务器（即一个公共功能号）
         本客户端句柄KBDCHandle为非线程安全，即大部分操作，尽量只在一个线程上使用
*********************************************************************/
#ifndef KBDCLT_H 
#define KBDCLT_H

#define MAXFVLEN  1024   // 在KBDCGetFieldValue中fieldvalue预分配的字节数

#ifdef KBDCLT_EXPORTS
#define KBDCLT_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define KBDCLT_API __declspec(dllimport)
#else
#define KBDCLT_API 
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif
typedef void * KBDCHandle;


// 函数名: KBDCGetLocalLicensePair
// 编程  : 陈永华 2006-12-29 17:54:54
// 描述  : 为了给客户端程序的帮助页面显示本地安装的授权号的申请码
// 参数  : unsigned int *p1 [OUT]: 返回本地安装授权的申请码1
// 参数  : unsigned int *p2 [OUT]: 返回本地安装授权的申请码2
KBDCLT_API void KBDCGetLocalLicensePair(unsigned int *p1, unsigned int *p2);


// 函数名: KBDCInit
// 编程  : 陈永华 2006-12-29 11:37:21
// 描述  : 客户接口库初试化
// 返回  : int 0 － 成功；<0: 各种失败类型
// 参数  : int debug [IN]: 0 － 不要调试信息； !=0 - 打开调试跟踪文件
// 参数  : const char *license [IN]: 授权号，需要向Kingstar申请授权号
// 参数  : char *eMsg [OUT]：当返回不为 0 的时候，返回的错误信息； 调用方预选分配1024字节空间
KBDCLT_API int KBDCInit(int debug, const char *license, char *eMsg);


// 函数名: KBDCExit
// 编程  : 陈永华 2006-12-29 13:16:48
// 描述  : 退出接口库
// 返回  : void 
KBDCLT_API void KBDCExit();


// 函数名: NewKBDCHandle
// 编程  : 陈永华 2006-12-29 13:19:29
// 描述  : 获取客户端接口句柄
// 返回  : KBDCHandle : NULL - 失败；否则 - 成功
// 参数  : char *eMsg ：当失败返回的时候，返回错误信息； 调用方预选分配1024字节空间
KBDCLT_API KBDCHandle KBDCNewHandle(char *eMsg);


// 函数名: DeleteKBDCHandle
// 编程  : 陈永华 2006-12-29 13:22:43
// 描述  : 释放客户端接口句柄
// 返回  : void 
// 参数  : KBDCHandle *chandle : 通过NewKBDCHandle获得的客户端接口句柄
KBDCLT_API void KBDCDeleteHandle(KBDCHandle chandle);


// 函数名: KBDCBeginRequest
// 编程  : 陈永华 2006-12-29 13:28:14
// 描述  : 准备一个请求
// 返回  : int : 0 成功；<0 失败
// 参数  : KBDCHandle chandle [IN]: 通过NewKBDCHandle获得的客户端接口句柄
// 参数  : int reqno [IN]: 请求的功能号
// 参数  : char *eMsg [OUT]: 当失败返回的时候，返回错误信息； 调用方预选分配1024字节空间
KBDCLT_API int KBDCBeginRequest(KBDCHandle chandle, int reqno, char *eMsg);


// 函数名: KBDCSetFieldValue
// 编程  : 陈永华 2006-12-29 15:18:38
// 描述  : 设置请求数据中的指定字段值
// 返回  : int : 0 成功；<0 失败
// 参数  : KBDCHandle chandle [IN]: 已经调用了KBDCBeginRequest的客户端接口句柄
// 参数  : const char *fieldname [IN]: 指定的字段名，如vsmess
// 参数  : const char *fieldvalue [IN]: 指定该字段的值，用字符串表示
KBDCLT_API int KBDCSetFieldValue(KBDCHandle chandle, const char *fieldname,const char *fieldvalue);


// 函数名: KBDCCallSvr
// 编程  : 陈永华 2006-12-29 15:54:57
// 描述  : 将上述设置准备好的请求发送给服务器端，等待服务端的应答返回
// 返回  : int : >=0 成功； <0 失败，返回错误码
// 参数  : KBDCHandle chandle [IN]: 通过NewKBDCHandle获得的客户端接口句柄，并且已经通过KBDCBeginRequest和KBDCSetFieldValue
//         准备好了请求数据
// 参数  : int waittime [IN]: 等待应答的时间，毫秒计
// 参数  : char *eMsg [OUT]:  当失败返回的时候，返回错误信息； 调用方预选分配1024字节空间
KBDCLT_API int KBDCCallSvr(KBDCHandle chandle, int waittime, char *eMsg);


// 函数名: KBDCGetRetCode
// 编程  : 陈永华 2006-12-29 16:00:54
// 描述  : 获取KBDCCallSvr后的服务端返回的返回码
// 返回  : int : >=0 返回的返回码，在调用KBDCCallSvr成功后获取；<0: 错误 
// 参数  : KBDCHandle chandle [IN]: 操作的客户端接口句柄
KBDCLT_API int KBDCGetRetCode(KBDCHandle chandle);


// 函数名: KBDCNextRetRecord
// 编程  : 陈永华 2006-12-29 16:04:49
// 描述  : 在调用KBDCCallSvr后，缺省的返回记录序号为0，如果用KBDCGetFieldValue读下一条记录中的内容，则需要调用本函数
// 返回  : int : >=0 成功，即内部一个值；<0 失败，(-1)表示没有下一条记录了，或其他原因
// 参数  : KBDCHandle chandle [IN]: 操作的客户端接口句柄
// 参数  : char *eMsg [OUT]:  当失败返回的时候，返回错误信息； 调用方预选分配1024字节空间
KBDCLT_API int KBDCNextRetRecord(KBDCHandle chandle, char *eMsg);


// 函数名: KBDCGetFieldValue
// 编程  : 陈永华 2006-12-29 16:09:29
// 描述  : 取当前记录中的各个字段的值
// 返回  : int : >=0 成功；<0 失败，表示错误码
// 参数  : KBDCHandle chandle [IN]: 操作的客户端接口句柄
// 参数  : const char *fieldname [IN]: 指定取值的字段名，如vsmess
// 参数  : char *fieldvalue [OUT]: 返回的字段值， 调用方预选分配1024字节空间
// 参数  : char *eMsg [OUT]:  当失败返回的时候，返回错误信息； 调用方预选分配1024字节空间
KBDCLT_API int KBDCGetFieldValue(KBDCHandle chandle, const char *fieldname, char *fieldvalue, char *eMsg);


#ifdef __cplusplus
}
#endif

#undef KBDCLT_API

#endif
