#ifndef  __T_attserial_H_
#define  __T_attserial_H_
typedef struct 
{
		int	serial_id;
		int	device_id;
		int	cust_id;
		int	card_id;
		char	phy_id[20+1];
		char	show_cardno[20+1];
		char	att_date[8+1];
		char	att_time[6+1];
		int	tx_mark;
		char	status[1+1];
}T_t_attserial;
int DB_t_attserial_add(T_t_attserial *pt_attserial);
#endif
