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
#include "fdsqc.h"

int F847226(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	int card_id;
	char oper_code[11] = "";
	char sysdate[9] = "";
	char systime[7] = "";
	char work_key[51] = "";
	T_t_pif_operator tOper;
	T_t_pif_oper_authcard tAuthCard;
	T_t_tif_tradeserial tSerial;
	double uni_no = 0.0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tOper,0,sizeof tOper);
	memset(&tAuthCard,0,sizeof tAuthCard);
	memset(&tSerial,0,sizeof tSerial);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SDATE2,F_SBANK_ACC,0);

	des2src(oper_code,rPack->sname2);
	if(strlen(oper_code) == 0)
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
	
	ret = DB_t_pif_operator_read_by_oper_code(oper_code,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_OPER_NOT_EXIST;
		else
			*pRetCode = E_DB_OPERATOR_R;
		goto L_RETU;
	}

	if(strcmp(OPERATOR_LOGOUT,tOper.status) == 0)
	{
		writelog(LOG_ERR,"操作员[%s]已注销",oper_code);
		*pRetCode = E_OPERLOGON_UNREG;
		goto L_RETU;
	}
	//todo:判断如果该操作员持有该卡已经发行过,那么系统允许重复发行,但是不计流水
	//todo:用于解决操作员发行卡失败后,必须回收卡才能继续处理的问题
	ret=is_already_publish_authcard(rPack->sname,oper_code,&card_id);
	if(!ret)
	{
		//writelog(LOG_ERR,"physical_no=[%s],oper_code=[%s],card_id=[%d]",rPack->sname,oper_code,card_id);
		ret = DB_t_pif_oper_authcard_read_by_card_id(card_id,&tAuthCard);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				*pRetCode = E_AUTHCARD_NOT_EXISTS;
			else
				*pRetCode = E_DB_OPER_AUTHCARD_R;
			goto L_RETU;
		}
		out_pack->lvol0 = tAuthCard.card_id;
		out_pack->lvol1 = tAuthCard.privilege;
		des2src(out_pack->sdate2,tAuthCard.expired_date);
		des2src(out_pack->scust_limit,tAuthCard.oper_code);
		des2src(out_pack->sbank_acc,work_key);
		des2src(out_pack->scust_limit2,tOper.oper_name);
		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}

	if((ret = is_oper_has_authcard(oper_code)))
	{
		if(ret == 1)
			*pRetCode = E_OPER_ALREADY_HAS_AUTHCARD;
		else
			*pRetCode = ret;
		goto L_RETU;
	}
	ret=is_physical_no_in_use(rPack->sname);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=GetParameter(GLOBE_999_DEVAUTHKEY,work_key);
	if( ret)
	{
		*pRetCode= ret;
		goto L_RETU;
	}

	ret = getNewUniqNo(KEYTYPE_CARD_ID,&uni_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	tAuthCard.card_id = D2I(uni_no);

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&uni_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tSerial.serial_no = D2I(uni_no);

	getsysdate(sysdate);
	getsystime(systime);

	des2src(tAuthCard.issue_date,sysdate);
	des2src(tAuthCard.issue_time,systime);
	des2src(tAuthCard.oper_code,oper_code);
	des2src(tAuthCard.card_phyid,rPack->sname);
	des2src(tAuthCard.expired_date,rPack->sdate2);
	tAuthCard.privilege = rPack->lvol0;
	tAuthCard.status = AUTHCARD_STATUS_NORMAL;
	// TODO : 检查物理卡号是否已经存在
	ret = DB_t_pif_oper_authcard_add(&tAuthCard);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			writelog(LOG_ERR,"授权卡交易卡号已存在[%d]",tAuthCard.card_id);
			*pRetCode = E_DB_OPER_AUTHCARD_E;
		}
		else
			*pRetCode = E_DB_OPER_AUTHCARD_I;
		goto L_RETU;
	}

	tSerial.card_id = tAuthCard.card_id;
	tSerial.serial_state = SERISTAT_NONEEDDEBT;
	tSerial.serial_type = TXCODE_ISSUE_AUTHCARD;
	des2src(tSerial.operate_date,sysdate);
	des2src(tSerial.operate_time,systime);
	des2src(tSerial.enteract_date,sysdate);
	des2src(tSerial.enteract_time,systime);
	des2src(tSerial.collect_date,sysdate);
	des2src(tSerial.collect_time,systime);
	des2src(tSerial.oper_code,rPack->scust_limit);
	ret = DB_t_tif_tradeserial_add(&tSerial);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			writelog(LOG_ERR,"记录流水表失败!");
			*pRetCode = E_DB_TRADESERIAL_E;
		}
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"发行授权卡成功，操作员[%s]交易卡号[%d]流水号[%d]"
		,tAuthCard.oper_code,tAuthCard.card_id,tSerial.serial_no);


	out_pack->lvol0 = tAuthCard.card_id;
	out_pack->lvol1 = tAuthCard.privilege;
	des2src(out_pack->sdate2,tAuthCard.expired_date);
	des2src(out_pack->scust_limit,tAuthCard.oper_code);
	des2src(out_pack->sbank_acc,work_key);
	des2src(out_pack->scust_limit2,tOper.oper_name);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;		
}

