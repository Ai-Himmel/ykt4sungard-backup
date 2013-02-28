
#include "stdafx.h"
#include <stdlib.h>  // for qsort
#include "cpack.h"
#include "bdefine.h"
#include "logfile.h"
#include "mypub.h"
#include "svrlink.h"
#include "XPack.h"
#include "BUShm.h"
#include "bupub.h"
#include "pubfunc.h"

extern CSvrLink *g_pSvrLink;  // 与业务调度中心的连接
extern CLogFile g_LogFile;

//#include "BDFunc.inl"  // 这里就是每个写后台的人使用各自的文件，一直到总集成的时候，统一成一个文件即可

// 函数名: FTestIReply  1010
// 编程  : 陈永华 2004-7-1 9:37:27
// 描述  : 将请求数据原封不动返回给请求端，主要用于测试架构部分的响应速度
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rPack
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestIReply(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg)
{
   ST_PACKHEAD phead;
   g_pSvrLink->GetRequestHead(&phead);
   g_pSvrLink->SetCol(handle,phead.ParmBits);
   PutRow(handle,rPack,iRetCode,szMsg);
   //AnswerData(handle,*iRetCode,szMsg); 按照缺省为AM_AUTO模式下，就不需要本行了
   return(1);
}

// 性能测试：ExtCall(rPack->lvol0,rPack->lvol1,rPack->lvol2,...) 1030
int FPTestExtCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg)
{
   ST_CPACK icpack;
   ST_CPACK icapack;
   ST_PACK icarrays[MAXROW];

   int rtn;
   g_pSvrLink->GetRequestHead(&(icpack.head));
   icpack.head.RequestType = 1010;
   memcpy(&(icpack.pack),rPack,sizeof(ST_PACK));
   rtn = g_pSvrLink->ExtCall(rPack->lvol0,rPack->lvol1,rPack->lvol2,0,5,&icpack,&icapack,icarrays);
   if (rtn>0)
   {
      g_pSvrLink->SetCol(handle,icapack.head.ParmBits);
      g_pSvrLink->PutRowData(&(icapack.pack));
   }
   else
   {
      *iRetCode = 10300-rtn;
      sprintf(szMsg,"ExtCall(%d,%d,%d,...) timeout or Error!",rPack->lvol0,rPack->lvol1,rPack->lvol2);
      g_pSvrLink->Err_Deal(szMsg,*iRetCode);
   }
   return(1);
}

// 性能测试：IntCall(rPack->vsmess,...) RACall(...) 1031
int FPTestIntCall(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg)
{
   ST_CPACK icpack;
   ST_CPACK icapack;
   ST_PACK icarrays[MAXROW];
   int rtn;
   g_pSvrLink->GetRequestHead(&(icpack.head));
   icpack.head.RequestType = 1010;
   memcpy(&(icpack.pack),rPack,sizeof(ST_PACK));
   if (rPack->vsmess[0]=='\0')
   {
      rtn = g_pSvrLink->RACall(5,&icpack,&icapack,icarrays);
   }
   else
   {
      rtn = g_pSvrLink->IntCall(rPack->vsmess,5,&icpack,&icapack,icarrays);
   }
   if (rtn>0)
   {
      g_pSvrLink->SetCol(handle,icapack.head.ParmBits);
      g_pSvrLink->PutRowData(&(icapack.pack));
   }
   else
   {
      *iRetCode = 10300-rtn;
      if ('\0'==rPack->vsmess[0])
         sprintf(szMsg,"RACall(...) timeout or Error");
      else
         sprintf(szMsg,"IntCall(%s,...) timeout or Error!",rPack->vsmess);
      g_pSvrLink->Err_Deal(szMsg,*iRetCode);
   }
   return(1);
}


// 性能测试：ExtTransfer(rPack->lvol1,rPack->lvol2,...) 1032
int FPTestExtTransfer(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg)
{
   ST_CPACK icpack;
   int rtn;
   g_pSvrLink->GetRequestHead(&(icpack.head));
   icpack.head.RequestType = 1010;
   memcpy(&(icpack.pack),rPack,sizeof(ST_PACK));
   rtn = g_pSvrLink->ExtTransfer(rPack->lvol1,rPack->lvol2,&icpack);
   if (rtn<0)
   {
      *iRetCode = 10320-rtn;
      sprintf(szMsg,"ExtTransfer(%d,%d,...) Error!",rPack->lvol1,rPack->lvol2);
      g_pSvrLink->Err_Deal(szMsg,*iRetCode);
   }
   return(1);
}

