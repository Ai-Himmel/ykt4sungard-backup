#ifndef  __T_carddtl_H_
#define  __T_carddtl_H_
typedef struct 
{
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		int	branchno;
		char	opercode[8+1];
		int	cardtype;
		int	usetype;
		char	summary[60+1];
		int	inoutflag;
		int	transcnt;
		char	cardphyid[16+1];
		char	showcardno[10+1];
}T_t_carddtl;
int DB_t_carddtl_add(T_t_carddtl *pt_carddtl);
int DB_t_carddtl_read_by_accdate_and_termid_and_termseqno_and_opercode(char *v_accdate,int v_termid,int v_termseqno,char *v_opercode,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_update_by_accdate_and_termid_and_termseqno_and_opercode(char *v_accdate,int v_termid,int v_termseqno,char *v_opercode,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_del_by_accdate_and_termid_and_termseqno_and_opercode(char *v_accdate,int v_termid,int v_termseqno,char *v_opercode);
int DB_t_carddtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno_and_opercode(char *v_accdate,int v_termid,int v_termseqno,char *v_opercode,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_update_lock_by_c0(T_t_carddtl *pt_carddtl);
int DB_t_carddtl_free_lock_by_c0();
int DB_t_carddtl_open_select_by_c1_and_accdate_and_termid_and_termseqno_and_opercode(char *v_accdate,int v_termid,int v_termseqno,char *v_opercode);
int DB_t_carddtl_fetch_select_by_c1(T_t_carddtl *pt_carddtl);
int DB_t_carddtl_close_select_by_c1();
#endif
