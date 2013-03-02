#ifndef  __T_drhldtim_H_
#define  __T_drhldtim_H_
typedef struct 
{
		int	hid;
		char	h_date[8+1];
		int	time_grp_id;
		int	flag;
		char	last_update[14+1];
}T_t_door_holiday_times;
int DB_t_door_holiday_times_add(T_t_door_holiday_times *pt_door_holiday_times);
int DB_t_door_holiday_times_read_by_hid_and_h_date(int v_hid,char *v_h_date,T_t_door_holiday_times *pt_door_holiday_times);
int DB_t_door_holiday_times_del_by_hid(int v_hid);
int DB_t_door_holiday_times_update_by_hid_and_h_date(int v_hid,char *v_h_date,T_t_door_holiday_times *pt_door_holiday_times);
int DB_t_door_holiday_times_open_select_by_c0_and_hid(int v_hid);
int DB_t_door_holiday_times_fetch_select_by_c0(T_t_door_holiday_times *pt_door_holiday_times);
int DB_t_door_holiday_times_close_select_by_c0();
#endif
