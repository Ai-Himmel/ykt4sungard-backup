#ifndef  __T_doordevhld_H_
#define  __T_doordevhld_H_
typedef struct 
{
		char	holiday_name[60+1];
		char	device_id[8+1];
		char	start_date[8+1];
		char	end_date[8+1];
		char	start_time[6+1];
		char	end_time[6+1];
		char	version[12+1];
		char	send_flag[1+1];
		int	day_count;
}T_t_door_device_holiday;
int DB_t_door_device_holiday_add(T_t_door_device_holiday *pt_door_device_holiday);
int DB_t_door_device_holiday_read_by_device_id(char *v_device_id,T_t_door_device_holiday *pt_door_device_holiday);
int DB_t_door_device_holiday_read_by_device_id_and_holiday_name(char *v_device_id,char *v_holiday_name,T_t_door_device_holiday *pt_door_device_holiday);
int DB_t_door_device_holiday_del_by_device_id_and_holiday_name(char *v_device_id,char *v_holiday_name);
int DB_t_door_device_holiday_open_select_by_cur0_and_device_id(char *v_device_id);
int DB_t_door_device_holiday_fetch_select_by_cur0(T_t_door_device_holiday *pt_door_device_holiday);
int DB_t_door_device_holiday_close_select_by_cur0();
#endif
