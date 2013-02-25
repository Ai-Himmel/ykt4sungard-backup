#ifndef _KS_LIAONING_H_
#define _KS_LIAONING_H_

#include "kscardtype.h"
#include "..\\ks_cardtype\\ks_cardtype.h"

class ks_zjvcc_cardtype:public CCardType
{
private:
protected:
	virtual int checkCardType(int ct);
	int RestoreRecord();
public:
	ks_zjvcc_cardtype();
	//int SetupDF03();
	int SelectADF();
	int UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKeyType,byte ucKey[16]);
	int CalcSafeMac4Sam(const char *szCmdbuf,char *szMac);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	//int VerifyPin(const char* sPin);

	int ExecExtAuthCmd8(byte ucExtAuthKey[16],int nKeyIndex=0);
	int ExtAuth(const char *cardphyid,int keyidx);
	int GetRandomNum8(byte *uRandomNum);

};

#endif // _KS_LIAONING_H_
