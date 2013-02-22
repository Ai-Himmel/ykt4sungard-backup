/********************************************************************
	created:	2004/09/23
	created:	23:9:2004   23:26
	filename: 	e:\proj\goldmem\ksbcc\packbase\packhandle.cpp
	file path:	e:\proj\goldmem\ksbcc\packbase
	file base:	packhandle
	file ext:	cpp
	author:		陈永华
	
	purpose:	利用报文结构定义文件，实现报文编码、解码，字段赋值工作；
            为了及早发现上层程序的错误（包括隐含的），采用严格的检查；

  2004/10/21: CYH 
            在HP小型机器中，出现了BUS-Error，只好修改对pdlist[i]中数据的存取
            为了简化在普通机器上的编码，可能也可以优化一些性能，
            特用宏定义NOBUSERROR保留原来的部分
            NOBUSERROR

  2006-12-23 0:44:39 
            DecodeHead: 为了防止乱数据包接受解码导致利用本解包的出现故障
            限制ph->recCount的值超过MAXPACKROWS, 否则，直接影响BCC、BU部分
            使用PackC部分的代码引起的不稳定。
*********************************************************************/
// PackHandle.cpp: implementation of the CPackHandle class.
//
//////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <memory.h>
#ifdef WIN32
//   #include <Winsock2.h>
#else
   #include <unistd.h>
//   #include <netinet/in.h> /* sockaddr_in */
#endif
#include "PackB.h"
#include "PackHandle.h"

//static unsigned char _bits[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPackHandle::CPackHandle()
{
/* ****** Updated by CHENYH at 2005-12-3 15:05:59 ****** 
   // 不想用ws2_32.lib库
   bReverse = (ntohs(1)==1);
*******************************************************/
   int i=1;
   bReverse = ((*(char *)&i)==0);  // true: 0x00,0x00,0x00,0x01; false: 0x01,0x00,0x00,0x00

   iMode = 0;  // as Default
   memset(version,0,sizeof(version));
   memset(pdlist,0,sizeof(pdlist));
}

CPackHandle::~CPackHandle()
{

}


// 函数名: CPackHandle::Initialize
// 编程  : 陈永华 2004-9-23 23:46:48
// 描述  : 初始化本包处理句柄，装载指定的包格式文件
// 返回  : int 
//           >=0  - 成功 返回最后一个有效字段号；
//            -1  - 包格式文件不能打开；
//            -2  - 指定文件格式错误；不能被本版本所辨别 
// 参数  : char *szPackDefFile：包格式文件名称
/* ****** designed by CHENYH at 2004-9-23 23:48:16 ****** 
包格式文件的格式定义：
   int i1;  本文件生成的机器上整数1的表示值，以免本文件最终使用的机器与生成的机器字序格式的不同导致结构紊乱
   unsigned char iMode;
   char version[20];
   unsigned char iVersionID;
   int iLastPField;
   ST_PDATALIST pdlist[255];
*/
int CPackHandle::Initialize(const char *szPackDefFile)
{
   FILE *pdfile;
   int i1,i;
   unsigned int offset;

   
   iLastPField = -1;
   nPackLength = 0;
   memset(pdlist,0,sizeof(pdlist));
   pdfile = fopen(szPackDefFile,"rb");
   if (pdfile==NULL)
   {
      return(-1);
   }
   i1 = 0;
   fread(&i1,sizeof(i1),1,pdfile);
   i=1; 
   rev_data(&i,sizeof(i));
   if (i1!=1&&i1!=i)
   {
      fclose(pdfile);
      return(-2);
   }
   fread(&iMode,sizeof(iMode),1,pdfile);

   fread(version,sizeof(version),1,pdfile);
   fread(&iVersionID,sizeof(iVersionID),1,pdfile);
/* ****** Updated by CHENYH at 2004-10-7 10:51:19 ****** 
   if (i1!=1)
   {
      rev_data(&iVersionID,sizeof(iVersionID));
   }
*/
   fread(&iLastPField,sizeof(iLastPField),1,pdfile);
   if (i1!=1)
   {
      rev_data(&iLastPField,sizeof(iLastPField));
   }
   if (iLastPField<1||iLastPField>=PARMBITS)
   {
      fclose(pdfile);
      return(-3);
   }
   if ((int)fread(pdlist,sizeof(ST_PDATALIST),iLastPField+1,pdfile)<iLastPField+1)
   {
      fclose(pdfile);
      return(-4);
   }

   ST_PDATALIST *pfd;

   if (i1!=1)
   {
      for (i=0,pfd=pdlist;i<=iLastPField;i++,pfd++)
      {
         rev_data(&(pfd->nLength),sizeof(pfd->nLength));
         rev_data(&(pfd->dwOffset),sizeof(pfd->dwOffset));
      }
   }
   fclose(pdfile);
   // 检查格式文件的完整性：
   offset = 0; 
   pfd=pdlist; // 2004/10/20
   for (i=0;i<=iLastPField;i++,pfd++)
   {
      switch (pfd->wType)
      {
      case PDL_INT:
         if (pfd->nLength!=sizeof(int))
         {
            return(-5);
         }
      case PDL_DOUBLE:
         if (pfd->wType==PDL_DOUBLE)
         {
            if (pfd->nLength!=sizeof(double))
            {
               return(-6);
            }
         }
      case PDL_CHAR:
      case PDL_VCHAR:
      case PDL_UCHAR:
         if (pfd->nLength<=0||pfd->nLength>256)
         {
            return(-7);
         }
         if (offset!=pfd->dwOffset)
         {
            return(-8);
         }
         offset += pfd->nLength;         
         break;
      default:
         break;
      }
   }
   nPackLength = offset;
   return(iLastPField);
}

/* Swap bytes in 16 bit value.  */
#define _cyh__bswap_16(x) \
   ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))

/* Swap bytes in 32 bit value.  */
#define _cyh__bswap_32(x) \
   ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |		      \
   (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))