// 性能测试：IntTransfer(rPack->vsmess,...) RATransfer(...) 1033
int FPTestIntTransfer(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg)
{
   ST_CPACK icpack;
   int rtn;
   g_pSvrLink->GetRequestHead(&(icpack.head));
   icpack.head.RequestType = 1010;
   memcpy(&(icpack.pack),rPack,sizeof(ST_PACK));
   if (rPack->vsmess[0]=='\0')
   {
      rtn = g_pSvrLink->RATransfer(&icpack);
   }
   else
   {
      rtn = g_pSvrLink->IntTransfer(rPack->vsmess,&icpack);
   }
   if (rtn<0)
   {
      *iRetCode = 10330-rtn;
      if ('\0'==rPack->vsmess[0])
         sprintf(szMsg,"RATransfer(...) Error [%d]!",rtn);
      else
         sprintf(szMsg,"IntTransfer(%s,...) Error [%d]!",rPack->vsmess,rtn);
      g_pSvrLink->Err_Deal(szMsg,*iRetCode);
   }
   return(1);
}



int FGetFile(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   char szfile[256];
   int maxlen;
   FILE *fp;
   ST_SDPACK *psd;
   struct stat fst;
   int idx;

   strcpy(szfile,rpack->vsmess);
   maxlen = sizeof(ST_PACK)-4;
   if (maxlen>4000)
      maxlen = 4000;
   fp = sh_fopen(szfile,"rb",SH_DENYNO);
   //g_pSvrLink->SetMaxRow(1);  // 强制单记录返回
   if (fp==NULL)
   {
      sprintf(szMsg,"Cannot open the file:<%s>!",szfile);
      *iRetCode = 9980;
   }
   else
   {
      psd = (ST_SDPACK *)rpack;
	  idx = 0;
      while (!feof(fp))
      {
         psd->usDataLength = fread(psd->data,1,maxlen,fp);
         g_pSvrLink->PutRowData(rpack);
		 writelog(LOG_DEBUG,"answer pack index[%d]",++idx);
      }
      fclose(fp);
      stat(szfile,&fst);
      sprintf(szMsg,"%ld",fst.st_mtime);
      *iRetCode = 1;
   }
   g_pSvrLink->SetCol(handle,F_VSMESS,END_FIELD);
   memcpy(rpack->vsmess,szMsg,sizeof(rpack->vsmess));  // 这里用memcpy代替strcpy，防止内存超界拷贝
   g_pSvrLink->PutRow(handle,rpack,*iRetCode,szMsg);
   return(1);
}

struct T_SHMTest
{
   int m_iSerialNo;  // 开始作为一个序列号
   int m_iBUNumber;  // BU的序号作为最后写的BU的标识
   int m_iBCCID;     // BCC的私有功能号 （bccBFuncNo+bccID）
   char m_szDBlock[1024]; // 作为一个数据块的操作
};

#define SHMTESTNAME "BCCSHMTEST"
int FTestBURunTime(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   // 本功能是为了测试BCC中对BU组中的MAXRUNTIME是否如说明起作用
   int sleeptime=atoi(rpack->vsmess);
   if (sleeptime<=0)
      sleeptime=1;
   g_pSvrLink->SetCol(handle,F_VSMESS,END_FIELD);
   g_pSvrLink->SetMaxRow(1);
   sprintf(rpack->vsmess,"Record on Tick:%u",GetTickCount());
   g_pSvrLink->PutRowData(rpack); // 先返回一条记录
   mysleep(sleeptime*1000);
   sprintf(rpack->vsmess,"Record on Tick:%u",GetTickCount());
   g_pSvrLink->PutRowData(rpack); 
   return(1);
}

// lvol0 - sno; lvol1 - dno; lvol2 - fno; lvol3 - n cpack data
int FTestPushData(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   ST_PACKHEAD phead;
   ST_CPACK pushpack;
   int n = rpack->lvol3;
   g_pSvrLink->GetRequestHead(&phead);
   g_pSvrLink->SetCol(handle,phead.ParmBits);
   PutRow(handle,rpack,iRetCode,szMsg);

   // 将请求数据也推送给另外一个应用服务器去，当然这里只能由BU接收了。
   if (n<1) n = 1;
   g_pSvrLink->GetRequestHead(&(pushpack.head));
   pushpack.head.RequestType = 1010;
   pushpack.head.recCount = 1;
   memcpy(&(pushpack.pack),rpack,sizeof(pushpack.pack));
   for (pushpack.pack.lvol3=0;pushpack.pack.lvol3<n; pushpack.pack.lvol3++)
   {
      g_pSvrLink->PushData(rpack->lvol0,rpack->lvol1,rpack->lvol2,0,&pushpack,PM_ACK,500);
      pushpack.head.RequestType++;
   }
   return(1);
}

