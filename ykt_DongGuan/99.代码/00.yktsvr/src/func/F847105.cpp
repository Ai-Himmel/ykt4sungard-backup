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
/*
static int process_change_card(const T_t_customer* tCustomer,T_t_card *originCard)
{
	int ret = 0;
	int mainCardId = 0;
	T_t_card tCard;
	// ���ע���Ĳ��ǹ�����ʱ��ֱ��������
	if( CT_TEMP != originCard->type_id )
	{
		ret = InsertToBlkList(originCard->cardno,CANCEL_BLACKLIST);
		return ret;
	}
	ret = DB_t_card_open_select_by_c1_and_custid(tCustomer->custid);
	if( ret )
	{
		return ret;
	}
	while(1)
	{
		memset(&tCard,0,sizeof(T_t_card));
		ret = DB_t_card_fetch_select_by_c1(&tCard);
		if( ret )
		{
			if(ret == DB_NOTFOUND)
			{
				ret = 0;
				break;
			}
			else
				return E_DB_CARD_R;

		}
		// �����¼��ʽ��
		if(CT_NORMAL == tCard.type_id && strncmp(tCard.cardattr,CARDSTAT_LOGOUT,4) )
		{
			mainCardId = tCard.cardno;
		}
		if( strncmp(tCard.cardattr,CARDSTAT_REG,4) == 0 )
		{
			// �ҵ���һ�������Ŀ�
			mainCardId = tCard.cardno;
			DB_t_card_close_select_by_c1();
			break;
		}
	}
	if( mainCardId != 0 )
	{
		// ���ɻ�������
		ret = InsertToBlkList(mainCardId,CHCARD_BLACKLIST);
	}
	return ret;
}
*/

