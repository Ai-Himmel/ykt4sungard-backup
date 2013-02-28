#ifndef  __T_cardtrans_H_
#define  __T_cardtrans_H_
typedef struct 
{
		int	cardno;
		char	transdate[8+1];
		char	transtime[6+1];
		int	transcode;
		int	termid;
		int	termseqno;
		int	dpscnt;
		int	paycnt;
		double	amount;
		double	cardbefbal;
		double	cardaftbal;
		int	updcnt;
		char	updtime[14+1];
}T_t_cardtrans;
int DB_t_cardtrans_add(T_t_cardtrans *pt_cardtrans);
int DB_t_cardtrans_read_by_cardno(int v_cardno,T_t_cardtrans *pt_cardtrans);
int DB_t_cardtrans_update_by_cardno(int v_cardno,T_t_cardtrans *pt_cardtrans);
int DB_t_cardtrans_del_by_cardno(int v_cardno);
int DB_t_cardtrans_read_lock_by_c0_and_cardno(int v_cardno,T_t_cardtrans *pt_cardtrans);
int DB_t_cardtrans_update_lock_by_c0(T_t_cardtrans *pt_cardtrans);
int DB_t_cardtrans_del_lock_by_c0();
int DB_t_cardtrans_free_lock_by_c0();
#endif
