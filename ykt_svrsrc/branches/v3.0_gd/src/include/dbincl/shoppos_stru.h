#ifndef  __T_shoppos_H_
#define  __T_shoppos_H_
typedef struct 
{
		int	id;
		int	deviceid;
		char	devphyid[30+1];
		int	shopid;
		char	endtime[6+1];
		char	remark[240+1];
		char	startdate[8+1];
		char	enddate[8+1];
		char	status[1+1];
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_shoppos;
int DB_t_shoppos_add(T_t_shoppos *pt_shoppos);
int DB_t_shoppos_read_by_id(int v_id,T_t_shoppos *pt_shoppos);
int DB_t_shoppos_update_by_id(int v_id,T_t_shoppos *pt_shoppos);
int DB_t_shoppos_del_by_id(int v_id);
int DB_t_shoppos_read_lock_by_c0_and_id(int v_id,T_t_shoppos *pt_shoppos);
int DB_t_shoppos_update_lock_by_c0(T_t_shoppos *pt_shoppos);
int DB_t_shoppos_free_lock_by_c0();
int DB_t_shoppos_open_select_by_c1_and_deviceid(int v_deviceid);
int DB_t_shoppos_fetch_select_by_c1(T_t_shoppos *pt_shoppos);
int DB_t_shoppos_close_select_by_c1();
#endif
