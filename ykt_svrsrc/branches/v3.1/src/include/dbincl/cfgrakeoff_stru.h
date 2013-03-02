#ifndef  __T_cfgrakeoff_H_
#define  __T_cfgrakeoff_H_
typedef struct 
{
		int	shopid;
		int	amount;
		double	agio;
		char	remark[240+1];
}T_t_cfgrakeoff;
int DB_t_cfgrakeoff_open_select_by_c0_and_shopid(int v_shopid);
int DB_t_cfgrakeoff_fetch_select_by_c0(T_t_cfgrakeoff *pt_cfgrakeoff);
int DB_t_cfgrakeoff_close_select_by_c0();
int DB_t_cfgrakeoff_add(T_t_cfgrakeoff *pt_cfgrakeoff);
int DB_t_cfgrakeoff_read_lock_by_c1_and_shopid_and_amount(int v_shopid,int v_amount,T_t_cfgrakeoff *pt_cfgrakeoff);
int DB_t_cfgrakeoff_update_lock_by_c1(T_t_cfgrakeoff *pt_cfgrakeoff);
int DB_t_cfgrakeoff_free_lock_c1();
int DB_t_cfgrakeoff_del_by_shopid(int v_shopid);
int DB_t_cfgrakeoff_del_by_shopid_and_amount(int v_shopid,int v_amount);
int DB_t_cfgrakeoff_read_by_shopid_and_amount(int v_shopid,int v_amount,T_t_cfgrakeoff *pt_cfgrakeoff);
#endif
