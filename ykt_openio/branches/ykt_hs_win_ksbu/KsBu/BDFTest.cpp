
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

extern CSvrLink *g_pSvrLink;  // ��ҵ��������ĵ�����
extern CLogFile g_LogFile;

#include "BDFunc.inl"  // �������ÿ��д��̨����ʹ�ø��Ե��ļ���һֱ���ܼ��ɵ�ʱ��ͳһ��һ���ļ�����

// ������: FTestIReply  1010
// ���  : ������ 2004-7-1 9:37:27
// ����  : ����������ԭ�ⲻ�����ظ�����ˣ���Ҫ���ڲ��Լܹ����ֵ���Ӧ�ٶ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rPack
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestIReply(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg)
{
   ST_PACKHEAD phead;
   g_pSvrLink->GetRequestHead(&phead);
   g_pSvrLink->SetCol(handle,phead.ParmBits);
   PutRow(handle,rPack,iRetCode,szMsg);
   //AnswerData(handle,*iRetCode,szMsg); ����ȱʡΪAM_AUTOģʽ�£��Ͳ���Ҫ������
   return(1);
}

// ���ܲ��ԣ�ExtCall(rPack->lvol0,rPack->lvol1,rPack->lvol2,...) 1030
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

// ���ܲ��ԣ�IntCall(rPack->vsmess,...) RACall(...) 1031
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


// ���ܲ��ԣ�ExtTransfer(rPack->lvol1,rPack->lvol2,...) 1032
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

// ���ܲ��ԣ�IntTransfer(rPack->vsmess,...) RATransfer(...) 1033
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

   strcpy(szfile,rpack->vsmess);
   maxlen = sizeof(ST_PACK)-4;
   if (maxlen>4000)
      maxlen = 4000;
   fp = sh_fopen(szfile,"rb",SH_DENYNO);
   //g_pSvrLink->SetMaxRow(1);  // ǿ�Ƶ���¼����
   if (fp==NULL)
   {
      sprintf(szMsg,"Cannot open the file:<%s>!",szfile);
      *iRetCode = 9980;
   }
   else
   {
      psd = (ST_SDPACK *)rpack;
      while (!feof(fp))
      {
         psd->usDataLength = fread(psd->data,1,maxlen,fp);
         g_pSvrLink->PutRowData(rpack);
      }
      fclose(fp);
      stat(szfile,&fst);
      sprintf(szMsg,"%ld",fst.st_mtime);
      *iRetCode = 1;
   }
   g_pSvrLink->SetCol(handle,F_VSMESS,END_FIELD);
   memcpy(rpack->vsmess,szMsg,sizeof(rpack->vsmess));  // ������memcpy����strcpy����ֹ�ڴ泬�翽��
   g_pSvrLink->PutRow(handle,rpack,*iRetCode,szMsg);
   return(1);
}

struct T_SHMTest
{
   int m_iSerialNo;  // ��ʼ��Ϊһ�����к�
   int m_iBUNumber;  // BU�������Ϊ���д��BU�ı�ʶ
   int m_iBCCID;     // BCC��˽�й��ܺ� ��bccBFuncNo+bccID��
   char m_szDBlock[1024]; // ��Ϊһ�����ݿ�Ĳ���
};

