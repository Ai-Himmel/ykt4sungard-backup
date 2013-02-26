/********************************************************************
	created:	2004/10/11
	created:	11:10:2004   15:08
	filename: 	e:\proj\n_dce\xpack\xpack.cpp
	file path:	e:\proj\n_dce\xpack
	file base:	xpack
	file ext:	cpp
	author:		CHENYH
	
	purpose:	本文件提供的类，为了能够让C++的开发者灵活方便的使用CPACK类打包
            方法。
            2006-2-22 12:55:11 
            在DecodeRow中加入了输入参数不正确的检查，否则容易导致程序崩溃
*********************************************************************/
// XPack.cpp: implementation of the CXPack class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "XPack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXPack::CXPack(const char *szPackDefFile)
{
   phandle.Initialize(szPackDefFile);
}

CXPack::~CXPack()
{

}

int CXPack::Initialize(const char *szPackDefFile)
{
   return(phandle.Initialize(szPackDefFile));
}

void CXPack::ResetPackHead(ST_PACKHEAD *phead, const ST_PACKHEAD *refphead)
{
   memset(phead,0,sizeof(ST_PACKHEAD));
   //phandle.ResetParmBits(phead->ParmBits);  多余2006-2-24 11:21:51
   if (refphead!=NULL)
   {
      phead->userdata=refphead->userdata;
      memcpy(&(phead->hook),&(refphead->hook),sizeof(phead->hook));
      memcpy(&(phead->addr),&(refphead->addr),sizeof(phead->addr));
      phead->RequestType = refphead->RequestType;
      phead->firstflag = refphead->firstflag;
   }
   else
      phead->firstflag = 1;
   phead->nextflag = 0;
   phead->recCount = 1;
   phead->retCode = 0;
}

int CXPack::EncodeHead(const ST_PACKHEAD *pHead, void *buf)
{
   return(phandle.EncodeHead(pHead,buf));
}

int CXPack::EncodeRow(const ST_PACKHEAD *phead, const void *pdata, void *ebuf, int ebsize)
{
   int rtn;
   if (pdata==NULL
      /* ****** Updated by CHENYH at 2005-11-12 16:53:01 ****** 
      ||phead->recCount<=0
      *******************************************************/
      )
      return(0);
   rtn = phandle.EncodeRow(phead->ParmBits,pdata,ebuf,ebsize);
   if (rtn==0)
   {
/* ****** Updated by CHENYH at 2004-10-14 15:23:34 ****** 
      if ((int)(phead->recCount)>ebsize)
         return(-11); // 被编码的数据超过用于编码的缓冲区长度
      if (phead->recCount>0)
      {
         memcpy(ebuf,pdata,phead->recCount);
      }
      return(phead->recCount);
*/
      ST_SDPACK *psd=(ST_SDPACK *)pdata;
      rtn = psd->usDataLength+sizeof(psd->usDataLength);
      if (rtn>ebsize||rtn>phandle.GetPackLength())
         return(-11);
      memcpy(ebuf,pdata,rtn);
      HostByteOrder(ebuf,sizeof(psd->usDataLength));
      return(rtn);
   }
   else
   {
      return(rtn);
   }
}

int CXPack::DecodeHead(const void *buf, int blen, ST_PACKHEAD *pHead)
{
   return(phandle.DecodeHead(buf,blen,pHead));
}

int CXPack::DecodeRow(const ST_PACKHEAD *phead, const void *ebuf, int eblen, void *pdata)
{
   int rtn;
   rtn = phandle.DecodeRow(phead->ParmBits,ebuf,eblen,pdata);
   if (rtn==0)
   {

/* ****** Updated by CHENYH at 2004-10-14 15:39:24 ****** 
      if (phead->recCount>0)
      {
         memcpy(pdata,ebuf,phead->recCount);
      }
      return(phead->recCount);
*/
      ST_SDPACK *psd=(ST_SDPACK *)pdata;
      memcpy(pdata,ebuf,sizeof(psd->usDataLength));
      HostByteOrder(pdata,sizeof(psd->usDataLength));      
      /* ****** Updated by CHENYH at 2006-2-22 12:31:30 ******
      因为出现了传入数据不正确导致这里异常  
      *******************************************************/
      if (eblen<(int)(sizeof(psd->usDataLength)+psd->usDataLength))
      {
         psd->usDataLength = 0;
         return(-10);   //  是不eblen传入参数错
      }
      //////////////////////////////////////////////////////////////////////////
      if (psd->usDataLength>0)
         memcpy(psd->data,((char *)ebuf)+sizeof(psd->usDataLength),psd->usDataLength);
      return(psd->usDataLength+sizeof(psd->usDataLength));
   }
   else
      return(rtn);
}

