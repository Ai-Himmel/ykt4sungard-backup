#include <stdio.h>
//#include <unistd.h>
#include <string.h>
#ifdef WIN32
#include <Winsock2.h>
#else
#include <unistd.h>
#include <memory.h>
#include <netinet/in.h> /* sockaddr_in */
#endif

//#include <netinet/in.h> 
//#include "mytypes.h"
#include "cpack.h"

static unsigned char _bits[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void Reverse(void *buf,int len)
{
/*
	功能:RS6000上转换字节序

*/
	int i,l;
   unsigned char *pb;
   unsigned char b;
   if (len<2) 
      return;
   if (htons(1)==1)
   {
      pb = (unsigned char *)buf;
      l = len>>1;
	   for(i=0;i<l;i++)
	   {
         b = pb[i];
         pb[i]=pb[len-i-1];
         pb[len-i-1]=b;
	   }
   }
}

void Reserve(void *buf,int len)
{
	Reverse(buf,len);
}


int _DecodeSingleItem(int idx,ST_PACK *pPack,char *pSrc)
{
/*

*/
	short vsl;
   int l;

#define CP(a)	memcpy(pPack->a,pSrc,sizeof(pPack->a)); \
				l=sizeof(pPack->a);
#define DP(a)	memcpy(&pPack->a,pSrc,sizeof(pPack->a));\
				Reverse((unsigned char *)&pPack->a,sizeof(pPack->a));\
				l=sizeof(pPack->a);
#define VP(a)	memcpy(&vsl,pSrc,2);\
				Reverse((unsigned char *)&vsl,sizeof(short));\
				memcpy(pPack->a,pSrc+2,vsl);\
				l=2+vsl;
	switch(idx)
	{
	case F_SCUST_NO:
		CP(scust_no);
		break;
	case F_SCUST_NO2:
		CP(scust_no2);
		break;
	case F_SHOLDER_AC_NO:
		CP(sholder_ac_no);
		break;
	case F_SHOLDER_AC_NO2:
		CP(sholder_ac_no2);
		break;
	case F_SHOLDER_TYPE:
		CP(sholder_type);
		break;
	case F_SHOLDER_TYPE2:
		CP(sholder_type2);
		break;
	case F_SNAME:
		CP(sname);
		break;
	case F_SNAME2:
		CP(sname2);
		break;

	case F_SALL_NAME:
		CP(sall_name);
		break;
	case F_SMARKET_CODE:
		CP(smarket_code);
		break;
	case F_SMARKET_CODE2:
		CP(smarket_code2);
		break;
	case F_SDATE0:
		CP(sdate0);
		break;
	case F_SDATE1:
		CP(sdate1);
		break;
	case F_SDATE2:
		CP(sdate2);
		break;
	case F_SDATE3:
		CP(sdate3);
		break;
	case F_STIME0:
		CP(stime0);
		break;

	case F_STIME1:
		CP(stime1);
		break;
	case F_STIME2:
		CP(stime2);
		break;
	case F_STIME3:
		CP(stime3);
		break;
	case F_LVOL0:
		DP(lvol0);
		break;
	case F_LVOL1:
		DP(lvol1);
		break;
	case F_LVOL2:
		DP(lvol2);
		break;
	case F_LVOL3:
		DP(lvol3);
		break;
	case F_LVOL4:
		DP(lvol4);
		break;

	case F_LVOL5:
		DP(lvol5);
		break;
	case F_LVOL6:
		DP(lvol6);
		break;
	case F_LVOL7:
		DP(lvol7);
		break;
	case F_LVOL8:
		DP(lvol8);
		break;
	case F_LVOL9:
		DP(lvol9);
		break;
	case F_LVOL10:
		DP(lvol10);
		break;
	case F_LVOL11:
		DP(lvol11);
		break;
	case F_LVOL12:
		DP(lvol12);
		break;

	case F_DAMT0:
		DP(damt0);
		break;
	case F_DAMT1:
		DP(damt1);
		break;
	case F_DAMT2:
		DP(damt2);
		break;
	case F_DAMT3:
		DP(damt3);
		break;
	case F_DAMT4:
		DP(damt4);
		break;
	case F_DAMT5:
		DP(damt5);
		break;
	case F_DAMT6:
		DP(damt6);
		break;
	case F_DAMT7:
		DP(damt7);
		break;

	case F_DAMT8:
		DP(damt8);
		break;
	case F_DAMT9:
		DP(damt9);
		break;
	case F_DAMT10:
		DP(damt10);
		break;
	case F_DAMT11:
		DP(damt11);
		break;
	case F_DAMT12:
		DP(damt12);
		break;
	case F_DAMT13:
		DP(damt13);
		break;
	case F_DAMT14:
		DP(damt14);
		break;
	case F_DAMT15:
		DP(damt15);
		break;

	case F_DAMT16:
		DP(damt16);
		break;
	case F_DAMT17:
		DP(damt17);
		break;
	case F_DAMT18:
		DP(damt18);
		break;
	case F_DAMT19:
		DP(damt19);
		break;
	case F_DAMT20:
		DP(damt20);
		break;
	case F_DAMT21:
		DP(damt21);
		break;
	case F_DAMT22:
		DP(damt22);
		break;
	case F_DAMT23:
		DP(damt23);
		break;

	case F_DAMT24:
		DP(damt24);
		break;
	case F_DAMT25:
		DP(damt25);
		break;
	case F_DAMT26:
		DP(damt26);
		break;
	case F_DAMT27:
		DP(damt27);
		break;
	case F_DAMT28:
		DP(damt28);
		break;
	case F_DAMT29:
		DP(damt29);
		break;
	case F_DAMT30:
		DP(damt30);
		break;
	case F_DAMT31:
		DP(damt31);
		break;

	case F_DAMT32:
		DP(damt32);
		break;
	case F_DAMT33:
		DP(damt33);
		break;
	case F_SSTOCK_CODE:
		CP(sstock_code);
		break;
	case F_SSTOCK_CODE2:
		CP(sstock_code2);
		break;
	case F_SCUST_TYPE:
		CP(scust_type);
		break;
	case F_SCUST_TYPE2:
		CP(scust_type2);
		break;
	case F_SSTAT_TYPE:
		CP(sstat_type);
		break;
	case F_SSTAT_TYPE2:
		CP(sstat_type2);
		break;

	case F_SROOM_NO:
		CP(sroom_no);
		break;
	case F_SROOM_NO2:
		CP(sroom_no2);
		break;
	case F_SOPEN_EMP:
		CP(sopen_emp);
		break;
	case F_SCLOSE_EMP:
		CP(sclose_emp);
		break;
	case F_SCHANGE_EMP:
		CP(schange_emp);
		break;
	case F_SCHECK_EMP:
		CP(scheck_emp);
		break;
	case F_SEMP:
		CP(semp);
		break;
	case F_SNATION_CODE:
		CP(snation_code);
		break;

	case F_LCERT_CODE:
		DP(lcert_code);
		break;
	case F_STX_PWD:
		CP(stx_pwd);
		break;
	case F_STX_PWD2:
		CP(stx_pwd2);
		break;
	case F_SWITHDRAW_PWD:
		CP(swithdraw_pwd);
		break;
	case F_SWITHDRAW_PWD2:
		CP(swithdraw_pwd2);
		break;
	case F_SEMP_PWD:
		CP(semp_pwd);
		break;
	case F_SEMP_PWD2:
		CP(semp_pwd2);
		break;
	case F_SBANK_PWD:
		CP(sbank_pwd);
		break;

	case F_SBANK_PWD2:
		CP(sbank_pwd2);
		break;
	case F_SCUST_AUTH:
		CP(scust_auth);
		break;
	case F_SCUST_AUTH2:
		CP(scust_auth2);
		break;
	case F_SCUST_LIMIT:
		CP(scust_limit);
		break;
	case F_SCUST_LIMIT2:
		CP(scust_limit2);
		break;
	case F_LSAFE_LEVEL:
		DP(lsafe_level);
		break;
	case F_LSAFE_LEVEL2:
		DP(lsafe_level2);
		break;
	case F_SPOST_CODE:
		CP(spost_code);
		break;

	case F_SPOST_CODE2:
		CP(spost_code2);
		break;
	case F_SPHONE:
		CP(sphone);
		break;
	case F_SPHONE2:
		CP(sphone2);
		break;
	case F_SPHONE3:
		CP(sphone3);
		break;
	case F_SPAGER:
		CP(spager);
		break;
	case F_SEMAIL:
		CP(semail);
		break;
	case F_SEMAIL2:
		CP(semail2);
		break;
	case F_SNOTE:
		CP(snote);
		break;

	case F_SNOTE2:
		CP(snote2);
		break;
	case F_SCERT_NO:
		CP(scert_no);
		break;
	case F_SCERT_NO2:
		CP(scert_no2);
		break;
	case F_SCERT_ADDR:
		CP(scert_addr);
		break;
	case F_SSTATUS0:
		CP(sstatus0);
		break;
	case F_SSTATUS1:
		CP(sstatus1);
		break;
	case F_SSTATUS2:
		CP(sstatus2);
		break;
	case F_SSTATUS3:
		CP(sstatus3);
		break;

	case F_SSTATUS4:
		CP(sstatus4);
		break;
	case F_LWITHDRAW_FLAG:
		DP(lwithdraw_flag);
		break;
	case F_SADDR:
		CP(saddr);
		break;
	case F_SADDR2:
		CP(saddr2);
		break;
	case F_SSERIAL0:
		CP(sserial0);
		break;
	case F_SSERIAL1:
		CP(sserial1);
		break;
	case F_SSERIAL2:
		CP(sserial2);
		break;
	case F_SSERIAL3:
		CP(sserial3);
		break;

	case F_SSERIAL4:
		CP(sserial4);
		break;
	case F_SCURRENCY_TYPE:
		CP(scurrency_type);
		break;
	case F_SCURRENCY_TYPE2:
		CP(scurrency_type2);
		break;
	case F_SBRANCH_CODE0:
		CP(sbranch_code0);
		break;
	case F_SBRANCH_CODE1:
		CP(sbranch_code1);
		break;
	case F_SBRANCH_CODE2:
		CP(sbranch_code2);
		break;
	case F_USSET0:
		CP(usset0);
		break;
	case F_USSET1:
		CP(usset1);
		break;

	case F_USSET2:
		CP(usset2);
		break;
	case F_USSET3:
		CP(usset3);
		break;
	case F_USSET4:
		CP(usset4);
		break;
	case F_USSET5:
		CP(usset5);
		break;
	case F_USSET6:
		CP(usset6);
		break;
	case F_SSTATION0:
		CP(sstation0);
		break;
	case F_SSTATION1:
		CP(sstation1);
		break;
	case F_SBANK_ACC:
		CP(sbank_acc);
		break;

	case F_SBANK_ACC2:
		CP(sbank_acc2);
		break;
	case F_LBANK_ACC_TYPE:
		DP(lbank_acc_type);
		break;
	case F_LBANK_ACC_TYPE2:
		DP(lbank_acc_type2);
		break;
	case F_SMAIN_FLAG:
		CP(smain_flag);
		break;
	case F_SMAIN_FLAG2:
		CP(smain_flag2);
		break;
	case F_SBANK_CODE:
		CP(sbank_code);
		break;
	case F_SBANK_CODE2:
		CP(sbank_code2);
		break;
	case F_SEMP_NO:
		CP(semp_no);
		break;

	case F_SEMP_NO2:
		CP(semp_no2);
		break;
	case F_DRATE0:
		DP(drate0);
		break;
	case F_DRATE1:
		DP(drate1);
		break;
	case F_LSERIAL0:
		DP(lserial0);
		break;
	case F_LSERIAL1:
		DP(lserial1);
		break;
	case F_SBANKNAME:
		CP(sbankname);
		break;
	case F_SBANKNAME2:
		CP(sbankname2);
		break;
	case F_SCARD0:
		CP(scard0);
		break;

	case F_SCARD1:
		CP(scard1);
		break;
	case F_SORDER0:
		CP(sorder0);
		break;
	case F_SORDER1:
		CP(sorder1);
		break;
	case F_SORDER2:
		CP(sorder2);
		break;
	case F_SCUSTTYPES:
		CP(scusttypes);
		break;
	case F_SSECTYPES:
		CP(ssectypes);
		break;
	case F_VSMESS:
		VP(vsmess);
		break;
	case F_VSVARSTR0:
		VP(vsvarstr0);
		break;
	case F_VSVARSTR1:
		VP(vsvarstr1);
		break;
	case F_VSVARSTR2:
		VP(vsvarstr2);
		break;

	case F_VSVARSTR3:
		VP(vsvarstr3);
		break;
	default:
      l = 0;
		printf("decodesingleitem no this param =%d ......\n",idx);
	}
#undef CP
#undef DP
#undef VP
   return(l);
}

BOOL DecodeHead(unsigned char *buf,int len,ST_PACKHEAD *pHead,char *eMsg)
{
	if (len<(int)sizeof(ST_PACKHEAD))
	{
		sprintf(eMsg,"包大小小于包头的大小。[%d][%d]\n",len,sizeof(ST_PACKHEAD));
		return FALSE;
	}
	memcpy(pHead,buf,sizeof(ST_PACKHEAD));
	Reverse((unsigned char *)&pHead->RequestType,sizeof(pHead->RequestType));
	Reverse((unsigned char *)&pHead->firstflag,sizeof(pHead->firstflag));
	Reverse((unsigned char *)&pHead->nextflag,sizeof(pHead->nextflag));
	Reverse((unsigned char *)&pHead->recCount,sizeof(pHead->recCount));
	Reverse((unsigned char *)&pHead->retCode,sizeof(pHead->retCode));
	Reverse((unsigned char *)&pHead->hook.UserID,sizeof(pHead->hook.UserID));
	Reverse((unsigned char *)&pHead->hook.queuetype,sizeof(pHead->hook.queuetype));
	return TRUE;
}

BOOL DecodeBufHead(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg)
{
   return(DecodeHead(buf,len,&(pPack->head),eMsg));
}


// 函数名: DecodeAPack
// 编程  : 陈永华 2004-2-18 22:11:08
// 描述  : 根据ST_PACKHEAD中的位图从缓存中解码出具体的CPACK记录
// 返回  : int 解包实际使用缓存的长度
// 参数  : char *buf 编码的缓存起始指针
// 参数  : int len   编码的长度
// 参数  : ST_PACKHEAD *phead 编码位图存放的CPACK头
// 参数  : ST_PACK *pack 解包存放的CPACK记录
// 参数  : char *eMsg 错误信息
int DecodeAPack(char *buf,int len,ST_PACKHEAD *phead,ST_PACK *pack,char *eMsg)
{
   int i,j;
   int l;
   l = 0;
   memset(pack,0,sizeof(ST_PACK));
   for (i=0;i<PARMBYTES;i++)
   {
      for (j=0;j<8;j++)
      {
         if (phead->ParmBits[i] & _bits[j])
         {
            l+= _DecodeSingleItem((i<<8)+_bits[j],pack,buf+l);
         }
      }
   }
   if (l>len)
   {
      sprintf(eMsg,"包数据长度[%d]<实际解包需要的长度[%d]\n",len,l);
   }
   return(l);
}

BOOL DecodeBuf(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg)
{

/* ****** Updated by CHENYH at 2004-2-18 18:48:59 ****** 
	unsigned char *p;
	int i;
	ST_PACKHEAD *ph;
	unsigned char b0;
	int j;
	int result;
	if (len< sizeof(ST_PACKHEAD))
	{
		sprintf(eMsg,"包大小小于包头的大小。[%d][%d]\n",len,sizeof(ST_PACKHEAD));
		return FALSE;
	}
	p = buf;
	memcpy(&pPack->head,p,sizeof(ST_PACKHEAD));
	Reverse((unsigned char *)&pPack->head.RequestType,sizeof(pPack->head.RequestType));
	Reverse((unsigned char *)&pPack->head.firstflag,sizeof(pPack->head.firstflag));
	Reverse((unsigned char *)&pPack->head.nextflag,sizeof(pPack->head.nextflag));
	Reverse((unsigned char *)&pPack->head.recCount,sizeof(pPack->head.recCount));
	Reverse((unsigned char *)&pPack->head.retCode,sizeof(pPack->head.retCode));
	Reverse((unsigned char *)&pPack->head.hook.UserID,sizeof(pPack->head.hook.UserID));
	Reverse((unsigned char *)&pPack->head.hook.queuetype,sizeof(pPack->head.hook.queuetype));
	p = buf+sizeof(ST_PACKHEAD);
	ph = &pPack->head;
	memset(&pPack->pack,0,sizeof(pPack->pack));
	for(i=0;i<PARMBYTES;i++)
	{
		b0 = ph->ParmBits[i];
		for(j=0;j<8;j++)
		{
			if (b0 & _bits[j])
				result = (i<<8)+_bits[j];
			else
				continue;
			p += _DecodeSingleItem(result,&pPack->pack,(char *)p);
		}
	}
	return TRUE;
*/
   int l,i;
   if (DecodeBufHead(buf,len,pPack,eMsg)==FALSE)
      return(FALSE);
   if (pPack->head.recCount==0)
      return(TRUE);
   l = sizeof(ST_PACKHEAD);
   i = DecodeAPack((char *)(buf+l),len-l,&(pPack->head),&(pPack->pack),eMsg);
   if (i>len-l)
      return(FALSE);
   else
      return(TRUE);
}

BOOL DecodeBufWithArray(unsigned char *buf,int len,ST_CPACK *pPack,ST_PACK *packArray,
						int *recCount,char *eMsg)
{
/* ****** Updated by CHENYH at 2004-2-18 18:51:52 ****** 
	unsigned char *p;
	int i;
	int cnt;
	ST_PACKHEAD *ph;
	unsigned char b0;
	int j;
	int result;
	ST_PACK *pp;


	if (len< sizeof(ST_PACKHEAD))
	{
		sprintf(eMsg,"包大小小于包头的大小。[%d][%d]\n",len,sizeof(ST_PACKHEAD));
		return FALSE;
	}

	p = buf;
	memcpy(&pPack->head,p,sizeof(ST_PACKHEAD));
	Reverse((unsigned char *)&pPack->head.RequestType,sizeof(pPack->head.RequestType));
	Reverse((unsigned char *)&pPack->head.firstflag,sizeof(pPack->head.firstflag));
	Reverse((unsigned char *)&pPack->head.nextflag,sizeof(pPack->head.nextflag));
	Reverse((unsigned char *)&pPack->head.recCount,sizeof(pPack->head.recCount));
	Reverse((unsigned char *)&pPack->head.retCode,sizeof(pPack->head.retCode));
	Reverse((unsigned char *)&pPack->head.hook.UserID,sizeof(pPack->head.hook.UserID));
	Reverse((unsigned char *)&pPack->head.hook.queuetype,sizeof(pPack->head.hook.queuetype));

	if (pPack->head.recCount>1 && packArray == NULL)
	{
		strcpy(eMsg,"多纪录解包要求packArray != NULL");
		return FALSE;
	}

	*recCount = pPack->head.recCount;

	p = buf+sizeof(ST_PACKHEAD);
	ph = &pPack->head;
	pp = &pPack->pack;
	for(cnt = 0; cnt < *recCount ;cnt ++)
	{
	   memset(pp,0,sizeof(ST_PACK));
		for(i=0;i<PARMBYTES;i++)
		{
			b0 = ph->ParmBits[i];
			for(j=0;j<8;j++)
			{
				if (b0 & _bits[j])
					result = (i<<8)+_bits[j];
				else
					continue;
				_DecodeSingleItem(result,pp,(char **)&p);
			}
		}
		if (packArray == NULL)
			break;
		pp = &packArray[cnt];
	}
	return TRUE;
*/
   int l,i;
   int r;
   ST_PACK *pp;
   if (DecodeBufHead(buf,len,pPack,eMsg)==FALSE)
      return(FALSE);
   l = sizeof(ST_PACKHEAD);
   pp = &(pPack->pack);
   for (r=0;r<(int)pPack->head.recCount;r++)
   {
      if (pp==NULL)
         break;
      i = DecodeAPack((char *)buf+l,len-l,&(pPack->head),pp,eMsg);
      l += i;
      if (l>=len) 
         break;
      pp = packArray+r;
   }
   *recCount = r;
   if (pp==NULL)
   {
		strcpy(eMsg,"多纪录解包要求packArray != NULL");
		return FALSE;
   }
   if (l>len)
   {
      return(FALSE);
   }
   return(TRUE);
}


// 函数名: _EncodeSingleItem
// 编程  : 陈永华修改 2004-2-18 23:00:14
// 描述  : 对指定的字段进行编码
// 返回  : int 编码使用缓存的长度
// 参数  : int idx  IN F_xxx表示的字段
// 参数  : ST_PACK *pPack IN 被编码的记录
// 参数  : char *pDst  OUT 编码存放的缓存
int _EncodeSingleItem(int idx,ST_PACK *pPack,char *pDst)
{
	int l;
	short vsl;


#define CP(a)	memcpy(pDst,pPack->a,sizeof(pPack->a)); \
				l=sizeof(pPack->a);
#define DP(a)	memcpy(pDst,&pPack->a,sizeof(pPack->a));\
				Reverse(pDst,sizeof(pPack->a));\
				l=sizeof(pPack->a);
#define VP(a)	vsl=strlen(pPack->a)+1;\
			   *((short *)pDst)=vsl;\
				Reverse(pDst,sizeof(short));\
				memcpy(pDst+2,pPack->a,vsl);\
			   l=2+vsl;
	switch(idx)
	{
	case F_SCUST_NO:
		CP(scust_no);
		break;
	case F_SCUST_NO2:
		CP(scust_no2);
		break;
	case F_SHOLDER_AC_NO:
		CP(sholder_ac_no);
		break;
	case F_SHOLDER_AC_NO2:
		CP(sholder_ac_no2);
		break;
	case F_SHOLDER_TYPE:
		CP(sholder_type);
		break;
	case F_SHOLDER_TYPE2:
		CP(sholder_type2);
		break;
	case F_SNAME:
		CP(sname);
		break;
	case F_SNAME2:
		CP(sname2);
		break;

	case F_SALL_NAME:
		CP(sall_name);
		break;
	case F_SMARKET_CODE:
		CP(smarket_code);
		break;
	case F_SMARKET_CODE2:
		CP(smarket_code2);
		break;
	case F_SDATE0:
		CP(sdate0);
		break;
	case F_SDATE1:
		CP(sdate1);
		break;
	case F_SDATE2:
		CP(sdate2);
		break;
	case F_SDATE3:
		CP(sdate3);
		break;
	case F_STIME0:
		CP(stime0);
		break;

	case F_STIME1:
		CP(stime1);
		break;
	case F_STIME2:
		CP(stime2);
		break;
	case F_STIME3:
		CP(stime3);
		break;
	case F_LVOL0:
		DP(lvol0);
		break;
	case F_LVOL1:
		DP(lvol1);
		break;
	case F_LVOL2:
		DP(lvol2);
		break;
	case F_LVOL3:
		DP(lvol3);
		break;
	case F_LVOL4:
		DP(lvol4);
		break;

	case F_LVOL5:
		DP(lvol5);
		break;
	case F_LVOL6:
		DP(lvol6);
		break;
	case F_LVOL7:
		DP(lvol7);
		break;
	case F_LVOL8:
		DP(lvol8);
		break;
	case F_LVOL9:
		DP(lvol9);
		break;
	case F_LVOL10:
		DP(lvol10);
		break;
	case F_LVOL11:
		DP(lvol11);
		break;
	case F_LVOL12:
		DP(lvol12);
		break;

	case F_DAMT0:
		DP(damt0);
		break;
	case F_DAMT1:
		DP(damt1);
		break;
	case F_DAMT2:
		DP(damt2);
		break;
	case F_DAMT3:
		DP(damt3);
		break;
	case F_DAMT4:
		DP(damt4);
		break;
	case F_DAMT5:
		DP(damt5);
		break;
	case F_DAMT6:
		DP(damt6);
		break;
	case F_DAMT7:
		DP(damt7);
		break;

	case F_DAMT8:
		DP(damt8);
		break;
	case F_DAMT9:
		DP(damt9);
		break;
	case F_DAMT10:
		DP(damt10);
		break;
	case F_DAMT11:
		DP(damt11);
		break;
	case F_DAMT12:
		DP(damt12);
		break;
	case F_DAMT13:
		DP(damt13);
		break;
	case F_DAMT14:
		DP(damt14);
		break;
	case F_DAMT15:
		DP(damt15);
		break;

	case F_DAMT16:
		DP(damt16);
		break;
	case F_DAMT17:
		DP(damt17);
		break;
	case F_DAMT18:
		DP(damt18);
		break;
	case F_DAMT19:
		DP(damt19);
		break;
	case F_DAMT20:
		DP(damt20);
		break;
	case F_DAMT21:
		DP(damt21);
		break;
	case F_DAMT22:
		DP(damt22);
		break;
	case F_DAMT23:
		DP(damt23);
		break;

	case F_DAMT24:
		DP(damt24);
		break;
	case F_DAMT25:
		DP(damt25);
		break;
	case F_DAMT26:
		DP(damt26);
		break;
	case F_DAMT27:
		DP(damt27);
		break;
	case F_DAMT28:
		DP(damt28);
		break;
	case F_DAMT29:
		DP(damt29);
		break;
	case F_DAMT30:
		DP(damt30);
		break;
	case F_DAMT31:
		DP(damt31);
		break;

	case F_DAMT32:
		DP(damt32);
		break;
	case F_DAMT33:
		DP(damt33);
		break;
	case F_SSTOCK_CODE:
		CP(sstock_code);
		break;
	case F_SSTOCK_CODE2:
		CP(sstock_code2);
		break;
	case F_SCUST_TYPE:
		CP(scust_type);
		break;
	case F_SCUST_TYPE2:
		CP(scust_type2);
		break;
	case F_SSTAT_TYPE:
		CP(sstat_type);
		break;
	case F_SSTAT_TYPE2:
		CP(sstat_type2);
		break;

	case F_SROOM_NO:
		CP(sroom_no);
		break;
	case F_SROOM_NO2:
		CP(sroom_no2);
		break;
	case F_SOPEN_EMP:
		CP(sopen_emp);
		break;
	case F_SCLOSE_EMP:
		CP(sclose_emp);
		break;
	case F_SCHANGE_EMP:
		CP(schange_emp);
		break;
	case F_SCHECK_EMP:
		CP(scheck_emp);
		break;
	case F_SEMP:
		CP(semp);
		break;
	case F_SNATION_CODE:
		CP(snation_code);
		break;

	case F_LCERT_CODE:
		DP(lcert_code);
		break;
	case F_STX_PWD:
		CP(stx_pwd);
		break;
	case F_STX_PWD2:
		CP(stx_pwd2);
		break;
	case F_SWITHDRAW_PWD:
		CP(swithdraw_pwd);
		break;
	case F_SWITHDRAW_PWD2:
		CP(swithdraw_pwd2);
		break;
	case F_SEMP_PWD:
		CP(semp_pwd);
		break;
	case F_SEMP_PWD2:
		CP(semp_pwd2);
		break;
	case F_SBANK_PWD:
		CP(sbank_pwd);
		break;

	case F_SBANK_PWD2:
		CP(sbank_pwd2);
		break;
	case F_SCUST_AUTH:
		CP(scust_auth);
		break;
	case F_SCUST_AUTH2:
		CP(scust_auth2);
		break;
	case F_SCUST_LIMIT:
		CP(scust_limit);
		break;
	case F_SCUST_LIMIT2:
		CP(scust_limit2);
		break;
	case F_LSAFE_LEVEL:
		DP(lsafe_level);
		break;
	case F_LSAFE_LEVEL2:
		DP(lsafe_level2);
		break;
	case F_SPOST_CODE:
		CP(spost_code);
		break;

	case F_SPOST_CODE2:
		CP(spost_code2);
		break;
	case F_SPHONE:
		CP(sphone);
		break;
	case F_SPHONE2:
		CP(sphone2);
		break;
	case F_SPHONE3:
		CP(sphone3);
		break;
	case F_SPAGER:
		CP(spager);
		break;
	case F_SEMAIL:
		CP(semail);
		break;
	case F_SEMAIL2:
		CP(semail2);
		break;
	case F_SNOTE:
		CP(snote);
		break;

	case F_SNOTE2:
		CP(snote2);
		break;
	case F_SCERT_NO:
		CP(scert_no);
		break;
	case F_SCERT_NO2:
		CP(scert_no2);
		break;
	case F_SCERT_ADDR:
		CP(scert_addr);
		break;
	case F_SSTATUS0:
		CP(sstatus0);
		break;
	case F_SSTATUS1:
		CP(sstatus1);
		break;
	case F_SSTATUS2:
		CP(sstatus2);
		break;
	case F_SSTATUS3:
		CP(sstatus3);
		break;

	case F_SSTATUS4:
		CP(sstatus4);
		break;
	case F_LWITHDRAW_FLAG:
		DP(lwithdraw_flag);
		break;
	case F_SADDR:
		CP(saddr);
		break;
	case F_SADDR2:
		CP(saddr2);
		break;
	case F_SSERIAL0:
		CP(sserial0);
		break;
	case F_SSERIAL1:
		CP(sserial1);
		break;
	case F_SSERIAL2:
		CP(sserial2);
		break;
	case F_SSERIAL3:
		CP(sserial3);
		break;

	case F_SSERIAL4:
		CP(sserial4);
		break;
	case F_SCURRENCY_TYPE:
		CP(scurrency_type);
		break;
	case F_SCURRENCY_TYPE2:
		CP(scurrency_type2);
		break;
	case F_SBRANCH_CODE0:
		CP(sbranch_code0);
		break;
	case F_SBRANCH_CODE1:
		CP(sbranch_code1);
		break;
	case F_SBRANCH_CODE2:
		CP(sbranch_code2);
		break;
	case F_USSET0:
		CP(usset0);
		break;
	case F_USSET1:
		CP(usset1);
		break;
	case F_USSET2:
		CP(usset2);
		break;
	case F_USSET3:
		CP(usset3);
		break;
	case F_USSET4:
		CP(usset4);
		break;
	case F_USSET5:
		CP(usset5);
		break;
	case F_USSET6:
		CP(usset6);
		break;
	case F_SSTATION0:
		CP(sstation0);
		break;
	case F_SSTATION1:
		CP(sstation1);
		break;
	case F_SBANK_ACC:
		CP(sbank_acc);
		break;

	case F_SBANK_ACC2:
		CP(sbank_acc2);
		break;
	case F_LBANK_ACC_TYPE:
		DP(lbank_acc_type);
		break;
	case F_LBANK_ACC_TYPE2:
		DP(lbank_acc_type2);
		break;
	case F_SMAIN_FLAG:
		CP(smain_flag);
		break;
	case F_SMAIN_FLAG2:
		CP(smain_flag2);
		break;
	case F_SBANK_CODE:
		CP(sbank_code);
		break;
	case F_SBANK_CODE2:
		CP(sbank_code2);
		break;
	case F_SEMP_NO:
		CP(semp_no);
		break;

	case F_SEMP_NO2:
		CP(semp_no2);
		break;
	case F_DRATE0:
		DP(drate0);
		break;
	case F_DRATE1:
		DP(drate1);
		break;
	case F_LSERIAL0:
		DP(lserial0);
		break;
	case F_LSERIAL1:
		DP(lserial1);
		break;
	case F_SBANKNAME:
		CP(sbankname);
		break;
	case F_SBANKNAME2:
		CP(sbankname2);
		break;
	case F_SCARD0:
		CP(scard0);
		break;

	case F_SCARD1:
		CP(scard1);
		break;
	case F_SORDER0:
		CP(sorder0);
		break;
	case F_SORDER1:
		CP(sorder1);
		break;
	case F_SORDER2:
		CP(sorder2);
		break;
	case F_SCUSTTYPES:
		CP(scusttypes);
		break;
	case F_SSECTYPES:
		CP(ssectypes);
		break;
	case F_VSMESS:
      pPack->vsmess[255]='\0';  // CYH 为了防止因为长度超界导致编码错，宁可提示信息错
		VP(vsmess);
		break;
	case F_VSVARSTR0:
      pPack->vsvarstr0[255]='\0';  // CYH 为了防止因为长度超界导致编码错，宁可提示信息错
		VP(vsvarstr0);
		break;
	case F_VSVARSTR1:
      pPack->vsvarstr1[255]='\0';  // CYH 为了防止因为长度超界导致编码错，宁可提示信息错
		VP(vsvarstr1);
		break;
	case F_VSVARSTR2:
      pPack->vsvarstr2[255]='\0';  // CYH 为了防止因为长度超界导致编码错，宁可提示信息错
		VP(vsvarstr2);
		break;

	case F_VSVARSTR3:
      pPack->vsvarstr3[255]='\0';  // CYH 为了防止因为长度超界导致编码错，宁可提示信息错
		VP(vsvarstr3);
		break;
	default:
		printf("encodesingleitem no this param =%d ......\n",idx);
      l = 0;
	}
#undef CP
#undef DP
#undef VP
   return(l);
}

int GetItemEncodeLength(int idx)
{
	int l;
   ST_PACK *pPack;

#define CP(a)	l=sizeof(pPack->a);
#define DP(a)	l=sizeof(pPack->a);
#define VP(a)	l=2+sizeof(pPack->a);
	switch(idx)
	{
	case F_SCUST_NO:
		CP(scust_no);
		break;
	case F_SCUST_NO2:
		CP(scust_no2);
		break;
	case F_SHOLDER_AC_NO:
		CP(sholder_ac_no);
		break;
	case F_SHOLDER_AC_NO2:
		CP(sholder_ac_no2);
		break;
	case F_SHOLDER_TYPE:
		CP(sholder_type);
		break;
	case F_SHOLDER_TYPE2:
		CP(sholder_type2);
		break;
	case F_SNAME:
		CP(sname);
		break;
	case F_SNAME2:
		CP(sname2);
		break;

	case F_SALL_NAME:
		CP(sall_name);
		break;
	case F_SMARKET_CODE:
		CP(smarket_code);
		break;
	case F_SMARKET_CODE2:
		CP(smarket_code2);
		break;
	case F_SDATE0:
		CP(sdate0);
		break;
	case F_SDATE1:
		CP(sdate1);
		break;
	case F_SDATE2:
		CP(sdate2);
		break;
	case F_SDATE3:
		CP(sdate3);
		break;
	case F_STIME0:
		CP(stime0);
		break;

	case F_STIME1:
		CP(stime1);
		break;
	case F_STIME2:
		CP(stime2);
		break;
	case F_STIME3:
		CP(stime3);
		break;
	case F_LVOL0:
		DP(lvol0);
		break;
	case F_LVOL1:
		DP(lvol1);
		break;
	case F_LVOL2:
		DP(lvol2);
		break;
	case F_LVOL3:
		DP(lvol3);
		break;
	case F_LVOL4:
		DP(lvol4);
		break;

	case F_LVOL5:
		DP(lvol5);
		break;
	case F_LVOL6:
		DP(lvol6);
		break;
	case F_LVOL7:
		DP(lvol7);
		break;
	case F_LVOL8:
		DP(lvol8);
		break;
	case F_LVOL9:
		DP(lvol9);
		break;
	case F_LVOL10:
		DP(lvol10);
		break;
	case F_LVOL11:
		DP(lvol11);
		break;
	case F_LVOL12:
		DP(lvol12);
		break;

	case F_DAMT0:
		DP(damt0);
		break;
	case F_DAMT1:
		DP(damt1);
		break;
	case F_DAMT2:
		DP(damt2);
		break;
	case F_DAMT3:
		DP(damt3);
		break;
	case F_DAMT4:
		DP(damt4);
		break;
	case F_DAMT5:
		DP(damt5);
		break;
	case F_DAMT6:
		DP(damt6);
		break;
	case F_DAMT7:
		DP(damt7);
		break;

	case F_DAMT8:
		DP(damt8);
		break;
	case F_DAMT9:
		DP(damt9);
		break;
	case F_DAMT10:
		DP(damt10);
		break;
	case F_DAMT11:
		DP(damt11);
		break;
	case F_DAMT12:
		DP(damt12);
		break;
	case F_DAMT13:
		DP(damt13);
		break;
	case F_DAMT14:
		DP(damt14);
		break;
	case F_DAMT15:
		DP(damt15);
		break;

	case F_DAMT16:
		DP(damt16);
		break;
	case F_DAMT17:
		DP(damt17);
		break;
	case F_DAMT18:
		DP(damt18);
		break;
	case F_DAMT19:
		DP(damt19);
		break;
	case F_DAMT20:
		DP(damt20);
		break;
	case F_DAMT21:
		DP(damt21);
		break;
	case F_DAMT22:
		DP(damt22);
		break;
	case F_DAMT23:
		DP(damt23);
		break;

	case F_DAMT24:
		DP(damt24);
		break;
	case F_DAMT25:
		DP(damt25);
		break;
	case F_DAMT26:
		DP(damt26);
		break;
	case F_DAMT27:
		DP(damt27);
		break;
	case F_DAMT28:
		DP(damt28);
		break;
	case F_DAMT29:
		DP(damt29);
		break;
	case F_DAMT30:
		DP(damt30);
		break;
	case F_DAMT31:
		DP(damt31);
		break;

	case F_DAMT32:
		DP(damt32);
		break;
	case F_DAMT33:
		DP(damt33);
		break;
	case F_SSTOCK_CODE:
		CP(sstock_code);
		break;
	case F_SSTOCK_CODE2:
		CP(sstock_code2);
		break;
	case F_SCUST_TYPE:
		CP(scust_type);
		break;
	case F_SCUST_TYPE2:
		CP(scust_type2);
		break;
	case F_SSTAT_TYPE:
		CP(sstat_type);
		break;
	case F_SSTAT_TYPE2:
		CP(sstat_type2);
		break;

	case F_SROOM_NO:
		CP(sroom_no);
		break;
	case F_SROOM_NO2:
		CP(sroom_no2);
		break;
	case F_SOPEN_EMP:
		CP(sopen_emp);
		break;
	case F_SCLOSE_EMP:
		CP(sclose_emp);
		break;
	case F_SCHANGE_EMP:
		CP(schange_emp);
		break;
	case F_SCHECK_EMP:
		CP(scheck_emp);
		break;
	case F_SEMP:
		CP(semp);
		break;
	case F_SNATION_CODE:
		CP(snation_code);
		break;

	case F_LCERT_CODE:
		DP(lcert_code);
		break;
	case F_STX_PWD:
		CP(stx_pwd);
		break;
	case F_STX_PWD2:
		CP(stx_pwd2);
		break;
	case F_SWITHDRAW_PWD:
		CP(swithdraw_pwd);
		break;
	case F_SWITHDRAW_PWD2:
		CP(swithdraw_pwd2);
		break;
	case F_SEMP_PWD:
		CP(semp_pwd);
		break;
	case F_SEMP_PWD2:
		CP(semp_pwd2);
		break;
	case F_SBANK_PWD:
		CP(sbank_pwd);
		break;

	case F_SBANK_PWD2:
		CP(sbank_pwd2);
		break;
	case F_SCUST_AUTH:
		CP(scust_auth);
		break;
	case F_SCUST_AUTH2:
		CP(scust_auth2);
		break;
	case F_SCUST_LIMIT:
		CP(scust_limit);
		break;
	case F_SCUST_LIMIT2:
		CP(scust_limit2);
		break;
	case F_LSAFE_LEVEL:
		DP(lsafe_level);
		break;
	case F_LSAFE_LEVEL2:
		DP(lsafe_level2);
		break;
	case F_SPOST_CODE:
		CP(spost_code);
		break;

	case F_SPOST_CODE2:
		CP(spost_code2);
		break;
	case F_SPHONE:
		CP(sphone);
		break;
	case F_SPHONE2:
		CP(sphone2);
		break;
	case F_SPHONE3:
		CP(sphone3);
		break;
	case F_SPAGER:
		CP(spager);
		break;
	case F_SEMAIL:
		CP(semail);
		break;
	case F_SEMAIL2:
		CP(semail2);
		break;
	case F_SNOTE:
		CP(snote);
		break;

	case F_SNOTE2:
		CP(snote2);
		break;
	case F_SCERT_NO:
		CP(scert_no);
		break;
	case F_SCERT_NO2:
		CP(scert_no2);
		break;
	case F_SCERT_ADDR:
		CP(scert_addr);
		break;
	case F_SSTATUS0:
		CP(sstatus0);
		break;
	case F_SSTATUS1:
		CP(sstatus1);
		break;
	case F_SSTATUS2:
		CP(sstatus2);
		break;
	case F_SSTATUS3:
		CP(sstatus3);
		break;

	case F_SSTATUS4:
		CP(sstatus4);
		break;
	case F_LWITHDRAW_FLAG:
		DP(lwithdraw_flag);
		break;
	case F_SADDR:
		CP(saddr);
		break;
	case F_SADDR2:
		CP(saddr2);
		break;
	case F_SSERIAL0:
		CP(sserial0);
		break;
	case F_SSERIAL1:
		CP(sserial1);
		break;
	case F_SSERIAL2:
		CP(sserial2);
		break;
	case F_SSERIAL3:
		CP(sserial3);
		break;

	case F_SSERIAL4:
		CP(sserial4);
		break;
	case F_SCURRENCY_TYPE:
		CP(scurrency_type);
		break;
	case F_SCURRENCY_TYPE2:
		CP(scurrency_type2);
		break;
	case F_SBRANCH_CODE0:
		CP(sbranch_code0);
		break;
	case F_SBRANCH_CODE1:
		CP(sbranch_code1);
		break;
	case F_SBRANCH_CODE2:
		CP(sbranch_code2);
		break;
	case F_USSET0:
		CP(usset0);
		break;
	case F_USSET1:
		CP(usset1);
		break;
	case F_USSET2:
		CP(usset2);
		break;
	case F_USSET3:
		CP(usset3);
		break;
	case F_USSET4:
		CP(usset4);
		break;
	case F_USSET5:
		CP(usset5);
		break;
	case F_USSET6:
		CP(usset6);
		break;
	case F_SSTATION0:
		CP(sstation0);
		break;
	case F_SSTATION1:
		CP(sstation1);
		break;
	case F_SBANK_ACC:
		CP(sbank_acc);
		break;

	case F_SBANK_ACC2:
		CP(sbank_acc2);
		break;
	case F_LBANK_ACC_TYPE:
		DP(lbank_acc_type);
		break;
	case F_LBANK_ACC_TYPE2:
		DP(lbank_acc_type2);
		break;
	case F_SMAIN_FLAG:
		CP(smain_flag);
		break;
	case F_SMAIN_FLAG2:
		CP(smain_flag2);
		break;
	case F_SBANK_CODE:
		CP(sbank_code);
		break;
	case F_SBANK_CODE2:
		CP(sbank_code2);
		break;
	case F_SEMP_NO:
		CP(semp_no);
		break;

	case F_SEMP_NO2:
		CP(semp_no2);
		break;
	case F_DRATE0:
		DP(drate0);
		break;
	case F_DRATE1:
		DP(drate1);
		break;
	case F_LSERIAL0:
		DP(lserial0);
		break;
	case F_LSERIAL1:
		DP(lserial1);
		break;
	case F_SBANKNAME:
		CP(sbankname);
		break;
	case F_SBANKNAME2:
		CP(sbankname2);
		break;
	case F_SCARD0:
		CP(scard0);
		break;

	case F_SCARD1:
		CP(scard1);
		break;
	case F_SORDER0:
		CP(sorder0);
		break;
	case F_SORDER1:
		CP(sorder1);
		break;
	case F_SORDER2:
		CP(sorder2);
		break;
	case F_SCUSTTYPES:
		CP(scusttypes);
		break;
	case F_SSECTYPES:
		CP(ssectypes);
		break;
	case F_VSMESS:
		VP(vsmess);
		break;
	case F_VSVARSTR0:
		VP(vsvarstr0);
		break;
	case F_VSVARSTR1:
		VP(vsvarstr1);
		break;
	case F_VSVARSTR2:
		VP(vsvarstr2);
		break;

	case F_VSVARSTR3:
		VP(vsvarstr3);
		break;
	default:
      l = 0;
	}
#undef CP
#undef DP
#undef VP
   return(l);
}

int EmulateEncodeLen(ST_PACKHEAD *phead)
{
   int i,j,l;
   unsigned char *pb = phead->ParmBits;
   l = 0;
   for (i=0;i<PARMBYTES;i++)
   {
      for (j=0;j<8;j++)
      {
         if (pb[i]&_bits[j])
         {
            l += GetItemEncodeLength((i<<8)+_bits[j]);
         }
      }
   }
   return(l);
}


BOOL ModifyHead(ST_PACKHEAD *pHeadPack,unsigned char *buf)
{
	ST_PACKHEAD *ph;
	ph = (ST_PACKHEAD *)buf;
	memcpy(ph,pHeadPack,sizeof(ST_PACKHEAD));
	Reverse((unsigned char *)&ph->RequestType,sizeof(pHeadPack->RequestType));
	Reverse((unsigned char *)&ph->firstflag,sizeof(pHeadPack->firstflag));
	Reverse((unsigned char *)&ph->nextflag,sizeof(pHeadPack->nextflag));
	Reverse((unsigned char *)&ph->recCount,sizeof(pHeadPack->recCount));
	Reverse((unsigned char *)&ph->retCode,sizeof(pHeadPack->retCode));
	Reverse((unsigned char *)&ph->hook.UserID,sizeof(pHeadPack->hook.UserID));
	Reverse((unsigned char *)&ph->hook.queuetype,sizeof(pHeadPack->hook.queuetype));
	return TRUE;
}

BOOL EncodeRow(ST_PACKHEAD *pHead,ST_PACK *pRowPack,unsigned char *buf,int *len,char *eMsg)
{
	int l;
	int i,j;
	unsigned char *pb;

	l = 0;
   pb = pHead->ParmBits;
	for(i=0;i<PARMBYTES;i++)
	{
		for(j=0;j<8;j++)
		{
			if (pb[i] & _bits[j])
         {
            l+=_EncodeSingleItem((i<<8)+_bits[j],pRowPack,(char *)buf+l);
         }
		}
	}
	*len = l;
	return TRUE;
}


BOOL EncodeBuf(ST_CPACK *pPack,unsigned char *buf,int *len,char *eMsg)
{
	int l;
	unsigned char *p;
	ST_PACKHEAD *ph;

   ph = &(pPack->head);
   ModifyHead(ph,buf);
   l = 0;
   p = buf+sizeof(ST_PACKHEAD);

/* ****** Updated by CHENYH at 2004-2-18 13:48:28 ****** 
	l = sizeof(ST_PACKHEAD);
	p = buf;
	memcpy(p,&pPack->head,sizeof(pPack->head));
	ph = (ST_PACKHEAD*)p;
	Reverse((unsigned char *)&ph->RequestType,sizeof(pPack->head.RequestType));
	Reverse((unsigned char *)&ph->firstflag,sizeof(pPack->head.firstflag));
	Reverse((unsigned char *)&ph->nextflag,sizeof(pPack->head.nextflag));
	Reverse((unsigned char *)&ph->recCount,sizeof(pPack->head.recCount));
	Reverse((unsigned char *)&ph->retCode,sizeof(pPack->head.retCode));
	Reverse((unsigned char *)&ph->hook.UserID,sizeof(pPack->head.hook.UserID));
	Reverse((unsigned char *)&ph->hook.queuetype,sizeof(pPack->head.hook.queuetype));
	ph = &pPack->head;
	p+=sizeof(pPack->head);
*/
   EncodeRow(ph,&(pPack->pack),p,&l,eMsg);
   *len = l+sizeof(ST_PACKHEAD);
	return TRUE;
}

BOOL EncodeBufArray(ST_CPACK *pPack,ST_PACK *pArray,unsigned char *buf,int *len,char *eMsg)
{
	int l,ll;
	unsigned char *p;
	int cnt;
	ST_PACK *pp;

	if (pPack->head.recCount>1 && pArray == NULL)
	{
		strcpy(eMsg,"多纪录压包要求pArray != NULL");
		return FALSE;
	}
   p = buf; *len = 0;
   if (EncodeBuf(pPack,buf,&l,eMsg))
   {
      p = buf+l;
      ll = l;
      cnt = pPack->head.recCount-1;
      pp = pArray;
      for (;cnt>0;cnt--)
      {
         EncodeRow(&(pPack->head),pp,p,&l,eMsg);
         pp++;
         p += l;
         ll += l;         
      }
      *len = ll;
      return(TRUE);
   }
   else return(FALSE);

/* ****** Updated by CHENYH at 2004-2-18 14:04:51 ****** 

	l = sizeof(ST_PACKHEAD);
	p = buf;
	memcpy(p,&pPack->head,sizeof(pPack->head));
	ph = (ST_PACKHEAD*)p;
	Reverse((unsigned char *)&ph->RequestType,sizeof(pPack->head.RequestType));
	Reverse((unsigned char *)&ph->firstflag,sizeof(pPack->head.firstflag));
	Reverse((unsigned char *)&ph->nextflag,sizeof(pPack->head.nextflag));
	Reverse((unsigned char *)&ph->recCount,sizeof(pPack->head.recCount));
	Reverse((unsigned char *)&ph->retCode,sizeof(pPack->head.retCode));
	Reverse((unsigned char *)&ph->hook.UserID,sizeof(pPack->head.hook.UserID));
	Reverse((unsigned char *)&ph->hook.queuetype,sizeof(pPack->head.hook.queuetype));
	ph = &pPack->head;
	p+=sizeof(pPack->head);
	pp = &pPack->pack;

	for(cnt = 0; cnt < (int)(pPack->head.recCount); cnt ++ )
	{
		for(i=0;i<PARMBYTES;i++)
		{
			b0 = ph->ParmBits[i];
			for(j=0;j<8;j++)
			{
				if (b0 & _bits[j])
					result = (i<<8)+_bits[j];
				else
					continue;
				_EncodeSingleItem(result,pp,(char **)&p,&l);
			}
		}
		if (pArray == NULL)
			break;
		pp = &pArray[cnt];
	}
	*len = l;
	return TRUE;

*/
}

BOOL SetParmBit(ST_PACKHEAD *ph,int bit)
{
	unsigned short hi,low;

	hi = (bit&0xFF00)>>8;
	low = (bit &0x00ff);
	if (hi>PARMBYTES)
		return FALSE;
	ph->ParmBits[hi]|=low;
	return TRUE;
}

BOOL ClearParmBit(ST_PACKHEAD *ph,int bit)
{
	unsigned short hi,low;

   hi = (bit&0xFF00)>>8;
   low = (bit &0x00ff);
   if (hi>=PARMBYTES)
      return FALSE;
   ph->ParmBits[hi] &= ~low;
	return TRUE;
}


void ShowPackNext(ST_CPACK *pPack,ST_PACK *pack,char *buf)
{
	int i;
	unsigned char b0;
	int j;
	int result;

	strcpy(buf,"\n");
	for(i=0;i<PARMBYTES;i++)
	{
		b0 = pPack->head.ParmBits[i];
		for(j=0;j<8;j++)
		{
			if (b0 & _bits[j])
				result = (i<<8)+_bits[j];
			else
				continue;
			ShowPackItem(result,pack,buf+strlen(buf));
		}
	}
}


BOOL SetErrorPack(ST_CPACK *inPack,ST_CPACK *outPack,
				  char *emsg,int eCode)
{
	char e[300];

	memcpy(&outPack->head.addr,&inPack->head.addr,sizeof(outPack->head.addr));
	memcpy(outPack->head.hook.queuename,inPack->head.hook.queuename,
		sizeof(inPack->head.hook.queuename));
	outPack->head.hook.queuetype = inPack->head.hook.queuetype;
	memcpy(outPack->head.hook.hostname,inPack->head.hook.hostname,
		sizeof(inPack->head.hook.hostname));
	outPack->head.firstflag = 1;
	outPack->head.nextflag = 0;
	outPack->head.recCount = 1;
	outPack->head.retCode = eCode;
	memset(outPack->head.ParmBits,0,sizeof(outPack->head.ParmBits));
	outPack->head.hook.UserID = inPack->head.hook.UserID;

	if (strlen(emsg)>250)
		memcpy(e,emsg,250);
	else
		strcpy(e,emsg);
	e[250]=0;
	strcpy(outPack->pack.vsmess,e);
	SetParmBit(&outPack->head , F_VSMESS);
	return 1;
}

BOOL SetErrorPack2(ST_CPACK *outPack,char *emsg,int eCode)
{
	char e[300];

	memset((char *)outPack,0,sizeof(ST_CPACK));
	outPack->head.firstflag = 1;
	outPack->head.nextflag = 0;
	outPack->head.recCount = 1;
	outPack->head.retCode = eCode;
	memset(outPack->head.ParmBits,0,sizeof(outPack->head.ParmBits));

	if (strlen(emsg)>250)
		memcpy(e,emsg,250);
	else
		strcpy(e,emsg);
	e[250]=0;
	strcpy(outPack->pack.vsmess,e);
	SetParmBit(&outPack->head , F_VSMESS);
	return 1;
}

BOOL SetErrorPackNew(ST_CPACK *inPack,ST_CPACK *outPack,
				  char *emsg,char *emsg2,int eCode)
{
	char e[300];

	memcpy(&outPack->head.addr,&inPack->head.addr,sizeof(outPack->head.addr));
	memcpy(outPack->head.hook.queuename,inPack->head.hook.queuename,
		sizeof(inPack->head.hook.queuename));
	outPack->head.hook.queuetype = inPack->head.hook.queuetype;
	memcpy(outPack->head.hook.hostname,inPack->head.hook.hostname,
		sizeof(inPack->head.hook.hostname));
	outPack->head.firstflag = 1;
	outPack->head.nextflag = 0;
	outPack->head.recCount = 1;
	outPack->head.retCode = eCode;
	memset(outPack->head.ParmBits,0,sizeof(outPack->head.ParmBits));
	outPack->head.hook.UserID = inPack->head.hook.UserID;

	if (strlen(emsg)>250)
		memcpy(e,emsg,250);
	else
		strcpy(e,emsg);
	e[250]=0;
	strcpy(outPack->pack.vsmess,e);
	SetParmBit(&outPack->head , F_VSMESS);

	if (strlen(emsg2)>250)
		memcpy(e,emsg2,250);
	else
		strcpy(e,emsg2);
	e[250]=0;
	strcpy(outPack->pack.vsvarstr0,e);
	SetParmBit(&outPack->head , F_VSVARSTR0);
	return 1;
}

BOOL SetErrorPack2New(ST_CPACK *outPack,char *emsg,char *emsg2,int eCode)
{
	char e[300];

	memset((char *)outPack,0,sizeof(ST_CPACK));
	outPack->head.firstflag = 1;
	outPack->head.nextflag = 0;
	outPack->head.recCount = 1;
	outPack->head.retCode = eCode;
	memset(outPack->head.ParmBits,0,sizeof(outPack->head.ParmBits));

	if (strlen(emsg)>250)
		memcpy(e,emsg,250);
	else
		strcpy(e,emsg);
	e[250]=0;
	strcpy(outPack->pack.vsmess,e);
	SetParmBit(&outPack->head , F_VSMESS);

	if (strlen(emsg2)>250)
		memcpy(e,emsg2,250);
	else
		strcpy(e,emsg2);
	e[250]=0;
	strcpy(outPack->pack.vsvarstr0,e);
	SetParmBit(&outPack->head , F_VSVARSTR0);
	return 1;
}

BOOL SetNormalPack(ST_CPACK *inPack,ST_CPACK *outPack,int nextflag,
				   int recCount)
{

	memcpy(&outPack->head.addr,&inPack->head.addr,sizeof(inPack->head.addr));
	memcpy(outPack->head.hook.queuename,inPack->head.hook.queuename,
		sizeof(inPack->head.hook.queuename));
	outPack->head.hook.queuetype = inPack->head.hook.queuetype;
	memcpy(outPack->head.hook.hostname,inPack->head.hook.hostname,
		sizeof(inPack->head.hook.hostname));
	outPack->head.firstflag = inPack->head.firstflag;
	outPack->head.nextflag = nextflag;
	outPack->head.recCount = recCount;
	outPack->head.retCode = 0;
	memset(outPack->head.ParmBits,0,sizeof(outPack->head.ParmBits));
	outPack->head.hook.UserID = inPack->head.hook.UserID;
	return TRUE;
}

void ShowPack(ST_CPACK *pack,char *buf)
{
	int i;
	unsigned char b0;
	int j;
	int result;
	int oldlen,len;
	len=0;
	sprintf(buf,"HEAD ");
	sprintf(buf+strlen(buf),"REQ=%d,",pack->head.RequestType);
	sprintf(buf+strlen(buf),"FL=%d,",pack->head.firstflag);
	sprintf(buf+strlen(buf),"NL=%d,",pack->head.nextflag);
	sprintf(buf+strlen(buf),"REC=%d,",pack->head.recCount);
	sprintf(buf+strlen(buf),"CODE=%d,",pack->head.retCode);
	sprintf(buf+strlen(buf),"USER=%d,",pack->head.userdata);
//	sprintf(buf+strlen(buf),"USERID=%d,",pack->head.hook.UserID);
	sprintf(buf+strlen(buf),"HOST=%s,",pack->head.hook.hostname);
	sprintf(buf+strlen(buf),"QUEUE=%s,",pack->head.hook.queuename);
//	sprintf(buf+strlen(buf),"QUEUETYPE=%d,",pack->head.hook.queuetype);
//	sprintf(buf+strlen(buf),"ADDR=");
//	ShowHex((unsigned char *)&pack->head.addr,sizeof(pack->head.addr),buf+strlen(buf));
	sprintf(buf+strlen(buf)," HEAD");

	/*
	sprintf(buf+strlen(buf),"PACK.HEAD.ParmBits:");
	ShowHex(pack->head.ParmBits,sizeof(pack->head.ParmBits),buf+strlen(buf));
	*/
	printf("%s\n",buf);
	strcpy(buf,"\0");
	printf("PACK________________________________________________________<\n");
	oldlen=strlen(buf);
	for(i=0;i<PARMBYTES;i++)
	{
		b0 = pack->head.ParmBits[i];
		for(j=0;j<8;j++)
		{
			if (b0 & _bits[j])
				result = (i<<8)+_bits[j];
			else
				continue;
			ShowPackItem(result,&(pack->pack),buf+strlen(buf));
			if( (strlen(buf)-oldlen)>70)
			{
				printf("%s\n",buf);
				strcpy(buf,"\0");
				oldlen=strlen(buf);
			}
		}
	}
	sprintf(buf+strlen(buf)-1,"\nPACK________________________________________________________>\n");
	printf("%s",buf);
}

void ShowHex(unsigned char *p,int len,char* buf)
{
	int i;
	for(i=0;i<len;i++)
	{
		sprintf(buf+i*4,"[%02x]",p[i]);
	}
}

void ShowPackItem(int idx,ST_PACK *pack,char *buf)
{
#define PC(b,a,c)	sprintf(c,"%s=%s,",b,pack->a);
#define PI(b,a,c)	sprintf(c,"%s=%d,",b,pack->a);
#define PD(b,a,c)	sprintf(c,"%s=%lf,",b,pack->a);
#define PH(b,a,c)	sprintf(c,"%s=",b); \
					ShowHex(pack->a,sizeof(pack->a),c+strlen(c)); \
					sprintf(c+strlen(c),"%s",",");
#define PV(b,a,c)	sprintf(c,"%s=%s,",b,pack->a);

	switch(idx)
	{
	case F_SCUST_NO:
		PC("SCUST_NO",scust_no,buf);
		break;
	case F_SCUST_NO2:
		PC("SCUST_NO2",scust_no2,buf);
		break;
	case F_SHOLDER_AC_NO:
		PC("SHOLDER_AC_NO",sholder_ac_no,buf);
		break;
	case F_SHOLDER_AC_NO2:
		PC("SHOLDER_AC_NO2",sholder_ac_no2,buf);
		break;
	case F_SHOLDER_TYPE:
		PC("SHOLDER_TYPE",sholder_type,buf);
		break;
	case F_SHOLDER_TYPE2:
		PC("SHOLDER_TYPE2",sholder_type2,buf);
		break;
	case F_SNAME:
		PC("SNAME",sname,buf);
		break;
	case F_SNAME2:
		PC("SNAME2",sname2,buf);
		break;

	case F_SALL_NAME:
		PC("SALL_NAME",sall_name,buf);
		break;
	case F_SMARKET_CODE:
		PC("SMARKET_CODE",smarket_code,buf);
		break;
	case F_SMARKET_CODE2:
		PC("SMARKET_CODE2",smarket_code2,buf);
		break;
	case F_SDATE0:
		PC("SDATE0",sdate0,buf);
		break;
	case F_SDATE1:
		PC("SDATE1",sdate1,buf);
		break;
	case F_SDATE2:
		PC("SDATE2",sdate2,buf);
		break;
	case F_SDATE3:
		PC("SDATE3",sdate3,buf);
		break;
	case F_STIME0:
		PC("STIME0",stime0,buf);
		break;

	case F_STIME1:
		PC("STIME1",stime1,buf);
		break;
	case F_STIME2:
		PC("STIME2",stime2,buf);
		break;
	case F_STIME3:
		PC("STIME3",stime3,buf);
		break;
	case F_LVOL0:
		PI("LVOL0",lvol0,buf);
		break;
	case F_LVOL1:
		PI("LVOL1",lvol1,buf);
		break;
	case F_LVOL2:
		PI("LVOL2",lvol2,buf);
		break;
	case F_LVOL3:
		PI("LVOL3",lvol3,buf);
		break;
	case F_LVOL4:
		PI("LVOL4",lvol4,buf);
		break;

	case F_LVOL5:
		PI("LVOL5",lvol5,buf);
		break;
	case F_LVOL6:
		PI("LVOL6",lvol6,buf);
		break;
	case F_LVOL7:
		PI("LVOL7",lvol7,buf);
		break;
	case F_LVOL8:
		PI("LVOL8",lvol8,buf);
		break;
	case F_LVOL9:
		PI("LVOL9",lvol9,buf);
		break;
	case F_LVOL10:
		PI("LVOL10",lvol10,buf);
		break;
	case F_LVOL11:
		PI("LVOL11",lvol11,buf);
		break;
	case F_LVOL12:
		PI("LVOL12",lvol12,buf);
		break;

	case F_DAMT0:
		PD("DAMT0",damt0,buf);
		break;
	case F_DAMT1:
		PD("DAMT1",damt1,buf);
		break;
	case F_DAMT2:
		PD("DAMT2",damt2,buf);
		break;
	case F_DAMT3:
		PD("DAMT3",damt3,buf);
		break;
	case F_DAMT4:
		PD("DAMT4",damt4,buf);
		break;
	case F_DAMT5:
		PD("DAMT5",damt5,buf);
		break;
	case F_DAMT6:
		PD("DAMT6",damt6,buf);
		break;
	case F_DAMT7:
		PD("DAMT7",damt7,buf);
		break;

	case F_DAMT8:
		PD("DAMT8",damt8,buf);
		break;
	case F_DAMT9:
		PD("DAMT9",damt9,buf);
		break;
	case F_DAMT10:
		PD("DAMT10",damt10,buf);
		break;
	case F_DAMT11:
		PD("DAMT11",damt11,buf);
		break;
	case F_DAMT12:
		PD("DAMT12",damt12,buf);
		break;
	case F_DAMT13:
		PD("DAMT13",damt13,buf);
		break;
	case F_DAMT14:
		PD("DAMT14",damt14,buf);
		break;
	case F_DAMT15:
		PD("DAMT15",damt15,buf);
		break;

	case F_DAMT16:
		PD("DAMT16",damt16,buf);
		break;
	case F_DAMT17:
		PD("DAMT17",damt17,buf);
		break;
	case F_DAMT18:
		PD("DAMT18",damt18,buf);
		break;
	case F_DAMT19:
		PD("DAMT19",damt19,buf);
		break;
	case F_DAMT20:
		PD("DAMT20",damt20,buf);
		break;
	case F_DAMT21:
		PD("DAMT21",damt21,buf);
		break;
	case F_DAMT22:
		PD("DAMT22",damt22,buf);
		break;
	case F_DAMT23:
		PD("DAMT23",damt23,buf);
		break;

	case F_DAMT24:
		PD("DAMT24",damt24,buf);
		break;
	case F_DAMT25:
		PD("DAMT25",damt25,buf);
		break;
	case F_DAMT26:
		PD("DAMT26",damt26,buf);
		break;
	case F_DAMT27:
		PD("DAMT27",damt27,buf);
		break;
	case F_DAMT28:
		PD("DAMT28",damt28,buf);
		break;
	case F_DAMT29:
		PD("DAMT29",damt29,buf);
		break;
	case F_DAMT30:
		PD("DAMT30",damt30,buf);
		break;
	case F_DAMT31:
		PD("DAMT31",damt31,buf);
		break;

	case F_DAMT32:
		PD("DAMT32",damt32,buf);
		break;
	case F_DAMT33:
		PD("DAMT33",damt33,buf);
		break;
	case F_SSTOCK_CODE:
		PC("SSTOCK_CODE",sstock_code,buf);
		break;
	case F_SSTOCK_CODE2:
		PC("SSTOCK_CODE2",sstock_code2,buf);
		break;
	case F_SCUST_TYPE:
		PC("SCUST_TYPE",scust_type,buf);
		break;
	case F_SCUST_TYPE2:
		PC("SCUST_TYPE2",scust_type2,buf);
		break;
	case F_SSTAT_TYPE:
		PC("SSTAT_TYPE",sstat_type,buf);
		break;
	case F_SSTAT_TYPE2:
		PC("SSTAT_TYPE2",sstat_type2,buf);
		break;

	case F_SROOM_NO:
		PC("SROOM_NO",sroom_no,buf);
		break;
	case F_SROOM_NO2:
		PC("SROOM_NO2",sroom_no2,buf);
		break;
	case F_SOPEN_EMP:
		PC("SOPEN_EMP",sopen_emp,buf);
		break;
	case F_SCLOSE_EMP:
		PC("SCLOSE_EMP",sclose_emp,buf);
		break;
	case F_SCHANGE_EMP:
		PC("SCHANGE_EMP",schange_emp,buf);
		break;
	case F_SCHECK_EMP:
		PC("SCHECK_EMP",scheck_emp,buf);
		break;
	case F_SEMP:
		PC("SEMP",semp,buf);
		break;
	case F_SNATION_CODE:
		PC("SNATION_CODE",snation_code,buf);
		break;

	case F_LCERT_CODE:
		PI("LCERT_CODE",lcert_code,buf);
		break;
	case F_STX_PWD:
		PC("STX_PWD",stx_pwd,buf);
		break;
	case F_STX_PWD2:
		PC("STX_PWD2",stx_pwd2,buf);
		break;
	case F_SWITHDRAW_PWD:
		PC("SWITHDRAW_PWD",swithdraw_pwd,buf);
		break;
	case F_SWITHDRAW_PWD2:
		PC("SWITHDRAW_PWD2",swithdraw_pwd2,buf);
		break;
	case F_SEMP_PWD:
		PC("SEMP_PWD",semp_pwd,buf);
		break;
	case F_SEMP_PWD2:
		PC("SEMP_PWD2",semp_pwd2,buf);
		break;
	case F_SBANK_PWD:
		PC("SBANK_PWD",sbank_pwd,buf);
		break;

	case F_SBANK_PWD2:
		PC("SBANK_PWD2",sbank_pwd2,buf);
		break;
	case F_SCUST_AUTH:
		PC("SCUST_AUTH",scust_auth,buf);
		break;
	case F_SCUST_AUTH2:
		PC("SCUST_AUTH2",scust_auth2,buf);
		break;
	case F_SCUST_LIMIT:
		PC("SCUST_LIMIT",scust_limit,buf);
		break;
	case F_SCUST_LIMIT2:
		PC("SCUST_LIMIT2",scust_limit2,buf);
		break;
	case F_LSAFE_LEVEL:
		PI("LSAFE_LEVEL",lsafe_level,buf);
		break;
	case F_LSAFE_LEVEL2:
		PI("LSAFE_LEVEL2",lsafe_level2,buf);
		break;
	case F_SPOST_CODE:
		PC("SPOST_CODE",spost_code,buf);
		break;

	case F_SPOST_CODE2:
		PC("SPOST_CODE2",spost_code2,buf);
		break;
	case F_SPHONE:
		PC("SPHONE",sphone,buf);
		break;
	case F_SPHONE2:
		PC("SPHONE2",sphone2,buf);
		break;
	case F_SPHONE3:
		PC("SPHONE3",sphone3,buf);
		break;
	case F_SPAGER:
		PC("SPAGER",spager,buf);
		break;
	case F_SEMAIL:
		PC("SEMAIL",semail,buf);
		break;
	case F_SEMAIL2:
		PC("SEMAIL2",semail2,buf);
		break;
	case F_SNOTE:
		PC("SNOTE",snote,buf);
		break;

	case F_SNOTE2:
		PC("SNOTE2",snote2,buf);
		break;
	case F_SCERT_NO:
		PC("SCERT_NO",scert_no,buf);
		break;
	case F_SCERT_NO2:
		PC("SCERT_NO2",scert_no2,buf);
		break;
	case F_SCERT_ADDR:
		PC("SCERT_ADDR",scert_addr,buf);
		break;
	case F_SSTATUS0:
		PC("SSTATUS0",sstatus0,buf);
		break;
	case F_SSTATUS1:
		PC("SSTATUS1",sstatus1,buf);
		break;
	case F_SSTATUS2:
		PC("SSTATUS2",sstatus2,buf);
		break;
	case F_SSTATUS3:
		PC("SSTATUS3",sstatus3,buf);
		break;

	case F_SSTATUS4:
		PC("SSTATUS4",sstatus4,buf);
		break;
	case F_LWITHDRAW_FLAG:
		PI("LWITHDRAW_FLAG",lwithdraw_flag,buf);
		break;
	case F_SADDR:
		PC("SADDR",saddr,buf);
		break;
	case F_SADDR2:
		PC("SADDR2",saddr2,buf);
		break;
	case F_SSERIAL0:
		PC("SSERIAL0",sserial0,buf);
		break;
	case F_SSERIAL1:
		PC("SSERIAL1",sserial1,buf);
		break;
	case F_SSERIAL2:
		PC("SSERIAL2",sserial2,buf);
		break;
	case F_SSERIAL3:
		PC("SSERIAL3",sserial3,buf);
		break;

	case F_SSERIAL4:
		PC("SSERIAL4",sserial4,buf);
		break;
	case F_SCURRENCY_TYPE:
		PC("SCURRENCY_TYPE",scurrency_type,buf);
		break;
	case F_SCURRENCY_TYPE2:
		PC("SCURRENCY_TYPE2",scurrency_type2,buf);
		break;
	case F_SBRANCH_CODE0:
		PC("SBRANCH_CODE0",sbranch_code0,buf);
		break;
	case F_SBRANCH_CODE1:
		PC("SBRANCH_CODE1",sbranch_code1,buf);
		break;
	case F_SBRANCH_CODE2:
		PC("SBRANCH_CODE2",sbranch_code2,buf);
		break;
	case F_USSET0:
		PH("USSET0",usset0,buf);
		break;
	case F_USSET1:
		PH("USSET1",usset1,buf);
		break;

	case F_USSET2:
		PH("USSET2",usset2,buf);
		break;
	case F_USSET3:
		PH("USSET3",usset3,buf);
		break;
	case F_USSET4:
		PH("USSET4",usset4,buf);
		break;
	case F_USSET5:
		PH("USSET5",usset5,buf);
		break;
	case F_USSET6:
		PH("USSET6",usset6,buf);
		break;
	case F_SSTATION0:
		PC("SSTATION0",sstation0,buf);
		break;
	case F_SSTATION1:
		PC("SSTATION1",sstation1,buf);
		break;
	case F_SBANK_ACC:
		PC("SBANK_ACC",sbank_acc,buf);
		break;

	case F_SBANK_ACC2:
		PC("SBANK_ACC2",sbank_acc2,buf);
		break;
	case F_LBANK_ACC_TYPE:
		PI("LBANK_ACC_TYPE",lbank_acc_type,buf);
		break;
	case F_LBANK_ACC_TYPE2:
		PI("LBANK_ACC_TYPE2",lbank_acc_type2,buf);
		break;
	case F_SMAIN_FLAG:
		PC("SMAIN_FLAG",smain_flag,buf);
		break;
	case F_SMAIN_FLAG2:
		PC("SMAIN_FLAG2",smain_flag2,buf);
		break;
	case F_SBANK_CODE:
		PC("SBANK_CODE",sbank_code,buf);
		break;
	case F_SBANK_CODE2:
		PC("SBANK_CODE2",sbank_code2,buf);
		break;
	case F_SEMP_NO:
		PC("SEMP_NO",semp_no,buf);
		break;

	case F_SEMP_NO2:
		PC("SEMP_NO2",semp_no2,buf);
		break;
	case F_DRATE0:
		PD("DRATE0",drate0,buf);
		break;
	case F_DRATE1:
		PD("DRATE1",drate1,buf);
		break;
	case F_LSERIAL0:
		PI("LSERIAL0",lserial0,buf);
		break;
	case F_LSERIAL1:
		PI("LSERIAL1",lserial1,buf);
		break;
	case F_SBANKNAME:
		PC("SBANKNAME",sbankname,buf);
		break;
	case F_SBANKNAME2:
		PC("SBANKNAME2",sbankname2,buf);
		break;
	case F_SCARD0:
		PC("SCARD0",scard0,buf);
		break;

	case F_SCARD1:
		PC("SCARD1",scard1,buf);
		break;
	case F_SORDER0:
		PC("SORDER0",sorder0,buf);
		break;
	case F_SORDER1:
		PC("SORDER1",sorder1,buf);
		break;
	case F_SORDER2:
		PC("SORDER2",sorder2,buf);
		break;
	case F_VSMESS:
		PV("VSMESS",vsmess,buf);
		break;
	case F_SCUSTTYPES:
		PC("SCUSTTYPES",scusttypes,buf);
		break;
	case F_SSECTYPES:
		PC("SSECSTTYPES",ssectypes,buf);
		break;
	case F_VSVARSTR0:
		PV("VSVARSTR0",vsvarstr0,buf);
		break;
	case F_VSVARSTR1:
		PV("VSVARSTR1",vsvarstr1,buf);
		break;
	case F_VSVARSTR2:
		PV("VSVARSTR2",vsvarstr2,buf);
		break;

	case F_VSVARSTR3:
		PC("VSVARSTR3",vsvarstr3,buf);
		break;
	}
#undef PC
#undef PI
#undef PD
#undef PH
}

void GetPatitionKey(int patitionmap,ST_PACK pack,char *key)
{
#define CP(a)	memcpy(key,pack.a,sizeof(pack.a));
#define DP(a)	memcpy(key,&pack.a,sizeof(pack.a));
#define VP(a)	memcpy(key,pack.a,sizeof(pack.a));

	switch(patitionmap)
	{
	case F_SCUST_NO:
		CP(scust_no);
		break;
	case F_SCUST_NO2:
		CP(scust_no2);
		break;
	case F_SHOLDER_AC_NO:
		CP(sholder_ac_no);
		break;
	case F_SHOLDER_AC_NO2:
		CP(sholder_ac_no2);
		break;
	case F_SHOLDER_TYPE:
		CP(sholder_type);
		break;
	case F_SHOLDER_TYPE2:
		CP(sholder_type2);
		break;
	case F_SNAME:
		CP(sname);
		break;
	case F_SNAME2:
		CP(sname2);
		break;

	case F_SALL_NAME:
		CP(sall_name);
		break;
	case F_SMARKET_CODE:
		CP(smarket_code);
		break;
	case F_SMARKET_CODE2:
		CP(smarket_code2);
		break;
	case F_SDATE0:
		CP(sdate0);
		break;
	case F_SDATE1:
		CP(sdate1);
		break;
	case F_SDATE2:
		CP(sdate2);
		break;
	case F_SDATE3:
		CP(sdate3);
		break;
	case F_STIME0:
		CP(stime0);
		break;

	case F_STIME1:
		CP(stime1);
		break;
	case F_STIME2:
		CP(stime2);
		break;
	case F_STIME3:
		CP(stime3);
		break;
	case F_LVOL0:
		DP(lvol0);
		break;
	case F_LVOL1:
		DP(lvol1);
		break;
	case F_LVOL2:
		DP(lvol2);
		break;
	case F_LVOL3:
		DP(lvol3);
		break;
	case F_LVOL4:
		DP(lvol4);
		break;

	case F_LVOL5:
		DP(lvol5);
		break;
	case F_LVOL6:
		DP(lvol6);
		break;
	case F_LVOL7:
		DP(lvol7);
		break;
	case F_LVOL8:
		DP(lvol8);
		break;
	case F_LVOL9:
		DP(lvol9);
		break;
	case F_LVOL10:
		DP(lvol10);
		break;
	case F_LVOL11:
		DP(lvol11);
		break;
	case F_LVOL12:
		DP(lvol12);
		break;

	case F_DAMT0:
		DP(damt0);
		break;
	case F_DAMT1:
		DP(damt1);
		break;
	case F_DAMT2:
		DP(damt2);
		break;
	case F_DAMT3:
		DP(damt3);
		break;
	case F_DAMT4:
		DP(damt4);
		break;
	case F_DAMT5:
		DP(damt5);
		break;
	case F_DAMT6:
		DP(damt6);
		break;
	case F_DAMT7:
		DP(damt7);
		break;

	case F_DAMT8:
		DP(damt8);
		break;
	case F_DAMT9:
		DP(damt9);
		break;
	case F_DAMT10:
		DP(damt10);
		break;
	case F_DAMT11:
		DP(damt11);
		break;
	case F_DAMT12:
		DP(damt12);
		break;
	case F_DAMT13:
		DP(damt13);
		break;
	case F_DAMT14:
		DP(damt14);
		break;
	case F_DAMT15:
		DP(damt15);
		break;

	case F_DAMT16:
		DP(damt16);
		break;
	case F_DAMT17:
		DP(damt17);
		break;
	case F_DAMT18:
		DP(damt18);
		break;
	case F_DAMT19:
		DP(damt19);
		break;
	case F_DAMT20:
		DP(damt20);
		break;
	case F_DAMT21:
		DP(damt21);
		break;
	case F_DAMT22:
		DP(damt22);
		break;
	case F_DAMT23:
		DP(damt23);
		break;

	case F_DAMT24:
		DP(damt24);
		break;
	case F_DAMT25:
		DP(damt25);
		break;
	case F_DAMT26:
		DP(damt26);
		break;
	case F_DAMT27:
		DP(damt27);
		break;
	case F_DAMT28:
		DP(damt28);
		break;
	case F_DAMT29:
		DP(damt29);
		break;
	case F_DAMT30:
		DP(damt30);
		break;
	case F_DAMT31:
		DP(damt31);
		break;

	case F_DAMT32:
		DP(damt32);
		break;
	case F_DAMT33:
		DP(damt33);
		break;
	case F_SSTOCK_CODE:
		CP(sstock_code);
		break;
	case F_SSTOCK_CODE2:
		CP(sstock_code2);
		break;
	case F_SCUST_TYPE:
		CP(scust_type);
		break;
	case F_SCUST_TYPE2:
		CP(scust_type2);
		break;
	case F_SSTAT_TYPE:
		CP(sstat_type);
		break;
	case F_SSTAT_TYPE2:
		CP(sstat_type2);
		break;

	case F_SROOM_NO:
		CP(sroom_no);
		break;
	case F_SROOM_NO2:
		CP(sroom_no2);
		break;
	case F_SOPEN_EMP:
		CP(sopen_emp);
		break;
	case F_SCLOSE_EMP:
		CP(sclose_emp);
		break;
	case F_SCHANGE_EMP:
		CP(schange_emp);
		break;
	case F_SCHECK_EMP:
		CP(scheck_emp);
		break;
	case F_SEMP:
		CP(semp);
		break;
	case F_SNATION_CODE:
		CP(snation_code);
		break;

	case F_LCERT_CODE:
		DP(lcert_code);
		break;
	case F_STX_PWD:
		CP(stx_pwd);
		break;
	case F_STX_PWD2:
		CP(stx_pwd2);
		break;
	case F_SWITHDRAW_PWD:
		CP(swithdraw_pwd);
		break;
	case F_SWITHDRAW_PWD2:
		CP(swithdraw_pwd2);
		break;
	case F_SEMP_PWD:
		CP(semp_pwd);
		break;
	case F_SEMP_PWD2:
		CP(semp_pwd2);
		break;
	case F_SBANK_PWD:
		CP(sbank_pwd);
		break;

	case F_SBANK_PWD2:
		CP(sbank_pwd2);
		break;
	case F_SCUST_AUTH:
		CP(scust_auth);
		break;
	case F_SCUST_AUTH2:
		CP(scust_auth2);
		break;
	case F_SCUST_LIMIT:
		CP(scust_limit);
		break;
	case F_SCUST_LIMIT2:
		CP(scust_limit2);
		break;
	case F_LSAFE_LEVEL:
		DP(lsafe_level);
		break;
	case F_LSAFE_LEVEL2:
		DP(lsafe_level2);
		break;
	case F_SPOST_CODE:
		CP(spost_code);
		break;

	case F_SPOST_CODE2:
		CP(spost_code2);
		break;
	case F_SPHONE:
		CP(sphone);
		break;
	case F_SPHONE2:
		CP(sphone2);
		break;
	case F_SPHONE3:
		CP(sphone3);
		break;
	case F_SPAGER:
		CP(spager);
		break;
	case F_SEMAIL:
		CP(semail);
		break;
	case F_SEMAIL2:
		CP(semail2);
		break;
	case F_SNOTE:
		CP(snote);
		break;

	case F_SNOTE2:
		CP(snote2);
		break;
	case F_SCERT_NO:
		CP(scert_no);
		break;
	case F_SCERT_NO2:
		CP(scert_no2);
		break;
	case F_SCERT_ADDR:
		CP(scert_addr);
		break;
	case F_SSTATUS0:
		CP(sstatus0);
		break;
	case F_SSTATUS1:
		CP(sstatus1);
		break;
	case F_SSTATUS2:
		CP(sstatus2);
		break;
	case F_SSTATUS3:
		CP(sstatus3);
		break;

	case F_SSTATUS4:
		CP(sstatus4);
		break;
	case F_LWITHDRAW_FLAG:
		DP(lwithdraw_flag);
		break;
	case F_SADDR:
		CP(saddr);
		break;
	case F_SADDR2:
		CP(saddr2);
		break;
	case F_SSERIAL0:
		CP(sserial0);
		break;
	case F_SSERIAL1:
		CP(sserial1);
		break;
	case F_SSERIAL2:
		CP(sserial2);
		break;
	case F_SSERIAL3:
		CP(sserial3);
		break;

	case F_SSERIAL4:
		CP(sserial4);
		break;
	case F_SCURRENCY_TYPE:
		CP(scurrency_type);
		break;
	case F_SCURRENCY_TYPE2:
		CP(scurrency_type2);
		break;
	case F_SBRANCH_CODE0:
		CP(sbranch_code0);
		break;
	case F_SBRANCH_CODE1:
		CP(sbranch_code1);
		break;
	case F_SBRANCH_CODE2:
		CP(sbranch_code2);
		break;
	case F_USSET0:
		CP(usset0);
		break;
	case F_USSET1:
		CP(usset1);
		break;
	case F_USSET2:
		CP(usset2);
		break;
	case F_USSET3:
		CP(usset3);
		break;
	case F_USSET4:
		CP(usset4);
		break;
	case F_USSET5:
		CP(usset5);
		break;
	case F_USSET6:
		CP(usset6);
		break;
	case F_SSTATION0:
		CP(sstation0);
		break;
	case F_SSTATION1:
		CP(sstation1);
		break;
	case F_SBANK_ACC:
		CP(sbank_acc);
		break;

	case F_SBANK_ACC2:
		CP(sbank_acc2);
		break;
	case F_LBANK_ACC_TYPE:
		DP(lbank_acc_type);
		break;
	case F_LBANK_ACC_TYPE2:
		DP(lbank_acc_type2);
		break;
	case F_SMAIN_FLAG:
		CP(smain_flag);
		break;
	case F_SMAIN_FLAG2:
		CP(smain_flag2);
		break;
	case F_SBANK_CODE:
		CP(sbank_code);
		break;
	case F_SBANK_CODE2:
		CP(sbank_code2);
		break;
	case F_SEMP_NO:
		CP(semp_no);
		break;

	case F_SEMP_NO2:
		CP(semp_no2);
		break;
	case F_DRATE0:
		DP(drate0);
		break;
	case F_DRATE1:
		DP(drate1);
		break;
	case F_LSERIAL0:
		DP(lserial0);
		break;
	case F_LSERIAL1:
		DP(lserial1);
		break;
	case F_SBANKNAME:
		CP(sbankname);
		break;
	case F_SBANKNAME2:
		CP(sbankname2);
		break;
	case F_SCARD0:
		CP(scard0);
		break;

	case F_SCARD1:
		CP(scard1);
		break;
	case F_SORDER0:
		CP(sorder0);
		break;
	case F_SORDER1:
		CP(sorder1);
		break;
	case F_SORDER2:
		CP(sorder2);
		break;
	case F_SCUSTTYPES:
		CP(scusttypes);
		break;
	case F_SSECTYPES:
		CP(ssectypes);
		break;
	case F_VSMESS:
		VP(vsmess);
		break;
	case F_VSVARSTR0:
		VP(vsvarstr0);
		break;
	case F_VSVARSTR1:
		VP(vsvarstr1);
		break;
	case F_VSVARSTR2:
		VP(vsvarstr2);
		break;

	case F_VSVARSTR3:
		VP(vsvarstr3);
		break;
	default:
		printf("encodesingleitem no this param =%d ......\n",patitionmap);

	}
#undef CP
#undef DP
#undef VP
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
