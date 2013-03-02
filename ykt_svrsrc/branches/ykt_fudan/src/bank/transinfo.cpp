/* ----------------------------------------------------------
 * �������ƣ�transinfo.h
 * �������ڣ�2004-09-09 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�����ת�ʸ��ֽ��׺���ʵ��
 * ----------------------------------------------------------
 * �޸�����: 2005-03-10
 * �޸���Ա: ����
 * �޸�����: ��������ͨ�Ų����Ƶ�bank.h������bu������룬��bankguard����
 *           �˴�ֻ����pos�������������нӿڵ��ã�
 * �汾��Ϣ��1.0.1.1
 * ----------------------------------------------------------*/
#include <stdlib.h>
#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
#include "errdef.h"
#include "mypub.h"
#include "tcp.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
#include "account.h"
#include "bank.h"


#ifndef	DEBUG
	#define	DEBUG
#endif
void dec2hex(unsigned char *sDec,int dec_len,char *sHex);
void hex2dec(char *sHex,unsigned char * sDec,int dec_len);



//��ѯת����ˮ
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID * handle,int *pRetCode,char *szMsg);
int DelTrans(INNER_TRANS_REQUEST * pnode,int other_serial_no)
{
	int ret=0;
	T_t_tif_tradeserial  tradeserial;
	INNER_TRANS_REQUEST from_pos;
	double unique=0;
	memset(&tradeserial,0,sizeof(T_t_tif_tradeserial));			//�����ˮ�ṹ��
	memset(&from_pos,0,sizeof(from_pos));
	memcpy(&from_pos,pnode,sizeof(from_pos));
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);			//��ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	tradeserial.card_id=atoi(from_pos.CardNo);
	tradeserial.purse_id=0;
	tradeserial.serial_no=int(unique);
	tradeserial.serial_type=TRADE_INNER_DETRANS;			//���״���
	tradeserial.serial_state=SERISTAT_NONEEDDEBT;			//��ˮ״̬
	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		memcpy(tradeserial.operate_date,from_pos.TradeDate,sizeof(from_pos.TradeDate));		//��������
		memcpy(tradeserial.operate_time,from_pos.TradeTime,sizeof(from_pos.TradeTime));		//����ʱ��
	}
	//memcpy(tradeserial.operate_date,from_pos.TradeDate,sizeof(from_pos.TradeDate));		//��������
	//memcpy(tradeserial.operate_time,from_pos.TradeTime,sizeof(from_pos.TradeTime));		//����ʱ��
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));//�ɼ�����
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));//�ɼ�ʱ��
	tradeserial.maindevice_id=GetTransferSystemId();				//��ϵͳ����
	tradeserial.device_id=atoi(from_pos.TerminalId);			//�ն�ID
	tradeserial.trade_fee=atol(from_pos.TransMoney)/100;			//ת�ʽ��
	memcpy(tradeserial.b_act_id,from_pos.BankCardNo,sizeof(from_pos.BankCardNo));	//���п��ţ�����������������ݿ��ֶ�
	tradeserial.sys_id=AGRICULTURE_BANK_CODE;				//�ⲿϵͳ��ʶ���˴�Ϊ���ֶ������--- ũҵ����Ϊ1
	tradeserial.condition_id=SELF_TRANS;						//�Զ�/����ת�ʱ�ʶ
	strcpy(tradeserial.oper_code,"system");						//����Ա����
	tradeserial.other_seri_no=other_serial_no;					//ԭʼ��ˮ��
	tradeserial.tmark=0;									//������¼�������ʹ�����

	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		return 	E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	writelog(LOG_ERR,"detrans ok");
	return	0;


}

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
	p->out_balance=IA->dOutCardBala;			//����ֵ
	return 0;
}

