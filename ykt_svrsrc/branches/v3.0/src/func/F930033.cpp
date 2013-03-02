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
#include "acctrans.h"
#include "busqc.h"

int F930033(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	
	int ret=0;
	T_t_posdtl posdtl;
	
	/*
	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		writelog(LOG_ERR,"subsys_id[%d]dyn_key[%s]",rPack->lcert_code,rPack->scust_limit2);
		*pRetCode =  ret;
		goto L_RETU;
	}
	*/
	memset(&posdtl,0,sizeof(posdtl));
	
	posdtl.devseqno= rPack->lvol4;							//�ϴ�����ˮ��
	posdtl.transmark=rPack->lvol12;							//999���ױ��
	posdtl.sysid  = rPack->lcert_code;						//�ϴ�����վ��ʶ(ǰ�û�ע���)
	des2src(posdtl.devphyid, rPack->sdate1);				//�����豸ID
//	des2src(posdtl.inpower_no,rPack->stx_pwd);				//�ն��豸��Ȩ��	
//	posdtl.comu_ver=rPack->lbank_acc_type;					//ͨ�Ű汾��
//	posdtl.run_reason = rPack->lbank_acc_type2;				//����ԭ��
//	des2src(posdtl.crc,rPack->sbank_code2);				//CRCУ��

	posdtl.cardno= rPack->lvol5;							//���׿���
	posdtl.purseno = rPack->lvol6;						//����Ǯ����
	posdtl.cardbefbal= rPack->lvol9;							//�뿨���
	posdtl.cardaftbal = rPack->lvol10;						//�������
	posdtl.amount = rPack->lvol8;							//�������ѽ��
	posdtl.cardcnt= rPack->lvol7;							//��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
	posdtl.transcode = 930033;								//���״���
 	snprintf(posdtl.transdate,9,"20%s",rPack->spost_code);		//��������(��ʽ�����������)
	des2src(posdtl.transtime,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	posdtl.subsidyno = rPack->lvol11;						//�������κ�
	getsysdate(posdtl.coldate);
	getsystime(posdtl.coltime);
	posdtl.status[0]='1';
	ret = DB_t_posdtl_add(&posdtl);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_posdtl_add ret[%d]",ret);
		if(DB_REPEAT==ret)
			return 0;	
		else
			*pRetCode = E_DB_POSDTL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;		
}
