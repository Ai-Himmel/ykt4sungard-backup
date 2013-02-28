#ifndef  __T_vaccdtl_H_
#define  __T_vaccdtl_H_
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
		char	voucherno[20+1];
		int	transcode;
		int	transtype;
		char	summary[60+1];
		char	subjno[20+1];
		char	accno[10+1];
		char	accname[60+1];
		int	dcflag;
		double	amount;
		double	balance;
		char	oppsubjno[20+1];
		char	oppaccno[10+1];
		char	oppaccname[60+1];
		char	opercode[8+1];
		char	remark[240+1];
}T_v_accdtl;
int DB_v_accdtl_add(T_v_accdtl *pv_accdtl);
int DB_v_accdtl_read_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(const char *v_accno,const char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_v_accdtl *pv_accdtl);
int DB_v_accdtl_open_select_by_c1_and_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno);
int DB_v_accdtl_fetch_select_by_c1(T_v_accdtl *pv_accdtl);
int DB_v_accdtl_close_select_by_c1();
#endif