int FTestBCCExtTransfer(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   ST_CPACK icpack;
   int rtn;
   CXPack *xpack = (CXPack *)GetDefaultXPack();
   g_pSvrLink->GetRequestHead(&(icpack.head));  // 先从CSvrLink中取得请求包头
   icpack.head.RequestType = 1013;
   icpack.head.recCount = 1;  // 不管原始请求是多记录与否，这里都设定为只有1条请求记录
   AddFieldValue(&icpack,"vsmess","150");  // 1013功能需要的字段值
   // 表示本处理是应该采用Transfer模式转发给另外的BU进行处理的：
   rtn = g_pSvrLink->ExtTransfer(rpack->lvol1,rpack->lvol2,&icpack);
   // 本模式下，本BU不需要返回结果给客户端了。则先关闭自动应答模式：
/* ****** Updated by CHENYH at 2005-9-23 16:17:12 ****** 
   // 在BCC的Transfer功能中已经自动设置了本模式
   g_pSvrLink->SetAnswerMode(AM_CONFIRM);  // 将自动应答模式转换为显式应答模式
*******************************************************/
   // 这样就会因为没有调用PutRow、PutRowData等，不至于会返回一个空记录给客户端而干预正常转发后BU返回结果了
   return(1);
}


int FTestBCCExtCall(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   ST_CPACK icpack;
   unsigned short sno,dno,fno;
   CXPack *xpack = (CXPack *)GetDefaultXPack();
   ST_CPACK icapack;
   ST_PACK icarrays[MAXROW];
   ST_PACK *prec;
   int i,rtn,n;
   //g_pSvrLink->GetRequestHead(&(icpack.head));  // 先从CSvrLink中取得请求包头,以保留各个请求字段原来的值和位图
   g_pSvrLink->ResetNormalCPack(&icpack,0,1);
   icpack.head.RequestType = 1013;
   sno = handle->SourceNo; //rpack->lvol0;
   dno = rpack->lvol1;
   fno = rpack->lvol2;
   AddFieldValue(&icpack,"vsmess","150");  // 1013功能需要的字段值
   rtn = g_pSvrLink->ExtCall(sno,dno,fno,0,5,&icpack,&icapack,icarrays);
   n = 0;
   while (rtn>0)
   {
      prec = &(icapack.pack);
      g_pSvrLink->SetCol(handle,icapack.head.ParmBits);
      for (i=0;i<icapack.head.recCount;i++)
      {
         g_pSvrLink->PutRowData(prec);
         n++;
         prec = icarrays+i;
      }
      if (icapack.head.nextflag!=0)
      {
         rtn = g_pSvrLink->ExtCallNext(5,&icapack,icarrays);
      }
      else break;
   }
   if (rtn<0)
   {
      // -2: 应答返回超时；-1: g_SvrLink与BCC的连接出现问题！
      *iRetCode = 10100-rtn;
      sprintf(szMsg,"ExtCall(%d,%d,%d,...) timeout or Error!",rpack->lvol0,rpack->lvol1,rpack->lvol2);
      g_pSvrLink->Err_Deal(szMsg,*iRetCode);
   }
   return(1);  
}


int FTestBCCIntTransfer(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   char szICBUGroupID[MAXBUGRPID];
   ST_CPACK icpack;
   int rtn;
   CXPack *xpack = (CXPack *)GetDefaultXPack();
   g_pSvrLink->GetRequestHead(&(icpack.head));  // 先从CSvrLink中取得请求包头
   icpack.head.RequestType = 1013;
   icpack.head.recCount = 1;  // 不管原始请求是多记录与否，这里都设定为只有1条请求记录
   strncpy(szICBUGroupID,rpack->vsmess,sizeof(szICBUGroupID));
   AddFieldValue(&icpack,"vsmess","150");  // 1013功能需要的字段值
   // 表示本处理是应该采用Transfer模式转发给另外的BU进行处理的：
   if (szICBUGroupID[0]=='\0')
   {
      rtn = g_pSvrLink->RATransfer(&icpack);
   }
   else
   {
      rtn = g_pSvrLink->IntTransfer(szICBUGroupID,&icpack);
   }
   // 本模式下，本BU不需要返回结果给客户端了。则先关闭自动应答模式：
/* ****** Updated by CHENYH at 2005-9-23 16:17:12 ****** 
   // 在BCC的Transfer功能中已经自动设置了本模式
   g_pSvrLink->SetAnswerMode(AM_CONFIRM);  // 将自动应答模式转换为显式应答模式
*******************************************************/
   // 这样就会因为没有调用PutRow、PutRowData等，不至于会返回一个空记录给客户端而干预正常转发后BU返回结果了
   return(1);
}

