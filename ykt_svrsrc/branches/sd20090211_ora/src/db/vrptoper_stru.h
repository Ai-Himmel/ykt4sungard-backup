#ifndef  __T_vrptoper_H_
#define  __T_vrptoper_H_
typedef struct 
{
		int	serial_type;
		int	trade_count;
		int	maindevice_id;
		int	device_id;
		char	oper_code[10+1];
		double	trade_amt;
		double	acc_add_amt;
		double	shp_add_amt;
		double	dep_add_amt;
		double	earn_add_amt;
		double	bank_add_amt;
		double	deposit_amt;
		double	in_amt;
		double	cost_amt;
		double	cash_amt;
		double	check_amt;
		double	outlay_amt;
		double	down_subsidy_amt;
		double	up_subsidy_amt;
}T_v_tif_report_oper;
int DB_v_tif_report_oper_open_select_by_c1();
int DB_v_tif_report_oper_fetch_select_by_c1(T_v_tif_report_oper *pv_tif_report_oper);
int DB_v_tif_report_oper_close_select_by_c1();
#endif
