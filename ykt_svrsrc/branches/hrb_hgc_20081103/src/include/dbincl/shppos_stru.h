#ifndef  __T_shppos_H_
#define  __T_shppos_H_
typedef struct 
{
		int	id;
		int	device_id;
		int	shop_id;
		char	begin_date[10+1];
		char	begin_time[8+1];
		char	end_time[8+1];
		char	end_date[10+1];
		char	comments[150+1];
}T_t_cif_shop_pos;
int DB_t_cif_shop_pos_add(T_t_cif_shop_pos *pt_cif_shop_pos);
int DB_t_cif_shop_pos_read_by_shop_id(int v_shop_id,T_t_cif_shop_pos *pt_cif_shop_pos);
int DB_t_cif_shop_pos_del_all();
int DB_t_cif_shop_pos_open_select_by_c0_and_device_id(int v_device_id);
int DB_t_cif_shop_pos_fetch_select_by_c0(T_t_cif_shop_pos *pt_cif_shop_pos);
int DB_t_cif_shop_pos_close_select_by_c0();
#endif
