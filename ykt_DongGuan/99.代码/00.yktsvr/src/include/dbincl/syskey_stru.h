#ifndef  __T_syskey_H_
#define  __T_syskey_H_
typedef struct 
{
		char	keycode[60+1];
		char	keyname[60+1];
		int	keyval;
		int	maxval;
		char	keytype[0+1];
}T_t_syskey;
int DB_t_syskey_add(T_t_syskey *pt_syskey);
int DB_t_syskey_del_by_keycode(const char *v_keycode);
int DB_t_syskey_read_by_keycode(const char *v_keycode,T_t_syskey *pt_syskey);
int DB_t_syskey_read_lock_by_cur_and_keycode(const char *v_keycode,T_t_syskey *pt_syskey);
int DB_t_syskey_update_by_keycode(char *v_keycode,T_t_syskey *pt_syskey);
int DB_t_syskey_update_lock_by_cur(T_t_syskey *pt_syskey);
int DB_t_syskey_free_lock_cur();
#endif
