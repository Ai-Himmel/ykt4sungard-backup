/* --------------------------------------------
 * 程序名称: F47105.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:  退卡
 * --------------------------------------------
 * 修改日期:2004-10-12
 * 修改人员:	闻剑
 * 修改描述: 增加记账交易处理
 * 版本信息:1.0.0.1
 * 备注信息:
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

// 住训学员退卡
static int process26(char *begin_date,InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret = 0;
	T_t_cif_cut_svrfee tCutsvrfee;
	memset(&tCutsvrfee,0,sizeof tCutsvrfee);
	double srv_fee_charge = get_svr_fee_charge(IA->sArrInActno[0],begin_date,IA->sTxDate);
	double svr_fee_incard = svr_fee_in_card(p->customer_id, begin_date, IA->sTxDate);
	double svr_fee_noincard = svr_fee_no_in_card(p->customer_id, begin_date, IA->sTxDate);
	double person_acc_in = get_person_acc_in(IA->sArrInActno[0],begin_date,IA->sTxDate);
	double draw_money = get_draw_money(IA->sArrInActno[0],begin_date,IA->sTxDate);
	double subsidy_incard = subsidy_in_card(p->customer_id, begin_date, IA->sTxDate);
	
	//自充值金额
	double self_money = person_acc_in + subsidy_incard - draw_money;

	// 账户余额大于自充值金额
	if(amtcmp(p->trade_fee, self_money) >=0)
	{
		IA->dArrInAmt[0] = self_money;			
		IA->dArrInAmt[1] = p->trade_fee - self_money;
	}
	else
	{
		IA->dArrInAmt[0] = p->trade_fee;			
		IA->dArrInAmt[1] = 0;
	}

	IA->dArrInAmt[2]=p->deposit_fee;				//押金
	IA->pVoidPointer=NULL;
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
		
	writelog(LOG_ERR,"out_balance= [%f]",IA->dOutCardBala);
	if(amtcmp(IA->dOutCardBala,0)>0)
	{
		return E_ENTER_ACCOUNT;
	}
	p->out_balance=0;						//出卡值

	writelog(LOG_DEBUG,"srv_fee_charge[%f],svr_fee_incard[%f],svr_fee_noincard[%f],draw_money[%f],self_money[%f]",srv_fee_charge,svr_fee_incard,svr_fee_noincard,draw_money,self_money);
	ret = DB_t_cif_cut_svrfee_read_by_cut_id(p->customer_id,&tCutsvrfee);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{			
			tCutsvrfee.cut_id = p->customer_id;
			tCutsvrfee.svrfee_charge = srv_fee_charge + svr_fee_incard + svr_fee_noincard;
			tCutsvrfee.self_money = self_money;
			tCutsvrfee.svrfee_bala = IA->dArrInAmt[1];
			des2src(tCutsvrfee.close_date,p->operate_date);
			ret = DB_t_cif_cut_svrfee_add(&tCutsvrfee);
			if(ret)
				return E_DB_CUT_SVRFEE_I;
		}
		else
			return E_DB_CUT_SVRFEE_R;
	}
	else
	{
		//tCutsvrfee.cut_id = p->customer_id;
		tCutsvrfee.svrfee_charge = srv_fee_charge + svr_fee_incard + svr_fee_noincard;
		tCutsvrfee.self_money = self_money;
		tCutsvrfee.svrfee_bala = IA->dArrInAmt[1];
		des2src(tCutsvrfee.close_date,p->operate_date);
		ret = DB_t_cif_cut_svrfee_update_by_cut_id(p->customer_id,&tCutsvrfee);
		if(ret)
			return E_DB_CUT_SVRFEE_U;
	}
	return 0;
}
static int process(ST_PACK *rPack,InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret =0;
	int *ptype=NULL;

	ptype=(int*)IA->pVoidPointer;
	switch(*ptype)
	{
		case TYPE_CASH:	//现金
			IA->iArrInFeeSwitch[1]=1;
			break;
		case TYPE_BILL:	//支票
			IA->iArrInFeeSwitch[2]=1;
			break;
		case TYPE_FUNDBOOK:	//经费本
			IA->iArrInFeeSwitch[3]=1;
			break;
		default:
			writelog(LOG_ERR,"type[%d]",*ptype);
			IA->iArrInFeeSwitch[1]=1;
			break;
	}
	IA->pVoidPointer=NULL;

	IA->dArrInAmt[0]=p->trade_fee;				//卡余额
	IA->dArrInAmt[1]=p->boardfee;				//搭伙费
	IA->dArrInAmt[2]=p->deposit_fee;				//押金

	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
		
	writelog(LOG_ERR,"out_balance= [%f]",IA->dOutCardBala);
	if(amtcmp(IA->dOutCardBala,0)>0)
	{
		return E_ENTER_ACCOUNT;
	}
	p->out_balance=0;						//出卡值
	/*
	ret = process_change_card(&tCustomer,&tCard);
	return ret;
	*/
	return 0;
}

