#ifndef  __T_vtransdtl_H_
#define  __T_vtransdtl_H_
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
}T_v_transdtl;
int DB_v_transdtl_read_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno,T_v_transdtl *pv_transdtl);
int DB_v_transdtl_read_by_accdate_and_termid_and_devseqno(const char *v_accdate,int v_termid,int v_devseqno,T_v_transdtl *pv_transdtl);
int DB_v_transdtl_read_by_accdate_and_devphyid_and_devseqno(const char *v_accdate,const char *v_devphyid,int v_devseqno,T_v_transdtl *pv_transdtl);
int DB_v_transdtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_v_transdtl *pv_transdtl);
int DB_v_transdtl_del_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno);
int DB_v_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno,T_v_transdtl *pv_transdtl);
int DB_v_transdtl_update_lock_by_c0(T_v_transdtl *pv_transdtl);
int DB_v_transdtl_free_lock_by_c0();
int DB_v_transdtl_read_lock_by_c1_and_accdate_and_termid_and_devseqno(const char *v_accdate,int v_termid,int v_devseqno,T_v_transdtl *pv_transdtl);
int DB_v_transdtl_update_lock_by_c1(T_v_transdtl *pv_transdtl);
int DB_v_transdtl_free_lock_by_c1();
#endif
