#ifndef  __T_device_collect_log_H_
#define  __T_device_collect_log_H_
typedef struct 
{
		int	id;
		int	device_id;
		double	cur_collect_bala;
		char	collect_date[10+1];
		char	collect_time[8+1];
		double	last_collect_bala;
		char	oper_code[10+1];
		int	serial_num;
		int	deal_flag;
		int	serial_type;
}T_t_tif_device_collect_log;
int DB_t_tif_device_collect_log_add(T_t_tif_device_collect_log *pt_tif_device_collect_log);
int DB_t_tif_device_collect_log_update_by_id(int v_id,T_t_tif_device_collect_log *pt_tif_device_collect_log);
int DB_t_tif_device_collect_log_read_by_id_and_device_id(int v_id,int v_device_id,T_t_tif_device_collect_log *pt_tif_device_collect_log);
int DB_t_tif_device_collect_log_read_lock_by_cur_and_id_and_device_id(int v_id,int v_device_id,T_t_tif_device_collect_log *pt_tif_device_collect_log);
int DB_t_tif_device_collect_log_update_lock_by_cur(T_t_tif_device_collect_log *pt_tif_device_collect_log);
int DB_t_tif_device_collect_log_free_lock_by_cur();
#endif
