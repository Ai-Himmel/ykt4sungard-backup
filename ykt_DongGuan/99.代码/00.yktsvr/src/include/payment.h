#ifndef _PAYMENT_H_
#define _PAYMENT_H_

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include <list>
#include "errdef.h" 
#include "pubdb.h"
#include "busqc.h"
#include "dbfunc.h"
#include "pubfunc.h"
#include "acctrans.h"
#include "cpack.h"
#include "svrlink.h"

#define DECLARE_PAYMENT(n,p) static int n##reg_;
#define REGISTER_PAYMENT(n) int n::n##reg_ = register_payment(new n);

enum PAYEEACCTYPE {PAT_INPUT=0,PAT_CARDNO,PAT_CUSTID,PAT_STUEMPNO};
class CPaymentBase
{
	DECLARE_PAYMENT(CPaymentBase,NULL)
private:
	int paycode_;
	char refno_[15];
	char mac_[9];
protected:
	T_t_shop shop_;
	T_t_transdtl dtl_;
	T_t_card card_;
	T_t_account account_;
    int is_push_module_;
public:	
	int pushflag_;
	T_t_cfgpayment payment_;
	T_t_paypara	   paypara_;
	CPaymentBase(int paycode):paycode_(paycode),is_push_module_(0)
	{		
		memset(&payment_,0,sizeof(payment_));
		memset(&shop_,0,sizeof(shop_));
		memset(&dtl_,0,sizeof(dtl_));
		memset(&card_,0,sizeof(card_));
		memset(&account_,0,sizeof(account_));
		memset(refno_,0,sizeof(refno_));
		memset(mac_,0,sizeof(mac_));
	}
	CPaymentBase():paycode_(0)
	{
	}
	virtual ~CPaymentBase()
	{}
	int tend_acc(ST_PACK *rPack,ST_PACK *out_pack);
	int acc(ST_PACK *rPack,ST_PACK *out_pack,T_t_transdtl **transdtl);
	int get_refno();
	virtual int init(TRUSERID *handle,ST_CPACK *aPack,ST_PACK *in_pack);
	virtual int qry_acc(TRUSERID* handle,ST_PACK *rPack,ST_PACK *out_pack)
	{
		return -1;
	}
	virtual int pre_transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack)
	{
		return -1;
	}
	virtual int transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack)
	{
		return -1;
	}
	virtual int transfer_reverse(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack)
	{
		return -1;
	}
	virtual int fini(int result,ST_PACK *in_pack);
	const int paycode() const { return paycode_; }
    int is_push_module() const { return is_push_module_; }
    void set_push_module(int m) { is_push_module_ = m; }
	// static member
public:
	typedef std::list<CPaymentBase*> PAYMENT_LIST;
	static std::list<CPaymentBase*> s_payments_;
	static CPaymentBase* find_payment(int paycode);
};
// 代收费支付交易
#define PAYMENT_NORMAL 240998
class CNormalPayTrans : public CPaymentBase
{
	DECLARE_PAYMENT(CNormalPayTrans,CPaymentBase)
private:
	int req_paycode_;
public:
	CNormalPayTrans():CPaymentBase(PAYMENT_NORMAL)
	{}
	
	int PackData(ST_PACK *rPack,ST_CPACK& sPack);
	virtual int pre_transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	virtual int transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	virtual int transfer_reverse();
	virtual int qry_acc(TRUSERID* handle,ST_PACK *rPack,ST_PACK *out_pack);
	virtual int init(TRUSERID *handle,ST_CPACK *aPack,ST_PACK *in_pack);
	virtual int fini(int result,ST_PACK *in_pack);
};
// 测试转账模块
class CTestTrans : public CPaymentBase
{
	DECLARE_PAYMENT(CTestTrans,CPaymentBase)
public:
	CTestTrans():CPaymentBase(240999)
	{
	}
	virtual int pre_transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	virtual int transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
};

// 广州大学城手机转账
class CGDMobileTrans : public CPaymentBase
{
	// declare payment
public:
	CGDMobileTrans():CPaymentBase(240200)
	{
	}
	virtual int pre_transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	virtual int transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);

	DECLARE_PAYMENT(CGDMobileTrans,CPaymentBase)
private:
	int package_send_data(ST_PACK *rPack,int flag,char *send_data);
	static const int package_len=327;
	static const int timeout = 10;
};

// 广州大学城水控转账
class CGDWaterTrans : public CPaymentBase
{
public:
	CGDWaterTrans():CPaymentBase(240201)
	{
	}
	virtual int pre_transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	virtual int transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);

	DECLARE_PAYMENT(CGDWaterTrans,CPaymentBase)
};

// 广州大学城空中充值接口
class CGDCTPayment : public CPaymentBase
{
public:
    CGDCTPayment():CPaymentBase(3062)
    {set_push_module(1); }
    int PackData(ST_PACK *rPack,ST_CPACK& sPack);
    virtual int pre_transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	virtual int transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);

	DECLARE_PAYMENT(CGDCTPayment,CPaymentBase)
};

/*
// 第三方统一支付交易
class CPayTrans : public CPaymentBase
{
	// declare payment
public:
	
	CPayTrans(int paycode):CPaymentBase(paycode)
	{
	}
	virtual int qry_acc(TRUSERID* handle,ST_PACK *rPack,ST_PACK *out_pack);
	virtual int pre_transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	
	virtual int transfer(TRUSERID* handle,ST_PACK *in_pack,ST_PACK *out_pack);
	//交易冲正
	virtual int transfer_reverse();

//	DECLARE_PAYMENT(CPayTrans,CPaymentBase)
private:
};
*/
#endif // _PAYMENT_ 


