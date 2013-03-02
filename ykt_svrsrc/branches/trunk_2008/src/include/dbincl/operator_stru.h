#ifndef  __T_operator_H_
#define  __T_operator_H_
typedef struct 
{
		char	oper_code[10+1];
		char	employee_id[20+1];
		int	card_id;
		char	oper_name[32+1];
		char	phone[40+1];
		char	mobile[40+1];
		char	addr[80+1];
		char	zip[6+1];
		char	email[60+1];
		char	if_station[1+1];
		char	if_access[1+1];
		char	pwd[32+1];
		char	status[1+1];
		char	menu_set[800+1];
		char	func_set[600+1];
		char	login_time[26+1];
		char	logout_time[26+1];
		int	module_qty;
		int	fail_number;
		char	login_ip[20+1];
		char	mac_addr[20+1];
		char	login_flag[1+1];
		char	login_app[1+1];
		char	reg_date[8+1];
		char	reg_time[8+1];
		char	order_status[1+1];
		char	seat_no[10+1];
		int	main_func;
		char	recv_rsp_flag[1+1];
		char	recv_info_flag[1+1];
		int	login_batch;
		int	source_no;
		int	node_id;
		char	specify_func_flag[1+1];
		char	force_logout_reason[70+1];
		char	comments[100+1];
}T_t_pif_operator;
int DB_t_pif_operator_read_by_oper_code(char *v_oper_code,T_t_pif_operator *pt_pif_operator);
int DB_t_pif_operator_update_by_oper_code(char *v_oper_code,T_t_pif_operator *pt_pif_operator);
#endif