// 函数名: CPackHandle::rev_data
// 编程  : 陈永华 2004-9-24 0:07:10
// 描述  : 将data的字序反转
// 返回  : void 
// 参数  : void *data
// 参数  : unsigned int datalen
void CPackHandle::rev_data(void *data, unsigned int datalen)
{
#ifdef NOBUSERROR
   switch (datalen)
   {
   case 4:
      {
         register unsigned int __x = *(unsigned int *)data;
         *(unsigned int *)data = _cyh__bswap_32(__x);
      }
      return;
   case 8:
      {
         register unsigned int __x,__y;
         __x = ((unsigned int *)data)[0];
         __y = ((unsigned int *)data)[1];
         ((unsigned int *)data)[0]=_cyh__bswap_32(__y);
         ((unsigned int *)data)[1]=_cyh__bswap_32(__x);
      }
      return;
   case 2:
      {
         register unsigned short __x = *(unsigned short *)data;
         *(unsigned short *)data = _cyh__bswap_16(__x);
      }
      return;
   default:
      {
         unsigned char *pb=(unsigned char *)data;
         unsigned char *pe=pb+datalen-1;
         unsigned char b;
         while (pb<pe)
         {
            b = *pb;
            *pb=*pe;
            *pe=b;
            pb++;pe--;
         }
      }
   }
#else
   register unsigned char *pb=(unsigned char *)data;
   register unsigned char *pe=pb+datalen-1;
   register unsigned char b;
   while (pb<pe)
   {
      b = *pb;
      *pb=*pe;
      *pe=b;
      pb++;pe--;
   }
#endif
}


// 函数名: CPackHandle::P_Index
// 编程  : 陈永华 2004-9-24 15:42:40
// 描述  : 位图－》字段序号的转换
// 返回  : int 返回字段序号值； <0: 非法位图；
// 参数  : int parmbit 〔IN〕 位图
int CPackHandle::P_Index(int parmbit)
{
   int index;
   unsigned char bmask=0x01;
   unsigned char fpb=(unsigned char)(parmbit&0x00ff);
   for (index=0;index<8;index++,bmask<<=1)
   {
      if (bmask==fpb) break;
   }
   if (index>=8)
      return(-1);
   index += (parmbit&0xff00)>>5;
   if (index>=PARMBITS)
      return(-2);
   return(index);
}


// 函数名: CPackHandle::EncodeHead
// 编程  : 陈永华 2004-9-24 16:30:57
// 描述  : 将包头数据编码到指定的缓冲区
// 返回  : int ： sizeof(ST_PACKHEAD)
// 参数  : ST_PACKHEAD *pHead 〔IN〕 包头数据
// 参数  : void *buf 〔OUT〕存放编码的缓冲区
int CPackHandle::EncodeHead(const ST_PACKHEAD *pHead, void *buf)
{
   ST_PACKHEAD *ph = (ST_PACKHEAD *)buf;
   memcpy(buf,pHead,sizeof(ST_PACKHEAD));
   if (bReverse)
   {
      rev_data(&(ph->RequestType),sizeof(ph->RequestType));
      rev_data(&(ph->recCount),sizeof(ph->recCount));
      rev_data(&(ph->retCode),sizeof(ph->retCode));
      rev_data(&(ph->hook.UserID),sizeof(ph->hook.UserID));
      rev_data(&(ph->hook.queuetype),sizeof(ph->hook.queuetype));
   }
   return(sizeof(ST_PACKHEAD));
}




// 函数名: CPackHandle::DecodeHead
// 编程  : 陈永华 2004-9-24 16:32:51
// 描述  : 将编码缓冲区中解码到包头中
// 返回  : int ：sizeof(ST_PACKHEAD) ；<0 - 缓冲区长度太小
// 参数  : void *buf [IN] : 编码缓冲区 
// 参数  : int blen [IN] : 编码缓冲区长度
// 参数  : ST_PACKHEAD *ph [OUT]: 包头指针
int CPackHandle::DecodeHead(const void *buf, int blen, ST_PACKHEAD *ph)
{
   if (blen<(int)sizeof(ST_PACKHEAD))
      return(-1);
   memcpy(ph,buf,sizeof(ST_PACKHEAD));
   if (bReverse)
   {
      rev_data(&(ph->RequestType),sizeof(ph->RequestType));
      rev_data(&(ph->recCount),sizeof(ph->recCount));
      rev_data(&(ph->retCode),sizeof(ph->retCode));
      rev_data(&(ph->hook.UserID),sizeof(ph->hook.UserID));
      rev_data(&(ph->hook.queuetype),sizeof(ph->hook.queuetype));
   }
   // 2006-12-23 0:44:39 为了防止乱数据包接受解码导致利用本解包的出现故障
   if (ph->recCount>MAXPACKROWS)
   {
      ph->recCount = MAXPACKROWS;
   }
   return(sizeof(ST_PACKHEAD));
}


// 函数名: CPackHandle::EncodeRow
// 编程  : 陈永华 2004-9-26 14:53:27
// 描述  : 根据位图，将一个记录数据pdata编码到编码缓冲区中
// 返回  : int 
/* 
      >=0:成功，返回编码占用的长度；
      <0:编码失败 
         -1: 编码位图有误(有未定义的位图设置); 
         -10: 缓冲区长度不足
*/
// 参数  : unsigned char *parmbits 〔IN〕：32字节的编码位图表
// 参数  : void *pdata （IN）：记录数据，记录数据结构参见本报文句柄初始化中装载
// 参数  : void *ebuf （OUT）：用于编码存放的缓冲区
// 参数  : int ebsize （IN）：编码缓冲区的最大长度
int CPackHandle::EncodeRow(const unsigned char *parmbits, const void *pdata, void *ebuf, int ebsize)
{
   int mbyte;
   unsigned char bmask;
   int eblen=0;  // 真实编码数据长度
   unsigned char *pc=(unsigned char *)ebuf;
   int eflen;    // 对每个字段的编码长度
   ST_PDATALIST *pfd=pdlist;
      
   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0x00;bmask<<=1,pfd++)
      {
         if (pfd>pdlist+iLastPField)
            return(eblen);  // 不用再检查编码下去了，因为后面都为未定义的字段
         if (parmbits[mbyte]&bmask)
         {
            if (eblen+pfd->nLength+1>ebsize)
               return(-10);
            eflen = EncodeSingleField(pfd,pdata,pc);
            if (eflen<0)
               return(eflen);
            else
            {
               eblen+=eflen; 
               pc+=eflen;
            }
         }
      }
   }
   return(eblen);
}


