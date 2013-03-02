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

// 下载时间段到汉军门禁机中
typedef struct{
	int major_dev_id;
	int minor_dev_id;
	int task_dev_id;
	int max_count_of_week;
	int max_count_of_day;
	int max_count_of_holiday;
	int day_seqno;
	int need_reload;
}hndr_check_dev_info_t;

typedef int (*hundure_add_930107_func)(hndr_check_dev_info_t *dev,int dayid);
typedef int (*hundure_add_930105_func)(hndr_check_dev_info_t *dev,int week_id);

//门禁时间段
typedef struct{
	char begin_time[5];			// hhmm
	char end_time[5];			//hhmm
	int  time_level;				// 1:上班时段，2:非上班时段
}TIMESEC;							

int do_gcu3_add_930107(hndr_check_dev_info_t *dev,int timeid);
int do_rac2000_add_930107(hndr_check_dev_info_t *dev,int timeid);
int do_hundure_add_930105(hndr_check_dev_info_t * dev,int week_id,hundure_add_930107_func pfunc_add_930107);

int do_soyal_add_930105(int major_devid,int week_id);
int do_0121_add_930105(int major_devid,int week_id);
int process930105(int devid,int week);
int process930105S(int devid,char *incontent);
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

int add_new_door_week_tbl(T_t_door_dev_week_tbl *week_tbl,int maxcnt,int mul=1,int count=0);
int add_new_door_time_sect_tbl(T_t_door_dev_timesect_tbl *time_tbl,int maxcnt);
int add_new_door_time_group_tbl(T_t_door_dev_time_group_tbl *tg_tbl,int maxcnt);
int add_new_door_holiday_tbl(T_t_door_dev_holiday_tbl *holiday_tbl,int maxcnt);

int get_door_dev_by_parent_and_termid(T_t_pif_device *device,int parent_id,int termid);
int find_device_by_parent_termid(T_t_pif_device *device,int parent_termid,int termid,int phytype);
int find_device_by_devinfo(T_t_pif_device *device,int sysid,int termid,const char *devtype,int phytype);
int get_card_by_phyno(T_t_pif_card *card,const char *phyno);
int Db_t_tif_rcvdtl_backup();
int Db_t_tif_rcvdtl_del_all_by_step_commit();
int Get_Credit_and_Debit_Balance(char begin_date[8+1],char end_date[8+1],double *debit_fee,double *credit_fee);
int DB_t_tif_tradeserial_next_flush(T_t_tif_tradeserial *pt_tif_tradeserial);
int DB_t_tif_tradeserial_done_flush(T_t_tif_tradeserial* ptradeserial);
int device_login_yes_or_no(int device_id);

int get_max_cust_vol(int cust_id,char max_vol[13]);


int dynamic_execute_sql(const char *sqlstr,int *count);
int device_login_yes_or_no(int device_id);
int get_card_no_by_physical_no(int *card_id,char *phycardno);
int check_card_pwd_by_card(int card_id,const char *pwd);
int get_card_by_weigand_no(T_t_pif_card *card,const char *weigand_no);
int GetCountSubsidyByNotEquStatus(int *count,char *status,char *batch_no);
int get_batch_no_by_subsidy_no(int subsidy_no,char *batch_no);
int judge_with_max_subsidy_no_within_new(int subsidy_no);
int CreateShopReport_01();


int getTurnOverFeebyStuempNO(char *stuempNo,double *outFee);
int updateBminfoByStuempNo(char *stuempNo);
int updateBMStudentPayStatus(char *stuempNo);



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
