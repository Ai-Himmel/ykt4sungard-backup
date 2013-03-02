#ifndef  __T_operauthcd_H_
#define  __T_operauthcd_H_
typedef struct 
{
		int	cardno;
		char	opercode[8+1];
		char	cardphyid[16+1];
		int	privilege;
		char	expiredate[8+1];
		char	status[10+1];
		char	opendate[8+1];
}T_t_operauthcard;
int DB_t_operauthcard_add(T_t_operauthcard *pt_operauthcard);
int DB_t_operauthcard_read_by_cardno(int v_cardno,T_t_operauthcard *pt_operauthcard);
int DB_t_operauthcard_update_by_cardno(int v_cardno,T_t_operauthcard *pt_operauthcard);
int DB_t_operauthcard_open_select_by_cur_and_opercode(char *v_opercode);
int DB_t_operauthcard_fetch_select_by_cur(T_t_operauthcard *pt_operauthcard);
int DB_t_operauthcard_free_lock_cur();
#endif
