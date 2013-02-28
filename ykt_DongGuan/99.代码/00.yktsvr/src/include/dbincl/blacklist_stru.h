#ifndef  __T_blacklist_H_
#define  __T_blacklist_H_
typedef struct 
{
		int	cardid;
		int	cardno;
		char	cardsn[20+1];
		char	listtype[1+1];
		char	listverno[14+1];
		int	listlevel;
		int	intolistcause;
		int	intolistcnt;
		int	intolistdate;
		int	rmflag;
		int	rmdate;
}T_t_blacklist;
int DB_t_blacklist_add(T_t_blacklist *pt_blacklist);
int DB_t_blacklist_read_by_cardid(int v_cardid,T_t_blacklist *pt_blacklist);
int DB_t_blacklist_update_by_cardid(int v_cardid,T_t_blacklist *pt_blacklist);
int DB_t_blacklist_del_by_cardid(int v_cardid);
int DB_t_blacklist_read_lock_by_c0_and_cardid(int v_cardid,T_t_blacklist *pt_blacklist);
int DB_t_blacklist_update_lock_by_c0(T_t_blacklist *pt_blacklist);
int DB_t_blacklist_del_lock_by_c0();
int DB_t_blacklist_free_lock_by_c0();
#endif
