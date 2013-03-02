#ifndef  __T_trdcdshp_H_
#define  __T_trdcdshp_H_
typedef struct 
{
		int	trade_code;
		int	shop_id;
}T_t_tradecode_shop;
int DB_t_tradecode_shop_add(T_t_tradecode_shop *pt_tradecode_shop);
int DB_t_tradecode_shop_read_lock_by_c1_and_trade_code_and_shop_id(int v_trade_code,int v_shop_id,T_t_tradecode_shop *pt_tradecode_shop);
int DB_t_tradecode_shop_update_lock_by_c1_and_trade_code_and_shop_id(T_t_tradecode_shop *pt_tradecode_shop);
int DB_t_tradecode_shop_free_lock_by_c1();
int DB_t_tradecode_shop_open_select_by_c0_and_trade_code(int v_trade_code);
int DB_t_tradecode_shop_fetch_select_by_c0(T_t_tradecode_shop *pt_tradecode_shop);
int DB_t_tradecode_shop_close_select_by_c0();
#endif
