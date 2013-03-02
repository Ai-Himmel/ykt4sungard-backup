#ifndef  __T_txdtl_H_
#define  __T_txdtl_H_
typedef struct 
{
		char	device_id[8+1];
		int	serial_no;
		char	tx_date[8+1];
		char	tx_time[6+1];
		int	mode_code;
		int	card_no;
		int	use_type;
		int	inductor_no;
		int	work_mark;
		int	tx_mark;
		char	crc[5+1];
		int	sys_id;
		char	col_date[8+1];
		char	col_time[6+1];
		char	status[1+1];
		int	err_code;
}T_t_door_txdtl;
int DB_t_door_txdtl_add(T_t_door_txdtl *pt_door_txdtl);
#endif
