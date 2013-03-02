#ifndef  __T_cardtype_H_
#define  __T_cardtype_H_
typedef struct 
{
		int	cardtype;
		char	cardtypename[60+1];
		char	anonymflag[1+1];
		int	feetype;
		int	cardcostfee;
		char	reuseable[1+1];
		char	renewable[1+1];
		char	recycleable[1+1];
		char	fixdayflag[1+1];
		int	fixdaycnt;
		char	purpose[240+1];
		char	useflag[1+1];
}T_t_cardtype;
int DB_t_cardtype_add(T_t_cardtype *pt_cardtype);
int DB_t_cardtype_read_by_cardtype(int v_cardtype,T_t_cardtype *pt_cardtype);
int DB_t_cardtype_read_by_anonymflag(char *v_anonymflag,T_t_cardtype *pt_cardtype);
int DB_t_cardtype_update_by_cardtype(int v_cardtype,T_t_cardtype *pt_cardtype);
int DB_t_cardtype_del_by_cardtype(int v_cardtype);
int DB_t_cardtype_read_lock_by_c0_and_cardtype(int v_cardtype,T_t_cardtype *pt_cardtype);
int DB_t_cardtype_update_lock_by_c0(T_t_cardtype *pt_cardtype);
int DB_t_cardtype_free_lock_by_c0();
#endif
