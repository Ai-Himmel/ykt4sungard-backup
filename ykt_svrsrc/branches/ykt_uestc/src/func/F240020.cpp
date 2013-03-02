/* --------------------------------------------
 * ��������: F240020.cpp
 * ��������: 2010-10-22
 * ��������: xlh
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��ת�˺�̨��¼��ˮ
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
#include "busqc.h"
static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret = 0;

	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	IA->iMainDevId=p->maindevice_id;			//����վ��ʶ
	IA->iDevId=p->device_id;					//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	IA->iTradeNo=p->serial_type;				//������
	strcpy(IA->sTxDate,p->operate_date);		//��������
	strcpy(IA->sTxTime,p->operate_time);		//����ʱ��
	strcpy(IA->sTxCollectDate,p->collect_date);	//�ɼ�����
	strcpy(IA->sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,p->enteract_date);	//��������
	strcpy(IA->sTxAccTime,p->enteract_time);	//����ʱ��
	strcpy(IA->sMdeOper,p->oper_code);		//¼�� ����Ա
	strcpy(IA->sChkOper,p->reserve_1);		//���� ����Ա
	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;	//��������
        IA->iTxCnt=p->trade_count;
	IA->dInCardBala=p->in_balance;				//�뿨ֵ						//�뿨ֵ
	IA->dOutCardBala=-1;						//����ֵ
	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;		//����ֵ
	return 0;
}

int F240020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int i=0;
	char sysdate[11]="";
	char systime[9]="";
	char logicdate[11] = "";
	char buffer[16]="";
	char sMaxCardBalance[20]="";
	double unique=0;
	char dateserialno[30]="";
	char sDebugMsg[1024]="";
	double trans_amt=0.0;
	char sMsg[300]="";
	char serial_nostr[30]="";
	char customer_idstr[30]="";
	T_t_tif_tradeserial  tradeserial;
	double dMaxCardBalance=0;
	InAcc  IA;
	T_t_pif_device t_device;
	T_t_pif_card		card;
	T_t_aif_account	tAccount;		//�ʻ���
	T_t_bankcard 	bankcard;
	T_t_cfgbank     cfgbank;
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	memset(&t_device,0,sizeof(t_device));
	memset(&card,0,sizeof(card));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&bankcard,0,sizeof(bankcard));
	memset(&cfgbank,0,sizeof(cfgbank));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_AUTH,F_SNAME,F_SNAME2,F_LSERIAL0,F_STX_PWD,F_LVOL5,F_LVOL6,0);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);											//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(tradeserial.operate_date);
		getsystime(tradeserial.operate_time);
	}
	//�ж��Ƿ������ս���״̬
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		*pRetCode=GET_BALANCE_ERR;
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		goto L_RETU;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		*pRetCode=E_TRANS_BANK_SERVICE_NOEXIT;
		writelog(LOG_ERR,"System is balance now!");
		goto L_RETU;
	}
	
	//ת�˲�����תС�����
	if((rPack->lvol5)%100>0)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"ת�˽�����������");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	if(rPack->lvol5<1)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"ת�˽���Ϊ0");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}	
	writelog(LOG_ERR,"lvol5[%d]",rPack->lvol5);
	ret=DB_t_pif_device_read_by_device_id(rPack->lcert_code, &t_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_by_device_id err,errcode=[%d],device_id=[%d]",ret,tradeserial.device_id);
		return E_DB_DEVICE_R;
	}
	
	ret=DB_t_pif_card_read_by_card_id(rPack->lvol0,&card);
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
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_A;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no=D2I(unique);




	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));	//�ɼ�����
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));	//�ɼ�ʱ��
	Strncpy_t(tradeserial.enteract_date,logicdate,sizeof(tradeserial.enteract_date));	//��������
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//����ʱ��
	tradeserial.maindevice_id=GetTransferSystemId();		//��ϵͳ����
	tradeserial.device_id=rPack->lcert_code;			//�ն�ID
	tradeserial.serial_no=D2I(unique);
	tradeserial.serial_type=TXCODE_BANK_SCHOOL;
	tradeserial.serial_state=SERISTAT_NODEBT;	//��ˮ״̬				
	tradeserial.condition_id=SELF_TRANS;	
	tradeserial.sys_id=rPack->lcert_code;	//��ʾ����		
	tradeserial.trade_fee= rPack->lvol5/100.0;
	tradeserial.in_balance=rPack->lvol6/100.00;
	tradeserial.trade_count=rPack->lvol1+1;	//��ֵ����
	tradeserial.card_id=rPack->lvol0;
	tradeserial.out_balance=tradeserial.in_balance;
	Strncpy_t(tradeserial.oper_code,OPER_SYSTEM_KEY,sizeof(tradeserial.oper_code));	//����Ա����
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
	writelog(LOG_ERR,"lvol5[%lf]",dMaxCardBalance);
	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		goto L_RETU;
	}

	tradeserial.customer_id=card.cosumer_id;
	//��ȡ�ͻ��շ�����ֶ�
	writelog(LOG_ERR," card.cosumer_id[%d]",card.cosumer_id);
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
		{
			*pRetCode=E_DB_CUTINFO_UPD_N;
			goto L_RETU;
		}
		else
		{
			*pRetCode=E_DB_CUTINFO_UPD_R;
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
				*pRetCode=E_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	//У��󶨹�ϵ
	ret = DB_t_bankcard_read_by_custid(card.cosumer_id, &bankcard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			strcpy(szMsg,"ѧ���ź����п���δ��");
			return E_DB_BANKCARD_N;
		}
		else
		{
			return E_DB_BANKCARD_R;
		}
	}
	
	ret = DB_t_cfgbank_read_by_bankcode(bankcard.bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}
	
	if(strncmp(tradeserial.enteract_time,cfgbank.bankstarttime,6) < 0
		|| strncmp(tradeserial.enteract_time,cfgbank.bankendtime,6) > 0)
	{
		return E_OUT_BANKTIME;
	}
         writelog(LOG_DEBUG,sDebugMsg);
	T_t_refno tRefno;
	memset(&tRefno,0,sizeof(tRefno));	
	get_random(tRefno.mac);
	ret= GetNewRefno(tRefno.refno);
	if(ret)
		return ret;
	des2src(tRefno.lastsaved,tradeserial.operate_time);
	des2src(tRefno.accdate,tradeserial.enteract_date);
	tRefno.termid = tradeserial.sys_id;
	tRefno.termseqno = tradeserial.serial_no;
	des2src(dateserialno,tradeserial.operate_date);
	sprintf(serial_nostr,"%d",tradeserial.serial_no);
	strcat(dateserialno, serial_nostr);
	des2src(tRefno.dateserialno,dateserialno);
	ret=DB_t_refno_add(&tRefno);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_REFNO_E;
		else
			return E_DB_REFNO_I;
	}
	des2src(tradeserial.b_act_id,bankcard.bankcardno);
	des2src(tradeserial.showid,card.showid);
	tradeserial.reviseserial_no=atoi(tRefno.refno);
	//��¼��ˮ���ݣ������ṩ��ȷ����ˮ�ţ��Լ�����ҵ�񲻳ɹ�����ѯ
	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_I;
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		goto L_RETU;
	}

	ret=db_commit();
	if(ret)
	{
		*pRetCode=E_DB_COMMIT;
		writelog(LOG_ERR,"db_commit error,error code=[%d]",ret);
		goto L_RETU;

	}
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
		*pRetCode=E_ACC_BANK;
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


	sprintf(sMsg,"��ֵǰ�����:%.2lf ת�ʺ����:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    	strcat(sDebugMsg,sMsg);
		//ҵ������󣬻ع�����
	ret=db_rollback();
	if(ret)
	{
		*pRetCode=E_DB_ROLLBACK;
		writelog(LOG_ERR,"db_rollback error,error code=[%d]",ret);
		goto L_RETU;
	}
	
	des2src(out_pack->scust_auth,bankcard.bankcardno);					// ���п���
	sprintf(customer_idstr,"%d",tradeserial.customer_id);
	des2src(out_pack->sname,customer_idstr);							// ѧ����
	des2src(out_pack->sname2,tRefno.refno);							// ���ײο��� Ŀǰû��
	des2src(out_pack->stx_pwd,tRefno.mac);								// �����
	out_pack->lserial0=tradeserial.serial_no;									// �ն���ˮ��
	out_pack->lvol5 = D2I(tradeserial.trade_fee*100);									// ���׽�� (��)
	out_pack->lvol6 = D2I(tradeserial.in_balance*100);									// �뿨ֵ(��)

	writelog(LOG_INFO,"bankcardno[%s],stuempno[%s],refno[%s],termseqno[%d],inputamt[%d],befbal[%d]",out_pack->scust_auth,
		out_pack->sname,out_pack->sname2,out_pack->lserial0,out_pack->lvol5,out_pack->lvol6);
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
	L_RETU:
	return -1;
}
