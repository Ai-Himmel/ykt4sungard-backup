/* --------------------------------------------
 * 程序名称: F849009.c
 * 创建日期: 2006-7-31
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 补写水控钱包
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
#include "fdsqc.h"

int F849009(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	T_t_pif_card tCard;
	T_t_tif_tradeserial tTradeSerial;
	T_t_tif_tradeserial_his tTradeSerialHis;
	T_t_tif_tradeserial tNewSerial;
	char logicdate[11] = "";
	char operdate[11] = "";
	char sysdate[9] = "";
	char systime[7] = "";
	char buf[64];
	int serial_no;
	double dSerialno;
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);

	memset(&tTradeSerial,0,sizeof tTradeSerial);
	memset(&tTradeSerialHis,0,sizeof tTradeSerialHis);
	memset(&tNewSerial,0,sizeof tNewSerial);
	memset(&tCard,0,sizeof tCard);
	GetLogicDate(logicdate);
	getsysdate(sysdate);
	getsystime(systime);

	ret = DB_t_pif_card_read_by_card_id(in_pack->lvol0,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_CARD_N;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}

	if(tCard.is_managefee[0] != CARDWFAIL_WATER)
	{
		*pRetCode = E_CARDSTATE_NOTWRITEFAIL;
		goto L_RETU;
	}

	ret = GetXmlValue(operdate,sizeof operdate,XML_KEY_OPERATEDATE2,tCard.comments);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	
	ret = GetXmlValue(buf,sizeof buf,XML_KEY_SERIALNO2,tCard.comments);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	serial_no = atoi(buf);
	tNewSerial.in_balance = in_pack->lvol3;
	if(strncmp(logicdate,operdate,8) == 0)
	{
		// 当前记录
		ret = DB_t_tif_tradeserial_read_by_serial_no(serial_no,&tTradeSerial);
		if(ret)
		{
			writelog(LOG_ERR,"serial no[%d] read error! ",serial_no);
			if(DB_NOTFOUND == ret)
				*pRetCode = E_SERIALNO_NOT_EXIST;
			else 
				*pRetCode = E_DB_TRADESERIAL_R;
			goto L_RETU;
		}

		if(tTradeSerial.card_id != in_pack->lvol0)
		{
			*pRetCode = E_CARDNO_NOT_EXIST;
			goto L_RETU;
		}

		tNewSerial.trade_fee = tTradeSerial.trade_fee;
		
	}
	else
	{
		//历史记录
		ret = DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(operdate,serial_no,&tTradeSerialHis);
		if(ret)
		{
			writelog(LOG_ERR,"serial no[%d] read error",serial_no);
			if(DB_NOTFOUND == ret)
				*pRetCode = E_SERIALNO_NOT_EXIST;
			else
				*pRetCode = E_DB_TRADESERIAL_R;
			goto L_RETU;
		}
		if(tTradeSerialHis.card_id != in_pack->lvol0 )
		{
			writelog(LOG_ERR,"card no[%d] not exists",in_pack->lvol0);
			*pRetCode = E_CARDNO_NOT_EXIST;
			goto L_RETU;
		}
		
		tNewSerial.trade_fee = tTradeSerialHis.trade_fee;
		
	}

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	tNewSerial.serial_no = D2I(dSerialno);
	tNewSerial.card_id = in_pack->lvol0;
	tNewSerial.serial_type = TXCODE_WATER_REWRITE_CARD;
	tNewSerial.serial_state = SERISTAT_DEBT;
	tNewSerial.other_seri_no = 0;
	tNewSerial.purse_id = PURSE_NO_FOUR;
	tNewSerial.maindevice_id = in_pack->lvol1;
	tNewSerial.device_id = in_pack->lvol1;
	des2src(tNewSerial.showid,tCard.showid);
	tNewSerial.customer_id = tCard.cosumer_id;
	tNewSerial.reviseserial_no = D2I(dSerialno);
	
	des2src(tNewSerial.oper_code,in_pack->scust_limit);
	tNewSerial.out_balance = tNewSerial.in_balance + tNewSerial.trade_fee;
	des2src(tNewSerial.operate_date,sysdate);
	des2src(tNewSerial.operate_time,systime);
	des2src(tNewSerial.collect_date,sysdate);
	des2src(tNewSerial.collect_time,systime);
	des2src(tNewSerial.enteract_date,sysdate);
	des2src(tNewSerial.enteract_time,systime);
	
	ret = DB_t_tif_tradeserial_add(&tNewSerial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,0);
	out_pack->lvol0 = tCard.card_id;
	out_pack->lvol1 = tNewSerial.out_balance;
	out_pack->lvol2 = tNewSerial.serial_no;
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
L_RETU:
	return -1;
}

