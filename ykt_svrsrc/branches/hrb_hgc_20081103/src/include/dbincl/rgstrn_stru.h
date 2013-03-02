#ifndef  __T_rgstrn_H_
#define  __T_rgstrn_H_
typedef struct 
{
		int	cust_id;
		int	reg_id;
		int	device_id;
		char	device_name[250+1];
		char	tx_date[8+1];
		char	tx_time[6+1];
		int	reg_flag;
		char	comments[250+1];
}T_t_tif_registration;
int DB_t_tif_registration_add(T_t_tif_registration *pt_tif_registration);
int DB_t_tif_registration_read_lock_by_c0_and_cust_id_and_reg_id(int v_cust_id,int v_reg_id,T_t_tif_registration *pt_tif_registration);
int DB_t_tif_registration_update_lock_by_c0(T_t_tif_registration *pt_tif_registration);
int DB_t_tif_registration_free_lock_c0();
#endif
