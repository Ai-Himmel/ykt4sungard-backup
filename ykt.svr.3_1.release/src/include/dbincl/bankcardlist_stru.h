#ifndef  __T_bankcardlist_H_
#define  __T_bankcardlist_H_
typedef struct {
    char	batchno[30+1];
    int	seqno;
    char	transdate[8+1];
    int	custid;
    char	stuempno[20+1];
    char	bankcardno[30+1];
    int	optype;
    char	opercode[8+1];
    int	status;
    char	remark[240+1];
} T_t_bankcardlist;
int DB_t_bankcardlist_add(T_t_bankcardlist *pt_bankcardlist);
int DB_t_bankcardlist_read_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_bankcardlist *pt_bankcardlist);
int DB_t_bankcardlist_update_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_bankcardlist *pt_bankcardlist);
int DB_t_bankcardlist_del_by_batchno_and_seqno(char *v_batchno,int v_seqno);
int DB_t_bankcardlist_del_by_batchno(char *v_batchno);
int DB_t_bankcardlist_read_lock_by_c0_and_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_bankcardlist *pt_bankcardlist);
int DB_t_bankcardlist_update_lock_by_c0(T_t_bankcardlist *pt_bankcardlist);
int DB_t_bankcardlist_free_lock_by_c0();
int DB_t_bankcardlist_open_select_by_c1_and_batchno_and_seqno(char *v_batchno,int v_seqno);
int DB_t_bankcardlist_fetch_select_by_c1(T_t_bankcardlist *pt_bankcardlist);
int DB_t_bankcardlist_close_select_by_c1();
#endif
