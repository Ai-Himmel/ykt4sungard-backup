#ifndef _HTTPS_H
#define _HTTPS_H
#include "stdafx.h"
#include "kst_struct.h"
#include "bu_agdsjsw.h"
typedef std::map<std::string,std::string> KeyValueMap;

struct MemoryStruct {
  char *memory;
  size_t size;
};
int GetXmlData(char * data,Agd_ThirdPay &ThirdPay,char* fistchild);
char* intdata(char* str);
char* destorydata(char* str);
char* get_std_name(kst_ald_sqr query);
char* makegetname(kst_ald_pay pay);
char* fixdata(kst_ald_pay pay,Agd_ThirdPay &ThirdPay);
char* get_payid_date(kst_ald_pay query,Agd_ThirdPay &ThirdPay);
int sendhttpsint();
int send_https_get_usename(kst_ald_sqr &query,Agd_ThirdPay &ThirdPay);
int send_https_get_inpayamountid(kst_ald_sqr &query,Agd_ThirdPay &ThirdPay);
int get_name_httpquest(kst_ald_pay &pay,Agd_ThirdPay &ThirdPay);
int get_pay_id(kst_ald_pay &query,Agd_ThirdPay &ThirdPay);
int sendhttpsdestory();
int sendhttpsfix(kst_ald_pay &pay,Agd_ThirdPay &ThirdPay);
int recodepaydata(Agd_ThirdPay &ThirdPay);
#endif