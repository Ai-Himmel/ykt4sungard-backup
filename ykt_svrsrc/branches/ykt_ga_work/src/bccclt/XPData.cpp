// XPData.cpp: implementation of the CBCXPData class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "XPack.h"
#include "cxpack.h"
#include "XPData.h"
#include "DRTPRouter.h"
#include "bccclt.h"
#include "nbccclt.h"

CMUTEX g_DRTPMutex;
int g_DRTPNodes=0;
int g_MaxDRTPNodes=0;
CDrtpRouter *g_pDRTPNode=NULL;

extern FILE *g_fpLog;

// 函数名: *getfmttime
// 编程  : 陈永华 2003-10-14 11:23:47
// 描述  : 将tm的时间转换为本地时间的格式化字符串，本子系统中non-thread-safe
// 返回  : char * 格式化的字符串指针, NULL 则使用内部静态空间存放格式化的字符串，
// 参数  : time_t *ptm ：需要转换的时间 ==NULL 则为转换时时间点
// 参数  : int fmttype 
/*
0 : hh:mm:ss
1 : MM/DD-hh:mm:ss
2 : YYYY/MM/DD-hh:mm:ss
3 : YYYYMMDD
4 : hhmmss
其他 : YYYYMMDDhhmmss
*/
// 参数  : char *outstr 输出字符串的缓存，=NULL则使用内部的静态缓存，其长度需要视fmttype而定
char *getfmttime(void *ptm,int fmttype,char *outstr)
{
   static char tstr[80];
   struct tm tmloc;
   time_t timet;
   
   if (ptm==NULL)
   {
      ptm = &timet;
      time(&timet);
   }
   else
   {
      memcpy(&timet,ptm,sizeof(timet));
   }
   if (outstr==NULL)
   {
      outstr = tstr;
   }
   //localtime_r(&tm,&tmloc);
   memcpy(&tmloc,localtime(&timet),sizeof(tmloc));
   if (fmttype==0)
   {
      // %H:%M:%S:
      strftime(outstr,79,"%H:%M:%S",&tmloc);
   }
   else if (fmttype==1)
   {
      // %m/%d-%H:%M:%S
      strftime(outstr,79,"%m/%d %H:%M:%S",&tmloc);
   }
   else if (fmttype==2)
   {
      strftime(outstr,79,"%Y/%m/%d %H:%M:%S",&tmloc);
   }
   else if (fmttype==3)
   {
      strftime(outstr,79,"%Y%m%d",&tmloc);
   }
   else if (fmttype==4)
   {
      strftime(outstr,79,"%H%M%S",&tmloc);
   }
   else 
   {
      strftime(outstr,79,"%Y%m%d%H%M%S",&tmloc);
   }
   return(outstr);
}

bool CheckDebugLog();

void Debug_FileOut(char *msg,char *fmt,...)
{
   va_list pArg;
   char chMsg[2048];
   
   if (CheckDebugLog())
   {
      fprintf(g_fpLog,"%s %s: ",getfmttime(NULL,1,NULL),msg);
      va_start(pArg,fmt);
      vsprintf(chMsg,fmt,pArg);
      va_end(pArg);
      fprintf(g_fpLog,"%s\n",chMsg);
      fflush(g_fpLog);
   }
}

void Debug_HeadOut(char *msg,ST_PACKHEAD *phead)
{
   if (CheckDebugLog())
   {
      fprintf(g_fpLog,"\n%s %s HEAD:"
      "\tRequestType=%u\n"
      "\tfirstflag=%d\n"
      "\tnextflag=%d\n"
      "\thook.queuetype=%u\n"
      "\thook.hostname+1=%s\n"
      "\trecCount=%u\n"
      "\tretCode=%u\n",
      getfmttime(NULL,1,NULL),
      msg,
      phead->RequestType,
      phead->firstflag,
      phead->nextflag,
      phead->hook.queuetype,
      phead->hook.hostname+1,
      phead->recCount,
      phead->retCode
      );
   }
}

