#ifndef  __T_depoper_H_
#define  __T_depoper_H_
typedef struct 
{
		char	oper_code[30+1];
		char	status[1+1];
		char	usedevlimit_flag[1+1];
		char	shopoper_flag[1+1];
		char	open_date[8+1];
		char	close_date[8+1];
		int	max_amt;
		int	total_cnt;
		int	total_amt;
		char	lastday[8+1];
		int	lastday_total_cnt;
		int	lastday_total_amt;
		char	last_device_id[30+1];
		int	last_pos_serial_no;
		int	last_host_serial_no;
		int	last_card_id;
		char	last_saved[30+1];
}T_t_deposit_oper;
int DB_t_deposit_oper_add(T_t_deposit_oper *pt_deposit_oper);
int DB_t_deposit_oper_read_by_oper_code(char *v_oper_code,T_t_deposit_oper *pt_deposit_oper);
int DB_t_deposit_oper_read_lock_by_cur_and_oper_code(char *v_oper_code,T_t_deposit_oper *pt_deposit_oper);
int DB_t_deposit_oper_update_lock_by_cur(T_t_deposit_oper *pt_deposit_oper);
int DB_t_deposit_oper_free_lock_by_cur();
int DB_t_deposit_oper_del_by_oper_code(char *v_oper_code);
int DB_t_deposit_oper_read_lock_by_c1_and_last_device_id_and_last_pos_serial_no(char *v_last_device_id,int v_last_pos_serial_no,T_t_deposit_oper *pt_deposit_oper);
int DB_t_deposit_oper_update_lock_by_c1(T_t_deposit_oper *pt_deposit_oper);
int DB_t_deposit_oper_free_lock_by_c1();
#endif
