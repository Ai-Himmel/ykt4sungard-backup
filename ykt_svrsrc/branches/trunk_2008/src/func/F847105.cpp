/* --------------------------------------------
 * ��������: F47105.sqc
 * ��������: 9 17 2004
 * ��������: ��Ҷ��
 * �汾��Ϣ: 1.0.0.0
 * ������:  �˿�
 * --------------------------------------------
 * �޸�����:2004-10-12
 * �޸���Ա:	�Ž�
 * �޸�����: ���Ӽ��˽��״���
 * �汾��Ϣ:1.0.0.1
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����: 2008-3-8
 * �޸���Ա: ����
 * �޸�����: 
 * 1. �޸Ŀ��ⲻƽ�˿��ж� 
 * 2. �����˿�ʱ�˲����Ĳ���
 *    �˲��� 
 *     �裺���첹��
 *     �����ֽ�
 *    ���˲���
 *     �裺���첹��
 *     ����Ӫҵ������
 *
 * �汾��Ϣ:1.0.0.2
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����: 2008-3-26
 * �޸���Ա: ����
 * �޸�����: 
 * 1. �޸Ŀ��ⲻƽ�˿�����
 * 2. �������·�ʱ�Ѿ���������˻����˿�ʱ���ݿ��в������κ����������ȡ���
 * 3. ��ϸ��Ƽ����������˿�ҵ������ĵ�
 *
 * �汾��Ϣ:1.0.0.3
 * ��ע��Ϣ:
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

/*
 * \brief ��������δ��ȡ����״̬Ϊ����ȡ
 */
static int do_refundment_subsidy(T_t_aif_account *account,double *subsidy_money,char *oper_code,int subsidy_no)
{
	T_t_tif_subsidy tSubsidy;
	char tx_date[9]="";
	char tx_time[7]="";
	double total_money = 0.0;
	int ret;
	char status[2] = "";

	getsysdate(tx_date);
	getsystime(tx_time);
	status[0] = SUBSIDY_STAT_NORMAL;
	// �����׿����˿�
	ret = DB_t_tif_subsidy_open_select_for_update_by_c3_and_card_no_and_status(
		account->card_id,status);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			writelog(LOG_ERR,"open subsidy error,card_id[%d],ret[%d]",account->card_id,ret);
			return E_DB_SUBSIDY_R;
		}
	}
	else
	{
		while(1)
		{
			memset(&tSubsidy,0,sizeof tSubsidy);
			ret = DB_t_tif_subsidy_fetch_select_by_c3(&tSubsidy);
			if(ret)
			{
				if(DB_NOTFOUND == ret)
					break;
				writelog(LOG_ERR,"read subsidy error,card_id[%d],ret[%d]",account->card_id,ret);
				return E_DB_SUBSIDY_R;
			}
			if(subsidy_no > -1 && tSubsidy.subsidy_no <= subsidy_no)
			{
				writelog(LOG_INFO,"cardid[%d]online subsidy_no[%d],db subsidy_no[%d] ignore",
						 account->card_id,subsidy_no,tSubsidy.subsidy_no);
				continue;
			}
			total_money += D4U5(tSubsidy.amount,2);
			tSubsidy.status[0] = SUBSIDY_STAT_FINISHED;
			des2src(tSubsidy.get_date,tx_date);
			des2src(tSubsidy.get_time,tx_time);
			des2src(tSubsidy.oper_code,oper_code);
			ret = DB_t_tif_subsidy_update_lock_by_c3(&tSubsidy);
			if(ret)
			{
				writelog(LOG_ERR,"update subsidy error,card_id[%d],subsidy_no[%d],ret[%d]",
						 tSubsidy.card_no,tSubsidy.subsidy_no,ret);
				return E_DB_SUBSIDY_U;
			}
		}
	}
	*subsidy_money = total_money;
	return 0;
}

/**
 * \brief ���ݿ��ⲻƽ�Ľ�������̿��
 */
