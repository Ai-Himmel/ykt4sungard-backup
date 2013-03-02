#ifndef  __T_syspara_H_
#define  __T_syspara_H_
typedef struct 
{
		int	paraid;
		char	paraval[60+1];
		char	paraname[60+1];
		char	paraunit[30+1];
		char	displayflag[1+1];
		char	remark[240+1];
		char	lastsaved[30+1];
}T_t_syspara;
int DB_t_syspara_add(T_t_syspara *pt_syspara);
int DB_t_syspara_read_by_paraid(int v_paraid,T_t_syspara *pt_syspara);
int DB_t_syspara_update_by_paraid(int v_paraid,T_t_syspara *pt_syspara);
int DB_t_syspara_del_by_paraid(int v_paraid);
int DB_t_syspara_read_lock_by_c0_and_paraid(int v_paraid,T_t_syspara *pt_syspara);
int DB_t_syspara_update_lock_by_c0(T_t_syspara *pt_syspara);
int DB_t_syspara_free_lock_by_c0();
#endif
