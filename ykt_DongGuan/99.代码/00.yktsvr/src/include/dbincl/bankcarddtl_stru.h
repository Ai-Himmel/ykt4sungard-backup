#ifndef  __T_bankcarddtl_H_
#define  __T_bankcarddtl_H_
typedef struct 
{
		char	refno[14+1];
		char	transdate[8+1];
		char	transtime[6+1];
		int	termid;
		char	opercode[8+1];
		char	batchno[30+1];
		int	custid;
		char	custname[60+1];
		char	stuempno[20+1];
		char	bankcardno[30+1];
		int	optype;
		int	adddelflag;
		int	errcode;
		char	remark[240+1];
}T_t_bankcarddtl;
int DB_t_bankcarddtl_add(T_t_bankcarddtl *pt_bankcarddtl);
int DB_t_bankcarddtl_read_by_refno(const char *v_refno,T_t_bankcarddtl *pt_bankcarddtl);
int DB_t_bankcarddtl_update_by_refno(char *v_refno,T_t_bankcarddtl *pt_bankcarddtl);
int DB_t_bankcarddtl_del_by_refno(const char *v_refno);
int DB_t_bankcarddtl_read_lock_by_c0_and_refno(const char *v_refno,T_t_bankcarddtl *pt_bankcarddtl);
int DB_t_bankcarddtl_update_lock_by_c0(T_t_bankcarddtl *pt_bankcarddtl);
int DB_t_bankcarddtl_free_lock_by_c0();
int DB_t_bankcarddtl_open_select_by_c1_and_batchno(const char *v_batchno);
int DB_t_bankcarddtl_fetch_select_by_c1(T_t_bankcarddtl *pt_bankcarddtl);
int DB_t_bankcarddtl_close_select_by_c1();
#endif
