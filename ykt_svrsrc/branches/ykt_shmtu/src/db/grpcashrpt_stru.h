#ifndef  __T_grpcashrpt_H_
#define  __T_grpcashrpt_H_
typedef struct 
{
		char	group_id[10+1];
		double	pre_money;
		double	cur_money;
		char	upd_date[8+1];
		char	last_check_date[8+1];
		char	last_check_time[6+1];
}T_t_group_cash_report;
int DB_t_group_cash_report_add(T_t_group_cash_report *pt_group_cash_report);
int DB_t_group_cash_report_read_by_group_id(char *v_group_id,T_t_group_cash_report *pt_group_cash_report);
int DB_t_group_cash_report_read_lock_by_c1_and_group_id(char *v_group_id,T_t_group_cash_report *pt_group_cash_report);
int DB_t_group_cash_report_update_lock_by_c1(T_t_group_cash_report *pt_group_cash_report);
int DB_t_group_cash_report_free_lock_by_c1();
int DB_t_group_cash_report_open_select_for_update_by_cur2();
int DB_t_group_cash_report_fetch_select_by_cur2(T_t_group_cash_report *pt_group_cash_report);
int DB_t_group_cash_report_update_lock_by_cur2(T_t_group_cash_report *pt_group_cash_report);
int DB_t_group_cash_report_close_select_by_cur2();
#endif
