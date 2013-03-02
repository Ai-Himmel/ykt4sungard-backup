#ifndef  __T_rptcardbalance_H_
#define  __T_rptcardbalance_H_
typedef struct 
{
		char	balance_date[10+1];
		char	account_id[16+1];
		int	cardno;
		char	cut_name[60+1];
		char	stuemp_no[20+1];
		int	type_id;
		char	dept_name[100+1];
		double	db_bala;
		double	card_bala;
		int	nobala_num;
		double	diff_bala;
		char	data_sign[8+1];
		char	reserve1[20+1];
		char	reserve2[20+1];
}T_t_tif_report_carddb_nobalance;
int DB_t_tif_report_carddb_nobalance_add(T_t_tif_report_carddb_nobalance *pt_tif_report_carddb_nobalance);
int DB_t_tif_report_carddb_nobalance_del_by_balance_date(char *v_balance_date);
int DB_t_tif_report_carddb_nobalance_open_select_between_c1_and_balance_date_and_balance_date(char *v_balance_date_2,char *v_balance_date_3);
int DB_t_tif_report_carddb_nobalance_fetch_select_by_c1(T_t_tif_report_carddb_nobalance *pt_tif_report_carddb_nobalance);
int DB_t_tif_report_carddb_nobalance_close_select_by_c1();
#endif
