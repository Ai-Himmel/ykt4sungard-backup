/********************************************************************
	created:	2005/08/23
	created:	23:8:2005   16:32
	filename: 	D:\proj\ksbass\bankbu\bdefine.cpp
	file path:	D:\proj\ksbass\bankbu
	file base:	bdefine
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 2005-8-23 16:32:43 为了提高功能入口检索速度，改为排序后采用二分法
            快速定位功能定义项
*********************************************************************/
// BDefine.cpp: implementation of the TBDefine class.
//
//////////////////////////////////////////////////////////////////////
//#define _DEBUG1    // 为了内存检查需要

#include "stdafx.h"
#include <stdlib.h>  // for qsort
#include "bdefine.h"
#include "logfile.h"
#include "mypub.h"
#include "svrlink.h"
#include "cxpack.h"
extern CSvrLink g_SvrLink;  // 与业务调度中心的连接
extern CLogFile *g_pLogFile;

TBDefine *g_BDefines;

XPROCESS_M pProcess=NULL;
XCALLBDFUNC_M pCallBDFunc=NULL;
XWRITEAPPFUNC pWriteAppInfo=NULL;


CSvrLink *BUPubInitialize(TBDefine *pBDefine,XCALLBDFUNC_M pCallFunc,XWRITEAPPFUNC pWriteApp,CLogFile *pLogFile,XPROCESS_M process)
{
   g_BDefines = pBDefine;
   pCallBDFunc = pCallFunc;
   pWriteAppInfo = pWriteApp;
   g_pLogFile = pLogFile;
   pProcess = process;
   return(&g_SvrLink);
}



static int nBPFunctions=0;
int BPFComp(const void *t1,const void *t2)
{
   if (((TBDefine *)t1)->RequestType>((TBDefine *)t2)->RequestType)
      return(1);
   if (((TBDefine *)t1)->RequestType==((TBDefine *)t2)->RequestType)
      return(0);
   else return(-1);
}


// 函数名: ResetBPFunctions
// 编程  : 陈永华 2004-2-11 22:40:49
// 描述  : 重置功能表中的参数
// 返回  : int :登记的功能个数
int ResetBPFunctions()
{
   int i;
   TBDefine *pbd=g_BDefines;
   for (i=0;;i++,pbd++)
   {
      if (pbd->RequestType==0)
         break;

/* ****** Updated by CHENYH at 2004-2-17 17:29:32 ****** 
      if (pbd->iPriority<1)
         pbd->iPriority = 1;
      else if (pbd->iPriority>3)
         pbd->iPriority = 3;
*/
      pbd->bStoped = false;
      pbd->nSuccess = pbd->nFail = pbd->nTt_max = pbd->nTt_min = 0;
      pbd->dTakentime = 0;
   }
   nBPFunctions = i;
   qsort(g_BDefines,nBPFunctions,sizeof(TBDefine),BPFComp);
   return(i);
}


// 函数名: ListBPFunctions
// 编程  : 陈永华 2004-2-11 22:41:18
// 描述  : 显示功能表中的统计或导出到文件中
// 返回  : int 登记的功能个数
// 参数  : char *bpfile ： NULL 或 “”则在屏幕上显示，否则导出到指定文件中
int ListBPFunctions(char *bpfile)
{
   int i;
   TBDefine *pbd=g_BDefines;
   FILE *fp=NULL;
   if (bpfile!=NULL && bpfile[0]!='\0')
   {
      fp = fopen(bpfile,"wt");
   }
   if (fp==NULL)
   {
      //      12345678901234567890123456789012345678901234567890123456789012345678901234567890
      //      123456 12345 1234 1234567890 1234567890 123456789012345 123456 123456
      printf("funcno|class|stop|   success|   failure|           time| t_max| t_min\n");
   }
   for (i=0;;i++,pbd++)
   {
      if (pbd->RequestType==0)
         break;
      if (fp==NULL)
      {
         printf("%6u|%5d|   %c|%10u|%10u|%15.0lf|%6u|%6u\n",
            pbd->RequestType,
            pbd->iPriority,
            pbd->bStoped?'N':'Y',
            pbd->nSuccess,
            pbd->nFail,
            pbd->dTakentime,
            pbd->nTt_max,
            pbd->nTt_min
            );
      }
      else
      {
         fprintf(fp,"%u|%s|%s|%d|%c|%u|%u|%.0lf|%u|%u\n",
            pbd->RequestType,
            pbd->szRTName,
            pbd->szProgrammer,
            pbd->iPriority,
            pbd->bStoped?'N':'Y',
            pbd->nSuccess,
            pbd->nFail,
            pbd->dTakentime,
            pbd->nTt_max,
            pbd->nTt_min
            );
      }
   }
   if (fp!=NULL)
      fclose(fp);
   return(i);
}


// 函数名: FindBPFunction
// 编程  : 陈永华 2004-2-11 22:50:46
// 描述  : 根据功能号，查询对应的功能表项
// 返回  : int <0:没有找到；>=0:在功能表中对应的序号
// 参数  : unsigned int reqtype ：功能号
int FindBPFunction(unsigned int reqtype)
{
   int i,l,r;
   if (reqtype==0)
      return(-10);
   l = 0;
   if (g_BDefines[l].RequestType==reqtype)
      return(l);
   if (g_BDefines[l].RequestType>reqtype)
      return(-3);
   r = nBPFunctions-1;
   if (g_BDefines[r].RequestType==reqtype)
      return(r);
   if (g_BDefines[r].RequestType<reqtype)
      return(-2);
   while (r>l+1)
   {
      i = (l+r)>>1;
      if (g_BDefines[i].RequestType==reqtype)
         return(i);
      if (g_BDefines[i].RequestType>reqtype)
      {
         r = i-1;
         if (g_BDefines[r].RequestType==reqtype)
            return(r);
      }
      else
      {
         l = i+1;
         if (g_BDefines[l].RequestType==reqtype)
            return(l);
      }
   }

/* ****** Updated by CHENYH at 2005-8-23 16:40:01 ****** 
   // 在这里改用二分法检索：
   for (i=0;;i++)
   {
      if (g_BDefines[i].RequestType==0)
         break;
      if (g_BDefines[i].RequestType==reqtype)
         return(i);
   }
*******************************************************/
   return(-1);
}

