/* --------------------------------------------
 * 程序名称: F47104.c
 * 创建日期: 2005-08-08
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  补办卡
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
#include "fdsqc.h"
#include "dbfunc_foo.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret = 0;

	//根据卡号和钱包号得到消费者账号(借方)
	IA->iMainDevId=p->maindevice_id;			//工作站标识
	IA->iDevId=p->device_id;					//设备ID
	IA->iSerialNo=p->serial_no;					//流水号
	IA->iTradeNo=p->serial_type;				//交易码
	strcpy(IA->sTxDate,p->operate_date);		//交易日期
	strcpy(IA->sTxTime,p->operate_time);		//交易时间
	strcpy(IA->sTxCollectDate,p->collect_date);	//采集日期
	strcpy(IA->sTxCollectTime,p->collect_time);	//采集时间
	strcpy(IA->sTxAccDate,p->enteract_date);	//记账日期
	strcpy(IA->sTxAccTime,p->enteract_time);	//记账时间
	strcpy(IA->sMdeOper,p->oper_code);		//录入 操作员
	strcpy(IA->sChkOper,p->reserve_1);		//复核 操作员
	p->in_balance=0;							//入卡值
	IA->dOutCardBala=-1;						//出卡值
	IA->iTxCnt=1;							//交易次数
	//修改借方和贷方帐户余额,记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;		//出卡值
	return 0;
}
int F847104(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret =0;
	int len = 0;
	int i=0;
	int hi_cutid=0;
	char h_showcardid[11] = "";						//显示卡号
	char h_password[7] = "";							//卡密码
	double h_temp_Card_id = 0;						//卡号
	double dSerialNo=0;
	char seed_key[17] = "";							//种子密钥
	char card_endtime[8 + 1] = "";						//卡的有效截至日期
	char logicdate[11]="";								//业务日期
	char sysdate[11]="";
	char systime[9]="";
	char sEndDate[9]="";
	char sMsg[256]="";
	char sMaxCardBalance[20]="";
	char lost_date[11]="";
	double dMaxCardBalance=0;
	int lost_card_id=0;
	T_t_pif_card		tCard;
	T_t_pif_card		tOldCard;
	T_t_cif_customer 	tCustomer;
	T_t_pif_spefee 	tSpeFee;
    //	T_t_pif_cardlossinfo tCardLossInfo;
	T_t_tif_tradeserial  tradeserial;
	T_t_aif_account tAccount;
	InAcc  IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
           F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
           F_SDATE0,F_SNAME,F_SNAME2,
           F_SOPEN_EMP,F_SSTATUS0,
           F_DAMT2,F_LSERIAL1,F_VSMESS,0);

	memset(&tCard,0,sizeof(tCard));
	memset(&tOldCard,0,sizeof(tOldCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
    //	memset(&tCardLossInfo,0,sizeof(tCardLossInfo));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);										//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//检查客户信息，判断是否可以发行卡
	hi_cutid=rPack->lvol0;									//客户号
	des2src(tCard.physical_no, rPack->sbank_acc);				//物理卡号
	trim(h_showcardid);
	ret=IsExistFreezeCardByCustomId(hi_cutid);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=IsExistNoLostCardByCustomId(hi_cutid);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	if(strlen(h_showcardid))
	{
		ret=IsExistShowCardNo(h_showcardid);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	ret=IsExistCardByPhyCardNo(tCard.physical_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=GetLostCardIdByCustomId_TypeId(hi_cutid,CT_NORMAL,&lost_card_id);
	if(ret)
	{
		writelog(LOG_ERR,"customer[%d]tCard type_id[%d]",hi_cutid,CT_NORMAL);
		*pRetCode = ret;
		goto L_RETU;
	}

    /*
      ret=DB_t_pif_cardlossinfo_read_by_card_id_and_state_id(lost_card_id, STATE_VALID, &tCardLossInfo);
      if(ret)
      {
      writelog(LOG_ERR,"lost_card_id[%d]",lost_card_id);
      if(DB_NOTFOUND==ret)
      *pRetCode =  E_CARDNO_NOT_EXIST;
      else
      *pRetCode =  E_DB_CARD_R;
      goto L_RETU;
      }
    */
	ret=get_latest_lost_date_by_card_no(lost_card_id,lost_date);
	if(ret)
	{
		writelog(LOG_ERR,"lost_card_id[%d]",lost_card_id);
		*pRetCode =ret;
		goto L_RETU;
	}
	//先检查客户的挂失的正式卡是否到了补办日期
	ret=GetLostCardValiddate(lost_date,sEndDate);
	if(ret)
	{
		*pRetCode =ret;
		goto L_RETU;
	}

	if(strncmp(sEndDate,sysdate,8)>0)
	{
		writelog(LOG_ERR,"lost_normal_card_id[%d]lost_date[%s]end_date[%s]",lost_card_id,lost_date,sEndDate);
		*pRetCode =  E_NORMALCARD_NOT_REACH_ENDDATE;
		goto L_RETU;
	}
    /*
	//更新卡挂失日期表中该卡状态为无效
	ret=UpdateCardLossInfoState(lost_card_id,STATE_VALID,STATE_INVALID);
	if(ret)
	{
    *pRetCode = ret;
    goto L_RETU;
	}
    */
	//注销原卡
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(lost_card_id,&tOldCard);
	if(ret)
	{
		writelog(LOG_ERR,"lost_card_id[%d]",lost_card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode = E_CARDNO_NOT_EXIST;
		else
			*pRetCode =  E_DB_CARD_R;
		goto L_RETU;
	}
	des2src(tOldCard.state_id,CARDSTAT_LOGOUT);		//注销
	des2src(tOldCard.end_time,sysdate);				//注销日期
	ret=DB_t_pif_card_update_lock_by_cur(&tOldCard);
	if(ret)
	{
		writelog(LOG_ERR,"lost_card_id[%d]",lost_card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode =   E_CARDNO_NOT_EXIST;
		else
			*pRetCode =  E_DB_CARD_R;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();

	ret = InsertToCutUpdList(tOldCard.card_id,CUTUPD_CH_OLDCARD,tOldCard.physical_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(hi_cutid, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",hi_cutid);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	//得到收费类别
	if(tCustomer.fee_type<1)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//更新客户表的收费类别字段
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
	}
	DB_t_cif_customer_free_lock_cur();

	tradeserial.trade_fee =D4U5(rPack->damt0,2);
	//	准备数据插入卡信息表
	memcpy(seed_key,STATIC_SEED_KEY,16);			//读种子密钥
	if(strlen(tCustomer.can_time)==8)
	{
		ret=IsInvalidDateTime(tCustomer.can_time,"YYYYMMDD");
		if(ret)
		{
			*pRetCode=E_TB_CUSTOMER_ENDTIME;
			goto L_RETU;
		}
		if(strncmp(tCustomer.can_time,sysdate,8)<=0)
		{
			*pRetCode=E_TB_CUSTOMER_ENDTIME;
			goto L_RETU;
		}
		des2src(card_endtime,tCustomer.can_time);
	}
	else if(strlen(rPack->sdate0)==0)
	{
		*pRetCode=E_TB_CUSTOMER_NO_ENDTIME;
		goto L_RETU;
	}
	else
	{
		ret=IsInvalidDateTime(rPack->sdate0,"YYYYMMDD");
		if(ret)
		{
			*pRetCode = E_INPUT_DATE;
			goto L_RETU;
		}
		if(strncmp(rPack->sdate0,sysdate,8)<=0)
		{
			*pRetCode=E_INPUT_DATE;
			goto L_RETU;
		}
		des2src(card_endtime,rPack->sdate0);
	}

	tradeserial.trade_fee = rPack->damt0;								//金额
	tradeserial.other_seri_no = 0;										//上传端流水号
	tradeserial.serial_state = SERISTAT_DEBT;								//流水状态
	des2src(tradeserial.operate_date,sysdate);							//发生日期
	des2src(tradeserial.operate_time,systime);							//发生时间
	des2src(tradeserial.collect_date,sysdate);								//采集日期
	des2src(tradeserial.collect_time,systime);								//采集时间
	des2src(tradeserial.enteract_date,logicdate);							//处理日期
	des2src(tradeserial.enteract_time,systime);							//处理时间
	tradeserial.maindevice_id = rPack->lvol6;								//上传工作站标识
	tradeserial.device_id = rPack->lvol7;									//采集设备标识
	tradeserial.purse_id = PURSE_NO_ONE;								//钱包号
	tradeserial.customer_id = tCustomer.cut_id;							//客户标识
	tradeserial.sys_id = 0;												//外部系统标识
	des2src(tradeserial.oper_code, rPack->scust_limit);					//操作员号

	len=strlen(tCustomer.man_id) ;
	if (len >= 6)
	{
		strncpy(h_password,&(tCustomer.man_id[len-6]),6);
		if(h_password[5]>'9'||h_password[5]<'0')
			h_password[5]='0';
	}
	else
	{
		strcpy(h_password,DEFAULT_CUST_PWD);
	}
	ret = getNewUniqNo(KEYTYPE_CARD_ID,&h_temp_Card_id);						//获取最大卡号
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tCard.card_id = D2I(h_temp_Card_id);											//卡号
	des2src(tCard.showid,h_showcardid);										//显示卡号
	des2src(tCard.is_main,TYPE_YES);  											//是否为主卡
	des2src(tCard.state_id,CARDSTAT_REG);										//卡状态
	tCard.type_id = CT_NORMAL;													//卡类别
	EncodePwd(seed_key,h_password,tCard.password,0);							//卡密码
	tCard.cosumer_id = hi_cutid;													//客户标识
	tCard.account_count = ACCOUNT_COUNT_ONE;									//卡对应帐户个数
	des2src(tCard.begin_time,sysdate);											//注册时间
	des2src(tCard.end_time, card_endtime);										//截至时间

	tCard.phytype = PHYTYPE_NO_ONE;											//设备物理型号;默认为1
	//	插入卡信息
	ret = DB_t_pif_card_add(&tCard);
	if (ret)
	{
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_CARD_E;
		else
			*pRetCode = E_DB_CARD_I;
		goto L_RETU;
	}
	ret = InsertToCutUpdList(tCard.card_id,CUTUPD_CH_NEWCARD,tCard.physical_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	
	//修改帐户表中对应的卡号,类型,状态
	ret=DB_t_aif_account_read_lock_by_c0_and_card_id_and_purse_id(lost_card_id,PURSE_NO_ONE,&tAccount);
	if (ret)
	{
		writelog(LOG_ERR,"normalcard_account_id[%s]",lost_card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode =  E_ACTNO_NOT_EXIST;
		else
			*pRetCode =  E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=1)
	{
		*pRetCode=E_ACTNO_LOGOUT;
		goto L_RETU;
	}
	tAccount.card_id=tCard.card_id;
	tAccount.card_balance=tAccount.cur_freebala;			//更新卡余额与库余额一致
	tAccount.consume_count=0;
	ret=DB_t_aif_account_update_lock_by_c0(&tAccount);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_update_lock_by_cur4 ret[%d]account_id[%s]",ret,tAccount.account_id);
		if(DB_NOTFOUND==ret)
			*pRetCode =   E_ACTNO_EXIST;
		else
			*pRetCode =  E_DB_ACCOUNT_U;
	}
	DB_t_aif_account_free_lock_c0();

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  						//获得最大流水号
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	tradeserial.serial_no=D2I(dSerialNo);
	tradeserial.serial_type=TXCODE_CHANGE_CARD;
	tradeserial.card_id=tCard.card_id;				//新卡号
	des2src(tradeserial.showid,tCard.showid);			//显示卡号

	strcpy(IA.sArrInActno[0],tAccount.account_id);		//账号
	IA.dArrInAmt[0]=tradeserial.trade_fee;			//交易金额
	IA.iUseCardFlag=USE_CARD_TYPE_ONLINE;		//联机交易
	IA.dInCardBala=tAccount.cur_freebala;			//入卡值
	IA.iTxCnt=1;
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"流水号:%d 卡号:%d ",IA.iSerialNo,IA.iCardNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
        case TXTYPE_TOLL_DEPOSIT:
        case TXTYPE_DEDUCT_DEPOSIT:
        case TXTYPE_RETURN_DEPOSIT:
            tradeserial.deposit_fee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_PRE_TOLL_BOARD:
        case TXTYPE_TOLL_BOARD:
        case TXTYPE_DEDUCT_BOARD:
        case TXTYPE_RETURN_BOARD:
            tradeserial.boardfee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_TOLL_CHARGE:
            tradeserial.in_fee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_TOLL_CARDCOST:
            tradeserial.cost_fee=IA.dArrOutAmt[i];
            break;
        default:
            break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	sprintf(sMsg,"卡当前余额:%.2lf元",tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
	//检查金额是否超过最大额度
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	dMaxCardBalance=atof(sMaxCardBalance);
	if(amtcmp(tradeserial.out_balance,dMaxCardBalance)>0)
	{
		writelog(LOG_ERR,"tradeserial.out_balance[%lf]",tradeserial.out_balance);
		*pRetCode=E_AMT_EXCEED_MAX;
		goto L_RETU;
	}

	//返回卡号\密码\显示卡号\客户类型\图书证号\有效截至日期
	out_pack->lvol0 = (int)h_temp_Card_id;						//交易卡号
	out_pack->lvol1 = tCustomer.cut_type;						//客户类别
	out_pack->lvol5 = tCustomer.fee_type;						//收费类别
	des2src(out_pack->scust_no,h_showcardid);					//显示卡号
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//部门号
	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//学号
	des2src(out_pack->scust_auth2,tCustomer.man_id);			//身份证号
	des2src(out_pack->sname,tCustomer.cut_name);				//客户姓名
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//图书证号
	des2src(out_pack->sstatus0,tCustomer.sex);					//性别
	des2src(out_pack->sopen_emp,h_password);					//卡密码
	des2src(out_pack->sdate0,card_endtime);					//有效截至日期

	out_pack->damt2=tradeserial.out_balance;					//出卡值
	out_pack->lserial1=tradeserial.serial_no;						//流水号
	// add by 汤成 2005-8-8
	// 增加向名单表写入记录
	/*
	ret = InsertToBlkList((int)h_temp_Card_id,CHCARD_BLACKLIST);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	*/
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
  L_RETU:
	return -1;
}

