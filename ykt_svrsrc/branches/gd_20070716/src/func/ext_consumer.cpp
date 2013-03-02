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
#include "tcp.h"
#include "rsa.h"
#include "ext_consumer.h"
#include "svrlink.h"
#include "bupub.h"

#define PRE_CHEDK_ENTER_ACCOUNT_MOBILE_TRANS		240200		//�ֻ���ֵ
#define PRE_ENTER_ACCOUNT_WATER_TRANS	240201	//ˮ��ת��
#define TERMINAL_TRADE						240202

extern CSvrLink g_SvrLink;
int SetHeadCol(ST_CPACK *in_cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, in_cpack);
	while ((arg = va_arg(ap, int)) >= 0)
	{
		SetParmBit(&(in_cpack->head), arg);
	}
	va_end(ap);
    return(g_SvrLink.SetCol(0, in_cpack->head.ParmBits));
}

	
static int packege_send_data(ST_PACK *in_pack,int flag,char *send_data){
	int ret =0;
	//char cellphone[31]="";	//��ֵ�ֻ���
	double money=0;			//��ֵ���
	char sysdate[11]="";
	char systime[9]="";
	char sysdatetime[20]="";
	char serialno[20]="";
	char sCutId[21]="";
	char sMoney[20]="";
	T_t_pif_card	tCard;
//	ext_phone_trans_t phone_trans_struct;
	ext_phone_trans_t* phone_trans_struct;
	phone_trans_struct=(ext_phone_trans_t*)send_data;
	
	memset(&tCard,0,sizeof(tCard));
	memset(phone_trans_struct,0x20,sizeof(ext_phone_trans_t));
	
	phone_trans_struct->prix[0]=0x31;
	memcpy(phone_trans_struct->length,"0067",4);
	if(1==flag)
	{
		memcpy(phone_trans_struct->type,"0100",4);
	}
	else if(2==flag)
	{
		memcpy(phone_trans_struct->type,"0200",4);		
	}
	//memcpy(phone_trans_struct->bitery,"0000000000000000",16);
	memset(phone_trans_struct->bitery,'0',sizeof(phone_trans_struct->bitery));
	ret=DB_t_pif_card_read_by_card_id(in_pack->lvol0, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}
	sprintf(phone_trans_struct->cutid,"%-22d",tCard.card_id);	//�ĳɴ�����
	money = in_pack->damt1;
	int i_money=D4U5(money*100,0);
	sprintf(sMoney,"%07d",i_money);
	memcpy(phone_trans_struct->money,sMoney,sizeof(phone_trans_struct->money));
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}
	strcpy(sysdatetime,sysdate+4);
	strcat(sysdatetime,systime);
	memcpy(phone_trans_struct->datetime,sysdatetime,10);
	memcpy(phone_trans_struct->tracenum,sysdate,8);
	sprintf(serialno,"%06d",in_pack->lvol6%1000000);
	memcpy(phone_trans_struct->tracenum+8,serialno,6);
	memcpy(phone_trans_struct->phone,in_pack->sphone,strlen(in_pack->sphone));
	memcpy(phone_trans_struct->retnum,"00",2);
	memcpy(phone_trans_struct->plugdata,"123456789012345678901234567890123456",36);	

	/*
	memcpy(send_data,phone_trans_struct->prix,1);
	memcpy(send_data+1,phone_trans_struct->length,4);
	memcpy(send_data+5,phone_trans_struct->type,4);
	memcpy(send_data+9,phone_trans_struct->bitery,16);
	memcpy(send_data+25,phone_trans_struct->cutid,22);
	memcpy(send_data+47,phone_trans_struct->money,7);
	memcpy(send_data+54,phone_trans_struct->datetime,10);
	memcpy(send_data+64,phone_trans_struct->tracenum,14);
	memcpy(send_data+78,phone_trans_struct->phone,11);
	memcpy(send_data+89,phone_trans_struct->retnum,2);
	memcpy(send_data+91,phone_trans_struct->plugdata,36);
	*/
	writelog(LOG_ERR,"package send data=[%s]",send_data);
	return 0;
	
}

#define package_len 327
#define TIMEOUT 180

