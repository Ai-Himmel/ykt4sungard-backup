#ifndef  __T_scheduledtasklog_H_
#define  __T_scheduledtasklog_H_
typedef struct 
{
		char	transdate[8+1];
		char	starttime[6+1];
		int	taskno;
		char	progname[60+1];
		char	endtime[30+1];
		char	runstatus[1+1];
		char	summary[240+1];
}T_t_scheduledtasklog;
int DB_t_scheduledtasklog_add(T_t_scheduledtasklog *pt_scheduledtasklog);
int DB_t_scheduledtasklog_read_by_transdate_and_starttime_and_taskno(char *v_transdate,char *v_starttime,int v_taskno,T_t_scheduledtasklog *pt_scheduledtasklog);
int DB_t_scheduledtasklog_update_by_transdate_and_starttime_and_taskno(char *v_transdate,char *v_starttime,int v_taskno,T_t_scheduledtasklog *pt_scheduledtasklog);
int DB_t_scheduledtasklog_del_by_transdate_and_starttime_and_taskno(char *v_transdate,char *v_starttime,int v_taskno);
int DB_t_scheduledtasklog_read_lock_by_c0_and_transdate_and_starttime_and_taskno(char *v_transdate,char *v_starttime,int v_taskno,T_t_scheduledtasklog *pt_scheduledtasklog);
int DB_t_scheduledtasklog_update_lock_by_c0(T_t_scheduledtasklog *pt_scheduledtasklog);
int DB_t_scheduledtasklog_free_lock_by_c0();
#endif