void Debug_PackOut(char *msg, CXPack *pXPack,ST_PACKHEAD *phead,ST_PACK *pack)
{
   if (!CheckDebugLog())
      return;
   int ilastfidx;
   int i;
   const ST_PDATALIST *pdl=pXPack->GetPackDef(ilastfidx);
   int n=0;
   char value[320];
   fprintf(g_fpLog,"%s %s PACK:\n",getfmttime(NULL,1,NULL),msg);
   for (i=0;i<=ilastfidx;i++)
   {
      if (pXPack->IsValidField(phead,i))
      {
         pXPack->GetFieldValue(pack,i,value);
         fprintf(g_fpLog,"\t%s(%d:%d)=%s\n",
            pdl[i].szName,
            pdl[i].wType,
            pdl[i].nLength,
            value
            );
         n++;
      }
   }
   if (n<=0)
   {
      ST_SDPACK *psd = (ST_SDPACK *)pack;
      if (psd->usDataLength<pXPack->GetPackLength())
      {
         fprintf(g_fpLog,"\tSDPACK:Length=%u [",psd->usDataLength);
         fwrite(psd->data,psd->usDataLength,1,g_fpLog);
         fprintf(g_fpLog,"]\n");
      }
      else
      {
         fprintf(g_fpLog,"\tSDPACK:Length=%u >= MaxLength(%d) -- Invalid SDPACK!\n",
            psd->usDataLength,pXPack->GetPackLength());
      }
   }
   fflush(g_fpLog);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static unsigned int g_userdata0=0;
CBCXPData::CBCXPData()
{
   m_iClassID = XPD_CLTID;
   m_pXPack = NULL;
   m_userdata = g_userdata0;
   g_userdata0 += 1000;
   Reset();
}

CBCXPData::~CBCXPData()
{
   m_pXPack = NULL;
}

void CBCXPData::Reset()
{
   int i;
   memset(&m_head,0,sizeof(m_head));
   m_head.firstflag = 1;
   m_head.recCount = 1;
   for (i=0;i<=100;i++)
      memset(m_packs+i,0,sizeof(ST_PACK));   
}

CXPack * CBCXPData::GetXPack()
{
   return(m_pXPack);
}


int CBCXPData::GetFieldType(int Col)
{
   int ilf;
   const ST_PDATALIST *pdlist = m_pXPack->GetPackDef(ilf);
   if (Col>=0 && Col<=ilf)
   {
      return(pdlist[Col].wType);
   }
   return(-1);
}


bool CBCXPData::GetFieldInfo(int col, char *name, int &type, int &length)
{
   int ilf;
   const ST_PDATALIST *pdlist = m_pXPack->GetPackDef(ilf);
   if (col>=0 && col<=ilf)
   {
      memcpy(name,pdlist[col].szName,sizeof(pdlist[col].szName));
      type = pdlist[col].wType;
      length = pdlist[col].nLength;
      return(type!=0);
   }
   return(false);
}


int CBCXPData::GetFieldType(char *fieldname)
{
   int fidx = m_pXPack->FindFieldIndex(fieldname);
   return(GetFieldType(fidx));
}

bool CBCXPData::GetIntField(int row, int col, long *value)
{
   if (row<0||row>=m_head.recCount)
      return(false);
   *value = m_pXPack->GetFieldValueI(m_packs+row,col);
   return(true);
}

bool CBCXPData::GetDoubleField(int row, int col, double *value)
{
   if (row<0||row>=m_head.recCount)
      return(false);
   *value = m_pXPack->GetFieldValueD(m_packs+row,col);
   return(true);
}

bool CBCXPData::GetStringField(int row, int col, char *value)
{
   if (row<0||row>=m_head.recCount)
      return(false);
   /* ****** Updated by CHENYH at 2006-6-30 11:21:51 ****** 
   m_pXPack->GetFieldValue(m_packs+row,col,value);
   *******************************************************/
   m_pXPack->GetPrintFieldValue(m_packs+row,col,value);
   return(true);
}

bool CBCXPData::GetIntField(int row, const char *fieldname, long *value)
{
   if (row<0||row>=m_head.recCount)
      return(false);
   *value = m_pXPack->GetFieldValueI(m_packs+row,fieldname);
   return(true);
}

bool CBCXPData::GetDoubleField(int row, const char *fieldname, double *value)
{
   if (row<0||row>=m_head.recCount)
      return(false);
   *value = m_pXPack->GetFieldValueD(m_packs+row,fieldname);
   return(true);
}

bool CBCXPData::GetStringField(int row, const char *fieldname, char *value)
{
   if (row<0||row>=m_head.recCount)
      return(false);
   /* ****** Updated by CHENYH at 2006-6-30 11:21:06 ****** 
   m_pXPack->GetFieldValue(m_packs+row,fieldname,value);
   *******************************************************/
   int fidx = m_pXPack->FindCFieldIndex(fieldname);
   if (fidx<0)
      return(false);
   m_pXPack->GetPrintFieldValue(m_packs+row,fidx,value);
   return(true);
}

bool CBCXPData::SetIntField(int row, int col, long value)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   return(m_pXPack->AddField(m_packs+row,col,(int)value,&m_head));
}

