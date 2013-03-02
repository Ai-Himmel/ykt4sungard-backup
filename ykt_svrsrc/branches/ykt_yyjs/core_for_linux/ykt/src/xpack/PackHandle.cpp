/********************************************************************
	created:	2004/09/23
	created:	23:9:2004   23:26
	filename: 	e:\proj\goldmem\ksbcc\packbase\packhandle.cpp
	file path:	e:\proj\goldmem\ksbcc\packbase
	file base:	packhandle
	file ext:	cpp
	author:		������
	
	purpose:	���ñ��Ľṹ�����ļ���ʵ�ֱ��ı��롢���룬�ֶθ�ֵ������
            Ϊ�˼��緢���ϲ����Ĵ��󣨰��������ģ��������ϸ�ļ�飻

  2004/10/21: CYH 
            ��HPС�ͻ����У�������BUS-Error��ֻ���޸Ķ�pdlist[i]�����ݵĴ�ȡ
            Ϊ�˼�����ͨ�����ϵı��룬����Ҳ�����Ż�һЩ���ܣ�
            ���ú궨��NOBUSERROR����ԭ���Ĳ���
            NOBUSERROR

  2006-12-23 0:44:39 
            DecodeHead: Ϊ�˷�ֹ�����ݰ����ܽ��뵼�����ñ�����ĳ��ֹ���
            ����ph->recCount��ֵ����MAXPACKROWS, ����ֱ��Ӱ��BCC��BU����
            ʹ��PackC���ֵĴ�������Ĳ��ȶ���
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
   // ������ws2_32.lib��
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


// ������: CPackHandle::Initialize
// ���  : ������ 2004-9-23 23:46:48
// ����  : ��ʼ��������������װ��ָ���İ���ʽ�ļ�
// ����  : int 
//           >=0  - �ɹ� �������һ����Ч�ֶκţ�
//            -1  - ����ʽ�ļ����ܴ򿪣�
//            -2  - ָ���ļ���ʽ���󣻲��ܱ����汾����� 
// ����  : char *szPackDefFile������ʽ�ļ�����
/* ****** designed by CHENYH at 2004-9-23 23:48:16 ****** 
����ʽ�ļ��ĸ�ʽ���壺
   int i1;  ���ļ����ɵĻ���������1�ı�ʾֵ�����Ȿ�ļ�����ʹ�õĻ��������ɵĻ��������ʽ�Ĳ�ͬ���½ṹ����
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
   // ����ʽ�ļ��������ԣ�
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

// ������: CPackHandle::rev_data
// ���  : ������ 2004-9-24 0:07:10
// ����  : ��data������ת
// ����  : void 
// ����  : void *data
// ����  : unsigned int datalen
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


// ������: CPackHandle::P_Index
// ���  : ������ 2004-9-24 15:42:40
// ����  : λͼ�����ֶ���ŵ�ת��
// ����  : int �����ֶ����ֵ�� <0: �Ƿ�λͼ��
// ����  : int parmbit ��IN�� λͼ
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


// ������: CPackHandle::EncodeHead
// ���  : ������ 2004-9-24 16:30:57
// ����  : ����ͷ���ݱ��뵽ָ���Ļ�����
// ����  : int �� sizeof(ST_PACKHEAD)
// ����  : ST_PACKHEAD *pHead ��IN�� ��ͷ����
// ����  : void *buf ��OUT����ű���Ļ�����
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




// ������: CPackHandle::DecodeHead
// ���  : ������ 2004-9-24 16:32:51
// ����  : �����뻺�����н��뵽��ͷ��
// ����  : int ��sizeof(ST_PACKHEAD) ��<0 - ����������̫С
// ����  : void *buf [IN] : ���뻺���� 
// ����  : int blen [IN] : ���뻺��������
// ����  : ST_PACKHEAD *ph [OUT]: ��ͷָ��
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
   // 2006-12-23 0:44:39 Ϊ�˷�ֹ�����ݰ����ܽ��뵼�����ñ�����ĳ��ֹ���
   if (ph->recCount>MAXPACKROWS)
   {
      ph->recCount = MAXPACKROWS;
   }
   return(sizeof(ST_PACKHEAD));
}


// ������: CPackHandle::EncodeRow
// ���  : ������ 2004-9-26 14:53:27
// ����  : ����λͼ����һ����¼����pdata���뵽���뻺������
// ����  : int 
/* 
      >=0:�ɹ������ر���ռ�õĳ��ȣ�
      <0:����ʧ�� 
         -1: ����λͼ����(��δ�����λͼ����); 
         -10: ���������Ȳ���
*/
// ����  : unsigned char *parmbits ��IN����32�ֽڵı���λͼ��
// ����  : void *pdata ��IN������¼���ݣ���¼���ݽṹ�μ������ľ����ʼ����װ��
// ����  : void *ebuf ��OUT�������ڱ����ŵĻ�����
// ����  : int ebsize ��IN�������뻺��������󳤶�
int CPackHandle::EncodeRow(const unsigned char *parmbits, const void *pdata, void *ebuf, int ebsize)
{
   int mbyte;
   unsigned char bmask;
   int eblen=0;  // ��ʵ�������ݳ���
   unsigned char *pc=(unsigned char *)ebuf;
   int eflen;    // ��ÿ���ֶεı��볤��
   ST_PDATALIST *pfd=pdlist;
      
   for (mbyte=0;mbyte<PARMBYTES;mbyte++)
   {
      for (bmask=0x01;bmask!=0x00;bmask<<=1,pfd++)
      {
         if (pfd>pdlist+iLastPField)
            return(eblen);  // �����ټ�������ȥ�ˣ���Ϊ���涼Ϊδ������ֶ�
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


// ������: CPackHandle::EncodeSingleField
// ���  : ������ 2004-9-26 16:02:48
// ����  : �����ֶζ��壬��ָ���ļ�¼pdata�е���Ӧ�ֶν��б��룬�����ŵ�pbuf��
// ����  : int >0:�ɹ����ر��볤�ȣ�-1: ʧ�ܣ����ֶ�û���ڽṹ�����ж���
// ����  : ST_PDATALIST *pfd ��IN�����ṹ�����еı����ֶζ���
// ����  : void *pdata��IN����Ҫ����ļ�¼����
// ����  : void *pbuf ��OUT���������ŵĻ�����
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
            // ����ԭ��CPACK�ı��뷽ʽ:
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
            // �µı��뷽ʽ
            flen = strlen(pf);
            if (flen>pfd->nLength)
               flen=pfd->nLength;
            if (flen>255)
               flen = 255;
            pb[0]=(unsigned char)flen;
            memcpy(pb+1,pf,flen); 
            flen++; // ����һ�������ֶ�
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


// ������: CPackHandle::DecodeSingleField
// ���  : ������ 2004-9-26 16:25:55
// ����  : �����ֶζ��壬�ӱ���λ��pbuf�е���Ӧ�ֶν��뵽��¼pdata���ֶ���
// ����  : int >0:�ɹ����ر��볤�ȣ����ں����ı���λ�õ�����<0: ʧ�ܣ�-1 �޸��ֶζ���, -2 ������󣬱��볤�ȣ������ֶζ��峤��
// ����  : ST_PDATALIST *pfd ��IN�����ṹ�����еı����ֶζ���
// ����  : void *pbuf ��IN��������λ��
// ����  : void *pdata ��OUT���������ֶδ�ŵļ�¼
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
            // ����ԭ��CPACK�ı��뷽ʽ:
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
            // �µı��뷽ʽ
            flen = pb[0];
            if (flen>pfd->nLength)
               return(-2);
            memcpy(pf,pb+1,flen);
            if (flen<pfd->nLength)
               pf[flen]='\0';
            flen++; // ����һ�������ֶ�
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



// ������: CPackHandle::DecodeRow
// ���  : ������ 2004-9-26 17:09:58
// ����  : ����λͼ��parmbits�������뻺����ebuf�е����ݣ����뵽���ݼ�¼pdata��
// ����  : int 
/* 
      >=0:�ɹ������ر���ռ�õĳ��ȣ�
      <0:����ʧ�� 
         -1: ����λͼ����(��δ�����λͼ����); 
         -2: �������ֶ����ݳ�������;
         -10: ���������Ȳ���
*/
// ����  : unsigned char *parmbits ��IN��:λͼ��
// ����  : void *ebuf ��IN��:
// ����  : int ebtlen ��IN��:
// ����  : void *pdata ��OUT��:
int CPackHandle::DecodeRow(const unsigned char *parmbits, const void *ebuf, int ebtlen, void *pdata)
{
   int mbyte;
   unsigned char bmask;
   int eblen=0;  // ��ʵ�������ݳ���
   unsigned char *pc=(unsigned char *)ebuf;
   int eflen;    // ��ÿ���ֶεı��볤��
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
                  return(-3);  // ������Ҫ�ĳ��ȳ��������ʵ�ʳ���
            }
         }
      }
   }
   return(eblen);
}


