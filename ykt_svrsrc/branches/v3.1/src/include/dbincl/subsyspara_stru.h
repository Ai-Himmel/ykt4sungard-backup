#ifndef  __T_subsyspara_H_
#define  __T_subsyspara_H_
typedef struct 
{
		int	sysid;
		char	workmode[1+1];
		int	beatinterval;
		int	beatcntlimit;
		int	reqbeatfuncno;
		int	reqdevfuncno;
		int	reqtaskfuncno;
		int	respfuncno;
		int	exectimeout;
		int	colinterval;
		int	qryinterval;
		int	taskmaxlimit;
		int	bccdrtpno;
		char	bccdrtpip[15+1];
		int	bccdrtpport;
		int	bccmainfuncno;
		int	bccinterval;
}T_t_subsyspara;
int DB_t_subsyspara_add(T_t_subsyspara *pt_subsyspara);
int DB_t_subsyspara_read_by_sysid(int v_sysid,T_t_subsyspara *pt_subsyspara);
int DB_t_subsyspara_update_by_sysid(int v_sysid,T_t_subsyspara *pt_subsyspara);
int DB_t_subsyspara_del_by_sysid(int v_sysid);
int DB_t_subsyspara_read_lock_by_c0_and_sysid(int v_sysid,T_t_subsyspara *pt_subsyspara);
int DB_t_subsyspara_update_lock_by_c0(T_t_subsyspara *pt_subsyspara);
int DB_t_subsyspara_free_lock_by_c0();
int DB_t_subsyspara_open_select_by_c1();
int DB_t_subsyspara_fetch_select_by_c1(T_t_subsyspara *pt_subsyspara);
int DB_t_subsyspara_close_select_by_c1();
#endif