#define SHMTESTNAME "BCCSHMTEST"
int FTestBURunTime(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   // ��������Ϊ�˲���BCC�ж�BU���е�MAXRUNTIME�Ƿ���˵��������
   int sleeptime=atoi(rpack->vsmess);
   if (sleeptime<=0)
      sleeptime=1;
   g_pSvrLink->SetCol(handle,F_VSMESS,END_FIELD);
   g_pSvrLink->SetMaxRow(1);
   sprintf(rpack->vsmess,"Record on Tick:%u",GetTickCount());
   g_pSvrLink->PutRowData(rpack); // �ȷ���һ����¼
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

   // ����������Ҳ���͸�����һ��Ӧ�÷�����ȥ����Ȼ����ֻ����BU�����ˡ�
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
   g_pSvrLink->GetRequestHead(&(icpack.head));  // �ȴ�CSvrLink��ȡ�������ͷ
   icpack.head.RequestType = 1013;
   icpack.head.recCount = 1;  // ����ԭʼ�����Ƕ��¼������ﶼ�趨Ϊֻ��1�������¼
   AddFieldValue(&icpack,"vsmess","150");  // 1013������Ҫ���ֶ�ֵ
   // ��ʾ��������Ӧ�ò���Transferģʽת���������BU���д���ģ�
   rtn = g_pSvrLink->ExtTransfer(rpack->lvol1,rpack->lvol2,&icpack);
   // ��ģʽ�£���BU����Ҫ���ؽ�����ͻ����ˡ����ȹر��Զ�Ӧ��ģʽ��
/* ****** Updated by CHENYH at 2005-9-23 16:17:12 ****** 
   // ��BCC��Transfer�������Ѿ��Զ������˱�ģʽ
   g_pSvrLink->SetAnswerMode(AM_CONFIRM);  // ���Զ�Ӧ��ģʽת��Ϊ��ʽӦ��ģʽ
*******************************************************/
   // �����ͻ���Ϊû�е���PutRow��PutRowData�ȣ������ڻ᷵��һ���ռ�¼���ͻ��˶���Ԥ����ת����BU���ؽ����
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
   //g_pSvrLink->GetRequestHead(&(icpack.head));  // �ȴ�CSvrLink��ȡ�������ͷ,�Ա������������ֶ�ԭ����ֵ��λͼ
   g_pSvrLink->ResetNormalCPack(&icpack,0,1);
   icpack.head.RequestType = 1013;
   sno = handle->SourceNo; //rpack->lvol0;
   dno = rpack->lvol1;
   fno = rpack->lvol2;
   AddFieldValue(&icpack,"vsmess","150");  // 1013������Ҫ���ֶ�ֵ
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
      // -2: Ӧ�𷵻س�ʱ��-1: g_SvrLink��BCC�����ӳ������⣡
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
   g_pSvrLink->GetRequestHead(&(icpack.head));  // �ȴ�CSvrLink��ȡ�������ͷ
   icpack.head.RequestType = 1013;
   icpack.head.recCount = 1;  // ����ԭʼ�����Ƕ��¼������ﶼ�趨Ϊֻ��1�������¼
   strncpy(szICBUGroupID,rpack->vsmess,sizeof(szICBUGroupID));
   AddFieldValue(&icpack,"vsmess","150");  // 1013������Ҫ���ֶ�ֵ
   // ��ʾ��������Ӧ�ò���Transferģʽת���������BU���д���ģ�
   if (szICBUGroupID[0]=='\0')
   {
      rtn = g_pSvrLink->RATransfer(&icpack);
   }
   else
   {
      rtn = g_pSvrLink->IntTransfer(szICBUGroupID,&icpack);
   }
   // ��ģʽ�£���BU����Ҫ���ؽ�����ͻ����ˡ����ȹر��Զ�Ӧ��ģʽ��
/* ****** Updated by CHENYH at 2005-9-23 16:17:12 ****** 
   // ��BCC��Transfer�������Ѿ��Զ������˱�ģʽ
   g_pSvrLink->SetAnswerMode(AM_CONFIRM);  // ���Զ�Ӧ��ģʽת��Ϊ��ʽӦ��ģʽ
*******************************************************/
   // �����ͻ���Ϊû�е���PutRow��PutRowData�ȣ������ڻ᷵��һ���ռ�¼���ͻ��˶���Ԥ����ת����BU���ؽ����
   return(1);
}

// ������: FTestBCCIntCall
// ���  : ������ 2005-9-22 11:07:44
// ����  : �ù��ܺ�1013����BCC��IntCall/IntCallNext��RACall/RACallNext�Ĺ���
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack��vsmess=����ģ£���ţ��������RACall/RACallNext
// ����  : int *iRetCode
// ����  : char *szMsg
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
   AddFieldValue(&icpack,"vsmess","150");  // 1013������Ҫ���ֶ�ֵ
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
      // -2: Ӧ�𷵻س�ʱ��-1: g_SvrLink��BCC�����ӳ������⣡
      g_pSvrLink->Err_Deal("Call timeout or Error!",10010-rtn);
   }
   return(1);
}

// ������: FBCCShmGetRecord
// ���  : ������ 2005-9-21 16:28:02
// ����  : ��ȡָ�������ڴ��е�����(Ϊ�˲����������)
// ����  : Ӧ������ݣ� lvol0=m_iSerialNo; lvol1=m_iBUNumber; lvol2=m_iBCCID; vsmess=m_szDBlock
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack �� ��
// ����  : int *iRetCode
// ����  : char *szMsg
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


// ������: FBCCShmSetRecord
// ���  : ������ 2005-9-21 18:22:08
// ����  : ��ȡ�����ڴ��е����ݷ��ظ��ͻ��ˣ���������е�ֵ���õ������ڴ���
// ����  : Ӧ������ݣ� lvol0=m_iSerialNo; lvol1=m_iBUNumber; lvol2=m_iBCCID; vsmess=m_szDBlock
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack: lvol0=m_iSerialNo; vsmess=m_szDBlock
// ����  : int *iRetCode
// ����  : char *szMsg
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
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // ȡ�õ�ǰXPACK���ڲ�ȱʡʵ��
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
   // ׷��һ���ֶΣ�
   SetCol(handle,F_LVOL1,F_LVOL2,END_FIELD);

