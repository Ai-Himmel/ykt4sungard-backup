#ifndef  __T_shopaccount_H_
#define  __T_shopaccount_H_
typedef struct 
{
		char	accno[20+1];
		char	accname[60+1];
		char	subjno[20+1];
		int	shopid;
		char	accpwd[32+1];
		char	status[1+1];
		double	ydaytbal;
		double	balance;
		char	opendate[8+1];
		char	closedate[8+1];
		char	lasttransdate[30+1];
		char	lastaccdate[8+1];
}T_t_shopaccount;
int DB_t_shopaccount_add(T_t_shopaccount *pt_shopaccount);
int DB_t_shopaccount_read_by_shopid(int v_shopid,T_t_shopaccount *pt_shopaccount);
int DB_t_shopaccount_read_by_accno(char *v_accno,T_t_shopaccount *pt_shopaccount);
int DB_t_shopaccount_update_by_accno(char *v_accno,T_t_shopaccount *pt_shopaccount);
int DB_t_shopaccount_del_by_accno(char *v_accno);
int DB_t_shopaccount_read_lock_by_c0_and_accno(char *v_accno,T_t_shopaccount *pt_shopaccount);
int DB_t_shopaccount_update_lock_by_c0(T_t_shopaccount *pt_shopaccount);
int DB_t_shopaccount_free_lock_by_c0();
#endif
