#ifndef  __T_cardnochange_H_
#define  __T_cardnochange_H_
typedef struct 
{
		int	oldcardno;
		int	newcardno;
		char	changedate[8+1];
}T_t_cardnochange;
int DB_t_cardnochange_add(T_t_cardnochange *pt_cardnochange);
int DB_t_cardnochange_read_by_oldcardno(int v_oldcardno,T_t_cardnochange *pt_cardnochange);
int DB_t_cardnochange_update_by_oldcardno(int v_oldcardno,T_t_cardnochange *pt_cardnochange);
int DB_t_cardnochange_del_by_oldcardno(int v_oldcardno);
int DB_t_cardnochange_read_lock_by_c0_and_oldcardno(int v_oldcardno,T_t_cardnochange *pt_cardnochange);
int DB_t_cardnochange_update_lock_by_c0(T_t_cardnochange *pt_cardnochange);
int DB_t_cardnochange_free_lock_by_c0();
#endif
