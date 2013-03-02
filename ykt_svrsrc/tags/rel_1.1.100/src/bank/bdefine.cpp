// BDefine.cpp: implementation of the TBDefine class.
//
//////////////////////////////////////////////////////////////////////
//#define _DEBUG1    // Ϊ���ڴ�����Ҫ
#ifdef _DEBUG1
#include "afx.h"
#endif

#include "stdafx.h"
#include "bdefine.h"
#include "logfile.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "bdfunc.inc"  // �������ÿ��д��̨����ʹ�ø��Ե��ļ���һֱ���ܼ��ɵ�ʱ��ͳһ��һ���ļ�����

// ������: FTestIReply
// ���  : ������ 2004-3-8 14:21:58
// ����  : ������Ӧ�ٶȲ��ԣ����ڲ��Կ�������Ӧ
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rPack
// ����  : int *iRetCode
// ����  : char *szMsg
#include "svrlink.h"
extern CSvrLink g_SvrLink;  // ��ҵ��������ĵ�����
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
   ����pArrays�� Ϊ���ܹ����մ���������¼�����
*/
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg)
{
   int rtn;
#ifdef _DEBUG1
CMemoryState cm1, cm2, cm3;
#endif
   APPFUNC pFunc = g_BDefines[fno].pFunc;

#ifdef _DEBUG1
	cm1.Checkpoint();
#endif
 	 rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
	if(rtn)
	{
		int r=0;
	   	char sErrMsg[60]="";
	   	char sOutMsg[256]="";
		if(strlen(szMsg))
			snprintf(sOutMsg,256,"\t[%s]",szMsg);
		get_errcode_msg(*iRetCode, sErrMsg);
		snprintf(szMsg,256,"%s%s",sErrMsg,sOutMsg);
		r=db_rollback();
		if(r)
		{
			writelog(LOG_ERR,"rollback err[%d]",r);
			snprintf(szMsg,256,"%s���ݿ�����ع�ʧ��",szMsg);				
		}
		ERR_DEAL(szMsg,*iRetCode);
	}
	else
	{
		int r=0;
		r=db_commit();
		if(r)
		{
			rtn=r;
			writelog(LOG_ERR,"commit err[%d]",r);
			snprintf(szMsg,256,"%s���ݿ������ύʧ��",szMsg);	
			r=db_rollback();
			if(r)
			{
				writelog(LOG_ERR,"rollback err[%d]",r);
				snprintf(szMsg,256,"%s���ݿ�����ع�ʧ��",szMsg);				
			}
			ERR_DEAL( szMsg,*iRetCode);
		}
	}

#ifdef _DEBUG1
	cm2.Checkpoint();
	if (cm3.Difference(cm1, cm2))
   {
      BCCMsgLogOut(14444,"��ִ�й��ܺ�:%uʱ�򣬾���飬�ڴ���ִ���!",rpack->head.RequestType);
      g_LogFile.WriteLogEx(14444,"��ִ�й��ܺ�:%uʱ�򣬾���飬�ڴ���ִ���!",rpack->head.RequestType);
		cm3.DumpStatistics();
   }
#endif 
   
   if (g_BUnit.m_SqlDB.lErrorCode<=-10000)  // ����SQL�Ƚ����صĴ���
   {
      if (SQLIsConnectOK()==0)
      {
         SQLDisconnect();
      }
      g_BUnit.m_SqlDB.lErrorCode = 0;
   }
   return(rtn);
}

// ������: ResetBPFunctions
// ���  : ������ 2004-2-11 22:40:49
// ����  : ���ù��ܱ��еĲ���
// ����  : int :�ǼǵĹ��ܸ���
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


// ������: ListBPFunctions
// ���  : ������ 2004-2-11 22:41:18
// ����  : ��ʾ���ܱ��е�ͳ�ƻ򵼳����ļ���
// ����  : int �ǼǵĹ��ܸ���
// ����  : char *bpfile �� NULL �� ����������Ļ����ʾ�����򵼳���ָ���ļ���
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


// ������: FindBPFunction
// ���  : ������ 2004-2-11 22:50:46
// ����  : ���ݹ��ܺţ���ѯ��Ӧ�Ĺ��ܱ���
// ����  : int <0:û���ҵ���>=0:�ڹ��ܱ��ж�Ӧ�����
// ����  : unsigned int reqtype �����ܺ�
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