bool CBCXPData::SetIntField(int row, const char *fieldname, long value)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   return(m_pXPack->AddField(m_packs+row,fieldname,(int)value,&m_head));
}

bool CBCXPData::SetDoubleField(int row, int col, double value)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   return(m_pXPack->AddField(m_packs+row,col,value,&m_head));
}

bool CBCXPData::SetDoubleField(int row, const char *fieldname, double value)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   return(m_pXPack->AddField(m_packs+row,fieldname,value,&m_head));
}

bool CBCXPData::SetStringField(int row, int col, const char *value)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   return(m_pXPack->AddField(m_packs+row,col,value,&m_head));
}


bool CBCXPData::SetStringField(int row, const char *fieldname, const char *value)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   return(m_pXPack->AddField(m_packs+row,fieldname,value,&m_head));
}



bool CBCXPData::SetRequestType(int reqtype)
{
   m_head.RequestType = reqtype;
   return(true);
}

bool CBCXPData::IsEof()
{
   return(m_head.nextflag==0);
}

int CBCXPData::GetRecordCount()
{
   return(m_head.recCount);
}

long CBCXPData::GetRetCode()
{
   return(m_head.retCode);
}

int CBCXPData::EncodeXPackForRequest(char *buf, int bufsize)
{
   int len;
   int rtn;
   unsigned int i;
   if (bufsize<(int)sizeof(ST_PACKHEAD))
      return(0);
   m_head.firstflag = 1;
   m_head.nextflag = 0;
   Debug_HeadOut("REQ",&m_head);
   len = m_pXPack->EncodeHead(&m_head,buf);
   for (i=0;i<m_head.recCount;i++)
   {
      Debug_PackOut("REQ",m_pXPack,&m_head,m_packs+i);
      rtn = m_pXPack->EncodeRow(&m_head,m_packs+i,buf+len,bufsize-len);
      if (rtn<0)
         return(rtn);
      len += rtn;
   }
   return(len);
}

int CBCXPData::EncodeXPackForNext(char *buf, int bufsize)
{
   int len;
   int rtn;
   if (bufsize<(int)sizeof(ST_PACKHEAD))
      return(0);
   m_head.firstflag = 0;
   m_head.nextflag = 1;
   memcpy(&(m_head.hook),&(m_lasthook),sizeof(m_head.hook));
   rtn = m_head.recCount;
   m_head.recCount = 0; // 针对BCC的情况，不需要数据包体，即可取后续数据了
   Debug_HeadOut("REQNEXT",&m_head);
   len = m_pXPack->EncodeHead(&m_head,buf);
   m_head.recCount = rtn;
   /* ****** Updated by CHENYH at 2005-11-12 23:05:58 ****** 
   for (unsigned int i=0;i<m_head.recCount;i++)
   {
      rtn = m_pXPack->EncodeRow(&m_head,m_packs+i,buf+len,bufsize-len);
      if (rtn<0)
         return(rtn);
      len += rtn;
   }
   *******************************************************/
   return(len);
}

bool CBCXPData::DecodeXPack(const char *buf, int buflen)
{
   int len;
   int rtn;
   unsigned int i;
   rtn = m_pXPack->DecodeHead(buf,buflen,&m_head);
   if (rtn<=0)
      return(false);
   Debug_HeadOut("ANS",&m_head);
   len = rtn;
   for (i=0;i<m_head.recCount;i++)
   {
      rtn = m_pXPack->DecodeRow(&m_head,buf+len,buflen-len,m_packs+i);
      if (rtn<=0)
         return(false);
      Debug_PackOut("ANS",m_pXPack,&m_head,m_packs+i);
      len += rtn;
   }
   memcpy(&m_lasthook,&(m_head.hook),sizeof(m_lasthook));
   return(true);
}

int CBCXPData::GetPrivateFunctionForNext()
{
   if (m_lasthook.hostname[0]==0
      ||(m_lasthook.queuename[0]>='0'&&m_lasthook.queuename[0]<='9'))
   {
      return(m_lasthook.queuetype);
   }
   else
   {
      return(0);
   }
}

