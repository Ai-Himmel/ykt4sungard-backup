/********************************************************************
	created:	2004/10/11
	created:	11:10:2004   15:16
	filename: 	e:\proj\n_dce\xpack\packc.c
	file path:	e:\proj\n_dce\xpack
	file base:	packc
	file ext:	c
	author:		CHENYH
	
	purpose:	本文件纯粹为了兼容提供原来关于CPACK的C类型的各种方法。
   2006-3-23 1:00:21 为了尽量兼容cpack.cpp，而修改了DecodeBufWithArray
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <memory.h>
#ifdef WIN32
#include <Winsock2.h>
#else
#include <unistd.h>
#include <netinet/in.h> /* sockaddr_in */
#endif
#include "PackB.h"
#include "PackHandle.h"
#include "XPack.h"

#define MAXENCODEBLEN   8196

/* 以下代码是用来字节对齐使用的 */
   #ifdef WIN32
      #define __PACKED__ 
      #pragma pack(push,1)
   #else
      #ifdef __GNUC__
         #define __PACKED__	__attribute__ ((packed))
         //#pragma pack(push,1)
      #else
         #ifdef HP_UX
            #define __PACKED__
            #pragma pack 1
         #else
            #define __PACKED__
            #pragma options align=packed
         #endif
      #endif
   #endif

typedef struct _ST_PACK 
{
   char buf[4096];
} __PACKED__ ST_PACK;

typedef struct _ST_CPACK
{
   ST_PACKHEAD head;
   ST_PACK     pack;
} __PACKED__ ST_CPACK;



   #ifdef WIN32
      #pragma pack(pop)
   #else
      #ifdef __GNUC__
      #else
         #ifdef HP_UX
            #pragma pack 0
         #else
            #pragma options align=reset
         #endif
      #endif
   #endif
   #undef __PACKED__

#include "PackC.h"


// 一个缺省创建的实例，采用cpack.dat
CXPack g_pack;


void * GetDefaultXPack()
{
   return(&g_pack);
}

void Reverse(void *buf,int len)
{
   if (len<2) 
      return;

/* ****** Updated by CHENYH at 2004-10-14 17:42:20 ****** 
   if (htons(1)==1)
   {      
      CPackHandle::rev_data(buf,len);
   }
*/
   g_pack.HostByteOrder(buf,len);
}

void Reserve(void *buf,int len)
{
   Reverse(buf,len);
}


int DecodeHead(unsigned char *buf,int len,ST_PACKHEAD *pHead,char *eMsg)
{
   int rtn = g_pack.DecodeHead(buf,len,pHead);
   if (rtn<0)
   {
      sprintf(eMsg,"包大小[%d]小于包头的大小[%d]。\n",len,(int)sizeof(ST_PACKHEAD));
      return(0);
   }
   else 
      return(rtn);
}

int DecodeBufHead(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg)
{
   return(DecodeHead(buf,len,&(pPack->head),eMsg));
}

int DecodeAPack(char *buf,int len,ST_PACKHEAD *phead,ST_PACK *pack,char *eMsg)
{
   int rtn;
   rtn = g_pack.DecodeRow(phead,buf,len,pack);
   if (rtn<0 && eMsg!=NULL)
   {
      if (rtn==-1)
      {
         strcpy(eMsg,"编码有误，有未定义的字段设置!");
      }
      else if (rtn==-2)
      {
         strcpy(eMsg,"解码错误，编码中的字段长度超过定义!");
      }
      else
      {
         strcpy(eMsg,"解码错误，实际编码需要的长度超过提供的长度!");
      }
   }
   return(rtn);
}

int DecodeBuf(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg)
{
   int rtn;
   rtn = g_pack.DecodeHead(buf,len,&(pPack->head));
   if (rtn>0 && pPack->head.recCount>0)
   {
      rtn += g_pack.DecodeRow(&(pPack->head),buf+rtn,len-rtn,&(pPack->pack));
   }
   if (rtn<0)
   {
      if (eMsg!=NULL)
         sprintf(eMsg,"解包失败！错误码%d!",rtn);
      return(0);
   }
   else
      return(rtn);
}

