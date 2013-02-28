#ifndef  __T_rptshoprakeoff_H_
#define  __T_rptshoprakeoff_H_
typedef struct 
{
		char	accdate[8+1];
		int	shopid;
		char	accno[20+1];
		char	accname[60+1];
		double	rakeoffrate;
		int	transcnt;
		double	transamt;
		double	rakeoffamt;
		double	amount;
		double	balance;
}T_t_rptshoprakeoff;
int DB_t_rptshoprakeoff_add(T_t_rptshoprakeoff *pt_rptshoprakeoff);
int DB_t_rptshoprakeoff_read_by_accdate_and_accno(const char *v_accdate,const char *v_accno,T_t_rptshoprakeoff *pt_rptshoprakeoff);
int DB_t_rptshoprakeoff_update_by_accdate_and_accno(char *v_accdate,char *v_accno,T_t_rptshoprakeoff *pt_rptshoprakeoff);
int DB_t_rptshoprakeoff_del_by_accdate_and_accno(const char *v_accdate,const char *v_accno);
int DB_t_rptshoprakeoff_read_lock_by_c0_and_accdate_and_accno(const char *v_accdate,const char *v_accno,T_t_rptshoprakeoff *pt_rptshoprakeoff);
int DB_t_rptshoprakeoff_update_lock_by_c0(T_t_rptshoprakeoff *pt_rptshoprakeoff);
int DB_t_rptshoprakeoff_free_lock_by_c0();
#endif
