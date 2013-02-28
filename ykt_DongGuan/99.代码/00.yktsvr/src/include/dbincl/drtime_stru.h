#ifndef  __T_drtime_H_
#define  __T_drtime_H_
typedef struct 
{
		int	timeid;
		char	timename[60+1];
		char	starttime[6+1];
		char	endtime[6+1];
		int	adddelflag;
		int	downstatus;
		char	updatetime[30+1];
}T_t_doortime;
int DB_t_doortime_add(T_t_doortime *pt_doortime);
int DB_t_doortime_read_by_timeid(int v_timeid,T_t_doortime *pt_doortime);
int DB_t_doortime_update_by_timeid(int v_timeid,T_t_doortime *pt_doortime);
int DB_t_doortime_del_by_timeid(int v_timeid);
int DB_t_doortime_read_lock_by_c0_and_timeid(int v_timeid,T_t_doortime *pt_doortime);
int DB_t_doortime_update_lock_by_c0(T_t_doortime *pt_doortime);
int DB_t_doortime_free_lock_by_c0();
#endif
