/* --------------------------------------------
 * ��������: F930033.sqc
 * ��������: 20050306
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ɼ�������ˮ
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

int F930033(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	
	int ret=0;
	T_t_tif_rcvdtl tRcvdtl;
	
	/*
	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		writelog(LOG_ERR,"subsys_id[%d]dyn_key[%s]",rPack->lcert_code,rPack->scust_limit2);
		*pRetCode =  ret;
		goto L_RETU;
	}
	*/
	memset(&tRcvdtl,0,sizeof(tRcvdtl));
	
	tRcvdtl.serial_no= rPack->lvol4;							//�ϴ�����ˮ��
	tRcvdtl.tx_mark=rPack->lvol12;							//999���ױ��
	tRcvdtl.sys_id  = rPack->lcert_code;						//�ϴ�����վ��ʶ(ǰ�û�ע���)
	des2src(tRcvdtl.device_id, rPack->sdate1);				//�����豸ID
	des2src(tRcvdtl.inpower_no,rPack->stx_pwd);				//�ն��豸��Ȩ��	
	tRcvdtl.comu_ver=rPack->lbank_acc_type;					//�������κ�
	tRcvdtl.run_reason = rPack->lbank_acc_type2;				//����ԭ��
	des2src(tRcvdtl.crc,rPack->sbank_code2);				//CRCУ��

	tRcvdtl.card_no= rPack->lvol5;							//���׿���
	tRcvdtl.purse_no = rPack->lvol6;						//����Ǯ����
	tRcvdtl.in_bala= rPack->lvol9;							//�뿨���
	tRcvdtl.out_bala = rPack->lvol10;						//�������
	tRcvdtl.amount = rPack->lvol8;							//�������ѽ��
	tRcvdtl.total_cnt= rPack->lvol7;							//��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
	tRcvdtl.tx_code = 930033;								//���״���
 	snprintf(tRcvdtl.tx_date,9,"20%s",rPack->spost_code);		//��������(��ʽ�����������)
	des2src(tRcvdtl.tx_time,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	tRcvdtl.fee_code = rPack->lvol11;						
	getsystimestamp(tRcvdtl.col_timestamp);
	if(tRcvdtl.tx_mark==2)
		tRcvdtl.status[0]='6';								//��;�ο�����
	else if(tRcvdtl.tx_mark==153 || tRcvdtl.tx_mark == 251)
		tRcvdtl.status[0]='1';
	else
		tRcvdtl.status[0]='5';
	ret = DB_t_tif_rcvdtl_add(&tRcvdtl);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_rcvdtl_add ret[%d]",ret);
		if(DB_REPEAT==ret)
			return 0;	
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	//�ع�����
	return -1;		
}
