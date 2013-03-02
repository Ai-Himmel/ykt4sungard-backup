/* --------------------------------------------
 * ��������: F847101.sqc
 * ��������: 9 17 2004
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������:  ������ʽ��
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

	p->in_balance=0;						//�뿨ֵ
	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//��������
	IA->dInCardBala=0;					//�뿨ֵ
	IA->dOutCardBala=-1;					//����ֵ
	IA->iTxCnt=1;						//���״���
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

int F847101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int	hi_cutid = 0;											//�ͻ�ID
	int	hi_cuttype = 0;										//�ͻ�����
	int i=0;
	int ret = 0;
	int len = 0;
	char h_showcardid[11] = "";						//��ʾ����
	char h_password[7] = "";							//������
	double h_temp_Card_id = 0;						//����
	char seed_key[17] = "";							//������Կ
	char card_endtime[8 + 1] = "";						//������Ч��������
	char logicdate[11]="";								//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	char sMsg[256]="";
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	int 	type=0;										//��ֵ����
	T_t_cif_customer tCustomer;
	T_t_pif_card tCard;

	T_t_aif_account  tAccount;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_pif_spefee 	tSpeFee;
	double dUniqNo = 0;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&IA,0,sizeof(IA));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSavdtl,0,sizeof(tSavdtl));

#ifdef DEBUG
	writelog(LOG_DEBUG,"rPack->scust_auth2[%s]",rPack->scust_auth2);
#endif
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_LSERIAL1,F_VSMESS,0);
	hi_cutid = rPack->lvol0;									//�ͻ�ID
	hi_cuttype = rPack->lvol3;									//�ͻ����
	des2src(h_showcardid,rPack->scust_no);					//��ʾ����
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}

	//���ͻ���Ϣ���ж��Ƿ���Է��п�
	des2src(tCard.physical_no, rPack->sbank_acc);				//������
	trim(h_showcardid);
	if(strlen(h_showcardid))
	{
		ret=IsExistShowCardNo(h_showcardid);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	
	ret=IsExistCardByPhyCardNo(tCard.physical_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	
	ret=IsExistCardByCustomId(hi_cutid);
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	//ret = DB_t_cif_customer_read_by_cut_id(hi_cutid, &tCustomer);

	//�õ��շ����

	memset(&tCustomer,0,sizeof tCustomer);
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(hi_cutid, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",hi_cutid);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
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

	tradeserial.trade_fee =D4U5(rPack->damt0,2);

	//������Ƿ񳬹������
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	dMaxCardBalance=atof(sMaxCardBalance);
	if(amtcmp(tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		writelog(LOG_ERR,"tradeserial.trade_fee[%lf]",tradeserial.trade_fee);
		*pRetCode=E_AMT_EXCEED_MAX;
		goto L_RETU;
	}
	//	׼�����ݲ��뿨��Ϣ��
	memcpy(seed_key,STATIC_SEED_KEY,16);			//��������Կ

	if(strlen(tCustomer.can_time)==8)
	{
		ret=IsInvalidDateTime(tCustomer.can_time,"YYYYMMDD");
		if(ret)
		{
			*pRetCode=E_TB_CUSTOMER_ENDTIME;
			goto L_RETU;
		}
		if(strncmp(tCustomer.can_time,sysdate,8)<=0)
		{
			*pRetCode=E_TB_CUSTOMER_ENDTIME;
			goto L_RETU;
		}
		des2src(card_endtime,tCustomer.can_time);
	}
	else if(strlen(rPack->sdate0)==0)
	{
		*pRetCode=E_TB_CUSTOMER_NO_ENDTIME;
		goto L_RETU;
	}
	else
	{
		ret=IsInvalidDateTime(rPack->sdate0,"YYYYMMDD");
		if(ret)
		{
			*pRetCode = E_INPUT_DATE;
			goto L_RETU;
		}
		if(strncmp(rPack->sdate0,sysdate,8)<=0)
		{
			*pRetCode=E_INPUT_DATE;
			goto L_RETU;
		}
		des2src(card_endtime,rPack->sdate0);
	}
	//	Ĭ������, ��ʼȡ���֤�ĺ�6λ, û�����֤����666666.
	len=strlen(tCustomer.man_id) ;
	if (len >= 6)
	{
		strncpy(h_password,&(tCustomer.man_id[len-6]),6);
		if(h_password[5]>'9'||h_password[5]<'0')
			h_password[5]='0';
	}
	else
	{
		strcpy(h_password,DEFAULT_CUST_PWD);
	}

	ret = getNewUniqNo(KEYTYPE_CARD_ID,&h_temp_Card_id);						//��ȡ��󿨺�
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tCard.card_id = D2I(h_temp_Card_id);											//����
	des2src(tCard.showid,h_showcardid);										//��ʾ����
	des2src(tCard.is_main,TYPE_YES);  											//�Ƿ�Ϊ����
	des2src(tCard.state_id,CARDSTAT_REG);										//��״̬
	tCard.type_id = CT_NORMAL;													//�����
	EncodePwd(seed_key,h_password,tCard.password,0);							//������
	tCard.cosumer_id = hi_cutid;													//�ͻ���ʶ
	tCard.account_count = ACCOUNT_COUNT_ONE;									//����Ӧ�ʻ�����
	des2src(tCard.begin_time,sysdate);											//ע��ʱ��
	des2src(tCard.end_time, card_endtime);										//����ʱ��

	tCard.phytype = PHYTYPE_NO_ONE;											//�豸�����ͺ�;Ĭ��Ϊ1
	//	���뿨��Ϣ
	ret = DB_t_pif_card_add(&tCard);
	if (ret)
	{
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_CARD_E;
		else
			*pRetCode = E_DB_CARD_I;
		goto L_RETU;
	}
	
	//	׼�����ݲ����ʻ���Ϣ��
	ret = getNewActno(tAccount.account_id);  	    									//�������ʺ�
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	des2src(tAccount.open_date,sysdate);		   								//����ʱ��
	des2src(tAccount.open_time,systime);
	tAccount.current_state = ACCOUNTSTAT_REGIST;      							//��ǰ״̬
	tAccount.act_type = ACCTYPE_PERMAIN;				        					//�ʺ����
	tAccount.customer_id = tCustomer.cut_id;				        					//�ͻ���
	des2src(tAccount.cut_name,tCustomer.cut_name);								//�ͻ�����
	tAccount.cut_type = tCustomer.cut_type;										//�ͻ����
	des2src(tAccount.stuemp_no,tCustomer.stuemp_no); 							//�ͻ�ѧ�Ż�Ա����
	tAccount.card_id = tCard.card_id;		 										//��������
	tAccount.purse_id = PURSE_NO_ONE;											//������Ǯ����
	tAccount.card_type = CT_NORMAL;											//�����
	des2src(tAccount.subno,SUBJECT_INDIVIDUALSAVING);							//������Ŀ
	des2src(tAccount.isautotra,TYPE_NO); 										//�Ƿ��Զ�ת��
	//	�����ʻ���Ϣ��
	ret = DB_t_aif_account_add(&tAccount);
	if (ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_ACCOUNT_E;
		else
			*pRetCode = E_DB_ACCOUNT_I;
		goto L_RETU;
	}
     
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqNo);  						//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	  
	// add by ����2005-09-05
	// ��¼������ʽ����Ϣ
	/////////////////////////////////////////////////////////////////////////
	ret = InsertToCutUpdList(tCard.card_id, CUTUPD_ADD,tCard.physical_no);
	
	if( ret )
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	/////////////////////////////////////////////////////////////////////////
	tradeserial.serial_no = D2I(dUniqNo);											//��ˮ��
	tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	tradeserial.serial_type =TXCODE_CARD_OPEN_CASH;
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��

	tradeserial.maindevice_id = rPack->lvol6;												//�ϴ�����վ��ʶ
	tradeserial.device_id = rPack->lvol7;													//�ɼ��豸��ʶ
	tradeserial.card_id = tCard.card_id;													//����
	des2src(tradeserial.showid,tCard.showid);												//��ʾ����
	tradeserial.purse_id = PURSE_NO_ONE;												//Ǯ����
	tradeserial.customer_id = hi_cutid;													//�ͻ���ʶ

	des2src(tradeserial.oper_code , rPack->scust_limit);			//����Ա����
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	tradeserial.trade_count=1;														//��ǰ�����״���
	type=rPack->lvol4;										//��������
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(type)
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
			*pRetCode=E_INPUT_DEPOSIT_TYPE;
			goto L_RETU;
	}
	switch(type)
	{
		case TYPE_CASH:		//�ֽ�
			break;
 		case TYPE_BILL:		//֧Ʊ
		case TYPE_FUNDBOOK:	//���ѱ�
//		case TYPE_OTHER:	//����
 			tSavdtl.amount=rPack->damt0;				//������
 			if(amtcmp(tSavdtl.amount,0)<=0)
				break;
			des2src(tSavdtl.bill_no,rPack->sphone);		//Ʊ�ݺ���
			if(strlen(tSavdtl.bill_no)<1)
			{
				*pRetCode=E_INPUT_BILLNO;
				goto L_RETU;
			}
			tSavdtl.card_no=tCard.card_id;				//����
			des2src(tSavdtl.oper_no,rPack->scust_limit);	//����Ա
			tSavdtl.seqno=tradeserial.serial_no;			//��ˮ��
			des2src(tSavdtl.tx_date,logicdate);			//��������
			des2src(tSavdtl.tx_time,systime);			//����ʱ��
			tSavdtl.cnt=1;								//Ʊ������
			tSavdtl.bill_type=type;						//Ʊ������
			tSavdtl.tx_code=tradeserial.serial_type;		//������
			ret=DB_t_tif_savdtl_add(&tSavdtl);
			if(ret)
			{
				if(DB_REPEAT==ret)
					*pRetCode = E_DB_SAVDTL_E;
				else
					*pRetCode = E_DB_SAVDTL_I;
				goto L_RETU;
			}
			break;
		default:
			*pRetCode=E_TXCODE_NOT_EXIST;
			goto L_RETU;
	}
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;
	
	//����������ģ��
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"process ret[%d]",ret);
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
	sprintf(sMsg,"����ǰ���:%.2lfԪ",tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	// ���뽻����ˮ��
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
	/*
	// ���ӷ����¿�ʱ���Ž���������
	ret = CheckNewCardHook(&tCustomer, tCard.card_id);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	*/
	//	���ؿ���\����\��ʾ����\�ͻ�����\ͼ��֤��\��Ч��������
	out_pack->lvol0 = (int)h_temp_Card_id;                      //���׿���
	out_pack->lvol1 = tCustomer.cut_type;						//�ͻ����
	out_pack->lvol5 = tCustomer.fee_type;						//�շ����
	des2src(out_pack->scust_no,h_showcardid);					//��ʾ����
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//���ź�
	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//ѧ��
	des2src(out_pack->scust_auth2,tCustomer.man_id);			//���֤��
	des2src(out_pack->sname,tCustomer.cut_name);				//�ͻ�����
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//ͼ��֤��
	des2src(out_pack->sstatus0,tCustomer.sex);					//�Ա�
	des2src(out_pack->sopen_emp,h_password);					//������
	des2src(out_pack->sdate0,card_endtime);					//��Ч��������

	out_pack->damt2=tradeserial.out_balance;					//����ֵ
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