int CBCXPData::GetBranchNoForNext()
{
   if (m_lasthook.hostname[0]==0 && m_lasthook.hostname[1]>='0'&&m_lasthook.hostname[1]<='9')
   {
      return(atoi(m_lasthook.hostname+1)); // for KSMBCC answer mode;
   }
   else if (m_lasthook.hostname[0]>='0'&&m_lasthook.hostname[0]<='9')
   {
      // BCCADP=1
      return(atoi(m_lasthook.hostname+10));
   }
   return(0);  // 无法得到
}

bool CBCXPData::SetRecordCount(int recordcount)
{
   m_head.recCount = recordcount;
   return(true);
}

bool CBCXPData::ResetPackHead()
{
   memset(&m_head,0,sizeof(m_head));
   m_head.recCount = 1;
   m_head.firstflag = 1;
   //m_head.nextflag = 0;
   return(true);
}

bool CBCXPData::SetMaxRetCount(int maxretcount)
{
   if (maxretcount<0 || maxretcount>MAXROWS)
      return(false);
   m_head.retCode = maxretcount;
   return(true);
}

int CBCXPData::GetXPackType()
{
   if (m_pXPack->IsRawDataPack(&m_head))
      return(1);
   else
      return(0);
}


bool CBCXPData::SetRawRecord(int row, void *RawData, unsigned short RawDataLength)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (RawDataLength>sizeof(ST_PACK)-sizeof(unsigned short))
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   memset(m_head.ParmBits,0,sizeof(m_head.ParmBits));
   char *pr=(char *)(m_packs+row);
   memcpy(pr,&RawDataLength,sizeof(unsigned short));
   if (RawDataLength>0)
      memcpy(pr+sizeof(unsigned short),RawData,RawDataLength);
   return(true);
}

bool CBCXPData::SetRawRecord(int row, ST_SDPACK *psd)
{
   if (row<0||row>=MAXROWS)
      return(false);
   if (m_head.recCount<=row)
      m_head.recCount = row+1;
   memset(m_head.ParmBits,0,sizeof(m_head.ParmBits));
   memcpy(m_packs+row,psd,sizeof(psd->usDataLength)+psd->usDataLength);
   return(true);
}



ST_SDPACK * CBCXPData::GetRawRecord(int row)
{
   ST_SDPACK *pr;
   if (row<0||row>=m_head.recCount)
      return(NULL);
   if (m_pXPack->IsRawDataPack(&m_head))
   {
      pr = (ST_SDPACK *)(m_packs+row);
      if (pr->usDataLength<sizeof(m_packs[0])-sizeof(pr->usDataLength))
         return(pr);
   }
   return(NULL);
}

int CBCXPData::GetMaxColumn()
{
   int ilf;
   m_pXPack->GetPackDef(ilf);
   return(ilf);
}

bool CBCXPData::IsValidColumn(int col)
{
   return(m_pXPack->IsValidField(&m_head,col));
}

int CBCXPData::GetFieldColumn(char *fieldname)
{
   return(m_pXPack->FindFieldIndex(fieldname));
}


bool CBCXPData::IsValidColumn(char *fieldname)
{
   return(m_pXPack->IsValidField(&m_head,fieldname));   
}

bool CBCXPData::HaveNextPack()
{
   return(m_head.nextflag!=0);
}


bool CBCXPData::CallRequest(int drtpno, int branchno, int function, int timeout, int &errcode, char *errmsg)
{
   char buf[MAXENCODEBUFSIZE];
   int blen;
   errcode = 0;
   m_head.userdata = ++m_userdata;
   blen = EncodeXPackForRequest(buf,MAXENCODEBUFSIZE);
   if (blen>=(int)sizeof(ST_PACKHEAD))
   {
      errcode = CLISendReceive(drtpno,branchno,function,timeout,buf,blen,errmsg);
      if (errcode==0)
      {
         m_drtpno = drtpno;
         m_branchno = branchno;
         m_funcno = function;
      }
   }
   else
   {
      errcode = -100;
      strcpy(errmsg,"Encode XPack failure!");
   }
   return(errcode==0);   
}

