#ifndef _KSG_ADVANSTACARD_H_
#define _KSG_ADVANSTACARD_H_

#pragma  once
#include "AdvanSta.h"
class KSAdvanstaCard
{
private:
	int port_;
	int errcode_;
public:
	KSAdvanstaCard();
	~KSAdvanstaCard();
	int open();
	int close();
	int Increment(int money,char *msg,PURCHASEINCREASE *result);
	int ReadBalance(PURCHSEARCH *purch);
	int GetErrCode() const 
	{
		return errcode_;
	}
	const char *GetErrMsg();
};
#endif // _KSG_ADVANSTACARD_H_