// 函数名: CPackHandle::EncodeSingleField
// 编程  : 陈永华 2004-9-26 16:02:48
// 描述  : 根据字段定义，对指定的记录pdata中的相应字段进行编码，编码存放到pbuf中
// 返回  : int >0:成功返回编码长度；-1: 失败，该字段没有在结构定义中定义
// 参数  : ST_PDATALIST *pfd （IN）：结构定义中的编码字段定义
// 参数  : void *pdata（IN）：要编码的记录数据
// 参数  : void *pbuf （OUT）：编码存放的缓冲区
int CPackHandle::EncodeSingleField(const ST_PDATALIST *pfd, const void *pdata, void *pbuf)
{
   int flen;
   char *pf=((char *)pdata)+pfd->dwOffset;
   switch (pfd->wType)
   {
   case PDL_CHAR:
   case PDL_VCHAR:
      {
         unsigned char *pb=(unsigned char *)pbuf;
         if (iMode==0)
         {
            // 兼容原来CPACK的编码方式:
            if (pfd->wType==PDL_CHAR)
            {
               flen = pfd->nLength;
               memcpy(pb,pf,flen);
            }
            else
            {
               unsigned short slen;
               slen = strlen(pf)+1;
               if (slen>256)
                  slen = 256;
               //*(short *)pb=(short)flen;
               memcpy(pb,&slen,sizeof(slen));
               if (bReverse)
               {
                  rev_data(pb,sizeof(short));
               }
               memcpy(pb+sizeof(short),pf,slen);
               flen = slen + sizeof(short);
            }
         }
         else
         {
            // 新的编码方式
            flen = strlen(pf);
            if (flen>pfd->nLength)
               flen=pfd->nLength;
            if (flen>255)
               flen = 255;
            pb[0]=(unsigned char)flen;
            memcpy(pb+1,pf,flen); 
            flen++; // 加上一个长度字段
         }
      }
      break;
   case PDL_UCHAR:
      flen = pfd->nLength;
      memcpy(pbuf,pf,flen);
      break;
   case PDL_INT:
   case PDL_DOUBLE:
      flen = pfd->nLength;
      memcpy(pbuf,pf,flen);
      if (bReverse)
      {
         rev_data(pbuf,flen);
      }
      break;
   default:
      return(-1);
   }
   return(flen);
}


// 函数名: CPackHandle::DecodeSingleField
// 编程  : 陈永华 2004-9-26 16:25:55
// 描述  : 根据字段定义，从编码位置pbuf中的相应字段解码到记录pdata的字段中
// 返回  : int >0:成功返回编码长度，用于后续的编码位置调整；<0: 失败，-1 无该字段定义, -2 编码错误，编码长度，超过字段定义长度
// 参数  : ST_PDATALIST *pfd （IN）：结构定义中的编码字段定义
// 参数  : void *pbuf （IN）：编码位置
// 参数  : void *pdata （OUT）：解码字段存放的记录
int CPackHandle::DecodeSingleField(const ST_PDATALIST *pfd, const void *pbuf, void *pdata)
{
   int flen;
   char *pf=((char *)pdata)+pfd->dwOffset;
   switch (pfd->wType)
   {
   case PDL_CHAR:
   case PDL_VCHAR:
      {
         unsigned char *pb=(unsigned char *)pbuf;
         if (iMode==0)
         {
            // 兼容原来CPACK的编码方式:
            if (pfd->wType==PDL_CHAR)
            {
               flen = pfd->nLength;
               memcpy(pf,pbuf,flen);
            }
            else
            {
               short vsl;
               memcpy(&vsl,pbuf,sizeof(short));
               if (bReverse)
               {
                  rev_data(&vsl,sizeof(short));
               }
               flen = vsl;
               if (flen>256)
                  return(-2);
               
               memcpy(pf,pb+sizeof(short),flen);
               flen += sizeof(short);
            }
         }
         else
         {
            // 新的编码方式
            flen = pb[0];
            if (flen>pfd->nLength)
               return(-2);
            memcpy(pf,pb+1,flen);
            if (flen<pfd->nLength)
               pf[flen]='\0';
            flen++; // 加上一个长度字段
         }
      }
      break;
   case PDL_UCHAR:
      flen = pfd->nLength;
      memcpy(pf,pbuf,flen);
      break;
   case PDL_INT:
   case PDL_DOUBLE:
      flen = pfd->nLength;
      memcpy(pf,pbuf,flen);
      if (bReverse)
      {
         rev_data(pf,flen);
      }
      break;
   default:
      return(-1);
   }
   return(flen);   
}



// 函数名: CPackHandle::DecodeRow
// 编程  : 陈永华 2004-9-26 17:09:58
// 描述  : 根据位图表parmbits，将编码缓冲区ebuf中的数据，解码到数据记录pdata中
// 返回  : int 
/* 
      >=0:成功，返回编码占用的长度；
      <0:解码失败 
         -1: 编码位图有误(有未定义的位图设置); 
         -2: 编码中字段数据超出定义;
         -10: 缓冲区长度不足
*/
// 参数  : unsigned char *parmbits （IN）:位图表
// 参数  : void *ebuf （IN）:
// 参数  : int ebtlen （IN）:
// 参数  : void *pdata （OUT）:
int CPackHandle::DecodeRow(const unsigned char *parmbits, const void *ebuf, int ebtlen, void *pdata)
{
   int mbyte;
   unsigned char bmask;
   int eblen=0;  // 真实编码数据长度
   unsigned char *pc=(unsigned char *)ebuf;
   int eflen;    // 对每个字段的编码长度
   ST_PDATALIST *pfd=pdlist;

   memset(pdata,0,nPackLength);
   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0x00;bmask<<=1,pfd++)
      {
         if (pfd>pdlist+iLastPField)
            return(eblen);
         if (parmbits[mbyte]&bmask)
         {
            eflen = DecodeSingleField(pfd,pc,pdata);
            if (eflen<0)
               return(eflen);
            else
            {
               eblen += eflen;
               pc+=eflen;
               if (eblen>ebtlen)
                  return(-3);  // 解码需要的长度超出编码的实际长度
            }
         }
      }
   }
   return(eblen);
}


// 函数名: CPackHandle::FindFieldIndex
// 编程  : 陈永华 2004-9-27 12:19:30
// 描述  : 从报文结构定义中，根据字段名字符串查找字段编号
// 返回  : int >=0: 成功找到，返回对应字段编号；<0:失败，本结构定义中，没有指定名称的字段
// 参数  : char *fieldname（IN）: 字段名称
int CPackHandle::FindFieldIndex(const char *fieldname)
{
   int fidx;
   ST_PDATALIST *pfd=pdlist;
   for (fidx=0;fidx<=iLastPField;fidx++,pfd++)
   {
      if (pfd->wType>0)
      {
         if (strcmp(fieldname,pfd->szName)==0)
            return(fidx);
      }
   }
   return(-1);
}




