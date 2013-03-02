#ifndef  __T_thrdptsrl_H_
#define  __T_thrdptsrl_H_
typedef struct 
{
		int	id;
		char	sysid[6+1];
		int	up_serial;
		char	tx_date[8+1];
		char	tx_time[6+1];
		char	device_id[20+1];
		char	device_name[60+1];
		char	card_phy_no[8+1];
		int	cutid;
		int	cardid;
		char	ecode[8+1];
		char	emsg[100+1];
}T_t_thirdparty_serial;
int DB_t_thirdparty_serial_add(T_t_thirdparty_serial *pt_thirdparty_serial);
#endif
