#ifndef  __T_netacc_H_
#define  __T_netacc_H_
typedef struct 
{
		char	accno[20+1];
		char	accname[240+1];
		char	subjno[20+1];
		char	accpwd[64+1];
		int	custid;
		char	stoppayflag[1+1];
		char	status[1+1];
		double	ydaybal;
		double	balance;
		double	availbal;
		double	frozebal;
		char	lasttransdate[8+1];
		char	lastaccdate[8+1];
		char	opendate[8+1];
		char	closedate[8+1];
}T_t_netacc;
int DB_t_netacc_add(T_t_netacc *pt_netacc);
int DB_t_netacc_read_by_custid(int v_custid,T_t_netacc *pt_netacc);
int DB_t_netacc_read_by_accno(char *v_accno,T_t_netacc *pt_netacc);
int DB_t_netacc_update_by_accno(char *v_accno,T_t_netacc *pt_netacc);
int DB_t_netacc_del_by_accno(char *v_accno);
int DB_t_netacc_read_lock_by_c0_and_accno(char *v_accno,T_t_netacc *pt_netacc);
int DB_t_netacc_update_lock_by_c0(T_t_netacc *pt_netacc);
int DB_t_netacc_free_lock_by_c0();
#endif
