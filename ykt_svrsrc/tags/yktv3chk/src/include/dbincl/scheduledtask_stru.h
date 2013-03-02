#ifndef  __T_scheduledtask_H_
#define  __T_scheduledtask_H_
typedef struct 
{
		int	taskno;
		char	summary[240+1];
		char	progname[60+1];
		char	progpath[240+1];
		char	progargv[240+1];
		int	dialy;
		int	weekly;
		int	monthly;
		char	starttime[6+1];
		char	endtime[6+1];
		char	useflag[1+1];
}T_t_scheduledtask;
int DB_t_scheduledtask_add(T_t_scheduledtask *pt_scheduledtask);
int DB_t_scheduledtask_read_by_taskno(int v_taskno,T_t_scheduledtask *pt_scheduledtask);
int DB_t_scheduledtask_update_by_taskno(int v_taskno,T_t_scheduledtask *pt_scheduledtask);
int DB_t_scheduledtask_del_by_taskno(int v_taskno);
int DB_t_scheduledtask_read_lock_by_c0_and_taskno(int v_taskno,T_t_scheduledtask *pt_scheduledtask);
int DB_t_scheduledtask_update_lock_by_c0(T_t_scheduledtask *pt_scheduledtask);
int DB_t_scheduledtask_free_lock_by_c0();
#endif
