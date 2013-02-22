#ifndef _KS_DONGGUAN_CARDTYPE_H_
#define _KS_DONGGUAN_CARDTYPE_H_

#include "kscardtype.h"
#include "ks_cardtype.h"

class DGCardType : public CCardType
{
private:
	int initDef();
	//char m_AppSerialNo_[17];
protected:
	virtual int checkCardType(int ct);
	void GetSupportCardType(unsigned int cardTypes[],int &cnt);
	virtual int doSuccessRequestCard();
	int readAppSerialNo();
public:
	DGCardType();
	~DGCardType();
	virtual int  SelectADF ();
	virtual int  InitUserCard (const char *sShowCardNo);
	virtual int  RestoreFactorySettings ();
	virtual int InitCardTypeDLL();
	virtual int AddMoney(ST_TRANSPACK *transpack);
	virtual int PayMoney(ST_TRANSPACK *payment);
	virtual int CalcMacOnline(ST_TRANSPACK *transpack,char *sMac);
};

#endif // _KS_DONGGUAN_CARDTYPE_H_