static int do_refundment_subsidy(T_t_aif_account *account,double *subsidy_money,char *opercode,int subsidy_no)
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
	ret = DB_t_tif_subsidy_open_select_for_update_by_c3_and_cardno_and_status(
		account->cardno,status);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			writelog(LOG_ERR,"open subsidy error,cardno[%d],ret[%d]",account->cardno,ret);
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
				writelog(LOG_ERR,"read subsidy error,cardno[%d],ret[%d]",account->cardno,ret);
				return E_DB_SUBSIDY_R;
			}
			if(subsidy_no > -1 && tSubsidy.subsidy_no < subsidy_no)
			{
				writelog(LOG_INFO,"cardid[%d]online subsidy_no[%d],db subsidy_no[%d] ignore",
						 account->cardno,subsidy_no,tSubsidy.subsidy_no);
				continue;
			}
			total_money += D4U5(tSubsidy.amount,2);
			tSubsidy.status[0] = SUBSIDY_STAT_FINISHED;
			des2src(tSubsidy.get_date,tx_date);
			des2src(tSubsidy.get_time,tx_time);
			des2src(tSubsidy.opercode,opercode);
			ret = DB_t_tif_subsidy_update_lock_by_c3(&tSubsidy);
			if(ret)
			{
				writelog(LOG_ERR,"update subsidy error,cardno[%d],subsidy_no[%d],ret[%d]",
						 tSubsidy.cardno,tSubsidy.subsidy_no,ret);
				return E_DB_SUBSIDY_U;
			}
		}
	}
	*subsidy_money = total_money;
	return 0;
}
static int do_accounting_subsidy(InAcc *IA,double subsidy_money)
{
	InAcc subIA;
	int ret;
	memset(&subIA,0,sizeof subIA);
	subIA = *IA;
	if(amtcmp(subsidy_money,0.0) < 0)
	{
		// ��ȡ���� 
		subIA.dArrInAmt[0] = subsidy_money;
		subIA.iTradeNo = TXCODE_SUBSIDY_LOG;
		subIA.iArrInFeeSwitch[7]=0;
	}
	else if(amtcmp(subsidy_money,0.0) > 0)
	{
		subIA.dArrInAmt[0] = subsidy_money;
		subIA.iTradeNo = TXCODE_SUBSIDY_LOG;
		subIA.iArrInFeeSwitch[7]=1;
	}
	else
		return 0;
	ret=AccountProcess(&subIA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	IA->iSubIndex = 1;
	return 0;
}

static int process(ST_PACK *rPack,InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret =0;
	int *ptype=NULL;
	double dSerialNo=0;
	int upd_flag=0;
	T_t_aif_account  	tAccount;
	T_t_customer	tCustomer;
	T_t_card		tCard;
	T_t_spefee 	tSpeFee;
	int cancel_account = 1;
	double subsidy_money = 0.0;

	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	//ע��ԭ��
	ret=DB_t_card_read_lock_by_c0_and_cardno(p->cardno, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	if(p->cardno!=tCard.cardno)
	{
		DB_t_card_free_lock_by_c0();
		writelog(LOG_ERR,"cardno[%d] db cardno[%d]",p->cardno,tCard.cardno);
		return E_DB_CARD_R;
	}
	p->depositfee =tCard.depositfee;			//Ѻ��
//	tCard.depositfee=0;
	des2src(tCard.cardattr,CARDSTAT_LOGOUT);		//ע��
	des2src(tCard.endtime,p->operate_date);			//ע������
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		return E_DB_CARD_U;
	}
	DB_t_card_free_lock_by_c0();
	//����ǷǼ�����ʱ����ע���ͻ�
	ret=DB_t_customer_read_lock_by_cur_and_custid(tCard.custid,&tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"custid[%d]",tCard.custid);
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
				return E_DB_SPEFEE_R;

			}
		}
		else
		{
			tCustomer.feetype=tSpeFee.feetype;
		}
		upd_flag=1;
	}
	if(upd_flag)
	{
		ret=DB_t_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			writelog(LOG_ERR,"custid[%d]",tCard.custid);
			return E_DB_CUSTOMER_U;
		}
	}
	DB_t_customer_free_lock_cur();
	IA->iFeeType=tCustomer.feetype;
	ret=DB_t_aif_account_read_by_cardno_and_purseno(tCard.cardno,PURSE_NO_ONE, &tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_cardno_and_purseno ret[%d]cardno[%d]",ret,tCard.cardno);
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
		if(amtcmp(D4U5(tAccount.cur_freebala,2),IA->dInCardBala)<0)
		{
			writelog(LOG_ERR,"cardno[%d] act_id[%s] cur_freebala[%lf],input card_balance[%lf]",tCard.cardno,tAccount.account_id,tAccount.cur_freebala,IA->dInCardBala);
			return E_CARD_ACC_NO_EQ;
		}
		if(amtcmp(D4U5(tAccount.cur_freebala,2),IA->dInCardBala)>0)
		{
			writelog(LOG_ERR,"cardno[%d] act_id[%s] cur_freebala[%lf],input card_balance[%lf]",tCard.cardno,tAccount.account_id,tAccount.cur_freebala,IA->dInCardBala);
			//ֻ�޸ķ��������ȫ�ˣ���ˮ����ģ����д����
			p->trade_fee = IA->dInCardBala;			//�������//Changed by hhd at 2005-10-22 14:21
			strcpy(p->reserve_2,"���ⲻ��|��������˿�");
			// ������
			cancel_account = 0;
			//p->managefee	=  (D4U5(tAccount.cur_freebala,2)-IA->dInCardBala);
		}
		else p->trade_fee = tAccount.cur_freebala;
	}
	else
	{
		p->trade_fee = tAccount.cur_freebala;			//�������//Changed by hhd at 2005-10-22 14:21
	}

	des2src(IA->sArrInActno[0],tAccount.account_id);	//���ʻ�

	// �Ƿ���δ��ȡ����, ���˲���
	if(IS_YES==rPack->lvol4)
	{
		// ����δ��ȡ�������
		if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)					//�п�����
			ret = do_refundment_subsidy(&tAccount,&subsidy_money,p->opercode,rPack->lvol5);
		else
			ret = do_refundment_subsidy(&tAccount,&subsidy_money,p->opercode,-1);
		if(ret)
		{
			return ret;
		}
		/*
		ret = do_accounting_subsidy(IA,subsidy_money);
		if(ret)
		{
			writelog(LOG_ERR,"accounting subsidy error,ret[%d]",ret);
			return ret;
		}
		*/
		if(amtcmp(subsidy_money,0.0)>0)
		{
			IA->dArrInAmt[4] = subsidy_money;
		}
		else
		{
			IA->dArrInAmt[5] = -subsidy_money;
		}
		p->trade_fee += subsidy_money;
		//IA->dInCardBala += subsidy_money;
		writelog(LOG_DEBUG,"account[%s]cardid[%d],subsidy_money[%.2f]",
				 tAccount.account_id,tAccount.cardno,subsidy_money);
	}


	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  						//��������ˮ��
	if(ret)
	{
		return ret;
	}
	//��Ԥ�����תΪѧУ����
	p->serial_no=D2I(dSerialNo);
	des2src(p->showid,tCard.showid);		//��ʾ����
	p->in_fee = 0;							//�����/������
	//p->trade_fee = tAccount.cur_freebala;			//�������//Changed by hhd at 2005-10-22 14:21
	p->managefee	=  tAccount.cur_frozebala;		//������//Changed by hhd at 2005-10-22 14:21
	IA->iTradeNo=p->serial_type;				//������
	IA->iMainDevId=p->maindeviceid;			//����վ��ʶ
	IA->iDevId=p->deviceid;					//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	des2src(IA->sTxDate,p->operate_date);		//��������
	des2src(IA->sTxTime,p->operate_time);		//����ʱ��
	des2src(IA->sTxCollectDate,p->collect_date);	//�ɼ�����
	des2src(IA->sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
	des2src(IA->sTxAccDate,p->enteract_date);	//��������
	des2src(IA->sTxAccTime,p->enteract_time);	//����ʱ��


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
	IA->dArrInAmt[1]=p->managefee;				//����
	IA->dArrInAmt[2]=p->depositfee;				//Ѻ��

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
		writelog(LOG_ERR,"DB_t_aif_account_read_lock_by_cur_and_account_id ret[%d]account_id[%s]",ret,IA->sArrInActno[0]);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	//Changed by hhd at 2005-10-22 14:21
	//�޸��˻�״̬ʱ����Щ�˻���Ϊ4��ʱ״̬
	//�ȴ�δ�ϴ���ˮ�ش�����
	//if(strcmp(p->reserve_2,"���ⲻ��|��������˿�")==0)
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
	writelog(LOG_ERR,"out_balance= [%f]",IA->dOutCardBala);
	if(amtcmp(IA->dOutCardBala,0)>0)
	{
		return E_ENTER_ACCOUNT;
	}
	p->out_balance=0;						//����ֵ
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
	int origin_cardno = 0;
	int billtype=0;
	char cardphyid[16+1] = "";
	char logicdate[11] = "";												//ҵ������
	char sysdate[11]="";
	char lost_date[11]="";
	char systime[9]="";
	char sEndDate[9]="";
	char sMsg[256]="";
	T_t_card		tCard;
	T_t_cardlossinfo cardlossinfo;
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
	origin_cardno = rPack->lvol1;   										//ԭ����
	des2src(cardphyid, rPack->sbank_acc);							//������
	if(rPack->lvol1<1)
	{
		*pRetCode=E_INPUT_CARDNO_CANNOT_NULL;
		goto L_RETU;
	}
	//��ѯ֧Ʊ���ѱ����޳�ֵ��¼
	/*
	ret=ChkSavdtl(origin_cardno,&tSavdtl);
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
		tSavdtl.billtype=TYPE_CASH;
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
	tradeserial.maindeviceid = rPack->lvol6;								//�ϴ�����վ��ʶ
	tradeserial.deviceid = rPack->lvol7;									//�ɼ��豸��ʶ
	tradeserial.purseno = PURSE_NO_ONE;								//Ǯ����
	tradeserial.sys_id = 0;												//�ⲿϵͳ��ʶ
	des2src(tradeserial.opercode, rPack->scust_limit);					//����Ա��
	tradeserial.cardno=origin_cardno;
	ret=DB_t_card_read_lock_by_c0_and_cardno(origin_cardno,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
//	writelog(LOG_DEBUG,"input cardno[%d] cardno[%d]",origin_cardno,tCard.cardno);
	tradeserial.custid = tCard.custid;							//�ͻ���ʶ
	if(strncmp(tCard.cardattr,CARDSTAT_REG,4)==0)
	{
		//����������Ƿ�һ��
		trim(cardphyid);
		trim(tCard.cardphyid);
		if(strcmp(tCard.cardphyid,cardphyid)!=0)
		{
			DB_t_card_free_lock_by_c0();
			writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,cardphyid);
			*pRetCode= E_CARD_PHYNO_DIFFER;
			goto L_RETU;
		}
	}
	else if('2'==tCard.cardattr[CARDSTAT_TYPE_REG])
	{
		DB_t_card_free_lock_by_c0();
		*pRetCode = E_CARD_CLOSE;
		goto L_RETU;
	}
	//changed by hhd��̩���ֳ��޸ģ�����Ҳ�����������������Ϊ��Ԥ
	//����д��ʧ�ܺ�����д��ʧ�ܣ����ѿ�Ϊ׼�˿������ε������ж�
	/*
	else if('3'==tCard.cardattr[CARDSTAT_TYPE_REG])
	{
		DB_t_card_free_lock_by_c0();
		*pRetCode=E_CARD_CHANGE;
		goto L_RETU;
	}
	*/
	else if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
	{
		DB_t_card_free_lock_by_c0();
		*pRetCode=E_CARD_FREEZE;
		goto L_RETU;
	}
	/*
	else if(tCard.cardattr[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
	{
		DB_t_card_free_lock_by_c0();
		*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	*/
	else if(tCard.cardattr[CARDSTAT_TYPE_LOST]==STATE_TRUE)
	{
		if(IS_YES==rPack->lvol12)
		{
			DB_t_card_free_lock_by_c0();
			*pRetCode=E_CARD_LOST;
			goto L_RETU;
		}
		/*
		ret=DB_t_cardlossinfo_read_by_cardno_and_state_id(origin_cardno, STATE_VALID, &cardlossinfo);
		if(ret)
		{
			DB_t_card_free_lock_by_c0();
			writelog(LOG_ERR,"lost_cardno[%d]",origin_cardno);
			if(DB_NOTFOUND==ret)
				*pRetCode =  E_CARDNO_NOT_EXIST;
			else
				*pRetCode =  E_DB_CARD_R;
			goto L_RETU;
		}
		*/
		ret=get_latest_lost_date_by_cardno(origin_cardno,lost_date);
		if(ret)
		{
			DB_t_card_free_lock_by_c0();
			writelog(LOG_ERR,"lost_cardno[%d]",origin_cardno);
			*pRetCode =ret;
			goto L_RETU;
		}
		//�ȼ��ͻ��Ĺ�ʧ����ʽ���Ƿ��˲�������
		ret=GetLostCardValiddate(lost_date,sEndDate);
		if(ret)
		{
			DB_t_card_free_lock_by_c0();
			*pRetCode =ret;
			goto L_RETU;
		}
		if(strncmp(sEndDate,sysdate,8)>0)
		{
			DB_t_card_free_lock_by_c0();
			writelog(LOG_ERR,"lost_normal_cardno[%d]lost_date[%s]end_date[%s]",origin_cardno,lost_date,sEndDate);
			*pRetCode =  E_NORMALCARD_NOT_REACH_ENDDATE;
			goto L_RETU;
		}
/*
		//���¿���ʧ���ڱ��иÿ�״̬Ϊ��Ч
		ret=UpdateCardLossInfoState(origin_cardno,STATE_VALID,STATE_INVALID);
		if(ret)
		{
			DB_t_card_free_lock_by_c0();
			*pRetCode =ret;
			goto L_RETU;
		}
*/
		//��������µ�Ѻ�����˵�,�����������ʧ���˵�
//		IsReturnDeposit=IS_NO;
	}
	else if(IS_YES!=rPack->lvol12)
	{
		DB_t_card_free_lock_by_c0();
		*pRetCode=E_NOCARD;
		goto L_RETU;
	}
	//ע��ԭ��
	des2src(tCard.cardattr,CARDSTAT_LOGOUT);		//ע��
	des2src(tCard.endtime,tradeserial.operate_date);	//ע������
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode =   E_CARDNO_NOT_EXIST;
		else
			*pRetCode =  E_DB_CARD_R;
		goto L_RETU;
	}
	DB_t_card_free_lock_by_c0();

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
	billtype=TYPE_CASH;
