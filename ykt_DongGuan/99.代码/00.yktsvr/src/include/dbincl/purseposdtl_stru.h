#ifndef  __T_purseposdtl_H_
#define  __T_purseposdtl_H_
typedef struct 
{
		char	transdate[8+1];
		char	transtime[6+1];
		int	termid;
		char	devphyid[20+1];
		int	devseqno;
		int	cardno;
		int	pursetype;
		int	cardcnt;
		double	cardbefbal;
		double	amount;
		double	cardaftbal;
		int	transmark;
		int	datatype;
		int	shopid;
		char	batchno[30+1];
		int	sysid;
		char	coldate[8+1];
		char	coltime[6+1];
		char	accdate[8+1];
		char	acctime[6+1];
		int	termseqno;
		char	status[1+1];
		int	errcode;
		char	errmsg[240+1];
		char	delflag[1+1];
}T_t_purseposdtl;
int DB_t_purseposdtl_add(T_t_purseposdtl *pt_purseposdtl);
int DB_t_purseposdtl_read_by_transdate_and_devphyid_and_devseqno_and_cardno(const char *v_transdate,const char *v_devphyid,int v_devseqno,int v_cardno,T_t_purseposdtl *pt_purseposdtl);
int DB_t_purseposdtl_update_by_transdate_and_devphyid_and_devseqno_and_cardno(char *v_transdate,char *v_devphyid,int v_devseqno,int v_cardno,T_t_purseposdtl *pt_purseposdtl);
int DB_t_purseposdtl_del_by_transdate_and_devphyid_and_devseqno_and_cardno(const char *v_transdate,const char *v_devphyid,int v_devseqno,int v_cardno);
int DB_t_purseposdtl_read_lock_by_c0_and_transdate_and_devphyid_and_devseqno_and_cardno(const char *v_transdate,const char *v_devphyid,int v_devseqno,int v_cardno,T_t_purseposdtl *pt_purseposdtl);
int DB_t_purseposdtl_update_lock_by_c0(T_t_purseposdtl *pt_purseposdtl);
int DB_t_purseposdtl_free_lock_by_c0();
#endif
