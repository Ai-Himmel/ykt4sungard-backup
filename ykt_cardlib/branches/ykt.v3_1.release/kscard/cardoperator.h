#ifndef _CARDOPERATOR_H_
#define _CARDOPERATOR_H_

#include "kscard_imp.h"
#include "kscardtype.h"

class CardOperator
{
public:
	CardOperator(ks_cardtype_base *cardtype);
	~CardOperator();
	int Deposite(ST_TRANSPACK &pack);
	int DepositeRetry(ST_TRANSPACK &pack);
	int DepositeCancel(ST_TRANSPACK &pack);
  int DepositeInit(ST_TRANSPACK &pack);
  int DepositeDebit(ST_TRANSPACK &pack);
private:
	CardOperator(const CardOperator&);
	CardOperator& operator= (const CardOperator&);
	int SendLoadInitial(ST_TRANSPACK &pack);
	int SendLoadDebit(ST_TRANSPACK &pack,char *sMac2);
	int SendRetry(ST_TRANSPACK &pack,char *sMac2);
private:
	int card_balance_;
	int card_deposit_count_;
	char account_date_[9];
	char app_serial_no_[33];
	ks_cardtype_base *cardtype_;
};
#endif // _CARDOPERATOR_H_