static int do_close_account(InAcc *IA,double diff_money)
{
	InAcc subIA;
	int ret;
	memset(&subIA,0,sizeof subIA);
	subIA = *IA;
	subIA.dArrInAmt[0] = 0;
	subIA.dArrInAmt[1] = 0;
	subIA.dArrInAmt[2] = 0;
	subIA.dArrInAmt[3] = 0;
	subIA.dArrInAmt[4] = 0;
	subIA.dArrInAmt[5] = 0;
	// ���������0
	// ��� �����˻� ���� ���̿�
	if(amtcmp(diff_money,0.0) > 0)
	{
		subIA.dArrInAmt[4] = diff_money;
		des2src(subIA.sArrInActno[2],IA->sArrInActno[0]);	//���ʻ�
	}
	else
	{
		// ��� ���̿� ���� �����˻�
		//IA->dArrInAmt[0] = withdrawal_money -
		subIA.dArrInAmt[5] = -diff_money;
		des2src(subIA.sArrInActno[3],IA->sArrInActno[0]);	//���ʻ�
	}
	
	ret = AccountProcess(&subIA);
	if(ret)
	{
		writelog(LOG_ERR,"account[%s],close account ret[%d]",subIA.sArrInActno[0],ret);
		return ret;
	}
	IA->iSubIndex = subIA.iSubIndex;
	return 0;
}
/**
 * \brief ��������ҵ��
 */
