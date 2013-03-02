#ifndef  __T_attend_H_
#define  __T_attend_H_
typedef struct 
{
		char	device_id[30+1];
		char	tx_date[8+1];
		char	tx_time[6+1];
		char	phycard_no[8+1];
		int	serial_no;
		int	cust_id;
		int	card_no;
		int	tx_mark;
		char	crc[5+1];
		int	sys_id;
		char	col_date[8+1];
		char	col_time[6+1];
		char	comments[250+1];
}T_t_attend_txdtl;
int DB_t_attend_txdtl_add(T_t_attend_txdtl *pt_attend_txdtl);
#endif
