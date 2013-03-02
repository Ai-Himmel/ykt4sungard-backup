#ifndef  __T_account_H_
#define  __T_account_H_
typedef struct 
{
		char	accno[20+1];
		int	acctype;
		char	accname[240+1];
		char	subjno[20+1];
		char	accpwd[64+1];
		int	custid;
		int	cardno;
		int	purseno;
		double	daycostamt;
		double	daycostmaxamt;
		double	singlemaxamt;
		double	cardmaxbal;
		char	stoppayflag[1+1];
		char	status[1+1];
		double	ydaybal;
		double	ydayavailbal;
		double	ydayfrozebal;
		double	balance;
		double	availbal;
		double	frozebal;
		double	subsidybal;
		int	subsidyno;
		double	foregift;
		int	lastcardcnt;
		double	lastcardbal;
		char	lasttransdate[8+1];
		char	lastaccdate[8+1];
		int	lastsubsidyno;
		int	lastsubsidyamt;
		char	opendate[8+1];
		char	closedate[8+1];
}T_t_account;
int DB_t_account_add(T_t_account *pt_account);
int DB_t_account_read_by_accno(char *v_accno,T_t_account *pt_account);
int DB_t_account_read_by_custid_and_acctype(int v_custid,int v_acctype,T_t_account *pt_account);
int DB_t_account_read_by_cardno_and_purseno(int v_cardno,int v_purseno,T_t_account *pt_account);
int DB_t_account_update_by_accno(char *v_accno,T_t_account *pt_account);
int DB_t_account_del_by_accno(char *v_accno);
int DB_t_account_read_lock_by_c0_and_accno(char *v_accno,T_t_account *pt_account);
int DB_t_account_update_lock_by_c0(T_t_account *pt_account);
int DB_t_account_free_lock_by_c0();
int DB_t_account_read_lock_by_c1_and_cardno_and_purseno(int v_cardno,int v_purseno,T_t_account *pt_account);
int DB_t_account_update_lock_by_c1(T_t_account *pt_account);
int DB_t_account_free_lock_by_c1();
#endif
