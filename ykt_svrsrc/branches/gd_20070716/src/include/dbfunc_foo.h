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
//得到独立核算商户的个数和总的营业额
int GetSumCountIndepShop(double *sum,int *count);
//得到操作员分组一天的现金总合,去掉现金划拨和充正交易部分
int ReadFromOpenGroupAndRepOper(char *group_no,double *GroupCash);
/////////////////////////////////////////////////////////////////
/// 会议签到使用的函数
int GetConferenceIDByDev(T_t_door_txdtl* tTxdtl,int *conf,char sign[1]);
int SaveConferenceSerial(T_t_door_txdtl* tTxdtl,int conf,int custid,char sign);
int CheckOperatorPwd(char* oper,char* pwd);
int CheckShopMealTypeConflict();

int is_oper_has_authcard(char oper[11]);
int is_already_publish_authcard(char physical_no[8+1],char operator_code[10+1],int *card_id);
int is_physical_no_in_use(char physical_no[8+1] );

int SaveKQSerial(T_t_door_txdtl* tTxdtl);

int process930117(T_t_door_device_cardlist *cardlist,int addflag,int seq);
int process930121(int cardid,int addflag,char * version,int devid,int seq);

int count_times_of_holiday(int holiday_id,int *count);

int get_curr_card_by_custid(int custid,T_t_pif_card *card);

int add_new_door_week_tbl(T_t_door_dev_week_tbl *week_tbl,int maxcnt);
int add_new_door_time_sect_tbl(T_t_door_dev_timesect_tbl *time_tbl,int maxcnt);
int add_new_door_time_group_tbl(T_t_door_dev_time_group_tbl *tg_tbl,int maxcnt);
int add_new_door_holiday_tbl(T_t_door_dev_holiday_tbl *holiday_tbl,int maxcnt);

int get_door_dev_by_parent_and_termid(T_t_pif_device *device,int parent_id,int termid);
int get_card_by_phyno(T_t_pif_card *card,const char *phyno);
int Db_t_tif_rcvdtl_backup();
int Db_t_tif_rcvdtl_del_all_by_step_commit();
int Get_Credit_and_Debit_Balance(char begin_date[8+1],char end_date[8+1],double *debit_fee,double *credit_fee);

int get_max_cust_vol(int cust_id,char max_vol[13]);

int find_device_by_sys_termno(int sys_id,int term_no,int *dev_id);


int dynamic_execute_sql(const char *sqlstr,int *count);
int rakeoff_transfer_day(int shop_id);
int agio_transfer_month(int shop_id,double month_rake_balance,double  month_sum_balance);
int GetSumShopBalanceMonth(char *begin_date,char *end_date,int shop_id,double *rake_sum,double *total_sum);
int get_before_month_with_day(char *in_date,char *out_date);
int GetCountSubsidyByNotEquStatus(int *count,char *status,char *batch_no);
int GetFirstSubsidybycustnoandstatus(int v_cust_no,int card_no,int card_sidy_no,char *v_status,T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_tradeserial_next_flush(T_t_tif_tradeserial *pt_tif_tradeserial);
int DB_t_tif_tradeserial_done_flush(T_t_tif_tradeserial* ptradeserial);
int device_login_yes_or_no(int device_id);
int judge_with_max_subsidy_no_within_new(int subsidy_no);
int get_batch_no_by_subsidy_no(int subsidy_no,char *batch_no);
int get_card_no_by_physical_no(int *card_id,char *phycardno);
int DelTxdtlData();
int gen_report_tradelog_grouping(char *logic_date);
int gen_report_school_trade(char *logic_date);

int check_card_pwd_by_card(int card_id,const char *pwd);

int find_cutid_by_outsideno(int *cut_id,char *outside_no,int outside_type);
/**
 \breif 从sequence 中读取下一个ID 号
 \param seq_key - 表示表名, sequence 名为S_  + 表名
 \param seq_val - 读取的sequence 值
 \return 0 表示成功 , 失败返回错误码
 */
#ifdef ESQL_ORA
int ora_gen_sequence(const char *seq_key,int *seq_val);
#elif defined ESQL_DB2
#define ora_gen_sequence(seq_key,seq_val)  (0)
#endif

#ifdef __cplusplus
}
#endif

#endif // _DBFUNC_FOO_H_
