/** 
 * ģ���� - Ȧ��ת�˽��׳���
 * �ļ��� F240015.cpp
 * �ļ�ʵ�ֹ���
 * ���� 
 * �汾
 * ���� 2008-08-29
 * ��ע
 * $Id$
 */

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

int F240003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret = 0;

	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	IA->iMainDevId=p->maindevice_id;			//����վ��ʶ
	IA->iDevId=p->device_id;					//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	IA->iTradeNo=p->serial_type;				//������
	strcpy(IA->sTxDate,p->operate_date);		//��������
	strcpy(IA->sTxTime,p->operate_time);		//����ʱ��
	strcpy(IA->sTxCollectDate,p->collect_date);	//�ɼ�����
	strcpy(IA->sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,p->enteract_date);	//��������
	strcpy(IA->sTxAccTime,p->enteract_time);	//����ʱ��
	strcpy(IA->sMdeOper,p->oper_code);		//¼�� ����Ա
	strcpy(IA->sChkOper,p->reserve_1);		//���� ����Ա

	p->in_balance=0;						//�뿨ֵ
	IA->dInCardBala=0;					//�뿨ֵ
	IA->dOutCardBala=-1;					//����ֵ
	IA->iTxCnt=1;						//���״���
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


static int do_enteract(T_t_tif_tradeserial *reverse_serial,T_t_tif_tradeserial *tradeserial,InAcc *IA)
{
	int ret;
	double new_serial;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&new_serial);
	if(ret)
	{
		writelog(LOG_ERR,"���ɽ�����ˮ�Ŵ���");

		return ret;
	}
	tradeserial->serial_no = D2I(new_serial);
	tradeserial->serial_state = SERISTAT_DEBT;
	tradeserial->in_balance = reverse_serial->out_balance;
	tradeserial->out_balance = reverse_serial->in_balance;
	tradeserial->trade_fee = -reverse_serial->trade_fee;
	getsysdate(tradeserial->operate_date);
	getsystime(tradeserial->operate_time);
	des2src(tradeserial->enteract_time,tradeserial->operate_time);


	// �����˺�
	des2src(IA->sArrInActno[1],tradeserial->in_account_id);
	// �跽�˺�
	des2src(IA->sArrInActno[0],tradeserial->out_account_id);
	// ���׽��
	IA->dArrInAmt[0] = tradeserial->trade_fee;
	IA->iFeeType = tradeserial->comu_ver;
	// ������־
	IA->iTxFlag = ACC_TYPE_RUSH;
	ret = process(IA,tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process account ret[%d]",ret);
		return ret;
	}
	ret = DB_t_tif_tradeserial_add(tradeserial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}

	// ��¼ˮ��ˮ��
	reverse_serial->reviseserial_no = tradeserial->serial_no;
	
	return 0;
}
// 
static int do_reverse(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	// ���ں�̨������ˮ,Ȼ������ˮΪ����״̬, �� bankguard ���г���
	int ret;
	InAcc IA;
	char logic_date[9] = "";
	ST_PACK req_pack;
	T_t_tif_tradeserial reverse_serial;
	T_t_tif_tradeserial tradeserial;
	memset(&reverse_serial,0,sizeof reverse_serial);
	memset(&tradeserial,0,sizeof tradeserial);
	memset(&IA,0,sizeof IA);

	int serial_no;
	char oper_code[11] = "";
	serial_no = in_pack->lvol0;
	des2src(oper_code,in_pack->scust_limit);
	GetLogicDate(logic_date);
	
	if(strcmp(logic_date,in_pack->sdate0) != 0)
	{
		writelog(LOG_ERR,"reverse logic date error,system[%s],input[%s]",logic_date,in_pack->sdate0);
		return E_INPUT_DATE;
	}
	

	ret = DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(serial_no,&reverse_serial);
	if(ret)
	{
		writelog(LOG_ERR,"read serial error,serialno[%d]",serial_no);
		// �޶�Ӧ��ˮ,�ͷ��س����ɹ�
		if(DB_NOTFOUND == ret)
			return 0;
		return E_DB_TRADESERIAL_R;
	}
	if(reverse_serial.serial_state == SERISTAT_DEBT)
	{
		IA.iUseCardFlag = in_pack->lvol1; // �Ƿ񿨽��� 
		memcpy(&tradeserial,&reverse_serial,sizeof tradeserial);
		ret = do_enteract(&reverse_serial,&tradeserial,&IA);
		if(!ret)
		{
			// ��ˮ״̬��־�� �ѳ���
			reverse_serial.serial_state = SERISTAT_RUSH;
			ret = DB_t_tif_tradeserial_update_lock_by_cur(&reverse_serial);
			if(ret)
			{
				writelog(LOG_ERR,"���±�������ˮʧ��,ret[%d]",ret);
				ret = E_DB_TRADESERIAL_U;
			}
			else
			{
				// ����һ��Ȧ�������ˮ
				memset(&req_pack,0,sizeof req_pack);
				sprintf(req_pack.sserial0,"%d",reverse_serial.card_id);
				req_pack.lvol5 = D2I(reverse_serial.trade_fee * 100.0);
				req_pack.lvol6 = D2I(reverse_serial.in_balance * 100.0);
				des2src(req_pack.scust_auth,reverse_serial.b_act_id);
				req_pack.lvol2 = reverse_serial.sys_id;
				req_pack.lvol1 = reverse_serial.trade_count;
				req_pack.lvol3 = reverse_serial.purse_id;
				req_pack.lvol0 = reverse_serial.serial_no; // ����������ˮ��
				sprintf(req_pack.sorder2,"%d",reverse_serial.device_id);
				ret = F240003(handle,iRequest,&req_pack,pRetCode,szMsg);
				if(ret)
				{
					writelog(LOG_ERR,"�Ǽ�Ȧ�������ˮʧ��,ret[%d]",*pRetCode);
					ret = *pRetCode;
				}
			}
		}
	}
	else
	{
		writelog(LOG_ERR,"������ˮ�ѱ�����,�����ٴγ���,serial[%d]logicdate[%s]",
				 reverse_serial.serial_no,reverse_serial.enteract_date);
		ret = 0;
	}
	// �ر��α�
	DB_t_tif_tradeserial_free_lock_cur();
	return ret;
}


int F240015(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	ret = do_reverse(handle,iRequest,rPack,pRetCode,szMsg);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	writelog(LOG_ERR,"�����ɹ�,logic_date[%s],serial_no[%d]",rPack->sdate0,rPack->lvol0);
	return 0;
}