//	IA.pVoidPointer=&tSavdtl.billtype;
	IA.pVoidPointer=&billtype;
	IA.iCardNo=tCard.cardno;

	ret=process(rPack,&IA,&tradeserial);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"input cardno[%d] cardno[%d]",origin_cardno,tCard.cardno);
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
				tradeserial.depositfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_RETURN_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT_BILL:
			case TXTYPE_RETURN_DEPOSIT_FUNDBOOK:
				tradeserial.depositfee=IA.dArrOutAmt[i];
				out_pack->damt0+=IA.dArrOutAmt[i];
				break;
			case TXTYPE_DEDUCT_BOARD:
				tradeserial.managefee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial.managefee=IA.dArrOutAmt[i];
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
				sprintf(sMsg,"Ʊ�ݺ���:%s ",tSavdtl.billno);
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
//		out_pack->lvol1=tSavdtl.billtype;
	out_pack->lvol1=billtype;
//	des2src(out_pack->sdate0,tSavdtl.tx_date);
//	out_pack->damt1=tSavdtl.amount;							//���ѱ���ֵ���
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��
//		des2src(out_pack->sphone,tSavdtl.billno);
	ret = InsertToCutUpdList(origin_cardno, CUTUPD_CANCEL,tCard.cardphyid);
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

