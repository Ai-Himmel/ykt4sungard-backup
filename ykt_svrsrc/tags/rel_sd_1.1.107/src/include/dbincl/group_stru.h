#ifndef  __T_group_H_
#define  __T_group_H_
typedef struct 
{
		int	group_id;
		char	group_name[80+1];
		int	ref_cnt;
}T_t_door_group;
int DB_t_door_group_add(T_t_door_group *pt_door_group);
int DB_t_door_group_read_by_group_id(int v_group_id,T_t_door_group *pt_door_group);
int DB_t_door_group_read_by_group_name(char *v_group_name,T_t_door_group *pt_door_group);
int DB_t_door_group_read_lock_by_c0_and_group_id(int v_group_id,T_t_door_group *pt_door_group);
int DB_t_door_group_update_lock_by_c0(T_t_door_group *pt_door_group);
int DB_t_door_group_free_lock_c0();
#endif
