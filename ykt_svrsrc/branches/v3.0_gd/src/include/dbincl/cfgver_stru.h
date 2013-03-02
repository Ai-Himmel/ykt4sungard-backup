#ifndef  __T_cfgver_H_
#define  __T_cfgver_H_
typedef struct 
{
		int	cfgtype;
		int	cfgverno;
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_cfgver;
int DB_t_cfgver_add(T_t_cfgver *pt_cfgver);
int DB_t_cfgver_read_by_cfgtype(int v_cfgtype,T_t_cfgver *pt_cfgver);
int DB_t_cfgver_update_by_cfgtype(int v_cfgtype,T_t_cfgver *pt_cfgver);
int DB_t_cfgver_del_by_cfgtype(int v_cfgtype);
int DB_t_cfgver_read_lock_by_c0_and_cfgtype(int v_cfgtype,T_t_cfgver *pt_cfgver);
int DB_t_cfgver_update_lock_by_c0(T_t_cfgver *pt_cfgver);
int DB_t_cfgver_free_lock_by_c0();
#endif