//�ӵ�����ȷ���ֻ��������ȷ��
static int 	check_cellphone(ST_PACK *in_pack,transfer_control_t *trans_ctl)
{
	int ret = 0;	
	char host[16]="";		//�Է�������ip
	char portchar[10]="";
	short port=0;				//�Է�������port
	char rcvdata[package_len+1]="";		//���նԷ��Ĵ�������
	char senddata[package_len+1]="";	//���ܺ�Ĵ�������
	char tempdate[package_len+1-200]="";
	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;

	ext_phone_trans_t	 PhoneTrans;
	
	memset(tempdate,0,sizeof tempdate);
	trans_ctl->check_user_pwd = 0;
	CTcpSocket tcpsocket ;

	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	
	ret=GetParameter(2104, host);	
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2105, portchar);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2106, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2107, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ret = packege_send_data(in_pack,1,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}

	memcpy(tempdate,senddata,package_len-200);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_SCUST_AUTH,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	sPack.head.RequestType = 250001;
	des2src(sPack.pack.ssectypes,tempdate);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	return 0;

}
//��õ�������ֵҵ���Ӧ���̻�id
static int get_third_part_account(ST_PACK *in_pack,int trade_code,InAcc *IA){
	int ret=0;
	int cnt=0;
	char szActno[17]="";				//�ʻ�
	int shpid=0;						//�̻�ID
	T_t_cif_shop		shop;			//�̻���Ϣ��
	T_t_aif_account	account;		//�ʻ���
	T_t_cif_customer	tCustomer;		//�ͻ���
	T_t_pif_spefee 	tSpeFee;
	T_t_pif_card		tCard;
	T_t_tradecode_shop tradeshop;
	memset(&tCard,0,sizeof(tCard));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	//���ݽ��״���ȡ��
	memset(&tradeshop,0,sizeof(tradeshop));
	
	ret =DB_t_tradecode_shop_open_select_by_c0_and_trade_code(trade_code);
	if(ret){
		writelog(LOG_ERR,"DB_t_tradecode_shop_open_select_by_c0_and_trade_code error,errcode=[%d]",ret);
		return 	ret;
	}
	while(1){
		memset(&tradeshop,0,sizeof(tradeshop));
		ret =DB_t_tradecode_shop_fetch_select_by_c0(&tradeshop);
		if(ret){
			DB_t_tradecode_shop_close_select_by_c0();
			if(cnt==0)
			{
				writelog(LOG_ERR,"DB_t_tradecode_shop_fetch_select_by_c0 error errorcode=[%d]",ret);
				return E_SHP_ID_NOT_EXIST;
			}
			break;
		}
		cnt++;
		shpid = tradeshop.shop_id;
	}
	
	
	//�����̻�ID��ѯ�õ��̻���Ϣ
	ret=DB_t_cif_shop_read_by_shop_id(shpid, &shop);
	if(ret)
	{
		writelog(LOG_ERR,"read tablet_cif_shop  shpid[%d]",shpid);
		if(DB_NOTFOUND==ret)
		{
			return E_SHP_ID_NOT_EXIST;
		}
		else
			return E_DB_CARD_R;
	}
	//���ݿͻ��ź��̻����˺����Ͳ�ѯ�˺ű��õ��˺�
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(shop.cut_id,ACCTYPE_SHOPMAIN,&account);
	if(ret)
	{
		writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]cutid[%d]",ret,shop.cut_id);
		if(DB_NOTFOUND==ret)
			return  E_SHOP_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	strcpy(szActno,account.account_id);
	memset(&account,0,sizeof(account));
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(in_pack->lvol0,0,&account);
	if(ret)
	{
		writelog(LOG_ERR,"read t_aif_account err[%d]cardid[%d]",ret,in_pack->lvol0);
		if(DB_NOTFOUND==ret)
		{
			return E_ACTNO_NOT_EXIST;
		}
		else
			return E_DB_ACCOUNT_R;
	}

	des2src(IA->sArrInActno[0],account.account_id);					//�跽�˺�
	des2src(IA->sArrInActno[1],szActno);							//�����˺�


	return 0;
	
}

