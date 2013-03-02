#ifndef  __T_drgrprht_H_
#define  __T_drgrprht_H_
typedef struct 
{
		int	gid;
		char	oper_code[10+1];
}T_t_door_group_oper_right;
int DB_t_door_group_oper_right_add(T_t_door_group_oper_right *pt_door_group_oper_right);
int DB_t_door_group_oper_right_read_by_gid_and_oper_code(int v_gid,char *v_oper_code,T_t_door_group_oper_right *pt_door_group_oper_right);
int DB_t_door_group_oper_right_del_by_gid_and_oper_code(int v_gid,char *v_oper_code);
#endif
