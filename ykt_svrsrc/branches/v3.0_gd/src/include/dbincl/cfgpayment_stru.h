#ifndef  __T_cfgpayment_H_
#define  __T_cfgpayment_H_
typedef struct 
{
		int	paycode;
		char	summary[60+1];
		int	enabled;
		int	onlinepay;
		int	paychkflag;
		int	payeeacctype;
		int	shopid;
		int	bccfuncno;
		int	bccdrtpno;
		char	ip[15+1];
		int	port;
		int	timeout;
		char	lastsaved[30+1];
}T_t_cfgpayment;
int DB_t_cfgpayment_add(T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_read_by_paycode(int v_paycode,T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_update_by_paycode(int v_paycode,T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_del_by_paycode(int v_paycode);
int DB_t_cfgpayment_read_lock_by_c0_and_paycode(int v_paycode,T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_update_lock_by_c0(T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_free_lock_by_c0();
#endif
