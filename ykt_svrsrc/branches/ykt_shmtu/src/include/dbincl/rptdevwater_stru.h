#ifndef  __T_rptdevwater_H_
#define  __T_rptdevwater_H_
typedef struct 
{
		char	collect_date[8+1];
		char	balance_date[8+1];
		int	shop_id;
		int	device_id;
		int	trade_count;
		double	trade_fee;
		double	water_container;
		double	total_container;
		double	total_fee;
		double	mng_fee;
		char	data_sign[8+1];
		char	reserve_1[20+1];
		char	reserve_2[20+1];
		char	device_name[100+1];
		double	rakeoff_amt;
}T_t_tif_report_device_water;
int DB_t_tif_report_device_water_add(T_t_tif_report_device_water *pt_tif_report_device_water);
int DB_t_tif_report_device_water_del_by_balance_date(char *v_balance_date);
#endif