// ������: CPackHandle::FindFieldIndex
// ���  : ������ 2004-9-27 12:19:30
// ����  : �ӱ��Ľṹ�����У������ֶ����ַ��������ֶα��
// ����  : int >=0: �ɹ��ҵ������ض�Ӧ�ֶα�ţ�<0:ʧ�ܣ����ṹ�����У�û��ָ�����Ƶ��ֶ�
// ����  : char *fieldname��IN��: �ֶ�����
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




// ������: CPackHandle::SetParmBit
// ���  : ������ 2004-9-29 18:37:24
// ����  : ���ֶε�λͼ��ʽ���������ݱ��ĵ�λͼ
// ����  : int �����ֶε���ţ�<0:����ȷ��λͼ�����ʼ���ı��ĸ�ʽ������
// ����  : unsigned char *parmbits ��OUT���� ���ĵ�λͼ��
// ����  : int fpb (IN): ָ���ֶε�λͼֵ
int CPackHandle::SetParmBit(unsigned char *parmbits, int fpb)
{
   int fidx = P_Index(fpb);
   return(SetParmBitByFIndex(parmbits,fidx));
}


// ������: CPackHandle::SetParmBitByFIndex
// ���  : ������ 2004-9-29 18:40:39
// ����  : ���ֶε�˳���������ݱ��ĵ�λͼ
// ����  : int �����ֶε���ţ�<0: ����ȷ��λͼ�����ʼ���ı��ĸ�ʽ������
// ����  : unsigned char *parmbits ��OUT���� ���ĵ�λͼ��
// ����  : int fidx ��IN����ָ���ֶ����
int CPackHandle::SetParmBitByFIndex(unsigned char *parmbits, int fidx)
{
   return(SetPBIndex(parmbits,fidx,true));
}


