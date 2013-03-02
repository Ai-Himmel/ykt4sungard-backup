#ifndef  __T_device_H_
#define  __T_device_H_
typedef struct 
{
		int	deviceid;
		char	devicename[60+1];
		char	devphyid[30+1];
		int	deviceno;
		int	devphytype;
		char	devtypecode[30+1];
		char	devverno[30+1];
		char	cardphytype[2+1];
		int	fdeviceid;
		char	runstatus[1+1];
		char	status[1+1];
		int	svrportcnt;
		int	svrportno;
		int	commtype;
		char	ip[15+1];
		int	portno;
		int	baudrate;
		char	cardset[64+1];
		char	cardverno[30+1];
		int	lastseqno;
		char	lasttranstime[30+1];
		int	purseno;
		double	maxamt;
		int	sysid;
		char	areacode[3+1];
		char	doorlstver[30+1];
		int	devusage;
}T_t_device;
int DB_t_device_add(T_t_device *pt_device);
int DB_t_device_read_by_deviceid(int v_deviceid,T_t_device *pt_device);
int DB_t_device_update_by_deviceid(int v_deviceid,T_t_device *pt_device);
int DB_t_device_del_by_deviceid(int v_deviceid);
int DB_t_device_read_lock_by_c0_and_deviceid(int v_deviceid,T_t_device *pt_device);
int DB_t_device_update_lock_by_c0(T_t_device *pt_device);
int DB_t_device_free_lock_by_c0();
#endif
