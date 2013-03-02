/* --------------------------------------------
 * 程序名称: F847309.cpp
 * 创建日期: 2007-10-15
 * 程序作者: 李翔
 * 版本信息: 1.0.0.0
 * 程序功能: 水控钱包回转
 * --------------------------------------------
 * 修改日期: 2009-11-13
 * 修改者  : 王彦兵
 * 程序功能: 水控退款退到个人账户
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


#define SYNJONES_PACKET '2'

extern CSvrLink g_SvrLink;
static int SetHeadCol(ST_CPACK *in_cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, in_cpack);
	while ((arg = va_arg(ap, int)) >= 0)
	{
		SetParmBit(&(in_cpack->head), arg);
	}
	va_end(ap);
    return(g_SvrLink.SetCol(0, in_cpack->head.ParmBits));
}

static int CallThirdPart(ST_PACK *in_pack, ST_PACK *out_pack,int funcno)
{
	int ret = 0;
	int time_out = 5;
//	char port[6] = "";
	char drtp_branch[6] = "";
	char bcc_basefunc_no[6] = "";

	/*
	if (ret = GetParameter(3001, port))
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	*/
	if (ret = GetParameter(2401, drtp_branch))
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	
	if (ret = GetParameter(2402, bcc_basefunc_no))
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	
	ST_CPACK aPack; 			// 设置应答包
	ST_CPACK sPack; 			// 设置发送包
	ST_PACK ArrayPack;		// 设置返回的后续包

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES, F_LVOL0, F_LVOL1, F_LVOL2, F_SCUST_AUTH, 0);       
	sPack.head.RequestType = funcno;

	memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	writelog(LOG_INFO,"cut_id=[%d],money=[%d],transfer_type=[%d]",sPack.pack.lvol0,sPack.pack.lvol1,sPack.pack.lvol2);

	ret = ExtCall(0, atoi(drtp_branch), atoi(bcc_basefunc_no), 0, time_out, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 847309 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 847309 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}

	memcpy(out_pack, &(aPack.pack), sizeof(aPack.pack));
	return 0;
}

