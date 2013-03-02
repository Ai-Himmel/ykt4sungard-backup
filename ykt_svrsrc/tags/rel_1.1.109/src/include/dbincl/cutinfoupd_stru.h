#ifndef  __T_cutinfoupd_H_
#define  __T_cutinfoupd_H_
typedef struct 
{
		int	id;
		int	card_id;
		char	volume[12+1];
		int	flag;
		char	operate_date[8+1];
		char	operate_time[6+1];
}T_t_tif_cut_info_update;
int DB_t_tif_cut_info_update_add(T_t_tif_cut_info_update *pt_tif_cut_info_update);
int DB_t_tif_cut_info_update_read_lock_by_cur0_and_card_id_and_flag(int v_card_id,int v_flag,T_t_tif_cut_info_update *pt_tif_cut_info_update);
int DB_t_tif_cut_info_update_update_lock_by_cur0(T_t_tif_cut_info_update *pt_tif_cut_info_update);
int DB_t_tif_cut_info_update_free_lock_cur0();
int DB_t_tif_cut_info_update_del_by_card_id_and_flag(int v_card_id,int v_flag);
#endif
