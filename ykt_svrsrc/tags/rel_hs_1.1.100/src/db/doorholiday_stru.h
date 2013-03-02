#ifndef  __T_doorholiday_H_
#define  __T_doorholiday_H_
typedef struct 
{
		int	holiday_id;
		char	holiday_name[150+1];
		int	flag;
		char	last_update[14+1];
		int	day_cnt;
}T_t_door_holiday;
int DB_t_door_holiday_add(T_t_door_holiday *pt_door_holiday);
int DB_t_door_holiday_read_by_holiday_id(int v_holiday_id,T_t_door_holiday *pt_door_holiday);
int DB_t_door_holiday_update_by_holiday_id(int v_holiday_id,T_t_door_holiday *pt_door_holiday);
#endif
