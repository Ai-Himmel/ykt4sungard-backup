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
	double unique=0;
	memset(&tradeserial,0,sizeof(T_t_tif_tradeserial));			//�����ˮ�ṹ��

	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);			//��ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RETU;
	}

	tradeserial.card_id=atoi(rPack->sserial0);
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
	des2src(tradeserial.b_act_id,rPack->scust_auth);		//���п��ţ�����������������ݿ��ֶ�
	tradeserial.sys_id=rPack->lvol2;						//�ⲿϵͳ��ʶ���˴�Ϊ���ֶ������--- ũҵ����Ϊ1
	tradeserial.condition_id=SELF_TRANS;				//�Զ�/����ת�ʱ�ʶ
	des2src(tradeserial.oper_code,OPER_SYSTEM_KEY);	//����Ա����
	tradeserial.other_seri_no=rPack->lvol0;				//ԭʼ��ˮ��
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


