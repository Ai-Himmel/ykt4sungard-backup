#ifndef _DBFUNC_FOO_H_
#define _DBFUNC_FOO_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "pubdb.h"
#include "cpack.h"

#ifndef CHECK_DB_ERR
#define CHECK_DB_ERR db_chk_err(__FILE__,__LINE__,&sqlca)
#endif

int process930105(char * devid,int week);
int process930117NoDel(T_t_door_device_cardlist *cardlist,int addflag);
int Get_card_next_serial(int card_id,char *tx_date,int total_cnt,double *in_bala,double *out_bala);
int CheckGatewayDynKey(int sysid,char * dynKey);
int GetDevUsageByDevId(char * devid,int *usage);
int GetDevUsageById(int id,int *usage);
int GetDeviceByDevId(char * devid,T_t_pif_device * device);



/////////////////////////////////////////////////////////////////
/// 会议签到使用的函数
int GetConferenceIDByDev(T_t_door_txdtl* tTxdtl,int *conf,char sign[3]);
int SaveConferenceSerial(T_t_door_txdtl* tTxdtl,int conf,int custid,char sign[3]);

////////////////////////////////////////////////////////////////////
///考勤系统使用到的函数
int SaveKQSerial(T_t_door_txdtl* tTxdtl);

int get_cutid_by_show_card_no(const char * showno,int * cutid);

double get_totalFundBookMoney_by_card_no(int card_no,char beginmonth[5],char enddate[9]);
int rakeoff_transfer_day(int shop_id);

#ifdef __cplusplus
}
#endif

#endif // _DBFUNC_FOO_H_
