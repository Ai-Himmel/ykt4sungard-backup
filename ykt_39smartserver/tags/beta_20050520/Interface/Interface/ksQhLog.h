
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSQHLOG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSQHLOG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef __KSQHLOG_H
#define __KSQHLOG_H

#include "log.h"
#include "cpack.h"
const	int	LOG_APPCPACKCID				= 12;
const	char	LOG_APPCPACKCNAME[LOG_APPMAXNAME]	= "CPACKC包日志";

#ifdef _DEBUG
#pragma comment(lib,"../lib/KSLOGd.lib")
#pragma message("Automatically Linking KSLOGd.dll")
#else
#pragma comment(lib,"../lib/KSLOG.lib")
#pragma message("Automatically Linking KSLOG.dll")
#endif

#ifdef KSQHLOG_EXPORTS
#define KSQHLOG_API __declspec(dllexport)
#else
#define KSQHLOG_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksQhLogd.lib")
#pragma message("Automatically Linking ksQhLogd.dll")
#else
#pragma comment(lib,"../lib/ksQhLog.lib")
#pragma message("Automatically Linking ksQhLog.dll")
#endif
#endif

// This class is exported from the ksQhLog.dll
class KSQHLOG_API CKsQhLog : public CLog{
public:
	BOOL WriteDataWithCPackArray(ST_CPACK *pPack,ST_PACK *pArray,LPCSTR pszPackHint="CPACKC数据包");
	BOOL WriteDataWithCPack(ST_CPACK *pPack,LPCSTR pszPackHint="CPACKC数据包");
	BOOL WritePackC(void *pBuf, int nBufLen, LPCSTR pszPackHint="CPACKC数据包");
	CKsQhLog(void);
	virtual ~CKsQhLog();
	// TODO: add your methods here.
};
#ifdef __cplusplus
extern "C" {
#endif
//日志初始化函数
//输入参数：
//szAppName:应用程序的英文简称，生成的日志文件名称为szAppName+YYYYMMDD.klg
//szLogFilePath:日志文件的目录，如果目录不存在能够自动生成
//nFileHoldCount:日志目录下保留的日志文件个数，如果为0，则无限
//返回
//TRUE:成功
//FALSE:失败
BOOL KSQHLOG_API WINAPI AppLogInit(char *szAppName,char *szLogFilePath,int nFileHoldCount=0);

//记录字符串日志
//输入参数：
//szLogContent:字符串信息
//返回
//TRUE:成功
//FALSE:失败
BOOL KSQHLOG_API WINAPI AppWriteLog(char *szLogContent);

//记录cpack包日志
//输入参数：
//pBuf:cpack包压缩后的缓冲
//nBufLen:缓冲大小
//szPackHint:这个cpack包的描述
//返回
//TRUE:成功
//FALSE:失败
BOOL KSQHLOG_API WINAPI AppWriteCommPack(void *pBuf, int nBufLen, char *szPackHint="通讯包数据");

//记录cpack包日志-非压缩方式-单记录方式
//输入参数：
//pPack:cpack包指针
//szPackHint:这个cpack包的描述
//返回：
//TRUE:成功
//FALSE:失败
BOOL KSQHLOG_API WINAPI AppWriteDataWithCPack(ST_CPACK *pPack, LPCSTR szPackHint="CPACKC数据包");

//记录cpack包日志-非压缩方式-多记录方式
//输入参数：
//pPack:cpack包指针
//pArray:后续纪录包体指针
//szPackHint:这个cpack包的描述
//返回：
//TRUE:成功
//FALSE:失败
BOOL KSQHLOG_API WINAPI AppWriteDataWithCPackArray(ST_CPACK *pPack, ST_PACK *pArray, LPCSTR szPackHint="CPACKC数据包");

//关闭日志函数
//返回
//TRUE:成功
//FALSE:失败
BOOL KSQHLOG_API WINAPI AppLogClose();
#ifdef __cplusplus
}
#endif
#endif
