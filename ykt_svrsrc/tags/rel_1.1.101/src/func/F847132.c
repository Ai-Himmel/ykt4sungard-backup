/* --------------------------------------------
 * ��������: F847132.c
 * ��������: 2005-12-7
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �·�����
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/

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

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//�޿�����

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	return 0;
}


int F847132(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=0;
	int iTotalCnt=0;
	double dTotalAmt=0.0;
	double dSerialNo = 0;
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	char sMsg[256]="";
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_tif_subsidy  	tSubsidy;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&tSubsidy,0,sizeof(tSubsidy));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);					//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit)<1)
	{
		*pRetCode=E_INPUT_BATCH_NO;
		goto L_RETU;
	}
	if(strlen(rPack->scust_no)<1)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	if(amtcmp(rPack->damt0,0)<=0)
	{
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	des2src(tSubsidy.summary,rPack->semail);		//����ժҪ
	if(strlen(rPack->semail)<1)
	{
		*pRetCode=E_INPUT_SUMMARY;
		goto L_RETU;
	}
	des2src(tSubsidy.batch_no,rPack->scust_limit);
	tSubsidy.bill_type=rPack->lvol2;					//Ʊ������
	des2src(tSubsidy.bill_no,rPack->scust_auth2);	//Ʊ�ݺ���
	tSubsidy.amount=rPack->damt0;				//�������
	des2src(tSubsidy.subsidytype,rPack->smain_flag);//������־(0��ֵ1��ֵ)
	des2src(tSubsidy.subsidytype,"1");			//������־(0��ֵ1��ֵ)
	des2src(tSubsidy.broker_id,rPack->sname);		//���������֤��
	des2src(tSubsidy.broker_name,rPack->semail2);	//����������

	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(tSubsidy.bill_type)
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
	ret=stat_subsidy_amount_by_batch_no(tSubsidy.batch_no, &iTotalCnt,&dTotalAmt);
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	if(iTotalCnt!=rPack->lvol3)
	{
		strcpy(szMsg,"���������뵼������ݲ���");
		*pRetCode=E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	if(amtcmp(dTotalAmt,rPack->damt0)!=0)
	{
		strcpy(szMsg,"�����ܽ���뵼��Ĳ������ݲ���");
		*pRetCode=E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	ret=update_subsidy_info_by_batch_no(&tSubsidy);
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = (int)dSerialNo;											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_SET_SUBSIDY;
	tradeserial.serial_state = SERISTAT_DEBT;				//��ˮ״̬
	des2src(tradeserial.operate_date,logicdate);			//��������
	des2src(tradeserial.operate_time,systime);			//����ʱ��
	des2src(tradeserial.collect_date,sysdate);				//�ɼ�����
	des2src(tradeserial.collect_time,systime);				//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);			//��������
	des2src(tradeserial.enteract_time,systime);			//����ʱ��
	tradeserial.maindevice_id = rPack->lvol6;				//�ϴ�����վ��ʶ
	tradeserial.device_id = rPack->lvol7;					//�ɼ��豸��ʶ
	des2src(tradeserial.oper_code , rPack->scust_no);		//����Ա����
	tradeserial.sys_id = 0;								//�ⲿϵͳ��ʶ
	switch(tSubsidy.bill_type)
	{
		case TYPE_CASH:		//�ֽ�
			break;
 		case TYPE_BILL:		//֧Ʊ
		case TYPE_FUNDBOOK:	//���ѱ�
 			tSavdtl.amount=rPack->damt0;				//������
 			if(amtcmp(tSavdtl.amount,0)<=0)
				break;
			des2src(tSavdtl.bill_no,tSubsidy.bill_no);		//Ʊ�ݺ���
			if(strlen(tSavdtl.bill_no)<1)
			{
				*pRetCode=E_INPUT_BILLNO;
				goto L_RETU;
			}
			tSavdtl.card_no=0;							//����
			des2src(tSavdtl.oper_no,rPack->scust_limit);	//����Ա
			tSavdtl.seqno=tradeserial.serial_no;			//��ˮ��
			des2src(tSavdtl.tx_date,sysdate);			//��������
			des2src(tSavdtl.tx_time,systime);			//����ʱ��
			tSavdtl.cnt=1;								//Ʊ������
			tSavdtl.bill_type=tSubsidy.bill_type;			//Ʊ������
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
			*pRetCode=E_INPUT_DEPOSIT_TYPE;
			goto L_RETU;
	}
	IA.iFeeType=1;				//Ĭ��ֵ
	IA.dArrInAmt[0]=tradeserial.trade_fee;
//	if(strncmp(tSubsidy.subsidytype,"1",1)==0)
//		IA.dArrInAmt[0]=tradeserial.trade_fee;
//	else if(strncmp(tSubsidy.subsidytype,"2",1)==0)
//	{
//		IA.dArrInAmt[0]=-tradeserial.trade_fee;
//		IA.iTxFlag=1;
//	}
//	else
//	{
//		*pRetCode=E_INPUT_DATA_INVAILD;
//		sprintf(szMsg,"����Ĳ�������%s������",strncmp(tSubsidy.subsidytype);
//		goto L_RETU;
//	}
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;

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
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
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
