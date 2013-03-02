#ifndef  __T_registerpaylog_H_
#define  __T_registerpaylog_H_
typedef struct 
{
		char	stuemp_no[20+1];
		char	cut_name[60+1];
		int	register_flag;
		char	register_info[60+1];
		char	operate_date[10+1];
		char	operate_time[8+1];
		int	flag;
		int	reserver_no1;
		char	system_no[10+1];
		char	modify_date[10+1];
		char	modify_time[8+1];
		int	last_register_flag;
		int	reg_id;
}T_t_tif_register_pay_log;
int DB_t_tif_register_pay_log_add(T_t_tif_register_pay_log *pt_tif_register_pay_log);
int DB_t_tif_register_pay_log_read_by_register_flag(int v_register_flag,T_t_tif_register_pay_log *pt_tif_register_pay_log);
#endif
