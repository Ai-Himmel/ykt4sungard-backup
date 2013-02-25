#ifndef  __T_accdtl_H_
#define  __T_accdtl_H_
typedef struct {
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
    char	subjno[6+1];
    char	accno[10+1];
    char	accname[60+1];
    int	dcflag;
    double	amount;
    double	balance;
    char	oppsubjno[6+1];
    char	oppaccno[10+1];
    char	oppaccname[60+1];
    char	opercode[8+1];
    char	remark[240+1];
} T_t_accdtl;
int DB_t_accdtl_add(T_t_accdtl *pt_accdtl);
int DB_t_accdtl_read_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_accdtl *pt_accdtl);
int DB_t_accdtl_update_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_accdtl *pt_accdtl);
int DB_t_accdtl_del_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno);
int DB_t_accdtl_read_lock_by_c0_and_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_accdtl *pt_accdtl);
int DB_t_accdtl_update_lock_by_c0(T_t_accdtl *pt_accdtl);
int DB_t_accdtl_free_lock_by_c0();
int DB_t_accdtl_open_select_by_c1_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_accdtl_fetch_select_by_c1(T_t_accdtl *pt_accdtl);
int DB_t_accdtl_close_select_by_c1();
#endif
