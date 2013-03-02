#ifndef  __T_coshis_H_
#define  __T_coshis_H_
typedef struct 
{
		int	serial_no;
		int	other_seri_no;
		int	serial_type;
		int	tmark;
		int	system_id;
		char	device_id[8+1];
		int	card_id;
		int	purse_id;
		char	operate_date[6+1];
		char	operate_time[6+1];
		int	consume_count;
		int	consume_fee;
		int	in_balance;
		int	out_balance;
		char	dev_auth[8+1];
		int	comu_ver;
		int	run_reason;
		char	crc[5+1];
}T_t_tif_cosume_his;
int DB_t_tif_cosume_his_add(T_t_tif_cosume_his *pt_tif_cosume_his);
int DB_t_tif_cosume_his_del_by_serial_no(int v_serial_no);
int DB_t_tif_cosume_his_read_by_serial_no(int v_serial_no,T_t_tif_cosume_his *pt_tif_cosume_his);
int DB_t_tif_cosume_his_read_lock_by_cur_and_serial_no(int v_serial_no,T_t_tif_cosume_his *pt_tif_cosume_his);
int DB_t_tif_cosume_his_update_lock_by_cur(T_t_tif_cosume_his *pt_tif_cosume_his);
int DB_t_tif_cosume_his_free_lock_cur();
#endif
