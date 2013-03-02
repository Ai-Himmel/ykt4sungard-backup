#ifndef  __T_card_H_
#define  __T_card_H_
typedef struct 
{
		int	cardno;
		char	accno[10+1];
		int	cardtype;
		int	feetype;
		int	custid;
		char	stuempno[20+1];
		char	showcardno[10+1];
		char	cardphyid[8+1];
		char	cardpwd[32+1];
		char	expiredate[8+1];
		char	status[1+1];
		char	lossflag[1+1];
		char	lossdate[8+1];
		char	lossefttime[30+1];
		char	frozeflag[1+1];
		char	frozedate[8+1];
		char	badflag[1+1];
		char	badtype[1+1];
		char	baddate[8+1];
		char	lockflag[1+1];
		char	lockdate[8+1];
		char	opendate[8+1];
		char	closedate[8+1];
		char	cardverno[12+1];
		char	lastsaved[30+1];
}T_t_card;
int DB_t_card_add(T_t_card *pt_card);
int DB_t_card_read_by_cardno(int v_cardno,T_t_card *pt_card);
int DB_t_card_read_by_custid_and_status_and_cardtype(int v_custid,char *v_status,int v_cardtype,T_t_card *pt_card);
int DB_t_card_read_by_custid_and_status(int v_custid,char *v_status,T_t_card *pt_card);
int DB_t_card_read_by_showcardno_and_status(char *v_showcardno,char *v_status,T_t_card *pt_card);
int DB_t_card_read_by_cardphyid_and_status(char *v_cardphyid,char *v_status,T_t_card *pt_card);
int DB_t_card_update_by_cardno(int v_cardno,T_t_card *pt_card);
int DB_t_card_del_by_cardno(int v_cardno);
int DB_t_card_read_lock_by_cur_and_cardno(int v_cardno,T_t_card *pt_card);
int DB_t_card_update_lock_by_cur(T_t_card *pt_card);
int DB_t_card_free_lock_by_cur();
int DB_t_card_open_select_by_c1_and_custid(int v_custid);
int DB_t_card_fetch_select_by_c1(T_t_card *pt_card);
int DB_t_card_close_select_by_c1();
#endif
