#ifndef  __T_vrptdevwater_H_
#define  __T_vrptdevwater_H_
typedef struct 
{
		int	shop_id;
		int	device_id;
		int	trade_count;
		double	trade_fee;
		double	mng_fee;
		double	total_fee;
		char	device_name[100+1];
		double	water_container;
		double	total_container;
		char	collect_date[11+1];
}T_v_tif_report_water;
int DB_v_tif_report_water_open_select_by_cur1();
int DB_v_tif_report_water_fetch_select_by_cur1(T_v_tif_report_water *pv_tif_report_water);
int DB_v_tif_report_water_close_select_by_cur1();
#endif
