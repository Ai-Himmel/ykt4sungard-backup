#ifndef  __T_drgrp_H_
#define  __T_drgrp_H_
typedef struct 
{
		int	groupid;
		char	groupname[60+1];
		char	status[1+1];
		char	updatetime[30+1];
}T_t_doorgroup;
int DB_t_doorgroup_add(T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_read_by_groupid(int v_groupid,T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_update_by_groupid(int v_groupid,T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_del_by_groupid(int v_groupid);
int DB_t_doorgroup_read_lock_by_c0_and_groupid(int v_groupid,T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_update_lock_by_c0(T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_free_lock_by_c0();
#endif
