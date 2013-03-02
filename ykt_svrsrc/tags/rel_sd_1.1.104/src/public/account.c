/* --------------------------------------------
 * 程序名称: account.c
 * 创建日期: 2004-08-01
 * 程序作者: 闻剑
 * 版本信息: 1.0
 * 程序功能: 一卡通账务处理
 * --------------------------------------------
 * 修改日期:2005-07-14
 * 修改人员:闻剑
 * 修改描述:修改入账 处理
 * 版本信息:2.0
 * 备注信息:
 * --------------------------------------------*/


#include "pubdef.h"
#include "dictionary.h"
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "express.h"

#define TYPE_INPUT  1
#define TYPE_CONFIG 2
#define MAXNUM_SUBJECT  		30		//最大科目个数
#define MAXNUM_CFGTXFEE		60		//最大交易配置项个数
#define MAXNUM_CFGSPLIT		60		//最大交易类型个数

typedef struct
{
	int num;
	T_t_tif_cfgtxfee ArrCfgFee[MAXNUM_CFGTXFEE];
}Cfg_FEE;

typedef struct
{
	int num;
	T_t_tif_cfgsplit  ArrCfgsplit[MAXNUM_CFGSPLIT];
}CFG_SPLIT;
typedef struct
{
	int num;
	T_t_tif_subject	ArrSubject[MAXNUM_SUBJECT];
}CFG_SUB;

static Cfg_FEE  CfgFee;
static CFG_SPLIT CfgSplit;
static CFG_SUB  CfgSubject;
//static CFG_IDX  CfgIdx;

//初始化分录配置
int InitSplitCfg()
{
	int ret=-1;
	int row=0;
	static      int  	InitAccFlag=0;
	T_t_tif_cfgsplit  tCfgsplit;
	if(InitAccFlag)
		return 0;

	memset(&CfgSplit,0,sizeof(CfgSplit));

	ret=DB_t_tif_cfgsplit_open_select_by_c0();
	while(1)
	{
		memset(&tCfgsplit,0,sizeof(tCfgsplit));
		ret=DB_t_tif_cfgsplit_fetch_select_by_c0(&tCfgsplit);
		if(ret)
		{
			if(DB_NOTFOUND== ret)
			{
				if(row)
					break;
				else
					return E_DB_CFGSPLIT_N;
			}
			else
				return E_DB_CFGSPLIT_R;
		}
		row++;
		if(tCfgsplit.txtype>=MAXNUM_CFGSPLIT)
			return E_BEYOND_MAXNUM_SPLITCFG;	//超过分录最大数
		memcpy(&CfgSplit.ArrCfgsplit[tCfgsplit.txtype],&tCfgsplit,sizeof(tCfgsplit));
		CfgSplit.num++;
	}
	InitAccFlag=1;
	return 0;
}

//初始化交易配置
int InitTxFeeCfg()
{
	int ret=-1;
	static      int  	InitTxFlag=0;

	if(InitTxFlag)
		return 0;

	memset(&CfgFee,0,sizeof(CfgFee));

	ret=DB_t_tif_cfgtxfee_open_select_by_c0();
	while(1)
	{
		ret=DB_t_tif_cfgtxfee_fetch_select_by_c0((T_t_tif_cfgtxfee*)&CfgFee.ArrCfgFee[CfgFee.num]);
		if(ret)
		{
			if(DB_NOTFOUND== ret)
			{
				if(CfgFee.num)
					break;
				else
					return E_DB_TRADEACT_N;
			}
			else
				return E_DB_TRADEACT_R;
		}
		CfgFee.num++;
		if(CfgFee.num>=MAXNUM_CFGTXFEE)
			return E_BEYOND_MAXNUM_TRADECODE;	//交易码配置超过最大数
	}
	InitTxFlag=1;
	return 0;
}

int GetIndexTxFeeCfgByTxCode(int tx_code,int fee_type)
{
	register int index=0;
	for(index=0;index<CfgFee.num;index++)
	{
		if((CfgFee.ArrCfgFee[index].tx_code==tx_code)&&(CfgFee.ArrCfgFee[index].fee_type==fee_type))
			return index;
	}
	return -1;
}

