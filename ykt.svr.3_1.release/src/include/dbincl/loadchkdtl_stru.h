#ifndef  __T_loadchkdtl_H_
#define  __T_loadchkdtl_H_
typedef struct {
    char	transdate[8+1];
    char	refno[14+1];
    int	cardno;
    char	bankno[20+1];
    char	stuempno[30+1];
    char	bankrefno[8+1];
    double	amount;
    int	chkstatus;
    int	chkflag;
    char	chkoper[8+1];
    char	chkdate[8+1];
    char	chktime[6+1];
} T_t_loadchkdtl;
int DB_t_loadchkdtl_add(T_t_loadchkdtl *pt_loadchkdtl);
int DB_t_loadchkdtl_read_by_refno(char *v_refno,T_t_loadchkdtl *pt_loadchkdtl);
int DB_t_loadchkdtl_update_by_refno(char *v_refno,T_t_loadchkdtl *pt_loadchkdtl);
int DB_t_loadchkdtl_del_by_refno(char *v_refno);
int DB_t_loadchkdtl_read_lock_by_c0_and_refno(char *v_refno,T_t_loadchkdtl *pt_loadchkdtl);
int DB_t_loadchkdtl_update_lock_by_c0(T_t_loadchkdtl *pt_loadchkdtl);
int DB_t_loadchkdtl_free_lock_by_c0();
int DB_t_loadchkdtl_open_select_by_c1_and_cardno(int v_cardno);
int DB_t_loadchkdtl_fetch_select_by_c1(T_t_loadchkdtl *pt_loadchkdtl);
int DB_t_loadchkdtl_close_select_by_c1();
#endif
