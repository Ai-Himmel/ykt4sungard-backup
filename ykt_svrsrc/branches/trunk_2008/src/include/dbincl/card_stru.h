#ifndef  __T_card_H_
#define  __T_card_H_
typedef struct 
{
		int	card_id;
		char	showid[10+1];
		char	is_main[1+1];
		char	state_id[4+1];
		int	type_id;
		char	password[32+1];
		int	cosumer_id;
		int	account_count;
		char	is_managefee[1+1];
		double	deposit_fee;
		double	cost_fee;
		char	begin_time[26+1];
		char	end_time[26+1];
		char	physical_no[40+1];
		int	phytype;
		char	comments[255+1];
		char	bad_status[1+1];
}T_t_pif_card;
int DB_t_pif_card_add(T_t_pif_card *pt_pif_card);
int DB_t_pif_card_read_by_card_id(int v_card_id,T_t_pif_card *pt_pif_card);
int DB_t_pif_card_read_lock_by_cur_and_card_id(int v_card_id,T_t_pif_card *pt_pif_card);
int DB_t_pif_card_update_lock_by_cur(T_t_pif_card *pt_pif_card);
int DB_t_pif_card_free_lock_by_cur();
int DB_t_pif_card_open_select_by_c1_and_cosumer_id(int v_cosumer_id);
int DB_t_pif_card_fetch_select_by_c1(T_t_pif_card *pt_pif_card);
int DB_t_pif_card_close_select_by_c1();
int DB_t_pif_card_open_select_by_c2_and_cosumer_id_and_type_id(int v_cosumer_id,int v_type_id);
int DB_t_pif_card_fetch_select_by_c2(T_t_pif_card *pt_pif_card);
int DB_t_pif_card_close_select_by_c2();
int DB_t_pif_card_read_by_cosumer_id_and_type_id_and_state_id(int v_cosumer_id,int v_type_id,char *v_state_id,T_t_pif_card *pt_pif_card);
int DB_t_pif_card_read_lock_by_c3_and_cosumer_id_and_type_id_and_state_id(int v_cosumer_id,int v_type_id,char *v_state_id,T_t_pif_card *pt_pif_card);
int DB_t_pif_card_update_lock_by_c3(T_t_pif_card *pt_pif_card);
int DB_t_pif_card_free_lock_by_c3();
int DB_t_pif_card_open_select_for_update_by_c4_and_card_id(int v_card_id);
int DB_t_pif_card_fetch_select_by_c4(T_t_pif_card *pt_pif_card);
int DB_t_pif_card_update_lock_by_c4(T_t_pif_card *pt_pif_card);
int DB_t_pif_card_close_select_by_c4();
#endif
