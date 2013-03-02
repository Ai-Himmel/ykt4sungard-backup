#ifndef  __T_drtimsec_H_
#define  __T_drtimsec_H_
typedef struct 
{
		int	sid;
		char	sname[60+1];
		char	begin_time[6+1];
		char	end_time[6+1];
		int	flag;
		char	last_update[14+1];
}T_t_door_time_sect;
int DB_t_door_time_sect_add(T_t_door_time_sect *pt_door_time_sect);
int DB_t_door_time_sect_update_by_sid(int v_sid,T_t_door_time_sect *pt_door_time_sect);
int DB_t_door_time_sect_read_by_sid(int v_sid,T_t_door_time_sect *pt_door_time_sect);
int DB_t_door_time_sect_open_select_by_cur0();
int DB_t_door_time_sect_fetch_select_by_cur0(T_t_door_time_sect *pt_door_time_sect);
int DB_t_door_time_sect_close_select_by_cur0();
#endif
