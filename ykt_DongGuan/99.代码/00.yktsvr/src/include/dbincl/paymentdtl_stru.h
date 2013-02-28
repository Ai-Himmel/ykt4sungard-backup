#ifndef  __T_paymentdtl_H_
#define  __T_paymentdtl_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		int	shopid;
		char	accno[20+1];
		char	accname[240+1];
		char	transdate[8+1];
		char	transtime[6+1];
		double	amount;
		char	paybankaccno[30+1];
		char	paybankaccname[240+1];
		char	payeebankaccno[30+1];
		char	payeebankaccname[240+1];
		char	opercode[8+1];
}T_t_paymentdtl;
int DB_t_paymentdtl_add(T_t_paymentdtl *pt_paymentdtl);
int DB_t_paymentdtl_read_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno,T_t_paymentdtl *pt_paymentdtl);
int DB_t_paymentdtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_paymentdtl *pt_paymentdtl);
int DB_t_paymentdtl_del_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno);
int DB_t_paymentdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno,T_t_paymentdtl *pt_paymentdtl);
int DB_t_paymentdtl_update_lock_by_c0(T_t_paymentdtl *pt_paymentdtl);
int DB_t_paymentdtl_free_lock_by_c0();
int DB_t_paymentdtl_open_select_by_c1_and_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno);
int DB_t_paymentdtl_fetch_select_by_c1(T_t_paymentdtl *pt_paymentdtl);
int DB_t_paymentdtl_close_select_by_c1();
#endif
