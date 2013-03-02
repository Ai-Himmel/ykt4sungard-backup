#ifndef  __T_waterinf_H_
#define  __T_waterinf_H_
typedef struct 
{
		int	cust_no;
		int	water_meter_no;
		char	bind_date[8+1];
		char	bind_time[6+1];
		char	card_phyid[8+1];
}T_t_water_info;
int DB_t_water_info_add(T_t_water_info *pt_water_info);
int DB_t_water_info_read_lock_by_c1_and_cust_no(int v_cust_no,T_t_water_info *pt_water_info);
int DB_t_water_info_update_lock_by_c1_and_cust_no(T_t_water_info *pt_water_info);
int DB_t_water_info_free_lock_by_c1();
#endif
