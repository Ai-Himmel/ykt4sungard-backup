#ifndef  __T_groupmem_H_
#define  __T_groupmem_H_
typedef struct 
{
		int	groupid;
		int	deviceid;
		char	remark[240+1];
}T_t_doorgrpmember;
int DB_t_doorgrpmember_add(T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_read_by_groupid(int v_groupid,T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_read_lock_by_c0_and_groupid(int v_groupid,T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_update_lock_by_c0(T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_free_lock_c0();
int DB_t_doorgrpmember_open_select_by_cur1_and_groupid(int v_groupid);
int DB_t_doorgrpmember_fetch_select_by_cur1(T_t_doorgrpmember *pt_doorgrpmember);
int DB_t_doorgrpmember_close_select_by_cur1();
int DB_t_doorgrpmember_del_by_groupid_and_deviceid(int v_groupid,int v_deviceid);
int DB_t_doorgrpmember_del_by_groupid(int v_groupid);
#endif
