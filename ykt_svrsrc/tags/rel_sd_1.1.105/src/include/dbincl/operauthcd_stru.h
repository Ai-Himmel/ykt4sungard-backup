#ifndef  __T_operauthcd_H_
#define  __T_operauthcd_H_
typedef struct 
{
		int	card_id;
		char	oper_code[10+1];
		char	card_phyid[8+1];
		int	privilege;
		char	expired_date[8+1];
		int	status;
		char	issue_date[8+1];
		char	issue_time[6+1];
}T_t_pif_oper_authcard;
int DB_t_pif_oper_authcard_add(T_t_pif_oper_authcard *pt_pif_oper_authcard);
int DB_t_pif_oper_authcard_read_by_card_id(int v_card_id,T_t_pif_oper_authcard *pt_pif_oper_authcard);
int DB_t_pif_oper_authcard_update_by_card_id(int v_card_id,T_t_pif_oper_authcard *pt_pif_oper_authcard);
int DB_t_pif_oper_authcard_open_select_by_cur_and_oper_code(char *v_oper_code);
int DB_t_pif_oper_authcard_fetch_select_by_cur(T_t_pif_oper_authcard *pt_pif_oper_authcard);
int DB_t_pif_oper_authcard_free_lock_cur();
#endif
