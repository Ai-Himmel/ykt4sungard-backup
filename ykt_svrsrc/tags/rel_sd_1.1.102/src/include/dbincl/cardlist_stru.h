#ifndef  __T_cardlist_H_
#define  __T_cardlist_H_
typedef struct 
{
		char	device_id[8+1];
		int	card_no;
		char	card_serial_no[8+1];
		char	status[1+1];
		char	tx_date[8+1];
		char	tx_time[6+1];
		char	version[12+1];
		char	send_flag[1+1];
		char	stuemp_no[20+1];
}T_t_door_device_cardlist;
int DB_t_door_device_cardlist_add(T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_read_by_device_id_and_card_no(char *v_device_id,int v_card_no,T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_update_by_device_id_and_card_no(char *v_device_id,int v_card_no,T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_open_select_for_update_by_cur0_and_stuemp_no(char *v_stuemp_no);
int DB_t_door_device_cardlist_fetch_select_by_cur0(T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_update_lock_by_cur0(T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_close_select_by_cur0();
#endif
