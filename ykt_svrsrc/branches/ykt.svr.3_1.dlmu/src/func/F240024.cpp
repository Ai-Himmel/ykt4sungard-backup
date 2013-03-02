/* --------------------------------------------
 * 程序名称: F240024.cpp
 * 创建日期: 2010-08-17
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存查询银行卡余额
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


	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包
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
		strcpy(szMsg,"您的校园卡号和银行卡号未绑定");
		return ret;
	}
	/*
	ret=DB_t_card_read_by_custid_and_status(custid, "1", &card);
	if(ret)
	{
		strcpy(szMsg,"校园卡已经注销");
		return E_DB_CARD_N;
	}
	*/
	//校验绑定关系
	ret = DB_t_bankcard_read_by_custid(custid, &bankcard);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_bankcard_read_by_custid err,errcode=[%d]",ret);
		if(DB_NOTFOUND==ret)
		{
			strcpy(szMsg,"学工号和银行卡号未绑定");
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
		strcpy(szMsg,"学工号和银行卡号没绑定");

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
	drtp_branch = cfgbank.bccdrtpno;								// drtp 编号
	base_funcno = cfgbank.bccfuncno;							// 前置主功能号
	bcc_timeout = cfgbank.bcctimeout;								// 前置超时时间

	sPack.pack.lcert_code = 240100;								// 交易码
	des2src(sPack.pack.scust_limit2,cfgbank.bankip);					// 银行ip
	sPack.pack.lvol0 = cfgbank.bankport;							// 银行端口
	sPack.pack.lvol1 = cfgbank.banktimeout;					// 银行超时时间

	
	GetNewRefno(sPack.pack.sholder_ac_no);				// 一卡通交易参考号
	db_commit();
	des2src(sPack.pack.sdate0,getsysdate(NULL));					// 交易日期
	des2src(sPack.pack.scust_limit,customer.custname);				// 姓名
	des2src(sPack.pack.scust_auth2,customer.idno);					// 身份证号
	des2src(sPack.pack.scust_auth,rPack->scust_auth);				// 银行卡号
	des2src(sPack.pack.sphone3,rPack->sphone3);				//银行卡密码，ansi加密处理过
	des2src(sPack.pack.vsvarstr0, rPack->vsvarstr0);				//二磁道数据
	des2src(sPack.pack.vsvarstr1, rPack->vsvarstr1);				//三磁道数据
	des2src(sPack.pack.sorder2,device.devphyid);					//设备物理ID
	
	ret = ExtCall(0, drtp_branch, base_funcno, 0, bcc_timeout, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		writelog(LOG_ERR,"extcall 2401 ret[%d],retcode[%d] timeout[%d] ",ret,aPack.head.retCode,bcc_timeout);
		if (ret < 0)				// 通讯错误，要冲正的
		{
			writelog(LOG_ERR,"调用后台业务失败，业务终止");
			return E_BCC_NETWORK;
		}
		else						// 收到前置返回的错误
		{
			writelog(LOG_ERR,"%s",aPack.pack.vsmess);
			strcpy(szMsg,aPack.pack.vsmess);
			return E_COMMON_ERR;
		}
	}
	if(aPack.pack.lvol1 != 1)		// 前置解包错误
	{	
		writelog(LOG_ERR,"接收银行数据错误");
		return E_BCC_NETWORK;
	}

	out_pack->damt0=aPack.pack.damt0;
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;

}



