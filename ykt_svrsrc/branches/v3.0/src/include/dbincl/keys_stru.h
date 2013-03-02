#ifndef  __T_keys_H_
#define  __T_keys_H_
typedef struct 
{
		int	keyid;
		char	keyvalue[64+1];
		char	summary[200+1];
}T_t_keys;
int DB_t_keys_read_by_keyid(int v_keyid,T_t_keys *pt_keys);
#endif
