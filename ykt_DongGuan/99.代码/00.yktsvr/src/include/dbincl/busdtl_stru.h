#ifndef  __T_busdtl_H_
#define  __T_busdtl_H_
typedef struct 
{
		char	transdate[8+1];
		char	transtime[6+1];
		char	devphyid[20+1];
		int	devseqno;
		int	cardno;
		int	cardcnt;
		double	cardbefbal;
		double	amount;
		double	cardaftbal;
		int	transmark;
		int	datatype;
		int	shopid;
		char	stuempno[20+1];
		int	custid;
		char	custname[60+1];
		char	deptcode[30+1];
		int	feetype;
		char	batchno[30+1];
		char	coldate[8+1];
		char	coltime[6+1];
		char	accdate[8+1];
		char	acctime[6+1];
		int	termid;
		int	termseqno;
		char	status[1+1];
		int	errcode;
		char	errmsg[240+1];
}T_t_busdtl;
int DB_t_busdtl_add(T_t_busdtl *pt_busdtl);
int DB_t_busdtl_read_by_transdate_and_devphyid_and_devseqno(const char *v_transdate,const char *v_devphyid,int v_devseqno,T_t_busdtl *pt_busdtl);
int DB_t_busdtl_update_by_transdate_and_devphyid_and_devseqno(char *v_transdate,char *v_devphyid,int v_devseqno,T_t_busdtl *pt_busdtl);
int DB_t_busdtl_del_by_transdate_and_devphyid_and_devseqno(const char *v_transdate,const char *v_devphyid,int v_devseqno);
int DB_t_busdtl_read_lock_by_c0_and_transdate_and_devphyid_and_devseqno(const char *v_transdate,const char *v_devphyid,int v_devseqno,T_t_busdtl *pt_busdtl);
int DB_t_busdtl_update_lock_by_c0(T_t_busdtl *pt_busdtl);
int DB_t_busdtl_del_lock_by_c0();
int DB_t_busdtl_free_lock_by_c0();
int DB_t_busdtl_open_select_by_c1_and_transdate_and_devphyid_and_devseqno(const char *v_transdate,const char *v_devphyid,int v_devseqno);
int DB_t_busdtl_fetch_select_by_c1(T_t_busdtl *pt_busdtl);
int DB_t_busdtl_close_select_by_c1();
#endif
