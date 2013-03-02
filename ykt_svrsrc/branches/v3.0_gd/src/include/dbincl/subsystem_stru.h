#ifndef  __T_subsystem_H_
#define  __T_subsystem_H_
typedef struct 
{
		int	sysid;
		char	sysname[60+1];
		int	systype;
		char	runstatus[1+1];
		char	status[1+1];
		char	areacode[3+1];
		char	macaddr[20+1];
		char	ip[20+1];
		int	port;
		char	cardverno[12+1];
		char	initkey[32+1];
		char	dynakey[32+1];
		char	synctime[26+1];
		char	remark[100+1];
}T_t_subsystem;
int DB_t_subsystem_add(T_t_subsystem *pt_subsystem);
int DB_t_subsystem_read_by_sysid(int v_sysid,T_t_subsystem *pt_subsystem);
int DB_t_subsystem_update_by_sysid(int v_sysid,T_t_subsystem *pt_subsystem);
int DB_t_subsystem_del_by_sysid(int v_sysid);
int DB_t_subsystem_read_lock_by_c0_and_sysid(int v_sysid,T_t_subsystem *pt_subsystem);
int DB_t_subsystem_update_lock_by_c0(T_t_subsystem *pt_subsystem);
int DB_t_subsystem_free_lock_by_c0();
#endif
