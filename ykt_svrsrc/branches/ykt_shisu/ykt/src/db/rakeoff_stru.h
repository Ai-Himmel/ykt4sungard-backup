#ifndef  __T_rakeoff_H_
#define  __T_rakeoff_H_
typedef struct 
{
		int	shop_id;
		int	amount;
		double	agio;
		char	agio_desc[240+1];
}T_t_cfg_rakeoff;
int DB_t_cfg_rakeoff_open_select_by_c0_and_shop_id(int v_shop_id);
int DB_t_cfg_rakeoff_fetch_select_by_c0(T_t_cfg_rakeoff *pt_cfg_rakeoff);
int DB_t_cfg_rakeoff_close_select_by_c0();
int DB_t_cfg_rakeoff_add(T_t_cfg_rakeoff *pt_cfg_rakeoff);
int DB_t_cfg_rakeoff_read_lock_by_c1_and_shop_id_and_amount(int v_shop_id,int v_amount,T_t_cfg_rakeoff *pt_cfg_rakeoff);
int DB_t_cfg_rakeoff_update_lock_by_c1(T_t_cfg_rakeoff *pt_cfg_rakeoff);
int DB_t_cfg_rakeoff_free_lock_c1();
int DB_t_cfg_rakeoff_del_by_shop_id(int v_shop_id);
int DB_t_cfg_rakeoff_del_by_shop_id_and_amount(int v_shop_id,int v_amount);
int DB_t_cfg_rakeoff_read_by_shop_id_and_amount(int v_shop_id,int v_amount,T_t_cfg_rakeoff *pt_cfg_rakeoff);
#endif
