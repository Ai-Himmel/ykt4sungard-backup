#ifndef  __T_bankcardtmp_H_
#define  __T_bankcardtmp_H_
typedef struct {
    char	recordno[14+1];
    int	termid;
    char	batchno[30+1];
    char	opercode[8+1];
    int	custid;
    char	stuempno[20+1];
    char	bankcardno[30+1];
    int	optype;
    int	status;
    char	remark[240+1];
} T_t_bankcardtmp;
int DB_t_bankcardtmp_add(T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_read_by_recordno(char *v_recordno,T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_update_by_recordno(char *v_recordno,T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_del_by_recordno(char *v_recordno);
int DB_t_bankcardtmp_del_by_batchno(char *v_batchno);
int DB_t_bankcardtmp_read_lock_by_c0_and_recordno(char *v_recordno,T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_update_lock_by_c0(T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_free_lock_by_c0();
int DB_t_bankcardtmp_open_select_by_c1_and_batchno(char *v_batchno);
int DB_t_bankcardtmp_fetch_select_by_c1(T_t_bankcardtmp *pt_bankcardtmp);
int DB_t_bankcardtmp_close_select_by_c1();
#endif
