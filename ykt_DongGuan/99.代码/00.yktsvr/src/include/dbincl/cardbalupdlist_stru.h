#ifndef  __T_cardbalupdlist_H_
#define  __T_cardbalupdlist_H_
typedef struct 
{
		char	batchno[30+1];
		int	seqno;
		int	cardno;
		int	transdate;
		char	status[1+1];
		double	amount;
		char	summary[60+1];
		int	transcode;
		char	lastupdtime[30+1];
}T_t_cardbalupdlist;
int DB_t_cardbalupdlist_add(T_t_cardbalupdlist *pt_cardbalupdlist);
int DB_t_cardbalupdlist_read_by_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_cardbalupdlist *pt_cardbalupdlist);
int DB_t_cardbalupdlist_update_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_cardbalupdlist *pt_cardbalupdlist);
int DB_t_cardbalupdlist_del_by_batchno_and_seqno(const char *v_batchno,int v_seqno);
int DB_t_cardbalupdlist_read_lock_by_c0_and_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_cardbalupdlist *pt_cardbalupdlist);
int DB_t_cardbalupdlist_update_lock_by_c0(T_t_cardbalupdlist *pt_cardbalupdlist);
int DB_t_cardbalupdlist_del_lock_by_c0();
int DB_t_cardbalupdlist_free_lock_by_c0();
int DB_t_cardbalupdlist_open_select_for_update_by_c1_and_cardno_and_status(int v_cardno,char *v_status);
int DB_t_cardbalupdlist_fetch_select_by_c1(T_t_cardbalupdlist *pt_cardbalupdlist);
int DB_t_cardbalupdlist_update_select_by_c1(T_t_cardbalupdlist *pt_cardbalupdlist);
int DB_t_cardbalupdlist_close_select_by_c1();
#endif
