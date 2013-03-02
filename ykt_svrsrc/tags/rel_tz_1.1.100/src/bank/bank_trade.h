#ifndef _BANK_TRADE_H_
#define _BANK_TRADE_H_
#include <string.h>
#include <stdio.h>
#include "cpack.h"
#include "errdef.h"
#include "bank.h"
#include "bankdb.h"
#include "pubdef.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "mypub.h"
#include "pubfunc.h"
#include "account.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "gwpack.h"

int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID * handle,int *pRetCode,char *szMsg);
int query_subsidy(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int get_subsidy(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);


int do_buy_water(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_query_water(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_bind_water(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_write_card_error(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);

int do_query_power(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);
int do_buy_power(TRUSERID *handle,ST_PACK *in_pack,int *pRetCode,char *szMsg);
int do_query_power_dorm(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg);

#endif 

