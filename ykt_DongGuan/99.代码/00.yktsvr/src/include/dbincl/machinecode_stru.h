#ifndef  __T_machinecode_H_
#define  __T_machinecode_H_
typedef struct 
{
		char	machinecode[60+1];
		char	ip[15+1];
		char	lastsaved[30+1];
}T_t_machinecode;
int DB_t_machinecode_add(T_t_machinecode *pt_machinecode);
int DB_t_machinecode_read_by_ip(const char *v_ip,T_t_machinecode *pt_machinecode);
int DB_t_machinecode_read_by_machinecode(const char *v_machinecode,T_t_machinecode *pt_machinecode);
int DB_t_machinecode_update_by_machinecode(char *v_machinecode,T_t_machinecode *pt_machinecode);
int DB_t_machinecode_del_by_machinecode(const char *v_machinecode);
int DB_t_machinecode_del_by_ip(const char *v_ip);
int DB_t_machinecode_read_lock_by_c0_and_machinecode(const char *v_machinecode,T_t_machinecode *pt_machinecode);
int DB_t_machinecode_update_lock_by_c0(T_t_machinecode *pt_machinecode);
int DB_t_machinecode_free_lock_by_c0();
#endif
