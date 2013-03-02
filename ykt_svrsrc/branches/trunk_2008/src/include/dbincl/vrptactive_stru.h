#ifndef  __T_vrptactive_H_
#define  __T_vrptactive_H_
typedef struct 
{
		int	serial_type;
		int	trade_count;
		int	acc_add_num;
		double	acc_add_amt;
		int	shp_add_num;
		double	shp_add_amt;
		double	dep_add_amt;
		double	earn_add_amt;
		double	in_amt;
		double	deposit_amt;
		double	cost_amt;
		double	bank_add_amt;
		double	cash_add_amt;
		double	check_add_amt;
		double	outlay_add_amt;
		double	down_subsidy_amt;
		double	up_subsidy_amt;
}T_v_tif_report_active;
int DB_v_tif_report_active_open_select_by_cur1();
int DB_v_tif_report_active_fetch_select_by_cur1(T_v_tif_report_active *pv_tif_report_active);
int DB_v_tif_report_active_close_select_by_cur1();
#endif
