#ifndef  __T_doorholiday_H_
#define  __T_doorholiday_H_
typedef struct 
{
		int	holiday_id;
		char	holiday_name[60+1];
		char	start_date[8+1];
		char	end_date[8+1];
		char	start_time[6+1];
		char	end_time[6+1];
		int	ref_cnt;
		int	day_count;
}T_t_door_holiday;
int DB_t_door_holiday_add(T_t_door_holiday *pt_door_holiday);
int DB_t_door_holiday_read_by_holiday_name(char *v_holiday_name,T_t_door_holiday *pt_door_holiday);
int DB_t_door_holiday_read_by_holiday_id(int v_holiday_id,T_t_door_holiday *pt_door_holiday);
int DB_t_door_holiday_del_by_holiday_name(char *v_holiday_name);
int DB_t_door_holiday_del_by_holiday_id(int v_holiday_id);
int DB_t_door_holiday_read_lock_by_cur_and_holiday_id(int v_holiday_id,T_t_door_holiday *pt_door_holiday);
int DB_t_door_holiday_update_lock_by_cur(T_t_door_holiday *pt_door_holiday);
int DB_t_door_holiday_free_lock_cur();
#endif