// ������: CPackHandle::ClearParmBit
// ���  : ������ 2004-9-29 19:00:46
// ����  : ���ֶε�λͼ��ʽ��������ݱ��ĵ�λͼ
// ����  : int �����ֶε���ţ�<0:����ȷ��λͼ�����ʼ���ı��ĸ�ʽ������
// ����  : unsigned char *parmbits ��OUT���� ���ĵ�λͼ��
// ����  : int fpb (IN): ָ���ֶε�λͼֵ
int CPackHandle::ClearParmBit(unsigned char *parmbits, int fpb)
{
   int fidx = P_Index(fpb);
   return(ClearParmBitByFIndex(parmbits,fidx));   
}


// ������: CPackHandle::ClearParmBitByFIndex
// ���  : ������ 2004-9-29 18:52:28
// ����  : ���ֶε�˳��������ݱ��ĵ�λͼ
// ����  : int �����ֶε���ţ�<0: ����ȷ��λͼ�����ʼ���ı��ĸ�ʽ������
// ����  : unsigned char *parmbits ��OUT���� ���ĵ�λͼ��
// ����  : int fidx ��IN����ָ���ֶ����
int CPackHandle::ClearParmBitByFIndex(unsigned char *parmbits, int fidx)
{
   return(SetPBIndex(parmbits,fidx,false));
}