// 函数名: CPackHandle::SetParmBit
// 编程  : 陈永华 2004-9-29 18:37:24
// 描述  : 用字段的位图方式，设置数据报文的位图
// 返回  : int 返回字段的序号，<0:不正确的位图（与初始化的报文格式不符）
// 参数  : unsigned char *parmbits 〔OUT〕： 报文的位图表
// 参数  : int fpb (IN): 指定字段的位图值
int CPackHandle::SetParmBit(unsigned char *parmbits, int fpb)
{
   int fidx = P_Index(fpb);
   return(SetParmBitByFIndex(parmbits,fidx));
}


// 函数名: CPackHandle::SetParmBitByFIndex
// 编程  : 陈永华 2004-9-29 18:40:39
// 描述  : 用字段的顺序，设置数据报文的位图
// 返回  : int 返回字段的序号，<0: 不正确的位图（与初始化的报文格式不符）
// 参数  : unsigned char *parmbits 〔OUT〕： 报文的位图表
// 参数  : int fidx （IN）：指定字段序号
int CPackHandle::SetParmBitByFIndex(unsigned char *parmbits, int fidx)
{
   return(SetPBIndex(parmbits,fidx,true));
}


// 函数名: CPackHandle::ClearParmBit
// 编程  : 陈永华 2004-9-29 19:00:46
// 描述  : 用字段的位图方式，清除数据报文的位图
// 返回  : int 返回字段的序号，<0:不正确的位图（与初始化的报文格式不符）
// 参数  : unsigned char *parmbits 〔OUT〕： 报文的位图表
// 参数  : int fpb (IN): 指定字段的位图值
int CPackHandle::ClearParmBit(unsigned char *parmbits, int fpb)
{
   int fidx = P_Index(fpb);
   return(ClearParmBitByFIndex(parmbits,fidx));   
}


// 函数名: CPackHandle::ClearParmBitByFIndex
// 编程  : 陈永华 2004-9-29 18:52:28
// 描述  : 用字段的顺序，清除数据报文的位图
// 返回  : int 返回字段的序号，<0: 不正确的位图（与初始化的报文格式不符）
// 参数  : unsigned char *parmbits 〔OUT〕： 报文的位图表
// 参数  : int fidx （IN）：指定字段序号
int CPackHandle::ClearParmBitByFIndex(unsigned char *parmbits, int fidx)
{
   return(SetPBIndex(parmbits,fidx,false));
}




// 函数名: CPackHandle::GetEncodeFieldLength
// 编程  : 陈永华 2004-9-29 19:17:21
// 描述  : 以最大编码长度估算一个字段的编码长度
// 返回  : int ：最大编码长度
// 参数  : ST_PDATALIST *pfd（IN）：被编码的字段定义
int CPackHandle::GetEncodeFieldLength(const ST_PDATALIST *pfd)
{
   switch(pfd->wType) {
   case PDL_CHAR:
   case PDL_VCHAR:
      if (iMode==0)
      {
         // 兼容原来CPACK的编码方式:
         if (pfd->wType==PDL_CHAR)
         {
            return(pfd->nLength);
         }
         else
         {
            return(pfd->nLength+sizeof(short));
         }
      }
      else
      {
         return(pfd->nLength+1);
      }
   case PDL_INT:
   case PDL_DOUBLE:
      return(pfd->nLength);
   default:
      return(0);
   }
}



// 函数名: CPackHandle::EmulateEncodeLength
// 编程  : 陈永华 2004-9-29 19:24:04
// 描述  : 根据当前指定的位图表，估算一个数据记录编码需要最长的缓冲区
// 返回  : int ：返回需要编码缓冲区长度（字节）
// 参数  : unsigned char *parmbits（IN）：指定的位图表
int CPackHandle::EmulateEncodeLength(const unsigned char *parmbits)
{
   ST_PDATALIST *pfd=pdlist;
   int elen=0;
   int mbyte;
   unsigned char bmask;

   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0x00;bmask<<=1,pfd++)
      {
         if (pfd>pdlist+iLastPField)
            return(elen);
         if (parmbits[mbyte]&bmask)
         {
            elen += GetEncodeFieldLength(pfd);
         }
      }
   }
   return(elen);
}

char * CPackHandle::LRTrim(char *str)
{
   int i,len;
   len = strlen(str);
   for(i = len - 1; i >= 0; i --)
   {
      if(str[i] != ' ' && str[i] != 9)
         break;
      else
         str[i] = 0;
   }
   for(i = 0; i < len; i ++)
   {
      if(str[i] != ' ' && str[i] != 9)
         break;
   }
   if(i != 0)
   {
      strncpy(str, str + i, len - i);
      str[len - i] = 0;
   }
   return(str);   
}




bool CPackHandle::SetFieldValue(void *prec, const ST_PDATALIST *pfd, char *data)
{
   unsigned char *pdata;
   int l;
   pdata = ((unsigned char *)prec)+pfd->dwOffset;
   switch (pfd->wType)
   {
   case PDL_CHAR:
   case PDL_VCHAR:
      /* ****** Updated by CHENYH at 2006-2-27 0:04:01 ****** 
      也许这个字段的前后字符串中就有whitespace字符呢？
      LRTrim(data);
      *******************************************************/
      l = strlen(data);
      if (l>=pfd->nLength)
      {
         l = pfd->nLength-1;
      }
      memcpy(pdata,data,l);
      pdata[l]='\0';
      break;
   case PDL_UCHAR:
      if (data[0]=='0'&&(data[1]=='x'||data[1]=='X'))
      {
         Hex2Buffer(pdata,pfd->nLength,data+2);
      }
      else
      {
         memcpy(pdata,data,pfd->nLength);
      }
      break;
#ifdef NOBUSERROR
   case PDL_INT:
      *(int *)pdata = atoi(data);
      break;
   case PDL_DOUBLE:
      *(double *)pdata = atof(data);
      break;
#else
   case PDL_INT:
      {
         // 因为在HP-UX下，如果直接如下使用，会出现Bus error:
         //*(int *)pdata = atoi(data);
         // 如下才不会出现错误
         int dd=atoi(data);
         memcpy(pdata,&dd,sizeof(dd));
      }
      break;
   case PDL_DOUBLE:
      {
         //*(double *)pdata = atof(data);
         double dd=atof(data);
         memcpy(pdata,&dd,sizeof(dd));
      }
      break;
#endif
   default:
      return(false);
   }
   return(true);
}

