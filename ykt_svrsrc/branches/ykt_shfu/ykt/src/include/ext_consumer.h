#ifndef _EXT_COSUMER_H_
#define _EXT_COSUMER_H_
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "errdef.h" 
#include "pubdb.h"
#include "fdsqc.h"
#include "dbfunc.h"
#include "pubfunc.h"
#include "account.h"
#include "cpack.h"

//#ifdef __cplusplus 
//extern "C" {
//#endif
//请求号
#pragma once

typedef struct {
	int check_user_pwd;
	int tend_to_enter_account;
	int online_trade;
	char ext_msg[256];
}transfer_control_t;

typedef struct {
	int request_type;
	int tx_code;
	int (*pre_check_transfer)(ST_PACK *in_pack,ST_PACK *out_pack,transfer_control_t *control);
	int (*search_thirdparty_account)(ST_PACK *in_pack,int trade_code,InAcc *IA);
	int (*thirdparty_transfer)(ST_PACK *in_pack,char ext_msg[256]);
	int (*deal_self_out_pack)(ST_PACK *in_pack,ST_PACK *out_pack);
	int (*record_small_serial)(ST_PACK *in_pack,T_t_tif_tradeserial *tradeserial,ST_PACK *out_pack);
}ext_consumer_request_t;

#pragma pack(1)

typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char cutid[22];
	char money[7];
	char datetime[10];
	char tracenum[14];
	char phone[11];
	char retnum[2];
	char plugdata[36];
	char signcheck[200];
}ext_phone_trans_t;



typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	char money[7];
	char datetime[10];
	char tracenum[18];
	char retnum[4];
	char clientid[4];
	char signcheck[32];
}ext_elect_req_t;

typedef struct{
	char prix[1];//加密标志
	char length[4];//包长度
	char type[4];//信息类型
	char bitery[16];//位元图
	char room[20];//房间名称
	char cutid[22];//一卡通帐号
       char checkflag[1];//检查对应关系
	char clientid[4];//工作站号
	char signcheck[32];//数字签名码
}ext_elect_req_t847323;

typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	char relate[1];
	char clientid[4];
	char signcheck[32];
}ext_elect_search_req_t;

#pragma pack()

int ext_consumer_find_trade(int request_type,ext_consumer_request_t  *transfer);
int tend_to_enter_account(ST_PACK *in_pack,InAcc *IA,int trade_code,T_t_tif_tradeserial *tradeserial);
int record_serial(ST_PACK *in_pack,T_t_tif_tradeserial *tradeserial,ST_PACK *out_pack);
int enter_account(ST_PACK *in_pack,InAcc *IA,ST_PACK *out_pack);
int elec_room_deposit_search(ST_PACK *in_pack,ST_PACK *out_pack);

//#ifdef __cplusplus
//}
//#endif 

#endif // _EXT_COSUMER_H_

