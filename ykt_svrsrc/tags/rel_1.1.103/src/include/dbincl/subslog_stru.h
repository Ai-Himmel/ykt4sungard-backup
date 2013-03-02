#ifndef  __T_subslog_H_
#define  __T_subslog_H_
typedef struct 
{
		int	cust_id;
		char	login_name[50+1];
		char	log_date[8+1];
		char	log_time[6+1];
		int	flag;
		int	sussys_id;
		char	comments[255+1];
}T_t_subsys_log;
int DB_t_subsys_log_add(T_t_subsys_log *pt_subsys_log);
#endif