static int ProcessExtAcc(ST_PACK *in_pack, ST_PACK *out_pack)
{
	int ret = 0;
	double dUniqNo = 0;                              //最大流水号
	char sysdate[11] = "";
    char systime[7] = "";
	char logicdate[11] = "";
	int TxTypeCount = 0;
	char msg[256] = "";
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	
	T_t_tif_tradeserial tSerial;
	T_t_pif_card		tCard;
	T_t_cif_customer tCustomer;
	T_t_tradecode_shop tradeshop;
	T_t_cif_shop		shop;			//商户信息表
	T_t_aif_account	account;		//帐户表
	T_t_aif_account accperson;		//个人账户
	InAcc IAE;

	memset(&tSerial, 0, sizeof(tSerial));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tCustomer, 0, sizeof(tCustomer));
	memset(&IAE, 0, sizeof(IAE));
	memset(&tradeshop, 0, sizeof(tradeshop));
	memset(&shop, 0, sizeof(shop));
	memset(&account, 0, sizeof(account));
	memset(&accperson,0,sizeof(accperson));

	ret = DB_t_pif_card_read_by_card_id(in_pack->lvol1, &tCard);
	if (ret)
	{
		if(DB_NOTFOUND == ret)
		{
		    ret = E_DB_CARD_N;
		}
		else
		{
		    ret = E_DB_CARD_R;
	    }
	    return ret;
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

  	ret=DB_t_aif_account_read_by_card_id_and_purse_id(in_pack->lvol1, PURSE_NO_ONE,&accperson);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,in_pack->lvol1);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}

	if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_LOST])			// 挂失卡
	{
		in_pack->lvol3 = D2I(accperson.cur_freebala*100);
		in_pack->lvol10 = accperson.consume_count;
		IAE.iUseCardFlag = USE_CARD_TYPE_NULL;            
	}
	else
	{
		if(amtcmp(in_pack->lvol3,0)<0)		// 卡片余额
  			return E_INPUT_CARD_BALA;

		if(in_pack->lvol10<0)					// 卡片交易次数
			return E_INPUT_CARD_TXCNT;

		IAE.iUseCardFlag = USE_CARD_TYPE_ONLINE;            //联机交易
	}

	tSerial.trade_fee = in_pack->lvol0/100.0;                             		//转钱金额
    tSerial.in_balance = in_pack->lvol3/100.0;                                	//钱包入卡值
    
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
		return ret;
	
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(accperson.cur_bala+tSerial.trade_fee,dMaxCardBalance)>0)
		return  E_AMT_EXCEED_MAX;

	
    ret = getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqNo);              // 获得最大流水号
    if (ret)
    {
        writelog(LOG_ERR,"get_new_uniq_no[%d]",ret);
        return ret;
    }

	ret = DB_t_tradecode_shop_open_select_by_c0_and_trade_code(TXCODE_REFUND_WATER_ACCOUNT);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tradecode_shop_open_select_by_c0_and_trade_code error,errcode=[%d]",ret);
		return ret;
	}

	ret = DB_t_tradecode_shop_fetch_select_by_c0(&tradeshop);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tradecode_shop_fetch_select_by_c0 error errorcode=[%d]",ret);
		DB_t_tradecode_shop_close_select_by_c0();
		return E_SHP_ID_NOT_EXIST;
	}
	DB_t_tradecode_shop_close_select_by_c0();

	ret = DB_t_cif_shop_read_by_shop_id(tradeshop.shop_id, &shop);
	if (ret)
	{
		writelog(LOG_ERR,"read tablet_cif_shop  shpid[%d]",tradeshop.shop_id);
		if(DB_NOTFOUND == ret)
		{
			return E_SHP_ID_NOT_EXIST;
		}
		else
			return E_DB_CARD_R;
	}

	//根据客户号和商户主账号类型查询账号表，得到账号
	ret = DB_t_aif_account_read_by_customer_id_and_act_type(shop.cut_id,ACCTYPE_SHOPMAIN,&account);
	if (ret)
	{
		writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]cutid[%d]",ret,shop.cut_id);
		if(DB_NOTFOUND==ret)
			return  E_SHOP_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}

    getsysdate(sysdate);
    getsystime(systime);
    GetLogicDate(logicdate);
    tSerial.serial_no = D2I(dUniqNo);
    tSerial.other_seri_no = 0;
    tSerial.serial_state = SERISTAT_DEBT;                           //流水状态
    tSerial.serial_type = TXCODE_REFUND_WATER_ACCOUNT;              //交易类型
    des2src(tSerial.operate_date,sysdate);                           //发生日期
    des2src(tSerial.operate_time,systime);                           //发生时间
    des2src(tSerial.collect_date,sysdate);                           //采集日期
    des2src(tSerial.collect_time,systime);                           //采集时间
    des2src(tSerial.enteract_date,logicdate);                        //处理日期
    des2src(tSerial.enteract_time,systime);                          //处理时间

  	tSerial.maindevice_id = in_pack->lvol6;                            
    tSerial.device_id = in_pack->lvol7;                               //采集设备标识 
    tSerial.card_id = in_pack->lvol1;                                 //交易卡号
    des2src(tSerial.showid,tCard.showid);                            	//显示卡号
    tSerial.purse_id = PURSE_NO_ONE;                                //钱包号
    tSerial.customer_id = tCard.cosumer_id;                         	//客户号
    des2src(tSerial.oper_code, in_pack->scust_limit);                      //操作员代码
    tSerial.sys_id = 0;
	tSerial.trade_count=in_pack->lvol10+1;									//交易次数

	writelog(LOG_DEBUG,"水控退款金额[%.2lf]",tSerial.trade_fee);
    writelog(LOG_DEBUG,"水控退款入卡值[%.2lf]",tSerial.in_balance);
	
  	des2src(IAE.sArrInActno[1],account.account_id);                  	//商户帐户
  	des2src(IAE.sArrInActno[0],accperson.account_id);				//贷方帐号(个人)

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
    
    tSerial.out_balance = IAE.dOutCardBala;                  //出卡值  
	writelog(LOG_DEBUG,"水控退款出卡值[%.2lf]",tSerial.out_balance);

	sprintf(out_pack->vsmess,"水控流水号:%d 卡号:%d,退款金额:%f,出卡值:%f ",IAE.iSerialNo,IAE.iCardNo,tSerial.trade_fee,tSerial.out_balance);

	for(TxTypeCount = 1; TxTypeCount <= IAE.iOutTxTypeCnt; TxTypeCount++)
	{
		switch(IAE.iArrOutTxType[TxTypeCount])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tSerial.deposit_fee = IAE.dArrOutAmt[TxTypeCount];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tSerial.boardfee = IAE.dArrOutAmt[TxTypeCount];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tSerial.in_fee = IAE.dArrOutAmt[TxTypeCount];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tSerial.cost_fee = IAE.dArrOutAmt[TxTypeCount];
				break;
			default:
				break;
		}
		if (amtcmp(IAE.dArrOutAmt[TxTypeCount], 0) != 0)
		{
		    sprintf(msg,"%s:%.2lf元 ", IAE.sArrOutTxName[TxTypeCount], IAE.dArrOutAmt[TxTypeCount]);
			strcat(out_pack->vsmess, msg);
		}
	}

	writelog(LOG_DEBUG,out_pack->vsmess);

	//插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tSerial);
	if (ret)
	{
	    writelog(LOG_ERR,"ret[%d]",ret);
		if (DB_REPEAT == ret)
		{
		    ret = E_DB_TRADESERIAL_E;
		}
		else
		{
		    ret = E_DB_TRADESERIAL_I;
		}
		return ret;
	}

	out_pack->lvol1 = D2I(tSerial.out_balance*100);
	out_pack->lserial1 = tSerial.serial_no;
    return 0;
}


