#ifndef  __T_shpposlog_H_
#define  __T_shpposlog_H_
typedef struct 
{
		char	update_date[10+1];
		int	id;
		int	device_id;
		int	shop_id;
		char	begin_date[10+1];
		char	begin_time[8+1];
		char	end_time[8+1];
		char	end_date[10+1];
		char	comments[150+1];
		int	fee_code;
}T_t_cif_shop_pos_log;
int DB_t_cif_shop_pos_log_add(T_t_cif_shop_pos_log *pt_cif_shop_pos_log);
int DB_t_cif_shop_pos_log_open_select_by_cur1_and_update_date(char *v_update_date);
int DB_t_cif_shop_pos_log_fetch_select_by_cur1(T_t_cif_shop_pos_log *pt_cif_shop_pos_log);
int DB_t_cif_shop_pos_log_close_select_by_cur1();
int DB_t_cif_shop_pos_log_open_select_by_c0_and_update_date_and_device_id(char *v_update_date,int v_device_id);
int DB_t_cif_shop_pos_log_fetch_select_by_c0(T_t_cif_shop_pos_log *pt_cif_shop_pos_log);
int DB_t_cif_shop_pos_log_close_select_by_c0();
int DB_t_cif_shop_pos_log_open_select_by_c1_and_update_date_and_device_id(char *v_update_date,int v_device_id);
int DB_t_cif_shop_pos_log_fetch_select_by_c1(T_t_cif_shop_pos_log *pt_cif_shop_pos_log);
int DB_t_cif_shop_pos_log_close_select_by_c1();
int DB_t_cif_shop_pos_log_open_select_by_c2_and_update_date_and_device_id_and_fee_code(char *v_update_date,int v_device_id,int v_fee_code);
int DB_t_cif_shop_pos_log_fetch_select_by_c2(T_t_cif_shop_pos_log *pt_cif_shop_pos_log);
int DB_t_cif_shop_pos_log_close_select_by_c2();
#endif