/* ****** Updated by CHENYH at 2005-8-5 16:02:06 ****** 
   // ���ߣ���
   SetCol(handle,END_FIELD); // ���ԭ����λͼ�������ԭ����Ч�ֶεĶ��壩
   SetCol(handle,F_LVOL0,F_LVOL1,F_VSMESS,END_FIELD);  // ���������ֶ�
*******************************************************/
   for (i=0;i<nloops;i++)
   {
      g_pSvrLink->SMLock(shmhandle);
      g_pSvrLink->SMRead(shmhandle,&shmtest,0,sizeof(shmtest));
      rpack->lvol0 = shmtest.m_iSerialNo;
      rpack->lvol1 = shmtest.m_iBUNumber;
      rpack->lvol2 = shmtest.m_iBCCID;
      shmtest.m_szDBlock[101]='\0';  // ��ȥ����vsmess���磺
      sprintf(rpack->vsmess,"BCCSHMBuffer:%s",shmtest.m_szDBlock);
      PutRow(handle,rpack,iRetCode,szMsg);
      (shmtest.m_iSerialNo)++;
      shmtest.m_iBUNumber = g_pSvrLink->iThisProcID;
      shmtest.m_iBCCID = g_pSvrLink->bccBFuncNo+g_pSvrLink->bccID;
      sprintf(shmtest.m_szDBlock,"Updated by BU%d at %u",g_pSvrLink->iThisProcID,GetTickCount());
      g_pSvrLink->SMWrite(shmhandle,&shmtest,0,sizeof(shmtest));
      g_pSvrLink->SMUnlock(shmhandle);
      //mysleep(10);  // ���������BU�ڲ�������ô������ʱ����
   }
   // BCCSHM��Ϊ�˳־û��͹������ݣ�ʵ���ϲ�֧�ֶ�̬ʹ�ã���ˣ�Ҳ�Ͳ��ùر���
   return(1);  // ������
   
}

// ������: FTestBCCShm
// ���  : ������ 2005-7-19 23:29:02
// ����  : ����BCC�����ڴ���Դ�Ĳ���Ч��
// ����  : int 
// ����  : TRUSERID *handle
// ����  : int iRequest
// ����  : ST_PACK *rpack
// ����  : int *iRetCode
// ����  : char *szMsg
int FTestBCCShm(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest shmtest;
   int shmhandle;
   int i,nloops;
   unsigned int t1,t2;
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // ȡ�õ�ǰXPACK���ڲ�ȱʡʵ��
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

   // �����ͨ��vsmess����Ϣ���ظ����󷽣�
   sprintf(szMsg,"BCCSHMTEST: %d SMInterlockedAdd() called took %u MS, %d SMWrite() called took %u MS",
      nloops,t1,nloops,t2);
   SetCol(handle,F_VSMESS,END_FIELD);
   xpack->AddField(rpack,"vsmess",szMsg);
   PutRow(handle,rpack,iRetCode,szMsg);
   return(1);
}


/* ****** Updated by CHENYH at 2005-10-28 23:46:49 ****** 
 ��HP-UX��PC(Windows)�����ܱȽ�ʱ�򣬷��־���1011���ܲ��Ե��ٶ�HP��Win�죻
 ������1013���ܣ�HP(1����¼/70����) WIN��PCȴΪ(60����¼/10����)
 ���Ա�WIN����࣬Ϊ�˲��ҵ����ĸ������������ٶȣ����ṩ�����Թ���
 1. SMInterlockedAdd �� loops��ʱʱ�䣻
 2. sprintf��GetTickCount��loops��ʱʱ�䣻
 3. EncodeRow�ĺ�ʱʱ��
 4. ��1013�Ĺ���ͳ��ʱ��ȽϵĲ����BU->BCC�ύPutRowʱ����������������ݴ���ȣ��ĺ�ʱʱ����
*******************************************************/
int FGetBaseOperTimes(TRUSERID *handle,int iRequest, ST_PACK *rpack, int *iRetCode, char *szMsg)
{
   T_SHMTest shmtest;
   int shmhandle;
   int i,nloops;
   unsigned int t1,t2;
   ST_PACKHEAD phead;
   char ebuf[8192];
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // ȡ�õ�ǰXPACK���ڲ�ȱʡʵ��
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

   // �����ͨ��vsmess����Ϣ���ظ����󷽣�
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
   CXPack *xpack = (CXPack *)GetDefaultXPack();  // ȡ�õ�ǰXPACK���ڲ�ȱʡʵ��
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

   // �����ͨ��vsmess����Ϣ���ظ����󷽣�
   sprintf(szMsg,"BUSHMTEST: %d InterLockAdd() called took %u MS, %d Writes took %u MS",
      nloops,t1,nloops,t2);
   SetCol(handle,F_VSMESS,END_FIELD);
   xpack->AddField(rpack,"vsmess",szMsg);
   PutRow(handle,rpack,iRetCode,szMsg);
   return(1);
}




