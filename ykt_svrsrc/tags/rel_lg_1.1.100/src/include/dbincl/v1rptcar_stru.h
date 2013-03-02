#ifndef  __T_v1rptcar_H_
#define  __T_v1rptcar_H_
typedef struct 
{
		char	account_id[16+1];
		int	card_id;
		int	customer_id;
		char	cut_name[60+1];
		char	stuemp_no[20+1];
		int	card_type;
		char	classdept_no[20+1];
		double	db_bala;
		double	card_bala;
		int	nobala_num;
		double	diff_bala;
}T_v_tif_report_carddb_nobalance;
int DB_v_tif_report_carddb_nobalance_open_select_by_c1();
int DB_v_tif_report_carddb_nobalance_fetch_select_by_c1(T_v_tif_report_carddb_nobalance *pv_tif_report_carddb_nobalance);
int DB_v_tif_report_carddb_nobalance_close_select_by_c1();
#endif
