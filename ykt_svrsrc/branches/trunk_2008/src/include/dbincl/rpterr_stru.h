#ifndef  __T_rpterr_H_
#define  __T_rpterr_H_
typedef struct 
{
		char	balance_date[10+1];
		char	account_id[16+1];
		char	cut_name[60+1];
		char	stuemp_no[20+1];
		int	type_id;
		char	dept_name[100+1];
		double	last_bala;
		double	cur_bala;
		double	trade_amt;
		double	diff_bala;
		char	data_sign[8+1];
		char	reserve1[20+1];
		char	reserve2[20+1];
}T_t_tif_report_erracc;
int DB_t_tif_report_erracc_add(T_t_tif_report_erracc *pt_tif_report_erracc);
int DB_t_tif_report_erracc_del_by_balance_date(char *v_balance_date);
int DB_t_tif_report_erracc_open_select_between_c1_and_balance_date_and_balance_date(char *v_balance_date_2,char *v_balance_date_3);
int DB_t_tif_report_erracc_fetch_select_by_c1(T_t_tif_report_erracc *pt_tif_report_erracc);
int DB_t_tif_report_erracc_close_select_by_c1();
#endif
