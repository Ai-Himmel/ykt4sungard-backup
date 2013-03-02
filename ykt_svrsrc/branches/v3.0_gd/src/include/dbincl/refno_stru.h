#ifndef  __T_refno_H_
#define  __T_refno_H_
typedef struct 
{
		char	refno[14+1];
		char	mac[8+1];
		int	status;
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		char	lastsaved[30+1];
		char	drtphandle[120+1];
}T_t_refno;
int DB_t_refno_add(T_t_refno *pt_refno);
int DB_t_refno_read_by_refno(char *v_refno,T_t_refno *pt_refno);
int DB_t_refno_update_by_refno(char *v_refno,T_t_refno *pt_refno);
int DB_t_refno_del_by_refno(char *v_refno);
int DB_t_refno_read_lock_by_c0_and_refno(char *v_refno,T_t_refno *pt_refno);
int DB_t_refno_update_lock_by_c0(T_t_refno *pt_refno);
int DB_t_refno_free_lock_by_c0();
#endif
