/* --------------------------------------------
 * ��������: F47107.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ֽ�֧ȡ
 * --------------------------------------------
 * �޸�����:2004-10-12
 * �޸���Ա:	�Ž�
 * �޸�����: ���Ӽ��˽��״���
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
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

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	IA->iMainDevId=p->maindevice_id;				//����վ��ʶ
	IA->iDevId=p->device_id;						//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	IA->iTradeNo=p->serial_type;					//������
	strcpy(IA->sTxDate,p->operate_date);			//��������
	strcpy(IA->sTxTime,p->operate_time);			//����ʱ��
	strcpy(IA->sTxCollectDate,p->collect_date);		//�ɼ�����
	strcpy(IA->sTxCollectTime,p->collect_time);		//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,p->enteract_date);		//��������
	strcpy(IA->sTxAccTime,p->enteract_time);		//����ʱ��
	strcpy(IA->sMdeOper,p->oper_code);			//����Ա
	strcpy(IA->sChkOper,p->reserve_1);			//���˲���Ա

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//��������
	IA->iTxCnt=p->trade_count;					//���״���
	IA->dInCardBala=p->in_balance;				//�뿨ֵ
	IA->dOutCardBala=-1;							//����ֵ
	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//����ֵ
	return 0;
}

int F847107(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	int svrfee_feetype[30]; 
	int feetype_cnt=0;
	bool bsrvfee=false;
	
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	int card_id=0;
	char sMsg[256]="";
	char physical_no[41]="";
	T_t_tif_tradeserial  tradeserial;
	T_t_pif_card		tCard;
	T_t_tif_savdtl tSavdtl;
	T_t_cif_customer tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;		//�ʻ���
	InAcc	IA;
	double dSerialNo = 0;
	double self_money = 0; 
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	*pRetCode=0;

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&IA,0,sizeof(IA));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_VSMESS,0);

	card_id=rPack->lvol0;
	des2src(physical_no, rPack->sbank_acc);				//������

	if(amtcmp(rPack->damt0,0)<=0)
	{
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	if(amtcmp(rPack->damt1,0)<0)
	{
		*pRetCode=E_INPUT_CARD_BALA;
		goto L_RETU;
	}
	if(rPack->lvol10<1)
	{
		*pRetCode=E_INPUT_CARD_TXCNT;
		goto L_RETU;
	}

	if(amtcmp(rPack->damt1,rPack->damt0)<0)
	{
		writelog(LOG_ERR,"tCard balance[%lf] amount[%lf]",rPack->damt1,rPack->damt0);
		*pRetCode= E_BALANCE_SHORTAGE;
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}

	ret = Get_svrfee_feetype(svrfee_feetype, &feetype_cnt);
	if(ret)
		return ret;	
	
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			*pRetCode=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			*pRetCode=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	trim(physical_no);
	trim(tCard.physical_no);
	if(strcmp(tCard.physical_no,physical_no)!=0)
	{
		writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,physical_no);
		*pRetCode= E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}
	tradeserial.trade_fee = rPack->damt0;													//֧ȡ���
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]purse_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= 	E_ACTNO_NOT_EXIST;
		else
			*pRetCode= 	E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	if(amtcmp(tradeserial.trade_fee,tAccount.cur_freebala)>0)
	{
		writelog(LOG_ERR,"tradeserial.trade_fee[%lf]tAccount.cur_freebala[%lf]",tradeserial.trade_fee,tAccount.cur_freebala);
		*pRetCode=  E_BALANCE_SHORTAGE;
		goto L_RETU;
	}

	//��ѯ֧Ʊ���ѱ����޳�ֵ��¼
	ret=ChkSavdtl(card_id,&tSavdtl);
	if(ret)
	{
		writelog(LOG_ERR,"ChkSavdtl ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(tSavdtl.bill_type)
	{
		case TYPE_CASH:	//�ֽ�
			IA.iArrInFeeSwitch[1]=1;
			break;
		case TYPE_BILL:	//֧Ʊ
			IA.iArrInFeeSwitch[2]=1;
			break;
		case TYPE_FUNDBOOK:	//���ѱ�
			IA.iArrInFeeSwitch[3]=1;
			break;
		default:
			writelog(LOG_ERR,"type[%d]",tSavdtl.bill_type);
			IA.iArrInFeeSwitch[1]=1;
			break;
	}
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	//�õ��շ����
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
		//���¿ͻ�����շ�����ֶ�
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
		self_money = get_person_acc_in(tAccount.account_id ,tAccount.open_date,sysdate) +
					subsidy_in_card(tAccount.customer_id,tAccount.open_date,sysdate) - 
					get_draw_money(tAccount.account_id ,tAccount.open_date,sysdate);
		if(amtcmp(tradeserial.trade_fee,self_money)>0)
			return E_SELF_MONEY_SHORT;
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  	//�����ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = D2I(dSerialNo);						//��ˮ��
	tradeserial.other_seri_no = 0;							//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_DRAW_DEPOSIT_LOG;		//���״���
	tradeserial.serial_state = SERISTAT_DEBT;					//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);				//��������
	des2src(tradeserial.operate_time,systime);				//����ʱ��
	des2src(tradeserial.collect_date,sysdate);					//�ɼ�����
	des2src(tradeserial.collect_time,systime);					//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);				//��������
	des2src(tradeserial.enteract_time,systime);				//����ʱ��
	tradeserial.maindevice_id = rPack->lvol6;					//�ϴ�����վ��
	tradeserial.device_id = rPack->lvol7;						//�ɼ��豸��ʶ
	tradeserial.card_id = rPack->lvol0;						//����
	tradeserial.purse_id = rPack->lvol1;						//Ǯ����
	tradeserial.customer_id = rPack->lvol2;					//�ͻ���ʶ
	tradeserial.in_balance=rPack->damt1;					//�뿨ֵ
	tradeserial.trade_count=rPack->lvol10+1;				//���״���
	des2src(tradeserial.oper_code , rPack->scust_limit);		//����Ա����
	tradeserial.sys_id = 0;									//�ⲿϵͳ��ʶ

	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	strcpy(IA.sArrInActno[0],tAccount.account_id);
	IA.dArrInAmt[0]=tradeserial.trade_fee;					//�˺�

	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;

	//	����������ģ��
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"��ˮ��:%d ����:%d ",IA.iSerialNo,IA.iCardNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tradeserial.cost_fee=IA.dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	sprintf(sMsg,"֧ȡǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	//	���뿨������ˮ��
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
	out_pack->damt2=tradeserial.out_balance;							//����ֵ
	out_pack->lserial1=tradeserial.serial_no;								//��ˮ��
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
