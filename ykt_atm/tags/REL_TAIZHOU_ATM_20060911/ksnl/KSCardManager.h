#ifndef _KSCARDMANAGER_H_
#define _KSCARDMANAGER_H_

#pragma once
#include "afxwin.h"
#include <afxmt.h>
#include "kscomdef.h"


#define ERR_BASE 100
#define ERR_LOADKSCOM_DLL			ERR_BASE + 1
#define ERR_READCARDID				ERR_BASE + 2
#define ERR_READBALANCE				ERR_BASE + 3
#define ERR_CARD_NOT_CONSIST		ERR_BASE + 4
#define ERR_LOAD_FUNC				ERR_BASE + 5
#define ERR_SETWORKKEY				ERR_BASE + 6
#define ERR_PACKAGE_ADD_MONEY		ERR_BASE + 7
#define ERR_PACKAGE_DEC_MONEY		ERR_BASE + 8
#define ERR_OPEN_COM				ERR_BASE + 9
#define ERR_CLOSE_COM				ERR_BASE + 10
#define ERR_COM_NOT_OPEN			ERR_BASE + 11
#define ERR_CARD_NOT_EXIST			ERR_BASE + 12
#define ERR_PACKAGE_SET_MONEY		ERR_BASE + 13
#define ERR_USER_CANCEL				ERR_BASE + 14
#define ERR_SUCCEEDED				0

class CKSConfig;
class CKSWorkflow;

typedef struct {
	int cardid;
	unsigned char phyid[8];
	char password[7];
	double balance;
	int tx_cnt;
}KS_CARD_INFO;



class CKSCardManager
{
private:
	char m_workKey[17];
	CKSConfig * m_config;
	CKSWorkflow * m_workflow;
	int m_errno;
	int m_timeout;
	// 默认使用的钱包号
	static const int ms_globalPackageNo;
// 	int LoadKSComDLL();
// 	int LoadKSCom();
// 	int ReleaseKSCom();
	int LoadCardDLL();
	int LoadCardCom();
	int ReleaseCardCom();
	DWORD GetLastKey();
public:
	static int ciCardId;
	static int ciPhyId;
	static int ciPswd;
	static int ciBalance;
	static int ciAllInfo;

	static bool ms_isComOpen;

	CKSCardManager(CKSConfig * config,const char* workKey,CKSWorkflow * workflow);
	~CKSCardManager(void);
	int ReadCardInfo(KS_CARD_INFO * cardinfo,int ciBit,int timeout=-1);
	int AddMoney(int cardid,int money);
	int SetMoney(int cardid,int money);
	int TestCardExists(int timeout);
	inline int GetErrNo()
	{
		return errno;
	}
	CString GetErrMsg();
	int OpenCOM();
	int CloseCOM();
	bool IsCOMOpen();

	static UINT TestCardThread( LPVOID pParam );
	static CEvent ms_testCardEvent;
	static CEvent ms_cancelEvent;
};

#endif
