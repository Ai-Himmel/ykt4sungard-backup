#include "stdafx.h"
#include "kst_struct.h"
//查询交易
typedef struct queryald
{
	char discern[1];
	char length[4];
	char type[4];
	char bitmap[16];
	char roomname[20];
	char account[22];
	char Correspondence[1];
	char station[4];
    char signature[32];
}query;

//查询应答
typedef struct queryaldrec
{
	char discern[1];
	char length[4];
	char type[4];
	char bitmap[16];
	char roomname[20];
	char account[22];
	char Correspondence[1];
	char money[16];
	char elc_money[16];
	char elc_bal_money[16];
	char wat_money[16];
	char wat_bla_money[16];
	char retnum[4];
	char station[4];
    char signature[32];
}qureyrec;

//支伏
typedef struct payelect{
	char discern[1];
	char length[4];
	char type[4];
	char bitmap[16];
	char roomname[20];
	char account[22];
	char money[7];//7文档是16，先前代码是7
	char datetime[10];
	char tracenum[18];
	char retnum[4];
	char station[4];
	char signature[32];
}ext_elect_req_t;
char *getalderr(int errcode);
int getkst_ald_sqr(char *Tdata,kst_ald_sqr &sqr);
int getkst_ald_pay(char *Tdata,kst_ald_pay &pay);
int getkst_ald_rvs(char *Tdata,kst_ald_rvs &rvs);
int getkst_ald_rvs(char *Tdata,kst_ald_rvs &rvs);
int makekstsqldata(queryaldrec &rcvquery,char *Tdata);
int makekstsqldata_rj(queryaldrec &rcvquery,char *Tdata);
int makequerysenddata(queryald &Tdata,kst_ald_sqr &sqr);
int makepaysenddata(payelect &Tdata,kst_ald_pay &pay);
int makervssenddata(payelect &Tdata,kst_ald_rvs &rvs);
int makervssenddata(payelect &Tdata,kst_ald_rvs &rvs);
int makekstpaydata(ext_elect_req_t &pay,char *Tdata);
int makekstrecdata(ext_elect_req_t &pay,char *Tdata);
int get_rj_query(char *Tdata,queryaldrec &rtquery);