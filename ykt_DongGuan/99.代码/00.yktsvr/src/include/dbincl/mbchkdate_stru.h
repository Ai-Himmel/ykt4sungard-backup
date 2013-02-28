#ifndef  __T_mbchkdate_H_
#define  __T_mbchkdate_H_
typedef struct 
{
		char	chkdate[8+1];
		int	chkflag;
}T_t_mobilechkdate;
int DB_t_mobilechkdate_add(T_t_mobilechkdate *pt_mobilechkdate);
int DB_t_mobilechkdate_read_by_chkdate(const char *v_chkdate,T_t_mobilechkdate *pt_mobilechkdate);
int DB_t_mobilechkdate_update_by_chkdate(char *v_chkdate,T_t_mobilechkdate *pt_mobilechkdate);
int DB_t_mobilechkdate_del_by_chkdate(const char *v_chkdate);
int DB_t_mobilechkdate_read_lock_by_c0_and_chkdate(const char *v_chkdate,T_t_mobilechkdate *pt_mobilechkdate);
int DB_t_mobilechkdate_update_lock_by_c0(T_t_mobilechkdate *pt_mobilechkdate);
int DB_t_mobilechkdate_free_lock_by_c0();
#endif
