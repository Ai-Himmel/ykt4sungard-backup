#ifndef  __T_depshop_H_
#define  __T_depshop_H_
typedef struct 
{
		int	shop_id;
		char	status[1+1];
		char	account_id[30+1];
		char	shop_name[240+1];
		char	shop_man_name[30+1];
		int	id_type;
		char	id_no[60+1];
		char	open_date[8+1];
		char	close_date[8+1];
		double	deposit_ratio;
		int	deposit_total_cnt;
		double	deposit_total_amt;
		double	discount_total_amt;
}T_t_deposit_shop;
int DB_t_deposit_shop_add(T_t_deposit_shop *pt_deposit_shop);
int DB_t_deposit_shop_read_by_shop_id(int v_shop_id,T_t_deposit_shop *pt_deposit_shop);
int DB_t_deposit_shop_read_lock_by_cur_and_shop_id(int v_shop_id,T_t_deposit_shop *pt_deposit_shop);
int DB_t_deposit_shop_update_lock_by_cur(T_t_deposit_shop *pt_deposit_shop);
int DB_t_deposit_shop_free_lock_by_cur();
#endif
