/* --------------------------------------------
 * 程序名称: F240009.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 李珣
 * 版本信息: 1.0.0.0
 * 程序功能: 添加卡类别
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "account.h"
#include "fdsqc.h"

int ADD846001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg){
	int ret=0;	
	double dUniqNo=0;
	//int testno=rPack->lcert_code;
	T_t_pif_cardtype tcardtype;
	
	char type_name[200]="";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	trim(rPack->vsvarstr0);
	
	if(strlen(rPack->vsvarstr0)==0)
	{
			*pRetCode=E_INPUT_TYPENAME_NULL;
			goto L_RETU;
	}
	if(strlen(rPack->vsvarstr0)>20)
	{
			*pRetCode=E_INPUT_TYPENAME_TOOLONG;
			goto L_RETU;
	}
	
	des2src(type_name,rPack->vsvarstr0);
	trim(type_name);
	memset(&tcardtype,0,sizeof(tcardtype));
	ret=DB_t_pif_cardtype_read_by_type_name(type_name,&tcardtype);
	
	if(ret)
	{
			if(DB_NOTFOUND==ret)
			{
				*pRetCode=ret;
				goto L_RETU;	
			}
	}
	
	
	ResetNormalCPack(&aPack,0,1);
	
	
	memset(&tcardtype,0,sizeof(tcardtype));
	
	ret = getNewUniqNo(KEYTYPE_CARD_TYPE,&dUniqNo);
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	
	tcardtype.type_id=D2I(dUniqNo);
	des2src(tcardtype.type_name,type_name);
	tcardtype.type_code=rPack->lvol0;
	ret=DB_t_pif_cardtype_add(&tcardtype);
	if(ret)
	{
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_CARDTYPE_E;
		else
			*pRetCode = E_DB_CARDTYPE_I;
		goto L_RETU;
	}
	
	SetCol(handle,0);
 	SetCol(handle,F_VSVARSTR1,0);
 	
 	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

int Delete846001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{



}

int Update846001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	

}

int F846001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	
	switch(rPack->sstatus0[0])
	{
		case 'A':
			ret=ADD846001(handle,iRequest,rPack,pRetCode,szMsg);
			break;
		default:
			*pRetCode=E_INPUT_DATA_INVAILD;
			goto L_RETU;
	}

	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	
	
	
	
	return 0;	

L_RETU:
		return -1;

}