inline unsigned char Hex2Byte(char hex)
{
   if (hex>='a'&&hex<='f')
      return(hex-'a'+10);
   if (hex>='A'&&hex<='F')
      return(hex-'A'+10);
   if (hex>='0'&&hex<='9')
      return(hex-'0');
   return(0);
}


void CPackHandle::Hex2Buffer(unsigned char *buf, int len, char *hex)
{
   int i;
   char *phex=hex;
   for (i=0;i<len;i++)
   {
      if (*phex=='\0')
         break;
      buf[i] = (Hex2Byte(*phex)<<4); phex++;
      buf[i] |=(Hex2Byte(*phex)); phex++;
   }
   for (;i<len;i++)
   {
      buf[i]=0;
   }
}


// 函数名: CPackHandle::SetFieldValue
// 编程  : 陈永华 2004-9-30 21:52:27
// 描述  : 对数据记录prec中的指定字段pfd，赋值（用于各种类型）
// 返回  : bool 赋值成功与否
// 参数  : void *prec(OUT): 数据记录
// 参数  : ST_PDATALIST *pfd（IN）：指定的字段定义
// 参数  : char *data
bool CPackHandle::SetFieldValue(void *prec, int fidx, char *data)
{
   ST_PDATALIST *pfd=pdlist+fidx;
   if (fidx<0 || fidx>iLastPField || pfd->wType==0)
      return(false); // 字段编号超出结构定义范围, 或该字段没有定义
   return(SetFieldValue(prec,pdlist+fidx,data));
}


// 函数名: CPackHandle::SetFieldValue
// 编程  : 陈永华 2004-9-30 21:51:23
// 描述  : 对数据记录prec中的指定字段pfd，赋值（用于int、char *类型）
// 返回  : bool 赋值成功与否
// 参数  : void *prec(OUT): 数据记录
// 参数  : ST_PDATALIST *pfd（IN）：指定的字段定义
// 参数  : int ivalue（IN）：字段的int值
bool CPackHandle::SetFieldValue(void *prec, const ST_PDATALIST *pfd, int ivalue)
{
   char sztmp[40];
   sprintf(sztmp,"%d",ivalue);
   return(SetFieldValue(prec,pfd,sztmp));
}


// 函数名: CPackHandle::SetFieldValue
// 编程  : 陈永华 2004-9-30 21:48:37
// 描述  : 对数据记录prec中的指定字段pfd，赋值（用于double、char *类型）
// 返回  : bool 赋值成功与否
// 参数  : void *prec(OUT): 数据记录
// 参数  : ST_PDATALIST *pfd（IN）：指定的字段定义
// 参数  : double dvalue（IN）：字段的double值
bool CPackHandle::SetFieldValue(void *prec, const ST_PDATALIST *pfd, double dvalue)
{
   char sztmp[260];
   sprintf(sztmp,"%lf",dvalue);
   return(SetFieldValue(prec,pfd,sztmp));
}

// 函数名: AddField
// 编程  : 陈永华 2004-9-30 18:12:29
// 描述  : 对记录prec中的编号为fidx的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
// 返回  : bool 赋值成功与否
// 参数  : void *prec (OUT): 数据记录
// 参数  : int fidx(IN): 赋值的字段编号
// 参数  : char *data(IN): 字段的值
// 参数  : unsigned char *parmbits(OUT): 记录的位图表，
//          如果不为NULL，则对此表的位图作相应的设置
//          否则，仅作赋值处理
bool CPackHandle::AddField(void *prec, int fidx, const char *data, unsigned char *parmbits)
{
   // char buf[260]={0}; 2006-2-27 0:06:44
   // int i;
   if (fidx<0||fidx>iLastPField)
      return(false);
   /* ****** Updated by CHENYH at 2006-2-27 0:07:30 ****** 
   // 在SetFieldValue部分也会正常处理PDL_UCHAR, 并且也不会更改data中的值
   // 所以直接使用data变量，并为了调用关系data类型强制为char *
   switch (pdlist[fidx].wType)
   {
   case PDL_UCHAR:
      if (data[0]=='0' &&(data[1]=='x'||data[1]=='X'))
      {
         Hex2Buffer((unsigned char *)buf,pdlist[fidx].nLength,(char *)data+2);
      }
      else
      {
         memcpy(buf,data,pdlist[fidx].nLength);
      }
      buf[pdlist[fidx].nLength]=0;
      break;
   default:
      for (i=0;i<256;i++)
      {
         buf[i]=data[i];
         if (buf[i]=='\0') break;
      }
      break;
   }
   buf[255]='\0';
   if (SetFieldValue(prec,fidx,buf))
   *******************************************************/
   if (SetFieldValue(prec,fidx,(char *)data))
   {
      if (parmbits!=NULL)
         SetParmBitByFIndex(parmbits,fidx);
      return(true);
   }
   else return(false);
}

// 函数名: AddField
// 编程  : 陈永华 2004-9-30 18:08:26
// 描述  : 对记录prec中的名为fieldname的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
// 返回  : bool 赋值成功与否
// 参数  : void *prec (OUT): 数据记录
// 参数  : char *fieldname(IN): 字段名称
// 参数  : char *data(IN): 字段的值
// 参数  : unsigned char *parmbits(OUT): 记录的位图表，
//          如果不为NULL，则对此表的位图作相应的设置
//          否则，仅作赋值处理
bool CPackHandle::AddField(void *prec, const char *fieldname, const char *data, unsigned char *parmbits)
{
   int fidx = FindFieldIndex(fieldname);
   if (fidx<0)
      return(false);
   return(AddField(prec,fidx,data,parmbits));
}

