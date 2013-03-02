/* --------------------------------------------
 * ��������: F240024.cpp
 * ��������: 2010-08-17
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ���ѯ���п����
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
#include "acctrans.h"
#include "busqc.h"

int F240024(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int request_type = 2401;
	int drtp_branch  = 0;
	int base_funcno = 0;
	int bcc_timeout = 0;
	char bankcode[3] = "";

	ST_CPACK bPack;
	ST_PACK *out_pack = &(bPack.pack);
	ResetNormalCPack(&bPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,0);


	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�
	T_t_card card;
	memset(&card,0x00,sizeof card);
	T_t_bankcard bankcard;
	memset(&bankcard,0,sizeof bankcard);
	T_t_device device;
	memset(&device,0x00,sizeof device);
	
	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = request_type;
	
	SetHeadCol(&sPack,F_LCERT_CODE,F_SCUST_AUTH,F_LVOL0,F_LVOL1,F_SDATE0,
		F_SHOLDER_AC_NO,F_SPHONE,F_SPHONE3,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SCUST_AUTH,F_SCUST_AUTH2,F_DAMT0,F_SBANK_PWD,
		F_VSVARSTR0,F_VSVARSTR1,F_SORDER2,0);      
	int custid=0;
	ret = GetCustIDByBankcardno(rPack->scust_auth,&custid);
	if(ret)
	{
		strcpy(szMsg,"����У԰���ź����п���δ��");
		return ret;
	}
	/*
	ret=DB_t_card_read_by_custid_and_status(custid, "1", &card);
	if(ret)
	{
		strcpy(szMsg,"У԰���Ѿ�ע��");
		return E_DB_CARD_N;
	}
	*/
	//У��󶨹�ϵ
	ret = DB_t_bankcard_read_by_custid(custid, &bankcard);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_bankcard_read_by_custid err,errcode=[%d]",ret);
		if(DB_NOTFOUND==ret)
		{
			strcpy(szMsg,"ѧ���ź����п���δ��");
			return E_DB_BANKCARD_N;
		}
		else
		{
			return E_DB_BANKCARD_R;
		}
	}

	ret = DB_t_bankcard_read_by_custid_and_bankcardno(custid,rPack->scust_auth, &bankcard);
	if(ret)
	{
		strcpy(szMsg,"ѧ���ź����п���û��");

		return E_DB_BANKCARD_R;
	}
	des2src(bankcode,bankcard.bankcode);
	T_t_cfgbank cfgbank;
	memset(&cfgbank,0,sizeof cfgbank);
	ret = DB_t_cfgbank_read_by_bankcode(bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}
	if(cfgbank.bcctimeout<10)
		cfgbank.bcctimeout=10;
	if(cfgbank.banktimeout>=cfgbank.bcctimeout)
		cfgbank.banktimeout= cfgbank.bcctimeout-2;
		
	if(strncmp(getsystime(NULL),cfgbank.bankstarttime,6) < 0
		|| strncmp(getsystime(NULL),cfgbank.bankendtime,6) > 0)
	{
		return E_OUT_BANKTIME;
	}

	T_t_customer customer;
	memset(&customer,0,sizeof customer);
	ret = DB_t_customer_read_by_custid(custid, &customer);
	if(ret)
	{
		return E_DB_CUSTOMER_R;
	}
	ret=DB_t_device_read_by_deviceid(rPack->lcert_code, &device);
	if(ret)
	{
		return E_DB_DEVICE_R;
	}
	drtp_branch = cfgbank.bccdrtpno;								// drtp ���
	base_funcno = cfgbank.bccfuncno;							// ǰ�������ܺ�
	bcc_timeout = cfgbank.bcctimeout;								// ǰ�ó�ʱʱ��

	sPack.pack.lcert_code = 240100;								// ������
	des2src(sPack.pack.scust_limit2,cfgbank.bankip);					// ����ip
	sPack.pack.lvol0 = cfgbank.bankport;							// ���ж˿�
	sPack.pack.lvol1 = cfgbank.banktimeout;					// ���г�ʱʱ��

	
	GetNewRefno(sPack.pack.sholder_ac_no);				// һ��ͨ���ײο���
	db_commit();
	des2src(sPack.pack.sdate0,getsysdate(NULL));					// ��������
	des2src(sPack.pack.scust_limit,customer.custname);				// ����
	des2src(sPack.pack.scust_auth2,customer.idno);					// ���֤��
	des2src(sPack.pack.scust_auth,rPack->scust_auth);				// ���п���
	des2src(sPack.pack.sphone3,rPack->sphone3);				//���п����룬ansi���ܴ����
	des2src(sPack.pack.vsvarstr0, rPack->vsvarstr0);				//���ŵ�����
	des2src(sPack.pack.vsvarstr1, rPack->vsvarstr1);				//���ŵ�����
	des2src(sPack.pack.sorder2,device.devphyid);					//�豸����ID
	
	ret = ExtCall(0, drtp_branch, base_funcno, 0, bcc_timeout, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		writelog(LOG_ERR,"extcall 2401 ret[%d],retcode[%d] timeout[%d] ",ret,aPack.head.retCode,bcc_timeout);
		if (ret < 0)				// ͨѶ����Ҫ������
		{
			writelog(LOG_ERR,"���ú�̨ҵ��ʧ�ܣ�ҵ����ֹ");
			return E_BCC_NETWORK;
		}
		else						// �յ�ǰ�÷��صĴ���
		{
			writelog(LOG_ERR,"%s",aPack.pack.vsmess);
			strcpy(szMsg,aPack.pack.vsmess);
			return E_COMMON_ERR;
		}
	}
	if(aPack.pack.lvol1 != 1)		// ǰ�ý������
	{	
		writelog(LOG_ERR,"�����������ݴ���");
		return E_BCC_NETWORK;
	}

	out_pack->damt0=aPack.pack.damt0;
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;

}



