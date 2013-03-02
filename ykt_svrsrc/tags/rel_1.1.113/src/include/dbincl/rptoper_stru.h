#ifndef  __T_rptoper_H_
#define  __T_rptoper_H_
typedef struct 
{
		char	balance_date[10+1];
		char	operator_code[10+1];
		int	seri_type;
		int	maindevice_id;
		int	device_id;
		int	happen_num;
		double	happen_amt;
		double	mng_amt;
		double	ensure_amt;
		double	cost_amt;
		double	dep_amt;
		double	earn_amt;
		double	bank_amt;
		double	cash_amt;
		char	data_sign[8+1];
		char	reserve1[20+1];
		char	reserve2[20+1];
		double	acc_add_amt;
		double	shp_add_amt;
		double	check_amt;
		double	outlay_amt;
		double	down_subsidy_amt;
		double	up_subsidy_amt;
}T_t_tif_report_oper;
int DB_t_tif_report_oper_add(T_t_tif_report_oper *pt_tif_report_oper);
int DB_t_tif_report_oper_del_by_balance_date(char *v_balance_date);
int DB_t_tif_report_oper_open_select_between_c1_and_balance_date_and_balance_date(char *v_balance_date_2,char *v_balance_date_3);
int DB_t_tif_report_oper_fetch_select_by_c1(T_t_tif_report_oper *pt_tif_report_oper);
int DB_t_tif_report_oper_close_select_by_c1();
#endif
