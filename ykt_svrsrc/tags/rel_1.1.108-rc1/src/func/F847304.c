/* --------------------------------------------
 * 程序名称: F847304.c
 * 创建日期: 2006-12-20
 * 程序作者: 李翔
 * 版本信息: 1.0.0.0
 * 程序功能: 
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

int F847304(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
/*
    int ret=0;
	T_t_pif_card tCard;
	T_t_tif_tradeserial tTradeSerial;
	T_t_tif_tradeserial tNewSerial;
	T_t_tif_writefailed tWriteFailed;
	T_t_tif_tradeserial_his tTradeSerialHis;
	
	char logicdate[11] = "";
	char operdate[11] = "";
	char sysdate[9] = "";
	char systime[7] = "";
	char deal_flag[1 + 1] = "";
//	char buf[64];
	int serial_no = 0;
//	int write_card_failed_flag = 1;                       //0表示写卡未失败, 1表示写卡失败
	double dSerialno = 0;
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);

	memset(&tTradeSerial,0,sizeof tTradeSerial);
	memset(&tNewSerial,0,sizeof tNewSerial);
	memset(&tCard,0,sizeof tCard);
	memset(&tWriteFailed, 0, sizeof tWriteFailed);
	memset(&tTradeSerialHis, 0, sizeof tTradeSerialHis);
	GetLogicDate(logicdate);
	getsysdate(sysdate);
	getsystime(systime);
    deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
	ret = DB_t_pif_card_read_by_card_id(in_pack->lvol0,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_CARD_N;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}
    //补写小钱包
	ret = DB_t_tif_writefailed_read_lock_by_c1_and_card_id_and_purese_no_and_deal_flag(tCard.card_id,PURSE_NO_TWO,&deal_flag[0],&tWriteFailed);  // 直接判断有写卡失败标记的记录
	if (ret)
	{
        if (DB_NOTFOUND == ret)
        {
//            *pRetCode = E_DB_WRITEFAILED_N;     
            *pRetCode = E_WRITEFAILED_DEAL_FLAG_N;      // 没有查到就是已经写过的
        }
        else
        {
            *pRetCode = E_DB_WRITEFAILED_R;  
        }
        goto L_RETU;
    }
    //小钱包写卡失败,做补写业务
    serial_no = tWriteFailed.serial_no;
    tNewSerial.in_balance = in_pack->damt1;
    des2src(operdate,tWriteFailed.tx_date);
    if (strncmp(logicdate,operdate,8) == 0)
    {
	    //充值流水
	    ret = DB_t_tif_tradeserial_read_by_serial_no(serial_no,&tTradeSerial);
	    if(ret)
	    {
		    writelog(LOG_ERR,"serial no[%d] read error! ",serial_no);
		    if(DB_NOTFOUND == ret)
			    *pRetCode = E_SERIALNO_NOT_EXIST;
		    else 
			    *pRetCode = E_DB_TRADESERIAL_R;
		    DB_t_tif_writefailed_free_lock_by_c1();
		    goto L_RETU;
	    }
	    //再次判断是否交易卡号正确
	    if(tTradeSerial.card_id != in_pack->lvol0)
	    {
		    writelog(LOG_ERR,"card no[%d] not exists",in_pack->lvol0);
		    *pRetCode = E_CARDNO_NOT_EXIST;
		    DB_t_tif_writefailed_free_lock_by_c1();
		    goto L_RETU;
	    }
	    tNewSerial.trade_fee = tTradeSerial.trade_fee;
    }
    else 
    {
	    //查询当天结算的历史记录
	    ret = DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(operdate, serial_no, &tTradeSerialHis);
	    if (ret)
	    {
		    writelog(LOG_ERR,"serial no[%d] read error",serial_no);
		    if(DB_NOTFOUND == ret)
			    *pRetCode = E_SERIALNO_NOT_EXIST;
		    else
			    *pRetCode = E_DB_TRADESERIAL_R;
		    DB_t_tif_writefailed_free_lock_by_c1();
		    goto L_RETU;
	    }
	    if (tTradeSerialHis.card_id != in_pack->lvol0 )
	    {
		    writelog(LOG_ERR,"card no[%d] not exists",in_pack->lvol0);
		    *pRetCode = E_CARDNO_NOT_EXIST;
		    DB_t_tif_writefailed_free_lock_by_c1();
		    goto L_RETU;
	    }
	    tNewSerial.trade_fee = tTradeSerialHis.trade_fee;
    }
    ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);
    if(ret)
    {
	    *pRetCode = ret;
	    DB_t_tif_writefailed_free_lock_by_c1();
	    goto L_RETU;
    }
    //添加补写卡流水(小钱包)
    tNewSerial.serial_no = D2I(dSerialno);
    tNewSerial.card_id = in_pack->lvol0;
    tNewSerial.serial_type = TXCODE_REWRITE_SMALL_PACKET;
    tNewSerial.serial_state = SERISTAT_NONEEDDEBT;
    tNewSerial.other_seri_no = 0;
    tNewSerial.purse_id = PURSE_NO_TWO;
    tNewSerial.maindevice_id = in_pack->lvol1;
    tNewSerial.device_id = in_pack->lvol1;
    des2src(tNewSerial.showid,tCard.showid);
    tNewSerial.customer_id = tCard.cosumer_id;
    tNewSerial.reviseserial_no = D2I(dSerialno);

    des2src(tNewSerial.oper_code,in_pack->scust_no);
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
	    DB_t_tif_writefailed_free_lock_by_c1();
	    goto L_RETU;
    }

    tWriteFailed.deal_serial_no = tNewSerial.serial_no;
    des2src(tWriteFailed.deal_date,sysdate);
    des2src(tWriteFailed.deal_time,systime);
    tWriteFailed.deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_N;
    des2src(tWriteFailed.comments, "小钱包补写卡成功");
    ret = DB_t_tif_writefailed_update_lock_by_c1(&tWriteFailed);
    if (ret)
    {
	    if (DB_NOTFOUND == ret)
	    {
		    *pRetCode = E_DB_WRITEFAILED_N;
	    }
	    else
	    {
		    *pRetCode = E_DB_WRITEFAILED_U;    
	    }
	    goto L_RETU;
    }
	DB_t_tif_writefailed_free_lock_by_c1();
	ResetNormalCPack(&aPack, 0, 1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,0);
	out_pack->lvol0 = tCard.card_id;
	out_pack->lvol1 = tNewSerial.out_balance;
	out_pack->lvol2 = tNewSerial.serial_no;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
	*/
	return 0;
}
