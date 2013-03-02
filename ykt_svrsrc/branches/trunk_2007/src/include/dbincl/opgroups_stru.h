#ifndef  __T_opgroups_H_
#define  __T_opgroups_H_
typedef struct 
{
		char	group_id[10+1];
		char	group_name[100+1];
		char	group_state[1+1];
		char	group_acc[20+1];
}T_t_groups;
int DB_t_groups_read_by_group_id(char *v_group_id,T_t_groups *pt_groups);
int DB_t_groups_read_by_group_acc(char *v_group_acc,T_t_groups *pt_groups);
#endif
