#ifndef  __T_drseri_H_
#define  __T_drseri_H_
typedef struct 
{
		int	device_id;
		char	tx_date[8+1];
		char	tx_time[6+1];
		char	phycard_no[8+1];
		int	serial_no;
		int	card_no;
		int	tx_mark;
		char	crc[5+1];
		int	sys_id;
		char	col_date[8+1];
		char	col_time[6+1];
		char	comments[250+1];
}T_ykt_cur;
int DB_ykt_cur_add(T_ykt_cur *pykt_cur);
#endif
