#ifndef  __T_cardtype_H_
#define  __T_cardtype_H_
typedef struct 
{
		int	cardtype;
		char	cardtypename[60+1];
		int	cardphytype;
		int	anonymflag;
		int	prestoreamt;
		int	cardcostfee;
		int	maxdpsamt;
		int	maxcardbal;
		int	reuseable;
		int	renewable;
		int	recycleable;
		int	fixdayflag;
		int	fixdaycnt;
		int	enabled;
		char	remark[240+1];
}T_t_cardtype;
int DB_t_cardtype_add(T_t_cardtype *pt_cardtype);
int DB_t_cardtype_read_by_cardtype(int v_cardtype,T_t_cardtype *pt_cardtype);
int DB_t_cardtype_update_by_cardtype(int v_cardtype,T_t_cardtype *pt_cardtype);
int DB_t_cardtype_del_by_cardtype(int v_cardtype);
int DB_t_cardtype_read_lock_by_c0_and_cardtype(int v_cardtype,T_t_cardtype *pt_cardtype);
int DB_t_cardtype_update_lock_by_c0(T_t_cardtype *pt_cardtype);
int DB_t_cardtype_del_lock_by_c0();
int DB_t_cardtype_free_lock_by_c0();
#endif
