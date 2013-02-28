#ifndef  __T_unitcfg_H_
#define  __T_unitcfg_H_
typedef struct 
{
		char	paraname[60+1];
		char	paraval[240+1];
		char	paradesc[240+1];
}T_t_unitcfg;
int DB_t_unitcfg_add(T_t_unitcfg *pt_unitcfg);
int DB_t_unitcfg_read_by_paraname(const char *v_paraname,T_t_unitcfg *pt_unitcfg);
int DB_t_unitcfg_update_by_paraname(char *v_paraname,T_t_unitcfg *pt_unitcfg);
int DB_t_unitcfg_del_by_paraname(const char *v_paraname);
int DB_t_unitcfg_read_lock_by_c0_and_paraname(const char *v_paraname,T_t_unitcfg *pt_unitcfg);
int DB_t_unitcfg_update_lock_by_c0(T_t_unitcfg *pt_unitcfg);
int DB_t_unitcfg_del_lock_by_c0();
int DB_t_unitcfg_free_lock_by_c0();
#endif