//������ʽ��ֵ����
static int trans_request(ST_PACK *in_pack,char ext_msg[256]){
	int ret = 0;	
	char host[16]="";		//�Է�������ip
	char portchar[10]="";
	short port=0;				//�Է�������port
	char rcvdata[package_len+1]="";		//���նԷ��Ĵ�������
	char senddata[package_len+1]="";	//���ܺ�Ĵ�������
	char tempdate[package_len+1-200]="";
	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	ext_phone_trans_t	 PhoneTrans;

	memset(tempdate,0,sizeof tempdate);
	CTcpSocket tcpsocket ;

	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ret=GetParameter(2104, host);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return E_DB_TRADESERIALERROR_R;
	}
	ret=GetParameter(2105, portchar);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return E_DB_TRADESERIALERROR_R;
	}
	ret=GetParameter(2106, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2107, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);
	
	ret = packege_send_data(in_pack,2,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}

	memcpy(tempdate,senddata,package_len-200);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_LVOL1,F_SCUST_AUTH,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	sPack.head.RequestType = 250001;
	des2src(sPack.pack.ssectypes,tempdate);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;
	sPack.pack.lvol1=1;
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	return 0;

}


/**************************************************
	�ն�����ģ��
*******************************************************/
static int pre_check_term_trade(ST_PACK *in_pack,transfer_control_t *trans_ctl)
{
	T_t_pif_device tDevice;
	char curr_date[9];
	char curr_time[7];
	int shop_id;
	int ret;
	if(in_pack->lvol4 <= 0)
		return E_INPUT_DATA_INVAILD;

	trans_ctl->check_user_pwd = 0;
	
	memset(&tDevice,0,sizeof tDevice);
	tDevice.device_id = in_pack->lvol4;

	getsysdate(curr_date);
	getsystime(curr_time);
	if( strcmp(in_pack->sdate0,curr_date) != 0)
	{
		return E_INPUT_DATE;
	}
	ret = get_shpId_by_devId_date_time(&shop_id,tDevice.device_id,in_pack->sdate0
		,curr_time,0);
	if(ret)
	{
		writelog(LOG_ERR,"find shop id error dev [%d]",tDevice.device_id);
		return ret;
	}
	// �����̻���
	in_pack->lvol12 = shop_id;
	ret = DB_t_pif_device_read_lock_by_cur_and_device_id(in_pack->lvol4,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DEVICE_N;
		else
			return E_DB_DEVICE_R;
	}
	ret = 0;
	if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		ret = E_DEVICE_NOT_EXIST;
	}
	else if(tDevice.lasttraserno > in_pack->lvol5)
	{
		writelog(LOG_ERR,"�ն���ˮ�Ų���,devid[%d]input serial[%d]"
			,in_pack->lvol4,in_pack->lvol5);
		ret = E_SERIALNO_NOT_EXIST;
	}
	 DB_t_pif_device_free_lock_cur();
	 return ret;
}

static int search_account_from_term_id(ST_PACK *in_pack,int trade_code,InAcc *IA)
{
	T_t_pif_device tDevice;
	T_t_aif_account tAccount;
	T_t_cif_shop tShop;
	int shop_id;
	char curr_time[7] = "";
	int ret;
	if(in_pack->lvol4 <= 0)
		return E_INPUT_DATA_INVAILD;

	memset(&tDevice,0,sizeof tDevice);
	
	ret = DB_t_pif_device_read_by_device_id(in_pack->lvol4,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DEVICE_N;
		else
			return E_DB_DEVICE_R;
	}
	getsystime(curr_time);
	ret = get_shpId_by_devId_date_time(&shop_id,tDevice.device_id,in_pack->sdate0
		,curr_time,0);
	if(ret)
	{
		writelog(LOG_ERR,"cannot find shop ,dev[%d][%s - %s]"
			,tDevice.device_id,in_pack->sdate0,curr_time);
		return ret;
	}
	// �����̻���
	memset(&tShop,0,sizeof tShop);
	ret = DB_t_cif_shop_read_by_shop_id(shop_id,&tShop);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SHOP_N;
		return E_DB_SHOP_R;
	}
	memset(&tAccount,0,sizeof tAccount);
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(tShop.cut_id,ACCTYPE_SHOPMAIN,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]cutid[%d]",ret,tShop.cut_id);
		if(DB_NOTFOUND==ret)
			return  E_SHOP_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	des2src(IA->sArrInActno[1],tAccount.account_id);
	writelog(LOG_ERR,"shop account id[%s]",tAccount.account_id);
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(in_pack->lvol0,0,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"read t_aif_account err[%d]cardid[%d]",ret,in_pack->lvol0);
		if(DB_NOTFOUND==ret)
		{
			return E_ACTNO_NOT_EXIST;
		}
		else
			return E_DB_ACCOUNT_R;
	}
	des2src(IA->sArrInActno[0],tAccount.account_id);
	return 0;
	
}

