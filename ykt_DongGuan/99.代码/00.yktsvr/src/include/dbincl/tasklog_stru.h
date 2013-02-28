#ifndef  __T_tasklog_H_
#define  __T_tasklog_H_
typedef struct 
{
		char	transdate[8+1];
		char	starttime[6+1];
		int	taskno;
		char	progname[60+1];
		char	endtime[30+1];
		char	runstatus[1+1];
		char	summary[240+1];
}T_t_plantasklog;
int DB_t_plantasklog_add(T_t_plantasklog *pt_plantasklog);
int DB_t_plantasklog_read_by_transdate_and_starttime_and_taskno(const char *v_transdate,const char *v_starttime,int v_taskno,T_t_plantasklog *pt_plantasklog);
int DB_t_plantasklog_update_by_transdate_and_starttime_and_taskno(char *v_transdate,char *v_starttime,int v_taskno,T_t_plantasklog *pt_plantasklog);
int DB_t_plantasklog_del_by_transdate_and_starttime_and_taskno(const char *v_transdate,const char *v_starttime,int v_taskno);
int DB_t_plantasklog_read_lock_by_c0_and_transdate_and_starttime_and_taskno(const char *v_transdate,const char *v_starttime,int v_taskno,T_t_plantasklog *pt_plantasklog);
int DB_t_plantasklog_update_lock_by_c0(T_t_plantasklog *pt_plantasklog);
int DB_t_plantasklog_free_lock_by_c0();
#endif
