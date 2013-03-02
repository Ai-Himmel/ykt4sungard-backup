#ifndef  __T_dpsshoppos_H_
#define  __T_dpsshoppos_H_
typedef struct 
{
		int	shopid;
		int	deviceid;
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_dpsshoppos;
int DB_t_dpsshoppos_add(T_t_dpsshoppos *pt_dpsshoppos);
int DB_t_dpsshoppos_read_by_deviceid(int v_deviceid,T_t_dpsshoppos *pt_dpsshoppos);
int DB_t_dpsshoppos_update_by_deviceid_and_shopid(int v_deviceid,int v_shopid,T_t_dpsshoppos *pt_dpsshoppos);
int DB_t_dpsshoppos_del_by_deviceid(int v_deviceid);
int DB_t_dpsshoppos_read_lock_by_c0_and_deviceid_and_shopid(int v_deviceid,int v_shopid,T_t_dpsshoppos *pt_dpsshoppos);
int DB_t_dpsshoppos_update_lock_by_c0(T_t_dpsshoppos *pt_dpsshoppos);
int DB_t_dpsshoppos_free_lock_by_c0();
#endif
