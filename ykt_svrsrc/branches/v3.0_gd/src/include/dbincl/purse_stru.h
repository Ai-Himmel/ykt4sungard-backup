#ifndef  __T_purse_H_
#define  __T_purse_H_
typedef struct 
{
		int	purseno;
		char	pursename[60+1];
		double	cardmaxbal;
		char	useflag[1+1];
}T_t_purse;
int DB_t_purse_add(T_t_purse *pt_purse);
int DB_t_purse_read_by_purseno(int v_purseno,T_t_purse *pt_purse);
int DB_t_purse_update_by_purseno(int v_purseno,T_t_purse *pt_purse);
int DB_t_purse_del_by_purseno(int v_purseno);
#endif
