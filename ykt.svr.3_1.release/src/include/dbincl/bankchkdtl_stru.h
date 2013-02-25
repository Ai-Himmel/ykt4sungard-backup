#ifndef  __T_bankchkdtl_H_
#define  __T_bankchkdtl_H_
typedef struct {
    char	transdate[8+1];
    char	refno[14+1];
    char	stuempno[20+1];
    char	bankcardno[30+1];
    double	amount;
    int	chkstatus;
    int	chkflag;
    char	chkoper[8+1];
    char	chkdate[8+1];
    char	chktime[6+1];
} T_t_bankchkdtl;
int DB_t_bankchkdtl_add(T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_read_by_refno(char *v_refno,T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_update_by_refno(char *v_refno,T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_del_by_refno(char *v_refno);
int DB_t_bankchkdtl_read_lock_by_c0_and_refno(char *v_refno,T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_update_lock_by_c0(T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_free_lock_by_c0();
#endif