//POS��½	240101
int Pos_Login(INNER_TRANS_REQUEST * pNode)
{
	//double unique=0;
	int ret=0;
	INNER_TRANS_REQUEST  from_pos;


	//����δǩ���ɹ���POS���ܵ�½������Կ
	if(!BANK_LOGIN)
	{
		writelog(LOG_ERR,"System not login to bank,pos login forbidden!shm[1]=[%d]",shm[1]);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NETERR);
		return	E_TRANS_BANK_NETERR;
	}

	memcpy(&from_pos,pNode,sizeof(from_pos));
	T_t_tif_tradeserial  	tradeserial;		//��������ˮ�� 	tradeserial;
	T_t_pif_device 		t_pif_device;
	T_t_pif_cur_syspara 	t_syspara;


	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&t_pif_device,0,sizeof(t_pif_device));
	memset(&t_syspara,0,sizeof(t_syspara));

	ret=DB_t_pif_cur_syspara_read_by_id(2006, &t_syspara);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	ret=DB_t_pif_device_read_lock_by_cur_and_device_id(atoi(from_pos.TerminalId),&t_pif_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	t_pif_device.state_id=DEVISTAT_ONLINE;		//�����豸ע���״̬Ϊ����״̬
	ret=DB_t_pif_device_update_lock_by_cur(&t_pif_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_update_lock_by_cur error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

    	ret=db_commit();
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	//���Ӧ���������pNode
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	memcpy(pNode->BankCardPwd,shm+2+8,sizeof(pNode->BankCardPwd));
	memcpy(pNode->BankCardNewPwd,t_syspara.value,sizeof(pNode->BankCardNewPwd));
	writelog(LOG_INFO,"device login dev[%d] shm=[%s],pNode->bankcardpwd[%s]",t_pif_device.device_id,shm,pNode->BankCardPwd);
	return 0;
}


//��ѯУ԰�����
//��ʱ�ù���ȡ�����ն�ͨ����д��ȡ�����
int Pos_QuerySchool(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	//double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
	//T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	T_t_aif_account account;
	T_t_pif_card card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}


	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//�жϿ������Ƿ���ȷ
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

	//���ݿ��ź�Ǯ���ţ������ʺ�
	ret=GetActnoByCardIdAndPurseId(account_id,atoi(from_pos.CardNo),from_pos.Notecase);
	if(ret)
	{
		writelog(LOG_ERR,"GetActnoByCardIdAndPurseId err,CardNo=[%s],Notecase=[%s]",from_pos.CardNo,from_pos.Notecase);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}

	ret=DB_t_aif_account_read_by_account_id(account_id, &account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	//���Ӧ���
	memset(pNode,0,sizeof(from_pos));
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	//printf("�����= [%f]\n",account.cur_freebala);
	sprintf(pNode->AccountMoney,"%f",account.cur_freebala);
	writelog(LOG_INFO,"query school card balance succeed!");

	return 0;

}

//��ѯ���п����
int Pos_QueryBank(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	double unique=0;
//	char buffer[1024]="";


	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak,BankAnsPak;
	T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	struct SockNode SockNode;

	memset(&SockNode,0,sizeof(SockNode));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&tradeserial,0,sizeof(tradeserial));

	memcpy(&from_pos,pNode,sizeof(from_pos));


	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}


	//��֯���а�
	//д���״���
	memcpy( BankReqPak.TradeCode,TRADE_BANK_QUERY, BANK_TRADE_CODE_LEN);
	//д�������ںͽ���ʱ��
	ret=get_datetime_from_db(BankReqPak.TradeDate,BankReqPak.TradeTime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
		memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	}
	//memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	//memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//д���п����ֶ�
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//д���п����ֶ�
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);
	//д���п������ֶ�
	//ͨ��16���Ƹ�ʽ���䣬�ٽ���
	hex2dec(from_pos.BankCardPwd, (unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));
	#ifdef DEBUG
		char buffer[100]="";
		int k=0;
		for(int i=0;i<16;i++)
		{
			k=(unsigned char)BankReqPak.BankCardPwd[i];
			sprintf(&buffer[2*i],"%02X",k);
		}
		writelog(LOG_INFO,"BankCardNo=[%s],BankCardPwd=[%s]",BankReqPak.BankCardNo,buffer);
		writelog(LOG_INFO,"BankCardNo=[%s],fromCardPwd=[%s]",BankReqPak.BankCardNo,from_pos.BankCardPwd);
	#endif

	//дУ԰����ˮ��
	sprintf(BankReqPak.CustSn,"%-8f",unique);
	//дԺУ����
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);
	BankReqPak.AutoFlag='0';
	//дУ��mac��
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);

	//memcpy(SockNode.Buf,&BankReqPak,sizeof(BankReqPak));
	TRACE_BANK_TRANS(&BankReqPak,"send query bank package");

	ret=send_to_and_recv_from_bank((char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),0);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}


	TRACE_BANK_TRANS(&BankAnsPak,"receivce query bank package");

	//ũ����ʱδУ���mac,������ʱ���ε�
	/*
	ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	if(ret)
	{
		writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	//�������ݿ���ˮ��־,������дһЩ�����ֶ��Լ���д���з�����Ϣ�ȣ���������ʱ����û��
	/*
	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(int(unique), &tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"read from t_tif_tradeserial table error,error code=[%d]",ret);
		sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		db_rollback();
		return 	E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//���п���ʧ
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//���п�״̬����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//���п�����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//�����������
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//ͨѶ����Կ��
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}

	//���Ӧ���
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	memcpy(pNode->Balance,BankAnsPak.Balance,sizeof(pNode->Balance));
	writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%s]",BankAnsPak.Balance);
	return 0;

}

//�޸�У԰������
int Pos_ChangePwd(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	//char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
//	double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
//	T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	T_t_aif_account account;
	T_t_pif_card card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//�жϿ������Ƿ���ȷ
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

	Strncpy_t(account_pwd, from_pos.AccountNewPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);
	memcpy(card.password,pwd,sizeof(card.password));
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_update_lock_by_cur error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}
	//���Ӧ���

	memset(pNode,0,sizeof(from_pos));
	writelog(LOG_INFO,"Change school card password succeed!");
	return 0;

}

//��ʧУ԰��

int Pos_LostCard(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

  	int ret = 0;
	char enddate[10 + 1] = "";
	int	card_id = 0;
	char	Operator[33+1] = "";
	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
//	char		sCardState[5] = "";

	INNER_TRANS_REQUEST  from_pos;

	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_aif_account	account;
	T_t_pif_card	card;

	memset(&from_pos,0,sizeof(from_pos));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));

	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}

	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	ret=get_tradecard_no_by_stupid(from_pos.CardNo,&card_id);			//����ʶ
	if(ret)
	{
		if(100==ret)
		{
			writelog(LOG_ERR,"get_tradecard_no_by_stupid have no recode,errcode=[%d]",ret);
			return E_TRANS_SCHACC_NOEXIT;
		}
		if(-811==ret)
		{
			writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
			return E_TRANS_SCHCARD_TWICE;
		}
		writelog(LOG_ERR,"get_tradecard_no_by_stupid error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//writelog(LOG_INFO,"card_id=[%d]",*pCardid);


	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id,&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_by_card_id error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	Cut_id = card.cosumer_id;														//�ͻ���
	des2src(Operator,"system");												//����Ա��
	maindevice_id = GetTransferSystemId();											//�ϴ�����վ��ʶ
	device_id = atoi(from_pos.TerminalId);										//�ɼ��豸��ʶ

	//�жϿ������Ƿ���ȷ
	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		return E_TRANS_SCHCARD_PWDERR;
	}
	/*
	//	���ͻ���Ϣ���ж��Ƿ���Թ�ʧ
	ret = GetCardState(card_id,sCardState);
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"GetCardState error,errcode=[%d],card_id=[%d]",ret,card_id);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	//	�޸Ŀ�״̬Ϊ��ʧ
	card.state_id[CARDSTAT_TYPE_LOST]=STATE_TRUE;
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	���뿨��ʧ��Ч���ޱ�
	/*
	ret=GetLostCardValiddate(sysdate,enddate);											//��ù�ʧ��Ч����
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"GetLostCardValiddate=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	cardlossinfo.card_id = card_id;													//����
	des2src(cardlossinfo.begin_date,sysdate);											//��ʼ����
	des2src(cardlossinfo.end_date,enddate);											//��������
	des2src(cardlossinfo.operate_date,sysdate);										//��������
	des2src(cardlossinfo.operate_time,systime);										//����ʱ��
	cardlossinfo.state_id=STATE_VALID;												//��Ч
	ret = DB_t_pif_cardlossinfo_add(&cardlossinfo);
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_add=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	//����ÿ��ű�����,���ʧʱ�Ժ�����������
	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		ret=DB_t_tif_black_sheet_del_by_card_id_and_is_ad(card.card_id,DELETE_BLACKLIST);
		if(ret)
		{
			if(ret!=DB_NOTFOUND)
			{
				writelog(LOG_ERR,"DB_t_tif_black_sheet_del_by_card_id_and_is_ad error,errcode=[%d],card_id=[%d]",ret,card.card_id);
				return E_TRANS_UNKNOW_ERROR;
			}
		}
		ret=InsertToBlkList(card.card_id,ADD_BLACKLIST);
		if(ret)
		{
			writelog(LOG_ERR,"InsertToBlkList error,errcode=[%d],card_id=[%d]",ret,card.card_id);
			return E_TRANS_UNKNOW_ERROR;
		}

		//�㲥������
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card.card_id);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//��ɾ��־

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"AddMsgLst=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

	}


	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//��������
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);
	des2src(tradeserial.collect_date,tradeserial.operate_date);								//�ɼ�����
	des2src(tradeserial.collect_time,tradeserial.operate_time);								//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);							//��������
	des2src(tradeserial.enteract_time,tradeserial.operate_time);							//����ʱ��
	tradeserial.serial_no = (int)dUniqno;									//��ˮ��
	tradeserial.serial_type = TXCODE_CARD_LOSS;							//��ʧ
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;						//��ˮ״̬
	tradeserial.maindevice_id = GetTransferSystemId();						//�ϴ�����վ��ʶ
	tradeserial.device_id = atoi(from_pos.TerminalId);						//�ɼ��豸��ʶ
	tradeserial.card_id = card_id;										//���׿���
	tradeserial.customer_id=Cut_id;										//�ͻ���
	des2src(tradeserial.oper_code,Operator);
	tradeserial.other_seri_no=from_pos.SendNo;

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	return 0;
}

int Pos_UnlostCard(INNER_TRANS_REQUEST * pNode)
{

	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

  	int ret = 0;
	//char enddate[10 + 1] = "";
	//int	card_id = 0;
	char	Operator[33+1] = "";
	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
//	char		sCardState[5] = "";

	INNER_TRANS_REQUEST  from_pos;

	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_aif_account	account;
	T_t_pif_card	card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));


	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//�жϿ������Ƿ���ȷ
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}

	Cut_id = card.cosumer_id;													//�ͻ���
	des2src(Operator,"system");												//����Ա��
	//maindevice_id = GetTransferSystemId();										//�ϴ�����վ��ʶ
	//device_id = atoi(from_pos.TerminalId);										//�ɼ��豸��ʶ

	//des2src(sysdate,from_pos.TradeDate);
	//des2src(systime,from_pos.TradeTime);

	//des2src(black_sheet.operate_date,sysdate);
	//des2src(black_sheet.operate_time,systime);

	//des2src(hi_enddate,sysdate);
	//des2src(hi_endtime,systime);

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHCARD_FREEZE;
	//	return E_TRANS_SCHCARD_UNLOSTING;
	}
	//ȥ���ظ���ҵ����ƣ���������״̬�½�ң����·�����
	//�����ʧ״̬���ж��Ƿ���ڷǹ�ʧ�������һ�ſ�
	//����ǣ���������
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		ret=IsExistNoLostCardByCustomId(Cut_id);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			return E_TRANS_SCHCARD_TWICE;
		}
	}
	//�޸Ĺ�ʧ��״̬Ϊ��Ч
	/*
	ret=DB_t_pif_cardlossinfo_read_lock_by_cur1_and_card_id_and_state_id(card.card_id,STATE_VALID,&cardlossinfo);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_read_lock_by_cur1_and_card_id_and_state_id error,card_id=[%d],errcode=[%d]",card.card_id,ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	cardlossinfo.state_id=STATE_INVALID;
	des2src(cardlossinfo.end_date,sysdate);
	ret=DB_t_pif_cardlossinfo_update_lock_by_cur1(&cardlossinfo);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_update_lock_by_cur1 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//״̬��Ϊ����������Ч״̬,����Ϊ��״̬
		//�޸�ԭ���ĺ�������״̬��־Ϊ��Ч
		//	�����������
		black_sheet.card_id = card.card_id;
		black_sheet.is_ad = DELETE_BLACKLIST;
		des2src(black_sheet.operate_date,sysdate);
		des2src(black_sheet.operate_time,systime);
		memcpy(black_sheet.volume,sysdate+2,6);
		memcpy(black_sheet.volume+6,systime,6);
		strcpy(black_sheet.validdate,VALIDDATE);
		black_sheet.state_id = STATE_VALID;
		ret = DB_t_tif_black_sheet_add(&black_sheet);
		if (ret)
		{
			writelog(LOG_ERR,"DB_t_tif_black_sheet_add error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		//�㲥������
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,black_sheet.card_id);
		AddXmlItemStr(tMesList.incontent, XML_KEY_VERNUM, black_sheet.volume);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,black_sheet.is_ad);	//��ɾ��־

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"AddMsgLst error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
	}
	//	�޸Ŀ�״̬Ϊ���״̬
	card.state_id[CARDSTAT_TYPE_LOST]=STATE_FALSE;
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card.card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//��������
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);				//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	tradeserial.serial_no = (int)dUniqno;													//��ˮ��
	tradeserial.serial_type = TXCODE_CARD_COMEBACK_LOSS;								//���
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;										//��ˮ״̬
	tradeserial.maindevice_id = GetTransferSystemId();									//�ϴ�����վ��ʶ
	tradeserial.device_id = atoi(from_pos.TerminalId);										//�ɼ��豸��ʶ
	tradeserial.card_id = card.card_id;														//���׿���
	tradeserial.customer_id = Cut_id;
	des2src(tradeserial.oper_code, "system");
	//	���뿨������ˮ��
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	return 0;
}

//POSת��
int Pos_Transfer(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	double unique=0;
	int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak,BankAnsPak;
	T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	T_t_tif_tradeserial  tradeserial_bak;
	T_t_pif_card		card;
	InAcc	IA;

	memset(&tradeserial_bak,0,sizeof(tradeserial_bak));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&card,0,sizeof(card));

	memcpy(&from_pos,pNode,sizeof(from_pos));
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	//�ж��Ƿ������ս���״̬
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		writelog(LOG_ERR,"System is balance now!");
		return E_TRANS_BANK_SERVICE_NOEXIT;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return E_TRANS_SCHACC_NOEXIT;
	}

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHACC_DESTORY;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_WFAIL])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_WFAIL;
	}

	//ת�˲�����תС�����
	if(0!=memcmp(from_pos.TransMoney+7,"00",2))
	{
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",atol(from_pos.TransMoney)/100.00);
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}

	//��ʼ�����ˮ����
	//��ˮ��
    alarm(3);
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
    alarm(0);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
    
	tradeserial.serial_no=int(unique);
	//��¼��ˮ�ţ���Ϊ����ʹ��
	temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=from_pos.SendNo;	//�ϴ�����ˮ��
	tradeserial.serial_type=TRADE_INNER_TRANS;	//���״���
	tradeserial.serial_state=SERISTAT_NODEBT;	//��ˮ״̬
	tradeserial.card_id=atoi(from_pos.CardNo);
	tradeserial.purse_id=0;
	tradeserial.in_balance=double(atoi(from_pos.AccountMoney)/100.00);	//�뿨���
	tradeserial.out_balance=tradeserial.in_balance;						//�������
	tradeserial.trade_count=from_pos.RecvNo+1;							//��ǰ���н��״���

	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(tradeserial.operate_date);
		getsystime(tradeserial.operate_time);
	}
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));	//�ɼ�����
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));	//�ɼ�ʱ��
	Strncpy_t(tradeserial.enteract_date,logicdate,sizeof(tradeserial.enteract_date));	//��������
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//����ʱ��
	tradeserial.maindevice_id=GetTransferSystemId();	//��ϵͳ����
	tradeserial.device_id=atoi(from_pos.TerminalId);	//�ն�ID
	tradeserial.trade_fee=atol(from_pos.TransMoney)/100.00;	//ת�ʽ��
	//���п��ţ�����������������ݿ��ֶ�
	memcpy(tradeserial.b_act_id,from_pos.BankCardNo,sizeof(from_pos.BankCardNo));
	tradeserial.sys_id=AGRICULTURE_BANK_CODE;	//�ⲿϵͳ��ʶ���˴�Ϊ���ֶ������--- ũҵ����Ϊ1
	tradeserial.condition_id=SELF_TRANS;	//�Զ�/����ת�ʱ�ʶ
	//tradeserial.out_account_id=;
	//tradeserial.in_account_id=;
	tradeserial.customer_id=card.cosumer_id;
	strncpy(tradeserial.oper_code,"system",sizeof(tradeserial.oper_code));	//����Ա����
	//���������ˮ����
	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		return 	E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//����ˮ�ṹ������������Ϊ�������ʺ������
	//��ֹ�ظ��������
	memcpy(&tradeserial_bak,&tradeserial,sizeof(tradeserial_bak));

	double trade_fee=0;
	double board_fee=0;
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_aif_account	tAccount;		//�ʻ���
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;

	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));

	//�ж�ת�ʽ���Ƿ񳬳�Ǯ������޶�
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}

	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	//��ȡ�ͻ��շ�����ֶ�
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}

	if(0==tCustomer.fee_type)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				writelog(LOG_ERR,"DB_t_pif_spefee_read_by_dept_code_and_cut_type error,errcode=[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//���¿ͻ�����շ�����ֶ�
		/*
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
		*/
	}
	DB_t_cif_customer_free_lock_cur();
	//��д���˽ṹ,�����Ž�
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
/*
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;

*/
	//����--�Ƿ�processҲҪ�޸�

	ret=process(&IA,&tradeserial_bak);
	if(ret)
	{
		writelog(LOG_ERR,"test process err,errcode[%d]",ret);
		return	E_TRANS_UNKNOW_ERROR;
	}
	//������Գɹ���Ȼ�ع�
	ret=db_rollback();
	if(ret)
	{
		writelog(LOG_ERR,"db_rollback err,errcode[%d]",ret);
		return	E_TRANS_UNKNOW_ERROR;
	}

	//��֯���а�
	memcpy(BankReqPak.TradeCode,TRADE_BANK_TRANS, BANK_TRADE_CODE_LEN);	//д���״���
	memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//�������и��Ľӿ��е�У԰���˺��ֶ�ֻ��10������
	//����������У԰���˺��ֶ�����дУ԰������
	sprintf(BankReqPak.CustAccountNo,"%-10d",atoi(from_pos.CardNo));
	/*
	//дУ԰���ʺ�
	ret=GetActnoByCardIdAndPurseId(BankReqPak.CustAccountNo,atoi(from_pos.CardNo),from_pos.Notecase);
	if(ret)
	{
		writelog(LOG_ERR,"GetActnoByCardIdAndPurseId error,CardNo=[%s],Notecase=[%d]",from_pos.CardNo,from_pos.Notecase);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//д���п����ֶ�
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);	//д���п����ֶ�
	memcpy(BankReqPak.MercAccount,SCHOOL_ACCOUNT_NO,sizeof(BankReqPak.MercAccount));	//д�̻����ֶ�
	sprintf(BankReqPak.TransMoney,"%-9s",from_pos.TransMoney);	//дת�ʽ���ֶ�
	//ͨ��16���ƴ��䣬Ȼ�����
	hex2dec(from_pos.BankCardPwd,(unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));	//д���п������ֶ�
	sprintf(BankReqPak.CustSn,"%-d",tradeserial.serial_no);	//дУ԰����ˮ��
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);	//дԺУ����
	BankReqPak.AutoFlag='0';	//д�Զ�������־
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);//дУ��mac��

	TRACE_BANK_TRANS(&BankReqPak,"send transfer package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank((char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),0);
	if(ret)
	{
		if(E_TRANS_BANK_NOANSWER==ret)							//�������û�з��ذ������г�������
		{
			ret=DelTrans(&from_pos,temp_serial_no);
			if(ret)
			{
				writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return E_TRANS_UNKNOW_ERROR;
			}
			writelog(LOG_INFO,"This trade have detrans!");
			return E_TRANS_BANK_NOANSWER;
		}
		else
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
			return ret;
		}
	}

	TRACE_BANK_TRANS(&BankAnsPak,"receive transfer package");

	//У��mac���ж����н��հ��Ƿ���ȷ
	//ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	ret=0;
	if(ret)
	{
			writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
			ret=DelTrans(&from_pos,temp_serial_no);
			if(ret)
			{
				writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return E_TRANS_UNKNOW_ERROR;
			}
			ret=db_commit();
			if(ret)
			{
				writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
			}
			//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
			return	E_TRANS_BANK_RECVERR;
	}

	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//���п���ʧ
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//���п�״̬����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//���п�����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//�����������
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//ͨѶ����Կ��
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//����δ֪����
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}
	//�������ʲ���
	//trade_fee=0;
	//board_fee=0;

	//��д���˽ṹ,�����Ž�
	memset(&IA,0,sizeof(IA));
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process err,errcode[%d]",ret);
		ret=DelTrans(&from_pos, temp_serial_no);
		if(ret)
		{
			writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
			//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
			return E_TRANS_UNKNOW_ERROR;
		}
		return	E_TRANS_UNKNOW_ERROR;
	}
	char sMsg[255]="";
	char sDebugMsg[255]="";
	sprintf(sDebugMsg,"��ˮ��:%d ",IA.iSerialNo);
	double trans_amt=0.0;
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
    	sprintf(sMsg,"��ֵǰ�����:%.2lf ת�ʺ����:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    	strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);
	//double tmp_fee=0;
	//tmp_fee=tradeserial.out_balance;

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(tradeserial.serial_no,&tradeserial_bak);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	//tradeserial.out_balance=tmp_fee;
	tradeserial.serial_state=SERISTAT_DEBT;
	//tradeserial.out_balance=tradeserial.in_balance+tradeserial.trade_fee;
	//tradeserial.boardfee=board_fee;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_tif_tradeserial_free_lock_cur();
	writelog(LOG_ERR,"ou error,error code=[%d]",ret);
	sprintf(pNode->TransMoney,"%f",trans_amt);
	sprintf(pNode->ExtraMoney,"%f",tradeserial.boardfee);
	pNode->RecvNo=tradeserial.serial_no;
	pNode->MngFeeFlag='1';
	writelog(LOG_INFO,"transfer succeed!");
	return 0;
}
//POS�ɷ�
int Pos_Fee(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Pay fee function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//���Ӷ�Ӧ��ϵ
int Pos_AddRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Add realation function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//ɾ����Ӧ��ϵ
int Pos_DelRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Delete relation function is not support for a while!");
	return E_TRANS_FUNC_NONSUPPORT;
}
//��ѯУ԰��ת����ˮ
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID *handle,int *pRetCode,char *szMsg)
{

	char key[32+1]="";
	char pwd[32+1]="";
	//char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	int cnt=0;
	//double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
	T_t_tif_tradeserial  tradeserial;		//��������ˮ��
	T_t_aif_account account;
	T_t_pif_card card;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));


	//�ж��豸�Ƿ��½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//�жϿ������Ƿ���ȷ
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	ret=DB_t_tif_tradeserial_open_select_by_cur3_and_serial_type_and_card_id(TRADE_INNER_TRANS,card.card_id);
	if(ret)
	{
			db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ALERT,"declare cursor err sqlcode[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
	}
	SetCol(handle,0);
   	SetCol(handle,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);

	while(1)
	{
		ret=DB_t_tif_tradeserial_fetch_select_by_cur3(&tradeserial);
		if(ret)
		{
			DB_t_tif_tradeserial_close_select_by_cur3();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial table!");
						break;
					}
				else		break;
			}
			else
				return   E_TRANS_UNKNOW_ERROR;
		}
		cnt++;

		memcpy(from_pos.TradeDate,tradeserial.operate_date,sizeof(from_pos.TradeDate));
		memcpy(from_pos.TradeTime,tradeserial.operate_time,sizeof(from_pos.TradeTime));
		sprintf(from_pos.CardNo,"%d",tradeserial.card_id);
		memcpy(from_pos.BankCardNo,tradeserial.b_act_id,sizeof(from_pos.BankCardNo));
		sprintf(from_pos.TransMoney,"%d",int(tradeserial.trade_fee)*100);
		if(tradeserial.serial_state!=2)
		{
			sprintf(from_pos.RetCode,"%s","ʧ��");
		}
		else sprintf(from_pos.RetCode,"%s","�ɹ�");

		//��ʼ����Ӧ���
		Strncpy_t(out_pack->sclose_emp,from_pos.TradeCode,sizeof(out_pack->sclose_emp));
		Strncpy_t(out_pack->sorder0,from_pos.TransMoney,sizeof(out_pack->sorder0));
		Strncpy_t(out_pack->sorder1,from_pos.ExtraMoney,sizeof(out_pack->sorder1));
		Strncpy_t(out_pack->sserial1,from_pos.AccountMoney,sizeof(out_pack->sserial1));
		out_pack->lvol0=from_pos.SendNo;
		out_pack->lvol1=from_pos.RecvNo;
		memcpy(out_pack->sdate0,from_pos.TradeDate,sizeof(from_pos.TradeDate));
		memcpy(out_pack->stime0,from_pos.TradeTime,sizeof(from_pos.TradeTime));
		memcpy(out_pack->sdate1,from_pos.BankDate,sizeof(from_pos.BankDate));
		memcpy(out_pack->stime1,from_pos.BankTime,sizeof(from_pos.BankTime));
		Strncpy_t(out_pack->scust_no,from_pos.Balance,sizeof(out_pack->scust_no));
		Strncpy_t(out_pack->schange_emp,from_pos.RetCode,sizeof(out_pack->schange_emp));
		Strncpy_t(out_pack->sserial0,from_pos.CardNo,sizeof(out_pack->sserial0));
		out_pack->lvol2=from_pos.Notecase;
		Strncpy_t(out_pack->scust_auth,from_pos.BankCardNo,sizeof(out_pack->scust_auth));
		sprintf(out_pack->sstatus1,"%c",from_pos.MngFeeFlag);
		Strncpy_t(out_pack->semp_pwd,from_pos.AccountPwd,sizeof(out_pack->semp_pwd));
		Strncpy_t(out_pack->semp_pwd2,from_pos.AccountNewPwd,sizeof(out_pack->semp_pwd2));
		Strncpy_t(out_pack->sstation0,from_pos.BankCardPwd,sizeof(out_pack->sstation0));
		Strncpy_t(out_pack->sstation1,from_pos.BankCardNewPwd,sizeof(out_pack->sstation1));
		Strncpy_t(out_pack->sorder2,from_pos.TerminalId,sizeof(out_pack->sorder2));
//	printf("LINE:%d\n",__LINE__);

		PutRow(handle,out_pack,pRetCode,szMsg);
		if(cnt>=10)
		{
			DB_t_tif_tradeserial_close_select_by_cur3();
			break;
		}
	}
//	printf("LINE:%d\n",__LINE__);


	T_t_tif_tradeserial_his tradeserial_his;
	memset(&tradeserial_his,0,sizeof(tradeserial_his));

	if(cnt<10)
	{
		ret=DB_t_tif_tradeserial_his_open_select_by_cur1_and_serial_type_and_card_id(TRADE_INNER_TRANS,card.card_id);
		if(ret)
		{
				db_chk_err(__FILE__,__LINE__,&sqlca);
				writelog(LOG_ALERT,"declare cursor err sqlcode[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
		}
	//	printf("LINE:%d\n",__LINE__);

		while(1)
		{
			ret=DB_t_tif_tradeserial_his_fetch_select_by_cur1(&tradeserial_his);
			if(ret)
			{
				DB_t_tif_tradeserial_his_close_select_by_cur1();
				if(ret==DB_NOTFOUND)
				{
					writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial_his table!");
					break;
				}
				else
					return   E_TRANS_UNKNOW_ERROR;
			}
			cnt++;

			memcpy(from_pos.TradeDate,tradeserial_his.operate_date,sizeof(from_pos.TradeDate));
			memcpy(from_pos.TradeTime,tradeserial_his.operate_time,sizeof(from_pos.TradeTime));
			sprintf(from_pos.CardNo,"%d",tradeserial_his.card_id);
			memcpy(from_pos.BankCardNo,tradeserial_his.b_act_id,sizeof(from_pos.BankCardNo));
			sprintf(from_pos.TransMoney,"%d",int(tradeserial_his.trade_fee)*100);
			if(tradeserial_his.serial_state!=2)
			{
				sprintf(from_pos.RetCode,"%s","ʧ��");
			}
			else sprintf(from_pos.RetCode,"%s","�ɹ�");

			//��ʼ����Ӧ���
			Strncpy_t(out_pack->sclose_emp,from_pos.TradeCode,sizeof(out_pack->sclose_emp));
			Strncpy_t(out_pack->sorder0,from_pos.TransMoney,sizeof(out_pack->sorder0));
			Strncpy_t(out_pack->sorder1,from_pos.ExtraMoney,sizeof(out_pack->sorder1));
			Strncpy_t(out_pack->sserial1,from_pos.AccountMoney,sizeof(out_pack->sserial1));
			out_pack->lvol0=from_pos.SendNo;
			out_pack->lvol1=from_pos.RecvNo;
			Strncpy_t(out_pack->sdate0,from_pos.TradeDate,sizeof(out_pack->sdate0));
			Strncpy_t(out_pack->stime0,from_pos.TradeTime,sizeof(out_pack->stime0));
			Strncpy_t(out_pack->sdate1,from_pos.BankDate,sizeof(out_pack->sdate1));
			Strncpy_t(out_pack->stime1,from_pos.BankTime,sizeof(out_pack->stime1));
			Strncpy_t(out_pack->scust_no,from_pos.Balance,sizeof(out_pack->scust_no));
			Strncpy_t(out_pack->schange_emp,from_pos.RetCode,sizeof(out_pack->schange_emp));
			Strncpy_t(out_pack->sserial0,from_pos.CardNo,sizeof(out_pack->sserial0));
			out_pack->lvol2=from_pos.Notecase;
			Strncpy_t(out_pack->scust_auth,from_pos.BankCardNo,sizeof(out_pack->scust_auth));
			sprintf(out_pack->sstatus1,"%c",from_pos.MngFeeFlag);
			Strncpy_t(out_pack->semp_pwd,from_pos.AccountPwd,sizeof(out_pack->semp_pwd));
			Strncpy_t(out_pack->semp_pwd2,from_pos.AccountNewPwd,sizeof(out_pack->semp_pwd2));
			Strncpy_t(out_pack->sstation0,from_pos.BankCardPwd,sizeof(out_pack->sstation0));
			Strncpy_t(out_pack->sstation1,from_pos.BankCardNewPwd,sizeof(out_pack->sstation1));
			Strncpy_t(out_pack->sorder2,from_pos.TerminalId,sizeof(out_pack->sorder2));

			PutRow(handle,out_pack,pRetCode,szMsg);
			if(cnt>=10)
			{
				DB_t_tif_tradeserial_his_close_select_by_cur1();
				break;
			}

		}
	}


	writelog(LOG_INFO,"query trans record succeed!");
	return 0;
}
//Ȧ���д��ʧ�ܳ���(ʵ�ʲ���������ֻ�Ǹ�д��״̬)
int Pos_WriteErrCard(INNER_TRANS_REQUEST * pNode)
{

	int ret = 0;
	int card_id = 0;
	char logicdate[11]="";
	int serial_no=0;
	T_t_pif_card  card;
	T_t_tif_tradeserial tradeserial;

	INNER_TRANS_REQUEST from_pos;

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&card,0,sizeof(card));

	memcpy(&from_pos,pNode,sizeof(from_pos));
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"GetLogicDate err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	serial_no=from_pos.RecvNo;
	ret=DB_t_tif_tradeserial_read_by_serial_no(serial_no,&tradeserial);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_tif_tradeserial_read_by_serial_no err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//�޸�ԭ��״̬Ϊ����д��ʧ��״̬
	card_id = tradeserial.card_id;

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &card);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_pif_card_read_lock_by_cur_and_card_id err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	card.state_id[CARDSTAT_TYPE_WFAIL]=STATE_TRUE;
	memset(card.comments,0,sizeof(card.comments));
	AddXmlItemStr(card.comments, XML_KEY_OPERATEDATE,logicdate);
	AddXmlItemInt(card.comments,XML_KEY_SERIALNO,serial_no);
	AddXmlItemInt(card.comments,XML_KEY_TRADECODE,TRADE_INNER_TRANS);

	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_pif_card_update_lock_by_cur err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	writelog(LOG_INFO,"update card status succeed!");

	return 0;

}
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}
void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

