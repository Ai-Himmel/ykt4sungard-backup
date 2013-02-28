#ifndef  __T_inneracc_H_
#define  __T_inneracc_H_
typedef struct 
{
		char	accno[10+1];
		char	accname[60+1];
		char	subjno[20+1];
		double	ydaybal;
		double	balance;
		int	balflag;
		char	lasttransdate[8+1];
		char	lastaccdate[8+1];
}T_t_inneracc;
int DB_t_inneracc_add(T_t_inneracc *pt_inneracc);
int DB_t_inneracc_read_by_accno(const char *v_accno,T_t_inneracc *pt_inneracc);
int DB_t_inneracc_update_by_accno(char *v_accno,T_t_inneracc *pt_inneracc);
int DB_t_inneracc_del_by_accno(const char *v_accno);
int DB_t_inneracc_read_lock_by_c0_and_accno(const char *v_accno,T_t_inneracc *pt_inneracc);
int DB_t_inneracc_update_lock_by_c0(T_t_inneracc *pt_inneracc);
int DB_t_inneracc_free_lock_by_c0();
#endif
