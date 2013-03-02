#ifndef  __T_shoprate_H_
#define  __T_shoprate_H_
typedef struct 
{
		int	shop_id;
		int	feetype;
		int	rate;
}T_t_cif_shop_feerate;
int DB_t_cif_shop_feerate_add(T_t_cif_shop_feerate *pt_cif_shop_feerate);
int DB_t_cif_shop_feerate_open_select_by_c0_and_shop_id(int v_shop_id);
int DB_t_cif_shop_feerate_fetch_select_by_c0(T_t_cif_shop_feerate *pt_cif_shop_feerate);
int DB_t_cif_shop_feerate_close_select_by_c0();
int DB_t_cif_shop_feerate_del_by_shop_id_and_feetype(int v_shop_id,int v_feetype);
int DB_t_cif_shop_feerate_update_by_shop_id_and_feetype(int v_shop_id,int v_feetype,T_t_cif_shop_feerate *pt_cif_shop_feerate);
#endif
