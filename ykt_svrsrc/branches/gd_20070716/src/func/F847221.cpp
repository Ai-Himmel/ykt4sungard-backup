/* --------------------------------------------
 * ��������: F847221.sqc
 * ��������: 2006-9-25
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ϴ����������
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
#include "dbfunc_foo.h"

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


int F847221(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	double 	tx_money = 0.0;
	char  ia_buf[1024]="";
	char sMsg[256]="";
	double	dUniNo = 0;
	T_t_tif_tradeserial serial;
	T_t_tif_tradeserial old_serial;
	T_t_group_cash_report group_cash;
	T_t_groups groups;
	InAcc IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int i;

	ResetNormalCPack(&aPack,0,1);

	if(strlen(rPack->scard0) <= 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	ret = CheckOperatorPwd(rPack->scard0,rPack->semp_pwd);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	if(rPack->lvol1 <= 0)
	{
		*pRetCode = E_FAN_SERIAL_NOT_EXISTS;
		goto L_RETU;
	}

	// ���±�������ˮ��״̬
	memset(&old_serial,0,sizeof old_serial);
	ret = DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(rPack->lvol1,&old_serial);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_FAN_SERIAL_NOT_EXISTS;
		else
			*pRetCode = E_DB_TRADESERIAL_R;
		goto L_RETU;
	}

	if(SERISTAT_RUSH == old_serial.serial_state)
	{
		writelog(LOG_ERR,"��ˮ�ѱ�����,��ˮ��[%d]",old_serial.serial_no);
		*pRetCode = E_FAN_ALREADY_RUSHED;
		DB_t_tif_tradeserial_free_lock_cur();
		goto L_RETU;
	}

	old_serial.serial_state = SERISTAT_RUSH;
	ret = DB_t_tif_tradeserial_update_lock_by_cur(&old_serial);
	if(ret)
	{
		writelog(LOG_ERR,"������ˮ[%d]״̬ʧ��",old_serial.serial_no);
		*pRetCode = E_DB_TRADESERIAL_U;
		goto L_RETU;
	}
	DB_t_tif_tradeserial_free_lock_cur();

	tx_money = old_serial.trade_fee;
	// �����µĳ�����ˮ
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniNo);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	// ��ѯ��ɽ�����
	memset(&group_cash,0,sizeof group_cash);
	ret = DB_t_group_cash_report_read_lock_by_c1_and_group_id(old_serial.showid,&group_cash);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_FAN_ACC_NOT_EXISTS;
		else
			*pRetCode = E_DB_GRP_CASH_RPT_R;
		goto L_RETU;
	}
	
	/*
	if(amtcmp(tx_money,group_cash.cur_money)>0)
	{
		*pRetCode = E_FAN_ACC_INSUFFICIENT;
		DB_t_group_cash_report_free_lock_by_c1();
		goto L_RETU;
	}
	*/

	// ������ˮ
	memset(&serial,0,sizeof serial);
	serial.serial_no = (int)dUniNo;
	serial.serial_state = SERISTAT_DEBT;
	serial.serial_type = TXCODE_FAN_RUSH_PAY;
	getsysdate(serial.operate_date);
	getsystime(serial.operate_time);
	des2src(serial.collect_date,serial.operate_date);
	des2src(serial.collect_time,serial.operate_time);
	GetLogicDate(serial.enteract_date);
	des2src(serial.enteract_time,serial.operate_time);

	des2src(serial.oper_code,rPack->scard0);
	des2src(serial.reserve_1,rPack->scert_addr);
	serial.in_balance = tx_money;
	serial.trade_fee = tx_money * -1;
	// �̻���
	des2src(serial.showid,old_serial.showid);

	// ����
	memset(&IA,0,sizeof IA);
	IA.dArrInAmt[0] = serial.trade_fee;
	IA.iCardNo = 0;
	//�շ����Ϊ 1
	IA.iFeeType = 1;
	IA.iTxFlag = ACC_TYPE_RUSH;
	IA.pVoidPointer = ia_buf;
	ret = process(&IA,&serial);
	if(ret)
	{
		writelog(LOG_ERR,"account process error [%d]",ret);
		*pRetCode  = ret;
		DB_t_group_cash_report_free_lock_by_c1();
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,F_LVOL1,F_DAMT1,F_DAMT2,F_SBANK_ACC,0);
	
	sprintf(out_pack->vsmess,"��ˮ��:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	
	strcat(out_pack->vsmess,(char*)IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);

	des2src(group_cash.last_check_date,serial.operate_date);
	des2src(group_cash.last_check_time,serial.operate_time);
	group_cash.cur_money = group_cash.cur_money + tx_money;
	out_pack->lvol1 = serial.serial_no;
	out_pack->damt1 = serial.trade_fee;
	out_pack->damt2 = group_cash.cur_money;

	//������δ�����
	ret = DB_t_group_cash_report_update_lock_by_c1(&group_cash);
	if(ret)
	{
		*pRetCode = E_DB_GRP_CASH_RPT_U;
		goto L_RETU;
	}
	// add
	DB_t_group_cash_report_free_lock_by_c1();
	ret = DB_t_groups_read_by_group_id(group_cash.group_id,&groups);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_GROUP_N;
		else
			*pRetCode = E_DB_GROUP_R;
		goto L_RETU;
	}
	des2src(out_pack->sbank_acc,groups.group_acc);
	//������ˮ
	ret = DB_t_tif_tradeserial_add(&serial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	
L_RETU:
	return -1;
}
