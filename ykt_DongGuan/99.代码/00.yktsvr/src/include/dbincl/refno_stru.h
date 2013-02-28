#ifndef  __T_refno_H_
#define  __T_refno_H_
typedef struct 
{
		char	refno[14+1];
		char	reqrefno[20+1];
		char	mac[8+1];
		int	status;
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		char	lastsaved[30+1];
}T_t_refno;
int DB_t_refno_add(T_t_refno *pt_refno);
int DB_t_refno_read_by_refno(const char *v_refno,T_t_refno *pt_refno);
int DB_t_refno_update_by_refno(char *v_refno,T_t_refno *pt_refno);
int DB_t_refno_del_by_refno(const char *v_refno);
int DB_t_refno_read_lock_by_c0_and_refno(const char *v_refno,T_t_refno *pt_refno);
int DB_t_refno_update_lock_by_c0(T_t_refno *pt_refno);
int DB_t_refno_free_lock_by_c0();
int DB_t_refno_open_select_by_c1_and_status(int v_status);
int DB_t_refno_fetch_select_by_c1(T_t_refno *pt_refno);
int DB_t_refno_close_select_by_c1();
int DB_t_refno_read_by_reqrefno_and_accdate(const char *v_reqrefno,const char *v_accdate,T_t_refno *pt_refno);
#endif