static int do_term_trade(ST_PACK *in_pack,char ext_msg[256])
{
	T_t_pif_device tDevice;
	int ret;
	if(in_pack->lvol4 <= 0)
		return E_INPUT_DATA_INVAILD;
		
	ret = DB_t_pif_device_read_lock_by_cur_and_device_id(in_pack->lvol4,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DEVICE_N;
		else
			return E_DB_DEVICE_R;
	}
	
	ret = 0;
	if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		ret = E_DEVICE_NOT_EXIST;
	}
	else if(tDevice.lasttraserno > in_pack->lvol5)
	{
		writelog(LOG_ERR,"�ж���ˮ�Ų���,devid[%d]input serial[%d]"
			,in_pack->lvol4,in_pack->lvol5);
		ret = E_SERIALNO_NOT_EXIST;
	}
	else if(!ret)
	{
		tDevice.lasttraserno = in_pack->lvol5+1;
		ret = DB_t_pif_device_update_lock_by_cur(&tDevice);
		if(ret)
		{
			writelog(LOG_DEBUG,"�����ж���ˮ��ʧ��devid[%d]",in_pack->lvol4);
			return E_DB_DEVICE_N;
		}
	}
	 DB_t_pif_device_free_lock_cur();
	 return 0;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//ϵͳģ������
 int tend_to_enter_account(ST_PACK *in_pack,InAcc *IA,int trade_code,T_t_tif_tradeserial *tradeserial){
	int ret = 0;
	int i=0;
	int	card_id = 0;
	char	Operator[33+1] = "";
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double dUniqno = 0;
	char sMsg[256]="";
	double p33_amount =0;

	T_t_cif_customer 	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;
	T_t_pif_card	tCard;


	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));

	card_id=in_pack->lvol0;
	device_id=in_pack->lvol4;
	maindevice_id=in_pack->lvol3;
	
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
		return ret;
	}
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}


	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}

	
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			ret=E_ACTNO_NOT_EXIST;
		else
			ret=E_DB_ACCOUNT_R;
		return ret;
	}
	
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}
	//�õ��շ����
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
				return E_DB_SPEFEE_R;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//���¿ͻ�����շ�����ֶ�
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				ret= E_CUSTOMER_NOT_EXIST;
			else
				ret= E_DB_CUSTOMER_U;
			return ret;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	//���web�����ļ�¼�ͼ�¼Ϊweb����Ա����������ǰ̨�Ĳ���Ա����Ȧ���
	if(strlen(in_pack->semp)!=0)
	{
		des2src(Operator,in_pack->semp);
	}
	else if(strlen(in_pack->scust_no)!=0)
	{
		des2src(Operator,in_pack->scust_no);											//����Ա��			
	}
	else des2src(Operator,"web");
	//�ɼ��豸��ʶ
	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return ret;
	}
	
	strncpy(tradeserial->operate_date,sysdate,sizeof(sysdate)-1);				//��������
	strncpy(tradeserial->operate_time,systime,sizeof(systime)-1);
	des2src(tradeserial->collect_date,tradeserial->operate_date);								//�ɼ�����
	des2src(tradeserial->collect_time,tradeserial->operate_time);								//�ɼ�ʱ��
	des2src(tradeserial->enteract_date,logicdate);							//��������
	des2src(tradeserial->enteract_time,tradeserial->operate_time);							//����ʱ��
	tradeserial->serial_no = D2I(dUniqno);									//��ˮ��
	tradeserial->serial_type = trade_code;						//��ˮ����
	tradeserial->purse_id = PURSE_NO_ONE;					//Ǯ����
	tradeserial->serial_state = SERISTAT_NODEBT;								//��ˮ״̬
	tradeserial->maindevice_id = maindevice_id;						//�ϴ�����վ��ʶ
	tradeserial->other_seri_no = in_pack->lvol5;		// �ϴ�����ˮ��
	tradeserial->device_id = device_id;										//�ɼ��豸��ʶ
	tradeserial->card_id = card_id;										//���׿���
	tradeserial->customer_id=tCard.cosumer_id;								//�ͻ���
	des2src(tradeserial->oper_code,Operator);
	tradeserial->trade_count=in_pack->lvol1+1;		//���״���
	tradeserial->in_balance=in_pack->damt0;			//�뿨ֵ
	tradeserial->trade_fee=in_pack->damt1;				//���׽��
	strncpy(tradeserial->reserve_2,in_pack->vsmess,sizeof(tradeserial->reserve_2)-1);
	des2src(tradeserial->b_act_id,in_pack->sphone);

	IA->iCardNo=tCard.card_id;
	IA->iFeeType=tCustomer.fee_type;
	IA->dArrInAmt[0]=tradeserial->trade_fee;
	IA->iMainDevId=tradeserial->maindevice_id;				//����վ��ʶ
	IA->iDevId=tradeserial->device_id;						//�豸ID
	IA->iSerialNo=tradeserial->serial_no;					//��ˮ��
	IA->iTradeNo=tradeserial->serial_type;					//������
	strcpy(IA->sTxDate,tradeserial->operate_date);			//��������
	strcpy(IA->sTxTime,tradeserial->operate_time);			//����ʱ��
	strcpy(IA->sTxCollectDate,tradeserial->collect_date);		//�ɼ�����
	strcpy(IA->sTxCollectTime,tradeserial->collect_time);		//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,tradeserial->enteract_date);		//��������
	strcpy(IA->sTxAccTime,tradeserial->enteract_time);		//����ʱ��
	strcpy(IA->sMdeOper,tradeserial->oper_code);			//����Ա
	strcpy(IA->sChkOper,tradeserial->reserve_1);			//���˲���Ա

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//��������
	IA->iTxCnt=tradeserial->trade_count;					//���״���
	IA->dInCardBala=tradeserial->in_balance;				//�뿨ֵ
	IA->dOutCardBala=-1;							//����ֵ
	
		p33_amount = in_pack->damt1;
		IA->iArrInFeeSwitch[1]=0;
		if(amtcmp(p33_amount,0)<0)	//���Ϊ��������ʾ�ۿ�
		{
			IA->dArrInAmt[0]=-p33_amount;					//������
			IA->iArrInFeeSwitch[7]=0;
		}
		else							//���Ϊ��������ʶ����
		{
			IA->dArrInAmt[0]=p33_amount;
			IA->iArrInFeeSwitch[7]=1;
		}

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	tradeserial->out_balance=IA->dOutCardBala;			//����ֵ
	if(amtcmp(tradeserial->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}

	for(i=1;i<=IA->iOutTxTypeCnt;i++)
	{
		switch(IA->iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial->deposit_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial->boardfee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tradeserial->in_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tradeserial->cost_fee=IA->dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA->dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA->sArrOutTxName[i],IA->dArrOutAmt[i]);
		}
	}

	ret = db_rollback();
	if(ret)
	{
		writelog(LOG_ERR,"db_roll_back error,errcode=[%d]",ret);
		return E_DB_ROLLBACK;
	}
	return 0;
}

 int record_serial(ST_PACK *in_pack,T_t_tif_tradeserial *tradeserial,ST_PACK *out_pack){
	int ret =0;
	double dUniqno = 0;
	char sMsg[256]="";

	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return ret;
	}						
	tradeserial->serial_no = D2I(dUniqno);			//��ˮ��
	out_pack->damt1=tradeserial->trade_fee;		//��ֵ���
	out_pack->damt0=tradeserial->out_balance;	//����ֵ
	out_pack->lvol0=tradeserial->serial_no;//��ˮ��
	
	sprintf(sMsg,"����ǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",tradeserial->in_balance,tradeserial->out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);

	ret = DB_t_tif_tradeserial_add(tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_DB_COMMIT;
	}
	return 0;
	

}	