bool CBCXPData::CallNext(int timeout, int &errcode, char *errmsg)
{
   char buf[MAXENCODEBUFSIZE];
   int blen;
   int branchno,function;
   if (IsEof())
   {
      errcode = -101;
      strcpy(errmsg,"No more data from Server!");
      return(false);
   }
   function = GetPrivateFunctionForNext();
   if (function<=0)
      function = m_funcno;
   branchno = GetBranchNoForNext();
   if (branchno<=0)
      branchno = m_branchno;
   
   errcode = 0;
   blen = EncodeXPackForNext(buf,MAXENCODEBUFSIZE);
   if (blen>=(int)sizeof(ST_PACKHEAD))
   {
      errcode = CLISendReceive(m_drtpno,branchno,function,timeout,buf,blen,errmsg);
   }
   else
   {
      errcode = -100;
      strcpy(errmsg,"Encode XPack failure!");
   }
   return(errcode==0);   
}

int CBCXPData::CLISendReceive(int drtpno, int branchno, int function, int timeout, char *buf, int buflen, char *errmsg)
{
   int rtn;
   if (drtpno>=g_DRTPNodes||drtpno<0)
   {
      sprintf(errmsg,"No define DRTP Node[%d] with BCAddDrtpNode!",drtpno);
      return(-1001);
   }
   rtn = g_pDRTPNode[drtpno].CLISendReceive(branchno,function,timeout,buf,buflen,buf,MAXENCODEBUFSIZE,errmsg);
   /* ****** Updated by CHENYH at 2008-5-14 17:42:21 ****** 
   // 结果发现在本行中如果rtn=-103等，则会因为以unsigned方式比较而继续解码
   if (rtn>=sizeof(ST_PACKHEAD))
   */
   if (rtn>=(int)sizeof(ST_PACKHEAD))
   {
      if (DecodeXPack(buf,rtn))
      {
         return(0);
      }
      else
      {
         sprintf(errmsg,"Received Data (Length=%d), But Decode failure!",rtn);
         rtn = -10;
      }
   }
   else
   {
      if (rtn>0)
      {
         sprintf(errmsg,"Received Data (Length=%d), But Irregular data!",rtn);
         rtn = -11;
      }
      else if (rtn==0)
      {
         return(-12);
      }
   }
   return(rtn);
}


int CBCXPData::EmulateMaxRows()
{
   int recs;
   int maxlen=8000-sizeof(ST_PACKHEAD); // < MAXENCODEBUFSIZE
   int erlen = m_pXPack->EmulateEncodeLength(&m_head);
   if (erlen<1)
      return(1);
   recs = maxlen/erlen;
   if (recs<1)
      return(1);
   else
      return(recs>MAXROWS?MAXROWS:recs);
}


//////////////////////////////////////////////////////////////////////////
bool BCCCLTInit(int maxnodes)
{
   CPMUTEX pMutex(&g_DRTPMutex);
   if (maxnodes<1)
      return(false);
   if (g_DRTPNodes>0)
      return(false);
   if (g_pDRTPNode!=NULL)
   {
      return(true);
   }
   g_pDRTPNode = new CDrtpRouter[maxnodes];
   if (g_pDRTPNode!=NULL)
   {
      g_MaxDRTPNodes = maxnodes;
      return(true);
   }
   else
      return(false);
}

int BCAddDrtpNode(char *ip,int port)
{
   CPMUTEX pMutex(&g_DRTPMutex);
   int node;
   if (g_DRTPNodes>=g_MaxDRTPNodes)
      return(-1);
   node = g_DRTPNodes++;
   strcpy(g_pDRTPNode[node].m_IP,ip);
   g_pDRTPNode[node].m_port = port;
   return(node);
}

int AddDrtpNode(char *ip,int port)
{
   return(BCAddDrtpNode(ip,port));
}

bool CBCXPData::Broad(int drtpno, int destno, int funcno, int &errcode, char *errmsg)
{
   char buf[MAXENCODEBUFSIZE];
   int blen;
   errcode = 0;
   if (drtpno>=g_DRTPNodes||drtpno<0)
   {
      sprintf(errmsg,"No define DRTP Node[%d] with BCAddDrtpNode!",drtpno);
      errcode = -1001;
      return(false);
   }

   blen = EncodeXPackForRequest(buf,MAXENCODEBUFSIZE);
   if (blen>=(int)sizeof(ST_PACKHEAD))
   {
      errcode = g_pDRTPNode[drtpno].Broad(destno,funcno,buf,blen,errmsg);
      Debug_FileOut("Broad Return","Broad(%d,%d,...,%d,...)=%d",
         destno,
         funcno,
         blen,
         errcode);
   }
   else
   {
      errcode = -100;
      strcpy(errmsg,"Encode XPack failure!");
   }
   return(errcode==0);   
}

