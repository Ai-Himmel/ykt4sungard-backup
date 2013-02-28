#ifndef  __T_cardnoctl_H_
#define  __T_cardnoctl_H_
typedef struct 
{
		int	issueunit;
		int	cardno;
}T_t_cardnoctl;
int DB_t_cardnoctl_add(T_t_cardnoctl *pt_cardnoctl);
int DB_t_cardnoctl_read_by_issueunit(int v_issueunit,T_t_cardnoctl *pt_cardnoctl);
int DB_t_cardnoctl_update_by_issueunit(int v_issueunit,T_t_cardnoctl *pt_cardnoctl);
int DB_t_cardnoctl_del_by_issueunit(int v_issueunit);
int DB_t_cardnoctl_read_lock_by_c0_and_issueunit(int v_issueunit,T_t_cardnoctl *pt_cardnoctl);
int DB_t_cardnoctl_update_lock_by_c0(T_t_cardnoctl *pt_cardnoctl);
int DB_t_cardnoctl_del_lock_by_c0();
int DB_t_cardnoctl_free_lock_by_c0();
#endif
