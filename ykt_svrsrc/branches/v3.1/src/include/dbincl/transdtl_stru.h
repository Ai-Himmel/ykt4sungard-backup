#ifndef  __T_transdtl_H_
#define  __T_transdtl_H_
typedef struct 
{
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		char	transdate[8+1];
		char	transtime[6+1];
		char	refno[14+1];
		int	transcode;
		int	custid;
		char	custname[60+1];
		char	stuempno[20+1];
		char	showcardno[10+1];
		int	cardno;
		int	purseno;
		int	transflag;
		int	cardcnt;
		double	cardbefbal;
		double	cardaftbal;
		double	amount;
		double	addamt;
		double	managefee;
		int	paytype;
		char	voucherno[20+1];
		char	opercode[8+1];
		int	sysid;
		char	devphyid[20+1];
		int	devseqno;
		int	exttype;
		char	extdata[30+1];
		char	coldate[8+1];
		char	coltime[6+1];
		int	offlineflag;
		char	revflag[1+1];
		char	status[1+1];
		int	errcode;
		char	remark[240+1];
}T_t_transdtl;
int DB_t_transdtl_add(T_t_transdtl *pt_transdtl);
int DB_t_transdtl_read_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_read_by_accdate_and_termid_and_devseqno(char *v_accdate,int v_termid,int v_devseqno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_read_by_accdate_and_devphyid_and_devseqno(char *v_accdate,char *v_devphyid,int v_devseqno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_del_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_update_lock_by_c0(T_t_transdtl *pt_transdtl);
int DB_t_transdtl_free_lock_by_c0();
int DB_t_transdtl_read_lock_by_c1_and_accdate_and_termid_and_devseqno(char *v_accdate,int v_termid,int v_devseqno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_update_lock_by_c1(T_t_transdtl *pt_transdtl);
int DB_t_transdtl_free_lock_by_c1();
int DB_t_transdtl_read_by_refno(char *v_refno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_update_by_refno(char *v_refno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_read_lock_by_c2_and_refno(char *v_refno,T_t_transdtl *pt_transdtl);
int DB_t_transdtl_update_lock_by_c2(T_t_transdtl *pt_transdtl);
int DB_t_transdtl_free_lock_by_c2();
#endif
