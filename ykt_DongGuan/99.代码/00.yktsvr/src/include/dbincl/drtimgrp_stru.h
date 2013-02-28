#ifndef  __T_drtimgrp_H_
#define  __T_drtimgrp_H_
typedef struct 
{
		int	timegrpid;
		char	timegrpname[60+1];
		int	timeid1;
		int	timeid2;
		int	timeid3;
		int	timeid4;
		int	timeid5;
		int	timeid6;
		int	timeid7;
		int	timeid8;
		int	adddelflag;
		int	downstatus;
		char	updatetime[30+1];
}T_t_doortimegrp;
int DB_t_doortimegrp_add(T_t_doortimegrp *pt_doortimegrp);
int DB_t_doortimegrp_read_by_timegrpid(int v_timegrpid,T_t_doortimegrp *pt_doortimegrp);
int DB_t_doortimegrp_update_by_timegrpid(int v_timegrpid,T_t_doortimegrp *pt_doortimegrp);
int DB_t_doortimegrp_del_by_timegrpid(int v_timegrpid);
int DB_t_doortimegrp_read_lock_by_c0_and_timegrpid(int v_timegrpid,T_t_doortimegrp *pt_doortimegrp);
int DB_t_doortimegrp_update_lock_by_c0(T_t_doortimegrp *pt_doortimegrp);
int DB_t_doortimegrp_free_lock_by_c0();
#endif
