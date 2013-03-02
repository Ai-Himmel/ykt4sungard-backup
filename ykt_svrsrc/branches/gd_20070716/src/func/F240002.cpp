/* --------------------------------------------
 * ��������: F240002.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��ת�˺�̨ģ�����˽���
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

static int do_check_card_state(int card_id,T_t_pif_card *card)
{
	int ret;
	ret = DB_t_pif_card_read_by_card_id(card_id,card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		if(DB_NOTFOUND == ret)
			return E_DB_CARD_N;
		else
			return E_DB_CARD_R;
	}
	if(strncmp(card->state_id,CARDSTAT_LOGOUT,4)==0)
	{
		writelog(LOG_ERR,"card->state_id=[%d]",card->card_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	else if(STATE_TRUE==card->state_id[CARDSTAT_TYPE_LOST])
	{
		writelog(LOG_ERR,"card_state=[%s]",card->state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	else if(STATE_TRUE==card->state_id[CARDSTAT_TYPE_FREEZE])
	{
		writelog(LOG_ERR,"card_state=[%s]",card->state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	else if(STATE_TRUE==card->state_id[CARDSTAT_TYPE_WFAIL])
	{
		writelog(LOG_ERR,"card_state=[%s]",card->state_id);
		return E_TRANS_SCHCARD_WFAIL;
	}
	return 0;
}
static int do_check_elec_pwd(T_t_aif_account *account,const char *pwd)
{
	char temp[128] = "";
	char new_pwd[20] = "";
	int ret;
	ret = GetParameter(GLOBE_999_DEVAUTHKEY ,temp);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_PASSWORD_WRONG;
		return E_GLOBAL_PARAM_ERROR;
	}
	ret = decrypt_elec_card_pwd(0,temp,account->password,new_pwd);
	if(ret)
	{
		return E_GLOBAL_PARAM_ERROR;
	}
	if(strcmp(pwd,new_pwd) == 0)
	{
		return 0;
	}
	return E_PASSWORD_WRONG;
}
static int do_precheck(T_t_cif_customer *customer,ST_PACK *in_pack,char sAccount[][30],InAcc *IA)
{
	int ret;
	T_t_pif_card card;
	T_t_tradecode_shop tradecode_shop;
	T_t_cif_shop shop;
	char sMaxCardBalance[128] = "";
	double dMaxCardBalance = 0.0;
	double trade_fee;
	T_t_aif_account tAccount;
	memset(&card,0,sizeof card);
	card.card_id = atoi(in_pack->sserial0);
	memset(sAccount[0],0,sizeof sAccount[0]);
	des2src(sAccount[0],in_pack->sstation0); // �跽�˺�
	trade_fee = D4U5(in_pack->lvol5/100.0,2);
	switch(in_pack->lvol4)
	{
	case TXCODE_BANK_SCHOOL:
		IA->iUseCardFlag = IS_YES;
		ret = do_check_card_state(card.card_id,&card);
		if(ret)
			return ret;
		memset(&tAccount,0,sizeof tAccount);
		//�ж�ת�ʽ���Ƿ񳬳�Ǯ������޶�
		ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
			if(DB_NOTFOUND==ret)
			{
				return E_TRANS_SCHACC_NOEXIT;
			}
			else
			{
				return E_TRANS_UNKNOW_ERROR;
			}
		}

		ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
		if(ret)
		{
			writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		dMaxCardBalance=atof(sMaxCardBalance);
		if(amtcmp(tAccount.cur_bala+trade_fee,dMaxCardBalance)>0)
		{
			return E_TRANS_TRANSMONEY_OUTRANGE;
		}
		ret = DB_t_cif_customer_read_by_cut_id(card.cosumer_id,customer);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				return E_DB_CUSTOMER_N;
			return E_DB_CUSTOMER_R;
		}
		// �����˺�
		des2src(sAccount[1],tAccount.account_id);
		break;
	case TXCODE_BANK_ELEC:
		IA->iUseCardFlag = IS_NO;
		// ����Ǯ���˺�
		ret = find_cutid_by_outsideno(&card.cosumer_id,in_pack->scust_auth,1);
		if(ret)
		{
			writelog(LOG_ERR,"find outside_no error,outside_no[%s]",in_pack->scust_auth);
			return ret;
		}
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(card.cosumer_id,ACCTYPE_PEREACC,&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"query account error,cut_id[%d]type[%d]",card.cosumer_id,ACCTYPE_PEREACC);
			if(DB_NOTFOUND == ret)
				return E_NOTEXIST_EACCNO;
			return E_DB_ACCOUNT_R;
		}
		if(tAccount.current_state == ACCOUNTSTAT_LOGOUT)
			return E_ACTNO_LOGOUT;
		ret = do_check_elec_pwd(&tAccount,in_pack->semp_pwd);
		if(ret)
			return ret;
		ret = DB_t_cif_customer_read_by_cut_id(card.cosumer_id,customer);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				return E_CUSTOMER_NOT_EXIST;
			return E_DB_CUSTOMER_R;
		}
		des2src(sAccount[1],tAccount.account_id);
		break;
	case TXCODE_BANK_YCT:
		IA->iUseCardFlag = IS_NO;
		ret = do_check_card_state(card.card_id,&card);
		if(ret)
			return ret;
		memset(&tradecode_shop,0,sizeof tradecode_shop);
		ret = DB_t_tradecode_shop_read_by_trade_code(in_pack->lvol4,&tradecode_shop);
		if(ret)
		{
			writelog(LOG_ERR,"query tradecode shop error,tradecode[%d]",in_pack->lvol4);
			if(DB_NOTFOUND == ret)
				return E_DB_TRADECODE_SHOP_N;
			return E_DB_TRADECODE_SHOP_R;
		}	
		memset(&shop,0,sizeof shop);
		ret = DB_t_cif_shop_read_by_shop_id(tradecode_shop.shop_id,&shop);
		if(ret)
		{
			writelog(LOG_ERR,"query shop error,shopid[%d]",tradecode_shop.shop_id);
			if(DB_NOTFOUND == ret)
				return E_DB_SHOP_N;
			return E_DB_SHOP_R;
		}
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(shop.cut_id,ACCTYPE_SHOPMAIN,&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"query account error,cut_id[%d]",shop.cut_id);
			if(DB_NOTFOUND == ret)
				return E_DB_ACCOUNT_N;
			return E_DB_ACCOUNT_R;
		}
		if(tAccount.current_state == ACCOUNTSTAT_LOGOUT)
			return E_ACTNO_LOGOUT;
		// �����˺�
		writelog(LOG_ERR,"query tradecode[%d],shopid[%d]",in_pack->lvol4,shop.cut_id);
		memset(sAccount[1],0,sizeof sAccount[1]);
		des2src(sAccount[1],tAccount.account_id);
		customer->fee_type = 0;
		customer->cut_id = shop.cut_id;
		break;
	default:
		return E_TRANS_UNKNOW_ERROR;
	}
	writelog(LOG_ERR,"cractno[%s]dbactno[%s][%s]",sAccount[0],sAccount[1],tAccount.account_id);
	return ret;
}
static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;
	T_t_aif_account tAccount;

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

	// IA->iUseCardFlag=IS_YES;						//������
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
	if(IA->iUseCardFlag == IS_YES)
		p->out_balance=IA->dOutCardBala;			//����ֵ
	else
	{
		// ��ȡ�����˻����
		memset(&tAccount,0,sizeof tAccount);
		ret = DB_t_aif_account_read_by_account_id(IA->sArrInActno[1],&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"read account error!,actno[%s]",IA->sArrInActno[1]);
			return E_DB_ACCOUNT_R;
		}
		p->out_balance = tAccount.cur_freebala;
	}
	return 0;
}

// modify by ���� 2008-08-30 
// ������� ת��ģ��, У԰�����������Ȧ��ǰ�û���� , ת�˿ɷ�Ϊ���ֽ���:
// 1 : �п�ת�˽��� , ���ֽ�����Ҫ���У԰��״̬
// 2 : �޿�ת�˽��� , ����ָ���˻���������˻���ǰ״̬
int F240002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	double unique=0;
	int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	double trans_amt=0.0;
	char sMsg[255]="";
	char sDebugMsg[255]="";
	char sAccount[2][30];

	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	T_t_aif_account tAccount;
	InAcc	IA;

	memset(&tCustomer,0,sizeof tCustomer);
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&IA,0,sizeof(IA));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(sAccount,0,sizeof sAccount);
	//��д���˽ṹ,�����Ž�
	memset(&IA,0,sizeof(IA));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_SDATE0,0);


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

	//ת�˲�����תС�����
	if((rPack->lvol5)%100>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		goto L_RETU;
	}
	if(rPack->lvol4 == 0)
	{
		// ������ǰ�汾, Ĭ�Ͻ���ת Ȧ��ת��
		rPack->lvol4 = TXCODE_BANK_SCHOOL;
	}

	//��ʼ�����ˮ����
	ret = do_precheck(&tCustomer,rPack,sAccount,&IA);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	//��ˮ��

	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}


	tradeserial.serial_no=D2I(unique);
	//��¼��ˮ�ţ���Ϊ����ʹ��
	temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=rPack->lvol0;	//�ϴ�����ˮ��
	tradeserial.serial_type=rPack->lvol4;	//���״���
	tradeserial.serial_state=SERISTAT_NODEBT;	//��ˮ״̬
	tradeserial.card_id=atoi(rPack->sserial0);
	tradeserial.purse_id=0;
	tradeserial.in_balance=D4U5(rPack->lvol6/100.00,2);	//�뿨���
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
	tradeserial.trade_fee=D4U5(rPack->lvol5/100.0,2);	//ת�ʽ��
	Strncpy_t(tradeserial.b_act_id,rPack->scust_auth,sizeof(tradeserial.b_act_id));
	tradeserial.sys_id=rPack->lvol2;						//��ʾ����
	tradeserial.condition_id=SELF_TRANS;						//�Զ�/����ת�ʱ�ʶ
	tradeserial.customer_id=tCustomer.cut_id;
	Strncpy_t(tradeserial.oper_code,OPER_SYSTEM_KEY,sizeof(tradeserial.oper_code));	//����Ա����
	tradeserial.comu_ver=tCustomer.fee_type;
	des2src(tradeserial.in_account_id,sAccount[1]);
	des2src(tradeserial.out_account_id,sAccount[0]);

	//��¼��ˮ���ݣ������ṩ��ȷ����ˮ�ţ��Լ�����ҵ�񲻳ɹ�����ѯ
	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
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
	// ��һ�б���, ��֤�����������ߵ�ϵͳ����
	//des2src(IA.sArrInActno[0],sAccount[1]);			//�����ʻ�,�ֿ����˻�
	// �޸����˲���,��������ͳһ��������ת�˽���
	des2src(IA.sArrInActno[1],sAccount[1]);			//�����ʻ�,�ֿ����˻�
	des2src(IA.sArrInActno[0],sAccount[0]);			//�跽�ʺţ���ǰ�û��ϴ� , �����˺�
	
	IA.iCardNo=tradeserial.card_id;
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


	sprintf(sMsg,"��ֵǰ�����:%.2lf ת�ʺ����:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
	strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);

	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=tradeserial.boardfee;
	out_pack->lvol1=tradeserial.serial_no;
	des2src(out_pack->sdate0,logicdate);

	PutRow(handle,out_pack,pRetCode,szMsg);

	//ҵ������󣬻ع�����
	ret=db_rollback();
	if(ret)
	{
		*pRetCode=E_DB_ROLLBACK;
		writelog(LOG_ERR,"db_rollback error,error code=[%d]",ret);
		goto L_RETU;
	}

	return 0;

L_RETU:
	return -1;
}


