#ifndef  __T_cfgbank_H_
#define  __T_cfgbank_H_
typedef struct 
{
		char	bankcode[2+1];
		char	bankname[30+1];
		char	bankstarttime[6+1];
		char	bankendtime[6+1];
		char	bankip[15+1];
		int	bankport;
		int	banktimeout;
		int	bccdrtpno;
		int	bccfuncno;
		int	bcctimeout;
}T_t_cfgbank;
int DB_t_cfgbank_add(T_t_cfgbank *pt_cfgbank);
int DB_t_cfgbank_read_by_bankcode(const char *v_bankcode,T_t_cfgbank *pt_cfgbank);
#endif
