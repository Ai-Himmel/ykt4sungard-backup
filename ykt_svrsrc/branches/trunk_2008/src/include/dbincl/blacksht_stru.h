#ifndef  __T_blacksht_H_
#define  __T_blacksht_H_
typedef struct 
{
		int	card_id;
		char	volume[12+1];
		char	validdate[12+1];
		int	state_id;
		int	is_ad;
		char	operate_date[10+1];
		char	operate_time[8+1];
		char	end_date[10+1];
		char	end_time[8+1];
}T_t_tif_black_sheet;
int DB_t_tif_black_sheet_add(T_t_tif_black_sheet *pt_tif_black_sheet);
int DB_t_tif_black_sheet_read_by_card_id(int v_card_id,T_t_tif_black_sheet *pt_tif_black_sheet);
int DB_t_tif_black_sheet_read_by_card_id_and_is_ad(int v_card_id,int v_is_ad,T_t_tif_black_sheet *pt_tif_black_sheet);
int DB_t_tif_black_sheet_read_lock_by_cur_and_card_id(int v_card_id,T_t_tif_black_sheet *pt_tif_black_sheet);
int DB_t_tif_black_sheet_update_lock_by_cur(T_t_tif_black_sheet *pt_tif_black_sheet);
int DB_t_tif_black_sheet_free_lock_by_cur();
int DB_t_tif_black_sheet_del_by_card_id(int v_card_id);
int DB_t_tif_black_sheet_del_by_card_id_and_is_ad(int v_card_id,int v_is_ad);
#endif
