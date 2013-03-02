#ifndef  __T_cadlosinf_H_
#define  __T_cadlosinf_H_
typedef struct 
{
		char	operate_date[10+1];
		char	operate_time[8+1];
		int	cardno;
		int	state_id;
		char	begin_date[10+1];
		char	end_date[10+1];
}T_t_pif_cardlossinfo;
int DB_t_pif_cardlossinfo_read_by_cardno_and_state_id(int v_cardno,int v_state_id,T_t_pif_cardlossinfo *pt_pif_cardlossinfo);
int DB_t_pif_cardlossinfo_add(T_t_pif_cardlossinfo *pt_pif_cardlossinfo);
int DB_t_pif_cardlossinfo_read_lock_by_cur1_and_cardno_and_state_id(int v_cardno,int v_state_id,T_t_pif_cardlossinfo *pt_pif_cardlossinfo);
int DB_t_pif_cardlossinfo_update_lock_by_cur1(T_t_pif_cardlossinfo *pt_pif_cardlossinfo);
#endif
