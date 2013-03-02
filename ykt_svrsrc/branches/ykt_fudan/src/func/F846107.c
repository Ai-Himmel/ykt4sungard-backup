/* --------------------------------------------
 * 创建日期: 2008-12-5
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 坏卡登记
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "fdsqc.h"

int F846107(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	double seqno = 0;

	char sShowcardno[11] ="";

	T_t_pif_carddtl carddtl;
	T_t_pif_cardbook cardbook;
/*
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
*/	
	des2src(sShowcardno,rPack->scust_no);
	memset(&cardbook,0,sizeof(cardbook));
	memset(&carddtl,0,sizeof(carddtl));

	getsysdate(carddtl.accdate);
	getsystime(carddtl.acctime);
	carddtl.termid=0;												//上传工作站标识
	
	ret = getNewUniqNo(KEYTYPE_T_PIF_CARDDTL,&seqno);						//获取流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo[KEYTYPE_T_PIF_CARDDTL] ");
		return ret;
	}
	carddtl.termseqno = D2I(seqno);
	
	carddtl.cardtype=GetTypeFromShowNo(sShowcardno);
	carddtl.usetype[0]=CARDUSETYPE_BAD;
	
	carddtl.transcnt= 1;
	strcpy(carddtl.summary,"坏卡登记");
	des2src(carddtl.showcardno,sShowcardno);

	des2src(carddtl.opercode,rPack->sorder1);
	
	writelog(LOG_ERR,"opcode[%s],showcardno[%s],seqno[%d]",carddtl.opercode,sShowcardno,carddtl.termseqno);
	ret=DB_t_pif_carddtl_add(&carddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}	
/*
   	ret = DB_t_pif_cardbook_read_by_showcardno(sShowcardno, &cardbook);
	if(ret)
	{
		if(ret == DB_NOTFOUND)
			goto L_RET;
		return E_DB_CARDBOOK_R;
	}

	if(cardbook.usestatus[0] == '1')
		return E_CARDUSESTATUS_UNUSED;
	if(cardbook.usestatus[0] == '3')
		return E_CARDUSESTATUS_DISABLE;
	
	cardbook.usestatus[0] = '4';
	des2src(cardbook.opercode,rPack->sorder1);
	ret = DB_t_pif_cardbook_update_by_showcardno(sShowcardno, &cardbook);
	if(ret)
		return E_DB_CARDBOOK_U;
		
L_RET:	
*/

//	sprintf(outPack->vsmess,"坏卡登记成功");
//	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
