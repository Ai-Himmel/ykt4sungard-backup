#ifndef  __T_pursetransdtl_H_
#define  __T_pursetransdtl_H_
typedef struct 
{
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		int	pursetype;
		char	transdate[8+1];
		char	transtime[6+1];
		char	refno[14+1];
		int	transcode;
		int	custid;
		char	custname[60+1];
		char	stuempno[20+1];
		char	showcardno[10+1];
		int	cardno;
		int	transflag;
		int	cardcnt;
		double	cardbefbal;
		double	cardaftbal;
		double	amount;
		char	opercode[8+1];
		int	sysid;
		char	devphyid[20+1];
		int	devseqno;
		char	coldate[8+1];
		char	coltime[6+1];
		char	status[1+1];
		int	errcode;
		char	remark[240+1];
}T_t_pursetransdtl;
int DB_t_pursetransdtl_add(T_t_pursetransdtl *pt_pursetransdtl);
int DB_t_pursetransdtl_read_by_accdate_and_termid_and_termseqno_and_pursetype_and_cardno(const char *v_accdate,int v_termid,int v_termseqno,int v_pursetype,int v_cardno,T_t_pursetransdtl *pt_pursetransdtl);
int DB_t_pursetransdtl_update_by_accdate_and_termid_and_termseqno_and_pursetype_and_cardno(char *v_accdate,int v_termid,int v_termseqno,int v_pursetype,int v_cardno,T_t_pursetransdtl *pt_pursetransdtl);
int DB_t_pursetransdtl_del_by_accdate_and_termid_and_termseqno_and_pursetype_and_cardno(const char *v_accdate,int v_termid,int v_termseqno,int v_pursetype,int v_cardno);
int DB_t_pursetransdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno_and_pursetype_and_cardno(const char *v_accdate,int v_termid,int v_termseqno,int v_pursetype,int v_cardno,T_t_pursetransdtl *pt_pursetransdtl);
int DB_t_pursetransdtl_update_lock_by_c0(T_t_pursetransdtl *pt_pursetransdtl);
int DB_t_pursetransdtl_free_lock_by_c0();
#endif
