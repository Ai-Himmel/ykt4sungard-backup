#ifndef  __T_cardtransdtl_H_
#define  __T_cardtransdtl_H_
typedef struct 
{
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		char	transdate[8+1];
		char	transtime[6+1];
		char	coldate[8+1];
		char	coltime[6+1];
		int	transcode;
		int	paytype;
		char	voucherno[30+1];
		int	custid;
		int	cardno;
		int	purseno;
		int	cardcnt;
		double	amount;
		double	cardbefbal;
		double	cardaftbal;
		double	boardfee;
		char	opercode[8+1];
		int	subsysid;
		char	devphyid[30+1];
		int	devseqno;
		char	bankcode[2+1];
		char	bankcardno[30+1];
		char	mobile[30+1];
		char	revflag[1+1];
		char	status[1+1];
		int	errcode;
}T_t_cardtransdtl;
int DB_t_cardtransdtl_add(T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_read_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_del_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_cardtransdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_update_lock_by_c0(T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_free_lock_by_c0();
#endif
