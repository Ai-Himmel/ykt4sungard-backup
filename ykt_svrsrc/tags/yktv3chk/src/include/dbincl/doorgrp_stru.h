#ifndef  __T_doorgrp_H_
#define  __T_doorgrp_H_
typedef struct 
{
		int	groupid;
		char	groupname[80+1];
		int	flag;
}T_t_doorgroup;
int DB_t_doorgroup_add(T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_read_by_groupid(int v_groupid,T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_update_by_groupid(int v_groupid,T_t_doorgroup *pt_doorgroup);
int DB_t_doorgroup_del_by_groupid(int v_groupid);
#endif
