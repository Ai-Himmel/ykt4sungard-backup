#ifndef  __T_drevent_H_
#define  __T_drevent_H_
typedef struct 
{
		int	device_id;
		int	event_code;
		char	tx_date[8+1];
		char	tx_time[6+1];
		int	sysid;
		char	event_msg[255+1];
		char	col_date[8+1];
		char	col_time[6+1];
}T_t_door_events;
int DB_t_door_events_add(T_t_door_events *pt_door_events);
#endif