static int process(ST_PACK *rPack,InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret =0;
	int *ptype=NULL;
	double dSerialNo=0;
	int upd_flag=0;
	char temp[128] = "";
	T_t_aif_account  	tAccount;
	T_t_cif_customer	tCustomer;
	T_t_pif_card		tCard;
	T_t_pif_spefee 	tSpeFee;
	int cancel_account = 1;
	double subsidy_money = 0.0;
	double withdrawal_money = 0.0;
	double max_diff_money = 0.0;
	double diff_money = 0.0;
	
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	
	ret = GetParameter(GLOBAL_MAX_DIFF_MONEY,temp);
	if(ret)
	{
		return ret;
	}
	max_diff_money = D4U5(atof(temp),2);
	//ע��ԭ��
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(p->card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	if(p->card_id!=tCard.card_id)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",p->card_id,tCard.card_id);
		return E_DB_CARD_R;
	}
	p->deposit_fee =tCard.deposit_fee;			//Ѻ��
//	tCard.deposit_fee=0;
	des2src(tCard.state_id,CARDSTAT_LOGOUT);		//ע��
	des2src(tCard.end_time,p->operate_date);			//ע������
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",tCard.card_id);
		return E_DB_CARD_U;
	}
	DB_t_pif_card_free_lock_by_cur();
	//����ǷǼ�����ʱ����ע���ͻ�
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
		tCustomer.cut_state=CUSTSTAT_LOGOUT;		//ע��
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
	IA->iFeeType=tCustomer.fee_type;
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(tCard.card_id,PURSE_NO_ONE, &tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,tCard.card_id);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	/*Changed by hhd at 2005-10-22 14:21
	   �����ⲻƽ���˿����⣬������ⲻ�ȣ����жϿ����
	   �Ƿ�С�ڿ����������������˳��������տ����
	   �Ϳ����Ĳ�ֵ�����˿������Ѱ��ղ�ֵ���м������
	   ������˻������˻���ע�����ȴ�δ�ϴ�����ˮ
	*/
	if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)					//�п�����
	{
		withdrawal_money = tAccount.cur_freebala + tAccount.reserve_bala;
		//writelog(LOG_DEBUG,"InCardBala[%lf],withdrawal[%lf]",IA->dInCardBala,withdrawal_money);
		// �������+δ��ȡ��� С�ڿ�����������˿�
		if(amtcmp(D4U5(withdrawal_money,2),IA->dInCardBala)<0)
		{
			// ����ֵ���ڲ����趨ʱ���������˿�
			if(amtcmp(D4U5(IA->dInCardBala-withdrawal_money,2),max_diff_money) > 0)
			{
				writelog(LOG_DEBUG,"card_id[%d] act_id[%s] cur_freebala[%lf],input card_balance[%lf]",
					 tCard.card_id,tAccount.account_id,tAccount.cur_freebala,IA->dInCardBala);
				return E_CARD_ACC_NO_EQ;
			}
			// ��������˿�
			withdrawal_money = IA->dInCardBala;
		}
		else if(amtcmp(D4U5(withdrawal_money,2),IA->dInCardBala)>0)
		{
			writelog(LOG_DEBUG,"card_id[%d] act_id[%s] cur_freebala[%lf],input card_balance[%lf],withdrawal[%lf]",
					 tCard.card_id,tAccount.account_id,tAccount.cur_freebala,IA->dInCardBala,withdrawal_money);
			//ֻ�޸ķ��������ȫ�ˣ���ˮ����ģ����д����
			strcpy(p->reserve_2,"���ⲻ��|��������˿�");
			// ����
			withdrawal_money = IA->dInCardBala;
		}
		else
		{
			//withdrawal_money = tAccount.cur_freebala;
			withdrawal_money = IA->dInCardBala;
		}
	}
	else				//�޿��˿�
	{
		//�������Ϳ��п�������̫�󣬲�����
		if(amtcmp(fabs(tAccount.cur_freebala -tAccount.card_balance),max_diff_money)>0)
		{
			writelog(LOG_DEBUG,"card_id[%d] act_id[%s] cur_freebala[%lf], db card_balance[%lf]",
					 tCard.card_id,tAccount.account_id,tAccount.cur_freebala,tAccount.card_balance);
			return E_CARD_ACC_NO_EQ;
		}
		else			// ����С��ֵ��
			withdrawal_money = (tAccount.cur_freebala > tAccount.card_balance ? tAccount.card_balance :tAccount.cur_freebala)+tAccount.reserve_bala;
	}

	des2src(IA->sArrInActno[0],tAccount.account_id);	//���ʻ�

	// �Ƿ���δ��ȡ����, ���˲���
	if(IS_YES==rPack->lvol4)
	{
		// ����δ��ȡ�������
		if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)					//�п�����
		{
			ret = do_refundment_subsidy(&tAccount,&subsidy_money,p->oper_code,rPack->lvol5);
			// �˿��� = ����� + ����ȡ��� 
			withdrawal_money += subsidy_money;
		}
		else
		{
			ret = do_refundment_subsidy(&tAccount,&subsidy_money,p->oper_code,-1);
			if(ret==0)
			{
				if(amtcmp(D4U5(subsidy_money,2),D4U5(tAccount.reserve_bala,2))!=0)
				{
					writelog(LOG_ERR,"ϵͳ����ȷ,card_id[%d]subsidy [%.2f],current[%.2f]",
							 tAccount.card_id,subsidy_money,tAccount.reserve_bala);
					return E_RESERVE_BALA_DIFF;
				}
			}
		}
		if(ret)
		{
			return ret;
		}
		writelog(LOG_DEBUG,"account[%s]cardid[%d],subsidy_money[%.2f]",
				 tAccount.account_id,tAccount.card_id,subsidy_money);
	}


	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  						//��������ˮ��
	if(ret)
	{
		return ret;
	}

	//ע���ʻ�
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_lock_by_cur_and_account_id(IA->sArrInActno[0],&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_lock_by_cur_and_account_id ret[%d]account_id[%s]",
				 ret,IA->sArrInActno[0]);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}

	tAccount.cur_freebala += tAccount.reserve_bala + tAccount.cur_frozebala;
	// �˿������Ҫ���϶������
	withdrawal_money += tAccount.cur_frozebala;
	tAccount.reserve_bala = 0.0;
	tAccount.cur_frozebala = 0.0;
	// �����˿�ʱ���
	//writelog(LOG_DEBUG,"cur_bala[%lf],withdrawal_money[%lf]",tAccount.cur_bala,withdrawal_money);
	diff_money = tAccount.cur_bala - withdrawal_money;
	
	ret = DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_update_lock_by_cur ret[%d]account_id[%s]",ret,tAccount.account_id);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_U;
	}
	DB_t_aif_account_free_lock_cur();

	//des2src(IA->sArrInActno[1],tAccount.account_id);	//���ʻ�
	//��Ԥ�����תΪѧУ����
	p->serial_no=D2I(dSerialNo);
	des2src(p->showid,tCard.showid);		//��ʾ����
	p->in_fee = 0;							//�����/������
	//p->trade_fee = tAccount.cur_freebala;			//�������//Changed by hhd at 2005-10-22 14:21
	p->trade_fee = withdrawal_money;
	p->boardfee	=  tAccount.cur_frozebala;		//������//Changed by hhd at 2005-10-22 14:21
	IA->iTradeNo=p->serial_type;				//������
	IA->iMainDevId=p->maindevice_id;			//����վ��ʶ
	IA->iDevId=p->device_id;					//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	des2src(IA->sTxDate,p->operate_date);		//��������
	des2src(IA->sTxTime,p->operate_time);		//����ʱ��
	des2src(IA->sTxCollectDate,p->collect_date);	//�ɼ�����
	des2src(IA->sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
	des2src(IA->sTxAccDate,p->enteract_date);	//��������
	des2src(IA->sTxAccTime,p->enteract_time);	//����ʱ��
	des2src(IA->sMdeOper,p->oper_code);		//����Ա
	strcpy(IA->sChkOper,p->reserve_1);		//���˲���Ա


	ptype=(int*)IA->pVoidPointer;
	switch(*ptype)
	{
		case TYPE_CASH:	//�ֽ�
			IA->iArrInFeeSwitch[1]=1;
			break;
		case TYPE_BILL:	//֧Ʊ
			IA->iArrInFeeSwitch[2]=1;
			break;
		case TYPE_FUNDBOOK:	//���ѱ�
			IA->iArrInFeeSwitch[3]=1;
			break;
		default:
			writelog(LOG_ERR,"type[%d]",*ptype);
			IA->iArrInFeeSwitch[1]=1;
			break;
	}
	IA->pVoidPointer=NULL;
//�Ƿ��˿����ʹ���
	if(IS_YES==rPack->lvol3)
	{
		IA->iArrInFeeSwitch[5]=1;
	}
//�Ƿ���Ѻ��
	if(IS_YES==rPack->lvol2)
	{
		IA->iArrInFeeSwitch[6]=1;
	}

	IA->dArrInAmt[0]=p->trade_fee;				//�����
	//IA->dArrInAmt[1]=p->boardfee;				//����
	IA->dArrInAmt[2]=p->deposit_fee;			//Ѻ��
	if(amtcmp(diff_money,0.0) != 0)
	{
		writelog(LOG_DEBUG,"card balance not same,cardid[%d]diff[%.2f]",tAccount.card_id,diff_money);
		ret = do_close_account(IA,diff_money);
		if(ret)
		{
			return ret;
		}
	}
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	//ע���ʻ�
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_lock_by_cur_and_account_id(IA->sArrInActno[0],&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_lock_by_cur_and_account_id ret[%d]account_id[%s]",
				 ret,IA->sArrInActno[0]);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	//Changed by hhd at 2005-10-22 14:21
	//�޸��˻�״̬ʱ����Щ�˻���Ϊ4��ʱ״̬
	//�ȴ�δ�ϴ���ˮ�ش�����
	//if(strcmp(p->reserve_2,"���ⲻ��|��������˿�")==0)
	// modify 2008-3-26
	// �����޸�Ϊ���ⲻƽ���˿����������ӳ��̿��Ŀ���ˣ���˲�����Ҫ��ʱ״̬��
	if(!cancel_account)
	{
		tAccount.current_state= ACCOUNTSTAT_TEMP;			//��ʱ״̬
	}
	else
	{
		tAccount.current_state= ACCOUNTSTAT_LOGOUT;			//ע��
	}
	des2src(tAccount.close_date,p->operate_date);			//��������
	des2src(tAccount.close_time,p->operate_time);			//����ʱ��
	ret=DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_update_lock_by_cur ret[%d]account_id[%s]",ret,tAccount.account_id);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_U;
	}
	DB_t_aif_account_free_lock_cur();
	writelog(LOG_ERR,"out_balance= [%f],withdrawal=[%.2f]",IA->dOutCardBala,withdrawal_money);
	if(amtcmp(IA->dOutCardBala,0)>0)
	{
		return E_ENTER_ACCOUNT;
	}
	p->out_balance=0;						//����ֵ
	return 0;
}


