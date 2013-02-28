#ifndef  __T_banktransdtl_H_
#define  __T_banktransdtl_H_
typedef struct 
{
		int	accdate;
		char	refno[14+1];
		int	batchno;
		char	samno[12+1];
		int	samseqno;
		int	termdate;
		int	termtime;
		int	cardno;
		int	cardid;
		char	cardasno[20+1];
		int	cardtype;
		int	dpscnt;
		int	paycnt;
		int	amount;
		int	befcardbal;
		int	aftcardbal;
		int	balance;
		int	expdate;
		int	transcode;
		int	branchid;
		int	merchid;
		int	hostdate;
		int	hosttime;
		char	bankcode[12+1];
		char	bankcardno[20+1];
		char	bankrefno[12+1];
		int	status;
		int	wctatus;
		char	tac[8+1];
		int	errcode;
		char	remark[60+1];
}T_t_banktransdtl;
int DB_t_banktransdtl_add(T_t_banktransdtl *pt_banktransdtl);
int DB_t_banktransdtl_read_by_accdate_and_refno(int v_accdate,const char *v_refno,T_t_banktransdtl *pt_banktransdtl);
int DB_t_banktransdtl_update_by_accdate_and_refno(int v_accdate,char *v_refno,T_t_banktransdtl *pt_banktransdtl);
int DB_t_banktransdtl_del_by_accdate_and_refno(int v_accdate,const char *v_refno);
int DB_t_banktransdtl_read_lock_by_c0_and_accdate_and_refno(int v_accdate,const char *v_refno,T_t_banktransdtl *pt_banktransdtl);
int DB_t_banktransdtl_update_lock_by_c0(T_t_banktransdtl *pt_banktransdtl);
int DB_t_banktransdtl_del_lock_by_c0();
int DB_t_banktransdtl_free_lock_by_c0();
#endif