// 函数名: FTestBCCIntCall
// 编程  : 陈永华 2005-9-22 11:07:44
// 描述  : 用功能号1013测试BCC的IntCall/IntCallNext、RACall/RACallNext的功能
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack：vsmess=外调的ＢＵ组号，空则调用RACall/RACallNext
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestBCCIntCall(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   char szICBUGroupID[MAXBUGRPID];
   ST_CPACK icpack;
   ST_CPACK icapack;
   ST_PACK icarrays[MAXROW];
   ST_PACK *prec;
   int i,rtn,n;
   g_pSvrLink->ResetNormalCPack(&icpack,0,1);
   icpack.head.RequestType = 1013;
   strncpy(szICBUGroupID,rpack->vsmess,sizeof(szICBUGroupID));
   AddFieldValue(&icpack,"vsmess","150");  // 1013功能需要的字段值
   if (szICBUGroupID[0]=='\0')
   {
      rtn = g_pSvrLink->RACall(5,&icpack,&icapack,icarrays);
   }
   else
   {
      rtn = g_pSvrLink->IntCall(szICBUGroupID,5,&icpack,&icapack,icarrays);
   }
   
   n = 0;
   while(rtn>0) 
   {
      prec = &(icapack.pack);
      g_pSvrLink->SetCol(handle,icapack.head.ParmBits);
      for (i=0;i<icapack.head.recCount;i++)
      {
         g_pSvrLink->PutRowData(prec);
         n++;
         prec = icarrays+i;
      }
      if (icapack.head.nextflag!=0)
      {
         if (szICBUGroupID[0]=='\0')
         {
            rtn = g_pSvrLink->RACallNext(5,&icapack,icarrays);
         }
         else
         {
            rtn = g_pSvrLink->IntCallNext(5,&icapack,icarrays);
         }
      }
      else break;
   }
   if (rtn<0)
   {
      // -2: 应答返回超时；-1: g_SvrLink与BCC的连接出现问题！
      g_pSvrLink->Err_Deal("Call timeout or Error!",10010-rtn);
   }
   return(1);
}

// 函数名: FBCCShmGetRecord
// 编程  : 陈永华 2005-9-21 16:28:02
// 描述  : 获取指定共享内存中的数据(为了测试外调功能)
// 返回  : 应答包数据： lvol0=m_iSerialNo; lvol1=m_iBUNumber; lvol2=m_iBCCID; vsmess=m_szDBlock
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack － 无
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FBCCShmGetRecord(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest shmtest;
   int shmhandle;
   CXPack *xpack = (CXPack *)GetDefaultXPack();
   shmhandle = g_pSvrLink->SMOpenBlock(SHMTESTNAME,sizeof(T_SHMTest));
   if (shmhandle<0)
   {
      Error_Deal(10001,szMsg,"Cannot open BCCSHM(%s,%u)!",SHMTESTNAME,sizeof(T_SHMTest));
      return(0);
   }
   *iRetCode = 0; szMsg[0]='\0';
   SetCol(handle,F_VSMESS,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL4,F_LVOL5,F_LVOL6,END_FIELD);
   g_pSvrLink->SMRead(shmhandle,&shmtest,0,sizeof(shmtest));
   rpack->lvol0 = shmtest.m_iSerialNo;
   rpack->lvol1 = shmtest.m_iBUNumber;
   rpack->lvol2 = shmtest.m_iBCCID;
   rpack->lvol3 = sizeof(int);
   rpack->lvol4 = sizeof(long);
   rpack->lvol5 = sizeof(T_SHMTest);
   rpack->lvol6 = htonl(sizeof(T_SHMTest));
   strncpy(rpack->vsmess,shmtest.m_szDBlock,sizeof(rpack->vsmess)-1);
   PutRow(handle,rpack,iRetCode,szMsg);
   return(1);
}