// 函数名: AddField
// 编程  : 陈永华 2004-9-30 18:11:45
// 描述  : 对记录prec中的编号为fidx的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
// 返回  : bool 赋值成功与否
// 参数  : void *prec (OUT): 数据记录
// 参数  : int fidx(IN): 赋值的字段编号
// 参数  : int ivalue(IN): 字段的值
// 参数  : unsigned char *parmbits(OUT): 记录的位图表，
//          如果不为NULL，则对此表的位图作相应的设置
//          否则，仅作赋值处理
bool CPackHandle::AddField(void *prec, int fidx, int ivalue, unsigned char *parmbits)
{
   char sztmp[40];
   sprintf(sztmp,"%d",ivalue);
   return(AddField(prec,fidx,sztmp,parmbits));
}

// 函数名: AddField
// 编程  : 陈永华 2004-9-30 18:09:32
// 描述  : 对记录prec中的编号为fidx的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
// 返回  : bool 赋值成功与否
// 参数  : void *prec (OUT): 数据记录
// 参数  : int fidx(IN): 赋值的字段编号
// 参数  : double dvalue(IN): 字段的值
// 参数  : unsigned char *parmbits(OUT): 记录的位图表，
//          如果不为NULL，则对此表的位图作相应的设置
//          否则，仅作赋值处理
bool CPackHandle::AddField(void *prec, int fidx, double dvalue, unsigned char *parmbits)
{
   char sztmp[260];
   sprintf(sztmp,"%lf",dvalue);
   return(AddField(prec,fidx,sztmp,parmbits));
}

// 函数名: AddField
// 编程  : 陈永华 2004-9-30 18:07:30
// 描述  : 对记录prec中的名为fieldname的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
// 返回  : bool 赋值成功与否
// 参数  : void *prec (OUT): 数据记录
// 参数  : char *fieldname(IN): 字段名称
// 参数  : int ivalue(IN): 字段的值
// 参数  : unsigned char *parmbits(OUT): 记录的位图表，
//          如果不为NULL，则对此表的位图作相应的设置
//          否则，仅作赋值处理
bool CPackHandle::AddField(void *prec, const char *fieldname, int ivalue, unsigned char *parmbits)
{
   int fidx;
   fidx = FindFieldIndex(fieldname);
   if (fidx<0)
      return(false);
   return(AddField(prec,fidx,ivalue,parmbits));
}

// 函数名: AddField
// 编程  : 陈永华 2004-9-30 18:03:15
// 描述  : 对记录prec中的名为fieldname的字段赋值，如果位图表parmbits!=NULL，则同时设置相应的位图
// 返回  : bool 赋值成功与否
// 参数  : void *prec (OUT): 数据记录
// 参数  : char *fieldname(IN): 字段名称
// 参数  : double dvalue(IN): 字段的值
// 参数  : unsigned char *parmbits(OUT): 记录的位图表，
//          如果不为NULL，则对此表的位图作相应的设置
//          否则，仅作赋值处理
bool CPackHandle::AddField(void *prec, const char *fieldname, double dvalue, unsigned char *parmbits)
{
   int fidx;
   fidx = FindFieldIndex(fieldname);
   if (fidx<0)
      return(false);
   return(AddField(prec,fidx,dvalue,parmbits));
}

// 函数名: GetFieldValue
// 编程  : 陈永华 2004-9-30 19:45:03
// 描述  : 从数据记录中，读取字段编号为fidx的值（用字符串方式返回）
// 2006-6-1 9:47:08 为了提高处理效率，能够同时返回该字段的类型给上层
// 返回 : int 字段类型：
//          PDL_CHAR=1,          普通字符串模式，约定长度，最长不超过255
//          PDL_VCHAR=2,         变长字符，最长不超过255
//          PDL_UCHAR=3,         用于存放二进制数据的字段，比如权限等
//          PDL_INT=4,           整数字段，（由于在64位机中，long属于64位，而在32位机中则为32位，对于int则是固定的，因此本协议中不再采用long）
//          PDL_DOUBLE=5         double类型字段
////         // 返回  : char * 返回字段的值，==NULL:表示无效的字段名
// 参数  : void *prec（IN）：数据记录
// 参数  : int fidx（IN）：字段编号
// 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据
//             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
int CPackHandle::GetFieldValue(const void *prec, int fidx, char *value)
{
/* ****** Updated by CHENYH at 2004-10-20 17:28:33 ****** 
   if (fidx<0 || fidx>iLastPField || pdlist[fidx].wType==0)
*/
   ST_PDATALIST *pfd=pdlist+fidx;
   if (fidx<0 || fidx>iLastPField || pfd->wType==0)
      return(-1);
   return(GetFieldValue(prec,pdlist+fidx,value));      
}

/* ****** Updated by CHENYH at 2006-6-1 9:51:10 ****** 
将原来返回为字符串，改为返回字段类型信息
*******************************************************/
int CPackHandle::GetFieldValue(const void *prec, const ST_PDATALIST *pfd, char *value)
{
   unsigned char *pdata;
   int l;
   pdata = ((unsigned char *)prec)+pfd->dwOffset;
   switch (pfd->wType)
   {
   case PDL_CHAR:
   case PDL_VCHAR:
      l = strlen((char *)pdata);
      if (l>pfd->nLength)
         l = pfd->nLength;
      memcpy(value,pdata,l);
      value[l]='\0';
      return(pfd->wType);
   case PDL_UCHAR:
      memcpy(value,pdata,pfd->nLength);
      return(pfd->wType);
#ifdef NOBUSERROR
   case PDL_INT:
      sprintf(value,"%d",*(int*)pdata);
      return(pfd->wType);
   case PDL_DOUBLE:
      sprintf(value,"%lf",*(double *)pdata);
      return(pfd->wType);
#else
   case PDL_INT:
      {
         int iv;
         memcpy(&iv,pdata,sizeof(iv));
         sprintf(value,"%d",iv);
      }
      return(pfd->wType);
   case PDL_DOUBLE:
      {
         double dv;
         memcpy(&dv,pdata,sizeof(dv));
         sprintf(value,"%lf",dv);
      }
      return(pfd->wType);
#endif
   default:
      value[0]='\0';
      return(pfd->wType);
   }
}



// 函数名: GetFieldValueI
// 编程  : 陈永华 2004-9-30 19:59:19
// 描述  : 从数据记录中，读取字段编号为fidx的值（用int方式返回）
// 返回  : int 返回字段的整数值
// 参数  : void *prec（IN）：数据记录
// 参数  : int fidx（IN）：字段编号
int CPackHandle::GetFieldValueI(const void *prec, int fidx)
{
   char sztmp[260];
   if (GetFieldValue(prec,fidx,sztmp)>0)
      return(atoi(sztmp));
   else
      return(0);
}

