#ifndef  __T_rcvdtl_H_
#define  __T_rcvdtl_H_
typedef struct 
{
		char	tx_date[8+1];
		char	tx_time[6+1];
		int	card_no;
		char	device_id[8+1];
		int	serial_no;
		int	purse_no;
		int	in_bala;
		int	out_bala;
		int	amount;
		int	total_cnt;
		int	tx_code;
		int	tx_mark;
		int	comu_ver;
		int	run_reason;
		char	crc[4+1];
		char	inpower_no[8+1];
		int	sys_id;
		char	oper_no[8+1];
		char	status[1+1];
		char	col_timestamp[20+1];
		char	deal_date[8+1];
		char	deal_time[6+1];
		int	fee_code;
		int	err_code;
		int	manage_fee;
}T_t_tif_rcvdtl;
int DB_t_tif_rcvdtl_add(T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_del_by_status(char *v_status);
int DB_t_tif_rcvdtl_read_by_tx_date_and_tx_time_and_card_no_and_device_id_and_serial_no(char *v_tx_date,char *v_tx_time,int v_card_no,char *v_device_id,int v_serial_no,T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_read_lock_by_c0_and_tx_date_and_tx_time_and_card_no_and_device_id_and_serial_no(char *v_tx_date,char *v_tx_time,int v_card_no,char *v_device_id,int v_serial_no,T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_update_lock_by_c0(T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_free_lock_c0();
int DB_t_tif_rcvdtl_read_lock_by_c1_and_tx_date_and_tx_time_and_card_no_and_device_id_and_serial_no_and_status(char *v_tx_date,char *v_tx_time,int v_card_no,char *v_device_id,int v_serial_no,char *v_status,T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_update_by_tx_date_and_tx_time_and_card_no_and_device_id_and_serial_no(char *v_tx_date,char *v_tx_time,int v_card_no,char *v_device_id,int v_serial_no,T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_update_lock_by_c1(T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_free_lock_c1();
int DB_t_tif_rcvdtl_open_select_for_update_by_c2_and_status(char *v_status);
int DB_t_tif_rcvdtl_fetch_select_by_c2(T_t_tif_rcvdtl *pt_tif_rcvdtl);
int DB_t_tif_rcvdtl_close_select_by_c2();
#endif
