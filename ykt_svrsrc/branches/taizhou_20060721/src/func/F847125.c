/* --------------------------------------------
 * ��������: F847125.sqc
 * ��������: 2004-12-16
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:  ������ʱ��(�Ǽ��� )
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
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
	IA->iSerialNo=p->serial_no;				//��ˮ��
	IA->iTradeNo=p->serial_type;				//������
	strcpy(IA->sTxDate,p->operate_date);		//��������
	strcpy(IA->sTxTime,p->operate_time);		//����ʱ��
	strcpy(IA->sTxCollectDate,p->collect_date);	//�ɼ�����
	strcpy(IA->sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,p->enteract_date);	//��������
	strcpy(IA->sTxAccTime,p->enteract_time);	//����ʱ��
	strcpy(IA->sMdeOper,p->oper_code);		//¼�� ����Ա
	strcpy(IA->sChkOper,p->reserve_1);			//���˲���Ա

//	strcpy(IA->sActno[0],p->out_account_id);		//�˺�

//	IA->dAmt[0]=p->trade_fee;				//��ֵ���(����������)
//	IA->dAmt[1]=p->boardfee;					//��ֵ���(����)
//	IA->dAmt[2]=p->deposit_fee;				//Ԥ�����
//	IA->dAmt[3]=p->in_fee;					//������/�����
//	IA->dAmt[4]=p->cost_fee;					//���ɱ���

	p->in_balance=0;							//�뿨ֵ
	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;	//��������
	IA->iTxCnt=p->trade_count;				//���״���
	IA->dInCardBala=p->in_balance;			//�뿨ֵ
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

int F847125(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int	hi_cuttype = 0;										//�ͻ�����
	int i=0;
	int ret = 0;
	double dUniqno=0;
	char h_showcardid[11] = "";								//��ʾ����
	char h_password[7] = "";									//������
	double h_temp_Card_id = 0;								//����
	char seed_key[17] = "";									//������Կ
	char card_endtime[8 + 1] = "";							//������Ч��������
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char sMsg[256]="";
	double dSerial_no = 0;
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_pif_card tCard;
	T_t_aif_account  tAccount;
	T_t_tif_tradeserial  tradeserial;
	 T_t_cif_customer  tCustomer;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_DAMT3,F_DAMT4,F_DAMT5,F_LSERIAL1,F_VSMESS,0);

	memset(&IA,0,sizeof(IA));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCustomer,0,sizeof(tCustomer));

#ifdef DEBUG
	writelog(LOG_DEBUG,"rPack->damt0[%lf]",rPack->damt0);
	writelog(LOG_DEBUG,"rPack->scust_auth2[%s]",rPack->scust_auth2);
#endif

	tradeserial.trade_fee=rPack->damt0;					//������
	hi_cuttype = rPack->lvol3;									//�ͻ����
	trim(rPack->scust_no);
	des2src(h_showcardid,rPack->scust_no);					//��ʾ����
	des2src(tCard.physical_no, rPack->sbank_acc);				//������
	des2src(card_endtime,rPack->sdate0);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	ret=IsInvalidDateTime(card_endtime,"YYYYMMDD");
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	if(strlen(h_showcardid)!=10)
	{
		*pRetCode=E_INPUT_SHOWID;
		goto L_RETU;
	}
	ret=IsExistShowCardNo(h_showcardid);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=IsExistCardByPhyCardNo(tCard.physical_no);			//������
	if(ret)
	{
		writelog(LOG_ERR,"physical_no[%s]",tCard.physical_no);
		*pRetCode = ret;
		goto L_RETU;
	}
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
//�����ӿͻ�
	ret=getNewUniqNo(KEYTYPE_CUSTOMER, &dUniqno);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		goto L_RETU;
	}
	tCustomer.cut_id=(int)dUniqno;
	tCustomer.cut_type=hi_cuttype;					//�ͻ�����
	tCustomer.fee_type=tCustomer.cut_type;
	tCustomer.cut_state=CUSTSTAT_REGIST;
	des2src(tCustomer.is_havecard,TYPE_YES);
//	tCustomer.area=rPack->lvol10;						//����
/*
	ret=GetTempPersonId(tCustomer.stuemp_no);	//Ա����
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
*/
//	des2src(tCustomer.stuemp_no,h_showcardid);
	snprintf(tCustomer.cut_name,20,"��%.10s",h_showcardid);			//�ͻ� ����
	des2src(tCustomer.reg_time,sysdate);							//ע������
	ret=DB_t_cif_customer_add(&tCustomer);
	if(ret)
	{
		*pRetCode = E_DB_CUSTOMER_I;
		writelog(LOG_ERR,"DB_t_cif_customer_add ret[%d]",ret);
		goto L_RETU;
	}
	//	׼�����ݲ��뿨��Ϣ��
	memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));						//��������Կ

	//	Ĭ������, ��ʼȡ���֤�ĺ�6λ, û�����֤����666666.
	strcpy(h_password,"666666");
	ret = getNewUniqNo(KEYTYPE_CARD_ID,&h_temp_Card_id);						//��ȡ��󿨺�
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	tCard.card_id = (int)h_temp_Card_id;											//����
	des2src(tCard.showid,h_showcardid);											//��ʾ����
	des2src(tCard.is_main,TYPE_YES);  											//�Ƿ�Ϊ����
	des2src(tCard.state_id,CARDSTAT_REG);										//��״̬
	tCard.type_id = CT_TEMP_NONAME;											//�����
	EncodePwd(seed_key,h_password,tCard.password,0);							//������
	tCard.cosumer_id = tCustomer.cut_id;											//�ͻ���ʶ
	tCard.account_count = ACCOUNT_COUNT_ONE;									//����Ӧ�ʻ�����
	des2src(tCard.begin_time,logicdate);											//ע��ʱ��
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
	ret = getNewActno(tAccount.account_id);  	    //�������ʺ�
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	des2src(tAccount.open_date,logicdate);		   								//����ʱ��
	des2src(tAccount.open_time,systime);
	tAccount.current_state = ACCOUNTSTAT_REGIST;      							//��ǰ״̬
	tAccount.act_type = ACCTYPE_PERMAIN;				        					//�ʺ����
	tAccount.customer_id = tCustomer.cut_id;				        					//�ͻ���
	des2src(tAccount.cut_name,tCustomer.cut_name);								//�ͻ�����
	tAccount.cut_type = hi_cuttype;												//�ͻ����
	des2src(tAccount.stuemp_no,tCustomer.stuemp_no); 							//�ͻ�ѧ�Ż�Ա����
	tAccount.card_id =tCard.card_id; 											//��������
	tAccount.purse_id = PURSE_NO_ONE;										//������Ǯ����
	tAccount.card_type = tCard.type_id;											//�����
	des2src(tAccount.subno,SUBJECT_INDIVIDUALSAVING);						//������Ŀ
	des2src(tAccount.isautotra,TYPE_NO); 										//�Ƿ��Զ�ת��
	//	�����ʻ���Ϣ��
	ret = DB_t_aif_account_add(&tAccount);
	if (ret)
	{
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_ACCOUNT_E;
		else
			*pRetCode = E_DB_ACCOUNT_I;
		goto L_RETU;
	}
	//׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  						//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tradeserial.serial_no = (int)dSerial_no;											//��ˮ��
	tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_CARD_OPEN_FOR_TEMP;								//���״���
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
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
	tradeserial.customer_id = tCustomer.cut_id;											//�ͻ���ʶ
	des2src(tradeserial.oper_code,rPack->scust_limit);									//����Ա����
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	tradeserial.trade_count=1;														//��ǰ�����״���

	des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

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

	//	����������ģ��
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
	//	���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
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
	//	���ؿ���\����\��ʾ����\�ͻ�����\ͼ��֤��\��Ч��������
	out_pack->lvol0 = (int)h_temp_Card_id;						//���׿���
	out_pack->lvol1 = tCustomer.cut_type;						//�ͻ����
	out_pack->lvol5 = tCustomer.fee_type;						//�շ����
	des2src(out_pack->scust_no,h_showcardid);					//��ʾ����
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//���ź�
//	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//ѧ��
	des2src(out_pack->scust_auth2,tCustomer.man_id);			//���֤��
	des2src(out_pack->sname,tCustomer.cut_name);				//�ͻ�����
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//ͼ��֤��
	des2src(out_pack->sstatus0,tCustomer.sex);					//�Ա�
	des2src(out_pack->sopen_emp,h_password);					//������
	des2src(out_pack->sdate0,card_endtime);					//��Ч��������

	out_pack->damt2=tradeserial.out_balance;					//����ֵ
	out_pack->damt3=tradeserial.boardfee;						//����
	out_pack->damt4=tradeserial.cost_fee;						//�� �ɱ� ��
	out_pack->damt5=tradeserial.in_fee;							//������
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
