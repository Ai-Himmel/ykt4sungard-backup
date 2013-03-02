#ifndef  __T_acctransdtl_H_
#define  __T_acctransdtl_H_
typedef struct 
{
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		int	subseqno;
		char	transdate[8+1];
		char	transtime[6+1];
		int	paytype;
		char	voucherno[30+1];
		int	transcode;
		int	transtype;
		char	summary[60+1];
		char	subjno[20+1];
		char	accno[20+1];
		char	accname[240+1];
		char	dbcr[1+1];
		double	amount;
		double	balance;
		char	oppsubjno[20+1];
		char	oppaccno[20+1];
		char	oppaccname[240+1];
		char	opercode[8+1];
		char	remark[240+1];
}T_t_acctransdtl;
int DB_t_acctransdtl_add(T_t_acctransdtl *pt_acctransdtl);
int DB_t_acctransdtl_read_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_acctransdtl *pt_acctransdtl);
int DB_t_acctransdtl_update_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_acctransdtl *pt_acctransdtl);
int DB_t_acctransdtl_del_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno);
int DB_t_acctransdtl_read_lock_by_c0_and_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_acctransdtl *pt_acctransdtl);
int DB_t_acctransdtl_update_lock_by_c0(T_t_acctransdtl *pt_acctransdtl);
int DB_t_acctransdtl_free_lock_by_c0();
int DB_t_acctransdtl_open_select_by_c1_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_acctransdtl_fetch_select_by_c1(T_t_acctransdtl *pt_acctransdtl);
int DB_t_acctransdtl_close_select_by_c1();
#endif
