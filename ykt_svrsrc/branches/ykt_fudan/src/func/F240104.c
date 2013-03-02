/* --------------------------------------------
 * ��������: F240104.c
 * ��������: 2009-07-9
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: ��ȡ����
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
	if(amtcmp(p->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	return 0;
}

int F240104(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

  	int ret = 0;
	int i=0;
	int row=0;
//	int next_flag=0;
	int	card_id = 0;
	char	Operator[33+1] = "";
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char subsidy_no[21] = "";
	double dUniqno = 0;
	char sMaxCardBalance[20]="";
	char sMsg[256]="";
	double dMaxCardBalance=0;

	T_t_tif_tradeserial  tradeserial;
	T_t_cif_customer 	tCustomer;
	T_t_aif_account	tAccount;
	T_t_tif_subsidy	tSubsidy;
	T_t_pif_card	tCard;
	InAcc	IA;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
   	SetCol(handle,F_SSERIAL1,F_LVOL2,F_LVOL4,F_LVOL5,F_LVOL6,F_DAMT1,F_DAMT2,F_DAMT3,F_VSMESS,F_SEMAIL,0);

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));
	memset(&IA,0,sizeof(IA));

	card_id=in_pack->lvol0;
	
	in_pack->damt0 = D4U5(in_pack->lvol3/100.0,2);				//�����ʹ����뿨ֵ
	des2src(subsidy_no,in_pack->sname);							// �������κ�

	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
		return ret;
	}
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}
	/*�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(in_pack->sname)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	*/
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}
	/*�жϿ������Ƿ���ȷ
	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, in_pack->semp_pwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	if(0!=memcmp(pwd,tCard.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,tCard.password);
		return E_TRANS_SCHCARD_PWDERR;
	}
	*/
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}
	/*
	ret=DB_t_tif_subsidy_open_select_for_update_by_c1_and_cust_no_and_status(tCard.cosumer_id, "2");
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SUBSIDY_N;
		else
			return E_DB_SUBSIDY_R;
	}
	while(1)
	{
		memset(&tSubsidy,0,sizeof(tSubsidy));
		ret=DB_t_tif_subsidy_fetch_select_by_c1(&tSubsidy);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(row)
					break;
				else
					return E_USER_NO_SUBSIDY;
			}
			else
				return E_DB_SUBSIDY_R;
		}
		row++;
		if(row>1)
		{
			DB_t_tif_subsidy_close_select_by_c1();
			next_flag=1;
			break;
		}
		strcpy(tSubsidy.status,"3");
		getsysdate(tSubsidy.get_date);
		getsystime(tSubsidy.get_time);
		tSubsidy.card_no=card_id;
		tradeserial.trade_fee=tSubsidy.amount;			//�������
		des2src(out_pack->semail,tSubsidy.summary); //��ע˵��
		ret=DB_t_tif_subsidy_update_lock_by_c1(&tSubsidy);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_USER_NO_SUBSIDY;
			else
				return E_DB_SUBSIDY_U;
		}
	}
	*/
	memset(&tSubsidy,0,sizeof(tSubsidy));
	ret = DB_t_tif_subsidy_read_lock_by_c3_and_subsidy_no_and_cust_no_and_status(subsidy_no, tCard.cosumer_id, "2", &tSubsidy);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SUBSIDY_N;
		else
			return E_DB_SUBSIDY_R;
	}

	strcpy(tSubsidy.status,"3");
	getsysdate(tSubsidy.get_date);
	getsystime(tSubsidy.get_time);
	tSubsidy.card_no=card_id;
	tradeserial.trade_fee=tSubsidy.amount;			//�������
	des2src(out_pack->semail,tSubsidy.summary); //��ע˵��
	ret=DB_t_tif_subsidy_update_lock_by_c3(&tSubsidy);
	if(ret)
	{
		DB_t_tif_subsidy_free_lock_by_c3();
		if(DB_NOTFOUND==ret)
			return E_USER_NO_SUBSIDY;
		else
			return E_DB_SUBSIDY_U;
	}
	DB_t_tif_subsidy_free_lock_by_c3();
	
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			ret=E_ACTNO_NOT_EXIST;
		else
			ret=E_DB_ACCOUNT_R;
		return ret;
	}
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		return ret;
	}
	dMaxCardBalance=atof(sMaxCardBalance);
	if(amtcmp(in_pack->damt0+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		return  E_AMT_EXCEED_MAX;
	}
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}
	
	des2src(Operator,"system");												//����Ա��
	//maindevice_id = GetTransferSystemId();											//�ϴ�����վ��ʶ
	//device_id = atoi(in_pack->sname);										//�ɼ��豸��ʶ

	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return ret;
	}
	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//��������
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);
	des2src(tradeserial.collect_date,tradeserial.operate_date);								//�ɼ�����
	des2src(tradeserial.collect_time,tradeserial.operate_time);								//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);							//��������
	des2src(tradeserial.enteract_time,tradeserial.operate_time);							//����ʱ��
	tradeserial.serial_no = (int)dUniqno;									//��ˮ��
	tradeserial.serial_type = TXCODE_GET_SUBSIDY;						//����
	tradeserial.serial_state = SERISTAT_DEBT;								//��ˮ״̬
	tradeserial.maindevice_id = maindevice_id;						//�ϴ�����վ��ʶ
	tradeserial.device_id = device_id;										//�ɼ��豸��ʶ
	tradeserial.card_id = card_id;										//���׿���
	tradeserial.customer_id=tCard.cosumer_id;								//�ͻ���
	des2src(tradeserial.oper_code,Operator);
	tradeserial.trade_count=in_pack->lvol1+1;		//���״���
	// writelog(LOG_DEBUG,"�ϴ��뿨ֵ%.2lf",in_pack->damt0);
	tradeserial.in_balance=in_pack->damt0;			//�뿨ֵ
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
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
			case TXTYPE_BANK_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK:
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
	tradeserial.out_balance=IA.dOutCardBala;
//	out_pack->lvol2=next_flag;					//�Ƿ�����һ�ʲ���
	out_pack->damt1=tradeserial.trade_fee;		//�������
	out_pack->damt2=tradeserial.out_balance;	//����ֵ
	out_pack->damt3=tradeserial.boardfee;		//���ѽ��

	out_pack->lvol4=D2I(tradeserial.trade_fee*100);		//�������
	out_pack->lvol5=D2I(tradeserial.out_balance*100);	//����ֵ
	out_pack->lvol6=D2I(tradeserial.boardfee*100);		//���ѽ��
	sprintf(out_pack->sserial1,"%d", tradeserial.serial_no);
	
	sprintf(sMsg,"����ǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}
