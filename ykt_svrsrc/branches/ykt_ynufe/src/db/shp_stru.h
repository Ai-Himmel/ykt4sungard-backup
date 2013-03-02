#ifndef  __T_shp_H_
#define  __T_shp_H_
typedef struct 
{
		int	shop_id;
		int	cut_id;
		int	dept_id;
		char	shop_name[50+1];
		int	shop_type;
		char	is_indep[1+1];
		char	is_leaf[1+1];
		int	shop_state;
		char	b_act_id[40+1];
		char	b_act_name[60+1];
		char	shop_manager[20+1];
		char	man[60+1];
		char	sex[1+1];
		int	nation;
		char	man_id[50+1];
		char	tel[20+1];
		char	address[150+1];
		char	is_getfee[1+1];
		double	ratio;
		int	manager_type;
		int	duty_type;
		char	reg_time[26+1];
		char	can_time[26+1];
		char	comments[150+1];
		double	rakeoff_ratio;
		char	rakeoff_type[1+1];
}T_t_cif_shop;
int DB_t_cif_shop_add(T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_del_by_shop_id(int v_shop_id);
int DB_t_cif_shop_read_by_shop_id(int v_shop_id,T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_read_by_cut_id(int v_cut_id,T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_read_lock_by_cur1_and_shop_id(int v_shop_id,T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_update_by_shop_id(int v_shop_id,T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_update_lock_by_cur1(T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_free_lock_cur1();
int DB_t_cif_shop_open_select_by_cur2_and_dept_id(int v_dept_id);
int DB_t_cif_shop_fetch_select_by_cur2(T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_close_select_by_cur2();
int DB_t_cif_shop_open_select_by_cur3_and_is_indep(char *v_is_indep);
int DB_t_cif_shop_fetch_select_by_cur3(T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_close_select_by_cur3();
int DB_t_cif_shop_open_select_by_cur4();
int DB_t_cif_shop_fetch_select_by_cur4(T_t_cif_shop *pt_cif_shop);
int DB_t_cif_shop_close_select_by_cur4();
int DB_t_cif_shop_del_all();
#endif