int F847105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret =0;
	int i=0;
	int origin_card_id = 0;
	int bill_type=0;
	char physical_no[40+1] = "";
	char logicdate[11] = "";												//ҵ������
	char sysdate[11]="";
	char lost_date[11]="";
	char systime[9]="";
	char sEndDate[9]="";
	char sMsg[256]="";
	T_t_pif_card		tCard;
	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_tradeserial  tradeserial;
//	T_t_tif_savdtl tSavdtl;
	InAcc  IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&tradeserial,0,sizeof(tradeserial));
//	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&IA,0,sizeof(IA));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);											//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	origin_card_id = rPack->lvol1;   										//ԭ����
	des2src(physical_no, rPack->sbank_acc);							//������
	if(rPack->lvol1<1)
	{
		*pRetCode=E_INPUT_CARDNO_CANNOT_NULL;
		goto L_RETU;
	}
	//��ѯ֧Ʊ���ѱ����޳�ֵ��¼
	/*
	ret=ChkSavdtl(origin_card_id,&tSavdtl);
	if(ret)
	{
		writelog(LOG_ERR,"ChkSavdtl ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	//Added by hhd at 2006-06-29 begin
	//�����ж�:����뿨ֵ����100����龭�ѱ�֪���ֵ��
	//���򲻼��κ��жϣ��˿�ֽ���
	if(amtcmp(rPack->damt2,100.00)<0)
	{
		tSavdtl.bill_type=TYPE_CASH;
	}
	*/
	//Added by hhd at 2006-06-29 end

	tradeserial.other_seri_no = 0;										//�ϴ�����ˮ��
	tradeserial.serial_type=TXCODE_CALLBACK_CARD;						//���ܺ�
	tradeserial.serial_state = SERISTAT_DEBT;								//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);							//��������
	des2src(tradeserial.operate_time,systime);							//����ʱ��
	des2src(tradeserial.collect_date,sysdate);								//�ɼ�����
	des2src(tradeserial.collect_time,systime);								//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);							//��������
	des2src(tradeserial.enteract_time,systime);							//����ʱ��
	tradeserial.maindevice_id = rPack->lvol6;								//�ϴ�����վ��ʶ
	tradeserial.device_id = rPack->lvol7;									//�ɼ��豸��ʶ
	tradeserial.purse_id = PURSE_NO_ONE;								//Ǯ����
	tradeserial.sys_id = 0;												//�ⲿϵͳ��ʶ
	des2src(tradeserial.oper_code, rPack->scust_limit);					//����Ա��
	tradeserial.card_id=origin_card_id;
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(origin_card_id,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
//	writelog(LOG_DEBUG,"input card_id[%d] card_id[%d]",origin_card_id,tCard.card_id);
	tradeserial.customer_id = tCard.cosumer_id;							//�ͻ���ʶ
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)==0)
	{
		//����״̬�£��޿����ܻ���
		if(IS_YES!=rPack->lvol12)
		{
			*pRetCode = E_NOCARD;
			goto L_RETU;
		}

		////����������Ƿ�һ��
		trim(physical_no);
		trim(tCard.physical_no);
		if(strcmp(tCard.physical_no,physical_no)!=0)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,physical_no);
			*pRetCode= E_CARD_PHYNO_DIFFER;
			goto L_RETU;
		}
	}
	else if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	//changed by hhd��̩���ֳ��޸ģ�����Ҳ�����������������Ϊ��Ԥ
	//����д��ʧ�ܺ�����д��ʧ�ܣ����ѿ�Ϊ׼�˿������ε������ж�
	/*
	else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARD_CHANGE;
		goto L_RETU;
	}
	*/
	else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
	{
		if('1' != rPack->sstatus0[0])				//�������տ������Ƕ���״̬
		{
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode=E_CARDNO_FREEZE;
			goto L_RETU;
		}
	}
	/*
	else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	*/
	else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
	{
		if(IS_YES==rPack->lvol12)
		{
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode=E_CARDNO_LOST;
			goto L_RETU;
		}
		/*
		ret=DB_t_pif_cardlossinfo_read_by_card_id_and_state_id(origin_card_id, STATE_VALID, &cardlossinfo);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"lost_card_id[%d]",origin_card_id);
			if(DB_NOTFOUND==ret)
				*pRetCode =  E_CARDNO_NOT_EXIST;
			else
				*pRetCode =  E_DB_CARD_R;
			goto L_RETU;
		}
		*/
		ret=get_latest_lost_date_by_card_no(origin_card_id,lost_date);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"lost_card_id[%d]",origin_card_id);
			*pRetCode =ret;
			goto L_RETU;
		}
		//�ȼ��ͻ��Ĺ�ʧ����ʽ���Ƿ��˲�������
		ret=GetLostCardValiddate(lost_date,sEndDate);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode =ret;
			goto L_RETU;
		}
		if(strncmp(sEndDate,sysdate,8)>0)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"lost_normal_card_id[%d]lost_date[%s]end_date[%s]",origin_card_id,lost_date,sEndDate);
			*pRetCode =  E_NORMALCARD_NOT_REACH_ENDDATE;
			goto L_RETU;
		}
