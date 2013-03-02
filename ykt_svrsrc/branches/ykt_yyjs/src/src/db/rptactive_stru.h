#ifndef  __T_rptactive_H_
#define  __T_rptactive_H_
typedef struct 
{
		char	balance_date[10+1];
		int	seri_type;
		int	trade_number;
		double	trade_amt;
		int	acc_addnum;
		double	acc_amt;
		int	shop_addnum;
		double	shop_amt;
		double	dep_amt;
		double	earn_amt;
		double	mng_amt;
		double	cost_amt;
		double	ensure_amt;
		double	bank_amt;
		double	cash_amt;
		char	operator_code[10+1];
		char	data_sign[8+1];
		char	reserve1[20+1];
		char	reserve2[20+1];
		double	check_add_amt;
		double	outlay_add_amt;
		double	down_subsidy_amt;
		double	up_subsidy_amt;
}T_t_tif_report_active;
int DB_t_tif_report_active_add(T_t_tif_report_active *pt_tif_report_active);
int DB_t_tif_report_active_del_by_balance_date(char *v_balance_date);
int DB_t_tif_report_active_read_by_balance_date_and_seri_type(char *v_balance_date,int v_seri_type,T_t_tif_report_active *pt_tif_report_active);
int DB_t_tif_report_active_open_select_between_c1_and_balance_date_and_balance_date(char *v_balance_date_2,char *v_balance_date_3);
int DB_t_tif_report_active_fetch_select_by_c1(T_t_tif_report_active *pt_tif_report_active);
int DB_t_tif_report_active_close_select_by_c1();
#endif
