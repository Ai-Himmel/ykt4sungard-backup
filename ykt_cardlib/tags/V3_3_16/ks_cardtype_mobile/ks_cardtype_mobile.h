#ifndef KS_CARDTYPE_MOBILE_H_
#define KS_CARDTYPE_MOBILE_H_
#include <vector>
#include <set>
#include <map>
#include "..\\ks_cardtype\\ks_cardtype.h"
using namespace std;

class CCardTypeMobile:public CCardType
{
private:
	int UpdateDoorCustId();
	int CalcSafeMacWithKey(const unsigned char *key,const char* uCmd,int nCmdLen,char *szMac);
protected:
	virtual int checkCardType(int ct);
public:
	CCardTypeMobile();
	~CCardTypeMobile();
	virtual int SelectADF();
	int UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKey[16]);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual int RequestCard(char* szCardPhyID=NULL);
	virtual int WriteCard();
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	//virtual int InitForTrans(ST_TRANSPACK *trans,int trans_type);
};


#endif // _KS_ENC_H_

