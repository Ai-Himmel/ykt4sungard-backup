#ifndef  __T_bankchkcfg_H_
#define  __T_bankchkcfg_H_
typedef struct 
{
		int	bankid;
		char	localchktype[1+1];
		char	chkbegindate[8+1];
		char	chkdate[8+1];
		char	chkbegintime[6+1];
		char	cvtexecfile[240+1];
		char	chkexecfile[240+1];
		int	autoresolve;
}T_t_bankchkcfg;
int DB_t_bankchkcfg_add(T_t_bankchkcfg *pt_bankchkcfg);
int DB_t_bankchkcfg_read_by_bankid(int v_bankid,T_t_bankchkcfg *pt_bankchkcfg);
int DB_t_bankchkcfg_update_by_bankid(int v_bankid,T_t_bankchkcfg *pt_bankchkcfg);
int DB_t_bankchkcfg_del_by_bankid(int v_bankid);
int DB_t_bankchkcfg_read_lock_by_c0_and_bankid(int v_bankid,T_t_bankchkcfg *pt_bankchkcfg);
int DB_t_bankchkcfg_update_lock_by_c0(T_t_bankchkcfg *pt_bankchkcfg);
int DB_t_bankchkcfg_del_lock_by_c0();
int DB_t_bankchkcfg_free_lock_by_c0();
#endif
