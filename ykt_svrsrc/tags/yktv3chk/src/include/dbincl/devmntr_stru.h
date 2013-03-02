#ifndef  __T_devmntr_H_
#define  __T_devmntr_H_
typedef struct 
{
		int	deviceid;
		char	op_time[26+1];
		char	collect_time[26+1];
		char	is_ws[1+1];
		int	alarmno;
		int	beatstate;
		char	bsversion[12+1];
		int	hdper;
		int	emsper;
		int	cpuper;
		char	devtime[26+1];
		int	nouploadnum;
}T_t_mif_devmonitor;
int DB_t_mif_devmonitor_add(T_t_mif_devmonitor *pt_mif_devmonitor);
int DB_t_mif_devmonitor_read_by_deviceid(int v_deviceid,T_t_mif_devmonitor *pt_mif_devmonitor);
int DB_t_mif_devmonitor_update_by_deviceid(int v_deviceid,T_t_mif_devmonitor *pt_mif_devmonitor);
#endif
