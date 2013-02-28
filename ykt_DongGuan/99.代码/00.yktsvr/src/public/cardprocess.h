/* --------------------------------------------
 * 创建日期: 2008-06-15
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 检查卡状态模块
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#ifndef  __CARDPROCESS_H_
#define  __CARDPROCESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "bufunc.h"
#include "errdef.h"
#include "pubdef.h"
#include "esqlc.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include <iostream>
#include <sstream>
#include <set>
#include "dictionary.h"
#include "transfunc.h"
#include "checkcardstatus.h"

class CCardProcess
{
private:
	T_t_cardtype  _cardtype;	
	int _totalamt;
	int _otheramt;
	int _befcardbal;
	int _aftcardbal;	
	bool _outflag;
protected:
	TRANS _trans; 
	T_t_card  _card;
	T_t_dpsdtl  _dpsdtl;
	T_t_operdtl _operdtl;
	T_t_carddtl _carddtl;
	T_t_customer  _customer;
	T_t_operaccdtl _operaccdtl;
	int _errcode;
	bool lockflag;
	std::string _msg;
	virtual bool GetRefno();
	virtual bool buildOperdtl();
	virtual bool buildOperdtl_Oper();
	virtual bool buildOperdtl_Trans();
	virtual bool buildOperaccdtl();
	virtual bool buildCarddtl_Card();
	virtual bool buildCarddtl_Oper();
	virtual bool buildCarddtl_Pos();
	virtual bool buildCarddtl_Trans();
	virtual bool buildCarddtl();
	virtual bool buildDpsdtl();
	virtual bool buildDpsdtl_Card();
	virtual bool buildDpsdtl_Oper();
	virtual bool buildDpsdtl_Pos();
	virtual bool buildDpsdtl_Trans();
	void SetAmtOutflag(bool val=true){ _outflag=val;};
	bool AddOperdtl();
	bool AddOperaccdtl();
	bool AddDpsdtl();
	bool AddCarddtl();
public:
	CCardProcess();
	void SetTotalamt(int amount)
	{
		_totalamt=amount;
	}
	int  GetTotalamt()
	{
		return _totalamt;
	}
	void SetBefcardbal(int befcardbal)
	{
		_befcardbal  = befcardbal;
		_aftcardbal  = _befcardbal;
	}
	void SetAftcardbal(int aftcardbal)
	{
		_aftcardbal  = aftcardbal;
	}
	int  AftCardBalInc(int amount)
	{
		if(amount<0)
			return -1;
		_aftcardbal+=amount;
		return _aftcardbal;
	}
	int AftCardBalDec(int amount)
	{
		if(amount<0)
			return -1;
		_aftcardbal-=amount;
		return _aftcardbal;
	}	
	int  GetBefcardbal()
	{
		return _befcardbal;
	}
	int  GetAftcardbal()
	{
		return _aftcardbal;
	}
	void SetObjCard(const T_t_card& card);
	TRANS& GetTrans();
	virtual void SetTrans(const TRANS& trans);
	virtual ~CCardProcess();
	virtual bool Execute()
	{
		return true;
	};
	//执行前检查
	virtual bool ExecBefChk()
	{
		return true;
	};
	//执行后检查
	virtual bool ExecAftChk()
	{
		return true;
	};
	//保存前检查
	virtual bool SaveBefChk()
	{
		return true;
	};
	virtual bool SaveExecResult()
	{
		return true;
	}
	virtual bool CalcBalance(int amount)
	{
		return true;
	};
	virtual bool buildOutput()
	{
		int ret = GetCustBaseInfo(_card.custid, _customer.custname, _customer.mobile);
		if(ret)
		{
			_errcode = ret;
			return false;
		}
		return true;
	}
	int GetErrCode();
	const char* GetErrMsg();
	const T_t_card& GetObjCard();
	virtual bool LockCard(int cardid=0);
	virtual bool ExecUpdCard();
	virtual bool AddDtl()
	{
		return true;
	};
	const T_t_cardtype& GetObjCardtype()
	{
		if(!_cardtype.cardtype)
		{
			int ret = DB_t_cardtype_read_by_cardtype(_card.cardtype, &_cardtype);
			if(ret)
			{
				if(DB_NOTFOUND == ret)
					_errcode = E_DB_CARDTYPE_N;
				else
					_errcode = E_DB_CARDTYPE_R;
				return _cardtype;
			}
		}
		return _cardtype;
	}
	const T_t_customer& GetObjCustomer()
	{
		return _customer;
	}
	const T_t_carddtl& GetObjCarddtl()
	{
		return _carddtl;
	}
	const T_t_operdtl& GetObjOperdtl()
	{
		return _operdtl;
	}
	const T_t_dpsdtl& GetObjDpsdtl()
	{
		return _dpsdtl;
	}
};
inline CCardProcess::CCardProcess()
{
	_outflag=false;
	lockflag = false;
	_errcode = 0;
	_msg = "";
	_trans.inputamt=0;
	_totalamt=0;
	_otheramt=0;
	_aftcardbal=0;
	memset(&_operaccdtl, 0, sizeof(_operaccdtl));
	memset(&_card, 0, sizeof(_card));
	memset(&_customer, 0, sizeof(_customer));
	memset(&_cardtype, 0, sizeof(_cardtype));
	memset(&_operdtl, 0, sizeof(_operdtl));
	memset(&_carddtl, 0, sizeof(_carddtl));
	memset(&_dpsdtl, 0, sizeof(_dpsdtl));
	memset(&_trans, 0, sizeof(_trans));
}
inline CCardProcess::~CCardProcess()
{
	if(lockflag)
		DB_t_card_free_lock_by_c0();
}
inline bool CCardProcess::GetRefno()
{
	CAccTrans& ats = CAccTrans::GetInst();
	int ret = ats.GetNewRefno(_trans.refno);
	if(ret)
	{
		_errcode = ret;
		return false;
	}
	return true;
}
inline void CCardProcess::SetObjCard(const T_t_card& card)
{
	memcpy(&_card, &card, sizeof(_card));
}
inline void CCardProcess::SetTrans(const TRANS& trans)
{
	memcpy(&_trans,&trans,sizeof(_trans));
	_befcardbal=trans.befcardbal;
	_aftcardbal=trans.befcardbal;
}
inline TRANS& CCardProcess::GetTrans()
{
	return _trans;
}
inline bool CCardProcess::LockCard(int cardid)
{
	int ret = 0;
	if(cardid<1)
	{
		cardid=_trans.cardid;
	}
	memset(&_card, 0, sizeof(T_t_card));
	ret = DB_t_card_read_lock_by_c0_and_cardid(cardid, &_card);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			_errcode = ERRIF_CARD_NOTEXIST;
		else
			_errcode = E_DB_CARD_R;
		return false;
	}
	lockflag = true;
	return true;
}
inline const char* CCardProcess::GetErrMsg()
{
	if(_msg.size())
	{
		return _msg.c_str();
	}
	else
	{
		if(_errcode)
		{
			_msg = CAccTrans::GetInst().GetErrMsgTip(_errcode);
		}
		else
		{
			_msg = "其他错误";
		}
	}
	return _msg.c_str();
}
inline int CCardProcess::GetErrCode()
{
	if(_msg.size())
	{
		ERRTIP(_msg.c_str());
	}
	if(!_errcode)
	{
		_errcode = E_COMMON_ERR;
	}
	return _errcode;
}
inline bool CCardProcess::ExecUpdCard()
{
	if(!lockflag)
	{
		_msg = "游标没有打开";
		return false;
	}
	lockflag = false;
	int ret = DB_t_card_update_lock_by_c0(&_card);
	if(ret)
	{
		_errcode = E_DB_CARD_U;
		return false;
	}
	return true;
}
inline const T_t_card& CCardProcess::GetObjCard()
{
	return _card;
}
inline bool CCardProcess::buildCarddtl_Card()
{
	_carddtl.cardid = _card.cardid;
	_carddtl.cardno = _card.cardno;
	des2src(_carddtl.cardasno, _card.cardasno);
	_carddtl.cardtype = _card.cardtype;
	_carddtl.balance = _card.balance;
	return true;
}
inline bool CCardProcess::buildCarddtl_Oper()
{
	_carddtl.branchid = _trans.branchid;
	_carddtl.operid = _trans.operid;
	return true;
}
inline bool CCardProcess::buildCarddtl_Pos()
{
	_carddtl.posno = _trans.posno;
	_carddtl.posseqno = _trans.termseqno;
	des2src(_carddtl.samno, _trans.samno);
	_carddtl.samseqno = _trans.samseqno;
	return true;
}
inline bool CCardProcess::buildCarddtl_Trans()
{
	CAccTrans& ats = CAccTrans::GetInst();
	_carddtl.accdate = ats.accdate;
	_carddtl.hostdate = ats.hostdate;
	_carddtl.hosttime = ats.hosttime;
	if(_trans.termdate)
	{
		_carddtl.termdate = _trans.termdate;
		_carddtl.termtime = _trans.termtime;
	}
	else
	{
		_carddtl.termdate = ats.hostdate;
		_carddtl.termtime = ats.hosttime;
	}
	_carddtl.transcode = _trans.transcode;
	_carddtl.transtype = _trans.transtype;
	_carddtl.dpscnt = _trans.dpscnt;
	_carddtl.paycnt = _trans.paycnt;
	_carddtl.merchid = _trans.merchid;
	_carddtl.status = TRANSTATUS_SUCC;
	strcpy(_carddtl.refno, _trans.refno);
	des2src(_carddtl.remark, _trans.remark);
	_carddtl.otheramt = _otheramt;
	_carddtl.amount = GetTotalamt();
	_carddtl.befcardbal = GetBefcardbal();
	_carddtl.aftcardbal = GetAftcardbal();
	return true;
}
inline bool CCardProcess::buildCarddtl()
{
	buildCarddtl_Card();
	buildCarddtl_Oper();
	buildCarddtl_Pos();
	buildCarddtl_Trans();
	return true;
}
//记录卡交易明细
inline bool CCardProcess::AddCarddtl()
{
	int ret = 0;
	buildCarddtl();
	ret = DB_t_carddtl_add(&_carddtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			_errcode = E_DB_CARDDTL_E;
		else
			_errcode = E_DB_CARDDTL_I;
		return false;
	}
	return true;
}
inline bool CCardProcess::buildOperdtl_Oper()
{
	_operdtl.branchid = _trans.branchid;
	_operdtl.operid = _trans.operid;
	return true;
}
inline bool CCardProcess::buildOperdtl_Trans()
{
	CAccTrans& ats = CAccTrans::GetInst();
	_operdtl.accdate = ats.accdate;
	if(_trans.termdate>0)
	{
		_operdtl.hostdate = _trans.termdate;
		_operdtl.hosttime = _trans.termtime;
	}
	else
	{
		_operdtl.hostdate = ats.hostdate;
		_operdtl.hosttime = ats.hosttime;
	}
	GetCpackDataString(ats.reqpack, _operdtl.reqdata);
	strcpy(_operdtl.refno, _trans.refno);
	_operdtl.operseqno = _trans.operseqno;
	_operdtl.transcode = _trans.transcode;
	des2src(_operdtl.transdesc, _trans.remark);
	_operdtl.termid = _trans.termid;
	des2src(_operdtl.samno, _trans.samno);
	_operdtl.termseqno = _trans.termseqno;
	_operdtl.cardno = _card.cardno;
	_operdtl.amount = GetTotalamt();
	_operdtl.otheramt = _otheramt;
	_operdtl.status = TRANSTATUS_SUCC;
	return true;
}

inline bool CCardProcess::buildOperdtl()
{
	buildOperdtl_Oper();
	buildOperdtl_Trans();
	return true;
}
//记录卡交易明细
inline bool CCardProcess::AddOperdtl()
{
	int ret = 0;
	buildOperdtl();
	if(_operdtl.operseqno < 1)
	{
		_operdtl.operseqno = atol(_operdtl.refno + 6);
	}
	ret = DB_t_operdtl_add(&_operdtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			_errcode = E_DB_OPERDTL_E;
		else
			_errcode = E_DB_OPERDTL_I;
		return false;
	}
	return true;
}
inline bool CCardProcess::buildOperaccdtl()
{
	CAccTrans& ats = CAccTrans::GetInst();
	_operaccdtl.accdate = ats.accdate;
	_operaccdtl.transdate= ats.hostdate;
	strcpy(_operaccdtl.refno, _trans.refno);
	_operaccdtl.transcode = _trans.transcode;
	des2src(_operaccdtl.remark, _trans.remark);
	if(_outflag)
		_operaccdtl.outamt= GetTotalamt();
	else
		_operaccdtl.inamt=GetTotalamt();
	_operaccdtl.branchid= _trans.branchid;
	_operaccdtl.operid = _trans.operid;
	return true;
}
inline bool CCardProcess::AddOperaccdtl()
{
	int ret = 0;
	buildOperaccdtl();
	if(_operaccdtl.operid<1)
	{
		_msg = "操作员ID不能为0";
		return false;
	}
	if((0==_operaccdtl.inamt)&&(0==_operaccdtl.outamt))
		return true;
	ret = DB_t_operaccdtl_add(&_operaccdtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			_errcode = E_DB_OPERDTL_E;
		else
			_errcode = E_DB_OPERDTL_I;
		return false;
	}
	return true;
}

inline bool CCardProcess::buildDpsdtl_Card()
{
	_dpsdtl.cardid = _card.cardid;
	_dpsdtl.cardno = _card.cardno;
	des2src(_dpsdtl.cardasno, _card.cardasno);
	_dpsdtl.cardtype = _card.cardtype;
	_dpsdtl.balance = _card.balance;
	return true;
}
inline bool CCardProcess::buildDpsdtl_Oper()
{
	_dpsdtl.branchid = _trans.branchid;
	_dpsdtl.operid = _trans.operid;
	return true;
}
inline bool CCardProcess::buildDpsdtl_Pos()
{
	_dpsdtl.termid = _trans.termid;
	_dpsdtl.termseqno = _trans.termseqno;
	des2src(_dpsdtl.samno, _trans.samno);
	return true;
}
inline bool CCardProcess::buildDpsdtl_Trans()
{
	CAccTrans& ats = CAccTrans::GetInst();
	_dpsdtl.accdate = ats.accdate;
	_dpsdtl.hostdate = ats.hostdate;
	_dpsdtl.hosttime = ats.hosttime;
	if(_trans.termdate)
	{
		_dpsdtl.termdate = _trans.termdate;
		_dpsdtl.termtime = _trans.termtime;
	}
	else
	{
		_carddtl.termdate = ats.hostdate;
		_carddtl.termtime = ats.hosttime;
	}
	_dpsdtl.transcode = _trans.transcode;
	_dpsdtl.transtype = _trans.transtype;
	_dpsdtl.dpscnt = _trans.dpscnt;
	_dpsdtl.paycnt = _trans.paycnt;
	_dpsdtl.merchid = _trans.merchid;
	_dpsdtl.status = TRANSTATUS_SUCC;
	strcpy(_dpsdtl.refno, _trans.refno);
	des2src(_dpsdtl.remark, _trans.remark);
	_dpsdtl.befcardbal = GetBefcardbal();
	_dpsdtl.aftcardbal = GetAftcardbal();
	_dpsdtl.amount= GetTotalamt();
	_dpsdtl.otheramt = _otheramt;
	return true;
}
inline bool CCardProcess::buildDpsdtl()
{
	buildDpsdtl_Card();
	buildDpsdtl_Oper();
	buildDpsdtl_Pos();
	buildDpsdtl_Trans();
	return true;
}
//记录卡交易明细
inline bool CCardProcess::AddDpsdtl()
{
	int ret = 0;
	buildDpsdtl();	
	if(_dpsdtl.termseqno < 1)
	{
		_dpsdtl.termseqno= atol(_dpsdtl.refno + 6);
	}
	ret = DB_t_dpsdtl_add(&_dpsdtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			_errcode = E_DB_CARDDTL_E;
		else
			_errcode = E_DB_CARDDTL_I;
		return false;
	}
	return true;
}

class CNotCheckCardStatus
{
public:
	CNotCheckCardStatus(T_t_card &tCard)
	{}
	bool OnlineTransCheck()
	{
		return true;
	}
};


/////////////////////////////////////////////////////////////////////////////


class CCardDeposit: public CCardProcess
{
public:
	virtual bool ExecBefChk();
	virtual bool ExecAftChk();
	virtual bool buildCarddtl_Pos();
	virtual bool CalcBalance(int amount);
	virtual bool buildOperdtl_Trans();
	virtual bool Execute();
	virtual bool SaveExecResult();
};

inline bool CCardDeposit::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.OnlineTransCheck())
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}
	const T_t_cardtype& ct = GetObjCardtype();
	if(!ct.cardtype)
		return false;
	if(_trans.inputamt < 0)
	{
		char szMsg[128];
		sprintf(szMsg, "充值金额%.2lf错误", _trans.inputamt / 100.0);
		_msg =szMsg;
		return false;
	}
	if(_trans.inputamt > ct.maxdpsamt)
	{
		char szMsg[128];
		sprintf(szMsg, "充值金额%.2lf超过最大限额%.2lf", _trans.inputamt / 100.0, ct.maxdpsamt / 100.0);
		_msg = szMsg;
		return false;
	}
	if(_trans.fundtype>0)
	{
		switch(_trans.fundtype)
		{
		case 1:
			_trans.transtype = TRANSTYPE_DPSCASH;
			_trans.transcode = TC_CARDDPSCASH;
			break;
		case 2:
			_trans.transtype = TRANSTYPE_DPSBANKCARD;
			_trans.transcode = TC_CARDDPSBANK;
			break;
		case 3:
			_trans.transtype = TRANSTYPE_DPSBILL;
			_trans.transcode = TC_CARDDPSBILL;
			break;
		default:
			_msg = "该充值方式不支持";
			return false;
		}
	}
	return true;
}
inline bool CCardDeposit::ExecAftChk()
{
	const T_t_cardtype& ct = GetObjCardtype();
	if(!ct.cardtype)
		return false;
	if(GetAftcardbal()> ct.maxcardbal)
	{
		_msg = "充值后卡余额超过最大余额";
		return false;
	}
	if(GetAftcardbal()<GetBefcardbal())
	{
		_msg = "充值后卡余额不能小于充值前卡余额";
		return false;
	}
	if(GetAftcardbal()<0)
	{
		_msg="卡余额不足";
		return false;
	}	
	return true;
}
inline bool CCardDeposit::Execute()
{
	SetTotalamt(_trans.inputamt);
	if(!CalcBalance(GetTotalamt()))
		return false;
	return true;
}
inline bool CCardDeposit::buildCarddtl_Pos()
{
	CCardProcess::buildCarddtl_Pos();
	if(_carddtl.posseqno<1)
		_carddtl.posseqno = atol(_trans.refno+6);
	return true;
}
inline bool CCardDeposit::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	if(!AddOperaccdtl())
	{
		return false;
	}
	if(!AddDpsdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
inline  bool CCardDeposit::CalcBalance(int amount)
{
	if(amount<=0)
	{
		_msg="充值金额必须为大于0";
		return false;
	}
	CAccTrans& ats = CAccTrans::GetInst();
	_card.cardbal = AftCardBalInc(amount);
	_card.balance += amount;
	_card.dpsamt += amount;
	_card.dpsnum++;
	_card.dpscnt = _trans.dpscnt;
	if(_trans.paycnt)
		_card.paycnt = _trans.paycnt;
	_card.termid = _trans.termid;
	_card.transdate = ats.hostdate;
	_card.transtime = ats.hosttime;
	strcpy(_card.updtime, ats.hostdatetime);
	return true;
}
inline  bool CCardDeposit::buildOperdtl_Trans()
{
	CCardProcess::buildOperdtl_Trans();
	return true;
}
///////////////////////////////////////////////////////////////////////////////
class CCardPayment: public CCardProcess
{
public:	
	virtual bool CalcBalance(int amount);
	virtual bool ExecBefChk();
	virtual bool Execute();
	virtual bool ExecAftChk();
	virtual bool SaveExecResult();
};
inline bool CCardPayment::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.OnlineTransCheck())
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}
	return true;
}
inline  bool CCardPayment::CalcBalance(int amount)
{
	if(amount<=0)
	{
		_msg="扣卡金额必须大于0";
		return false;
	}
	_card.cardbal = AftCardBalDec(amount);
	_card.balance -= amount;
	_card.payamt += amount;
	_card.paynum++;
	if(_trans.dpscnt)
		_card.dpscnt = _trans.dpscnt;
	_card.paycnt = _trans.paycnt;
	_card.termid = _trans.termid;
	CAccTrans& ats = CAccTrans::GetInst();
	_card.transdate = ats.hostdate;
	_card.transtime = ats.hosttime;
	strcpy(_card.updtime, ats.hostdatetime);
	return true;
}
inline bool CCardPayment::Execute()
{
	if(!CalcBalance(_trans.inputamt))
		return false;
	SetTotalamt(_trans.inputamt);
	return true;
}
inline bool CCardPayment::ExecAftChk()
{
	if(GetAftcardbal()>GetBefcardbal())
	{
		_msg  ="卡余额计算错误";
		return false;
	}
	if(GetAftcardbal()<0)
	{
		_msg="卡余额不足";
		return false;
	}
	return true;
}
inline bool CCardPayment::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	SetAmtOutflag();
	if(!AddOperaccdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
//充值回退
class CCardDpsCancel: public CCardPayment
{
public:
	virtual bool ExecBefChk();
	virtual bool Execute();
	virtual bool buildCarddtl_Pos();
	virtual bool SaveExecResult();
};
inline bool CCardDpsCancel::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.OnlineTransCheck())
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}
	if(_trans.inputamt>=0)
	{
		_msg="回退金额必须小于0";
		return false;
	}
	return true;
}
inline bool CCardDpsCancel::Execute()
{
	if(!CalcBalance(-_trans.inputamt))
		return false;
	SetTotalamt(_trans.inputamt);
	return true;
}
inline bool CCardDpsCancel::buildCarddtl_Pos()
{
	CCardProcess::buildCarddtl_Pos();
	if(_carddtl.posseqno<1)
		_carddtl.posseqno = atol(_trans.refno+6);
	return true;
}
inline  bool CCardDpsCancel::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	if(!AddDpsdtl())
	{
		return false;
	}
	if(!AddOperaccdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
//交易冲正
class CCardTransRev: public CCardProcess
{
private:
	T_t_operaccdtl _orgiOperAccdtl;
public:
	CCardTransRev();
	virtual bool ExecBefChk();
	void SetOrgiOperaccdtl(const T_t_operaccdtl& orgiOperAccdtl)
	{
		memcpy(&_orgiOperAccdtl,&orgiOperAccdtl,sizeof(T_t_operaccdtl));
	};
	virtual bool buildOperaccdtl();
	virtual  bool CalcBalance(int amount);
	virtual bool Execute();
	virtual bool SaveExecResult();
};
inline CCardTransRev::CCardTransRev():CCardProcess()
{
	memset(& _orgiOperAccdtl,0,sizeof(_orgiOperAccdtl));
}
inline bool CCardTransRev::ExecBefChk()
{
	if(_card.delflag)
	{
		_msg = "当前卡已销户";
		return false;
	}
	return true;
}
inline bool CCardTransRev::buildOperaccdtl()
{
	CCardProcess::buildOperaccdtl();
	_operaccdtl.branchid= _orgiOperAccdtl.branchid;
	_operaccdtl.operid = _orgiOperAccdtl.operid;
	_operaccdtl.transdate=_orgiOperAccdtl.transdate;
	_operaccdtl.transcode=_orgiOperAccdtl.transcode;
	_operaccdtl.inamt= -_orgiOperAccdtl.inamt;
	_operaccdtl.outamt = -_orgiOperAccdtl.outamt;
	return true;
}
inline  bool CCardTransRev::CalcBalance(int amount)
{
	if(0==amount)
	{
		_msg="冲正金额不能为0";
		return false;
	}
	_card.balance += amount;
	if(amount>0)
		_card.dpsamt += amount;
	else
		_card.payamt += (-amount);
	_card.termid = _trans.termid;
	CAccTrans& ats = CAccTrans::GetInst();
	strcpy(_card.updtime, ats.hostdatetime);
	return true;
}
inline bool CCardTransRev::Execute()
{
	if(!CalcBalance(_trans.inputamt))
		return false;
	SetTotalamt(_trans.inputamt);
	return true;
}
inline  bool CCardTransRev::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}	
	if(!AddOperaccdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
//发行卡
class CCardIssue: public CCardDeposit
{
	
//T_t_cardmadeinfo  _cardmadeinfo;

public:
	virtual bool ExecBefChk();
	virtual bool ExecAftChk();
	virtual bool Execute();
	virtual bool SaveExecResult();
};
inline bool CCardIssue::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.VerifyCardStatus(CARDSTATUS_ISSUE))
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}		
	if(GetBefcardbal()!= _card.dpsamt)
	{
		char szMsg[256];
		if(GetBefcardbal() > _card.dpsamt)
		{
			sprintf(szMsg, "当前卡余额%.2lf大于预充值金额%.2lf", GetBefcardbal() / 100.0, _card.dpsamt / 100.0);
		}
		else
		{
			sprintf(szMsg, "当前卡余额%.2lf小于预充值金额%.2lf", GetBefcardbal() / 100.0,  _card.dpsamt/ 100.0);
		}
		_msg = szMsg;
		return false;
	}
	return true;
}
inline  bool CCardIssue::Execute()
{
	CAccTrans& ats = CAccTrans::GetInst();
	_card.dpscnt = _trans.dpscnt;
	_card.paycnt = _trans.paycnt;
	des2src(_card.cardphyid, _trans.cardphyid);
	des2src(_card.listversion, _card.issuebatchno);
	_card.issuedate = ats.hostdate;
	if(_card.enabledate < _card.issuedate)
		_card.enabledate = ats.hostdate;
	strcpy(_card.updtime, ats.hostdatetime);
	_card.status = CARDSTATUS_NORMAL;
	SetAftcardbal(_card.cardbal);
	return true;
}
inline bool CCardIssue::ExecAftChk()
{
	CAccTrans& ats = CAccTrans::GetInst();
	T_t_cardmadeinfo  cardmadeinfo;
	memset(&cardmadeinfo, 0, sizeof(cardmadeinfo));
	int ret = DB_t_cardmadeinfo_read_lock_by_c0_and_cardid(_trans.cardid, &cardmadeinfo);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			_errcode= E_DB_CARD_N;
		else
			_errcode=  E_DB_CARD_R;
		return false;
	}
	cardmadeinfo.madestatus = MADESTATUS_ISSUED;
	des2src(cardmadeinfo.cardphyid, _trans.cardphyid);
	ret = DB_t_cardmadeinfo_update_lock_by_c0(&cardmadeinfo);
	if(ret)
	{
		return E_DB_CARD_U;
	}
	if(cardmadeinfo.applyid)
	{
		T_t_apply apply;
		memset(&apply, 0, sizeof(apply));
		int ret = DB_t_apply_read_lock_by_c0_and_applyid(cardmadeinfo.applyid, &apply);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				return E_DB_APPLY_N;
			else
				return E_DB_APPLY_R;
		}
		if(apply.applytype != APPLYTYPE_OPENCARD)
		{
			DB_t_apply_free_lock_by_c0();
			_msg = ("该客户没有申请办卡");
			return false;
		}
		apply.status = APPLYSTATUS_SUCC;
		apply.handledate = ats.hostdate;
		strcpy(apply.updtime, ats.hostdatetime);
		ret = DB_t_apply_update_lock_by_c0(&apply);
		if(ret)
		{
			_errcode =  E_DB_APPLY_U;
			return false;
		}
	}
	if(GetBefcardbal()!= _card.balance)
	{
		char szMsg[2540];
		if(GetBefcardbal() > _card.balance)
		{
			sprintf(szMsg, "当前卡余额%.2lf大于预充值金额%.2lf", _trans.befcardbal / 100.0, _card.balance / 100.0);

		}
		else
		{
			sprintf(szMsg, "当前卡余额%.2lf小于预充值金额%.2lf", _trans.befcardbal / 100.0, _card.balance / 100.0);
		}
		_msg=szMsg;
		return false;
	}
	if(GetAftcardbal()<0)
	{
		_msg="卡余额不足";
		return false;
	}	
	return true;
}
inline bool CCardIssue::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	if(!AddOperaccdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}

class CCardClose: public CCardPayment
{
protected:
	int _ReturnAmt;
public:
	CCardClose();
	int GetReturnAmt()
	{
		return _ReturnAmt;
	};
	virtual bool ExecBefChk();
	virtual bool ExecAftChk();
	virtual bool Execute();
	virtual bool buildCarddtl_Pos();
	virtual bool SaveExecResult();
};
inline CCardClose::CCardClose()
{
	_ReturnAmt = 0;
}
inline bool CCardClose::ExecBefChk()
{
	CAccTrans& ats = CAccTrans::GetInst();
	CCheckCardStatus ccs(_card);
	if(!ccs.VerifyCardStatus(CARDSTATUS_CLOSE))
	{
		_msg = ccs.GetCheckMsg();
		return false;
	}
	if(_card.cardbal<0)
	{
		_msg="卡余额异常:当前余额小于0";
		return false;
	}
	SetBefcardbal(_card.cardbal);
	_ReturnAmt = _card.cardbal;
	if(_card.balance == _card.cardbal)
	{
		_card.status=CARDSTATUS_CLOSED;
		_card.delflag = 1;
		_card.deldate = ats.hostdate;
	}
	else if(_card.balance > _card.cardbal)
	{
		//转移到其他收入科目
		//如果大于系统允许的最大值,则不允许销户
		_card.status=CARDSTATUS_CLOSE;
	}
	else
	{
		//如果小于系统允许的最小值,则不允许销户
		_msg = "卡余额大于当前账户余额,请检查该卡交易明细";
		return false;
	}
	return true;
}
inline  bool CCardClose::Execute()
{
	if(_ReturnAmt!=0)
	{
		if(!CalcBalance(_ReturnAmt))
			return false;
	}
	SetTotalamt(_ReturnAmt);
	return true;
}
inline bool CCardClose::buildCarddtl_Pos()
{
	CCardProcess::buildCarddtl_Pos();
	if(_carddtl.posseqno<1)
		_carddtl.posseqno = atol(_trans.refno+6);
	return true;
}
inline bool CCardClose::ExecAftChk()
{
	if(GetAftcardbal()!=0||_card.balance!=0)
	{
		_msg = "退卡后卡余额不等于0";
		return false;
	}		
	return true;
}
inline  bool CCardClose::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}	
	SetAmtOutflag();
	if(!AddOperaccdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
//换卡
class CCardChange: public CCardClose
{
public:
	virtual bool ExecBefChk();
	virtual bool ExecAftChk();
	virtual bool SaveExecResult();
};
inline bool CCardChange::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.VerifyCardStatus(CARDSTATUS_CHANGE))
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}
	SetBefcardbal( _card.cardbal);
	_ReturnAmt = _card.cardbal;
	if(_card.balance == _card.cardbal)
	{
		_card.status=CARDSTATUS_CLOSED;
		_card.delflag = 1;
		_card.deldate = CAccTrans::GetInst().accdate;
	}
	else if(_card.balance > _card.cardbal)
	{
		//转移到其他收入科目
		//如果大于系统允许的最大值,则不允许销户
		_card.status=CARDSTATUS_CLOSE;
	}
	else
	{
		//如果小于系统允许的最小值,则不允许销户
		_msg = "卡余额大于当前账户余额,请检查该卡交易明细";
		return false;
	}
	return true;
}
inline bool CCardChange::ExecAftChk()
{
	if(_card.cardbal!=0)
	{
		_msg = "换卡后原卡余额不等于0";
		return false;
	}		
	return true;
}
inline bool CCardChange::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
//转入
class CCardTransferIn: public CCardDeposit
{
public:
	virtual bool SaveExecResult();
};
inline bool CCardTransferIn::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
class CCardRenew: public CCardClose
{
public:
	virtual bool ExecBefChk();
	virtual bool SaveExecResult();
};
inline bool CCardRenew::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.VerifyCardStatus(CARDSTATUS_RENEW))
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}
	_ReturnAmt = _card.cardbal;
	if(_card.balance == _card.cardbal)
	{
		_card.status=CARDSTATUS_CLOSED;
		_card.delflag = 1;
		_card.deldate = CAccTrans::GetInst().accdate;
	}
	else if(_card.balance > _card.cardbal)
	{
		//转移到其他收入科目
		//如果大于系统允许的最大值,则不允许销户
		_card.status=CARDSTATUS_CLOSE;
	}
	else
	{
		//如果小于系统允许的最小值,则不允许销户
		_msg = "卡余额大于当前账户余额,请检查该卡交易明细";
		return false;
	}
	return true;
}
inline bool CCardRenew::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	return true;
}
//重新发行
class CCardReissue: public CCardIssue
{
protected:
	CCardClose* _orgiObj;
public:
	CCardReissue();
	void SetOrgiTransObj(CCardClose* origObj);
	virtual bool ExecBefChk();
	virtual bool CalcBalance(int amount);
	virtual bool Execute();
	virtual bool ExecAftChk();
};
inline CCardReissue::CCardReissue()
{
	_orgiObj = NULL;
}
inline void CCardReissue::SetOrgiTransObj(CCardClose* origObj)
{
	_orgiObj = origObj;
}
inline bool CCardReissue::ExecBefChk()
{
	if(!CCardIssue::ExecBefChk())
		return false;
	if(!_orgiObj)
	{
		_msg = "函数调用错误,请先调用SetOrgiCardObj";
		return false;
	}
	if(_orgiObj->GetObjCard().cardno != _card.cardno)
	{
		_msg = "新卡号与原卡不符";
		return false;
	}
	return true;
}
inline bool CCardReissue::CalcBalance(int amount)
{
	if(amount<0)
		return false;
	CAccTrans& ats = CAccTrans::GetInst();
	_card.cardbal =  amount;
	_card.balance = amount;
	_card.dpscnt = _trans.dpscnt;
	if(_trans.paycnt)
		_card.paycnt = _trans.paycnt;
	_card.termid = _trans.termid;
	_card.transdate = ats.hostdate;
	_card.transtime = ats.hosttime;
	strcpy(_card.updtime, ats.hostdatetime);
	SetAftcardbal(_card.cardbal);
	return true;
}
inline bool CCardReissue::Execute()
{
	if(!CalcBalance(_orgiObj->GetReturnAmt()))
		return false;
	return true;
}
inline bool CCardReissue::ExecAftChk()
{
	if(GetAftcardbal()!= _orgiObj->GetReturnAmt())
	{
		_msg = "卡余额计算错误";
		return false;
	}
	return true;
}
class CCardBalUpd: public CCardProcess
{
public:
	virtual bool ExecBefChk();
	virtual bool CalcBalance(int amount);
	virtual bool Execute();
	virtual bool ExecAftChk();
	virtual bool SaveExecResult();
};
inline bool CCardBalUpd::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.OnlineTransCheck())
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}
	if(_trans.inputamt== 0)
	{
		_msg = "调整金额不能为0";
		return false;
	}
	return true;
}
inline  bool CCardBalUpd::CalcBalance(int amount)
{
	if(0==amount)
	{
		_msg="调整金额不能为0";
		return false;
	}
	if(amount>0)
	{
		_card.cardbal = AftCardBalInc(amount);
		_card.dpsamt+= amount;		
		_card.dpscnt++;
	}
	else
	{
		int changeamt=  -amount;
		_card.cardbal = AftCardBalDec(changeamt);
		_card.payamt += changeamt;
		_card.paynum++;
	}
	_card.dpscnt = _trans.dpscnt;
	_card.paycnt = _trans.paycnt;
	_card.termid = _trans.termid;
	CAccTrans& ats = CAccTrans::GetInst();
	_card.transdate = ats.hostdate;
	_card.transtime = ats.hosttime;
	strcpy(_card.updtime, ats.hostdatetime);
	return true;
}

inline bool CCardBalUpd::Execute()
{
	if(!CalcBalance(_trans.inputamt))
		return false;
	if(_trans.inputamt<0)
	{
		int  _errcode = UpdateCardBitmap(_card.cardid, _card.paycnt, CARDBITMAPTYPE_SYS_ONLINE);
		if(_errcode)
		{
			return false;
		}
	}
	return true;
}
inline bool CCardBalUpd::ExecAftChk()
{
	if(_trans.inputamt>0)
	{
		//加钱
		if(GetAftcardbal()>_card.balance)
		{
			_msg = "调整后卡余额不允许大于当前账户余额";
			return false;
		}
		if(GetAftcardbal()<GetBefcardbal())
		{
			_msg = "调整余额计算错误";
			return false;
		}
	}
	else
	{
		//扣钱
		if(GetAftcardbal()>GetBefcardbal())
		{
			_msg = "调整余额计算错误";
			return false;
		}
	}
	if(GetAftcardbal()<0)
	{
		_msg="卡余额不足";
		return false;
	}
	return true;
}

inline bool CCardBalUpd::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}

/*
//转账
class CCardTransfer: public CCardProcess {
public:
	CCardTransfer();
	virtual bool CalcBalance(int transamt);
};
*/
#endif
