#ifndef  __T_inneraccount_H_
#define  __T_inneraccount_H_
typedef struct 
{
		char	accno[20+1];
		char	accname[60+1];
		char	subjno[20+1];
		int	subjtype;
		char	status[1+1];
		double	ydaybal;
		double	balance;
		char	lasttransdate[30+1];
		char	lastaccdate[8+1];
}T_t_inneraccount;
int DB_t_inneraccount_add(T_t_inneraccount *pt_inneraccount);
int DB_t_inneraccount_read_by_accno(char *v_accno,T_t_inneraccount *pt_inneraccount);
int DB_t_inneraccount_update_by_accno(char *v_accno,T_t_inneraccount *pt_inneraccount);
int DB_t_inneraccount_del_by_accno(char *v_accno);
int DB_t_inneraccount_read_lock_by_c0_and_accno(char *v_accno,T_t_inneraccount *pt_inneraccount);
int DB_t_inneraccount_update_lock_by_c0(T_t_inneraccount *pt_inneraccount);
int DB_t_inneraccount_free_lock_by_c0();
#endif
