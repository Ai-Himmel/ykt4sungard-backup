#ifndef __CARD_BUSINESS_H_
#define __CARD_BUSINESS_H_

#include "stdio.h"
#include "desdll.h"
#include <time.h>

//#ifdef __cplusplus
//extern "C" {
//#endif

int read_m1card(unsigned char *cardid,unsigned char *bala,unsigned char *cnt);
int add_m1card(unsigned char *cardid,unsigned char *bala,int retries);
int auth_m1card(int portno,const char *cardkey);
int close_card_reader();
int write_m1card(int nPacketNo, unsigned long nMoney);
int test_func(char *msg);

//#ifdef __cplusplus
//}
//#endif

#endif