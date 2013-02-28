#ifndef CARDPAY_H_
#define CARDPAY_H_
#include"cardprocess.h"
//读卡器在线支付
class CCardPayTest:public CCardProcess
{
protected:
	T_t_paydtl _paydtl;
	bool buildPaydtl_Oper();
	bool buildPaydtl_Card();
	bool buildPaydtl_Pos();
	bool buildPaydtl_Trans();
	bool buildPaydtl();
	bool AddPaydtl();
public:
	virtual bool CalcBalance(int amount);
	virtual bool ExecBefChk();
	virtual bool Execute();
	virtual bool ExecAftChk();
	virtual bool SaveExecResult();
};
inline bool CCardPayTest::buildPaydtl_Card()
{
	_paydtl.cardid = _card.cardid;
	_paydtl.cardno = _card.cardno;
	des2src(_paydtl.cardasno, _card.cardasno);
	_paydtl.cardtype = _card.cardtype;
	_paydtl.balance = _card.balance;
	return true;
}
inline bool CCardPayTest::buildPaydtl_Oper()
{
	_paydtl.branchid = _trans.branchid;
	_paydtl.operid = _trans.operid;
	return true;
}
inline bool CCardPayTest::buildPaydtl_Pos()
{
	_paydtl.termid = _trans.termid;
	_paydtl.termseqno = _trans.termseqno;
	des2src(_paydtl.samno, _trans.samno);
	return true;
}
inline bool CCardPayTest::buildPaydtl_Trans()
{
	CAccTrans& ats = CAccTrans::GetInst();
	_paydtl.accdate = ats.accdate;
	_paydtl.hostdate = ats.hostdate;
	_paydtl.hosttime = ats.hosttime;
	if(_trans.termdate)
	{
		_paydtl.termdate = _trans.termdate;
		_paydtl.termtime = _trans.termtime;
	}
	else
	{
		_carddtl.termdate = ats.hostdate;
		_carddtl.termtime = ats.hosttime;
	}
	_paydtl.transcode = _trans.transcode;
	_paydtl.transtype = _trans.transtype;
	_paydtl.dpscnt = _trans.dpscnt;
	_paydtl.paycnt = _trans.paycnt;
	_paydtl.merchid = _trans.merchid;
	_paydtl.status = TRANSTATUS_INIT;
	strcpy(_paydtl.refno, _trans.refno);
	des2src(_paydtl.remark, _trans.remark);
	_paydtl.befcardbal = GetBefcardbal();
	_paydtl.aftcardbal = GetAftcardbal();
	_paydtl.amount= GetTotalamt();
//	_paydtl.otheramt ;
	return true;
}
inline bool CCardPayTest::buildPaydtl()
{
	memset(&_paydtl,0,sizeof(_paydtl));
	buildPaydtl_Card();
	buildPaydtl_Oper();
	buildPaydtl_Pos();
	buildPaydtl_Trans();
	return true;
}
//记录卡交易明细
inline bool CCardPayTest::AddPaydtl()
{
	int ret = 0;
	buildPaydtl();	
	if(_paydtl.termseqno < 1)
	{
		_paydtl.termseqno= atol(_paydtl.refno + 6);
	}
	ret = DB_t_paydtl_add(&_paydtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			_errcode = E_DB_PAYDTL_E;
		else
			_errcode = E_DB_PAYDTL_I;
		return false;
	}
	return true;
}

inline bool CCardPayTest::ExecBefChk()
{
	CCheckCardStatus CCS(_card);
	if(!CCS.OnlineTransCheck())
	{
		_msg = CCS.GetCheckMsg();
		return false;
	}
	//检查读卡器商户
	int ret=0;
	int posid=0;
	ret=GetDevIDBySamno(_trans.samno,&posid);
	if(ret)
	{
		_errcode=ret;
		return false;
	}
	T_t_pos pos;
	memset(&pos,0,sizeof(pos));
	ret=DB_t_pos_read_by_posid(posid,&pos);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			_errcode= E_DB_POS_N;
		else
			_errcode= E_DB_POS_R;
		return false;
	}
	if(pos.status[0]!=POSSTATUS_USED)
	{
		_msg="当前设备未启用";
		return false;
	}
	if(pos.merchid<1)
	{
		_msg="当前设备无对应商户";
		return false;
	}
	T_t_merch merch;
	memset(&merch,0,sizeof(merch));
	ret=DB_t_merch_read_by_merchid(pos.merchid,&merch);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			_errcode=E_DB_SHOP_N;
		else
			_errcode=E_DB_SHOP_R;
		return false;
	}
	if(merch.status!=1)
	{
		_msg="商户状态错误";
		return false;
	}
	_trans.termid = pos.posid;
	_trans.merchid=pos.merchid;
	return true;
}
inline bool CCardPayTest::CalcBalance(int amount)
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
inline bool CCardPayTest::Execute()
{
	if(!CalcBalance(_trans.inputamt))
		return false;
	SetTotalamt(_trans.inputamt);
	return true;
}
inline bool CCardPayTest::ExecAftChk()
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
inline bool CCardPayTest::SaveExecResult()
{
	if(!GetRefno())
		return false;
	if(!AddOperdtl())
	{
		return false;
	}
	if(!AddPaydtl())
	{
		return false;
	}
	return true;
}
class CCardPayTrans:public CCardPayTest
{
public:
	virtual bool ExecBefChk();
	virtual bool SaveExecResult();
	bool GetOrgiPaydtl(int accdate, char* refno);
	bool UpdPaydtl();
};
inline bool CCardPayTrans::GetOrgiPaydtl(int accdate, char* refno)
{
	int ret = 0;
	memset(&_paydtl,0,sizeof(_paydtl));
	ret = DB_t_paydtl_read_lock_by_c0_and_accdate_and_refno(accdate, refno, &_paydtl);
	if(ret)
	{
		writelog(LOG_ERR,"accdate[%d], refno[%s]",accdate, refno);
		if(DB_NOTFOUND == ret)
			return E_DB_PAYDTL_N;
		else
			return E_DB_PAYDTL_R;
	}
	if(TRANSTATUS_INIT != _paydtl.status)
	{
		DB_t_paydtl_free_lock_by_c0();
		if(TRANSTATUS_CANCEL == _paydtl.status)
		{
			ERRTIP("交易已经冲正");
		}
		else if(TRANSTATUS_SUCC == _paydtl.status)
		{
			ERRTIP("该交易已处理成功");
		}
		else
		{
			ERRTIP("该交易状态错误");
		}
		return false;
	}
	return true;
}
inline bool CCardPayTrans::UpdPaydtl()
{
	_paydtl.status = TRANSTATUS_SUCC;
	des2src(_paydtl.tac,_trans.temp);
	int ret = DB_t_paydtl_update_lock_by_c0(&_paydtl);
	if(ret)
	{
		_errcode= E_DB_PAYDTL_U;
		return false;
	}
	return true;
}
inline bool CCardPayTrans::ExecBefChk()
{
	if(!CCardPayTest::ExecBefChk())
		return false;
	CAccTrans& ats=CAccTrans::GetInst();
	if(!GetOrgiPaydtl(ats.accdate,_trans.refno))
	{
		return false;
	}
	_trans.inputamt=_paydtl.amount;
	_trans.dpscnt = _paydtl.dpscnt;
	_trans.paycnt = _paydtl.paycnt;
	SetBefcardbal(_paydtl.befcardbal);
	_trans.cardid = _paydtl.cardid;
	return true;
}
inline bool CCardPayTrans::SaveExecResult()
{
	if(!ExecUpdCard())
		return false;
	if(!UpdPaydtl())
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
