#ifndef  __T_seqnoctl_H_
#define  __T_seqnoctl_H_
typedef struct 
{
		int	termid;
		int	termseqno;
		int	accdate;
}T_t_seqnoctl;
int DB_t_seqnoctl_add(T_t_seqnoctl *pt_seqnoctl);
int DB_t_seqnoctl_read_by_termid(int v_termid,T_t_seqnoctl *pt_seqnoctl);
int DB_t_seqnoctl_update_by_termid(int v_termid,T_t_seqnoctl *pt_seqnoctl);
int DB_t_seqnoctl_del_by_termid(int v_termid);
int DB_t_seqnoctl_read_lock_by_c0_and_termid(int v_termid,T_t_seqnoctl *pt_seqnoctl);
int DB_t_seqnoctl_update_lock_by_c0(T_t_seqnoctl *pt_seqnoctl);
int DB_t_seqnoctl_free_lock_by_c0();
#endif
