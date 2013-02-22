/* --------------------------------------------
 * ��������: account.c
 * ��������: 2004-08-01
 * ��������: �Ž�
 * �汾��Ϣ: 1.0
 * ������: һ��ͨ������
 * --------------------------------------------
 * �޸�����:2005-07-14
 * �޸���Ա:�Ž�
 * �޸�����:�޸����� ����
 * �汾��Ϣ:2.0
 * ��ע��Ϣ:
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
#define MAXNUM_SUBJECT  		30		//����Ŀ����
#define MAXNUM_CFGTXFEE		60		//��������������
#define MAXNUM_CFGSPLIT		90		//��������͸���

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

//��ʼ����¼����
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
			return E_BEYOND_MAXNUM_SPLITCFG;	//������¼�����
		memcpy(&CfgSplit.ArrCfgsplit[tCfgsplit.txtype],&tCfgsplit,sizeof(tCfgsplit));
		CfgSplit.num++;
	}
	InitAccFlag=1;
	return 0;
}

//��ʼ����������
int InitTxFeeCfg(int tx_code)
{
	int ret=-1;
//  static      int  	InitTxFlag=0;

//	if(InitTxFlag)
//		return 0;

	memset(&CfgFee,0,sizeof(CfgFee));

	ret=DB_t_tif_cfgtxfee_open_select_by_c1_and_tx_code(tx_code);
	while(1)
	{
		//ret=DB_t_tif_cfgtxfee_fetch_select_by_c0((T_t_tif_cfgtxfee*)&CfgFee.ArrCfgFee[CfgFee.num]);
		ret=DB_t_tif_cfgtxfee_fetch_select_by_c1((T_t_tif_cfgtxfee*)&CfgFee.ArrCfgFee[CfgFee.num]);
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
			return E_BEYOND_MAXNUM_TRADECODE;	//���������ó��������
	}
	//InitTxFlag=1;
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

//��ʼ����Ŀ����
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
	int iTxType=0;		//��������
	char num_exp[256]="";
	char sFee[256]="";
	char sFormula[256]="";
	char sIdxDbActNo[4]="";
	char sIdxCrActNo[4]="";
	char sVocNo[21] = "";
	double dExpCalAmt=0;
	int iVocType = VOCTYPE_DEFALUT;
	char * pMessage = (char*)IA->pVoidPointer;

	int i = 0;
//	int idx=0;
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

	ret=InitTxFeeCfg(IA->iTradeNo);
	if(ret)
		return ret;
	ret=InitSplitCfg();
	if(ret)
		return ret;
	ret=InitSubjectCfg();
	if(ret)
		return ret;

	//���ݽ�����Ϳͻ��շ������������ñ�
	if(IA->iFeeType<1)
	{
		return E_CUSTOMER_NO_FEE_TYPE;
	}
	idxTxCfg=GetIndexTxFeeCfgByTxCode(IA->iTradeNo,IA->iFeeType);
	if(idxTxCfg<0)
	{
		//���û��ȡĬ��ֵ
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
		//��ʼ�����շѼ���
		ret=GetValueFromFmtBuf(CfgFee.ArrCfgFee[idxTxCfg].fee_list,",",config_cnt,sFee);
		if(ret)
		{
			if(1==config_cnt)
			{
				writelog(LOG_ERR, "TxCode[%d]FeeType[%d]fee_list[%s]",IA->iTradeNo,IA->iFeeType,CfgFee.ArrCfgFee[idxTxCfg].fee_list);
				return E_TXCODE_NOT_CONFIG;		//����δ����
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
			return E_EXP_NOT_CFG;		//����δ����
		}
//		writelog(LOG_DEBUG,"formula_list[%s]Formula[%s]",CfgFee.ArrCfgFee[idxTxCfg].formula_list,sFormula);
		//�õ��շ�����
		/*
		switch(iTxType)
		{
//			case TXTYPE_TOLL_DEPOSIT:		//��Ѻ��
			case TXTYPE_RETURN_DEPOSIT:		//��Ѻ��
			case TXTYPE_DEDUCT_DEPOSIT:	//��Ѻ��
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
		//���ݹ�ʽ���㷢����
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
		//������Ϊ0��continue
		if(amtcmp(dExpCalAmt,0)==0)
		{
			continue;
		}
		else if(amtcmp(dExpCalAmt,0)<0)
		{
			//������ǳ���������������С��0
			if(ACC_TYPE_NORMAL == IA->iTxFlag)
			{
				writelog(LOG_DEBUG,"��������[%s]��ǰ���׽��[%.4lf]",CfgSplit.ArrCfgsplit[iTxType].txname,dExpCalAmt);
				if(IA->pVoidPointer != NULL)
				{
					sprintf((char*)IA->pVoidPointer,"%.2lf",dExpCalAmt);
				}
				return E_AMT_LACK;
			}
		}
		else
		{
			//�������ײ����������0
			if(ACC_TYPE_RUSH == IA->iTxFlag)
			{
				writelog(LOG_DEBUG,"��������[%s]��ǰ���׽��[%.4lf]",CfgSplit.ArrCfgsplit[iTxType].txname,dExpCalAmt);
				return E_INPUT_AMT;
			}
		}
		//����Ϊ0�Ľ�������������������Ƿ��д���
		if(0==iTxType)
		{
			writelog(LOG_DEBUG,"��������[%s]��ǰ���׽��[%.4lf]",CfgSplit.ArrCfgsplit[iTxType].txname,dExpCalAmt);
			return E_INPUT_AMT;
		}
		memset(sIdxDbActNo,0,sizeof(sIdxDbActNo));
		memset(sIdxCrActNo,0,sizeof(sIdxCrActNo));
		memset(&tTradelogDb, 0, sizeof(tTradelogDb));
		memset(&tTradelogCr, 0, sizeof(tTradelogCr));

		switch (CfgSplit.ArrCfgsplit[iTxType].dbflag)
		{
		case TYPE_INPUT:
			/*
			ret=GetValueFromFmtBuf(CfgFee.ArrCfgFee[idxTxCfg].idxdbactno_list,",",config_cnt,sIdxDbActNo);
			if(ret)
			{
				writelog(LOG_ERR, "TxCode[%d]FeeType[%d]idxdbactno_list[%s]",IA->iTradeNo,IA->iFeeType,CfgFee.ArrCfgFee[idxTxCfg].idxdbactno_list);
				return E_ACTNO_IDX_NOT_CFG;		//����δ����
			}
			idx=atoi(sIdxDbActNo);
			if(idx<0)
				return E_ACTNO_IDX_CFG;
			strcpy(tTradelogDb.act_id, IA->sArrInActno[idx]);	//�跽�˺�
			*/
			if(TXCODE_CARD_DBCR!=IA->iTradeNo)
			{
				if(strcmp(CfgSplit.ArrCfgsplit[iTxType].dbsubno,CfgSplit.ArrCfgsplit[iTxType].crsubno)!=0)
				{
					if(strncmp(CfgSplit.ArrCfgsplit[iTxType].dbsubno,SUBJECT_INDIVIDUALSAVING,3)==0)
						strcpy(tTradelogDb.act_id, IA->sArrInActno[0]);	//�跽�˺�(person)
					else if(strncmp(CfgSplit.ArrCfgsplit[iTxType].dbsubno,SUBJECT_SHOPSAVING,3)==0)
						strcpy(tTradelogDb.act_id, IA->sArrInActno[1]);	//�跽�˺�(shop)
				}
				else
				{
					strcpy(tTradelogDb.act_id, IA->sArrInActno[0]);	//�跽�˺�(person)						
				}
			}
			else
			{
				strcpy(tTradelogDb.act_id, IA->sArrInActno[0]);	//�跽�˺�(person)
			}
			break;
		case TYPE_CONFIG:
			strcpy(tTradelogDb.act_id, CfgSplit.ArrCfgsplit[iTxType].dbactno);
			break;
		default:
			writelog(LOG_ERR, " TxType=[%d]",iTxType,CfgSplit.ArrCfgsplit[iTxType].dbflag);
			return E_DB_TRADEACT_R;
		}
		//�޸Ľ跽�ʻ����
		tTradelogDb.op_fee = dExpCalAmt;			//�跽������
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
			DB_t_aif_account_free_lock_cur();
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
		strcpy(tTradelogDb.subno,tAccountDb.subno);		//�跽��Ŀ��
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
				//����ʱ�Ӷ������п۳�����
				switch(CfgSplit.ArrCfgsplit[iTxType].fundtype)
				{
					case FUNDTYPE_BOARD://����
						//������Ѳ���,��ֻ���˻���ʣ��Ĵ���
						if(amtcmp(tAccountDb.cur_frozebala,0)<=0)
						{
							//�������Ϊ��ֵ��0,�򲻿�
							DB_t_aif_account_free_lock_cur();
							continue;
						}
						if(amtcmp(tAccountDb.cur_frozebala,tTradelogDb.op_fee)<0)
						{
							dExpCalAmt=tAccountDb.cur_frozebala;
							tTradelogDb.op_fee = dExpCalAmt;		//�跽������
						}
						tAccountDb.cur_bala =D4U5(tAccountDb.cur_bala- tTradelogDb.op_fee,6);			//�����
						tAccountDb.cur_frozebala = D4U5(tAccountDb.cur_frozebala - tTradelogDb.op_fee,6);
						break;
					default:
						tAccountDb.cur_bala =D4U5(tAccountDb.cur_bala- tTradelogDb.op_fee,6);			//�����
						tAccountDb.cur_freebala =D4U5(tAccountDb.cur_freebala-tTradelogDb.op_fee,6);	//�������
						//���¿����
						if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)
						{
							if(amtcmp(dOutCardBala,0)>=0)
							{
								tAccountDb.card_balance=dOutCardBala;					//�����
								if(IA->iTxCnt>0)
									tAccountDb.consume_count=IA->iTxCnt;			//���Ѵ�������
							}
							else if(amtcmp(dInCardBala,0)>=0)
							{
								//���뿨ֵ,û�г���ֵ,�������ֵ,�����
								dCardBala = dCardBala - D4U5(tTradelogDb.op_fee,2);	//�����
								IA->dOutCardBala=D4U5(dCardBala,2);
								tAccountDb.card_balance=IA->dOutCardBala;							//�˻������
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
										tAccountDb.consume_count=IA->iTxCnt;			//���Ѵ�������
								}
								else if(amtcmp(dInCardBala,0)>=0)
								{
									//���뿨ֵ,û�г���ֵ,�������ֵ,�����
									dCardBala = dCardBala - D4U5(tTradelogDb.op_fee,2);	//�����
									IA->dOutCardBala=D4U5(dCardBala,2);
									tAccountDb.card_balance=IA->dOutCardBala;							//�˻������
	 								if(IA->iTxCnt>0)
										tAccountDb.consume_count=IA->iTxCnt;
								}
							}
							//��ǰ���ײ������һ�ν���,���뿨ֵ,ֻ�������ֵ
							else if((amtcmp(dInCardBala,0)>=0)&&(amtcmp(dOutCardBala,0)<0))
							{
								//�������ֵ
								dCardBala = dCardBala - D4U5(tTradelogDb.op_fee,2);		//�����
								IA->dOutCardBala=D4U5(dCardBala,2);
	 						}
						}
						break;
				}
			}
			else
			{
				/*
				//��Ѻ�𵥶�����
				switch(iTxType)
				{
					case TXTYPE_RETURN_DEPOSIT:		//��Ѻ��
					case TXTYPE_DEDUCT_DEPOSIT:	//��Ѻ��
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
		//�ж�����Ƿ�С��0,������͸֧,�ʲ����ʻ�����
		//Ӧ���Ǹ�ծ���˻�
		if(strncmp(tAccountDb.subno,"2",1)==0)
		{
			if(amtcmp(tAccountDb.cur_bala,0)<0||amtcmp(tAccountDb.cur_freebala,0)<0)
			{
				writelog(LOG_ERR,"host serialno[%d]debit No[%d]account[%s]account.cur_bala[%lf]cur_freebala[%lf]cur_frozebala[%lf]amt[%lf]",IA->iSerialNo,i,tAccountDb.account_id,tAccountDb.cur_bala,tAccountDb.cur_freebala,tAccountDb.cur_frozebala,tTradelogDb.op_fee);
				DB_t_aif_account_free_lock_cur();
				return E_BALANCE_SHORTAGE;
			}
		}
		tTradelogDb.new_fee    = tAccountDb.cur_bala;						//�跽�ʻ������
		tTradelogDb.cur_frozebala=tAccountDb.cur_frozebala;					//������
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
		//��������˺�1
		switch (CfgSplit.ArrCfgsplit[iTxType].crflag)
		{
		case TYPE_INPUT:
			/*
			ret=GetValueFromFmtBuf(CfgFee.ArrCfgFee[idxTxCfg].idxcractno_list,",",config_cnt,sIdxCrActNo);
			if(ret)
			{
				writelog(LOG_ERR, "TxCode[%d]FeeType[%d]idxcractno_list[%s]",IA->iTradeNo,IA->iFeeType,CfgFee.ArrCfgFee[idxTxCfg].idxcractno_list);
				return E_ACTNO_IDX_NOT_CFG;		//����δ����
			}
			idx=atoi(sIdxCrActNo);
			if(idx<0)
				return E_ACTNO_IDX_CFG;
			strcpy(tTradelogCr.act_id, IA->sArrInActno[idx]);	//�����˺�
			*/
			if(TXCODE_CARD_DBCR!=IA->iTradeNo)
			{			
				if(strcmp(CfgSplit.ArrCfgsplit[iTxType].dbsubno,CfgSplit.ArrCfgsplit[iTxType].crsubno)!=0)
				{
					if(strncmp(CfgSplit.ArrCfgsplit[iTxType].crsubno,SUBJECT_INDIVIDUALSAVING,3)==0)
						strcpy(tTradelogCr.act_id, IA->sArrInActno[0]);	//�����˺�(person)
					else if(strncmp(CfgSplit.ArrCfgsplit[iTxType].crsubno,SUBJECT_SHOPSAVING,3)==0)
						strcpy(tTradelogCr.act_id, IA->sArrInActno[1]);	//�����˺�(shop)			
				}
				else
				{
					strcpy(tTradelogCr.act_id, IA->sArrInActno[1]);	//�����˺�(person)						
				}
			}
			else
			{
				strcpy(tTradelogCr.act_id, IA->sArrInActno[1]);	//�����˺�(person)						
			}
			break;
		case TYPE_CONFIG:
			strcpy(tTradelogCr.act_id, CfgSplit.ArrCfgsplit[iTxType].cractno);
			break;
		default:
			writelog(LOG_ERR, " TxType=[%d]",iTxType,CfgSplit.ArrCfgsplit[iTxType].crflag);
			return E_DB_TRADEACT_R;
		}
		//�޸Ĵ����ʻ����
		tTradelogCr.op_fee =dExpCalAmt;			//����������

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
			DB_t_aif_account_free_lock_cur();
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
		strcpy(tTradelogCr.subno, tAccountCr.subno);			//������Ŀ��
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
			tAccountCr.cur_bala =D4U5(tAccountCr.cur_bala- tTradelogCr.op_fee,6);							//��ǰ�����
			tAccountCr.cur_freebala =D4U5(tAccountCr.cur_freebala-tTradelogCr.op_fee,6);							//��ǰ�������
			cr_amt_flag=-1;
		}
		else
		{
			cr_amt_flag=1;
			//����ʻ�����Ϊ����,�������ѣ���Ҫ�ǳ�ֵʹ��
			if(strncmp(tAccountCr.subno,"201",3)==0)
			{
				tAccountCr.cur_bala =D4U5(tAccountCr.cur_bala+ tTradelogCr.op_fee,6);				//�����
				switch(CfgSplit.ArrCfgsplit[iTxType].fundtype)
				{
					case FUNDTYPE_BOARD:						//����
						tAccountCr.cur_frozebala =D4U5(tAccountCr.cur_frozebala+ tTradelogCr.op_fee,6);
						break;
					default:
						tAccountCr.cur_freebala =D4U5(tAccountCr.cur_freebala+ tTradelogCr.op_fee,6);	//�������
						//���¿����
						if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)
						{
							if(IA->iTxCnt>0)
								tAccountCr.consume_count=IA->iTxCnt;			//���Ѵ�������
							else
							{
								DB_t_aif_account_free_lock_cur();
								return E_INPUT_CARD_TXCNT;
							}
							if(amtcmp(dOutCardBala,0)>=0)
							{
								tAccountCr.card_balance=dOutCardBala;					//�����
							}
							else if(amtcmp(dInCardBala,0)>=0)
							{
								//���뿨ֵ,û�г���ֵ,�������ֵ,�����
								dCardBala = dCardBala + D4U5(tTradelogDb.op_fee,2);	//�����
								IA->dOutCardBala=D4U5(dCardBala,2);
								tAccountCr.card_balance=IA->dOutCardBala;							//�˻������
							}
						}
						else if(USE_CARD_TYPE_OFFLINE==IA->iUseCardFlag)
						{
							if(tAccountCr.consume_count<IA->iTxCnt)
							{
								if(IA->iTxCnt>0)
									tAccountCr.consume_count=IA->iTxCnt;			//���Ѵ�������
								if(amtcmp(dOutCardBala,0)>=0)
								{
									tAccountCr.card_balance=dOutCardBala;
								}
								else if(amtcmp(dInCardBala,0)>=0)
								{
									//���뿨ֵ,û�г���ֵ,�������ֵ,�����
									dCardBala = dCardBala + D4U5(tTradelogDb.op_fee,2);	//�����
									IA->dOutCardBala=D4U5(dCardBala,2);
									tAccountCr.card_balance=IA->dOutCardBala;							//�˻������
								}
							}
							//��ǰ���ײ������һ�ν���,���뿨ֵ,ֻ�������ֵ
							else if((amtcmp(dInCardBala,0)>=0)&&(amtcmp(dOutCardBala,0)<0))
							{
								//�������ֵ
								dCardBala = dCardBala + D4U5(tTradelogDb.op_fee,2);		//�����
								IA->dOutCardBala=D4U5(dCardBala,2);
	 						}
						}
						break;
				}
			}
			else
			{
				//��Ѻ�𵥶�����
				switch(iTxType)
				{
					case TXTYPE_TOLL_DEPOSIT:		//��Ѻ��
					case TXTYPE_TOLL_DEPOSIT_BILL:
					case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
						memset(&tCard,0,sizeof(tCard));
						if(IA->iCardNo<1)
						{
							DB_t_aif_account_free_lock_cur();
							return E_INPUT_CARDNO_CANNOT_NULL;
						}
						ret=DB_t_pif_card_read_lock_by_cur_and_card_id(IA->iCardNo,&tCard);
						if(ret)
						{
							DB_t_aif_account_free_lock_cur();
							if(DB_NOTFOUND==ret)
								return E_CARDNO_NOT_EXIST;
							else
								return E_DB_CARD_R;
						}
						tCard.deposit_fee=tTradelogCr.op_fee;
						ret=DB_t_pif_card_update_lock_by_cur(&tCard);
						if(ret)
						{
							DB_t_aif_account_free_lock_cur();
							if(DB_NOTFOUND==ret)
								return E_CARDNO_NOT_EXIST;
							else
								return E_DB_CARD_U;
						}
						DB_t_pif_card_free_lock_by_cur();
					default:
						break;
				}
				tAccountCr.cur_bala =D4U5(tAccountCr.cur_bala+tTradelogCr.op_fee,6);						//��ǰ�����
				tAccountCr.cur_freebala=D4U5(tAccountCr.cur_freebala+tTradelogCr.op_fee,6) ;					//��ǰ�������
			}
		}
		//�ж�����Ƿ�С��0,������͸֧,�ʲ����ʻ�����
		if(strncmp(tAccountCr.subno,"2",1)==0)
		{
			if(amtcmp(tAccountCr.cur_bala,0)<0||amtcmp(tAccountCr.cur_freebala,0)<0)
			{
				writelog(LOG_ERR,"host serialno[%d]credit No[%d+1]account[%s]account.cur_bala[%lf]cur_freebala[%lf]cur_frozebala[%lf]amt[%lf]",IA->iSerialNo,i,tAccountCr.account_id,tAccountCr.cur_bala,tAccountCr.cur_freebala,tAccountCr.cur_frozebala,tTradelogDb.op_fee);
				DB_t_aif_account_free_lock_cur();
				return E_BALANCE_SHORTAGE;
			}
		}
		tTradelogCr.new_fee = tAccountCr.cur_bala;			//�����ʻ����
		tTradelogCr.cur_frozebala=tAccountCr.cur_frozebala;		//������
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
		//���ӽ跽��¼��ˮ
		tTradelogDb.maindevice_id = IA->iMainDevId;		//����վ��ʶ
		tTradelogDb.device_id= IA->iDevId;				//�ն��豸ID
		tTradelogDb.serino = IA->iSerialNo;				//��ˮ��
		tTradelogDb.seri_type= IA->iTradeNo;				//������
		tTradelogDb.fee_type=iTxType;						//��¼���
		tTradelogDb.warrant_type = iVocType;				//ƾ֤����
		strcpy(tTradelogDb.warrant_no, sVocNo);				//ƾ֤��
		strcpy(tTradelogDb.comments, CfgSplit.ArrCfgsplit[iTxType].txname);	//ժҪ
		strcpy(tTradelogDb.operate_date, IA->sTxDate);		//��������
		strcpy(tTradelogDb.operate_time, IA->sTxTime);		//����ʱ��
		strcpy(tTradelogDb.collect_date,IA->sTxCollectDate);	//�ɼ�����
		strcpy(tTradelogDb.collect_time,IA->sTxCollectTime);	//�ɼ�ʱ��
		strcpy(tTradelogDb.enteract_date,IA->sTxAccDate);	//��������
		strcpy(tTradelogDb.enteract_time,IA->sTxAccTime);	//����ʱ��
		strcpy(tTradelogDb.record_oper, IA->sMdeOper);	//¼�����Ա
		strcpy(tTradelogDb.write_oper, IA->sChkOper);		//���˼���Ա
		tTradelogDb.outorin = DBCR_DEBIT;					//�跽��־
		strcpy(tTradelogDb.other_actid, tTradelogCr.act_id);		//�Է��˺�
		strcpy(tTradelogDb.other_subno, tTradelogCr.subno);	//�Է���Ŀ
		++IA->iSubIndex;
		tTradelogDb.annex = IA->iSubIndex;
		ret = DB_t_tif_tradelog_add(&tTradelogDb);
		if (ret)
		{
			writelog(LOG_ERR, "add ArrTradelog err[%d] ", ret);
			return E_DB_TRADELOG_I;
		}
		//���Ӵ�����¼��ˮ
		tTradelogCr.maindevice_id = IA->iMainDevId;		//����վ��ʶ
		tTradelogCr.device_id= IA->iDevId;				//�ն��豸ID
		tTradelogCr.serino = IA->iSerialNo;				//��ˮ��
		tTradelogCr.seri_type = IA->iTradeNo;				//������
		tTradelogCr.fee_type=iTxType;						//��¼���
		tTradelogCr.warrant_type = iVocType;					//ƾ֤����
		strcpy(tTradelogCr.warrant_no, sVocNo);				//ƾ֤��
		strcpy(tTradelogCr.comments,  CfgSplit.ArrCfgsplit[iTxType].txname);//ժҪ
		strcpy(tTradelogCr.operate_date, IA->sTxDate);		//��������
		strcpy(tTradelogCr.operate_time, IA->sTxTime);		//����ʱ��
		strcpy(tTradelogCr.collect_date,IA->sTxCollectDate);	//�ɼ�����
		strcpy(tTradelogCr.collect_time,IA->sTxCollectTime);	//�ɼ�ʱ��
		strcpy(tTradelogCr.enteract_date,tTradelogDb.enteract_date);//��������
		strcpy(tTradelogCr.enteract_time,tTradelogDb.enteract_time);//����ʱ��
		strcpy(tTradelogCr.record_oper, IA->sMdeOper);		//¼�����Ա
		strcpy(tTradelogCr.write_oper, IA->sChkOper);		//���˲���Ա
		tTradelogCr.outorin = DBCR_CREDIT;					//������־
		strcpy(tTradelogCr.other_actid, tTradelogDb.act_id);		//�Է��˺�
		strcpy(tTradelogCr.other_subno, tTradelogDb.subno);	//�Է���Ŀ
		tTradelogCr.annex = IA->iSubIndex;
		
		ret = DB_t_tif_tradelog_add(&tTradelogCr);
		if (ret)
		{
			writelog(LOG_ERR, "add ArrTradelog err[%d] ", ret);
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
				sprintf(pMessage+strlen(pMessage),"%s:�������%.2lfԪ", tAccountDb.cut_name,dExpCalAmt);
			else
				sprintf(pMessage+strlen(pMessage),"%s:������%.2lfԪ", tAccountDb.cut_name,dExpCalAmt);
			if(cr_amt_flag>0)
				sprintf(pMessage+strlen(pMessage)," %s:�������%.2lfԪ",tAccountCr.cut_name,dExpCalAmt);
			else
				sprintf(pMessage+strlen(pMessage)," %s:������%.2lfԪ", tAccountCr.cut_name,dExpCalAmt);
		}
	}
	//������뿨ֵ��û�г���ֵ�������ֵ�����뿨ֵ
	if(amtcmp(IA->dOutCardBala,0)<0)
	{
		if(amtcmp(IA->dInCardBala,0)>=0)
			IA->dOutCardBala=IA->dInCardBala;
	}
//	writelog(LOG_DEBUG,"serino[%d]IA->dInCardBala[%lf]IA->dOutCardBala[%lf]IA->iTxCnt[%d]",IA->iSerialNo,IA->dInCardBala,IA->dOutCardBala,IA->iTxCnt);
	return 0;
}
