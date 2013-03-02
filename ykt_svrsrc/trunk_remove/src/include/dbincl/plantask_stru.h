#ifndef  __T_plantask_H_
#define  __T_plantask_H_
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
}T_t_plantask;
int DB_t_plantask_add(T_t_plantask *pt_plantask);
int DB_t_plantask_read_by_taskno(int v_taskno,T_t_plantask *pt_plantask);
int DB_t_plantask_update_by_taskno(int v_taskno,T_t_plantask *pt_plantask);
int DB_t_plantask_del_by_taskno(int v_taskno);
int DB_t_plantask_read_lock_by_c0_and_taskno(int v_taskno,T_t_plantask *pt_plantask);
int DB_t_plantask_update_lock_by_c0(T_t_plantask *pt_plantask);
int DB_t_plantask_free_lock_by_c0();
#endif