int F847309(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
    int hi_cardid = 0;             //交易卡号
	char refund_type[2] = "";
	
    T_t_pif_card tCard;

	ST_PACK in_third_pack;
	ST_PACK out_third_pack;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);

	memset(&in_third_pack, 0, sizeof(in_third_pack));
	memset(&out_third_pack, 0, sizeof(out_third_pack));
    memset(&tCard, 0, sizeof(tCard));
    memset(&aPack, 0, sizeof(aPack));
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_LVOL1,F_DAMT0,F_DAMT1,F_DAMT2,F_VSMESS,F_LVOL9,F_LVOL5,F_LSERIAL1,0);

    hi_cardid = rPack->lvol1;
    if (hi_cardid <= 0)
    {
        *pRetCode = E_INPUT_CARDNO;
        goto L_RETU;
    }
    
    ret = DB_t_pif_card_read_by_card_id(hi_cardid,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
		    *pRetCode = E_DB_CARD_N;
		}
		else
		{
		    *pRetCode = E_DB_CARD_R;
	    }
	    goto L_RETU;
	}
	
    if (strncmp(tCard.state_id, TYPE_YES, 1) != 0)
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        *pRetCode = E_TRANS_SCHACC_DESTORY;
        goto L_RETU;
    }

    if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_LOST])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        *pRetCode = E_TRANS_SCHCARD_LOSTING;
        goto L_RETU;
    }

    if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_FREEZE])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        *pRetCode = E_TRANS_SCHCARD_FREEZE;
        goto L_RETU;
    }

	// 先查询出水控余额
	in_third_pack.lvol0 = tCard.cosumer_id;			        // 客户标识
	if (ret = CallThirdPart(&in_third_pack, &out_third_pack,847353))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	in_third_pack.lvol1 = out_third_pack.lvol0;
	rPack->lvol0 = out_third_pack.lvol0;
/***********************************************************************/
/************************非主钱包退帐计算*******************************/
	if (ret = GetParameter(3010, refund_type))
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
		
	if (SYNJONES_PACKET == refund_type[0])
	{	
//		memset(&in_third_pack, 0, sizeof(in_third_pack));
//		memset(&out_third_pack, 0, sizeof(out_third_pack));
//		in_third_pack.lvol0 = tCard.cosumer_id;					// 客户标识
//		in_third_pack.lvol1 = (int)(rPack->damt0 * 100);				// 交易金额
		in_third_pack.lvol2 = 1;										// 冲正
		
		if (ret = ProcessExtAcc(rPack, out_pack))
		{
			*pRetCode = ret;
			goto L_RETU;
		}

		if (ret = CallThirdPart(&in_third_pack, &out_third_pack,847352))
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
/***********************************************************************/
	
	PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
	return -1;	
}