/*
		//���¿���ʧ���ڱ��иÿ�״̬Ϊ��Ч
		ret=UpdateCardLossInfoState(origin_card_id,STATE_VALID,STATE_INVALID);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode =ret;
			goto L_RETU;
		}
*/
		//��������µ�Ѻ�����˵�,�����������ʧ���˵�
//		IsReturnDeposit=IS_NO;
	}
	else if(IS_YES!=rPack->lvol12)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_NOCARD;
		goto L_RETU;
	}
	//ע��ԭ��
	des2src(tCard.state_id,CARDSTAT_LOGOUT);		//ע��
	des2src(tCard.end_time,tradeserial.operate_date);	//ע������
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",tCard.card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode =   E_CARDNO_NOT_EXIST;
		else
			*pRetCode =  E_DB_CARD_R;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();

	//�Ƿ��˷�,�涨��ʽ������ʱ����Ѻ��,�Ǽ�����ʱ����Ѻ��
	if(IS_YES==rPack->lvol12)
	{
		IA.iUseCardFlag=USE_CARD_TYPE_ONLINE;		//��������
		IA.dInCardBala = rPack->damt2;				//�뿨ֵ
		IA.dOutCardBala=-1;							//-1 ��ʾ��ֵ
		IA.iTxCnt = rPack->lvol10+1;					//��ǰ�����״���
		tradeserial.in_balance = IA.dInCardBala;			//�뿨ֵ
		tradeserial.trade_count = IA.iTxCnt;
	}
	else
	{
		IA.iUseCardFlag=USE_CARD_TYPE_NULL;
		IA.dInCardBala = -1;				//-1 ��ʾ��ֵ
		IA.dOutCardBala=-1;				//-1 ��ʾ��ֵ
		IA.iTxCnt = -1;					//-1 ��ʾ��ֵ
	}
	bill_type=TYPE_CASH;
