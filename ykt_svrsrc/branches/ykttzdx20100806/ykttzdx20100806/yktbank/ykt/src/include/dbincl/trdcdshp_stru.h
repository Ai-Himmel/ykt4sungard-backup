#ifndef  __T_trdcdshp_H_
#define  __T_trdcdshp_H_
typedef struct 
{
		int	trade_code;
		int	shop_id;
}T_t_tradecode_shop;
int DB_t_tradecode_shop_add(T_t_tradecode_shop *pt_tradecode_shop);
int DB_t_tradecode_shop_read_lock_by_c1_and_trade_code(int v_trade_code,T_t_tradecode_shop *pt_tradecode_shop);
int DB_t_tradecode_shop_update_lock_by_c1_and_trade_code(T_t_tradecode_shop *pt_tradecode_shop);
int DB_t_tradecode_shop_free_lock_by_c1();
int DB_t_tradecode_shop_read_by_trade_code(int v_trade_code,T_t_tradecode_shop *pt_tradecode_shop);
#endif
