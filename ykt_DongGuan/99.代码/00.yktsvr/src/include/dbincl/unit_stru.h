#ifndef  __T_unit_H_
#define  __T_unit_H_
typedef struct 
{
		int	unitno;
		char	unitname[60+1];
		int	enabled;
		int	begindate;
		int	lastdate;
}T_t_unit;
int DB_t_unit_add(T_t_unit *pt_unit);
int DB_t_unit_read_by_unitno(int v_unitno,T_t_unit *pt_unit);
int DB_t_unit_update_by_unitno(int v_unitno,T_t_unit *pt_unit);
int DB_t_unit_del_by_unitno(int v_unitno);
int DB_t_unit_read_lock_by_c0_and_unitno(int v_unitno,T_t_unit *pt_unit);
int DB_t_unit_update_lock_by_c0(T_t_unit *pt_unit);
int DB_t_unit_del_lock_by_c0();
int DB_t_unit_free_lock_by_c0();
int DB_t_unit_open_select_by_c1_and_enabled(int v_enabled);
int DB_t_unit_fetch_select_by_c1(T_t_unit *pt_unit);
int DB_t_unit_close_select_by_c1();
#endif
