#ifndef  __T_cardlist_H_
#define  __T_cardlist_H_
typedef struct 
{
		int	device_id;
		int	cust_id;
		int	week_id;
		int	holiday_id;
		int	card_no;
		char	card_serial_no[8+1];
		int	status;
		char	update_time[14+1];
		char	download_time[14+1];
}T_t_door_device_cardlist;
int DB_t_door_device_cardlist_add(T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_read_by_device_id_and_cust_id(int v_device_id,int v_cust_id,T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_update_by_device_id_and_cust_id(int v_device_id,int v_cust_id,T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_open_select_for_update_by_cur0_and_cust_id(int v_cust_id);
int DB_t_door_device_cardlist_fetch_select_by_cur0(T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_update_lock_by_cur0(T_t_door_device_cardlist *pt_door_device_cardlist);
int DB_t_door_device_cardlist_close_select_by_cur0();
#endif
