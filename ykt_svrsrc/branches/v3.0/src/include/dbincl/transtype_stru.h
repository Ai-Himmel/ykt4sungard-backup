#ifndef  __T_transtype_H_
#define  __T_transtype_H_
typedef struct 
{
		int	transtype;
		char	transname[60+1];
		char	displayflag[1+1];
		char	useflag[1+1];
}T_t_transtype;
int DB_t_transtype_add(T_t_transtype *pt_transtype);
int DB_t_transtype_read_by_transtype(int v_transtype,T_t_transtype *pt_transtype);
int DB_t_transtype_update_by_transtype(int v_transtype,T_t_transtype *pt_transtype);
int DB_t_transtype_del_by_transtype(int v_transtype);
int DB_t_transtype_read_lock_by_c0_and_transtype(int v_transtype,T_t_transtype *pt_transtype);
int DB_t_transtype_update_lock_by_c0(T_t_transtype *pt_transtype);
int DB_t_transtype_free_lock_by_c0();
#endif
