#ifndef  __T_account_H_
#define  __T_account_H_
typedef struct {
    char	accno[10+1];
    char	accname[60+1];
    char	subjno[6+1];
    char	accpwd[64+1];
    int	custid;
    int	cardno;
    int	purseno;
    double	singlemaxamt;
    double	daycostmaxamt;
    char	status[1+1];
    double	foregift;
    double	ydaybal;
    double	balance;
    double	availbal;
    double	frozebal;
    double	subsidybal;
    int	subsidyno;
    double	cardbal;
    int	dpscnt;
    int	paycnt;
    double	lastsubsidyamt;
    int	lastsubsidyno;
    double	lastcardbal;
    int	lastdpscnt;
    int	lastpaycnt;
    char	lasttransdate[8+1];
    char	lastaccdate[8+1];
    char	opendate[8+1];
    char	closedate[8+1];
} T_t_account;
int DB_t_account_add(T_t_account *pt_account);
int DB_t_account_read_by_accno(char *v_accno,T_t_account *pt_account);
int DB_t_account_read_by_cardno(int v_cardno,T_t_account *pt_account);
int DB_t_account_update_by_accno(char *v_accno,T_t_account *pt_account);
int DB_t_account_del_by_accno(char *v_accno);
int DB_t_account_read_lock_by_c0_and_accno(char *v_accno,T_t_account *pt_account);
int DB_t_account_update_lock_by_c0(T_t_account *pt_account);
int DB_t_account_free_lock_by_c0();
#endif
