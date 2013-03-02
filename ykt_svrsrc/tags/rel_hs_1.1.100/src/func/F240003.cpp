/* --------------------------------------------
 * ��������: F240003.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ���������׵Ǽ�
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


int F240003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_tif_tradeserial  tradeserial;
	T_t_pif_card	card;
	double unique=0;
	memset(&tradeserial,0,sizeof(T_t_tif_tradeserial));			//�����ˮ�ṹ��
	memset(&card,0,sizeof card);

	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);			//��ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RETU;
	}
	ret=DB_t_pif_card_read_by_card_id(atoi(rPack->sserial0),&card);
	if(ret)
	{
		*pRetCode=E_TRANS_SCHACC_NOEXIT;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}


	tradeserial.card_id=atoi(rPack->sserial0);
	tradeserial.customer_id=card.cosumer_id;
	tradeserial.purse_id=0;
	tradeserial.serial_no=D2I(unique);
	tradeserial.serial_type=TXCODE_BANK_DETRANS;			//���״���
	tradeserial.serial_state=SERISTAT_NONEEDDEBT;			//��ˮ״̬
	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		des2src(tradeserial.operate_date,getsysdate(NULL));		//��������
		des2src(tradeserial.operate_time,getsystime(NULL));		//����ʱ��
	}
	des2src(tradeserial.collect_date,tradeserial.operate_date);//�ɼ�����
	des2src(tradeserial.collect_time,tradeserial.operate_time);//�ɼ�ʱ��
	tradeserial.maindevice_id=GetTransferSystemId();		//��ϵͳ����
	tradeserial.device_id=atoi(rPack->sorder2);			//�ն�ID
	tradeserial.trade_fee=rPack->lvol5/100.0;		//ת�ʽ��
	tradeserial.in_balance=rPack->lvol6/100.0;		//�뿨���
	tradeserial.out_balance=tradeserial.in_balance;		//�������	
	des2src(tradeserial.b_act_id,rPack->scust_auth);		//���п���
	tradeserial.sys_id=rPack->lvol2;						//�ⲿϵͳ��ʶ���˴�Ϊ�����ļ��ж�ȡ����
	tradeserial.condition_id=SELF_TRANS;				//�Զ�/����ת�ʱ�ʶ
	des2src(tradeserial.oper_code,OPER_SYSTEM_KEY);	//����Ա����
	tradeserial.reviseserial_no=rPack->lvol0;				//ԭʼ��ˮ��
	tradeserial.trade_count=rPack->lvol1+1;				//���״���
	tradeserial.tmark=0;		

	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RETU;
	}

	return 0;

L_RETU:
	return ret;
}