// 函数名: FBCCShmSetRecord
// 编程  : 陈永华 2005-9-21 18:22:08
// 描述  : 读取共享内存中的数据返回给客户端，将请求包中的值设置到共享内存中
// 返回  : 应答包数据： lvol0=m_iSerialNo; lvol1=m_iBUNumber; lvol2=m_iBCCID; vsmess=m_szDBlock
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack: lvol0=m_iSerialNo; vsmess=m_szDBlock
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FBCCShmSetRecord(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest shmtest,shmtestw;
   int shmhandle;
   CXPack *xpack = (CXPack *)GetDefaultXPack();
   shmhandle = g_pSvrLink->SMOpenBlock(SHMTESTNAME,sizeof(T_SHMTest));
   if (shmhandle<0)
   {
      Error_Deal(10001,szMsg,"Cannot open BCCSHM(%s,%u)!",SHMTESTNAME,sizeof(T_SHMTest));
      return(0);
   }
   *iRetCode = 0; szMsg[0]='\0';
   SetCol(handle,F_VSMESS,F_LVOL0,F_LVOL1,F_LVOL2,END_FIELD);
   shmtestw.m_iBUNumber = g_pSvrLink->iThisProcID;
   shmtestw.m_iSerialNo = rpack->lvol0;
   shmtestw.m_iBCCID = g_pSvrLink->bccBFuncNo+g_pSvrLink->bccID;
   strcpy(shmtestw.m_szDBlock,rpack->vsmess);
   g_pSvrLink->SMRead(shmhandle,&shmtest,0,sizeof(shmtest));
   rpack->lvol0 = shmtest.m_iSerialNo;
   rpack->lvol1 = shmtest.m_iBUNumber;
   rpack->lvol2 = shmtest.m_iBCCID;
   strncpy(rpack->vsmess,shmtest.m_szDBlock,sizeof(rpack->vsmess)-1);
   PutRow(handle,rpack,iRetCode,szMsg);
   g_pSvrLink->SMWrite(shmhandle,&shmtestw,0,sizeof(shmtest),true);
   return(1);
}


int FBCCShmMultiRows(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest shmtest;
   int shmhandle;
   int i,nloops;
   //unsigned int t1,t2;
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // 取得当前XPACK的内部缺省实例
   shmhandle = g_pSvrLink->SMOpenBlock(SHMTESTNAME,sizeof(T_SHMTest));
   if (shmhandle<0)
   {
      Error_Deal(10001,szMsg,"Cannot open BCCSHM(%s,%u)!",SHMTESTNAME,sizeof(T_SHMTest));
      return(1);
   }
   nloops = xpack->GetFieldValueI(rpack,"vsmess");
   if (nloops<1)
      nloops = 10;
   *iRetCode = 0; szMsg[0]='\0';
   SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   for (i=0;i<nloops;i++)
   {
      shmtest.m_iSerialNo = g_pSvrLink->SMInterlockedAdd(shmhandle,0,1);
      rpack->lvol0 = shmtest.m_iSerialNo;
      sprintf(rpack->vsmess,"SMInterlockedAdd(...,0,1)=%d called at %u",shmtest.m_iSerialNo,GetTickCount());
      PutRow(handle,rpack,iRetCode,szMsg);
   }
   // 追加一个字段：
   SetCol(handle,F_LVOL1,F_LVOL2,END_FIELD);

/* ****** Updated by CHENYH at 2005-8-5 16:02:06 ****** 
   // 或者：用
   SetCol(handle,END_FIELD); // 清除原来的位图（即清除原来有效字段的定义）
   SetCol(handle,F_LVOL0,F_LVOL1,F_VSMESS,END_FIELD);  // 重新设置字段
*******************************************************/
   for (i=0;i<nloops;i++)
   {
      g_pSvrLink->SMLock(shmhandle);
      g_pSvrLink->SMRead(shmhandle,&shmtest,0,sizeof(shmtest));
      rpack->lvol0 = shmtest.m_iSerialNo;
      rpack->lvol1 = shmtest.m_iBUNumber;
      rpack->lvol2 = shmtest.m_iBCCID;
      shmtest.m_szDBlock[101]='\0';  // 截去，怕vsmess超界：
      sprintf(rpack->vsmess,"BCCSHMBuffer:%s",shmtest.m_szDBlock);
      PutRow(handle,rpack,iRetCode,szMsg);
      (shmtest.m_iSerialNo)++;
      shmtest.m_iBUNumber = g_pSvrLink->iThisProcID;
      shmtest.m_iBCCID = g_pSvrLink->bccBFuncNo+g_pSvrLink->bccID;
      sprintf(shmtest.m_szDBlock,"Updated by BU%d at %u",g_pSvrLink->iThisProcID,GetTickCount());
      g_pSvrLink->SMWrite(shmhandle,&shmtest,0,sizeof(shmtest));
      g_pSvrLink->SMUnlock(shmhandle);
      //mysleep(10);  // 如果有其他BU在操作，那么就留出时间来
   }
   // BCCSHM是为了持久化和共享数据，实际上不支持动态使用，因此，也就不用关闭了
   return(1);  // 结束吧
   
}

