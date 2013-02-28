#ifndef  __T_account_H_
#define  __T_account_H_
typedef struct 
{
		char	accno[10+1];
		char	accname[60+1];
		char	subjno[20+1];
		char	accpwd[64+1];
		int	custid;
		int	cardno;
		double	singlemaxamt;
		double	daycostmaxamt;
		char	status[1+1];
		double	foregift;
		double	balance;
		double	availbal;
		double	frozebal;
		double	subsidybal;
		int	subsidyno;
		double	cardbal;
		int	dpscnt;
		int	paycnt;
		char	transtime[14+1];
		int	termid;
		char	opendate[8+1];
		char	closedate[8+1];
}T_t_account;
int DB_t_account_add(T_t_account *pt_account);
int DB_t_account_read_by_accno(const char *v_accno,T_t_account *pt_account);
int DB_t_account_read_by_cardno(int v_cardno,T_t_account *pt_account);
int DB_t_account_update_by_accno(char *v_accno,T_t_account *pt_account);
int DB_t_account_del_by_accno(const char *v_accno);
int DB_t_account_read_lock_by_c0_and_accno(const char *v_accno,T_t_account *pt_account);
int DB_t_account_update_lock_by_c0(T_t_account *pt_account);
int DB_t_account_free_lock_by_c0();
#endif
