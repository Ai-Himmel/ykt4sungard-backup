#include "dbfunc.h"

#ifdef __cplusplus
extern "C" {
#endif


int DB_t_tif_tradeserial_next_flush(T_t_tif_tradeserial* ptradeserial);
int DB_t_tif_tradeserial_done_flush(T_t_tif_tradeserial* ptradeserial);
int DB_v_tif_shopdeptfee_read_sum_fee(int* pCount,double* pAmt);
int DB_his_t_tif_tradeserial_get_count_by_serial_type(double *count,int serial_type,char *logicdate);
int DB_his_t_tif_tradeserial_get_sum_by_serial_type(double *SumMoney,int serial_type,char *logicdate);
int DB_t_tif_tradeserial_get_count_by_serial_type(double *count,int serial_type);
int DB_t_tif_tradeserial_get_sum_by_serial_type(double *SumMoney,int serial_type);

#ifdef __cplusplus
}
#endif

