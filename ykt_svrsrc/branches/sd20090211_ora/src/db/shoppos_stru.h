#ifndef  __T_shoppos_H_
#define  __T_shoppos_H_
typedef struct 
{
		char	device_id[30+1];
		int	shop_id;
		char	open_oper[30+1];
		char	last_saved[30+1];
}T_t_deposit_shoppos;
int DB_t_deposit_shoppos_add(T_t_deposit_shoppos *pt_deposit_shoppos);
int DB_t_deposit_shoppos_read_by_device_id(char *v_device_id,T_t_deposit_shoppos *pt_deposit_shoppos);
int DB_t_deposit_shoppos_del_by_device_id(char *v_device_id);
int DB_t_deposit_shoppos_del_by_shop_id(int v_shop_id);
#endif
