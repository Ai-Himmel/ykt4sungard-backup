#ifndef  __T_cardkeys_H_
#define  __T_cardkeys_H_
typedef struct 
{
		int	keyid;
		char	keyvalue[32+1];
		char	remark[240+1];
}T_t_cardkeys;
int DB_t_cardkeys_read_by_keyid(int v_keyid,T_t_cardkeys *pt_cardkeys);
#endif
