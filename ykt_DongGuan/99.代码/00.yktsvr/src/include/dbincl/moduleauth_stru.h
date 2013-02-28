#ifndef  __T_moduleauth_H_
#define  __T_moduleauth_H_
typedef struct 
{
		char	modulecode[30+1];
		char	modulename[60+1];
		char	menuset[800+1];
		char	funcset[600+1];
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_moduleauth;
int DB_t_moduleauth_add(T_t_moduleauth *pt_moduleauth);
int DB_t_moduleauth_read_by_modulecode(const char *v_modulecode,T_t_moduleauth *pt_moduleauth);
int DB_t_moduleauth_update_by_modulecode(char *v_modulecode,T_t_moduleauth *pt_moduleauth);
int DB_t_moduleauth_del_by_modulecode(const char *v_modulecode);
int DB_t_moduleauth_read_lock_by_c0_and_modulecode(const char *v_modulecode,T_t_moduleauth *pt_moduleauth);
int DB_t_moduleauth_update_lock_by_c0(T_t_moduleauth *pt_moduleauth);
int DB_t_moduleauth_free_lock_by_c0();
#endif
