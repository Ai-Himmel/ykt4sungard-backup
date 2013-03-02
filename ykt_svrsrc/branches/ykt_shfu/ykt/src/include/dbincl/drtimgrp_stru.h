#ifndef  __T_drtimgrp_H_
#define  __T_drtimgrp_H_
typedef struct 
{
		int	tgid;
		char	tgname[60+1];
		int	time1_id;
		int	time2_id;
		int	time3_id;
		int	time4_id;
		int	time5_id;
		int	time6_id;
		int	time7_id;
		int	time8_id;
		int	flag;
		char	update_time[14+1];
}T_t_door_times_group;
int DB_t_door_times_group_add(T_t_door_times_group *pt_door_times_group);
int DB_t_door_times_group_read_by_tgid(int v_tgid,T_t_door_times_group *pt_door_times_group);
int DB_t_door_times_group_update_by_tgid(int v_tgid,T_t_door_times_group *pt_door_times_group);
int DB_t_door_times_group_del_by_tgid(int v_tgid);
#endif
