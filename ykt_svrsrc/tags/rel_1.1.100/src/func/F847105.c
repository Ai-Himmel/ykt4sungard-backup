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

static int process_change_card(const T_t_cif_customer* tCustomer,T_t_pif_card *originCard)
{
	int ret = 0;
	int mainCardId = 0;
	T_t_pif_card tCard;
	// ���ע���Ĳ��ǹ�����ʱ��ֱ��������
	if( CT_TEMP != originCard->type_id )
	{
		ret = InsertToBlkList(originCard->card_id,CANCEL_BLACKLIST);
		return ret;
	}
	ret = DB_t_pif_card_open_select_by_c1_and_cosumer_id(tCustomer->cut_id);
	if( ret )
	{
		return ret;
	}
	while(1)
	{
		memset(&tCard,0,sizeof(T_t_pif_card));
		ret = DB_t_pif_card_fetch_select_by_c1(&tCard);
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
		if(CT_NORMAL == tCard.type_id && strncmp(tCard.state_id,CARDSTAT_LOGOUT,4) )
		{
			mainCardId = tCard.card_id;
		}
		if( strncmp(tCard.state_id,CARDSTAT_REG,4) == 0 )
		{
			// �ҵ���һ�������Ŀ�
			mainCardId = tCard.card_id;
			DB_t_pif_card_close_select_by_c1();
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
static int process(ST_PACK *rPack,InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret =0;
	int *ptype=NULL;
	double dSerialNo=0;
	int upd_flag=0;
	T_t_aif_account  	tAccount;
	T_t_cif_customer	tCustomer;
	T_t_pif_card		tCard;
	T_t_pif_spefee 	tSpeFee;

	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));
	memset(&tSpeFee,0,sizeof(tSpeFee));
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
	if(USE_CARD_TYPE_ONLINE==IA->iUseCardFlag)					//�п�����
	{
		if(amtcmp(D4U5(tAccount.cur_freebala,2),IA->dInCardBala)!=0)
		{
			writelog(LOG_ERR,"card_id[%d] act_id[%s] cur_freebala[%lf],input card_balance[%lf]",tCard.card_id,tAccount.account_id,tAccount.cur_freebala,IA->dInCardBala);
			return E_CARD_ACC_NO_EQ;
		}
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  						//��������ˮ��
	if(ret)
	{
		return ret;
	}
	//��Ԥ�����תΪѧУ����
	p->serial_no=(int)dSerialNo;
	des2src(p->showid,tCard.showid);		//��ʾ����
	p->in_fee = 0;							//�����/������
	p->trade_fee = tAccount.cur_freebala;			//�������
	p->boardfee	=  tAccount.cur_frozebala;		//������
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
	strcpy(IA->sChkOper,p->reserve_1);			//���˲���Ա

	des2src(IA->sArrInActno[0],tAccount.account_id);	//���ʻ�

	if(IS_YES==IA->iArrInFeeSwitch[3])				//�˿���
	{
		ptype=(int*)IA->pVoidPointer;
		switch(*ptype)
		{
			case TYPE_CASH:
				IA->dArrInAmt[1]=p->trade_fee;
				break;
			case TYPE_BILL:
				IA->dArrInAmt[2]=p->trade_fee;
				break;
			case TYPE_FUNDBOOK:
				IA->dArrInAmt[3]=p->trade_fee;
				break;
			case TYPE_OTHER:
				IA->dArrInAmt[4]=p->trade_fee;
				break;
			default:
				writelog(LOG_ERR,"type[%d]",*ptype);
				IA->dArrInAmt[1]=p->trade_fee;
				break;
		}
	}
	else
		IA->dArrInAmt[0]=p->trade_fee;
	IA->dArrInAmt[5]=p->deposit_fee;				//Ѻ��
	IA->dArrInAmt[6]=p->boardfee;				//����

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
	tAccount.current_state= ACCOUNTSTAT_LOGOUT;			//ע��
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

	if(amtcmp(IA->dOutCardBala,0)>0)
	{
		return E_ENTER_ACCOUNT;
	}
	p->out_balance=0;						//����ֵ

	ret = process_change_card(&tCustomer,&tCard);
	return ret;
}

int F847105(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret =0;
	int i=0;
	int origin_card_id = 0;
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
	T_t_tif_savdtl tSavdtl;
	InAcc  IA;

	memset(&tCard,0,sizeof(tCard));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSavdtl,0,sizeof(tSavdtl));
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
	ret=ChkSavdtl(origin_card_id,&tSavdtl);
	if(ret)
	{
		writelog(LOG_ERR,"ChkSavdtl ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
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
		//����������Ƿ�һ��
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
	else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARD_CHANGE;
		goto L_RETU;
	}
	else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARDNO_FREEZE;
		goto L_RETU;
	}
	else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
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
	IA.pVoidPointer=&tSavdtl.bill_type;
	IA.iCardNo=tCard.card_id;

	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;

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

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
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
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				out_pack->damt0+=IA.dArrOutAmt[i];
				break;
			case TXTYPE_DEDUCT_BOARD:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_RETURN_BOARD:
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
			if((TXTYPE_DRAW_BILL==IA.iArrOutTxType[i])||
			   (TXTYPE_DRAW_FUNDBOOK==IA.iArrOutTxType[i])||
			   (TXTYPE_DRAW_OTHER==IA.iArrOutTxType[i]))
			{
				sprintf(sMsg,"Ʊ�ݺ���:%s ",tSavdtl.bill_no);
				strcat(out_pack->vsmess,sMsg);
			}
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
	out_pack->lvol1=tSavdtl.bill_type;
	des2src(out_pack->sdate0,tSavdtl.tx_date);
	out_pack->damt1=tSavdtl.amount;							//���ѱ���ֵ���
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��
	des2src(out_pack->sphone,tSavdtl.bill_no);

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

