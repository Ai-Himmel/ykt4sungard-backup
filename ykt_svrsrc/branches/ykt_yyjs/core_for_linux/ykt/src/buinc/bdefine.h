/********************************************************************
	created:	2004/02/11
	created:	11:2:2004   14:15
	filename: 	E:\proj\goldmem\gmsvrall\BDefine.h
	file path:	E:\proj\goldmem\gmsvrall
	file base:	BDefine
	file ext:	h
	author:		CHENYH
	
	purpose:	本模块用于定义具体的业务处理功能表，包括g_BDefines
*********************************************************************/
// BDefine.h: interface for the TBDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)
#define AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cxpack.h"
#include "bupub.h"
#include "comstru.h"
#include "svrlink.h"
#include "logfile.h"

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

// 所有业务处理过程：
// 返回  : int 0 表示成功处理，其他作为处理失败
// 参数  : TRUSERID *handle 本请求数据的通讯请求端标识
// 参数  : ST_PACK *rPack 业务处理请求数据
// 参数  : int *iRetCode 处理结果的返回代码，0表示成功，其他就是处理失败，在本业务处理函数调用之前，已经被初始化为0
// 参数  : char *szMsg 处理结果的返回信息，在本业务处理函数调用之前，已经被初始化为空""
typedef int (* APPFUNC)(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg); 

#define INSERT_FUNCTION(funcno,func,comment,coder,pr) {funcno,func,comment,coder,pr,false,0,0,0,0,0},

typedef struct 
{
   unsigned int RequestType;  // 请求功能号
   APPFUNC  pFunc;            // 本功能函数指针，即调用入口地址
   char szRTName[80];         // 本功能业务名称
   char szProgrammer[20];     // 编程人员名
   int  iPriority;            // 优先级 目前分为1,2,3 自高到低
                              /* 同时也决定其处理的优先级
                                           1 - 交易类（会修改数据的请求）或 关键查询业务 ...
                                           2 - 单笔返回数据查询
                                           3 - 多笔返回数据查询
                              */
   bool bStoped;              // 是否暂时停止本业务
   unsigned int nSuccess;     // 处理成功次数
   unsigned int nFail;        // 处理失败次数
   double       dTakentime;   // 处理成功累计时间 以毫秒计，用于测试在本BCC下该业务的处理速度
   unsigned int nTt_max;      // 最大处理时间
   unsigned int nTt_min;      // 最小处理时间
} TBDefine;

extern TBDefine *g_BDefines;


// 编程  : 陈永华 2006-3-3 11:54:01
// 描述  : 当特殊项目需要自行组织调度功能的时候，需要在BU主框架中，提供该类定义的函数接口
// 返回  : int 
// 参数  : TRUSERID *handle [IN]: 发起请求方的句柄
// 参数  : char *rdata[IN]: 收到请求的数据 （未解压的数据）
// 参数  : int rdlen[IN]: 收到请求数据的长度
// 参数  : int *iRetCode [OUT]: 返回嘛
// 参数  : char *szMsg
typedef int (*XPROCESS_M)(TRUSERID *handle,char *rdata,int rdlen,int *iRetCode, char *szMsg);
extern XPROCESS_M pProcess;

typedef int (*XCALLBDFUNC_M)(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);
extern XCALLBDFUNC_M pCallBDFunc;
typedef int (*XWRITEAPPFUNC)(int bccBaseFuncNo,int bccID);
extern XWRITEAPPFUNC pWriteAppInfo;


/******* Updated by CHENYH at 2005-11-6 12:38:32 *******/
// 下面两个函数必须由主体程序实现：
// 然后通过
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);

// 函数名: WriteAppInfo
// 编程  : 陈永华 2004-3-22 15:34:38
// 描述  : BCC向第一个连接好的BU发起的一个刷新后台的请求，以便业务模块部分能够作相关处理
// 返回  : int 
// 参数  : int bccBaseFuncNo
// 参数  : int bccID
int WriteAppInfo(int bccBaseFuncNo,int bccID);
/*******************************************************/

// 函数名: ResetBPFunctions
// 编程  : 陈永华 2004-2-11 22:40:49
// 描述  : 重置功能表中的参数
// 返回  : int :登记的功能个数
BUPUB_API int ResetBPFunctions();


// 函数名: ListBPFunctions
// 编程  : 陈永华 2004-2-11 22:41:18
// 描述  : 显示功能表中的统计或导出到文件中
// 返回  : int 登记的功能个数
// 参数  : char *bpfile ： NULL 或 “”则在屏幕上显示，否则导出到指定文件中
BUPUB_API int ListBPFunctions(char *bpfile);


// 函数名: FindBPFunction
// 编程  : 陈永华 2004-2-11 22:50:46
// 描述  : 根据功能号，查询对应的功能表项
// 返回  : int <0:没有找到；>=0:在功能表中对应的序号
// 参数  : unsigned int reqtype ：功能号
BUPUB_API int FindBPFunction(unsigned int reqtype);


#ifdef __cplusplus
}
#endif

// 函数名: BUPubInitialize
// 编程  : 陈永华 2005-11-6 12:43:26
// 描述  : 通过本初试化，以便主体程序能够正常使用BUPub库
// 返回  : CSvrLink *: 返回bupub共享库内部中的一个原始实例
// 参数  : TBDefine *pBDefine － 主体程序提供的功能列表清单
// 参数  : XCALLBDFUNC_M pCallFunc － 主体程序提供的CallBDFunc的指针, 如果不用这种方式，而用XPROCESS_M方式提供功能调度的话，则这里可以设为NULL
// 参数  : XWRITEAPPFUNC pWriteApp － 主体程序提供的WriteAppInfo的函数指针
// 参数  : CLogFile *pLogFile - 本程序的主文本日志实例指针
// 参数  : XPROCESS_M process - 主体程序提供的另外一种功能调用的方式，这个时候本类不检查功能号，需要process内部处理一些相关的工作。
//                               当不用这种调用方式的话, 而用XALLBDFUNC_M方式，这里就该设置为NULL
BUPUB_API CSvrLink *BUPubInitialize(TBDefine *pBDefine,XCALLBDFUNC_M pCallFunc,XWRITEAPPFUNC pWriteApp,CLogFile *pLogFile,XPROCESS_M process=NULL);

#undef BUPUB_API

#endif // !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)
