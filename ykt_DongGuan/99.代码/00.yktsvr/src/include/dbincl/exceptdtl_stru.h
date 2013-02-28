#ifndef  __T_exceptdtl_H_
#define  __T_exceptdtl_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		char	refno[14+1];
		int	cardno;
		int	purseno;
		int	dpscnt;
		int	paycnt;
		double	cardbefbal;
		double	cardaftbal;
		int	failtype;
		int	status;
		char	remark[240+1];
		char	lastsaved[30+1];
}T_t_exceptdtl;
int DB_t_exceptdtl_add(T_t_exceptdtl *pt_exceptdtl);
int DB_t_exceptdtl_read_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno,T_t_exceptdtl *pt_exceptdtl);
int DB_t_exceptdtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_exceptdtl *pt_exceptdtl);
int DB_t_exceptdtl_del_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno);
int DB_t_exceptdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno,T_t_exceptdtl *pt_exceptdtl);
int DB_t_exceptdtl_update_lock_by_c0(T_t_exceptdtl *pt_exceptdtl);
int DB_t_exceptdtl_free_lock_by_c0();
#endif
