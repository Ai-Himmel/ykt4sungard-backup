#ifndef  __T_doorweek_H_
#define  __T_doorweek_H_
typedef struct 
{
		int	wid;
		char	week_name[60+1];
		int	flag;
		char	last_update[14+1];
		int	day1_id;
		int	day2_id;
		int	day3_id;
		int	day4_id;
		int	day5_id;
		int	day6_id;
		int	day7_id;
}T_t_door_weeks;
int DB_t_door_weeks_add(T_t_door_weeks *pt_door_weeks);
int DB_t_door_weeks_read_by_wid(int v_wid,T_t_door_weeks *pt_door_weeks);
int DB_t_door_weeks_update_by_wid(int v_wid,T_t_door_weeks *pt_door_weeks);
int DB_t_door_weeks_del_by_wid(int v_wid);
#endif