//初始化科目配置
int InitSubjectCfg()
{
	int ret=0;
	static      int  	InitSubNoFlag=0;

	if(InitSubNoFlag)
		return 0;

	memset(&CfgSubject,0,sizeof(CfgSubject));

	ret=DB_t_tif_subject_open_select_by_c0();
	if(ret)
	{
		return E_DB_SUBJECT_R;
	}
	while(1)
	{
		ret=DB_t_tif_subject_fetch_select_by_c0((T_t_tif_subject*)&CfgSubject.ArrSubject[CfgSubject.num]);
		if(ret)
		{
			if(DB_NOTFOUND== ret)
			{
				if(CfgSubject.num)
					break;
				else
					return E_DB_SUBJECT_N;
			}
			else
				return E_DB_SUBJECT_R;
		}
		CfgSubject.num++;
		if(CfgSubject.num>=MAXNUM_SUBJECT)
			return E_BEYOND_MAXNUM_SUBJECT;
	}
	InitSubNoFlag=1;
	return 0;
}
int GetIndexSubjectCfgBySubNo(char *subno)
{
	register int index=0;
	for(index=0;index<CfgSubject.num;index++)
	{
		if(strcmp(subno,CfgSubject.ArrSubject[index].subno)==0)
			return index;
	}
	return -1;
}
int AccountProcess(InAcc *IA)
{
	int ret=-1;
	int iTxType=0;		//交易类型
	char num_exp[256]="";
	char sFee[256]="";
	char sFormula[256]="";
	char sIdxDbActNo[4]="";
	char sIdxCrActNo[4]="";
	char sVocNo[21] = "";
	double dExpCalAmt=0;
	int iVocType = VOCTYPE_DEFALUT;

	int i = 0;
	int idx=0;
	int idxTxCfg=-1;
	int idxSubCfg=-1;
	int config_cnt=1;
	int db_amt_flag=0;
	int cr_amt_flag=0;
	double  dInCardBala=0;
	double  dCardBala=0;
	double  dOutCardBala=0;

	T_t_pif_card	  tCard;
	T_t_aif_account tAccountDb;
	T_t_aif_account tAccountCr;
	T_t_tif_tradelog tTradelogDb;
	T_t_tif_tradelog tTradelogCr;

	ret=InitTxFeeCfg();
	if(ret)
		return ret;
	ret=InitSplitCfg();
	if(ret)
		return ret;
	ret=InitSubjectCfg();
	if(ret)
		return ret;

	//根据交易码和客户收费类别读交易配置表
	if(IA->iFeeType<1)
	{
		return E_CUSTOMER_NO_FEE_TYPE;
	}
	idxTxCfg=GetIndexTxFeeCfgByTxCode(IA->iTradeNo,IA->iFeeType);
	if(idxTxCfg<0)
	{
		//如果没有取默认值
		idxTxCfg=GetIndexTxFeeCfgByTxCode(IA->iTradeNo,0);
		if(idxTxCfg<0)
		{
			writelog(LOG_ERR,"tx_code[%d]fee_type[%d]",IA->iTradeNo,IA->iFeeType);
			return E_CUSTOMER_NO_RIGHT;
		}
	}
	dInCardBala=IA->dInCardBala;
	dCardBala=IA->dInCardBala;
	dOutCardBala=IA->dOutCardBala;

	for(config_cnt=1;config_cnt<=MAXNUM_CFGSPLIT;config_cnt++)
	{
		//开始遍历收费集合
		ret=GetValueFromFmtBuf(CfgFee.ArrCfgFee[idxTxCfg].fee_list,",",config_cnt,sFee);
		if(ret)
		{
			if(1==config_cnt)
			{
				writelog(LOG_ERR, "TxCode[%d]FeeType[%d]fee_list[%s]",IA->iTradeNo,IA->iFeeType,CfgFee.ArrCfgFee[idxTxCfg].fee_list);
				return E_TXCODE_NOT_CONFIG;		//交易未配置
			}
			break;
		}
		iTxType=atoi(sFee);
		if(iTxType<0)
		{
			writelog(LOG_ERR,"tx_code[%d]fee_type[%d]",IA->iTradeNo,IA->iFeeType);
			return E_CUSTOMER_NO_RIGHT;
		}
//		writelog(LOG_DEBUG,"fee_list[%s]sFee[%s]",CfgFee.ArrCfgFee[idxTxCfg].fee_list,sFee);
		ret=GetValueFromFmtBuf(CfgFee.ArrCfgFee[idxTxCfg].formula_list,",",config_cnt,sFormula);
		if(ret)
		{
			writelog(LOG_ERR, "TxCode[%d]FeeType[%d]formula_list[%s]",IA->iTradeNo,IA->iFeeType,CfgFee.ArrCfgFee[idxTxCfg].formula_list);
			return E_EXP_NOT_CFG;		//交易未配置
		}
//		writelog(LOG_DEBUG,"formula_list[%s]Formula[%s]",CfgFee.ArrCfgFee[idxTxCfg].formula_list,sFormula);
		//得到收费类型
		/*
		switch(iTxType)
		{
//			case TXTYPE_TOLL_DEPOSIT:		//收押金
			case TXTYPE_RETURN_DEPOSIT:		//退押金
			case TXTYPE_DEDUCT_DEPOSIT:	//扣押金
				memset(&tCard,0,sizeof(tCard));
				if(IA->iCardNo<1)
				{
					return E_INPUT_CARDNO_CANNOT_NULL;
				}
				ret=DB_t_pif_card_read_by_card_id(IA->iCardNo,&tCard);
				if(ret)
				{
					if(DB_NOTFOUND==ret)
						return E_CARDNO_NOT_EXIST;
					else
						return E_DB_CARD_R;
				}
				dExpCalAmt=tCard.deposit_fee;
				break;

			default:
				ret=VarExp2NumExp(IA->dArrInAmt,IA->iArrInFeeSwitch,sFormula,num_exp);
				if(ret)
				{
					writelog(LOG_ERR,"ret[%d]txcode[%d]txtype[%d]formula[%s]",ret,IA->iTradeNo, iTxType,sFormula);
					return E_EXP_CFG;
				}
		//		writelog(LOG_ERR,"formula[%s]num_exp[%s]",sFormula,num_exp);
				ret=ExpCalAmt(num_exp, &dExpCalAmt);
				if(ret)
				{
					writelog(LOG_ERR,"formula[%s]num_exp[%s]",sFormula,num_exp);
					return E_EXP_CFG;
				}
				writelog(LOG_ERR,"formula[%s]num_exp[%s]amt[%lf]",sFormula,num_exp,dExpCalAmt);
				break;
		}
		*/
		//根据公式计算发生额
		ret=VarExp2NumExp(IA->dArrInAmt,IA->iArrInFeeSwitch,sFormula,num_exp);
		if(ret)
		{
			writelog(LOG_ERR,"ret[%d]txcode[%d]txtype[%d]formula[%s]",ret,IA->iTradeNo, iTxType,sFormula);
			return E_EXP_CFG;
		}
//		writelog(LOG_DEBUG,"formula[%s]num_exp[%s]",sFormula,num_exp);
		ret=ExpCalAmt(num_exp, &dExpCalAmt);
		if(ret)
		{
			writelog(LOG_ERR,"formula[%s]num_exp[%s]",sFormula,num_exp);
			return E_EXP_CFG;
		}
		dExpCalAmt=D4U5(dExpCalAmt,2);
//		writelog(LOG_DEBUG,"formula[%s]num_exp[%s]amt[%.4lf]",sFormula,num_exp,dExpCalAmt);
		//如果金额为0则continue
		if(amtcmp(dExpCalAmt,0)==0)
		{
			continue;
		}
		else if(amtcmp(dExpCalAmt,0)<0)
		{
			//如果不是冲正交易则不允许金额小于0
			if(ACC_TYPE_NORMAL == IA->iTxFlag)
			{
				writelog(LOG_DEBUG,"交易名称[%s]当前交易金额[%.4lf]",CfgSplit.ArrCfgsplit[iTxType].txname,dExpCalAmt);
				if(IA->pVoidPointer != NULL)
				{
					sprintf(IA->pVoidPointer,"%.2lf",dExpCalAmt);
				}
				return E_AMT_LACK;
			}
		}
		else
		{
			//冲正交易不允许金额大于0
			if(ACC_TYPE_RUSH == IA->iTxFlag)
			{
				writelog(LOG_DEBUG,"交易名称[%s]当前交易金额[%.4lf]",CfgSplit.ArrCfgsplit[iTxType].txname,dExpCalAmt);
				return E_INPUT_AMT;
			}
		}
		//类型为0的交易是用来检查输入金额是否有错误
		if(0==iTxType)
		{
			writelog(LOG_DEBUG,"交易名称[%s]当前交易金额[%.4lf]",CfgSplit.ArrCfgsplit[iTxType].txname,dExpCalAmt);
			return E_INPUT_AMT;
		}
		memset(sIdxDbActNo,0,sizeof(sIdxDbActNo));
		memset(sIdxCrActNo,0,sizeof(sIdxCrActNo));
		memset(&tTradelogDb, 0, sizeof(tTradelogDb));
		memset(&tTradelogCr, 0, sizeof(tTradelogCr));

		switch (CfgSplit.ArrCfgsplit[iTxType].dbflag)
		{
		case TYPE_INPUT:
			ret=GetValueFromFmtBuf(CfgFee.ArrCfgFee[idxTxCfg].idxdbactno_list,",",config_cnt,sIdxDbActNo);
			if(ret)
			{
				writelog(LOG_ERR, "TxCode[%d]FeeType[%d]idxdbactno_list[%s]",IA->iTradeNo,IA->iFeeType,CfgFee.ArrCfgFee[idxTxCfg].idxdbactno_list);
				return E_ACTNO_IDX_NOT_CFG;		//交易未配置
			}
			idx=atoi(sIdxDbActNo);
			if(idx<0)
				return E_ACTNO_IDX_CFG;
			strcpy(tTradelogDb.act_id, IA->sArrInActno[idx]);	//借方账号
			break;
		case TYPE_CONFIG:
			strcpy(tTradelogDb.act_id, CfgSplit.ArrCfgsplit[iTxType].dbactno);
			break;
		default:
			writelog(LOG_ERR, " TxType=[%d]",iTxType,CfgSplit.ArrCfgsplit[iTxType].dbflag);
			return E_DB_TRADEACT_R;
		}
		//修改借方帐户余额
		tTradelogDb.op_fee = dExpCalAmt;			//借方发生额
		memset(&tAccountDb, 0, sizeof(tAccountDb));
		ret = DB_t_aif_account_read_lock_by_cur_and_account_id(tTradelogDb.act_id, &tAccountDb);
		if (ret)
		{
			writelog(LOG_ERR, "read account err[%d]act_id[%s] ", ret, tTradelogDb.act_id);
			if (DB_NOTFOUND == ret)
				return E_ACTNO_NOT_EXIST;
			else
				return E_DB_ACCOUNT_R;
		}
		if(tAccountDb.current_state == ACCOUNTSTAT_LOGOUT)
		{
			writelog(LOG_ERR, "read account err[%d]act_id[%s]", E_ACTNO_LOGOUT, tAccountDb.account_id);
			return E_ACTNO_LOGOUT;
		}
		if(CfgSplit.ArrCfgsplit[iTxType].dbsubno[0]!=0)
		{
			if(strcmp(tAccountDb.subno,CfgSplit.ArrCfgsplit[iTxType].dbsubno)!=0)
			{
				DB_t_aif_account_free_lock_cur();
				writelog(LOG_ERR,"tradecode config_cnt[%d]TxType[%d]act_id[%s] tAccount.subno[%s]config dbsubno[%s]",config_cnt,iTxType,tAccountDb.account_id,tAccountDb.subno,CfgSplit.ArrCfgsplit[iTxType].dbsubno);
				return E_SPLIT_CFG;
			}
		}
		strcpy(tTradelogDb.subno,tAccountDb.subno);		//借方科目号
	//	writelog(LOG_DEBUG,"debit No[%d]account[%s]account.cur_bala[%lf]cur_freebala[%lf]cur_frozebala[%lf]amt[%lf]",i,account.account_id,account.cur_bala,account.cur_freebala,account.cur_frozebala,tTradelogDb.op_fee);
		idxSubCfg=GetIndexSubjectCfgBySubNo(tAccountDb.subno);
		if(idxSubCfg<0)
		{
			writelog(LOG_ERR, "GetIndexSubjectCfgBySubNo[%d] ",tAccountDb.subno);
			DB_t_aif_account_free_lock_cur();
			return E_DB_SUBJECT_N;
		}
		if (SUBTYPE_FUND== CfgSubject.ArrSubject[idxSubCfg].subtype|| SUBTYPE_COST== CfgSubject.ArrSubject[idxSubCfg].subtype )
		{
			tAccountDb.cur_bala = D4U5(tAccountDb.cur_bala+ tTradelogDb.op_fee,6);
			tAccountDb.cur_freebala = D4U5(tAccountDb.cur_freebala+ tTradelogDb.op_fee,6);
			db_amt_flag=1;
		}
		else
		{
			db_amt_flag=-1;
			if(strncmp(tAccountDb.subno,"201",3)==0)
			{
				//消费时从冻结金额中扣除搭伙费
				switch(CfgSplit.ArrCfgsplit[iTxType].fundtype)
				{
					case FUNDTYPE_BOARD://搭伙费
						//如果搭伙费不足,则只扣账户上剩余的搭伙费
						if(amtcmp(tAccountDb.cur_frozebala,0)<=0)
						{
							//如果搭伙费为负值或0,则不扣
							continue;
						}
						if(amtcmp(tAccountDb.cur_frozebala,tTradelogDb.op_fee)<0)
						{
							dExpCalAmt=tAccountDb.cur_frozebala;
							tTradelogDb.op_fee = dExpCalAmt;		//借方发生额
						}
						tAccountDb.cur_bala =D4U5(tAccountDb.cur_bala- tTradelogDb.op_fee,6);			//总余额
						tAccountDb.cur_frozebala = D4U5(tAccountDb.cur_frozebala - tTradelogDb.op_fee,6);
						break;
					default:
						tAccountDb.cur_bala =D4U5(tAccountDb.cur_bala- tTradelogDb.op_fee,6);			//总余额
						tAccountDb.cur_freebala =D4U5(tAccountDb.cur_freebala-tTradelogDb.op_fee,6);	//可用余额
						//更新卡余额
						if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)
						{
							if(amtcmp(dOutCardBala,0)>=0)
							{
								tAccountDb.card_balance=dOutCardBala;					//卡余额
								if(IA->iTxCnt>0)
									tAccountDb.consume_count=IA->iTxCnt;			//消费次数增加
							}
							else if(amtcmp(dInCardBala,0)>=0)
							{
								//有入卡值,没有出卡值,计算出卡值,卡余额
								dCardBala = dCardBala - D4U5(tTradelogDb.op_fee,2);	//卡余额
								IA->dOutCardBala=D4U5(dCardBala,2);
								tAccountDb.card_balance=IA->dOutCardBala;							//账户卡余额
 								if(IA->iTxCnt>0)
									tAccountDb.consume_count=IA->iTxCnt;
							}
						}
						else if(USE_CARD_TYPE_OFFLINE==IA->iUseCardFlag)
						{
							if(tAccountDb.consume_count<IA->iTxCnt)
							{
								if(amtcmp(dOutCardBala,0)>=0)
								{
									tAccountDb.card_balance=dOutCardBala;
									if(IA->iTxCnt>0)
										tAccountDb.consume_count=IA->iTxCnt;			//消费次数增加
								}
								else if(amtcmp(dInCardBala,0)>=0)
								{
									//有入卡值,没有出卡值,计算出卡值,卡余额
									dCardBala = dCardBala - D4U5(tTradelogDb.op_fee,2);	//卡余额
									IA->dOutCardBala=D4U5(dCardBala,2);
									tAccountDb.card_balance=IA->dOutCardBala;							//账户卡余额
	 								if(IA->iTxCnt>0)
										tAccountDb.consume_count=IA->iTxCnt;
								}
							}
							//当前交易不是最近一次交易,有入卡值,只计算出卡值
							else if((amtcmp(dInCardBala,0)>=0)&&(amtcmp(dOutCardBala,0)<0))
							{
								//计算出卡值
								dCardBala = dCardBala - D4U5(tTradelogDb.op_fee,2);		//卡余额
								IA->dOutCardBala=D4U5(dCardBala,2);
	 						}
						}
						break;
				}
			}
			else
			{
				/*
				//对押金单独处理
				switch(iTxType)
				{
					case TXTYPE_RETURN_DEPOSIT:		//退押金
					case TXTYPE_DEDUCT_DEPOSIT:	//扣押金
						memset(&tCard,0,sizeof(tCard));
						if(IA->iCardNo<1)
						{
							return E_INPUT_CARDNO_CANNOT_NULL;
						}
						ret=DB_t_pif_card_read_lock_by_cur_and_card_id(IA->iCardNo,&tCard);
						if(ret)
						{
							if(DB_NOTFOUND==ret)
								return E_CARDNO_NOT_EXIST;
							else
								return E_DB_CARD_R;
						}
						tCard.deposit_fee=0;
						ret=DB_t_pif_card_update_lock_by_cur(&tCard);
						if(ret)
						{
							if(DB_NOTFOUND==ret)
								return E_CARDNO_NOT_EXIST;
							else
								return E_DB_CARD_U;
						}
						DB_t_pif_card_free_lock_by_cur();
						break;
				}
				*/
				tAccountDb.cur_bala =D4U5(tAccountDb.cur_bala - tTradelogDb.op_fee,6);
				tAccountDb.cur_freebala =D4U5(tAccountDb.cur_freebala- tTradelogDb.op_fee,6);
			}

		}
		//判断余额是否小于0,不允许透支,资产类帐户除外
		//应该是负债类账户
		if(strncmp(tAccountDb.subno,"2",1)==0)
		{
			if(amtcmp(tAccountDb.cur_bala,0)<0||amtcmp(tAccountDb.cur_freebala,0)<0)
			{
				writelog(LOG_ERR,"host serialno[%d]debit No[%d]account[%s]account.cur_bala[%lf]cur_freebala[%lf]cur_frozebala[%lf]amt[%lf]",IA->iSerialNo,i,tAccountDb.account_id,tAccountDb.cur_bala,tAccountDb.cur_freebala,tAccountDb.cur_frozebala,tTradelogDb.op_fee);
				DB_t_aif_account_free_lock_cur();
				return E_BALANCE_SHORTAGE;
			}
		}
		tTradelogDb.new_fee    = tAccountDb.cur_bala;						//借方帐户总余额
		tTradelogDb.cur_frozebala=tAccountDb.cur_frozebala;					//冻结金额
		ret = DB_t_aif_account_update_lock_by_cur(&tAccountDb);
		if (ret)
		{
			writelog(LOG_ERR, "update account err[%d] account[%s]", ret,tAccountDb.account_id);
			if (DB_NOTFOUND == ret)
				return E_ACTNO_NOT_EXIST;
			else
				return E_DB_ACCOUNT_U;
		}
		DB_t_aif_account_free_lock_cur();
		//######################################################
		//处理贷方账号1
		switch (CfgSplit.ArrCfgsplit[iTxType].crflag)
		{
		case TYPE_INPUT:
			ret=GetValueFromFmtBuf(CfgFee.ArrCfgFee[idxTxCfg].idxcractno_list,",",config_cnt,sIdxCrActNo);
			if(ret)
			{
				writelog(LOG_ERR, "TxCode[%d]FeeType[%d]idxcractno_list[%s]",IA->iTradeNo,IA->iFeeType,CfgFee.ArrCfgFee[idxTxCfg].idxcractno_list);
				return E_ACTNO_IDX_NOT_CFG;		//交易未配置
			}
			idx=atoi(sIdxCrActNo);
			if(idx<0)
				return E_ACTNO_IDX_CFG;
			strcpy(tTradelogCr.act_id, IA->sArrInActno[idx]);	//借方账号
			break;
		case TYPE_CONFIG:
			strcpy(tTradelogCr.act_id, CfgSplit.ArrCfgsplit[iTxType].cractno);
			break;
		default:
			writelog(LOG_ERR, " TxType=[%d]",iTxType,CfgSplit.ArrCfgsplit[iTxType].crflag);
			return E_DB_TRADEACT_R;
		}
		//修改贷方帐户余额
		tTradelogCr.op_fee =dExpCalAmt;			//贷方发生额

		memset(&tAccountCr, 0, sizeof(tAccountCr));
		ret = DB_t_aif_account_read_lock_by_cur_and_account_id(tTradelogCr.act_id, &tAccountCr);
		if (ret)
		{
			writelog(LOG_ERR, "read account err[%d]act_id[%s]", ret, tTradelogCr.act_id);
			if (DB_NOTFOUND == ret)
				return E_ACTNO_NOT_EXIST;
			else
				return E_DB_ACCOUNT_R;
		}
		if(tAccountCr.current_state == ACCOUNTSTAT_LOGOUT)
		{
			writelog(LOG_ERR, "read account err[%d]act_id[%s]", E_ACTNO_LOGOUT, tAccountCr.account_id);
			return E_ACTNO_LOGOUT;
		}
		if(CfgSplit.ArrCfgsplit[iTxType].crsubno[0]!=0)
		{
			if(strcmp(tAccountCr.subno,CfgSplit.ArrCfgsplit[iTxType].crsubno)!=0)
			{
				writelog(LOG_ERR,"tradecode config_cnt[%d]TxType[%d]act_id[%s] tAccount.subno[%s]config dbsubno[%s]",config_cnt,iTxType,tAccountCr.account_id,tAccountCr.subno,CfgSplit.ArrCfgsplit[iTxType].crsubno);
				DB_t_aif_account_free_lock_cur();
				return E_SPLIT_CFG;
			}
		}
		strcpy(tTradelogCr.subno, tAccountCr.subno);			//贷方科目号
//		writelog(LOG_DEBUG,"credit No[%d]tAccount[%s]account.cur_bala[%lf]cur_freebala[%lf]cur_frozebala[%lf]amt[%lf]",i,account.account_id,account.cur_bala,account.cur_freebala,account.cur_frozebala,ArrTradelog[i+1].op_fee);

		idxSubCfg=GetIndexSubjectCfgBySubNo(tAccountCr.subno);
		if(idxSubCfg<0)
		{
			writelog(LOG_ERR, "GetIndexSubjectCfgBySubNo[%d] ", tAccountCr.subno);
			DB_t_aif_account_free_lock_cur();
			return E_DB_SUBJECT_N;
		}
		if (SUBTYPE_FUND== CfgSubject.ArrSubject[idxSubCfg].subtype|| SUBTYPE_COST== CfgSubject.ArrSubject[idxSubCfg].subtype )
		{
			tAccountCr.cur_bala =D4U5(tAccountCr.cur_bala- tTradelogCr.op_fee,6);							//当前总余额
			tAccountCr.cur_freebala =D4U5(tAccountCr.cur_freebala-tTradelogCr.op_fee,6);							//当前可用余额
			cr_amt_flag=-1;
		}
		else
		{
			cr_amt_flag=1;
			//如果帐户类型为个人,则计算搭伙费，主要是充值使用
			if(strncmp(tAccountCr.subno,"201",3)==0)
			{
				tAccountCr.cur_bala =D4U5(tAccountCr.cur_bala+ tTradelogCr.op_fee,6);				//总余额
				switch(CfgSplit.ArrCfgsplit[iTxType].fundtype)
				{
					case FUNDTYPE_BOARD:						//搭伙费
						tAccountCr.cur_frozebala =D4U5(tAccountCr.cur_frozebala+ tTradelogCr.op_fee,6);
						break;
					default:
						tAccountCr.cur_freebala =D4U5(tAccountCr.cur_freebala+ tTradelogCr.op_fee,6);	//可用余额
						//更新卡余额
						if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)
						{
							if(IA->iTxCnt>0)
								tAccountCr.consume_count=IA->iTxCnt;			//消费次数增加
							else
								return E_INPUT_CARD_TXCNT;
							if(amtcmp(dOutCardBala,0)>=0)
							{
								tAccountCr.card_balance=dOutCardBala;					//卡余额
							}
							else if(amtcmp(dInCardBala,0)>=0)
							{
								//有入卡值,没有出卡值,计算出卡值,卡余额
								dCardBala = dCardBala + D4U5(tTradelogDb.op_fee,2);	//卡余额
								IA->dOutCardBala=D4U5(dCardBala,2);
								tAccountCr.card_balance=IA->dOutCardBala;							//账户卡余额
							}
						}
						else if(USE_CARD_TYPE_OFFLINE==IA->iUseCardFlag)
						{
							if(tAccountCr.consume_count<IA->iTxCnt)
							{
								if(IA->iTxCnt>0)
									tAccountCr.consume_count=IA->iTxCnt;			//消费次数增加
								if(amtcmp(dOutCardBala,0)>=0)
								{
									tAccountCr.card_balance=dOutCardBala;
								}
								else if(amtcmp(dInCardBala,0)>=0)
								{
									//有入卡值,没有出卡值,计算出卡值,卡余额
									dCardBala = dCardBala + D4U5(tTradelogDb.op_fee,2);	//卡余额
									IA->dOutCardBala=D4U5(dCardBala,2);
									tAccountCr.card_balance=IA->dOutCardBala;							//账户卡余额
								}
							}
							//当前交易不是最近一次交易,有入卡值,只计算出卡值
							else if((amtcmp(dInCardBala,0)>=0)&&(amtcmp(dOutCardBala,0)<0))
							{
								//计算出卡值
								dCardBala = dCardBala + D4U5(tTradelogDb.op_fee,2);		//卡余额
								IA->dOutCardBala=D4U5(dCardBala,2);
	 						}
						}
						break;
				}
			}
			else
			{
				//对押金单独处理
				switch(iTxType)
				{
					case TXTYPE_TOLL_DEPOSIT:		//收押金
					case TXTYPE_TOLL_DEPOSIT_BILL:
					case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
						memset(&tCard,0,sizeof(tCard));
						if(IA->iCardNo<1)
						{
							return E_INPUT_CARDNO_CANNOT_NULL;
						}
						ret=DB_t_pif_card_read_lock_by_cur_and_card_id(IA->iCardNo,&tCard);
						if(ret)
						{
							if(DB_NOTFOUND==ret)
								return E_CARDNO_NOT_EXIST;
							else
								return E_DB_CARD_R;
						}
						tCard.deposit_fee=tTradelogCr.op_fee;
						ret=DB_t_pif_card_update_lock_by_cur(&tCard);
						if(ret)
						{
							if(DB_NOTFOUND==ret)
								return E_CARDNO_NOT_EXIST;
							else
								return E_DB_CARD_U;
						}
						DB_t_pif_card_free_lock_by_cur();
					default:
						break;
				}
				tAccountCr.cur_bala =D4U5(tAccountCr.cur_bala+tTradelogCr.op_fee,6);						//当前总余额
				tAccountCr.cur_freebala=D4U5(tAccountCr.cur_freebala+tTradelogCr.op_fee,6) ;					//当前可用余额
			}
		}
		//判断余额是否小于0,不允许透支,资产类帐户除外
		if(strncmp(tAccountCr.subno,"2",1)==0)
		{
			if(amtcmp(tAccountCr.cur_bala,0)<0||amtcmp(tAccountCr.cur_freebala,0)<0)
			{
				writelog(LOG_ERR,"host serialno[%d]credit No[%d+1]account[%s]account.cur_bala[%lf]cur_freebala[%lf]cur_frozebala[%lf]amt[%lf]",IA->iSerialNo,i,tAccountCr.account_id,tAccountCr.cur_bala,tAccountCr.cur_freebala,tAccountCr.cur_frozebala,tTradelogDb.op_fee);
				DB_t_aif_account_free_lock_cur();
				return E_BALANCE_SHORTAGE;
			}
		}
		tTradelogCr.new_fee = tAccountCr.cur_bala;			//贷方帐户余额
		tTradelogCr.cur_frozebala=tAccountCr.cur_frozebala;		//冻结金额
		ret = DB_t_aif_account_update_lock_by_cur(&tAccountCr);
		if (ret)
		{
			writelog(LOG_ERR, "update account err[%d] account[%s]", ret,tAccountCr.account_id);
			if (DB_NOTFOUND == ret)
				return E_ACTNO_NOT_EXIST;
			else
				return E_DB_ACCOUNT_U;
		}
		DB_t_aif_account_free_lock_cur();
		//增加借方分录流水
		tTradelogDb.maindevice_id = IA->iMainDevId;		//工作站标识
		tTradelogDb.device_id= IA->iDevId;				//终端设备ID
		tTradelogDb.serino = IA->iSerialNo;				//流水号
		tTradelogDb.seri_type= IA->iTradeNo;				//交易码
		tTradelogDb.fee_type=iTxType;						//分录序号
		tTradelogDb.warrant_type = iVocType;				//凭证类型
		strcpy(tTradelogDb.warrant_no, sVocNo);				//凭证号
		strcpy(tTradelogDb.comments, CfgSplit.ArrCfgsplit[iTxType].txname);	//摘要
		strcpy(tTradelogDb.operate_date, IA->sTxDate);		//交易日期
		strcpy(tTradelogDb.operate_time, IA->sTxTime);		//交易时间
		strcpy(tTradelogDb.collect_date,IA->sTxCollectDate);	//采集日期
		strcpy(tTradelogDb.collect_time,IA->sTxCollectTime);	//采集时间
		strcpy(tTradelogDb.enteract_date,IA->sTxAccDate);	//记账日期
		strcpy(tTradelogDb.enteract_time,IA->sTxAccTime);	//记账时间
		strcpy(tTradelogDb.record_oper, IA->sMdeOper);	//录入操作员
		strcpy(tTradelogDb.write_oper, IA->sChkOper);		//复核记账员
		tTradelogDb.outorin = DBCR_DEBIT;					//借方标志
		strcpy(tTradelogDb.other_actid, tTradelogCr.act_id);		//对方账号
		strcpy(tTradelogDb.other_subno, tTradelogCr.subno);	//对方科目
		++IA->iSubIndex;
		tTradelogDb.annex = IA->iSubIndex;
		ret = DB_t_tif_tradelog_add(&tTradelogDb);
		if (ret)
		{
			writelog(LOG_ERR, "add ArrTradelog err[%d] ", ret);
			return E_DB_TRADELOG_I;
		}
		//增加贷方分录流水
		tTradelogCr.maindevice_id = IA->iMainDevId;		//工作站标识
		tTradelogCr.device_id= IA->iDevId;				//终端设备ID
		tTradelogCr.serino = IA->iSerialNo;				//流水号
		tTradelogCr.seri_type = IA->iTradeNo;				//交易码
		tTradelogCr.fee_type=iTxType;						//分录序号
		tTradelogCr.warrant_type = iVocType;					//凭证类型
		strcpy(tTradelogCr.warrant_no, sVocNo);				//凭证号
		strcpy(tTradelogCr.comments,  CfgSplit.ArrCfgsplit[iTxType].txname);//摘要
		strcpy(tTradelogCr.operate_date, IA->sTxDate);		//交易日期
		strcpy(tTradelogCr.operate_time, IA->sTxTime);		//交易时间
		strcpy(tTradelogCr.collect_date,IA->sTxCollectDate);	//采集日期
		strcpy(tTradelogCr.collect_time,IA->sTxCollectTime);	//采集时间
		strcpy(tTradelogCr.enteract_date,tTradelogDb.enteract_date);//记账日期
		strcpy(tTradelogCr.enteract_time,tTradelogDb.enteract_time);//记账时间
		strcpy(tTradelogCr.record_oper, IA->sMdeOper);		//录入操作员
		strcpy(tTradelogCr.write_oper, IA->sChkOper);		//复核操作员
		tTradelogCr.outorin = DBCR_CREDIT;					//贷方标志
		strcpy(tTradelogCr.other_actid, tTradelogDb.act_id);		//对方账号
		strcpy(tTradelogCr.other_subno, tTradelogDb.subno);	//对方科目
		tTradelogCr.annex = IA->iSubIndex;
		
		ret = DB_t_tif_tradelog_add(&tTradelogCr);
		if (ret)
		{
			writelog(LOG_ERR, "add ArrTradelog err[%d] serial[%d]act[%s]annex[%d]", 
				ret,tTradelogCr.serino,tTradelogCr.act_id,tTradelogCr.annex);
			return E_DB_TRADELOG_I;
		}
		IA->dArrOutAmt[config_cnt]=dExpCalAmt;
		IA->iArrOutTxType[config_cnt]=iTxType;
		strcpy(IA->sArrOutTxName[config_cnt],CfgSplit.ArrCfgsplit[iTxType].txname);
		IA->iOutTxTypeCnt=config_cnt;
		//##############################################################
		if(IA->pVoidPointer!=NULL)
		{
			if(db_amt_flag>0)
				sprintf(IA->pVoidPointer+strlen(IA->pVoidPointer),"%s:余额增加%.2lf元", tAccountDb.cut_name,dExpCalAmt);
			else
				sprintf(IA->pVoidPointer+strlen(IA->pVoidPointer),"%s:余额减少%.2lf元", tAccountDb.cut_name,dExpCalAmt);
			if(cr_amt_flag>0)
				sprintf(IA->pVoidPointer+strlen(IA->pVoidPointer)," %s:余额增加%.2lf元",tAccountCr.cut_name,dExpCalAmt);
			else
				sprintf(IA->pVoidPointer+strlen(IA->pVoidPointer)," %s:余额减少%.2lf元", tAccountCr.cut_name,dExpCalAmt);
		}
	}
	//如果有入卡值但没有出卡值，则出卡值就是入卡值
	if(amtcmp(IA->dOutCardBala,0)<0)
	{
		if(amtcmp(IA->dInCardBala,0)>=0)
			IA->dOutCardBala=IA->dInCardBala;
	}
//	writelog(LOG_DEBUG,"serino[%d]IA->dInCardBala[%lf]IA->dOutCardBala[%lf]IA->iTxCnt[%d]",IA->iSerialNo,IA->dInCardBala,IA->dOutCardBala,IA->iTxCnt);
	return 0;
}
