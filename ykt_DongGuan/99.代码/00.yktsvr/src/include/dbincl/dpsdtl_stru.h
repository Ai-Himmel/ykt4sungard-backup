#ifndef  __T_dpsdtl_H_
#define  __T_dpsdtl_H_
typedef struct 
{
		int	accdate;
		char	refno[14+1];
		int	hostdate;
		int	hosttime;
		int	cardid;
		int	cardno;
		char	cardasno[20+1];
		int	cardtype;
		int	dpscnt;
		int	paycnt;
		int	termid;
		int	termseqno;
		char	samno[12+1];
		int	transtype;
		int	amount;
		int	otheramt;
		int	befcardbal;
		int	aftcardbal;
		char	lastsamno[12+1];
		int	lasttype;
		int	lastamt;
		int	lastdate;
		int	lasttime;
		int	balance;
		int	termdate;
		int	termtime;
		int	operid;
		int	branchid;
		int	merchid;
		int	transcode;
		int	status;
		int	wcstatus;
		int	errcode;
		int	dpsdate;
		int	dpstime;
		char	mac1[8+1];
		char	mac2[8+1];
		char	remark[60+1];
}T_t_dpsdtl;
int DB_t_dpsdtl_add(T_t_dpsdtl *pt_dpsdtl);
int DB_t_dpsdtl_read_by_accdate_and_refno(int v_accdate,const char *v_refno,T_t_dpsdtl *pt_dpsdtl);
int DB_t_dpsdtl_update_by_accdate_and_refno(int v_accdate,char *v_refno,T_t_dpsdtl *pt_dpsdtl);
int DB_t_dpsdtl_del_by_accdate_and_refno(int v_accdate,const char *v_refno);
int DB_t_dpsdtl_read_lock_by_c0_and_accdate_and_refno(int v_accdate,const char *v_refno,T_t_dpsdtl *pt_dpsdtl);
int DB_t_dpsdtl_update_lock_by_c0(T_t_dpsdtl *pt_dpsdtl);
int DB_t_dpsdtl_del_lock_by_c0();
int DB_t_dpsdtl_free_lock_by_c0();
#endif
