#ifndef  __T_cardtransdtl_H_
#define  __T_cardtransdtl_H_
typedef struct 
{
		int	cardno;
		int	transflag;
		int	cardcnt;
		char	transdate[8+1];
		char	transtime[6+1];
		char	termno[12+1];
		int	termsno;
		double	cardbefbal;
		double	amount;
		double	addamt;
		double	managefee;
		int	shopid;
		char	coldate[8+1];
		char	coltime[6+1];
		int	status;
		char	remark[240+1];
}T_t_cardtransdtl;
int DB_t_cardtransdtl_add(T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_read_by_cardno_and_transflag_and_cardcnt(int v_cardno,int v_transflag,int v_cardcnt,T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_update_by_cardno_and_transflag_and_cardcnt(int v_cardno,int v_transflag,int v_cardcnt,T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_del_by_cardno_and_transflag_and_cardcnt(int v_cardno,int v_transflag,int v_cardcnt);
int DB_t_cardtransdtl_read_lock_by_c0_and_cardno_and_transflag_and_cardcnt(int v_cardno,int v_transflag,int v_cardcnt,T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_update_lock_by_c0(T_t_cardtransdtl *pt_cardtransdtl);
int DB_t_cardtransdtl_free_lock_by_c0();
#endif
