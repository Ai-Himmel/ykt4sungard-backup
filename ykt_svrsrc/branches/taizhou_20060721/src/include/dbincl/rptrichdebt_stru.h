#ifndef  __T_rptrichdebt_H_
#define  __T_rptrichdebt_H_
typedef struct 
{
		char	balance_date[10+1];
		int	sub_code;
		char	sub_name[50+1];
		int	sub_type;
		double	last_bala;
		double	cur_bala;
		double	change_amt;
		char	date_sign[8+1];
		char	reserve1[20+1];
		char	reserve2[20+1];
}T_t_tif_report_rich_debt;
int DB_t_tif_report_rich_debt_add(T_t_tif_report_rich_debt *pt_tif_report_rich_debt);
int DB_t_tif_report_rich_debt_del_by_balance_date(char *v_balance_date);
int DB_t_tif_report_rich_debt_open_select_between_c1_and_balance_date_and_balance_date(char *v_balance_date_2,char *v_balance_date_3);
int DB_t_tif_report_rich_debt_fetch_select_by_c1(T_t_tif_report_rich_debt *pt_tif_report_rich_debt);
int DB_t_tif_report_rich_debt_close_select_by_c1();
#endif
