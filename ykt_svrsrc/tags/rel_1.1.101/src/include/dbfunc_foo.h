#ifndef _DBFUNC_FOO_H_
#define _DBFUNC_FOO_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "pubdb.h"
#include "cpack.h"

int process930105(char * devid,int week);
int process930117NoDel(T_t_door_device_cardlist *cardlist,int addflag);
int Get_card_next_serial(int card_id,char *tx_date,int total_cnt,double *in_bala,double *out_bala);

#ifdef __cplusplus
}
#endif

#endif // _DBFUNC_FOO_H_
