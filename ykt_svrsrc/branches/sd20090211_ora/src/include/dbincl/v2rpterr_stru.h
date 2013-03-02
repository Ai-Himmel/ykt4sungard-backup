#ifndef  __T_v2rpterr_H_
#define  __T_v2rpterr_H_
typedef struct 
{
		char	account_id[16+1];
		char	cut_name[60+1];
		char	stuemp_no[20+1];
		int	card_type;
		double	last_bala;
		double	cur_bala;
		double	sum_trade;
}T_v_tif_report_erracc;
int DB_v_tif_report_erracc_open_select_by_c1();
int DB_v_tif_report_erracc_fetch_select_by_c1(T_v_tif_report_erracc *pv_tif_report_erracc);
int DB_v_tif_report_erracc_close_select_by_c1();
#endif