//	IA.pVoidPointer=&tSavdtl.bill_type;
	IA.pVoidPointer=&bill_type;
	IA.iCardNo=tCard.card_id;

	ret=process(rPack,&IA,&tradeserial);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"input card_id[%d] card_id[%d]",origin_card_id,tCard.card_id);
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode= E_DB_TRADESERIAL_E;
		else
			*pRetCode= E_DB_TRADESERIAL_I;
		goto L_RETU;
	}

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_DAMT3,F_DAMT4,F_SDATE0,F_LVOL1,F_SPHONE,F_LSERIAL1,F_VSMESS,0);
	sprintf(out_pack->vsmess,"��ˮ��:%d ����:%d ",IA.iSerialNo,IA.iCardNo);
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
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
			/*
			if((TXTYPE_DRAW_BILL==IA.iArrOutTxType[i])||
			   (TXTYPE_DRAW_FUNDBOOK==IA.iArrOutTxType[i])||
			   (TXTYPE_DRAW_OTHER==IA.iArrOutTxType[i]))
			{
				sprintf(sMsg,"Ʊ�ݺ���:%s ",tSavdtl.bill_no);
				strcat(out_pack->vsmess,sMsg);
			}
			*/
		}
	}
	sprintf(sMsg,"ʵ��Ӧ�˽��:%.2lfԪ",out_pack->damt0);
		strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
//		out_pack->lvol1=tSavdtl.bill_type;
	out_pack->lvol1=bill_type;
//	des2src(out_pack->sdate0,tSavdtl.tx_date);
//	out_pack->damt1=tSavdtl.amount;							//���ѱ���ֵ���
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��
//		des2src(out_pack->sphone,tSavdtl.bill_no);
	ret = InsertToCutUpdList(origin_card_id, CUTUPD_CANCEL,tCard.physical_no);
	if( ret )
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

