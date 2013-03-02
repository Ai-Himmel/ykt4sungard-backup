#ifndef  __T_drweektime_H_
#define  __T_drweektime_H_
typedef struct 
{
		int	weekid;
		char	weekname[60+1];
		int	day1timegrpid;
		int	day2timegrpid;
		int	day3timegrpid;
		int	day4timegrpid;
		int	day5timegrpid;
		int	day6timegrpid;
		int	day7timegrpid;
		int	adddelflag;
		int	downstatus;
		char	updatetime[30+1];
}T_t_doorweektime;
int DB_t_doorweektime_add(T_t_doorweektime *pt_doorweektime);
int DB_t_doorweektime_read_by_weekid(int v_weekid,T_t_doorweektime *pt_doorweektime);
int DB_t_doorweektime_update_by_weekid(int v_weekid,T_t_doorweektime *pt_doorweektime);
int DB_t_doorweektime_del_by_weekid(int v_weekid);
int DB_t_doorweektime_read_lock_by_c0_and_weekid(int v_weekid,T_t_doorweektime *pt_doorweektime);
int DB_t_doorweektime_update_lock_by_c0(T_t_doorweektime *pt_doorweektime);
int DB_t_doorweektime_free_lock_by_c0();
#endif
