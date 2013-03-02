/* --------------------------------------------
 * ��������: F847127.c
 * ��������: 2005-11-18
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �ֹ���-�ֹ���
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
	strcpy(IA->sMdeOper,p->oper_code);			//����Ա(�������ʵĲ���Ա)
	strcpy(IA->sChkOper,p->reserve_1);			//���˲���Ա

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//�޿�����
	IA->iTxCnt=0;								//���״���
	IA->dInCardBala=0;							//�뿨ֵ
	IA->dOutCardBala=0;							//����ֵ

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
	return 0;
}

int F847127(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	InAcc	IA;
	char  ia_buf[1024]="";
	double dUniqno = 0;
	char sMsg[256]="";
	T_t_tif_tradeserial tradeserial;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	IA.pVoidPointer=ia_buf;
	ResetNormalCPack(&aPack,0,1);

	if(amtcmp(rPack->damt0,0)==0)
	{
		*pRetCode=E_INPUT_AMT_NULL;
		goto L_RETU;
	}
	trim(rPack->sbank_acc);
	trim(rPack->sbank_acc2);
	if(strcmp(rPack->sbank_acc,rPack->sbank_acc2)==0)
	{
		*pRetCode=E_INPUT_2ACTNO_EQ;
		goto L_RETU;
	}
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	if(strlen(rPack->scust_limit)==0)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit2)==0)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
	{
		writelog(LOG_ERR,"oper1[%s]oper2[%s]",rPack->scust_limit,rPack->scust_limit2);
		*pRetCode=E_INPUT_2OPER_EQ;
		goto L_RETU;
	}
	ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
	if(ret)
	{
		if(E_OPER_NOT_EXIST==ret)
			*pRetCode=E_INPUT_OPER_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			*pRetCode=E_INPUT_OPER_PWD;
		else
			*pRetCode=ret;
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	tradeserial.trade_fee = rPack->damt0;						//�������
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  		//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = (int)dUniqno;							//��ˮ��
	tradeserial.other_seri_no = 0;								//�ϴ�����ˮ��
	tradeserial.serial_type  = TXCODE_CARD_DBCR;				//������
	tradeserial.serial_state = SERISTAT_DEBT;						//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);					//��������
	des2src(tradeserial.operate_time,systime);					//����ʱ��
	des2src(tradeserial.collect_date,sysdate);						//�ɼ�����
	des2src(tradeserial.collect_time,systime);						//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);					//��������
	des2src(tradeserial.enteract_time,systime);					//����ʱ��
	tradeserial.maindevice_id = rPack->lvol6;						//�ϴ�����վ��ʶ
	tradeserial.in_balance=rPack->damt0;						//�뿨ֵ
	tradeserial.trade_count=0;									//���״���
	des2src(tradeserial.oper_code,rPack->scust_limit2);			//���ʲ���Ա����
	des2src(tradeserial.reserve_1,rPack->scust_limit);			//����Ա����
	tradeserial.sys_id = 0;										//�ⲿϵͳ��ʶ

	IA.iCardNo=0;
	IA.iFeeType=1;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	des2src(IA.sArrInActno[0],rPack->sbank_acc);				//�跽�ʺ�
	des2src(IA.sArrInActno[1],rPack->sbank_acc2);				//�����ʺ�
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
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	strcat(out_pack->vsmess,IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_DAMT4,F_VSMESS,0);
	out_pack->lserial1=tradeserial.serial_no;			//��ˮ��
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

