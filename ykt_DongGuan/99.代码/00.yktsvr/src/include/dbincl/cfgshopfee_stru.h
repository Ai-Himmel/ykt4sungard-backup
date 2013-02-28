#ifndef  __T_cfgshopfee_H_
#define  __T_cfgshopfee_H_
typedef struct 
{
		int	shopid;
		int	feetype;
		double	feerate;
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_cfgshopfee;
int DB_t_cfgshopfee_add(T_t_cfgshopfee *pt_cfgshopfee);
int DB_t_cfgshopfee_read_by_shopid_and_feetype(int v_shopid,int v_feetype,T_t_cfgshopfee *pt_cfgshopfee);
int DB_t_cfgshopfee_update_by_shopid_and_feetype(int v_shopid,int v_feetype,T_t_cfgshopfee *pt_cfgshopfee);
int DB_t_cfgshopfee_del_by_shopid_and_feetype(int v_shopid,int v_feetype);
int DB_t_cfgshopfee_read_lock_by_c0_and_shopid_and_feetype(int v_shopid,int v_feetype,T_t_cfgshopfee *pt_cfgshopfee);
int DB_t_cfgshopfee_update_lock_by_c0(T_t_cfgshopfee *pt_cfgshopfee);
int DB_t_cfgshopfee_free_lock_by_c0();
int DB_t_cfgshopfee_open_select_by_c1_and_shopid(int v_shopid);
int DB_t_cfgshopfee_fetch_select_by_c1(T_t_cfgshopfee *pt_cfgshopfee);
int DB_t_cfgshopfee_close_select_by_c1();
#endif
