/* --------------------------------------------
 * ��������: F847222.sqc
 * ��������: 2006-9-26
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ϴ������̻����ѽ���
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

typedef struct  _t_Trade_Param
{
	InAcc* pIA;			//����ģ��
	int shop_id;					//�����̻���	
	double trade_fee;				//���׽��
	int serial_no;				//��ˮ��
	double free_balance;			//�̻����
	double remain_balance;		//����ʣ����
	int out_shop_id;				//����Ҷ�ӽ���̻���
	int index;					//��������ˮ��
	char tx_date[9];
	char tx_time[7];
	char oper_code[11];
} trade_param_t;

static int process(InAcc *IA,trade_param_t *p)
{
	int ret=0;

	IA->iSerialNo = p->serial_no;				//��ˮ��
	IA->iSubIndex = p->index;
	IA->iTradeNo = TXCODE_FAN_BALANCE;		//������
	IA->dArrInAmt[0] = p->trade_fee;
	IA->iFeeType = 1;
	IA->iUseCardFlag = 0;				
	
	des2src(IA->sTxDate,p->tx_date);			//��������
	des2src(IA->sTxTime,p->tx_time);			//����ʱ��
	des2src(IA->sTxCollectDate,p->tx_date);		//�ɼ�����
	des2src(IA->sTxCollectTime,p->tx_time);		//�ɼ�ʱ��
	des2src(IA->sTxAccDate,p->tx_date);		//��������
	des2src(IA->sTxAccTime,p->tx_time);		//����ʱ��
	des2src(IA->sMdeOper,p->oper_code);			//����Ա(�������ʵĲ���Ա)

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
	//p->remain_balance -= IA->dOutCardBala;			//����ֵ
	if(amtcmp(IA->dOutCardBala,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	p->index = IA->iSubIndex;
	p->remain_balance -= p->trade_fee;
	return 0;
}

static int do_process_trade(trade_param_t * param)
{
	int ret;
	T_t_cif_shop shop;
	T_t_aif_account account;
	void * pTmp;
	InAcc * IA; 
	
	memset(&shop,0,sizeof shop);
	ret = DB_t_cif_shop_read_by_shop_id(param->out_shop_id,&shop);
	//writelog(LOG_DEBUG,"trade shop id[%d]",param->out_shop_id);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SHOP_N;
		else
			return E_DB_SHOP_R;
	}

	memset(&account,0,sizeof account);
	ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		shop.cut_id,ACCTYPE_SHOPMAIN,&account);
	if(ret)
	{
		writelog(LOG_ERR,"shop id[%d] custid[%d]",shop.shop_id,shop.cut_id);
		if(DB_NOTFOUND == ret)
			return E_FAN_ACC_NOT_EXISTS;
		return E_DB_ACCOUNT_R;
	}
	//writelog(LOG_DEBUG,"��Ҷ���̻�[%d]���н��[%.2lf]���[%.2lf]",
	//	param->out_shop_id,account.last_bala,param->remain_balance);
	if(amtcmp(account.last_bala,0) <= 0)
	{
		// �̻���������
		return 0;
	}
	// ����Ƿ��Ѿ�������
	if(amtcmp(param->remain_balance,0) == 0)
	{
		//ֻ�����̻����
		param->free_balance += account.last_bala;
		return 0;
	}
	// ���㽻�׽��
	if(amtcmp(param->remain_balance,account.last_bala) >= 0)
	{
		param->trade_fee = account.last_bala;
	}
	else
	{
		param->trade_fee = param->remain_balance;
	}
	// ����
	IA = param->pIA;
	//pTmp =  IA->pVoidPointer;
	memset(IA,0,sizeof(InAcc));
	des2src(IA->sArrInActno[1],account.account_id);
	IA->pVoidPointer = pTmp;
	ret = process(IA,param);
	if(ret)
	{
		writelog(LOG_ERR,"process account failed,ret [%d]shopid[%d]subindex[%d]",
			ret,param->out_shop_id,param->index);
		return ret;
	}
	// �����˻����
	// ����֮���˻�����Ѿ�������,��Ҫ���¶�ȡ
	memset(&account,0,sizeof account);
	ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		shop.cut_id,ACCTYPE_SHOPMAIN,&account);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_FAN_ACC_NOT_EXISTS;
		return E_DB_ACCOUNT_R;
	}
	account.last_bala -= param->trade_fee;
	account.last_freebala -= param->trade_fee;
	if(amtcmp(account.last_bala,0)< 0)
	{
		account.last_bala = 0.0;
		account.last_freebala = 0.0;
	}
	else
	{
		param->free_balance += account.last_bala;
	}
	ret = DB_t_aif_account_update_by_account_id(account.account_id,&account);
	if(ret)
	{
		writelog(LOG_ERR,"�����̻��˻����ʧ��ret[%d]",ret);
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}
	writelog(LOG_DEBUG,"�̻�[%d]�����[%.2lf]���[%.2lf]"
		,shop.shop_id,param->trade_fee,account.last_bala);
	return ret;
}

static int do_parse_shop(trade_param_t * param)
{
	int ret;
	int rows;
	T_v_cif_shop_tree shop_node;
	//writelog(LOG_DEBUG,"���̻�[%d]�������ѽ��[%.2lfԪ]"
	//	,param->shop_id,param->remain_balance);
	ret = DB_v_cif_shop_tree_open_select_by_c1_and_shop_id(param->shop_id);
	if(ret)
	{
		writelog(LOG_ERR,"��ѯ�̻���Ϣʧ��[%d]",ret);
		if(DB_NOTFOUND == 0)
			return E_SHOP_HAVE_SUB_NODE;
		else
			return E_DB_SHOP_R;
	}
	rows = 0;
	while(1)
	{
		memset(&shop_node,0,sizeof shop_node);
		ret = DB_v_cif_shop_tree_fetch_select_by_c1(&shop_node);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows > 0)
					break;
				else
					return E_FAN_SHOP_HAS_NO_LEAF;
			}
			return E_DB_SHOP_R;
		}
		rows++;
		param->out_shop_id = shop_node.leaf_id;
		ret = do_process_trade(param);
		if(ret)
		{
			writelog(LOG_ERR,"Ҷ���̻����ʧ��shop[%s],ret[%d]"
				,shop_node.shop_name,ret);
			DB_v_cif_shop_tree_close_select_by_c1();
			return ret;
		}
		
	}
	// ������н��,����Ϊ����
	if(amtcmp(param->remain_balance,0) > 0)
	{
		writelog(LOG_ERR,"����̻�����");
		return E_FAN_ACC_INSUFFICIENT;
	}
	return 0;
}

int F847222(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char  ia_buf[1024]="";
	char sMsg[256]="";
	double dUniNo;
	InAcc IA;
	T_t_tif_tradeserial serial;
	T_t_aif_account account;
	T_t_cif_shop shop;
	trade_param_t param;
	int shop_id;
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int i;

	ResetNormalCPack(&aPack,0,1);

	shop_id = atoi(rPack->sbank_acc);
	if(shop_id <= 0)
	{
		*pRetCode = E_SHOP_ACTNO_NOT_EXIST;
		goto L_RETU;
	}
	if(strlen(rPack->scard0) <= 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if(amtcmp(rPack->damt1,0)<=0)
	{
		*pRetCode = E_INPUT_AMT;
		goto L_RETU;
	}
	ret = CheckOperatorPwd(rPack->scard0,rPack->semp_pwd);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	memset(&account,0,sizeof account);
	memset(&shop,0,sizeof shop);
	
	ret = DB_t_cif_shop_read_by_shop_id(shop_id,&shop);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode  = E_SHOP_ACTNO_NOT_EXIST;
		else
			*pRetCode = E_DB_SHOP_R;
		goto L_RETU;
	}
	if(strcmp(shop.is_indep, TYPE_YES))
	{
		*pRetCode = E_FAN_SHOP_NOT_INDEP;
		goto L_RETU;
	}
	memset(&IA,0,sizeof IA);
	memset(&param,0,sizeof param);
	param.pIA = &IA;
	IA.pVoidPointer = ia_buf;
	param.shop_id = shop.shop_id;
	param.remain_balance = rPack->damt1;
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniNo);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	param.serial_no = D2I(dUniNo);

	//��ʼ����ˮ��¼
	memset(&serial,0,sizeof serial);
	serial.serial_no = param.serial_no;
	serial.serial_state = SERISTAT_DEBT;
	serial.serial_type = TXCODE_FAN_BALANCE;
	// ������ʾ�����ֶα����̻���
	sprintf(serial.showid,"%d",param.shop_id);
	getsysdate(serial.operate_date);
	getsystime(serial.operate_time);
	des2src(serial.collect_date,serial.operate_date);
	des2src(serial.collect_time,serial.operate_time);
	des2src(serial.enteract_date,serial.operate_date);
	des2src(serial.enteract_time,serial.operate_time);

	des2src(serial.oper_code,rPack->scard0);
	des2src(serial.reserve_1,rPack->scert_addr);
	serial.in_balance = param.remain_balance;
	serial.trade_fee = param.remain_balance;

	des2src(param.tx_date,serial.operate_date);
	des2src(param.tx_time,serial.operate_time);
	des2src(param.oper_code,rPack->scard0);
	
	ret = do_parse_shop(&param);
	if(ret)
	{
		writelog(LOG_ERR,"�̻����ʧ��shop[%d] ret [%d]",param.shop_id,ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,F_LVOL1,F_DAMT1,0);
	
		
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			//sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			//strcat(out_pack->vsmess,sMsg);
			writelog(LOG_INFO,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
		}
	}
	out_pack->lvol1 = IA.iSerialNo;
	out_pack->damt1 = param.free_balance;
	sprintf(out_pack->vsmess,"��ˮ��:%d �����[%.2lf]Ԫ,���[%.2lf]Ԫ"
		,IA.iSerialNo,rPack->damt1,out_pack->damt1);
	//strcat(out_pack->vsmess,IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);
	
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

