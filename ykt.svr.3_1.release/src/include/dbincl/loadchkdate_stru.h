#ifndef  __T_loadchkdate_H_
#define  __T_loadchkdate_H_
typedef struct {
    char	chkdate[8+1];
    int	chkflag;
} T_t_loadchkdate;
int DB_t_loadchkdate_add(T_t_loadchkdate *pt_loadchkdate);
int DB_t_loadchkdate_read_by_chkdate(char *v_chkdate,T_t_loadchkdate *pt_loadchkdate);
int DB_t_loadchkdate_update_by_chkdate(char *v_chkdate,T_t_loadchkdate *pt_loadchkdate);
int DB_t_loadchkdate_del_by_chkdate(char *v_chkdate);
int DB_t_loadchkdate_read_lock_by_c0_and_chkdate(char *v_chkdate,T_t_loadchkdate *pt_loadchkdate);
int DB_t_loadchkdate_update_lock_by_c0(T_t_loadchkdate *pt_loadchkdate);
int DB_t_loadchkdate_free_lock_by_c0();
#endif
