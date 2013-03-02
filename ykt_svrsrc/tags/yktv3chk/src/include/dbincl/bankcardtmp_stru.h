#ifndef  __T_bankcardtmp_H_
#define  __T_bankcardtmp_H_
typedef struct 
{
		char	batchno[30+1];
		int	seqno;
		int	custid;
		char	bankcode[2+1];
		char	bankcardno[30+1];
		char	opercode[8+1];
}T_t_bankcardtmp;
int DB_t_bankcardtmp_add(T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_read_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_update_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_del_by_batchno_and_seqno(char *v_batchno,int v_seqno);
int DB_t_bankcardtmp_read_lock_by_c0_and_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_update_lock_by_c0(T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_free_lock_by_c0();
int DB_t_bankcardtmp_open_select_by_c1_and_batchno(char *v_batchno);
int DB_t_bankcardtmp_fetch_select_by_c1(T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_close_select_by_c1();
#endif
