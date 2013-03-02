#ifndef  __T_subsys_H_
#define  __T_subsys_H_
typedef struct 
{
		int	system_id;
		char	system_name[60+1];
		int	system_type;
		int	state;
		int	area;
		int	server_id;
		char	ip[20+1];
		char	mac_addr[20+1];
		char	init_key[32+1];
		char	dyna_key[32+1];
		char	synch_time[26+1];
		int	version;
		char	manager[20+1];
		char	tel[20+1];
		char	address[150+1];
		char	comments[150+1];
		int	port;
}T_t_pif_subsystem;
int DB_t_pif_subsystem_add(T_t_pif_subsystem *pt_pif_subsystem);
int DB_t_pif_subsystem_read_by_system_id(int v_system_id,T_t_pif_subsystem *pt_pif_subsystem);
int DB_t_pif_subsystem_open_select_by_c0_and_system_type_and_state(int v_system_type,int v_state);
int DB_t_pif_subsystem_fetch_select_by_c0(T_t_pif_subsystem *pt_pif_subsystem);
int DB_t_pif_subsystem_close_select_by_c0();
int DB_t_pif_subsystem_open_select_by_c1_and_system_type(int v_system_type);
int DB_t_pif_subsystem_fetch_select_by_c1(T_t_pif_subsystem *pt_pif_subsystem);
int DB_t_pif_subsystem_close_select_by_c1();
#endif
