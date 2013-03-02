#ifndef  __T_shopaccdtl_H_
#define  __T_shopaccdtl_H_
typedef struct 
{
		char	accno[20+1];
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		int	subseqno;
		char	transdate[8+1];
		char	transtime[6+1];
		char	collectdate[8+1];
		char	collecttime[6+1];
		char	devphyid[30+1];
		int	shopid;
		char	accname[60+1];
		char	subjno[20+1];
		char	voucherno[30+1];
		int	transcode;
		int	transtype;
		char	summary[60+1];
		char	dbcr[1+1];
		double	amount;
		double	balance;
		char	othaccno[20+1];
		char	othsubjno[20+1];
}T_t_shopaccdtl;
int DB_t_shopaccdtl_add(T_t_shopaccdtl *pt_shopaccdtl);
int DB_t_shopaccdtl_read_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_shopaccdtl *pt_shopaccdtl);
int DB_t_shopaccdtl_update_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_shopaccdtl *pt_shopaccdtl);
int DB_t_shopaccdtl_del_by_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno);
int DB_t_shopaccdtl_read_lock_by_c0_and_accno_and_accdate_and_termid_and_termseqno_and_subseqno(char *v_accno,char *v_accdate,int v_termid,int v_termseqno,int v_subseqno,T_t_shopaccdtl *pt_shopaccdtl);
int DB_t_shopaccdtl_update_lock_by_c0(T_t_shopaccdtl *pt_shopaccdtl);
int DB_t_shopaccdtl_free_lock_by_c0();
int DB_t_shopaccdtl_open_select_by_c1_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_shopaccdtl_fetch_select_by_c1(T_t_shopaccdtl *pt_shopaccdtl);
int DB_t_shopaccdtl_close_select_by_c1();
#endif
