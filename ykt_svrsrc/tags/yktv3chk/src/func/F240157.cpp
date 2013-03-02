/* --------------------------------------------
 * ��������: F240157.c
 * ��������: 2005-06-24
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ�油��
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
#include "busqc.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;
#if 0
	IA->iMainDevId=p->maindeviceid;				//����վ��ʶ
	IA->iDevId=p->deviceid;						//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	IA->iTradeNo=p->serial_type;					//������
	strcpy(IA->sTxDate,p->operate_date);			//��������
	strcpy(IA->sTxTime,p->operate_time);			//����ʱ��
	strcpy(IA->sTxCollectDate,p->collect_date);		//�ɼ�����
	strcpy(IA->sTxCollectTime,p->collect_time);		//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,p->enteract_date);		//��������
	strcpy(IA->sTxAccTime,p->enteract_time);		//����ʱ��

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
#endif
	return 0;
}

int F240157(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	InAcc	IA;
	int iSeqNo = 0;
	int cardno=0;
	int iSerialno=0;
	char cardphyid[41]="";
	char sMaxCardBalance[20]="";
	char sMsg[256]="";
	double dMaxCardBalance=0;
	T_t_card		tCard;
	T_t_customer tCustomer;
	T_t_spefee 	tSpeFee;
	T_t_account	tAccount;		//�ʻ���
	T_t_tif_tradeserial tradeserial;
	T_t_tif_diff_transfer tDiffTransfer;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tDiffTransfer,0,sizeof(tDiffTransfer));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	ResetNormalCPack(&aPack,0,1);

	if(amtcmp(rPack->damt1,0)==0)
	{
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	if(strlen(rPack->scust_limit)==0)
	{
		*pRetCode=E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit2)==0)
	{
		*pRetCode=E_INPUT_AUTH_OPER_NULL;
		goto L_RETU;
	}
	if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
	{
		writelog(LOG_ERR,"oper[%s]auth_oper[%s]",rPack->scust_limit,rPack->scust_limit2);
		*pRetCode=E_OPER_AND_AUTH_OPER_EQ;
		goto L_RETU;
	}
	ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
	if(ret)
	{
		if(E_OPER_NOT_EXIST==ret)
			*pRetCode=E_AUTH_OPER_NOT_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			*pRetCode=E_AUTH_OPER_PWD;
		else
			*pRetCode=ret;
		goto L_RETU;
	}
	cardno=rPack->lvol0;
	des2src(cardphyid, rPack->sbank_acc);				//������
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	ret=DB_t_card_read_by_cardno(cardno, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(cardno!=tCard.cardno)
	{
		writelog(LOG_ERR,"cardno[%d] db cardno[%d]",cardno,tCard.cardno);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(strncmp(tCard.cardattr,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.cardattr[CARDSTAT_TYPE_REG])
			*pRetCode=E_CARDNO_LOGOUT;
		else if('3'==tCard.cardattr[CARDSTAT_TYPE_REG])
			*pRetCode=E_CARD_CHANGE;
		else if(STATE_TRUE==tCard.cardattr[CARDSTAT_TYPE_LOST])
			*pRetCode=E_CARDNO_LOST;
		else if(STATE_TRUE==tCard.cardattr[CARDSTAT_TYPE_FREEZE])
			*pRetCode=E_CARDNO_FREEZE;
		else if(STATE_TRUE==tCard.cardattr[CARDSTAT_TYPE_WFAIL])
			*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	trim(cardphyid);
	trim(tCard.cardphyid);
	if(strcmp(tCard.cardphyid,cardphyid)!=0)
	{
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,cardphyid);
		*pRetCode= E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}
	iSerialno=rPack->lserial0;
	ret=DB_t_tif_diff_transfer_read_lock_by_c0_and_op_date_and_local_sn(rPack->sdate0,iSerialno,&tDiffTransfer);
	if(ret)
	{
		writelog(LOG_ERR,"operater_date[%s]Serialno[%d]",rPack->sdate0,iSerialno);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_SERIALNO_NOT_EXIST;
		else
			*pRetCode=E_DB_TRADESERIAL_R;
		goto L_RETU;
	}
	if(cardno!=tDiffTransfer.cardno)
	{
		writelog(LOG_ERR,"input cardno [%d],DiffTransfer cardno[%d]",cardno,tDiffTransfer.cardno);
		DB_t_tif_diff_transfer_free_lock_by_c0();
		*pRetCode=E_CARDNO_SERIAL_NE;
		goto L_RETU;
	}
	if(SERISTAT_NODEBT!=tDiffTransfer.status)
	{
		DB_t_tif_diff_transfer_free_lock_by_c0();
		*pRetCode=E_TX_SERIAL_CANNOT_CZ;
		goto L_RETU;
	}
	if(amtcmp(tDiffTransfer.diff_amt,rPack->damt1)!=0)
	{
		DB_t_tif_diff_transfer_free_lock_by_c0();
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	tDiffTransfer.status=SERISTAT_DEBT;
	ret=DB_t_tif_diff_transfer_update_lock_by_c0(&tDiffTransfer);
	if(ret)
	{
		*pRetCode=E_DB_DIFF_TRANSFER_U;
		goto L_RETU;
	}
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	ret=DB_t_account_read_by_cardno_and_purseno(cardno, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_cardno_and_purseno ret[%d]cardno[%d]",ret,cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_ACTNO_NOT_EXIST;
		else
			*pRetCode=E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	tradeserial.trade_fee = rPack->damt1;				//��ֵ���
	if(amtcmp(tAccount.availbal+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode= E_AMT_EXCEED_MAX;
		goto L_RETU;
	}
	ret=DB_t_customer_read_lock_by_cur_and_custid(tCard.custid, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"custid[%d]",tCard.custid);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	//�õ��շ����
	if(tCustomer.feetype<1)
	{
		ret=DB_t_spefee_read_by_deptcode_and_custtype(tCustomer.deptcode, tCustomer.custtype,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.feetype=tCustomer.custtype;
			}
			else
			{
				DB_t_customer_free_lock_cur();
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.feetype=tSpeFee.feetype;
		}
		//���¿ͻ�����շ�����ֶ�
		ret=DB_t_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
	}

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&iSeqNo);  					//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = iSeqNo;					//��ˮ��
	tradeserial.other_seri_no = 0;								//�ϴ�����ˮ��
	tradeserial.serial_type  = TXCODE_MAKEUPSERIAL;
	tradeserial.serial_state = SERISTAT_DEBT;						//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);					//��������
	des2src(tradeserial.operate_time,systime);					//����ʱ��
	des2src(tradeserial.collect_date,sysdate);						//�ɼ�����
	des2src(tradeserial.collect_time,systime);						//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);					//��������
	des2src(tradeserial.enteract_time,systime);					//����ʱ��
	tradeserial.maindeviceid = rPack->lvol6;						//�ϴ�����վ��ʶ
//	tradeserial.deviceid = rPack->lvol7;							//�ɼ��豸��ʶ
	tradeserial.cardno =cardno;									//����
	tradeserial.purseno = PURSE_NO_ONE;						//Ǯ����
	tradeserial.custid = tCard.custid;					//�ͻ���ʶ
	tradeserial.in_balance=rPack->damt0;						//�뿨ֵ
	tradeserial.trade_count=rPack->lvol1+1;					//���״���
	des2src(tradeserial.opercode,rPack->scust_limit);			//����Ա����
	tradeserial.sys_id = 0;										//�ⲿϵͳ��ʶ

	des2src(IA.sArrInActno[0],tAccount.accno);						//�ʻ�
	IA.iCardNo=tCard.cardno;
	IA.iFeeType=tCustomer.feetype;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"��ˮ��:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.depositfee=IA.dArrOutAmt[i];
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
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	writelog(LOG_DEBUG,out_pack->vsmess);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_DAMT4,F_VSMESS,0);
	out_pack->lserial1=tradeserial.serial_no;			//��ˮ��
	out_pack->damt2=tradeserial.trade_fee;			//��ֵ���
	out_pack->damt3=tradeserial.boardfee;			//����
	out_pack->damt4=tradeserial.out_balance;		//����ֵ
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
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