int CXPack::EmulateEncodeLength(const ST_PACKHEAD *phead)
{
   int rtn = phandle.EmulateEncodeLength(phead->ParmBits);
   if (rtn==0)
      return(phead->recCount);
   else
      return(rtn);
}

int CXPack::SetParmBit(ST_PACKHEAD *phead, int fidx)
{
   return(phandle.SetParmBitByFIndex(phead->ParmBits,fidx));
}

int CXPack::ClearParmBit(ST_PACKHEAD *phead, int fidx)
{
   return(phandle.ClearParmBitByFIndex(phead->ParmBits,fidx));
}

void CXPack::OverwritePack(ST_PACKHEAD *dhead, void *dpack, const ST_PACKHEAD *shead, const void *spack)
{
   phandle.OverwritePack(dhead->ParmBits,dpack,shead->ParmBits,spack);
}

const ST_PDATALIST * CXPack::GetValidFieldInfo(const ST_PACKHEAD *phead, int vfnumber)
{
   return(phandle.GetValidFieldInfo(phead->ParmBits,vfnumber));
}

int CXPack::GetValidFieldCount(const ST_PACKHEAD *phead)
{
   return(phandle.GetValidFieldCount(phead->ParmBits));
}

const ST_PDATALIST * CXPack::GetPackDef(int &ilastvfidx)
{
   return(phandle.GetPackDef(ilastvfidx));
}

int CXPack::IGetFieldValue(const void *prec, int fidx, char *value)
{
   return(phandle.GetFieldValue(prec,fidx,value));
}

int CXPack::IGetFieldValue(const void *prec, const char *fieldname, char *value)
{
   return(phandle.GetFieldValue(prec,fieldname,value));
}

char *CXPack::GetFieldValue(const void *prec, int fidx, char *value)
{
   if (phandle.GetFieldValue(prec,fidx,value)>0)
      return(value);
   else
      return(NULL);
}

char *CXPack::GetFieldValue(const void *prec, const char *fieldname, char *value)
{
   if (phandle.GetFieldValue(prec,fieldname,value)>0)
      return(value);
   else
      return(NULL);
}

char * CXPack::GetPrintFieldValue(const void *prec, int fidx, char *pfv, int precision)
{
   return(phandle.GetPrintFieldValue(prec,fidx,pfv,precision));
}

int CXPack::FindFieldIndex(char *fieldname)
{
   return(phandle.FindFieldIndex(fieldname));
}

int CXPack::FindCFieldIndex(const char *fieldname)
{
   return(phandle.FindFieldIndex(fieldname));
}

bool CXPack::CheckValidField(const ST_PACKHEAD *phead, int fidx)
{
   return(phandle.CheckValidField(phead->ParmBits,fidx));
}

bool CXPack::AddField(void *prec, int fidx, const char *data, ST_PACKHEAD *phead)
{
   return(phandle.AddField(prec,fidx,data,(phead==NULL? NULL:phead->ParmBits)));
}

bool CXPack::AddField(void *prec, int fidx, int ivalue, ST_PACKHEAD *phead)
{
   return(phandle.AddField(prec,fidx,ivalue,(phead==NULL? NULL:phead->ParmBits)));
}

bool CXPack::AddField(void *prec, int fidx, double dvalue, ST_PACKHEAD *phead)
{
   return(phandle.AddField(prec,fidx,dvalue,(phead==NULL? NULL:phead->ParmBits)));
}

bool CXPack::AddField(void *prec, const char *fieldname, const char *data, ST_PACKHEAD *phead)
{
   return(phandle.AddField(prec,fieldname,data,(phead==NULL? NULL:phead->ParmBits)));
}

bool CXPack::AddField(void *prec, const char *fieldname, int ivalue, ST_PACKHEAD *phead)
{
   return(phandle.AddField(prec,fieldname,ivalue,(phead==NULL? NULL:phead->ParmBits)));
}

bool CXPack::AddField(void *prec, const char *fieldname, double dvalue, ST_PACKHEAD *phead)
{
   return(phandle.AddField(prec,fieldname,dvalue,(phead==NULL? NULL:phead->ParmBits)));
}

