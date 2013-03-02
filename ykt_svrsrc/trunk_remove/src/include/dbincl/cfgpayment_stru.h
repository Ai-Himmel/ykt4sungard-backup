#ifndef  __T_cfgpayment_H_
#define  __T_cfgpayment_H_
typedef struct 
{
		int	paycode;
		char	summary[60+1];
		int	shopid;
		int	enabled;
		char	lastsaved[30+1];
}T_t_cfgpayment;
int DB_t_cfgpayment_add(T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_read_by_paycode(int v_paycode,T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_update_by_paycode(int v_paycode,T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_del_by_paycode(int v_paycode);
int DB_t_cfgpayment_read_lock_by_c0_and_paycode(int v_paycode,T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_update_lock_by_c0(T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_free_lock_by_c0();
int DB_t_cfgpayment_open_select_by_c1_and_paycode(int v_paycode);
int DB_t_cfgpayment_fetch_select_by_c1(T_t_cfgpayment *pt_cfgpayment);
int DB_t_cfgpayment_close_select_by_c1();
#endif
