#ifndef  __T_card_H_
#define  __T_card_H_
typedef struct 
{
		int	cardid;
		int	cardno;
		int	custid;
		int	issueunit;
		char	cardasno[20+1];
		char	cardmngrno[20+1];
		char	carducid[20+1];
		char	cardphyid[16+1];
		int	cardtype;
		int	cardphytype;
		int	cardversion;
		char	listversion[14+1];
		int	status;
		int	madedate;
		char	issuebatchno[14+1];
		int	issuedate;
		int	enabledate;
		int	expdate;
		int	deposit;
		int	balance;
		int	cardbal;
		int	dpsamt;
		int	payamt;
		int	dpscnt;
		int	paycnt;
		int	dpsnum;
		int	paynum;
		int	termid;
		int	transdate;
		int	transtime;
		int	dpswfailflag;
		int	lossflag;
		int	lossdate;
		int	losseftdate;
		int	deldate;
		int	delflag;
		char	updtime[14+1];
}T_t_card;
int DB_t_card_add(T_t_card *pt_card);
int DB_t_card_read_by_cardid(int v_cardid,T_t_card *pt_card);
int DB_t_card_read_by_cardasno(const char *v_cardasno,T_t_card *pt_card);
int DB_t_card_update_by_cardid(int v_cardid,T_t_card *pt_card);
int DB_t_card_del_by_cardid(int v_cardid);
int DB_t_card_read_lock_by_c0_and_cardid(int v_cardid,T_t_card *pt_card);
int DB_t_card_update_lock_by_c0(T_t_card *pt_card);
int DB_t_card_del_lock_by_c0();
int DB_t_card_free_lock_by_c0();
int DB_t_card_read_lock_by_c1_and_cardasno(const char *v_cardasno,T_t_card *pt_card);
int DB_t_card_update_lock_by_c1(T_t_card *pt_card);
int DB_t_card_del_lock_by_c1();
int DB_t_card_free_lock_by_c1();
#endif
