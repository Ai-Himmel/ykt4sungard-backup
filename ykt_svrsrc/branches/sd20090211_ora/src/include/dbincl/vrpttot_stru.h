#ifndef  __T_vrpttot_H_
#define  __T_vrpttot_H_
typedef struct 
{
		int	total;
}T_v_tif_report_totalacc;
int DB_v_tif_report_totalacc_open_select_by_c1();
int DB_v_tif_report_totalacc_fetch_select_by_c1(T_v_tif_report_totalacc *pv_tif_report_totalacc);
int DB_v_tif_report_totalacc_close_select_by_c1();
#endif
