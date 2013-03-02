/* --------------------------------------------
 * ��������: F240001.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��ת����ʽ����
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


	IA->iUseCardFlag=IS_YES;						//������
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
	switch(IA->iTradeNo)
	{
	case TXCODE_BANK_YCT:
	case TXCODE_BANK_SCHOOL:
		p->out_balance=IA->dOutCardBala;			//����ֵ
		break;
	case TXCODE_BANK_ELEC:
		memset(&tAccount,0,sizeof tAccount);
		ret = DB_t_aif_account_read_by_account_id(IA->sArrInActno[1],&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"query account [%s] error",IA->sArrInActno[1]);
			return E_DB_ACCOUNT_R;
		}
		p->out_balance = tAccount.cur_freebala;
		break;
	}
	return 0;
}

int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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

	T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	T_t_aif_account	tAccount;
	InAcc	IA;

	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_SDATE0,0);



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

	//ģʽ�޸�Ϊ���������ʲ�����ˮ�ţ���¼��ˮ�ṹ����ʽ����ֻ�޸ĸ�
	//��ˮ�ĳ���ֵ�Լ���ˮ״̬

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(rPack->lvol7, &tradeserial);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_R;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d],serial_no=[%d]",
				 ret,rPack->lvol7);
		goto L_RETU;
	}

	if(tradeserial.serial_state != SERISTAT_NODEBT)
	{
		*pRetCode = E_TRANS_UNKNOW_ERROR;
		sprintf(szMsg,"������ˮ״̬����ȷ,serialno[%d]",rPack->lvol7);
		goto L_RETU;
	}
	//��д���˽ṹ,�����Ž�
	memset(&IA,0,sizeof(IA));
	des2src(IA.sArrInActno[0],tradeserial.out_account_id);			//�����ʻ�,�ֿ����˻�
	des2src(IA.sArrInActno[1],tradeserial.in_account_id);			//�跽�ʺţ���ǰ�û��ϴ�
	IA.iCardNo=tradeserial.card_id;
	IA.iFeeType=tradeserial.comu_ver; // �������˽���������ֶα��� Ȩ�����
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

	//���������ˮ����
	tradeserial.serial_state=SERISTAT_DEBT;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_update_lock_by_cur error,error code=[%d]",ret);
		goto L_RETU;
	}


	sprintf(sMsg,"��ֵǰ�����:%.2lf ת�ʺ����:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);

	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=tradeserial.boardfee;
	out_pack->lvol1=tradeserial.serial_no;
	out_pack->lvol2=D2I(tradeserial.out_balance * 100);
	des2src(out_pack->sdate0,logicdate);

	PutRow(handle,out_pack,pRetCode,szMsg);

	return 0;
	
L_RETU:
	return -1;
}

