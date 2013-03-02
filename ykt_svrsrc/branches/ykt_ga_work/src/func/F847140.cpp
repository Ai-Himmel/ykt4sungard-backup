/* --------------------------------------------
 * 修改日期: 2009-11-17
 * 修改者  : 王彦兵
 * 程序功能: 回收服务费 (提前结束培训)
 * --------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "mypub.h"
#include "pubfunc.h"
#include "account.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "svrlink.h"

int F847140(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	    int hi_cardid = 0;             //交易卡号
	    int hi_day = 0;					// 提前的天数
	    int hi_card_cnt = 0;
	    double hi_card_bala = 0;			// 卡余额
	    double service_fee = 0;		//每天的服务费金额
	    char   fee_buf[20]="";
	double dUniqNo = 0;                              //最大流水号
	char sysdate[11] = "";
    	char systime[7] = "";
	char logicdate[11] = "";
	
    	T_t_pif_card tCard;
	T_t_aif_account tAccount;
	T_t_tif_tradeserial tSerial;
	T_t_cif_customer tCustomer;
	InAcc IAE;
	T_t_cif_cut_svrfee tCutsvrfee;

	memset(&tSerial, 0, sizeof(tSerial));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCustomer, 0, sizeof(tCustomer));
	memset(&IAE, 0, sizeof(IAE));
	memset(&tCutsvrfee,0,sizeof tCutsvrfee);


    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack, 0, sizeof(aPack));
	    
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL1,F_VSMESS,F_LSERIAL1,0);

	hi_card_bala = rPack->lvol3/100.0;		
	hi_card_cnt = rPack->lvol2;
//	hi_day = rPack->lvol0;
    	hi_cardid = rPack->lvol1;
	service_fee = rPack->damt0;			//atof(fee_buf)*hi_day;		// 前台直接输入金额

	if(amtcmp(service_fee, 0)<=0)
		return E_INPUT_ERROR;
    if (hi_cardid <= 0)
       return E_INPUT_CARDNO;
    
    ret = DB_t_pif_card_read_by_card_id(hi_cardid,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		   return E_DB_CARD_N;		
		return E_DB_CARD_R;
	}
	
    if (strncmp(tCard.state_id, TYPE_YES, 1) != 0)
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        return E_CARDNO_LOGOUT;
    }

    if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_FREEZE])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
       	return E_CARDNO_FREEZE;
    }

	 if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_WFAIL])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
       	return E_CARDNO_WFAIL;
    }

	ret = DB_t_aif_account_read_by_card_id_and_purse_id(hi_cardid,PURSE_NO_ONE, &tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}

	/*
	if (ret = GetParameter(GLOBAL_SERVICE_FEE, fee_buf))
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	*/
	
	if(amtcmp(service_fee, tAccount.cur_freebala)>0)
	   		return E_SVR_FEE_SHORT;
	
	if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_LOST])			// 挂失卡
    {
    	hi_card_cnt = tAccount.consume_count;
		hi_card_bala = tAccount.cur_freebala;
		IAE.iUseCardFlag = USE_CARD_TYPE_NULL;            
	}
	else
	{
		if( hi_card_cnt <0)
	   		return E_INPUT_CARD_TXCNT;
		if(amtcmp(tAccount.cur_freebala,hi_card_bala)>0			// 库比卡大
   			&& amtcmp(service_fee, hi_card_bala)>0)
   			return E_SVR_FEE_SHORT;
		 IAE.iUseCardFlag = USE_CARD_TYPE_ONLINE;            //联机交易
	}

	ret = DB_t_cif_customer_read_by_cut_id(tCard.cosumer_id,&tCustomer);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            ret = E_DB_CUSTOMER_N;
        }
        else
        {
            ret = E_DB_CUSTOMER_R;
        }
        return ret;
    }

    ret = getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqNo);              // 获得最大流水号
    if (ret)
    {
        writelog(LOG_ERR,"get_new_uniq_no[%d]",ret);
        return ret;
    }

    getsysdate(sysdate);
    getsystime(systime);
    GetLogicDate(logicdate);
    tSerial.serial_no = D2I(dUniqNo);
    tSerial.other_seri_no = 0;
    tSerial.serial_state = SERISTAT_DEBT;                           //流水状态
    tSerial.serial_type = TXCODE_RECLAIM_SVR_FEE;              		//交易类型
    des2src(tSerial.operate_date,sysdate);                           //发生日期
    des2src(tSerial.operate_time,systime);                           //发生时间
    des2src(tSerial.collect_date,sysdate);                           //采集日期
    des2src(tSerial.collect_time,systime);                           //采集时间
    des2src(tSerial.enteract_date,logicdate);                        //处理日期
    des2src(tSerial.enteract_time,systime);                          //处理时间

  	tSerial.maindevice_id = rPack->lvol6;                            
    tSerial.device_id = rPack->lvol7;                               //采集设备标识 
    tSerial.card_id = hi_cardid;                                 	//交易卡号
    des2src(tSerial.showid,tCard.showid);                            	//显示卡号
    tSerial.purse_id = PURSE_NO_ONE;                                //钱包号
    tSerial.customer_id = tCard.cosumer_id;                         	//客户号
    des2src(tSerial.oper_code, rPack->semp);                      //操作员代码
    tSerial.sys_id = 0;
    tSerial.trade_fee = service_fee;                             		//转钱金额
    tSerial.in_balance = hi_card_bala;                                	//钱包入卡值
	tSerial.trade_count=hi_card_cnt+1;									//交易次数
	tSerial.out_balance = tSerial.in_balance - service_fee ;            //出卡值  
	
  //des2src(IAE.sArrInActno[1],account.account_id);                  	//商户帐户
  	des2src(IAE.sArrInActno[0],tAccount.account_id);					//借方帐号(个人)

    IAE.dArrInAmt[0] = tSerial.trade_fee;                            //交易金额
    IAE.iCardNo = tSerial.card_id;                                     	//交易卡号
    IAE.iFeeType = tCustomer.fee_type;                               //客户收费类型
	IAE.iMainDevId = tSerial.maindevice_id;                  				//工作站标示
    IAE.iDevId = tSerial.device_id;                     //设备ID号
    IAE.iSerialNo = tSerial.serial_no;                  //流水号
    IAE.iTradeNo = tSerial.serial_type;                 //交易代码 
    strcpy(IAE.sTxDate, tSerial.operate_date);               //交易日期
    strcpy(IAE.sTxTime, tSerial.operate_time);               //交易时间
    strcpy(IAE.sTxCollectDate, tSerial.collect_date);        //采集日期
    strcpy(IAE.sTxCollectTime, tSerial.collect_time);        //采集时间
    strcpy(IAE.sTxAccDate, tSerial.enteract_date);           //记帐日期
    strcpy(IAE.sTxAccTime, tSerial.enteract_time);           //记帐时间

    IAE.iTxCnt = tSerial.trade_count;                        //交易次数
    IAE.dInCardBala = tSerial.in_balance;                    //入卡值
    IAE.dOutCardBala = -1;                              //出卡值
    des2src(IAE.sMdeOper, tSerial.oper_code);                 //操作员号

    // 修改借方和贷方的帐户余额, 记会计分录入帐
    ret = AccountProcess(&IAE);
    if (ret)
    {
        writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
        return ret;
    }
    
 	sprintf(out_pack->vsmess,"回收服务费流水号:%d 卡号:%d,回收金额:%.2lf,出卡值:%.2lf ",IAE.iSerialNo,IAE.iCardNo,tSerial.trade_fee,tSerial.out_balance);

	writelog(LOG_DEBUG,out_pack->vsmess);

	//插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tSerial);
	if (ret)
	{
	    writelog(LOG_ERR,"ret[%d]",ret);  
		if (DB_REPEAT == ret)
	 		return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}

	ret = DB_t_cif_cut_svrfee_read_by_cut_id(tCard.cosumer_id,&tCutsvrfee);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{			
			tCutsvrfee.cut_id = tCard.cosumer_id;
			tCutsvrfee.svrfee_draw = service_fee;				// 回收服务费
			des2src(tCutsvrfee.close_date,sysdate);
			ret = DB_t_cif_cut_svrfee_add(&tCutsvrfee);
			if(ret)
				return E_DB_CUT_SVRFEE_I;
		}
		else
			return E_DB_CUT_SVRFEE_R;
	}
	else
	{
		tCutsvrfee.svrfee_draw += service_fee;				// 回收服务费
		des2src(tCutsvrfee.close_date,sysdate);
		ret = DB_t_cif_cut_svrfee_update_by_cut_id(tCard.cosumer_id,&tCutsvrfee);
		if(ret)
			return E_DB_CUT_SVRFEE_U;
	}

	out_pack->lvol1= D2I(tSerial.out_balance*100);
	out_pack->lserial1 = tSerial.serial_no;

	PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
	return -1;	
}

