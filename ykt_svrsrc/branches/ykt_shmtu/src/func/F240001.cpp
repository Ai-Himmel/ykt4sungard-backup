/* --------------------------------------------
 * ��������: F240001.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��ת����ʽ����
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
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

	IA->iUseCardFlag=IS_YES;						//������
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

int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	//double unique=0;
	//int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	double trans_amt=0.0;
	char sMsg[255]="";
	char sDebugMsg[255]="";

	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_aif_account	tAccount;		//�ʻ���
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	T_t_pif_card		card;
	InAcc	IA;

	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&card,0,sizeof(card));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,0);


	//memset(&tradeserial_bak,0,sizeof(tradeserial_bak));

	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		goto L_RETU;
	}

	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(rPack->sorder2)))
	{
		*pRetCode=E_TRANS_TERM_NOLOGIN;
		writelog(LOG_ERR,"Device don't login");
		goto L_RETU;
	}
	//�ж��Ƿ������ս���״̬
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		goto L_RETU;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		*pRetCode=E_TRANS_BANK_SERVICE_NOEXIT;
		writelog(LOG_ERR,"System is balance now!");
		goto L_RETU;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(rPack->sserial0),&card);
	if(ret)
	{
		*pRetCode=E_TRANS_SCHACC_NOEXIT;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		*pRetCode=E_TRANS_SCHACC_DESTORY;
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		goto L_RETU;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_LOSTING;
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		goto L_RETU;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_FREEZE;
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		goto L_RETU;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_WFAIL])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_WFAIL;
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		goto L_RETU;
	}

	//ת�˲�����תС�����
	if((rPack->lvol5)%100>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		goto L_RETU;
	}

	//��ʼ�����ˮ����
	//��ˮ��
	//ģʽ�޸�Ϊ���������ʲ�����ˮ�ţ���¼��ˮ�ṹ����ʽ����ֻ�޸ĸ�
	//��ˮ�ĳ���ֵ�Լ���ˮ״̬
/*
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}
*/

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(rPack->lvol7, &tradeserial);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_R;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d],serial_no=[%d]",ret,rPack->lvol7);
		goto L_RETU;
	}

	if(tradeserial.serial_state == SERISTAT_DEBT)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		goto L_FINISHED;
	}
	/*
	tradeserial.serial_no=D2I(unique);
	//��¼��ˮ�ţ���Ϊ����ʹ��
	//temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=rPack->lvol0;	//�ϴ�����ˮ��
	tradeserial.serial_type=TXCODE_BANK_SCHOOL;	//���״���
	tradeserial.serial_state=SERISTAT_NODEBT;	//��ˮ״̬
	tradeserial.card_id=atoi(rPack->sserial0);
	tradeserial.purse_id=0;
	tradeserial.in_balance=double((rPack->lvol6)/100.00);	//�뿨���
	tradeserial.out_balance=tradeserial.in_balance;			//�������
	tradeserial.trade_count=rPack->lvol1+1;				//��ǰ���н��״���

	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(tradeserial.operate_date);
		getsystime(tradeserial.operate_time);
	}
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));	//�ɼ�����
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));	//�ɼ�ʱ��
	Strncpy_t(tradeserial.enteract_date,logicdate,sizeof(tradeserial.enteract_date));	//��������
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//����ʱ��
	tradeserial.maindevice_id=GetTransferSystemId();		//��ϵͳ����
	tradeserial.device_id=atoi(rPack->sorder2);			//�ն�ID
	tradeserial.trade_fee=(rPack->lvol5)/100.0;	//ת�ʽ��
	Strncpy_t(tradeserial.b_act_id,rPack->scust_auth,sizeof(tradeserial.b_act_id));
	tradeserial.sys_id=rPack->lvol2;						//��ʾ����
	tradeserial.condition_id=SELF_TRANS;						//�Զ�/����ת�ʱ�ʶ
	tradeserial.customer_id=card.cosumer_id;
	Strncpy_t(tradeserial.oper_code,OPER_SYSTEM_KEY,sizeof(tradeserial.oper_code));	//����Ա����
*/
	//�ж�ת�ʽ���Ƿ񳬳�Ǯ������޶�
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
		if(DB_NOTFOUND==ret)
		{
			*pRetCode=E_TRANS_SCHACC_NOEXIT;
			goto L_RETU;
		}
		else
		{
			*pRetCode=E_TRANS_UNKNOW_ERROR;
			goto L_RETU;
		}
	}

	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RETU;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		goto L_RETU;
	}
	//��ȡ�ͻ��շ�����ֶ�
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
		{
			*pRetCode=E_TRANS_UNKNOW_ERROR;
			goto L_RETU;
		}
		else
		{
			*pRetCode=E_TRANS_UNKNOW_ERROR;
			goto L_RETU;
		}
	}

	if(0==tCustomer.fee_type)
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
				writelog(LOG_ERR,"DB_t_pif_spefee_read_by_dept_code_and_cut_type error,errcode=[%d]",ret);
				*pRetCode=E_TRANS_UNKNOW_ERROR;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	//��д���˽ṹ,�����Ž�
	memset(&IA,0,sizeof(IA));
	des2src(IA.sArrInActno[0],tAccount.account_id);			//�����ʻ�,�ֿ����˻�
	des2src(IA.sArrInActno[2],rPack->sstation0);				//�跽�ʺţ���ǰ�û��ϴ�
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process err,errcode[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RETU;
	}

	sprintf(sDebugMsg,"��ˮ��:%d ",IA.iSerialNo);
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
			case TXTYPE_BANK_PRE_TOLL_BOARD:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_BANK_TRANSFER:
				trans_amt=IA.dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(sDebugMsg,sMsg);
		}
	}

	//���������ˮ����
	tradeserial.serial_state=SERISTAT_DEBT;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_update_lock_by_cur error,error code=[%d]",ret);
		goto L_RETU;
	}


	sprintf(sMsg,"��ֵǰ�����:%.2lf ת�ʺ����:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    	strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);
	
L_FINISHED:
	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=tradeserial.boardfee;
	out_pack->lvol1=tradeserial.serial_no;

	PutRow(handle,out_pack,pRetCode,szMsg);

	return 0;
	
L_RETU:
	return -1;
}

