///////////////////////////////////////////////////////////////////////////////
#ifndef _KS_GLOBALDEF_H_
#define _KS_GLOBALDEF_H_

class KsCardDaemonCfg
{
public:
	KsCardDaemonCfg()
	{
	};
	std::string svrip_;
	int svrport_;
	int svrmainfunc_;
	int listenport_;
	int termid_;
	int samid_;
	int maxOfflineDtlCount_;
	int maxOfflineDtlDay_;
	int maxBackupDtlCount_;
	std::string devphyid_;
	wxCriticalSection m_critsect;
};
enum {DTLST_INIT = 0,DTLST_SUCCESS = 1,DTLST_UNCONFIRM=2,DTLST_CANCEL=3,DTLST_LOCKCARD=5,DTLST_FAILED};
enum {TC_PURCHASE = 1000, TC_CANCELPURCHASE = 1001 };

#endif // _KS_GLOBALDEF_H_
