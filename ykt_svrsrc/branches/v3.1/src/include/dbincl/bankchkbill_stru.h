#ifndef  __T_bankchkbill_H_
#define  __T_bankchkbill_H_
typedef struct 
{
		char	transdate[8+1];
		char	bankcardno[30+1];
		char	banksn[30+1];
		int	cardno;
		char	localsn[30+1];
		int	transcode;
		char	summary[60+1];
		double	bankamt;
		double	localamt;
		double	diffamt;
		char	chkflag[1+1];
}T_t_bankchkbill;
int DB_t_bankchkbill_add(T_t_bankchkbill *pt_bankchkbill);
int DB_t_bankchkbill_read_by_transdate_and_bankcardno_and_banksn_and_cardno(char *v_transdate,char *v_bankcardno,char *v_banksn,int v_cardno,T_t_bankchkbill *pt_bankchkbill);
int DB_t_bankchkbill_update_by_transdate_and_bankcardno_and_banksn_and_cardno(char *v_transdate,char *v_bankcardno,char *v_banksn,int v_cardno,T_t_bankchkbill *pt_bankchkbill);
int DB_t_bankchkbill_del_by_transdate_and_bankcardno_and_banksn_and_cardno(char *v_transdate,char *v_bankcardno,char *v_banksn,int v_cardno);
int DB_t_bankchkbill_read_lock_by_c0_and_transdate_and_bankcardno_and_banksn_and_cardno(char *v_transdate,char *v_bankcardno,char *v_banksn,int v_cardno,T_t_bankchkbill *pt_bankchkbill);
int DB_t_bankchkbill_update_lock_by_c0(T_t_bankchkbill *pt_bankchkbill);
int DB_t_bankchkbill_free_lock_by_c0();
int DB_t_bankchkbill_open_select_by_c1_and_transdate_and_bankcardno_and_banksn_and_cardno(char *v_transdate,char *v_bankcardno,char *v_banksn,int v_cardno);
int DB_t_bankchkbill_fetch_select_by_c1(T_t_bankchkbill *pt_bankchkbill);
int DB_t_bankchkbill_close_select_by_c1();
#endif
