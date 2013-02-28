#ifndef _BUBANK_BANKFUNC_H_
#define _BUBANK_BANKFUNC_H_
////////////////////////////////////////////////////////////////////////////////////
// bank write card status
////////////////////////////////////////////////////////////////////////////////////
#include "BUShm.h"
#include "cardprocess.h"
#include "bankerr.h"

class SHM_Lock_Guard
{
private:
	CBUShm &shm_;
	int locked_;
public:
	SHM_Lock_Guard(CBUShm &shm):shm_(shm),locked_(0)
	{
	}
	int lock()
	{
		if(shm_.Lock())
		{
			locked_ = 1;
			return 0;
		}
		return -1;
	}	
	~SHM_Lock_Guard()
	{
		if(locked_ == 1)
		{
			shm_.Unlock();
			locked_ = 0;
		}
	}
};

#define BK_SHMLOCK_GUARD(shm) SHM_Lock_Guard shm##shm__(shm); if(shm##shm__.lock()) return
#define BK_SHMLOCK_GUARD_RET(shm,ret) SHM_Lock_Guard shm##shm__(shm); if(shm##shm__.lock()) return (ret)

#define JB_BANK_ID 1
class BKConfiguration
{
private:
	typedef struct {
		unsigned int vernum;
	}CFGSHM_T;
	static BKConfiguration * instance_;
	typedef std::map<std::string,std::string> VALUE_MAP_TYPE;
	typedef std::map<int,std::string> ERRMSG_MAP_TYPE;
	VALUE_MAP_TYPE para_map_;
	ERRMSG_MAP_TYPE errmsg_map_;
	CFGSHM_T* cfgshm_;
	CBUShm cfgshm_handle_;
	CFGSHM_T localcfg_;
	int save_para(const char *para,const char *value);
	int save_int_para(const char *para,int value); 
	BKConfiguration();
	int init_shm();
	void delete_shm();
public:
	~BKConfiguration();
	static BKConfiguration* instance();
	static const char SHMCFG_NAME[];
	int load_config();
	int load_errmsg();
	int check_config_ver();
	int get_int_para(const char *para,int *value) const;
	int get_string_para(const char *para,char *value) const;
	const char *get_errmsg(int code,char *msg) const;
};

//////////////////////////////////////////////////////////////////////////////////
int BKCheckSysKey(int sysid,const char *dynkey,T_t_subsystem *sys);

int BKGenSysKey(const char *ip,const char *mac,const char *authcode,T_t_subsystem *sys);
int BKCheckBankCode(const char *bank_code,T_t_bank *bank);
int BKGetCardByCardASNo(const char *cardasno,T_t_card *tCard,int flag=0);
int BKUpdateCardForDps(const T_t_card &tCard);
int BKCheckCardStatus(const T_t_card &tCard);


/////////////////////////////////////////////////////////////////////////////////
//圈存
class CBankTransfer: public CCardDeposit
{
protected:
	T_t_banktransdtl _bankdtl;
	bool buildBankdtl_Card();
	bool buildBankdtl_Pos();
	bool buildBankdtl_Trans();
	bool buildBankdtl();
	bool AddBankdtl();
public:
	CBankTransfer();
	virtual bool ExecBefChk();
	const T_t_banktransdtl& GetObjBankdtl();
	virtual bool SaveExecResult();
};
inline CBankTransfer::CBankTransfer()
{
	memset(&_bankdtl, 0, sizeof(_bankdtl));
}
inline bool  CBankTransfer::ExecBefChk()
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
	if(_trans.inputamt <= 0)
	{
		_msg = "充值金额错误";
		return false;
	}
	if(_trans.inputamt > ct.maxdpsamt)
	{
		char szMsg[128];
		sprintf(szMsg, "充值金额%.2lf超过最大限额%.2lf", _trans.inputamt / 100.0, ct.maxdpsamt / 100.0);
		_msg = szMsg;
		return false;
	}
	// 验证上次写卡状态
	if(_card.dpsnum > 0)
	{
		// 认为写卡未成功
		if(_card.dpscnt == _trans.dpscnt)
		{
			_card.dpswfailflag = 1;
		}
		else if(_card.dpscnt > _trans.dpscnt)
		{
			// 卡充值次数异常
			writelog(LOG_ERR, "check dpscnt, db[%d] card[%d]", _card.dpscnt, _trans.dpscnt);
			_errcode = EB_CARDDPSCNTERR;
			return false;
		}
		else
		{
			_card.dpswfailflag = 0;
		}
	}
	return true;
}
inline bool CBankTransfer::buildBankdtl_Card()
{
	_bankdtl.cardid = _card.cardid;
	_bankdtl.cardno = _card.cardno;
	des2src(_bankdtl.cardasno, _card.cardasno);
	_bankdtl.cardtype = _card.cardtype;
	_bankdtl.balance = _card.balance;
	return true;
}
inline bool CBankTransfer::buildBankdtl_Pos()
{
	//_bankdtl.termid = _trans.termid;
	des2src(_bankdtl.samno, _trans.samno);
	_bankdtl.samseqno = _trans.samseqno;
	return true;
}
inline bool CBankTransfer::buildBankdtl_Trans()
{
	CAccTrans& ats = CAccTrans::GetInst();
	strcpy(_bankdtl.refno, _trans.refno);
	_bankdtl.accdate = ats.accdate;
	_bankdtl.hostdate = ats.hostdate;
	_bankdtl.hosttime = ats.hosttime;
	_bankdtl.termdate = _trans.termdate;
	_bankdtl.termtime = _trans.termtime;
	_bankdtl.transcode = _trans.transcode;
//	_bankdtl.transtype = _trans.transtype;
	_bankdtl.amount = GetTotalamt();
//	_bankdtl.otheramt = _trans.feeamt;
	_bankdtl.befcardbal = GetBefcardbal();
	_bankdtl.aftcardbal =GetAftcardbal();
	_bankdtl.dpscnt = _trans.dpscnt;
	_bankdtl.merchid = _trans.merchid;
	_bankdtl.status = TRANSTATUS_INIT;
	_bankdtl.wctatus = BWCS_INIT;
	//_bankdtl.citycode=citycode;
	return true;
}
inline bool CBankTransfer::buildBankdtl()
{
	CAccTrans& ats = CAccTrans::GetInst();
	_bankdtl.expdate = atoi(ats.reqpack->sdate1);
	des2src(_bankdtl.bankcode, ats.reqpack->sname);
	des2src(_bankdtl.bankcardno, ats.reqpack->sbank_acc);
	buildBankdtl_Card();
	buildBankdtl_Pos();
	buildBankdtl_Trans();
	return true;
}
inline bool CBankTransfer::AddBankdtl()
{
	buildBankdtl();
	int ret = DB_t_banktransdtl_add(&_bankdtl);
	if(ret)
	{
		if(DB_REPEAT == ret)
			_errcode = EB_TERMSEQERR;
		else
			_errcode = EB_SYSTEM;
		return false;
	}
	return true;
}
inline bool CBankTransfer::SaveExecResult()
{
//	if(!ExecUpdCard())
//		return false;
	if(!GetRefno())
		return false;
	if(!AddBankdtl())
	{
		return false;
	}
	if(!AddCarddtl())
	{
		return false;
	}
	return true;
}
inline const T_t_banktransdtl& CBankTransfer::GetObjBankdtl()
{
	return _bankdtl;
}

#endif 
