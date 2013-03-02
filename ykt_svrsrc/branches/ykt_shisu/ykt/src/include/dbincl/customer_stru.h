#ifndef  __T_customer_H_
#define  __T_customer_H_
typedef struct 
{
		int	cut_id;
		int	cut_type;
		int	cut_state;
		char	cut_name[60+1];
		char	password[32+1];
		int	area;
		char	lib_cardid[50+1];
		char	is_havecard[1+1];
		char	stuemp_no[20+1];
		char	classdept_no[10+1];
		char	classdept_name[50+1];
		char	s_code[100+1];
		char	man[60+1];
		char	sex[1+1];
		int	nation;
		char	man_id[50+1];
		char	tel[20+1];
		char	address[150+1];
		char	reg_time[26+1];
		char	can_time[26+1];
		int	fee_type;
		char	batch_no[14+1];
		char	class_no[10+1];
		char	med_feetype[5+1];
		char	in_date[10+1];
		char	building_no[5+1];
		char	floor_no[5+1];
		char	room_no[5+1];
		char	upd_date[10+1];
		char	upd_time[8+1];
		char	syn_time[14+1];
		char	comments[150+1];
		int	frozen_status;
}T_t_cif_customer;
int DB_t_cif_customer_add(T_t_cif_customer *pt_cif_customer);
int DB_t_cif_customer_del_by_cut_id(int v_cut_id);
int DB_t_cif_customer_read_by_cut_id(int v_cut_id,T_t_cif_customer *pt_cif_customer);
int DB_t_cif_customer_read_lock_by_cur_and_cut_id(int v_cut_id,T_t_cif_customer *pt_cif_customer);
int DB_t_cif_customer_update_lock_by_cur(T_t_cif_customer *pt_cif_customer);
int DB_t_cif_customer_free_lock_cur();
int DB_t_cif_customer_open_select_by_cur1_and_cut_id(int v_cut_id);
int DB_t_cif_customer_fetch_select_by_cur1(T_t_cif_customer *pt_cif_customer);
int DB_t_cif_customer_close_select_by_cur1();
int DB_t_cif_customer_read_by_stuemp_no(char *v_stuemp_no,T_t_cif_customer *pt_cif_customer);
int DB_t_cif_customer_read_by_stuemp_no_and_area(char *v_stuemp_no,int v_area,T_t_cif_customer *pt_cif_customer);
#endif
