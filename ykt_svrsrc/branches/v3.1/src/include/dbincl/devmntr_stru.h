#ifndef  __T_devmntr_H_
#define  __T_devmntr_H_
typedef struct 
{
		int	deviceid;
		char	optime[30+1];
		char	coltime[30+1];
		char	devtime[30+1];
		int	beatstatus;
		char	cardverno[12+1];
		int	hardiskper;
		int	memoryper;
		int	cpuper;
}T_t_devmonitor;
int DB_t_devmonitor_add(T_t_devmonitor *pt_devmonitor);
int DB_t_devmonitor_read_by_deviceid(int v_deviceid,T_t_devmonitor *pt_devmonitor);
int DB_t_devmonitor_update_by_deviceid(int v_deviceid,T_t_devmonitor *pt_devmonitor);
int DB_t_devmonitor_del_by_deviceid(int v_deviceid);
int DB_t_devmonitor_read_lock_by_c0_and_deviceid(int v_deviceid,T_t_devmonitor *pt_devmonitor);
int DB_t_devmonitor_update_lock_by_c0(T_t_devmonitor *pt_devmonitor);
int DB_t_devmonitor_free_lock_by_c0();
#endif
