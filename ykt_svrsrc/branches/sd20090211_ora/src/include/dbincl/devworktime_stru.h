#ifndef  __T_devworktime_H_
#define  __T_devworktime_H_
typedef struct 
{
		char	device_id[8+1];
		int	week;
		int	seqno;
		char	card_type[64+1];
		char	start_time[6+1];
		char	end_time[6+1];
		char	version[12+1];
		char	send_flag[1+1];
}T_t_door_device_worktime;
int DB_t_door_device_worktime_add(T_t_door_device_worktime *pt_door_device_worktime);
int DB_t_door_device_worktime_read_by_device_id_and_week(char *v_device_id,int v_week,T_t_door_device_worktime *pt_door_device_worktime);
int DB_t_door_device_worktime_del_by_device_id_and_week(char *v_device_id,int v_week);
int DB_t_door_device_worktime_del_by_device_id_and_week_and_seqno(char *v_device_id,int v_week,int v_seqno);
int DB_t_door_device_worktime_read_lock_by_cur_and_device_id_and_week_and_seqno(char *v_device_id,int v_week,int v_seqno,T_t_door_device_worktime *pt_door_device_worktime);
int DB_t_door_device_worktime_update_lock_by_cur(T_t_door_device_worktime *pt_door_device_worktime);
int DB_t_door_device_worktime_free_lock_cur();
int DB_t_door_device_worktime_open_select_by_cur1_and_device_id_and_week(char *v_device_id,int v_week);
int DB_t_door_device_worktime_fetch_select_by_cur1(T_t_door_device_worktime *pt_door_device_worktime);
int DB_t_door_device_worktime_close_select_by_cur1();
int DB_t_door_device_worktime_read_lock_by_cur2_and_device_id_and_week_and_start_time(char *v_device_id,int v_week,char *v_start_time,T_t_door_device_worktime *pt_door_device_worktime);
int DB_t_door_device_worktime_update_lock_by_cur2(T_t_door_device_worktime *pt_door_device_worktime);
int DB_t_door_device_worktime_free_lock_cur2();
#endif
