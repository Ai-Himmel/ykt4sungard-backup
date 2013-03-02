#ifndef  __T_authcard_H_
#define  __T_authcard_H_
typedef struct 
{
		char	physical_no[40+1];
		int	state_id;
		int	type_id;
		char	password1[32+1];
		char	password2[32+1];
		char	begin_time[26+1];
		char	end_time[26+1];
		int	phytype;
		char	comments[150+1];
}T_t_pif_authcard;
int DB_t_pif_authcard_add(T_t_pif_authcard *pt_pif_authcard);
int DB_t_pif_authcard_del_by_physical_no(char *v_physical_no);
int DB_t_pif_authcard_read_by_physical_no(char *v_physical_no,T_t_pif_authcard *pt_pif_authcard);
int DB_t_pif_authcard_read_lock_by_cur_and_physical_no(char *v_physical_no,T_t_pif_authcard *pt_pif_authcard);
int DB_t_pif_authcard_update_lock_by_cur(T_t_pif_authcard *pt_pif_authcard);
int DB_t_pif_authcard_free_lock_cur();
int DB_t_pif_authcard_open_select_by_cur1_and_physical_no(char *v_physical_no);
int DB_t_pif_authcard_fetch_select_by_cur1(T_t_pif_authcard *pt_pif_authcard);
int DB_t_pif_authcard_close_select_by_cur1();
#endif
