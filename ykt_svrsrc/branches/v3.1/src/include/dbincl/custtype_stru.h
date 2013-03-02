#ifndef  __T_custtype_H_
#define  __T_custtype_H_
typedef struct 
{
		int	custtype;
		char	custtypename[60+1];
		int	feetype;
		char	useflag[1+1];
}T_t_custtype;
int DB_t_custtype_add(T_t_custtype *pt_custtype);
int DB_t_custtype_read_by_custtype(int v_custtype,T_t_custtype *pt_custtype);
int DB_t_custtype_update_by_custtype(int v_custtype,T_t_custtype *pt_custtype);
int DB_t_custtype_del_by_custtype(int v_custtype);
int DB_t_custtype_read_lock_by_c0_and_custtype(int v_custtype,T_t_custtype *pt_custtype);
int DB_t_custtype_update_lock_by_c0(T_t_custtype *pt_custtype);
int DB_t_custtype_free_lock_by_c0();
#endif
