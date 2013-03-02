/********************************************************************
	created:	2004/02/11
	created:	11:2:2004   14:15
	filename: 	E:\proj\goldmem\fdsvrall\BDefine.h
	file path:	E:\proj\goldmem\fdsvrall
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

#include "fdsqc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#ifdef __cplusplus
}
#endif

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

extern TBDefine g_BDefines[];


/* ****** Updated by CHENYH at 2004-4-9 10:06:44 ****** 
   增加pArrays： 为了能够接收处理多请求记录的情况
*/
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);

// 函数名: ResetBPFunctions
// 编程  : 陈永华 2004-2-11 22:40:49
// 描述  : 重置功能表中的参数
// 返回  : int :登记的功能个数
int ResetBPFunctions();


// 函数名: ListBPFunctions
// 编程  : 陈永华 2004-2-11 22:41:18
// 描述  : 显示功能表中的统计或导出到文件中
// 返回  : int 登记的功能个数
// 参数  : char *bpfile ： NULL 或 “”则在屏幕上显示，否则导出到指定文件中
int ListBPFunctions(char *bpfile);


// 函数名: FindBPFunction
// 编程  : 陈永华 2004-2-11 22:50:46
// 描述  : 根据功能号，查询对应的功能表项
// 返回  : int <0:没有找到；>=0:在功能表中对应的序号
// 参数  : unsigned int reqtype ：功能号
int FindBPFunction(unsigned int reqtype);

#endif // !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)
