#ifndef  __T_carddtl_H_
#define  __T_carddtl_H_
typedef struct 
{
		int	accdate;
		char	refno[20+1];
		int	cardno;
		char	samno[12+1];
		int	samseqno;
		int	termdate;
		int	termtime;
		int	cardid;
		char	cardasno[20+1];
		int	cardtype;
		int	dpscnt;
		int	paycnt;
		int	befcardbal;
		int	aftcardbal;
		int	amount;
		int	otheramt;
		int	balance;
		int	transcode;
		int	transtype;
		char	transdesc[60+1];
		int	citycode;
		int	merchid;
		int	posno;
		int	posseqno;
		int	branchid;
		int	operid;
		int	hostdate;
		int	hosttime;
		int	status;
		int	wcstatus;
		int	errcode;
		char	remark[60+1];
}T_t_carddtl;
int DB_t_carddtl_add(T_t_carddtl *pt_carddtl);
int DB_t_carddtl_read_by_accdate_and_refno(int v_accdate,const char *v_refno,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_update_by_accdate_and_refno(int v_accdate,char *v_refno,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_del_by_accdate_and_refno(int v_accdate,const char *v_refno);
int DB_t_carddtl_read_lock_by_c0_and_accdate_and_refno(int v_accdate,const char *v_refno,T_t_carddtl *pt_carddtl);
int DB_t_carddtl_update_lock_by_c0(T_t_carddtl *pt_carddtl);
int DB_t_carddtl_del_lock_by_c0();
int DB_t_carddtl_free_lock_by_c0();
#endif