// 函数名: GetFieldValueD
// 编程  : 陈永华 2004-9-30 20:00:26
// 描述  : 从数据记录中，读取字段编号为fidx的值（用double方式返回）
// 返回  : double 返回字段的double值
// 参数  : void *prec（IN）：数据记录
// 参数  : int fidx（IN）：字段编号
double CPackHandle::GetFieldValueD(const void *prec, int fidx)
{
   char sztmp[260];
   if (GetFieldValue(prec,fidx,sztmp)>0)
      return(atof(sztmp));
   else
      return(0);
}

// 函数名: GetFieldValue
// 编程  : 陈永华 2004-9-30 20:01:12
// 描述  : 从数据记录中，读取字段名为fieldname的值（用字符串方式返回）
// 2006-6-1 9:47:08 为了提高处理效率，能够同时返回该字段的类型给上层
// 返回 : int 字段类型：
//          PDL_CHAR=1,          普通字符串模式，约定长度，最长不超过255
//          PDL_VCHAR=2,         变长字符，最长不超过255
//          PDL_UCHAR=3,         用于存放二进制数据的字段，比如权限等
//          PDL_INT=4,           整数字段，（由于在64位机中，long属于64位，而在32位机中则为32位，对于int则是固定的，因此本协议中不再采用long）
//          PDL_DOUBLE=5         double类型字段
////         // 返回  : char * 返回字段的值，==NULL:表示无效的字段名
// 参数  : void *prec（IN）：数据记录
// 参数  : char *fieldname（IN）：字段名称
// 参数  : char *value（OUT）：返回的字段值（用字符串方式表示）如果为PDL_UCHAR，则为该BIN字段的整个值，应该以BIN分解数据
//             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
int CPackHandle::GetFieldValue(const void *prec, const char *fieldname, char *value)
{
   int fidx = FindFieldIndex(fieldname);
   return(GetFieldValue(prec,fidx,value));
}

// 函数名: GetFieldValueI
// 编程  : 陈永华 2004-9-30 20:02:56
// 描述  : 从数据记录中，读取字段名为fieldname的值（用int方式返回）
// 返回  : int 返回字段的整数值
// 参数  : void *prec（IN）：数据记录
// 参数  : char *fieldname（IN）：字段名称
int CPackHandle::GetFieldValueI(const void *prec, const char *fieldname)
{
   int fidx = FindFieldIndex(fieldname);
   return(GetFieldValueI(prec,fidx));
}

// 函数名: GetFieldValueD
// 编程  : 陈永华 2004-9-30 20:03:49
// 描述  : 从数据记录中，读取字段名为fieldname的值（用double方式返回）
// 返回  : double 返回字段的double值
// 参数  : void *prec（IN）：数据记录
// 参数  : char *fieldname（IN）：字段名称
double CPackHandle::GetFieldValueD(const void *prec, const char *fieldname)
{
   int fidx = FindFieldIndex(fieldname);
   return(GetFieldValueD(prec,fidx));
}

// 函数名: GetPrintFieldValue
// 编程  : 陈永华 2004-9-30 20:20:58
// 描述  : 从数据记录prec中，输出指定字段pfd的值，以显示跟踪格式返回
// 返回  : char * 返回格式化的字段值，==NULL:非法字段
// 参数  : void *prec（IN）：数据记录
// 参数  : int fidx（IN）：字段编号
// 参数  : char *pfv（OUT）：输出缓冲区
//             由于字段定义长度不超过256，因此注意为了安全，本参数的长度应该大于等于256字节
char * CPackHandle::GetPrintFieldValue(const void *prec, int fidx, char *pfv, int precision)
{

/* ****** Updated by CHENYH at 2004-10-20 17:28:53 ****** 
   if (fidx<0 || fidx>iLastPField || pdlist[fidx].wType==0)
*/
   ST_PDATALIST *pfd=pdlist+fidx;
   if (fidx<0 || fidx>iLastPField || pfd->wType==0)
   {
      strcpy(pfv,"<NULL>");
      return(NULL); // 字段编号超出结构定义范围, 或该字段没有定义
   }
   return(GetPrintFieldValue(prec,pdlist+fidx,pfv,precision));
}

char * CPackHandle::GetPrintFieldValue(const void *prec, const ST_PDATALIST *pfd, char *pfv, int precision)
{
   unsigned char *pdata;
   int l;
   pdata = ((unsigned char *)prec)+pfd->dwOffset;
   switch (pfd->wType)
   {
   case PDL_CHAR:
   case PDL_VCHAR:
      l = strlen((char *)pdata);
      if (l>pfd->nLength)
         l = pfd->nLength;
      memcpy(pfv,pdata,l);
      pfv[l]='\0';
      return(pfv);
   case PDL_UCHAR:
      memcpy(pfv,"0x",2);
      for (l=0;l<pfd->nLength;l++)
      {
         sprintf(pfv+2+l+l,"%02X",pdata[l]);
      }
      return(pfv);
#ifdef NOBUSERROR
   case PDL_INT:
      sprintf(pfv,"%d",*(int *)pdata);
      return(pfv);
   case PDL_DOUBLE:
      if (precision<0)
      {
         sprintf(pfv,"%lf",*(double *)pdata);
      }
      else
      {
         char fmt[12];
         sprintf(fmt,"%%.%dlf",precision);
         sprintf(pfv,fmt,*(double *)pdata);
      }
      return(pfv);
#else
   case PDL_INT:
/* ****** Updated by CHENYH at 2004-10-21 10:36:37 ****** 
      sprintf(pfv,"%d",*(int *)pdata);
*/
      {
         int iv;
         memcpy(&iv,pdata,sizeof(iv));
         sprintf(pfv,"%d",iv);
      }
      return(pfv);
   case PDL_DOUBLE:
/* ****** Updated by CHENYH at 2004-10-21 10:36:45 ****** 
      if (precision<0)
      {
         sprintf(pfv,"%lf",*(double *)pdata);
      }
      else
      {
         char fmt[12];
         sprintf(fmt,"%%.%dlf",precision);
         sprintf(pfv,fmt,*(double *)pdata);
      }
*/
      {
         double dv;
         memcpy(&dv,pdata,sizeof(dv));
         if (precision<0)
         {
            sprintf(pfv,"%lf",dv);
         }
         else
         {
            char fmt[12];
            sprintf(fmt,"%%.%dlf",precision);
            sprintf(pfv,fmt,dv);
         }
      }
      return(pfv);
#endif
   default:
      strcpy(pfv,"<NULL>");
      return(NULL);
   }   
}