static int record_small_serial(ST_PACK *in_pack,T_t_tif_tradeserial *tradeserial,ST_PACK *out_pack){
	int ret =0;
	double dUniqno = 0;
	 T_t_tif_tradeserial  tPacketSerial;

	//�����ֵ��ˮ
	memset(&tPacketSerial, 0, sizeof tPacketSerial);
	memcpy(&tPacketSerial, tradeserial, sizeof tPacketSerial);
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		return ret;
	}
	tPacketSerial.serial_no = D2I(dUniqno);
	tPacketSerial.serial_state = SERISTAT_NONEEDDEBT;
	tPacketSerial.serial_type = TXCODE_SAVING_SMALL_PACKET;
	tPacketSerial.purse_id = 33;//33����Ǯ��
	tPacketSerial.in_balance = in_pack->damt2;
	tPacketSerial.trade_fee = in_pack->damt1;
	tPacketSerial.out_balance = tPacketSerial.in_balance + tPacketSerial.trade_fee;

	ret = DB_t_tif_tradeserial_add(&tPacketSerial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}

	out_pack->damt2=tPacketSerial.out_balance;
	out_pack->lvol1= D2I(dUniqno);			//��ˮ��

	return 0;
	

}	






//ϵͳ��ʽ����
 int enter_account(ST_PACK *in_pack,InAcc *IA,ST_PACK *out_pack){
	int ret = 0;
	int i=0;
	int	card_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char sMsg[256]="";
	double p33_amount=0;
	
	T_t_tif_tradeserial tradeserial;
	T_t_cif_customer 	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;
	T_t_pif_card	tCard;


	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	card_id=in_pack->lvol0;
	
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
		return ret;
	}
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}


	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}

	
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			ret=E_ACTNO_NOT_EXIST;
		else
			ret=E_DB_ACCOUNT_R;
		return ret;
	}
	
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}
	//�õ��շ����
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
				return E_DB_SPEFEE_R;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//���¿ͻ�����շ�����ֶ�
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				ret= E_CUSTOMER_NOT_EXIST;
			else
				ret= E_DB_CUSTOMER_U;
			return ret;
		}
	}
	DB_t_cif_customer_free_lock_cur();



	
	ret = DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(in_pack->lvol6,&tradeserial);
	if(ret)
	{
		if(DB_NOTFOUND == ret){
			ret = E_DB_TRADESERIAL_N;
		}else{
			ret = E_DB_TRADESERIAL_R;
		}
		
	}
	

	IA->iCardNo=tCard.card_id;
	IA->iFeeType=tCustomer.fee_type;
	IA->dArrInAmt[0]=tradeserial.trade_fee;
	IA->iMainDevId=tradeserial.maindevice_id;				//����վ��ʶ
	IA->iDevId=tradeserial.device_id;						//�豸ID
	IA->iSerialNo=tradeserial.serial_no;					//��ˮ��
	IA->iTradeNo=tradeserial.serial_type;					//������
	strcpy(IA->sTxDate,tradeserial.operate_date);			//��������
	strcpy(IA->sTxTime,tradeserial.operate_time);			//����ʱ��
	strcpy(IA->sTxCollectDate,tradeserial.collect_date);		//�ɼ�����
	strcpy(IA->sTxCollectTime,tradeserial.collect_time);		//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,tradeserial.enteract_date);		//��������
	strcpy(IA->sTxAccTime,tradeserial.enteract_time);		//����ʱ��
	strcpy(IA->sMdeOper,tradeserial.oper_code);			//����Ա
	strcpy(IA->sChkOper,tradeserial.reserve_1);			//���˲���Ա

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//��������
	IA->iTxCnt=tradeserial.trade_count;					//���״���
	IA->dInCardBala=tradeserial.in_balance;				//�뿨ֵ
	IA->dOutCardBala=-1;							//����ֵ

	p33_amount = tradeserial.trade_fee;
	IA->iArrInFeeSwitch[1]=0;
	if(amtcmp(p33_amount,0)<0)	//���Ϊ��������ʾ�ۿ�
	{
		IA->dArrInAmt[0]=-p33_amount;					//������
		IA->iArrInFeeSwitch[7]=0;
	}
	else							//���Ϊ��������ʶ����
	{
		IA->dArrInAmt[0]=p33_amount;
		IA->iArrInFeeSwitch[7]=1;
	}

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	tradeserial.out_balance=IA->dOutCardBala;			//����ֵ
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}

	for(i=1;i<=IA->iOutTxTypeCnt;i++)
	{
		switch(IA->iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.deposit_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial.boardfee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tradeserial.in_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tradeserial.cost_fee=IA->dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA->dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA->sArrOutTxName[i],IA->dArrOutAmt[i]);
		}
	}
	tradeserial.serial_state=SERISTAT_DEBT;
	ret = DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"db update t_tif_tradeserial error,errcode=[%d]",ret);
		return E_DB_TRADESERIAL_U;
	}

	DB_t_tif_tradeserial_free_lock_cur();
	
	out_pack->damt0=tradeserial.out_balance;	//����ֵ
	out_pack->damt1=tradeserial.trade_fee;		//���׽��	
	out_pack->lvol0 = tradeserial.serial_no;		//��ˮ��	
	sprintf(sMsg,"����ǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	
	return 0;
}

