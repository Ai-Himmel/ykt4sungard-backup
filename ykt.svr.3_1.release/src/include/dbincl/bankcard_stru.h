#ifndef  __T_bankcard_H_
#define  __T_bankcard_H_
typedef struct {
    int	custid;
    char	bankcode[2+1];
    char	bankcardno[30+1];
    char	batchno[30+1];
    char	createddate[8+1];
    char	lastsaved[30+1];
} T_t_bankcard;
int DB_t_bankcard_add(T_t_bankcard *pt_bankcard);
int DB_t_bankcard_read_by_custid(int v_custid,T_t_bankcard *pt_bankcard);
int DB_t_bankcard_del_by_custid(int v_custid);
int DB_t_bankcard_read_by_custid_and_bankcardno(int v_custid,char *v_bankcardno,T_t_bankcard *pt_bankcard);
int DB_t_bankcard_del_by_custid_and_bankcardno(int v_custid,char *v_bankcardno);
int DB_t_bankcard_del_by_batchno(char *v_batchno);
int DB_t_bankcard_read_lock_by_c0_and_custid(int v_custid,T_t_bankcard *pt_bankcard);
int DB_t_bankcard_update_lock_by_c0(T_t_bankcard *pt_bankcard);
int DB_t_bankcard_free_lock_by_c0();
#endif