int DecodeBufWithArray(unsigned char *buf,int len,ST_CPACK *pPack,ST_PACK *packArray,
						int *recCount,char *eMsg)
{
   int rtn;
   unsigned int i;
   char *pp=(char *)packArray;
   *recCount = 0;
   int plen = g_pack.GetPackLength();
   rtn = g_pack.DecodeHead(buf,len,&(pPack->head));
   if (rtn>0 && pPack->head.recCount>0)
   {
      rtn += g_pack.DecodeRow(&(pPack->head),buf+rtn,len-rtn,&(pPack->pack));

/* ****** Updated by CHENYH at 2004-12-1 14:07:32 ****** 
      准许多个自定义包解压：但是要求后续自定义包数据长度不超过sizeof(ST_PACK)
      if (g_pack.IsRawDataPack(&(pPack->head)))
      {
         *recCount=1;
         return(rtn);
      }
*/
      if (pp==NULL)
      {
         // 上层说明，只取单包吧：
         return(rtn);
      }
      for (i=1;i<pPack->head.recCount;i++)
      {
         int dlen;  // 2006-3-23 0:54:10 
         dlen = g_pack.DecodeRow(&(pPack->head),buf+rtn,len-rtn,pp);
         pp += plen;
         if (dlen<=0)
            return(0);
         rtn += dlen;
      }
      *recCount = i;
   }
   return(rtn<=0?0:rtn); // 2006-3-23 0:54:18 为了兼容原cpack.cpp中的定义
}

int EmulateEncodeLen(ST_PACKHEAD *phead)
{
   return(g_pack.EmulateEncodeLength(phead));
}

int ModifyHead(ST_PACKHEAD *phead,unsigned char *buf)
{
   int rtn;
   rtn = g_pack.EncodeHead(phead,buf);
   if (rtn<=0)
      return(0);
   else
      return(rtn);
}

int EncodeRow(ST_PACKHEAD *pHead,ST_PACK *pRowPack,unsigned char *buf,int *len,char *eMsg)
{
   int rtn;
   rtn = g_pack.EncodeRow(pHead,pRowPack,buf,MAXENCODEBLEN);
   if (rtn<=0)
      return(0);
   *len = rtn;
   return(rtn);
}

int EncodeBuf(ST_CPACK *pPack,unsigned char *buf,int *len,char *eMsg)
{
   int rtn;
   int l;
   l = g_pack.EncodeHead(&(pPack->head),buf);
   if (l<=0)
      return(0);
   if (pPack->head.recCount>0)
   {
      rtn = g_pack.EncodeRow(&(pPack->head),&(pPack->pack),buf+l,MAXENCODEBLEN-l);
      if (rtn<=0)
         return(0);
      l += rtn;
   }
   *len = l;
   return(l);
}

int EncodeBufArray(ST_CPACK *pPack,ST_PACK *pArray,unsigned char *buf,int *len,char *eMsg)
{
   int rtn;
   unsigned int i;
   char *pp;
   int plen = g_pack.GetPackLength();
   int l;

// ****** Updated by CHENYH at 2005-1-24 10:11:56 ****** 
   // 防止调用错误：
   if (pArray==NULL && pPack->head.recCount>1)
      pPack->head.recCount = 1;  
//////////////////////////////////////////////////////////////////////////


   l = g_pack.EncodeHead(&(pPack->head),buf);
   if (l<=0)
      return(0);

   pp = (char *)(&(pPack->pack));
   for (i=0;i<pPack->head.recCount;i++)
   {
      rtn = g_pack.EncodeRow(&(pPack->head),pp,buf+l,MAXENCODEBLEN-l);
      if (rtn<=0)
         return(0);
      l += rtn;
      pp = ((char *)pArray)+i*plen;
   }

/* ****** Updated by CHENYH at 2005-1-24 10:16:32 ****** 
   rtn = g_pack.EncodeRow(&(pPack->head),&(pPack->pack),buf+l,MAXENCODEBLEN-l);
   if (rtn<=0)
      return(0);
   l += rtn;

   pp = (char *)pArray;
   for (i=1;i<pPack->head.recCount;i++)
   {
      rtn = g_pack.EncodeRow(&(pPack->head),pp,buf+l,MAXENCODEBLEN-l);
      if (rtn<=0)
         return(0);
      l += rtn;
      pp += plen;
   }
*/
   *len = l;
   return(l);
}


