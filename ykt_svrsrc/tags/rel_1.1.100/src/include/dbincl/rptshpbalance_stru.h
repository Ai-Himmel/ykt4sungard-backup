#ifndef  __T_rptshpbalance_H_
#define  __T_rptshpbalance_H_
typedef struct 
{
		char	balance_date[10+1];
		int	shop_id;
		char	shop_name[50+1];
		int	dept_id;
		int	trade_num;
		double	trade_amt;
		double	mng_amt;
		double	total_amt;
		char	data_sign[8+1];
		char	reserve1[20+1];
		char	reserve2[20+1];
}T_t_tif_report_shop_balance;
int DB_t_tif_report_shop_balance_add(T_t_tif_report_shop_balance *pt_tif_report_shop_balance);
int DB_t_tif_report_shop_balance_del_by_balance_date(char *v_balance_date);
int DB_t_tif_report_shop_balance_open_select_between_c1_and_balance_date_and_balance_date(char *v_balance_date_2,char *v_balance_date_3);
int DB_t_tif_report_shop_balance_fetch_select_by_c1(T_t_tif_report_shop_balance *pt_tif_report_shop_balance);
int DB_t_tif_report_shop_balance_close_select_by_c1();
#endif
