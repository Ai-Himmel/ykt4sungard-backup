#ifndef  __T_cardverdtl_H_
#define  __T_cardverdtl_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		int	cardno;
		char	cardphyid[8+1];
		int	cardvertype;
		char	cardverno[30+1];
		char	delflag[1+1];
}T_t_cardverdtl;
int DB_t_cardverdtl_add(T_t_cardverdtl *pt_cardverdtl);
int DB_t_cardverdtl_read_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardverdtl *pt_cardverdtl);
int DB_t_cardverdtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardverdtl *pt_cardverdtl);
int DB_t_cardverdtl_del_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_cardverdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardverdtl *pt_cardverdtl);
int DB_t_cardverdtl_update_lock_by_c0(T_t_cardverdtl *pt_cardverdtl);
int DB_t_cardverdtl_free_lock_by_c0();
#endif
