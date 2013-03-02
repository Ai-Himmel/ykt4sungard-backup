#ifndef  __T_groupmem_H_
#define  __T_groupmem_H_
typedef struct 
{
		int	group_id;
		int	device_id;
		char	comments[150+1];
}T_t_door_group_member;
int DB_t_door_group_member_add(T_t_door_group_member *pt_door_group_member);
int DB_t_door_group_member_read_by_group_id(int v_group_id,T_t_door_group_member *pt_door_group_member);
int DB_t_door_group_member_read_lock_by_c0_and_group_id(int v_group_id,T_t_door_group_member *pt_door_group_member);
int DB_t_door_group_member_update_lock_by_c0(T_t_door_group_member *pt_door_group_member);
int DB_t_door_group_member_free_lock_c0();
int DB_t_door_group_member_open_select_by_cur1_and_group_id(int v_group_id);
int DB_t_door_group_member_fetch_select_by_cur1(T_t_door_group_member *pt_door_group_member);
int DB_t_door_group_member_close_select_by_cur1();
int DB_t_door_group_member_del_by_group_id_and_device_id(int v_group_id,int v_device_id);
int DB_t_door_group_member_del_by_group_id(int v_group_id);
#endif
