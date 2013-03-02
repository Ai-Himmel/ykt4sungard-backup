/* --------------------------------------------
 * 程序名称: F847121.c
 * 创建日期: 2005-05-26
 * 程序作者: 闻剑
 * 版本信息:
 * 程序功能:更新卡信息
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F847121(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double dSerialno=0;
	int card_id=0;
	T_t_pif_card tCard;
	T_t_tif_tradeserial tTradeserial;

	memset(&tCard,0,sizeof(tCard));
	memset(&tTradeserial,0,sizeof(tTradeserial));

	card_id=rPack->lvol0;
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	if(rPack->lvol2!=IS_NO)
	{
		if(strlen(rPack->scust_limit)==0)
		{
			*pRetCode=E_OPER_NOT_EXIST;
			goto L_RETU;
		}
		if(strlen(rPack->scust_limit2)==0)
		{
			*pRetCode=E_INPUT_AUTH_OPER_NULL;
			goto L_RETU;
		}
		if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
		{
			writelog(LOG_ERR,"oper[%s]auth_oper[%s]",rPack->scust_limit,rPack->scust_limit2);
			*pRetCode=E_OPER_AND_AUTH_OPER_EQ;
			goto L_RETU;
		}
		ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
		if(ret)
		{
			if(E_OPER_NOT_EXIST==ret)
				*pRetCode=E_AUTH_OPER_NOT_EXIST;
			else if(E_PASSWORD_WRONG==ret)
				*pRetCode=E_AUTH_OPER_PWD;
			else
				*pRetCode=ret;
			goto L_RETU;
		}
	}
	trim(rPack->scust_no);
	ret=IsInvalidDateTime(rPack->sdate0, "YYYYMMDD");
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//判断卡状态是否为写卡未成功状态
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARD_CHANGE;
		goto L_RETU;
	}
	trim(rPack->scust_no);
	if(strlen(rPack->scust_no)!=0)
	{
		if(strcmp(tCard.showid,rPack->scust_no)!=0)
		{
			ret=IsExistShowCardNo(rPack->scust_no);
			if(ret)
			{
				DB_t_pif_card_free_lock_by_cur();
				writelog(LOG_ERR,"showcardno[%s]",rPack->scust_no);
				*pRetCode=ret;
				goto L_RETU;
			}
		}
	}
	trim(rPack->sbank_acc);
	if(strcmp(tCard.physical_no,rPack->sbank_acc)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,rPack->sbank_acc);
		*pRetCode= E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}
	des2src(tCard.showid,rPack->scust_no);
	des2src(tCard.end_time,rPack->sdate0);

	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);  				//获得流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	tTradeserial.serial_no = (int)dSerialno;											//流水号
	tTradeserial.other_seri_no = 0;												//上传端流水号
	tTradeserial.serial_type = 847121;												//交易代码；备注：发卡+充值 用一个交易码，即847101； 发卡（不充值）另用一个交易码，即新的发卡程序文件名，从而区分发卡充值与发卡不充值的卡操作信息。
	tTradeserial.serial_state = SERISTAT_DEBT;										//流水状态
	des2src(tTradeserial.operate_date,sysdate);									//发生日期
	des2src(tTradeserial.operate_time,systime);									//发生时间
	des2src(tTradeserial.collect_date,sysdate);										//采集日期
	des2src(tTradeserial.collect_time,systime);										//采集时间
	des2src(tTradeserial.enteract_date,logicdate);									//处理日期
	des2src(tTradeserial.enteract_time,systime);									//处理时间
	des2src(tTradeserial.oper_code , rPack->scust_limit);
	tTradeserial.maindevice_id = rPack->lvol6;										//上传工作站标识
	tTradeserial.device_id = rPack->lvol7;											//采集设备标识
	tTradeserial.card_id = tCard.card_id;											//卡号
	des2src(tTradeserial.showid,tCard.showid);										//显示卡号
	tTradeserial.purse_id = PURSE_NO_ONE;										//钱包号
	tTradeserial.customer_id = tCard.cosumer_id;									//客户标识
//	tTradeserial.reviseserial_no=dSerialno;											//原写卡失败流水号
	des2src(tTradeserial.reserve_1,rPack->scust_limit2);							//授权操作员号
	des2src(tTradeserial.reserve_2,rPack->semp_pwd);								//授权操作员密码
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tTradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