int CXPack::GetFieldValueI(const void *prec, int fidx)
{
   return(phandle.GetFieldValueI(prec,fidx));
}


int CXPack::GetFieldValueI(const void *prec, const char *fieldname)
{
   return(phandle.GetFieldValueI(prec,fieldname));
}

double CXPack::GetFieldValueD(const void *prec, int fidx)
{
   return(phandle.GetFieldValueD(prec,fidx));
}

double CXPack::GetFieldValueD(const void *prec, const char *fieldname)
{
   return(phandle.GetFieldValueD(prec,fieldname));
}

unsigned short CXPack::xmk_crc16(const void *ptr, int count)
{
   return(CPackHandle::xmk_crc16(ptr,count));
}

char * CXPack::LRTrim(char *str)
{
   return(CPackHandle::LRTrim(str));
}

void CXPack::rev_data(void *data, unsigned int datalen)
{
   CPackHandle::rev_data(data,datalen);
}

bool CXPack::IsRawDataPack(const ST_PACKHEAD *phead)
{
   int mbyte;
   /* ****** Updated by CHENYH at 2004-10-14 15:55:08 ****** 
   unsigned char bmask;
   int fidx;
   for (mbyte=fidx=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0;bmask<<=1,fidx++)
      {
         if (fidx>254)
            return(true);
         if (phead->ParmBits[mbyte]&bmask)
            return(false);
      }
   }
   return(true);
   */
   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      if (phead->ParmBits[mbyte]!=0)
         return(false);
   }
   return(true);
}

int CXPack::GetPackLength()
{
   return(phandle.GetPackLength());
}

void CXPack::HostByteOrder(void *data, unsigned int datalength)
{
   phandle.HostByteOrder(data,datalength);
}
int CXPack::SetPackHead(ST_PACKHEAD *head,int recCount,int retCode,...)
{
	memset(head,0,sizeof(ST_PACKHEAD));
	head->firstflag = 1;
	head->nextflag = 0; 
	head->recCount = recCount;
	head->retCode = retCode;
	va_list ap;
	int arg;
	va_start(ap, retCode);
	while ((arg = va_arg(ap, int)) > END_FIELDMARK)
	{
		SetParmBit(head, arg);
	}
	va_end(ap);
	return 0;
}

bool CXPack::IsValidField(ST_PACKHEAD *phead, int fidx)
{
   if (fidx>=0 && fidx<=phandle.iLastPField && phandle.pdlist[fidx].wType!=0)
   {
      return (((phead->ParmBits[fidx>>3])&(0x01<<(fidx&0x07)))!=0);
   }
   else return(false);
}

bool CXPack::IsValidField(ST_PACKHEAD *phead, char *fieldname)
{
   return(IsValidField(phead,FindFieldIndex(fieldname)));
}



int CXPack::CheckEncodePack(const void *ebuf, int eblen,ST_PACKHEAD *ph)
{
   int rtn;
   int i;
   unsigned char *pbuf = (unsigned char *)ebuf;
   rtn = phandle.CheckEncodeHead(ebuf,eblen,ph);
   if (rtn<0)
      return(rtn); // -1:eblen ERROR,-2:INVALID recCount,-3:INVALID firstflag/nextflag ,-10:INVALID PARMBITS(over field),-11:INVALID PARMBITS(invalid parmbit)
   if (rtn==0)
   {
      // ST_SDPACK record
      ST_SDPACK *sdp;
      unsigned short usLen;
      int po = sizeof(ST_PACKHEAD);
      for (i=0;i<ph->recCount;i++)
      {
         if (po+sizeof(sdp->usDataLength)>eblen)
            return(-20); // lack of eblen
         sdp = (ST_SDPACK *)(pbuf+po);
         memcpy(&usLen,&(sdp->usDataLength),sizeof(usLen));
         HostByteOrder(&usLen,sizeof(usLen));
         if (usLen+sizeof(usLen)>phandle.GetPackLength())
            return(-30);  // too long SDPACK Data
         po += usLen+sizeof(usLen);
      }
      return(po);
   }
   else
   {
      rtn = (phandle.CheckEncodeRows(pbuf+sizeof(ST_PACKHEAD),eblen-sizeof(ST_PACKHEAD),ph));
      if (rtn<0)
         return(rtn);
      else
         return(rtn+sizeof(ST_PACKHEAD));
   }
}
