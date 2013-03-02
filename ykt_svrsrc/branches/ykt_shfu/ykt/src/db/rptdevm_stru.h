#ifndef  __T_rptdevm_H_
#define  __T_rptdevm_H_
typedef struct 
{
		char	balance_date[8+1];
		int	shop_id;
		int	device_id;
		int	meal_id;
		int	trade_count;
		double	trade_fee;
		double	mng_fee;
		double	total_fee;
		char	data_sign[8+1];
		char	reserve_1[20+1];
		char	reserve_2[20+1];
		char	device_name[150+1];
		char	meal_name[80+1];
}T_t_tif_report_device_meal;
int DB_t_tif_report_device_meal_add(T_t_tif_report_device_meal *pt_tif_report_device_meal);
int DB_t_tif_report_device_meal_del_by_balance_date(char *v_balance_date);
#endif
