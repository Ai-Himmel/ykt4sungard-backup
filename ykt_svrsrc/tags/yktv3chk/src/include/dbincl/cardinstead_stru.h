#ifndef  __T_cardinstead_H_
#define  __T_cardinstead_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		int	oldcardno;
		char	oldcardphyid[16+1];
		int	cardno;
		char	cardphyid[16+1];
}T_t_cardinstead;
int DB_t_cardinstead_add(T_t_cardinstead *pt_cardinstead);
int DB_t_cardinstead_read_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardinstead *pt_cardinstead);
int DB_t_cardinstead_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardinstead *pt_cardinstead);
int DB_t_cardinstead_del_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_cardinstead_read_lock_by_c0_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardinstead *pt_cardinstead);
int DB_t_cardinstead_update_lock_by_c0(T_t_cardinstead *pt_cardinstead);
int DB_t_cardinstead_free_lock_by_c0();
#endif
