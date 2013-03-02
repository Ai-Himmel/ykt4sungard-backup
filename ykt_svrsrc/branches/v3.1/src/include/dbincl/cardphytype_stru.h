#ifndef  __T_cardphytype_H_
#define  __T_cardphytype_H_
typedef struct 
{
		int	cardphytype;
		char	cardphytypename[60+1];
		int	useflag;
		int	cardphytypecode;
}T_t_cardphytype;
int DB_t_cardphytype_add(T_t_cardphytype *pt_cardphytype);
int DB_t_cardphytype_read_by_cardphytype(int v_cardphytype,T_t_cardphytype *pt_cardphytype);
int DB_t_cardphytype_update_by_cardphytype(int v_cardphytype,T_t_cardphytype *pt_cardphytype);
int DB_t_cardphytype_del_by_cardphytype(int v_cardphytype);
int DB_t_cardphytype_read_lock_by_c0_and_cardphytype(int v_cardphytype,T_t_cardphytype *pt_cardphytype);
int DB_t_cardphytype_update_lock_by_c0(T_t_cardphytype *pt_cardphytype);
int DB_t_cardphytype_free_lock_by_c0();
#endif
