#ifndef  __T_mecperrep_H_
#define  __T_mecperrep_H_
typedef struct 
{
		int	cut_id;
		char	rep_date[8+1];
		double	pre_money;
		double	cur_money;
}T_t_mec_per_daily_report;
int DB_t_mec_per_daily_report_read_lock_by_c1_and_cut_id(int v_cut_id,T_t_mec_per_daily_report *pt_mec_per_daily_report);
int DB_t_mec_per_daily_report_update_lock_by_c1(T_t_mec_per_daily_report *pt_mec_per_daily_report);
int DB_t_mec_per_daily_report_free_lock_c1();
int DB_t_mec_per_daily_report_add(T_t_mec_per_daily_report *pt_mec_per_daily_report);
#endif