static int deal_water_ctl_out_pack(ST_PACK *in_pack,ST_PACK *out_pack){
	int ret = 0;	
	char price1[16]="";	
	char price2[16]="";
	char price3[16]="";
	double d_price1 = 0;
	double d_price2 = 0;
	double d_price3 = 0;
	T_t_tif_tradeserial  tPacketSerial;
	memset(&tPacketSerial, 0, sizeof tPacketSerial);
	
	ret=GetParameter(2201, price1);	
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2202, price2);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2203, price3);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	d_price1 = atof(price1);
	d_price2 = atof(price2);
	d_price3 = atof(price3);

	out_pack->damt10 = D4U5(d_price1/600,4);
	out_pack->damt11 = D4U5(d_price2/600,4);
	out_pack->damt12 = D4U5(d_price3/600,4);
 	ret = DB_t_tif_tradeserial_read_by_serial_no(in_pack->lvol7, &tPacketSerial);  //������ˮ��
	if (ret)
	{
	    writelog(LOG_DEBUG,"����Ų�����������ˮ��[%d]",in_pack->lvol7);
	    if (DB_NOTFOUND == ret)
	    {
	        ret = E_DB_TRADESERIAL_N;
	    }
	    else
	    {
	        ret = E_DB_TRADESERIAL_R;
	    }
	    return ret;
	}
	out_pack->damt2=tPacketSerial.out_balance;
	out_pack->lvol1=tPacketSerial.serial_no;
	return 0;
	
}


static const ext_consumer_request_t  g_transfer_process[] = {
	{PRE_CHEDK_ENTER_ACCOUNT_MOBILE_TRANS, TXCODE_MOBILE_TRANS,check_cellphone,get_third_part_account,trans_request,NULL,NULL},
	{PRE_ENTER_ACCOUNT_WATER_TRANS,TXCODE_CONSUME, NULL,get_third_part_account,NULL,deal_water_ctl_out_pack,record_small_serial},
	{TERMINAL_TRADE,TXCODE_COSUME_LOG,pre_check_term_trade,search_account_from_term_id,do_term_trade,NULL,NULL},
	{-1,-1,NULL,NULL,NULL,NULL,NULL}
};


int ext_consumer_find_trade(int request_type,ext_consumer_request_t *transfer)
{
	int i = 0;
	while(g_transfer_process[i].request_type != -1)
	{
		if(g_transfer_process[i].request_type == request_type)
		{
			*transfer = g_transfer_process[i];;
			return 0;
		}
		i++;
	}
	return E_TRANS_FUNC_NONSUPPORT;
}


