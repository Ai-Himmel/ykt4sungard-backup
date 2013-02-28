#ifndef CARDDPS_H_
#define CARDDPS_H_
#include"cardprocess.h"
//读卡器在线支付

class CCardDpsTest: public CCardProcess
{
public:
	virtual bool ExecBefChk();
	virtual bool ExecAftChk();
	virtual bool CalcBalance(int amount);
	virtual bool buildDpsdtl();
	virtual bool Execute();
	virtual bool SaveExecResult();
};
inline bool CCardDpsTest::ExecBefChk()
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
inline bool CCardDpsTest::ExecAftChk()
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
inline bool CCardDpsTest::Execute()
{
	SetTotalamt(_trans.inputamt);
	if(!CalcBalance(GetTotalamt()))
		return false;
	return true;
}
inline bool CCardDpsTest::buildDpsdtl()
{
	if(!CCardProcess::buildDpsdtl())
		return false;
	CAccTrans& ats = CAccTrans::GetInst();
	_dpsdtl.dpsdate=atoi(ats.reqpack->sdate1);
	_dpsdtl.dpstime=atoi(ats.reqpack->stime1);
	memcpy(_dpsdtl.mac1,ats.reqpack->sholder_ac_no2,8);
	memcpy(_dpsdtl.mac2,ats.reqpack->sname,8);
	_dpsdtl.status=TRANSTATUS_INIT;
	return true;
}
inline bool CCardDpsTest::SaveExecResult()
{
	if(!GetRefno())
		return false;
	if(!AddDpsdtl())
	{
		return false;
	}
	return true;
}
inline  bool CCardDpsTest::CalcBalance(int amount)
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
///////////////////////////////////////////////////////////////////////////////
#if 0
template<class CardCheckPolicy,
		 class TransSavePolicy
		 >
	class CCardDps : public CCardDeposit
{
private:
	typedef CardCheckPolicy CHP;
	typedef TransSavePolicy TSP;
public:
	virtual bool ExecBefChk();
};
#endif
class CCardDpsTrans:public CCardDpsTest
{
private:
	bool bSucc;
public:
	CCardDpsTrans();
	bool succ();
	virtual bool LockCard(int cardid=0);
	virtual bool SaveExecResult();
	virtual bool buildCarddtl_Pos();
	bool GetOrgiDpsdtl(int accdate, char* refno);
	bool UpdDpsdtl();
};
inline CCardDpsTrans::CCardDpsTrans()
{
	CCardProcess::CCardProcess();
	bSucc=false;
}
inline bool CCardDpsTrans::succ()
{
	return bSucc;
}
inline bool CCardDpsTrans::GetOrgiDpsdtl(int accdate, char* refno)
{
	int ret = 0;
	memset(&_dpsdtl,0,sizeof(_dpsdtl));
	ret = DB_t_dpsdtl_read_lock_by_c0_and_accdate_and_refno(accdate, refno, &_dpsdtl);
	if(ret)
	{
		writelog(LOG_ERR,"accdate[%d], refno[%s]",accdate, refno);
		if(DB_NOTFOUND == ret)
			return E_DB_DPSDTL_N;
		else
			return E_DB_DPSDTL_R;
	}
	if(TRANSTATUS_INIT != _dpsdtl.status)
	{
		DB_t_dpsdtl_free_lock_by_c0();
		if(TRANSTATUS_CANCEL == _dpsdtl.status)
		{
			ERRTIP("交易已经冲正");
		}
		else if(TRANSTATUS_SUCC == _dpsdtl.status)
		{
			ERRTIP("该交易已处理成功");
			bSucc=true;
		}
		else
		{
			ERRTIP("该交易状态错误");
		}
		return false;
	}
	return true;
}
inline bool CCardDpsTrans::LockCard(int cardid)
{
	CAccTrans& ats = CAccTrans::GetInst();
	if(!GetOrgiDpsdtl(ats.accdate,_trans.refno))
	{
		return false;
	}
	_trans.cardid=_dpsdtl.cardid;
	memcpy(_trans.samno,_dpsdtl.samno,12);
	_trans.inputamt=_dpsdtl.amount;
	_trans.dpscnt = _dpsdtl.dpscnt;
	_trans.paycnt = _dpsdtl.paycnt;
	_trans.operid = _dpsdtl.operid;
	_trans.branchid = _dpsdtl.branchid;
	_trans.transcode = _dpsdtl.transcode;
	_trans.samseqno = _dpsdtl.termseqno;
	_trans.termtime = _dpsdtl.termtime;
	_trans.termdate = _dpsdtl.termdate;
	SetBefcardbal(_dpsdtl.befcardbal);
	_trans.cardid = _dpsdtl.cardid;
	return CCardProcess::LockCard(_trans.cardid);
}

inline bool CCardDpsTrans::UpdDpsdtl()
{
	_dpsdtl.status = TRANSTATUS_SUCC;
	int ret = DB_t_dpsdtl_update_lock_by_c0(&_dpsdtl);
	if(ret)
	{
		_errcode= E_DB_DPSDTL_U;
		return false;
	}
	return true;
}
inline bool CCardDpsTrans::buildCarddtl_Pos()
{
	CCardProcess::buildCarddtl_Pos();
	if(_carddtl.posseqno<1)
		_carddtl.posseqno = atol(_trans.refno+6);
	return true;
}
inline bool CCardDpsTrans::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!UpdDpsdtl())
	{
		return false;
	}
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
#endif
