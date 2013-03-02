#ifndef  __T_bankchkdate_H_
#define  __T_bankchkdate_H_
typedef struct 
{
		char	chkdate[8+1];
		int	chkflag;
}T_t_bankchkdate;
int DB_t_bankchkdate_add(T_t_bankchkdate *pt_bankchkdate);
int DB_t_bankchkdate_read_by_chkdate(char *v_chkdate,T_t_bankchkdate *pt_bankchkdate);
int DB_t_bankchkdate_update_by_chkdate(char *v_chkdate,T_t_bankchkdate *pt_bankchkdate);
int DB_t_bankchkdate_del_by_chkdate(char *v_chkdate);
int DB_t_bankchkdate_read_lock_by_c0_and_chkdate(char *v_chkdate,T_t_bankchkdate *pt_bankchkdate);
int DB_t_bankchkdate_update_lock_by_c0(T_t_bankchkdate *pt_bankchkdate);
int DB_t_bankchkdate_free_lock_by_c0();
#endif
