#ifndef  __T_cutinfoupd_H_
#define  __T_cutinfoupd_H_
typedef struct 
{
		int	id;
		int	cardno;
		char	volume[12+1];
		int	flag;
		char	operate_date[8+1];
		char	operate_time[6+1];
		char	physical_no[8+1];
}T_t_tif_cut_info_update;
int DB_t_tif_cut_info_update_add(T_t_tif_cut_info_update *pt_tif_cut_info_update);
int DB_t_tif_cut_info_update_del_by_cardno_and_flag(int v_cardno,int v_flag);
#endif