int SetParmBit(ST_PACKHEAD *ph,int fidx)
{
   if (g_pack.SetParmBit(ph,fidx)<0)
      return(0);
   else
      return(1);
}

int ClearParmBit(ST_PACKHEAD *ph,int fidx)
{
   if (g_pack.ClearParmBit(ph,fidx)<0)
      return(0);
   else
      return(1);
}

int SetErrorPack(ST_CPACK *inPack,ST_CPACK *outPack,char *emsg,int eCode)
{
   char e[256];
   ST_PACKHEAD *ph=&(outPack->head);
   g_pack.ResetPackHead(ph,&(inPack->head));
   ph->firstflag=1;
   ph->nextflag = 0;
   ph->retCode = eCode;
   memcpy(e,emsg,255);
   e[255]='\0';
   g_pack.AddField(&(outPack->pack),"vsmess",e,ph);
   ph->recCount=1;
   return(1);   
}

int SetErrorPack2(ST_CPACK *outPack,char *emsg,int eCode)
{
   char e[256];
   ST_PACKHEAD *ph=&(outPack->head);
   g_pack.ResetPackHead(ph);
   ph->retCode = eCode;
   memcpy(e,emsg,255);
   e[255]='\0';
   g_pack.AddField(&(outPack->pack),"vsmess",e,ph);
   ph->recCount=1;
   return(1);
}

int SetNormalPack(ST_CPACK *inPack,ST_CPACK *outPack,int nextflag,int recCount)
{
   ST_PACKHEAD *ph=&(outPack->head);
   g_pack.ResetPackHead(ph,&(inPack->head));
   ph->nextflag = nextflag;
   ph->recCount = recCount;
   return(1);
}

int SetNormalPack2(ST_CPACK *outPack,unsigned int reqtype,int recCount)
{
   ST_PACKHEAD *ph=&(outPack->head);
   g_pack.ResetPackHead(ph);
   ph->nextflag = 0;
   //ph->firstflag = 1; // 在CXPack::ResetPackHead()中设置了
   ph->RequestType = reqtype;
   ph->recCount = recCount;
   return(1);
}

int LoadPackDefFile(char *szPackDefFile)
{
   return g_pack.Initialize(szPackDefFile);
}

int ShowPackHead(char *buf,ST_PACKHEAD *phead)
{
   int i;
   int l;
   sprintf(buf,
      "HEAD:RT=%u,FF=%u,NF=%u,REC=%u,RET=%u,QT=%u QN=%s ParmBits=0x",
      phead->RequestType,
      phead->firstflag,
      phead->nextflag,
      phead->recCount,
      phead->retCode,
      phead->hook.queuetype,
      phead->hook.queuename
      );
   l = strlen(buf);
   for (i=0;i<(int)sizeof(phead->ParmBits);i++)
   {
      sprintf(buf+l,"%02X",phead->ParmBits[i]);
      l+=2;
   }
   return(l);
}

bool AddFieldValue(ST_CPACK *pack,const char *fieldname,const char *fieldvalue)
{
   return(g_pack.AddField(&(pack->pack),fieldname,fieldvalue,&(pack->head)));
}

bool AddFieldValueI(ST_CPACK *pack,const char *fieldname,const int ifvalue)
{
   return(g_pack.AddField(&(pack->pack),fieldname,ifvalue,&(pack->head)));
}

bool AddFieldValueD(ST_CPACK *pack,const char *fieldname,const double dvalue)
{
   return(g_pack.AddField(&(pack->pack),fieldname,dvalue,&(pack->head)));
}

int FindFieldIndex(const char *fieldname)
{
   return(g_pack.FindFieldIndex((char *)fieldname));
}
