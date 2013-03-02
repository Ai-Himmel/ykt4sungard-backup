#ifndef  __T_syskey_H_
#define  __T_syskey_H_
typedef struct 
{
		char	key_code[60+1];
		char	key_name[60+1];
		int	key_value;
		int	max_value;
}T_t_pif_syskey;
int DB_t_pif_syskey_add(T_t_pif_syskey *pt_pif_syskey);
int DB_t_pif_syskey_del_by_key_code(char *v_key_code);
int DB_t_pif_syskey_read_by_key_code(char *v_key_code,T_t_pif_syskey *pt_pif_syskey);
int DB_t_pif_syskey_read_lock_by_cur_and_key_code(char *v_key_code,T_t_pif_syskey *pt_pif_syskey);
int DB_t_pif_syskey_update_by_key_code(char *v_key_code,T_t_pif_syskey *pt_pif_syskey);
int DB_t_pif_syskey_update_lock_by_cur(T_t_pif_syskey *pt_pif_syskey);
int DB_t_pif_syskey_free_lock_cur();
#endif
