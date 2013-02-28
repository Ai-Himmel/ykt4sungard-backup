#ifndef  __T_front_H_
#define  __T_front_H_
typedef struct 
{
		int	frontid;
		char	frontname[60+1];
		char	ip[15+1];
		int	drtpport;
		int	drtpnode;
		int	bccmainfuncno;
}T_t_front;
int DB_t_front_add(T_t_front *pt_front);
int DB_t_front_read_by_frontid(int v_frontid,T_t_front *pt_front);
int DB_t_front_update_by_frontid(int v_frontid,T_t_front *pt_front);
int DB_t_front_del_by_frontid(int v_frontid);
int DB_t_front_read_lock_by_c0_and_frontid(int v_frontid,T_t_front *pt_front);
int DB_t_front_update_lock_by_c0(T_t_front *pt_front);
int DB_t_front_del_lock_by_c0();
int DB_t_front_free_lock_by_c0();
#endif
