#ifndef  __T_doorgrp_H_
#define  __T_doorgrp_H_
typedef struct 
{
		int	group_id;
		char	group_name[80+1];
		int	flag;
}T_t_door_group;
int DB_t_door_group_add(T_t_door_group *pt_door_group);
int DB_t_door_group_read_by_group_id(int v_group_id,T_t_door_group *pt_door_group);
int DB_t_door_group_update_by_group_id(int v_group_id,T_t_door_group *pt_door_group);
int DB_t_door_group_del_by_group_id(int v_group_id);
#endif
