/* --------------------------------------------
 * ��������: F930031.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:   �ɼ�������ʧ\�����ˮ
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubdef.h"
#include "errdef.h"
#include "busqc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "pubfunc.h"

int F930032(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;						//������
	int hi_sign = 0;					//��ʧ��ұ�־
	double h_temp_Serial_no = 0;		//������ˮ��
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	int dev_id=0;
	T_t_tif_tradeserial  tradeserial;

	memset(&tradeserial,0,sizeof(tradeserial));
	hi_sign = in_pack->lvol6;												//��ʧ��ұ�־

	ret=chk_dyn_key(in_pack->lcert_code,in_pack->scust_limit2);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);												//ҵ������
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	switch (hi_sign)
	{
		case 0:
			tradeserial.serial_type = TXCODE_CARD_LOSS;					//��ʧ
			break;
		case 1:
			tradeserial.serial_type = TXCODE_CARD_COMEBACK_LOSS;			//���
			break;
		case 2:
			tradeserial.serial_type = TXCODE_MODIFICATIONPW;				//�޸�����
			break;
		default:
			*pRetCode = -1;
			writelog(LOG_ERR,"��ʧ����޸������־����ERRCODE[%d] ",*pRetCode);
			goto L_RETU;
			break;
	}
	/*	��ȡ�豸ID	*/
	ret = GetDevIdByDevPhyId(&dev_id,in_pack->sdate1);	
	if (ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"GetDevIdByDevPhyId err[%d] ",ret);
		goto L_RETU;
	}	
	
	tradeserial.serial_state = SERISTAT_NODEBT;								//��ˮ״̬

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&h_temp_Serial_no);  			
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"��ȡ�����ˮ�Ŵ���: ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = D2I(h_temp_Serial_no);													//��ˮ��

 	snprintf(tradeserial.operate_date,9,"20%s",in_pack->spost_code);		//��������(��ʽ�����������)
	des2src(tradeserial.operate_time,in_pack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	tradeserial.other_seri_no = in_pack->lvol4;													//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_DEBT;													//��ˮ״̬
	tradeserial.maindeviceid = in_pack->lcert_code;												//�ϴ�����վ��ʶ
	tradeserial.deviceid = dev_id;														//�ɼ��豸��ʶ
	tradeserial.cardno = in_pack->lvol5;														//����
	Strncpy_t(tradeserial.showid,in_pack->sstation0,sizeof(tradeserial.showid));						//��ʾ����
	Strncpy_t(tradeserial.oldpwd,in_pack->sstock_code,sizeof(tradeserial.oldpwd));					//ԭʼ����
	Strncpy_t(tradeserial.newpwd,in_pack->sstock_code2,sizeof(tradeserial.newpwd));				//��������
	des2src(tradeserial.opercode,"system");
	
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
	return 0;
L_RETU:
	return -1;
}                                                 
