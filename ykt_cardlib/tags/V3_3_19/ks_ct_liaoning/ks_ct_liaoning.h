#ifndef _KS_LIAONING_H_
#define _KS_LIAONING_H_

#include "kscardtype.h"
#include "..\\ks_cardtype\\ks_cardtype.h"

class ks_ctln_cardtype:public CCardType
{
private:
protected:
	virtual int checkCardType(int ct);
	int RestoreRecord();
public:
	ks_ctln_cardtype();
	~ks_ctln_cardtype();
	virtual int SelectADF();
	virtual int OpenPort();
	int UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKeyType,byte ucKey[16]);
	virtual int InitUserCard(const char *sShowCardNo);
	virtual int RestoreFactorySettings();
	virtual void GetSupportCardType(unsigned int cardTypes[],int &cnt);

};

#endif // _KS_LIAONING_H_