// ������: CPackHandle::GetEncodeFieldLength
// ���  : ������ 2004-9-29 19:17:21
// ����  : �������볤�ȹ���һ���ֶεı��볤��
// ����  : int �������볤��
// ����  : ST_PDATALIST *pfd��IN������������ֶζ���
int CPackHandle::GetEncodeFieldLength(const ST_PDATALIST *pfd)
{
   switch(pfd->wType) {
   case PDL_CHAR:
   case PDL_VCHAR:
      if (iMode==0)
      {
         // ����ԭ��CPACK�ı��뷽ʽ:
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



// ������: CPackHandle::EmulateEncodeLength
// ���  : ������ 2004-9-29 19:24:04
// ����  : ���ݵ�ǰָ����λͼ������һ�����ݼ�¼������Ҫ��Ļ�����
// ����  : int ��������Ҫ���뻺�������ȣ��ֽڣ�
// ����  : unsigned char *parmbits��IN����ָ����λͼ��
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
      Ҳ������ֶε�ǰ���ַ����о���whitespace�ַ��أ�
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
         // ��Ϊ��HP-UX�£����ֱ������ʹ�ã������Bus error:
         //*(int *)pdata = atoi(data);
         // ���²Ų�����ִ���
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


// ������: CPackHandle::SetFieldValue
// ���  : ������ 2004-9-30 21:52:27
// ����  : �����ݼ�¼prec�е�ָ���ֶ�pfd����ֵ�����ڸ������ͣ�
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec(OUT): ���ݼ�¼
// ����  : ST_PDATALIST *pfd��IN����ָ�����ֶζ���
// ����  : char *data
bool CPackHandle::SetFieldValue(void *prec, int fidx, char *data)
{
   ST_PDATALIST *pfd=pdlist+fidx;
   if (fidx<0 || fidx>iLastPField || pfd->wType==0)
      return(false); // �ֶα�ų����ṹ���巶Χ, ����ֶ�û�ж���
   return(SetFieldValue(prec,pdlist+fidx,data));
}


// ������: CPackHandle::SetFieldValue
// ���  : ������ 2004-9-30 21:51:23
// ����  : �����ݼ�¼prec�е�ָ���ֶ�pfd����ֵ������int��char *���ͣ�
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec(OUT): ���ݼ�¼
// ����  : ST_PDATALIST *pfd��IN����ָ�����ֶζ���
// ����  : int ivalue��IN�����ֶε�intֵ
bool CPackHandle::SetFieldValue(void *prec, const ST_PDATALIST *pfd, int ivalue)
{
   char sztmp[40];
   sprintf(sztmp,"%d",ivalue);
   return(SetFieldValue(prec,pfd,sztmp));
}


// ������: CPackHandle::SetFieldValue
// ���  : ������ 2004-9-30 21:48:37
// ����  : �����ݼ�¼prec�е�ָ���ֶ�pfd����ֵ������double��char *���ͣ�
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec(OUT): ���ݼ�¼
// ����  : ST_PDATALIST *pfd��IN����ָ�����ֶζ���
// ����  : double dvalue��IN�����ֶε�doubleֵ
bool CPackHandle::SetFieldValue(void *prec, const ST_PDATALIST *pfd, double dvalue)
{
   char sztmp[260];
   sprintf(sztmp,"%lf",dvalue);
   return(SetFieldValue(prec,pfd,sztmp));
}

// ������: AddField
// ���  : ������ 2004-9-30 18:12:29
// ����  : �Լ�¼prec�еı��Ϊfidx���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec (OUT): ���ݼ�¼
// ����  : int fidx(IN): ��ֵ���ֶα��
// ����  : char *data(IN): �ֶε�ֵ
// ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
//          �����ΪNULL����Դ˱��λͼ����Ӧ������
//          ���򣬽�����ֵ����
bool CPackHandle::AddField(void *prec, int fidx, const char *data, unsigned char *parmbits)
{
   // char buf[260]={0}; 2006-2-27 0:06:44
   // int i;
   if (fidx<0||fidx>iLastPField)
      return(false);
   /* ****** Updated by CHENYH at 2006-2-27 0:07:30 ****** 
   // ��SetFieldValue����Ҳ����������PDL_UCHAR, ����Ҳ�������data�е�ֵ
   // ����ֱ��ʹ��data��������Ϊ�˵��ù�ϵdata����ǿ��Ϊchar *
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

// ������: AddField
// ���  : ������ 2004-9-30 18:08:26
// ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec (OUT): ���ݼ�¼
// ����  : char *fieldname(IN): �ֶ�����
// ����  : char *data(IN): �ֶε�ֵ
// ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
//          �����ΪNULL����Դ˱��λͼ����Ӧ������
//          ���򣬽�����ֵ����
bool CPackHandle::AddField(void *prec, const char *fieldname, const char *data, unsigned char *parmbits)
{
   int fidx = FindFieldIndex(fieldname);
   if (fidx<0)
      return(false);
   return(AddField(prec,fidx,data,parmbits));
}

// ������: AddField
// ���  : ������ 2004-9-30 18:11:45
// ����  : �Լ�¼prec�еı��Ϊfidx���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec (OUT): ���ݼ�¼
// ����  : int fidx(IN): ��ֵ���ֶα��
// ����  : int ivalue(IN): �ֶε�ֵ
// ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
//          �����ΪNULL����Դ˱��λͼ����Ӧ������
//          ���򣬽�����ֵ����
bool CPackHandle::AddField(void *prec, int fidx, int ivalue, unsigned char *parmbits)
{
   char sztmp[40];
   sprintf(sztmp,"%d",ivalue);
   return(AddField(prec,fidx,sztmp,parmbits));
}

// ������: AddField
// ���  : ������ 2004-9-30 18:09:32
// ����  : �Լ�¼prec�еı��Ϊfidx���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec (OUT): ���ݼ�¼
// ����  : int fidx(IN): ��ֵ���ֶα��
// ����  : double dvalue(IN): �ֶε�ֵ
// ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
//          �����ΪNULL����Դ˱��λͼ����Ӧ������
//          ���򣬽�����ֵ����
bool CPackHandle::AddField(void *prec, int fidx, double dvalue, unsigned char *parmbits)
{
   char sztmp[260];
   sprintf(sztmp,"%lf",dvalue);
   return(AddField(prec,fidx,sztmp,parmbits));
}

// ������: AddField
// ���  : ������ 2004-9-30 18:07:30
// ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec (OUT): ���ݼ�¼
// ����  : char *fieldname(IN): �ֶ�����
// ����  : int ivalue(IN): �ֶε�ֵ
// ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
//          �����ΪNULL����Դ˱��λͼ����Ӧ������
//          ���򣬽�����ֵ����
bool CPackHandle::AddField(void *prec, const char *fieldname, int ivalue, unsigned char *parmbits)
{
   int fidx;
   fidx = FindFieldIndex(fieldname);
   if (fidx<0)
      return(false);
   return(AddField(prec,fidx,ivalue,parmbits));
}

// ������: AddField
// ���  : ������ 2004-9-30 18:03:15
// ����  : �Լ�¼prec�е���Ϊfieldname���ֶθ�ֵ�����λͼ��parmbits!=NULL����ͬʱ������Ӧ��λͼ
// ����  : bool ��ֵ�ɹ����
// ����  : void *prec (OUT): ���ݼ�¼
// ����  : char *fieldname(IN): �ֶ�����
// ����  : double dvalue(IN): �ֶε�ֵ
// ����  : unsigned char *parmbits(OUT): ��¼��λͼ��
//          �����ΪNULL����Դ˱��λͼ����Ӧ������
//          ���򣬽�����ֵ����
bool CPackHandle::AddField(void *prec, const char *fieldname, double dvalue, unsigned char *parmbits)
{
   int fidx;
   fidx = FindFieldIndex(fieldname);
   if (fidx<0)
      return(false);
   return(AddField(prec,fidx,dvalue,parmbits));
}

// ������: GetFieldValue
// ���  : ������ 2004-9-30 19:45:03
// ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ�����ַ�����ʽ���أ�
// 2006-6-1 9:47:08 Ϊ����ߴ���Ч�ʣ��ܹ�ͬʱ���ظ��ֶε����͸��ϲ�
// ���� : int �ֶ����ͣ�
//          PDL_CHAR=1,          ��ͨ�ַ���ģʽ��Լ�����ȣ��������255
//          PDL_VCHAR=2,         �䳤�ַ����������255
//          PDL_UCHAR=3,         ���ڴ�Ŷ��������ݵ��ֶΣ�����Ȩ�޵�
//          PDL_INT=4,           �����ֶΣ���������64λ���У�long����64λ������32λ������Ϊ32λ������int���ǹ̶��ģ���˱�Э���в��ٲ���long��
//          PDL_DOUBLE=5         double�����ֶ�
////         // ����  : char * �����ֶε�ֵ��==NULL:��ʾ��Ч���ֶ���
// ����  : void *prec��IN�������ݼ�¼
// ����  : int fidx��IN�����ֶα��
// ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ�����ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ�����
//             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
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
��ԭ������Ϊ�ַ�������Ϊ�����ֶ�������Ϣ
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



// ������: GetFieldValueI
// ���  : ������ 2004-9-30 19:59:19
// ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ����int��ʽ���أ�
// ����  : int �����ֶε�����ֵ
// ����  : void *prec��IN�������ݼ�¼
// ����  : int fidx��IN�����ֶα��
int CPackHandle::GetFieldValueI(const void *prec, int fidx)
{
   char sztmp[260];
   if (GetFieldValue(prec,fidx,sztmp)>0)
      return(atoi(sztmp));
   else
      return(0);
}

// ������: GetFieldValueD
// ���  : ������ 2004-9-30 20:00:26
// ����  : �����ݼ�¼�У���ȡ�ֶα��Ϊfidx��ֵ����double��ʽ���أ�
// ����  : double �����ֶε�doubleֵ
// ����  : void *prec��IN�������ݼ�¼
// ����  : int fidx��IN�����ֶα��
double CPackHandle::GetFieldValueD(const void *prec, int fidx)
{
   char sztmp[260];
   if (GetFieldValue(prec,fidx,sztmp)>0)
      return(atof(sztmp));
   else
      return(0);
}

// ������: GetFieldValue
// ���  : ������ 2004-9-30 20:01:12
// ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ�����ַ�����ʽ���أ�
// 2006-6-1 9:47:08 Ϊ����ߴ���Ч�ʣ��ܹ�ͬʱ���ظ��ֶε����͸��ϲ�
// ���� : int �ֶ����ͣ�
//          PDL_CHAR=1,          ��ͨ�ַ���ģʽ��Լ�����ȣ��������255
//          PDL_VCHAR=2,         �䳤�ַ����������255
//          PDL_UCHAR=3,         ���ڴ�Ŷ��������ݵ��ֶΣ�����Ȩ�޵�
//          PDL_INT=4,           �����ֶΣ���������64λ���У�long����64λ������32λ������Ϊ32λ������int���ǹ̶��ģ���˱�Э���в��ٲ���long��
//          PDL_DOUBLE=5         double�����ֶ�
////         // ����  : char * �����ֶε�ֵ��==NULL:��ʾ��Ч���ֶ���
// ����  : void *prec��IN�������ݼ�¼
// ����  : char *fieldname��IN�����ֶ�����
// ����  : char *value��OUT�������ص��ֶ�ֵ�����ַ�����ʽ��ʾ�����ΪPDL_UCHAR����Ϊ��BIN�ֶε�����ֵ��Ӧ����BIN�ֽ�����
//             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
int CPackHandle::GetFieldValue(const void *prec, const char *fieldname, char *value)
{
   int fidx = FindFieldIndex(fieldname);
   return(GetFieldValue(prec,fidx,value));
}

// ������: GetFieldValueI
// ���  : ������ 2004-9-30 20:02:56
// ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ����int��ʽ���أ�
// ����  : int �����ֶε�����ֵ
// ����  : void *prec��IN�������ݼ�¼
// ����  : char *fieldname��IN�����ֶ�����
int CPackHandle::GetFieldValueI(const void *prec, const char *fieldname)
{
   int fidx = FindFieldIndex(fieldname);
   return(GetFieldValueI(prec,fidx));
}

// ������: GetFieldValueD
// ���  : ������ 2004-9-30 20:03:49
// ����  : �����ݼ�¼�У���ȡ�ֶ���Ϊfieldname��ֵ����double��ʽ���أ�
// ����  : double �����ֶε�doubleֵ
// ����  : void *prec��IN�������ݼ�¼
// ����  : char *fieldname��IN�����ֶ�����
double CPackHandle::GetFieldValueD(const void *prec, const char *fieldname)
{
   int fidx = FindFieldIndex(fieldname);
   return(GetFieldValueD(prec,fidx));
}

// ������: GetPrintFieldValue
// ���  : ������ 2004-9-30 20:20:58
// ����  : �����ݼ�¼prec�У����ָ���ֶ�pfd��ֵ������ʾ���ٸ�ʽ����
// ����  : char * ���ظ�ʽ�����ֶ�ֵ��==NULL:�Ƿ��ֶ�
// ����  : void *prec��IN�������ݼ�¼
// ����  : int fidx��IN�����ֶα��
// ����  : char *pfv��OUT�������������
//             �����ֶζ��峤�Ȳ�����256�����ע��Ϊ�˰�ȫ���������ĳ���Ӧ�ô��ڵ���256�ֽ�
char * CPackHandle::GetPrintFieldValue(const void *prec, int fidx, char *pfv, int precision)
{

/* ****** Updated by CHENYH at 2004-10-20 17:28:53 ****** 
   if (fidx<0 || fidx>iLastPField || pdlist[fidx].wType==0)
*/
   ST_PDATALIST *pfd=pdlist+fidx;
   if (fidx<0 || fidx>iLastPField || pfd->wType==0)
   {
      strcpy(pfv,"<NULL>");
      return(NULL); // �ֶα�ų����ṹ���巶Χ, ����ֶ�û�ж���
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


// ������: CPackHandle::SetPBIndex
// ���  : ������ 2004-10-6 23:09:42
// ����  : �����ֶ���ţ����û�������ݱ���λͼ����Ӧ���ֶ�λͼ
// ����  : int �� �ɹ����򷵻�>=0��fidx���ֶ���ţ���ʧ�ܣ��򷵻�<0
// ����  : unsigned char *parmbits(OUT): ���޸ĵ�λͼ��
// ����  : int fidx��IN�������û�������ֶ����
// ����  : bool bToSet��IN����true�����ã�false�����
int CPackHandle::SetPBIndex(unsigned char *parmbits, int fidx, bool bToSet)
{

/* ****** Updated by CHENYH at 2004-10-20 17:29:01 ****** 
   if (fidx<0 || fidx>iLastPField || pdlist[fidx].wType==0)
*/
   ST_PDATALIST *pfd=pdlist+fidx;
   if (fidx<0 || fidx>iLastPField || pfd->wType==0)
      return(-1); // �ֶα�ų����ṹ���巶Χ, ����ֶ�û�ж���
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


// ������: CPackHandle::xmk_crc16
// ���  : ������ 2004-10-6 23:46:39
// ����  : ͳ��һ���ڴ���crc16ֵ��ר�����ڸ������ݵ�������
// ����  : WORD �������õ�crc16
// ����  : void *vptr: һ���ڴ��
// ����  : int count: �ڴ����ֽ���
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
   �����ϲ㲻ͬӦ�ö��Ѿ���ѭ�˻���λͼ��������ڴ��ͷ����ҲҪ��ѭ��
   ��ˣ��򵥽�λͼ����ȫ����������Ϊ�ֶΡ������ж��壬��������ģʽ�Ŀ��ơ�
   ���������IsRawDataPack��Ҳ�ͼ򵥵ļ�鱾λͼ�����ֽڶ�Ϊ0���ɡ�
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


// ������: CPackHandle::OverwritePack
// ���  : ������ 2004-10-10 19:12:22
// ����  : ��Ŀ�걨�����ݼ�¼�пյ����ݣ���Դ�����е���Ч������д��������ֻ�Ե���¼��Ч��
//          ���Ŀ�걨���к�����Ч�����ݣ�����Դ���ĸ���
// ����  : void 
// ����  : unsigned char *dparmbits��OUT����Ŀ�걨�ĵ�λͼ��
// ����  : void *dpack��OUT����Ŀ�걨�ļ�¼
// ����  : const unsigned char *sparmbits��IN����Դ���ĵ�λͼ��
// ����  : const void *spack��IN����Դ���ļ�¼
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
