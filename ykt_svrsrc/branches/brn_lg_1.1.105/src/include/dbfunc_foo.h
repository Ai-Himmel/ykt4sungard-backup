#ifndef _DBFUNC_FOO_H_
#define _DBFUNC_FOO_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "pubdb.h"
#include "cpack.h"

#ifndef CHECK_DB_ERR
#define CHECK_DB_ERR  db_chk_err(__FILE__,__LINE__,&sqlca)
#endif

int process930105(int devid,int week);
int process930117NoDel(T_t_door_device_cardlist *cardlist,int addflag);
int Get_card_next_serial(int card_id,char *tx_date,int total_cnt,double *in_bala,double *out_bala);
int CheckGatewayDynKey(int sysid,char * dynKey);
int GetDevUsageByDevId(char * devid,int *usage);
int GetDevUsageById(int id,int *usage);



/////////////////////////////////////////////////////////////////
/// 会议签到使用的函数
int GetConferenceIDByDev(T_t_door_txdtl* tTxdtl,int *conf,char sign[1]);
int SaveConferenceSerial(T_t_door_txdtl* tTxdtl,int conf,int custid,char sign);
int CheckOperatorPwd(const char* operator,const char* pwd);
////////////////////////////////////////////////////////////////////
///考勤系统使用到的函数
int SaveKQSerial(T_t_door_txdtl* tTxdtl);

int get_cutid_by_show_card_no(const char * showno,int * cutid);

//subsidy
int is_cust_open_account(int cust_id,int act_type);
int GetCountSubsidyByNotEquStatus(int *count,char *status,char *batch_no);
int get_batch_no_by_subsidy_no(int subsidy_no,char *batch_no);
int judge_with_max_subsidy_no_within_new(int subsidy_no);
//int get_curr_card_by_custid(int custid,T_t_pif_card *card);
#ifdef __cplusplus
}
#endif

#endif // _DBFUNC_FOO_H_
