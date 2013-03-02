#ifndef  __T_vrptdevm_H_
#define  __T_vrptdevm_H_
typedef struct 
{
		int	shop_id;
		int	deviceid;
		int	meal_id;
		int	trade_count;
		double	trade_fee;
		double	mng_fee;
		double	total_fee;
}T_v_tif_report_device_meal;
int DB_v_tif_report_device_meal_open_select_by_cur1();
int DB_v_tif_report_device_meal_fetch_select_by_cur1(T_v_tif_report_device_meal *pv_tif_report_device_meal);
int DB_v_tif_report_device_meal_close_select_by_cur1();
#endif
