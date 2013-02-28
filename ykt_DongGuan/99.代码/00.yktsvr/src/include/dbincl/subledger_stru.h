#ifndef  __T_subledger_H_
#define  __T_subledger_H_
typedef struct 
{
		int	seqno;
		unsigned int	subjno;
		int	settledate;
		int	vouchertype;
		int	voucherno;
		char	summary[60+1];
		unsigned int	oppsubjno;
		double	dramt;
		double	cramt;
		int	balflag;
		double	balance;
		int	postdate;
}T_t_subledger;
int DB_t_subledger_add(T_t_subledger *pt_subledger);
int DB_t_subledger_read_by_seqno(int v_seqno,T_t_subledger *pt_subledger);
int DB_t_subledger_update_by_seqno(int v_seqno,T_t_subledger *pt_subledger);
int DB_t_subledger_del_by_seqno(int v_seqno);
int DB_t_subledger_read_lock_by_c0_and_seqno(int v_seqno,T_t_subledger *pt_subledger);
int DB_t_subledger_update_lock_by_c0(T_t_subledger *pt_subledger);
int DB_t_subledger_del_lock_by_c0();
int DB_t_subledger_free_lock_by_c0();
#endif
