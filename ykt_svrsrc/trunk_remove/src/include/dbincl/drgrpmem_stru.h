#ifndef  __T_drgrpmem_H_
#define  __T_drgrpmem_H_
typedef struct 
{
		int	groupid;
		int	deviceid;
		char	updatetime[30+1];
}T_t_doorgrpmember;
int DB_t_doorgrpmember_add(T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_read_by_groupid_and_deviceid(int v_groupid,int v_deviceid,T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_update_by_groupid_and_deviceid(int v_groupid,int v_deviceid,T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_del_by_groupid(int v_groupid);
int DB_t_doorgrpmember_del_by_groupid_and_deviceid(int v_groupid,int v_deviceid);
int DB_t_doorgrpmember_read_lock_by_c0_and_groupid_and_deviceid(int v_groupid,int v_deviceid,T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_update_lock_by_c0(T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_free_lock_by_c0();
#endif