// 函数名: CPackHandle::SetPBIndex
// 编程  : 陈永华 2004-10-6 23:09:42
// 描述  : 根据字段序号，设置或清除数据报文位图中相应的字段位图
// 返回  : int － 成功，则返回>=0的fidx（字段序号）；失败，则返回<0
// 参数  : unsigned char *parmbits(OUT): 被修改的位图表
// 参数  : int fidx（IN）：设置或清除的字段序号
// 参数  : bool bToSet（IN）：true－设置；false－清除
int CPackHandle::SetPBIndex(unsigned char *parmbits, int fidx, bool bToSet)
{

/* ****** Updated by CHENYH at 2004-10-20 17:29:01 ****** 
   if (fidx<0 || fidx>iLastPField || pdlist[fidx].wType==0)
*/
   ST_PDATALIST *pfd=pdlist+fidx;
   if (fidx<0 || fidx>iLastPField || pfd->wType==0)
      return(-1); // 字段编号超出结构定义范围, 或该字段没有定义
   if (bToSet)
   {
      (*(parmbits+(fidx>>3))) |= 0x01<<(fidx&0x07);      
   }
   else
   {
      (*(parmbits+(fidx>>3))) &= ~(0x01<<(fidx&0x07));
   }
   return(fidx);   
}


// 函数名: CPackHandle::xmk_crc16
// 编程  : 陈永华 2004-10-6 23:46:39
// 描述  : 统计一个内存块的crc16值，专门用于复核数据的完整性
// 返回  : WORD 计算所得的crc16
// 参数  : void *vptr: 一个内存块
// 参数  : int count: 内存块的字节数
unsigned short CPackHandle::xmk_crc16(const void *vptr, int count)
{
   unsigned short crc, i;
   char *ptr = (char *)vptr;
   crc = 0;
   while (--count >= 0) 
   {
      crc = (crc ^ (((unsigned short)*ptr++) << 8));
      for (i = 0; i < 8; ++i)
      {
         if (crc & 0x8000)
            crc = ((crc << 1) ^ 0x1021);
         else
            crc = crc << 1;
      }
   }
   return (crc & 0xFFFF);   
}

void CPackHandle::ResetParmBits(unsigned char *parmbits)
{
   memset(parmbits,0,PARMBYTES);

/* ****** Updated by CHENYH at 2004-10-14 15:18:15 ****** 
   基于上层不同应用都已经遵循了基本位图概念，并且在打包头部分也要遵循，
   因此，简单将位图部分全部留给了作为字段、数据列定义，不另行作模式的控制。
   这样，检查IsRawDataPack，也就简单的检查本位图所有字节都为0即可。
   if (iMode)
   {
      parmbits[PARMBYTES-1]=0x80;
   }
*/
}

const ST_PDATALIST * CPackHandle::GetValidFieldInfo(const unsigned char *parmbits, int vfnumber)
{
   int fidx;
   unsigned char bmask;
   int mbyte;
   ST_PDATALIST *pfd;
   
   fidx = 0;
   pfd=pdlist;
   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0x00;bmask<<=1,fidx++,pfd++)
      {
         if (fidx>iLastPField)
            return(NULL);
         if ((parmbits[mbyte]&bmask)!=0 && pfd->wType!=0)
         {
            if (vfnumber>0)
               vfnumber--;
            else 
               return(pfd);
         }
      }
   }
   return(NULL);   
}

int CPackHandle::GetValidFieldCount(const unsigned char *parmbits)
{
   int fidx,nvfs;
   unsigned char bmask;
   int mbyte;
   ST_PDATALIST *pfd;

   fidx = nvfs = 0;
   pfd = pdlist;
   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0x00;bmask<<=1,fidx++,pfd++)
      {
         if (fidx>iLastPField)
            return(nvfs);
         if ((parmbits[mbyte]&bmask)!=0 && pfd->wType!=0)
         {
            nvfs++;
         }
      }
   }
   return(nvfs);
}


// 函数名: CPackHandle::OverwritePack
// 编程  : 陈永华 2004-10-10 19:12:22
// 描述  : 将目标报文数据记录中空的数据，用源报文中的有效数据填写（本操作只对单记录有效）
//          如果目标报文中含有有效的数据，则不用源报文覆盖
// 返回  : void 
// 参数  : unsigned char *dparmbits（OUT）：目标报文的位图表
// 参数  : void *dpack（OUT）：目标报文记录
// 参数  : const unsigned char *sparmbits（IN）：源报文的位图表
// 参数  : const void *spack（IN）：源报文记录
void CPackHandle::OverwritePack(unsigned char *dparmbits, void *dpack, const unsigned char *sparmbits, const void *spack)
{
   ST_PDATALIST *pfd = pdlist;
   unsigned char bmask;
   int mbyte;
   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0;bmask<<=1,pfd++)
      {
         if (pfd>pdlist+iLastPField)
            break;
         if ((dparmbits[mbyte]&bmask)==0 && (sparmbits[mbyte]&bmask)!=0)
         {
            switch(pfd->wType) {
            case PDL_CHAR:
            case PDL_VCHAR:
            case PDL_UCHAR:
            case PDL_INT:
            case PDL_DOUBLE:
               memcpy(((char *)dpack)+pfd->dwOffset,((char *)spack)+pfd->dwOffset,pfd->nLength);
               dparmbits[mbyte] |= bmask;
            	break;
            default:
               break;
            }
         }
      }
   }
}

const ST_PDATALIST * CPackHandle::GetPackDef(int &ilastvfidx)
{
   ilastvfidx = iLastPField;
   return(pdlist);
}

bool CPackHandle::CheckValidField(const unsigned char *parmbits, int fidx)
{
   if (fidx<0||fidx>iLastPField)
      return(false);
   return ((parmbits[(fidx>>3)]&(0x01<<(fidx&0x07)))!=0);
}

int CPackHandle::GetPackLength()
{
   return(nPackLength);
}

void CPackHandle::HostByteOrder(void *data, unsigned int datalength)
{
   if (bReverse)
   {
      rev_data(data,datalength);
   }
}
