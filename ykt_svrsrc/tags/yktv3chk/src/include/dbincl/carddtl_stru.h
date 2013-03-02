#ifndef  __T_carddtl_H_
#define  __T_carddtl_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		int	cardtype;
		char	showcardno[10+1];
		char	cardphyid[16+1];
		char	cardusetype[1+1];
		char	opercode[8+1];
}T_t_carddtl;
int DB_t_carddtl_add(T_t_carddtl *pt_carddtl);
int DB_t_carddtl_read_by_accdate_and_termseqno_and_termid(char *v_accdate,int v_termseqno,int v_termid,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_update_by_accdate_and_termseqno_and_termid(char *v_accdate,int v_termseqno,int v_termid,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_del_by_accdate_and_termseqno_and_termid(char *v_accdate,int v_termseqno,int v_termid);
int DB_t_carddtl_read_lock_by_c0_and_accdate_and_termseqno_and_termid(char *v_accdate,int v_termseqno,int v_termid,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_update_lock_by_c0(T_t_carddtl *pt_carddtl);
int DB_t_carddtl_free_lock_by_c0();
#endif
