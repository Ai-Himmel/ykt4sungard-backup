// BDefine.cpp: implementation of the TBDefine class.
//
//////////////////////////////////////////////////////////////////////
//#define _DEBUG1    // 为了内存检查需要
#ifdef _DEBUG1
#include "afx.h"
#endif

#include "stdafx.h"
#include "bdefine.h"
#include "logfile.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "bdfunc.inc"  // 这里就是每个写后台的人使用各自的文件，一直到总集成的时候，统一成一个文件即可

// 函数名: FTestIReply
// 编程  : 陈永华 2004-3-8 14:21:58
// 描述  : 最快的相应速度测试，用于测试框架最快响应
// 返回  : int
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rPack
// 参数  : int *iRetCode
// 参数  : char *szMsg
#include "svrlink.h"
extern CSvrLink g_SvrLink;  // 与业务调度中心的连接
extern CLogFile g_LogFile;
int FTestIReply(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg)
{
   unsigned char *pb;
   pb = g_SvrLink.head.ParmBits;
   g_SvrLink.SetCol(handle,pb);
   PutRow(handle,rPack,iRetCode,szMsg);
   AnswerData(handle,*iRetCode,szMsg);
   return(0);
}



/* ****** Updated by CHENYH at 2004-4-9 10:06:44 ******
   增加pArrays： 为了能够接收处理多请求记录的情况
*/
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg)
{
   int r=0;
   int rtn=0;
   int sendtype=0;
   char param[101]="";
#ifdef _DEBUG1
CMemoryState cm1, cm2, cm3;
#endif
   APPFUNC pFunc = g_BDefines[fno].pFunc;

#ifdef _DEBUG1
	cm1.Checkpoint();
#endif
	*iRetCode=0;
	*szMsg=0;
	//判断是否是结帐时刻,如果是则等待处理
	sendtype=rpack->head.RequestType/10000;
	switch(sendtype)
       {
		case 93:
		case 95:
			rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
			break;
		default:
		 	rtn=GetSysParaVal(GLOBE_FLAG_BALANCE,param);
			if(rtn)
			{
				*iRetCode=rtn;
				break;
			}
			else if(strncmp(param,"0",1)!=0)
			{
				rtn=E_DAYEND_STATUS;
				*iRetCode=rtn;
				break;
			}
			rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
	              break;
       }
	if(rtn)
	{
	   	char sErrMsg[101]="";
		char sRetMsg[256]="";
		if(*szMsg)
			snprintf(sRetMsg,256," %s",szMsg);
		r=get_errcode_msg(*iRetCode, sErrMsg);
		db_rollback();
		snprintf(szMsg,256,"%s%s",sErrMsg,sRetMsg);
		writelog(LOG_ERR,"Func[%d]ecode[%d]msg[%s]",rpack->head.RequestType,*iRetCode,szMsg);
		ERR_DEAL(szMsg,*iRetCode);
		if(r)
		{
			AnswerData(handle,*iRetCode,szMsg);
			db_disconnect();
			writelog(LOG_ERR,"数据库错误,系统退出");
			exit(1);
		}
	}
	else
	{
		r=db_commit();
		if(r)
		{
			*iRetCode=E_DB_COMMIT;
			strcpy(szMsg,"数据库事务提交失败");
			writelog(LOG_ERR,"Func[%d]Msg[%s]",rpack->head.RequestType,szMsg);
			db_rollback();
			ERR_DEAL( szMsg,*iRetCode);
		}
	}
#ifdef _DEBUG1
	cm2.Checkpoint();
	if (cm3.Difference(cm1, cm2))
   {
      BCCMsgLogOut(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
      g_LogFile.WriteLogEx(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
		cm3.DumpStatistics();
   }
#endif

   if (g_BUnit.m_SqlDB.lErrorCode<=-10000)  // 出现SQL比较严重的错误
   {
      if (SQLIsConnectOK()==0)
      {
         SQLDisconnect();
      }
      g_BUnit.m_SqlDB.lErrorCode = 0;
   }
   return(rtn);
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
   int i;
   if (reqtype==0)
      return(-2);
   for (i=0;;i++)
   {
      if (g_BDefines[i].RequestType==0)
         break;
      if (g_BDefines[i].RequestType==reqtype)
         return(i);
   }
   return(-1);
}

