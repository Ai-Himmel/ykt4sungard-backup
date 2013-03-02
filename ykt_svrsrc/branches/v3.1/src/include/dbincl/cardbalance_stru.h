#ifndef  __T_cardbalance_H_
#define  __T_cardbalance_H_
typedef struct 
{
		char	accno[10+1];
		int	pursetype;
		int	cardno;
		int	oldcardno;
		char	transdate[8+1];
		char	transtime[6+1];
		int	dpscnt;
		int	paycnt;
		double	balance;
		double	cardbal;
		double	accumdpsamt;
}T_t_cardbalance;
int DB_t_cardbalance_add(T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_read_by_accno_and_pursetype(const char *v_accno,int v_pursetype,T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_read_by_pursetype_and_cardno(int v_pursetype,int v_cardno,T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_update_by_accno_and_pursetype(char *v_accno,int v_pursetype,T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_del_by_accno_and_pursetype(const char *v_accno,int v_pursetype);
int DB_t_cardbalance_read_lock_by_c0_and_accno_and_pursetype(const char *v_accno,int v_pursetype,T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_update_lock_by_c0(T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_free_lock_by_c0();
int DB_t_cardbalance_read_lock_by_c1_and_pursetype_and_cardno(int v_pursetype,int v_cardno,T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_update_lock_by_c1(T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_free_lock_by_c1();
int DB_t_cardbalance_open_select_by_c2_and_cardno(int v_cardno);
int DB_t_cardbalance_fetch_select_by_c2(T_t_cardbalance *pt_cardbalance);
int DB_t_cardbalance_close_select_by_c2();
#endif
