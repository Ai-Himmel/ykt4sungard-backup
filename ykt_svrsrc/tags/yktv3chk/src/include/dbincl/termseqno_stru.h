#ifndef  __T_termseqno_H_
#define  __T_termseqno_H_
typedef struct 
{
		int	termid;
		int	termseqno;
		char	operdevphyid[30+1];
		char	accdate[8+1];
}T_t_termseqno;
int DB_t_termseqno_add(T_t_termseqno *pt_termseqno);
int DB_t_termseqno_read_by_termid(int v_termid,T_t_termseqno *pt_termseqno);
int DB_t_termseqno_read_lock_by_c0_and_operdevphyid(char *v_operdevphyid,T_t_termseqno *pt_termseqno);
int DB_t_termseqno_update_lock_by_c0(T_t_termseqno *pt_termseqno);
int DB_t_termseqno_free_lock_by_c0();
int DB_t_termseqno_update_by_termid(int v_termid,T_t_termseqno *pt_termseqno);
int DB_t_termseqno_del_by_termid(int v_termid);
#endif
