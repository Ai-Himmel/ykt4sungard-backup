#ifndef  __T_posdtl_H_
#define  __T_posdtl_H_
typedef struct 
{
		char	transdate[8+1];
		char	transtime[6+1];
		char	devphyid[30+1];
		int	devseqno;
		int	cardno;
		int	purseno;
		int	cardcnt;
		double	cardbefbal;
		double	amount;
		double	cardaftbal;
		double	managefee;
		int	transmark;
		int	transcode;
		int	shopid;
		int	subsidyno;
		char	batchno[30+1];
		int	sysid;
		char	coldate[8+1];
		char	coltime[6+1];
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		char	status[1+1];
		int	errcode;
		char	errmsg[240+1];
		char	delflag[1+1];
}T_t_posdtl;
int DB_t_posdtl_add(T_t_posdtl *pt_posdtl);
int DB_t_posdtl_read_by_transdate_and_devphyid_and_devseqno(char *v_transdate,char *v_devphyid,int v_devseqno,T_t_posdtl *pt_posdtl);
int DB_t_posdtl_update_by_transdate_and_devphyid_and_devseqno(char *v_transdate,char *v_devphyid,int v_devseqno,T_t_posdtl *pt_posdtl);
int DB_t_posdtl_del_by_transdate_and_devphyid_and_devseqno(char *v_transdate,char *v_devphyid,int v_devseqno);
int DB_t_posdtl_read_lock_by_c0_and_transdate_and_devphyid_and_devseqno(char *v_transdate,char *v_devphyid,int v_devseqno,T_t_posdtl *pt_posdtl);
int DB_t_posdtl_update_lock_by_c0(T_t_posdtl *pt_posdtl);
int DB_t_posdtl_del_lock_by_c0();
int DB_t_posdtl_free_lock_by_c0();
int DB_t_posdtl_open_select_by_c1_and_transdate_and_devphyid_and_devseqno(char *v_transdate,char *v_devphyid,int v_devseqno);
int DB_t_posdtl_fetch_select_by_c1(T_t_posdtl *pt_posdtl);
int DB_t_posdtl_close_select_by_c1();
#endif
