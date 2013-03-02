/* --------------------------------------------
 * 程序名称: F847226
 * 创建日期: 2007-01-19
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员授权卡发行
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "dbfunc_foo.h"
#include "busqc.h"
#include "acctrans.h"

int F847226(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	int cardno;
	char opercode[11] = "";
	char sysdate[9] = "";
	char systime[7] = "";
	char work_key[51] = "";
	char cardphyid[21]="";
	T_t_operator tOper;
	T_t_authcard tAuthCard;
		
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tOper,0,sizeof tOper);
	memset(&tAuthCard,0,sizeof tAuthCard);
	//memset(&tSerial,0,sizeof tSerial);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SDATE2,F_SBANK_ACC,0);

	des2src(opercode,rPack->sname2);
	des2src(cardphyid,rPack->sname);
	if(strlen(opercode) == 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}

	if(strlen(rPack->scust_limit) == 0)
	{
		*pRetCode = E_INPUT_OPER_NULL;
		goto L_RETU;
	}

	
	if((ret = IsInvalidDateTime(rPack->sdate2,"YYYYMMDD")))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	
	ret = DB_t_operator_read_by_opercode(opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_OPER_NOT_EXIST;
		else
			return E_DB_OPERATOR_R;
	}
	if(tOper.status[0]=='0')
		return E_OPER_LOCK;
	
	if(tOper.status[0]== '2')
		return E_OPERLOGON_UNREG;

	//todo:判断如果该操作员持有该卡已经发行过,那么系统允许重复发行,但是不计流水
	//todo:用于解决操作员发行卡失败后,必须回收卡才能继续处理的问题
	ret=DB_t_authcard_read_by_opercode_and_status(opercode,"1",&tAuthCard);
	if(ret!=DB_NOTFOUND)
	{
		if(ret)
			return E_DB_AUTHCARD_R;
		//记录存在
		if(tAuthCard.cardstatus[CARDSTAT_TYPE_LOST]=='1')
		{
			//修改原来卡为注销状态
			tAuthCard.status[0]==STATUS_LOGOUT;
			des2src(tAuthCard.closedate,sysdate);
			ret=DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
			if(ret)
			{
				return E_DB_AUTHCARD_U;
			}
		}
		//return E_OPER_ALREADY_HAS_AUTHCARD;
		if(strcmp(cardphyid,tAuthCard.cardphyid)==0)
		{
			out_pack->lvol0 = tAuthCard.cardno;
			out_pack->lvol1 = tAuthCard.privilege;
			des2src(out_pack->sdate2,tAuthCard.expiredate);
			des2src(out_pack->scust_limit,tAuthCard.opercode);
			des2src(out_pack->sbank_acc,work_key);
			des2src(out_pack->scust_limit2,tOper.opername);
			PutRow(handle,out_pack,pRetCode,szMsg);
		}
		return 0;
	}
	ret=GetParameter(GLOBE_999_DEVAUTHKEY,work_key);
	if( ret)
	{
		*pRetCode= ret;
		goto L_RETU;
	}

	ret = getNewUniqNo(KEYTYPE_CARDNO,&cardno);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	tAuthCard.cardno = cardno;

	getsysdate(sysdate);
	getsystime(systime);

	des2src(tAuthCard.opendate,sysdate);
	des2src(tAuthCard.effectdate,sysdate);
	des2src(tAuthCard.opercode,opercode);
	des2src(tAuthCard.cardphyid,cardphyid);
	des2src(tAuthCard.expiredate,rPack->sdate2);
	tAuthCard.privilege = rPack->lvol0;
	memset(tAuthCard.cardstatus,'0',10);
	tAuthCard.status[0]=STATUS_NORMAL;
	// TODO : 检查物理卡号是否已经存在
	ret = DB_t_authcard_add(&tAuthCard);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_AUTHCARD_E;
		else
			return E_DB_AUTHCARD_I;
	}
	out_pack->lvol0 = tAuthCard.cardno;
	out_pack->lvol1 = tAuthCard.privilege;
	des2src(out_pack->sdate2,tAuthCard.expiredate);
	des2src(out_pack->scust_limit,tAuthCard.opercode);
	des2src(out_pack->sbank_acc,work_key);
	des2src(out_pack->scust_limit2,tOper.opername);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;		
}