int F847105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret =0;
	int i=0;
	int origin_card_id = 0;
	int bill_type=0;
	int upd_flag=0;
	int svrfee_feetype[30]; 
	int feetype_cnt=0;
	bool bsrvfee=false;
	
	char physical_no[40+1] = "";
	char logicdate[11] = "";												//业务日期
	char sysdate[11]="";
	char lost_date[11]="";
	char systime[9]="";
	char sEndDate[9]="";
	char sMsg[256]="";
	double dSerialNo=0;
	T_t_pif_card		tCard;
	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_libdeposit    libdeposit;
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account  	tAccount;
//	T_t_tif_savdtl tSavdtl;
	InAcc  IA;
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_LVOL1,F_LSERIAL1,F_VSMESS,0);


	memset(&tCard,0,sizeof(tCard));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&tradeserial,0,sizeof(tradeserial));
//	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&IA,0,sizeof(IA));
	memset(&tCustomer,0,sizeof tCustomer);
	memset(&tSpeFee,0,sizeof tSpeFee);
	memset(&tAccount,0,sizeof(tAccount));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);											//业务日期
	if(ret)	
		return ret;

	ret = Get_svrfee_feetype(svrfee_feetype, &feetype_cnt);
	if(ret)
		return ret;	
		
	writelog(LOG_DEBUG,"card_id[%d]",rPack->lvol1);
	origin_card_id = rPack->lvol1;   										//原卡号
	des2src(physical_no, rPack->sbank_acc);							//物理卡号
	if(rPack->lvol1<1)
		return E_INPUT_CARDNO_CANNOT_NULL;
	
	tradeserial.other_seri_no = 0;										//上传端流水号
	tradeserial.serial_type=TXCODE_CALLBACK_CARD;						//功能号
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
	tradeserial.sys_id = 0;												//外部系统标识
	des2src(tradeserial.oper_code, rPack->scust_limit);					//操作员号
	tradeserial.card_id=origin_card_id;
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(origin_card_id,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
//	writelog(LOG_DEBUG,"input card_id[%d] card_id[%d]",origin_card_id,tCard.card_id);
	tradeserial.customer_id = tCard.cosumer_id;							//客户标识
	ret = DB_t_tif_libdeposit_read_by_customer_id(tCard.cosumer_id, &libdeposit);			//检查是否有图书馆押金
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"err:DB_t_tif_libdeposit_read_by_customer_id[%d]",tCard.cosumer_id);
			return  E_DB_LIBDEPOSIT_R;
		}
	}
	else
	{
		if(libdeposit.fee_flag[0] =='1')
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"customer_id[%d] has libdeposit ",tCard.cosumer_id);
			return E_DB_LIBDEPOSIT_H;
		}
	}
	
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)==0)
	{
		//检查物理卡号是否一致
		trim(physical_no);
		trim(tCard.physical_no);
		if(strcmp(tCard.physical_no,physical_no)!=0)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,physical_no);
			return E_CARD_PHYNO_DIFFER;
		}
	}
	else if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		return E_CARDNO_LOGOUT;
	}
	else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
	{
		DB_t_pif_card_free_lock_by_cur();
		return E_CARDNO_FREEZE;
	}
	else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
	{
		if(IS_YES==rPack->lvol12)
		{
			DB_t_pif_card_free_lock_by_cur();
			return E_CARDNO_LOST;
		}
		ret=get_latest_lost_date_by_card_no(origin_card_id,lost_date);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"lost_card_id[%d]",origin_card_id);
			return ret;
		}
		//先检查客户的挂失的正式卡是否到了补办日期
		ret=GetLostCardValiddate(lost_date,sEndDate);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			return ret;
		}
		if(strncmp(sEndDate,sysdate,8)>0)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"lost_normal_card_id[%d]lost_date[%s]end_date[%s]",origin_card_id,lost_date,sEndDate);
			return E_NORMALCARD_NOT_REACH_ENDDATE;
		}

	}
	else if(IS_YES!=rPack->lvol12)
	{
		DB_t_pif_card_free_lock_by_cur();
		return E_NOCARD;
	}
	//注销原卡
	des2src(tCard.state_id,CARDSTAT_LOGOUT);		//注销
	des2src(tCard.end_time,tradeserial.operate_date);	//注销日期
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",tCard.card_id);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	DB_t_pif_card_free_lock_by_cur();

	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id,&tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cosumer_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(CT_TEMP_NONAME==tCard.type_id)
	{
		tCustomer.cut_state=CUSTSTAT_LOGOUT;		//注销
		upd_flag=1;
	}
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
				return E_DB_SPEFEE_R;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		upd_flag=1;
	}
	if(upd_flag)
	{
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			writelog(LOG_ERR,"cosumer_id[%d]",tCard.cosumer_id);
			return E_DB_CUSTOMER_U;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	IA.iFeeType=tCustomer.fee_type;

	//是否退费,规定正式卡和临时卡退押金,非记名临时卡退押金
	if(IS_YES==rPack->lvol12)
	{
		IA.iUseCardFlag=USE_CARD_TYPE_ONLINE;		//联机交易
		IA.dInCardBala = rPack->damt2;				//入卡值
		IA.dOutCardBala=-1;							//-1 表示空值
		IA.iTxCnt = rPack->lvol10+1;					//当前卡交易次数
		tradeserial.trade_count = IA.iTxCnt;
	}
	else
	{
		IA.iUseCardFlag=USE_CARD_TYPE_NULL;
		IA.dInCardBala = -1;				//-1 表示空值
		IA.dOutCardBala=-1;				//-1 表示空值
		IA.iTxCnt = -1;					//-1 表示空值
	}
	bill_type=TYPE_CASH;
//	IA.pVoidPointer=&tSavdtl.bill_type;
	IA.pVoidPointer=&bill_type;
	IA.iCardNo=tCard.card_id;
	des2src(tradeserial.showid,tCard.showid);		//显示卡号

	ret=DB_t_aif_account_read_by_card_id_and_purse_id(tCard.card_id,PURSE_NO_ONE, &tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,tCard.card_id);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
//	writelog(LOG_DEBUG,"cur_freebala[%f],card_bala[%f]",tAccount.cur_freebala,IA.dInCardBala);
	if(USE_CARD_TYPE_ONLINE==IA.iUseCardFlag)					//有卡交易
	{
		// 按小的退卡
		if(amtcmp(D4U5(tAccount.cur_freebala,2),IA.dInCardBala)>0)
		{
			writelog(LOG_ERR,"card_id[%d] act_id[%s] cur_freebala[%lf],input card_balance[%lf]",tCard.card_id,tAccount.account_id,tAccount.cur_freebala,IA.dInCardBala);
			//只修改发生额，搭伙费全退，流水入账模块进行处理吧
			tradeserial.trade_fee = IA.dInCardBala;			//可用余额//Changed by hhd at 2005-10-22 14:2
			strcpy(tradeserial.reserve_2,"卡库不符|按卡余额退卡");
			//p->boardfee	=  (D4U5(tAccount.cur_freebala,2)-IA->dInCardBala);
		}
		else 
		{
			tradeserial.trade_fee = tAccount.cur_freebala;
			IA.dInCardBala = tAccount.cur_freebala;
		}
	}
	else
	{
		tradeserial.trade_count = tAccount.consume_count;
		tradeserial.trade_fee = tAccount.cur_freebala;			//可用余额//Changed by hhd at 2005-10-22 14:21
	}
	tradeserial.in_balance = tradeserial.trade_fee;
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  						//获得最大流水号
	if(ret)
	{
		return ret;
	}
	//把预提费用转为学校收益
	tradeserial.serial_no=D2I(dSerialNo);
	tradeserial.in_fee = 0;							//管理费/手续费
	
	IA.iTradeNo=tradeserial.serial_type;				//交易码
	IA.iMainDevId=tradeserial.maindevice_id;			//工作站标识
	IA.iDevId=tradeserial.device_id;					//设备ID
	IA.iSerialNo=tradeserial.serial_no;					//流水号
	des2src(IA.sTxDate,tradeserial.operate_date);		//交易日期
	des2src(IA.sTxTime,tradeserial.operate_time);		//交易时间
	des2src(IA.sTxCollectDate,tradeserial.collect_date);	//采集日期
	des2src(IA.sTxCollectTime,tradeserial.collect_time);	//采集时间
	des2src(IA.sTxAccDate,tradeserial.enteract_date);	//记账日期
	des2src(IA.sTxAccTime,tradeserial.enteract_time);	//记账时间
	des2src(IA.sMdeOper,tradeserial.oper_code);		//操作员
	strcpy(IA.sChkOper,tradeserial.reserve_1);		//复核操作员

	des2src(IA.sArrInActno[0],tAccount.account_id);	//卡帐户

	//是否退卡余额和搭伙费
	if(IS_YES==rPack->lvol3)
	{
		IA.iArrInFeeSwitch[5]=1;
	}
	//是否退押金
	if(IS_YES==rPack->lvol2)
	{
		IA.iArrInFeeSwitch[6]=1;
	}

	sprintf(out_pack->vsmess,"流水号:%d 卡号:%d ",IA.iSerialNo,IA.iCardNo);

	for(i=0;i<feetype_cnt;i++)
	{
		if(tCustomer.fee_type == svrfee_feetype[i])
		{
			bsrvfee = true;
			break;
		}
	}
	if(bsrvfee)
	{
		tradeserial.deposit_fee =  tCard.deposit_fee;			//押金
		ret = process26(tAccount.open_date,&IA,&tradeserial);
		if(ret)
			return ret;
		
	//	sprintf(sMsg," 应退现金:%.2lf,服务费结余:%.2lf",IA.dArrInAmt[0],IA.dArrInAmt[1]);	
	//	strcat(out_pack->vsmess,sMsg);
	}
	else
	{	
		tradeserial.boardfee	=  tAccount.cur_frozebala;		//冻结金额//Changed by hhd at 2005-10-22 14:21
		tradeserial.deposit_fee =  tCard.deposit_fee;			//押金
		ret=process(rPack,&IA,&tradeserial);
		if(ret)
			return ret;			
	}

	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_DEDUCT_DEPOSIT:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_RETURN_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT_BILL:
			case TXTYPE_RETURN_DEPOSIT_FUNDBOOK:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				out_pack->damt0+=IA.dArrOutAmt[i];
				break;
			case TXTYPE_DEDUCT_BOARD:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				out_pack->damt0+=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CARDCOST:
				tradeserial.cost_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_DRAW_CASH:
			case TXTYPE_DRAW_BILL:
			case TXTYPE_DRAW_FUNDBOOK:
			case TXTYPE_DRAW_OTHER:
				tradeserial.trade_fee=IA.dArrOutAmt[i];
				out_pack->damt0+=IA.dArrOutAmt[i];
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

	sprintf(sMsg,"实际应退金额:%.2lf元",out_pack->damt0);
	strcat(out_pack->vsmess,sMsg);	
	
	//Changed by hhd at 2005-10-22 14:21
	//修改账户状态时，这些账户置为4临时状态
	//等待未上传流水回传入账
	ret=DB_t_aif_account_read_lock_by_cur4_and_card_id_and_purse_id(tCard.card_id,PURSE_NO_ONE, &tAccount);
	if(strcmp(tradeserial.reserve_2,"卡库不符|按卡余额退卡")==0)
	{
		tAccount.current_state= ACCOUNTSTAT_TEMP;			//临时状态
	}
	else
	{
		tAccount.current_state= ACCOUNTSTAT_LOGOUT;			//注销
	}
	des2src(tAccount.close_date,tradeserial.operate_date);			//销户日期
	des2src(tAccount.close_time,tradeserial.operate_time);			//销户时间
	ret=DB_t_aif_account_update_lock_by_cur4(&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_update_lock_by_cur4 ret[%d]account_id[%s]",ret,tAccount.account_id);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_U;
	}
	DB_t_aif_account_free_lock_cur4();
		
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	
	ret = InsertToCutUpdList(origin_card_id, CUTUPD_CANCEL,tCard.physical_no);
	if(ret)
	{
		writelog(LOG_DEBUG,"InsertToCutUpdList ret[%d]",ret);
		return ret;
	}
	
	PutRow(handle,out_pack,pRetCode,szMsg);

	return 0;
}