// 函数名: FTestBCCShm
// 编程  : 陈永华 2005-7-19 23:29:02
// 描述  : 测试BCC共享内存资源的操作效率
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : int iRequest
// 参数  : ST_PACK *rpack
// 参数  : int *iRetCode
// 参数  : char *szMsg
int FTestBCCShm(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest shmtest;
   int shmhandle;
   int i,nloops;
   unsigned int t1,t2;
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // 取得当前XPACK的内部缺省实例
   shmhandle = g_pSvrLink->SMOpenBlock(SHMTESTNAME,sizeof(T_SHMTest));
   if (shmhandle<0)
   {
      Error_Deal(10001,szMsg,"Cannot open BCCSHM(%s,%u)!",SHMTESTNAME,sizeof(T_SHMTest));
      return(1);
   }
   nloops = xpack->GetFieldValueI(rpack,"vsmess");
   if (nloops<1)
      nloops = 10;
   shmtest.m_iSerialNo = 0;
   shmtest.m_iBUNumber = g_pSvrLink->iThisProcID;
   shmtest.m_iBCCID = g_pSvrLink->bccBFuncNo+g_pSvrLink->bccID;
   strcpy(shmtest.m_szDBlock,SHMTESTNAME);
   g_pSvrLink->SMWrite(shmhandle,&shmtest,0,sizeof(shmtest),true);
   t1 = GetTickCount();
   for (i=0;i<nloops;i++)
   {
      shmtest.m_iSerialNo = g_pSvrLink->SMInterlockedAdd(shmhandle,0,1);
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   g_pSvrLink->SMLock(shmhandle);
   t2 = GetTickCount();
   for (i=0;i<nloops;i++)
   {
      sprintf(shmtest.m_szDBlock,"BU%d Update m_szDBlock(%d) HAHAHA",g_pSvrLink->iThisProcID,i);
      g_pSvrLink->SMWrite(shmhandle,&shmtest,0,sizeof(shmtest));
   }
   t2 = tc2_tc1(GetTickCount(),t2);
   g_pSvrLink->SMRead(shmhandle,szMsg,(unsigned int)(&(shmtest.m_szDBlock[0])-(char *)(&shmtest)),100,true);
   if (strcmp(szMsg,shmtest.m_szDBlock)!=0)
   {
      Error_Deal(10002,szMsg,"SMWrite or SMRead Test fail!");
   }
   g_pSvrLink->SMUnlock(shmhandle);

   // 将结果通过vsmess的信息返回给请求方：
   sprintf(szMsg,"BCCSHMTEST: %d SMInterlockedAdd() called took %u MS, %d SMWrite() called took %u MS",
      nloops,t1,nloops,t2);
   SetCol(handle,F_VSMESS,END_FIELD);
   xpack->AddField(rpack,"vsmess",szMsg);
   PutRow(handle,rpack,iRetCode,szMsg);
   return(1);
}


/* ****** Updated by CHENYH at 2005-10-28 23:46:49 ****** 
 在HP-UX与PC(Windows)的性能比较时候，发现尽管1011功能测试的速度HP比Win快；
 但是在1013功能：HP(1条记录/70毫秒) WIN－PC却为(60条记录/10毫秒)
 明显比WIN慢许多，为了查找到底哪个操作降低了速度，特提供本测试功能
 1. SMInterlockedAdd 的 loops耗时时间；
 2. sprintf＋GetTickCount的loops耗时时间；
 3. EncodeRow的耗时时间
 4. 与1013的功能统计时间比较的差就是BU->BCC提交PutRow时候的其他操作（数据传输等）的耗时时间了
*******************************************************/
int FGetBaseOperTimes(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest shmtest;
   int shmhandle;
   int i,nloops;
   unsigned int t1,t2;
   ST_PACKHEAD phead;
   char ebuf[8192];
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // 取得当前XPACK的内部缺省实例
   shmhandle = g_pSvrLink->SMOpenBlock(SHMTESTNAME,sizeof(T_SHMTest));
   if (shmhandle<0)
   {
      Error_Deal(10001,szMsg,"Cannot open BCCSHM(%s,%u)!",SHMTESTNAME,sizeof(T_SHMTest));
      return(1);
   }
   nloops = xpack->GetFieldValueI(rpack,"vsmess");
   if (nloops<1)
      nloops = 10;
   shmtest.m_iSerialNo = 0;
   shmtest.m_iBUNumber = g_pSvrLink->iThisProcID;
   shmtest.m_iBCCID = g_pSvrLink->bccBFuncNo+g_pSvrLink->bccID;
   strcpy(shmtest.m_szDBlock,SHMTESTNAME);
   g_pSvrLink->SMWrite(shmhandle,&shmtest,0,sizeof(shmtest),true);

   // 4. <nloops> *4 GetTickCount test:
   unsigned int tt0,tt1,tt2,tt3;
   tt3 = GetTickCount();
   SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   tt0 = t1 = GetTickCount();
   for (i=0;i<nloops;i++)
   {
      tt1 = GetTickCount();
      tt2 = GetTickCount();
      tt3 = GetTickCount();
      tt0 = GetTickCount();
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   g_pSvrLink->SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   rpack->lvol0 = 0;
   sprintf(rpack->vsmess,"%d loops of 4*GetTickCount test took %u ms",
      nloops,t1);
   g_pSvrLink->PutRowData(rpack);
   
   // 4. <nloops> total part1 of 1013 test:
   tt3 = GetTickCount();
   SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   tt0 = t1 = GetTickCount();
   for (i=0;i<nloops;i++)
   {
      tt1 = GetTickCount();
      rpack->lvol0 = g_pSvrLink->SMInterlockedAdd(shmhandle,0,1);
      tt2 = GetTickCount();
      sprintf(rpack->vsmess,"t0=%u,t1=%u,t2=%u,t3=%u",tt0,tt1,tt2,tt3);
      tt3 = GetTickCount();
      g_pSvrLink->PutRowData(rpack);
      tt0 = GetTickCount();
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   g_pSvrLink->SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   rpack->lvol0 = 4;
   sprintf(rpack->vsmess,"%d loops of Part1 of 1013 test took %u ms",
      nloops,t1);
   g_pSvrLink->PutRowData(rpack);
   
   // 1. <nloops> SMInterlockedAdd Operations test:
   t1 = GetTickCount();
   for (rpack->lvol0=0;rpack->lvol0<nloops;rpack->lvol0++)
   {
      shmtest.m_iSerialNo = g_pSvrLink->SMInterlockedAdd(shmhandle,0,1);
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   //rpack->lvol0 = 1;
   sprintf(rpack->vsmess,"%d loops of SMInterlockedAdd(...,0,1)=%d took %u ms",
      nloops,shmtest.m_iSerialNo,t1);
   g_pSvrLink->SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   g_pSvrLink->PutRowData(rpack);

   // 2. <nloops> sprintf+GetTickCount Operations test:
   t1 = GetTickCount();
   for (rpack->lvol0=0;rpack->lvol0<nloops;rpack->lvol0++)
   {
      sprintf(rpack->vsmess,"sprintf [%d] called at %u",rpack->lvol0,GetTickCount());
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   rpack->lvol0 = 2;
   sprintf(rpack->vsmess,"%d loops of sprintf+GetTickCount() took %u ms",
      nloops,t1);
   g_pSvrLink->SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   g_pSvrLink->PutRowData(rpack);

   // 3. <nloops> EncodeRow Operations test:
   g_pSvrLink->SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   g_pSvrLink->GetAnswerHead(&phead);
   phead.recCount = 1;
   t1 = GetTickCount();
   for (rpack->lvol0=0;rpack->lvol0<nloops;rpack->lvol0++)
   {
      rpack->lvol1 = xpack->EncodeRow(&phead,rpack,ebuf,sizeof(ebuf));
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   rpack->lvol0 = 3;
   sprintf(rpack->vsmess,"%d loops of EncodeRow()=%d took %u ms",
      nloops,rpack->lvol1,t1);
   g_pSvrLink->PutRowData(rpack);


   // 5. <nloops> PutRowData Operations test:
   g_pSvrLink->SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   sprintf(rpack->vsmess,"PutRowData Test begin at %u",GetTickCount());
   t1 = GetTickCount();
   for (rpack->lvol0=0;rpack->lvol0<nloops;rpack->lvol0++)
   {
      sprintf(rpack->vsmess,"PutRowData at %u",GetTickCount());
      rpack->lvol1 = g_pSvrLink->PutRowData(rpack);
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   g_pSvrLink->SetCol(handle,F_VSMESS,F_LVOL0,END_FIELD);
   rpack->lvol0 = 5;
   sprintf(rpack->vsmess,"%d loops of PutRowData()=%d took %u ms,End at %u",
      nloops,rpack->lvol1,t1,GetTickCount());
   g_pSvrLink->PutRowData(rpack);


   g_pSvrLink->SMLock(shmhandle);
   t2 = GetTickCount();
   for (i=0;i<nloops;i++)
   {
      sprintf(shmtest.m_szDBlock,"BU%d Update m_szDBlock(%d) HAHAHA",g_pSvrLink->iThisProcID,i);
      g_pSvrLink->SMWrite(shmhandle,&shmtest,0,sizeof(shmtest));
   }
   t2 = tc2_tc1(GetTickCount(),t2);
   g_pSvrLink->SMRead(shmhandle,szMsg,(unsigned int)(&(shmtest.m_szDBlock[0])-(char *)(&shmtest)),100,true);
   if (strcmp(szMsg,shmtest.m_szDBlock)!=0)
   {
      Error_Deal(10002,szMsg,"SMWrite or SMRead Test fail!");
   }
   g_pSvrLink->SMUnlock(shmhandle);

   // 将结果通过vsmess的信息返回给请求方：
   sprintf(szMsg,"BCCSHMTEST: %d PutRowData(...) called took %u MS, %d SMWrite() called took %u MS",
      nloops,t1,nloops,t2);
   SetCol(handle,F_VSMESS,END_FIELD);
   xpack->AddField(rpack,"lvol0",6);
   xpack->AddField(rpack,"vsmess",szMsg);
   PutRow(handle,rpack,iRetCode,szMsg);
   return(1);
}


#define BUSHMTESTKEY 730428
int FTestBUShm(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest *pTest;
   CBUShm bushm;
   int i,nloops;
   int rtn;
   unsigned int t1,t2;
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // 取得当前XPACK的内部缺省实例
   pTest = (T_SHMTest *)bushm.Open("BUSHMTEST",sizeof(T_SHMTest));
   if (pTest==NULL)
   {
      Error_Deal(10001,szMsg,"BUShm error:%s",bushm.GetMessage());
      return(1);
   }
   nloops = xpack->GetFieldValueI(rpack,"vsmess");
   if (nloops<1)
      nloops = 10;
   pTest->m_iSerialNo = 0;
   pTest->m_iBUNumber = g_pSvrLink->iThisProcID;
   pTest->m_iBCCID = g_pSvrLink->bccBFuncNo+g_pSvrLink->bccID;
   t1 = GetTickCount();
   for (i=0;i<nloops;i++)
   {
      bushm.Lock();
      rtn = ++(pTest->m_iSerialNo);
      bushm.Unlock();
   }
   t1 = tc2_tc1(GetTickCount(),t1);
   bushm.Lock();
   t2 = GetTickCount();
   for (i=0;i<nloops;i++)
   {
      sprintf(pTest->m_szDBlock,"BU%d Update m_szDBlock(%d) HAHAHA",g_pSvrLink->iThisProcID,i);
   }
   t2 = tc2_tc1(GetTickCount(),t2);
   sprintf(szMsg,"BU%d Update m_szDBlock(%d) HAHAHA",g_pSvrLink->iThisProcID,i-1);
   if (strcmp(szMsg,pTest->m_szDBlock)!=0)
   {
      Error_Deal(10002,szMsg,"BUShm write/read test fail!");
   }
   bushm.Unlock();
   bushm.Remove("BUSHMTEST");

   // 将结果通过vsmess的信息返回给请求方：
   sprintf(szMsg,"BUSHMTEST: %d InterLockAdd() called took %u MS, %d Writes took %u MS",
      nloops,t1,nloops,t2);
   SetCol(handle,F_VSMESS,END_FIELD);
   xpack->AddField(rpack,"vsmess",szMsg);
   PutRow(handle,rpack,iRetCode,szMsg);
   return(1);
}




