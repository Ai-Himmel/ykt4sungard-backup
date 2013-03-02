#ifndef  __T_extposdtl_H_
#define  __T_extposdtl_H_
typedef struct 
{
		char	transdate[8+1];
		char	transtime[6+1];
		int	termid;
		char	devphyid[20+1];
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
}T_t_extposdtl;
int DB_t_extposdtl_add(T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_del_by_status(char *v_status);
int DB_t_extposdtl_read_by_transdate_and_transtime_and_cardno_and_devphyid_and_devseqno(char *v_transdate,char *v_transtime,int v_cardno,char *v_devphyid,int v_devseqno,T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_read_lock_by_c0_and_transdate_and_transtime_and_cardno_and_devphyid_and_devseqno(char *v_transdate,char *v_transtime,int v_cardno,char *v_devphyid,int v_devseqno,T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_update_lock_by_c0(T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_free_lock_c0();
int DB_t_extposdtl_read_lock_by_c1_and_devseqno_and_transdate_and_transtime_and_devphyid_and_cardno_and_transcode(int v_devseqno,char *v_transdate,char *v_transtime,char *v_devphyid,int v_cardno,int v_transcode,T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_update_lock_by_c1(T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_free_lock_c1();
int DB_t_extposdtl_update_by_transdate_and_transtime_and_cardno_and_devphyid_and_devseqno(char *v_transdate,char *v_transtime,int v_cardno,char *v_devphyid,int v_devseqno,T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_open_select_for_update_by_c2_and_status(char *v_status);
int DB_t_extposdtl_fetch_select_by_c2(T_t_extposdtl *pt_extposdtl);
int DB_t_extposdtl_close_select_by_c2();
int DB_t_extposdtl_read_by_transdate_and_transtime_and_devphyid_and_devseqno(char *v_transdate,char *v_transtime,char *v_devphyid,int v_devseqno,T_t_extposdtl *pt_extposdtl);
#endif
