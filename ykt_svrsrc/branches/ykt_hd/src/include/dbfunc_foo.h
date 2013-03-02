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



/////////////////////////////////////////////////////////////////
/// 会议签到使用的函数
int GetConferenceIDByDev(T_t_door_txdtl* tTxdtl,int *conf);
int SaveConferenceSerial(T_t_door_txdtl* tTxdtl,int conf,int custid);

#ifdef __cplusplus
}
#endif

#endif // _DBFUNC_FOO_H_
