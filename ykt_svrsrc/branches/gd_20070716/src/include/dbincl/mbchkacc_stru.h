#ifndef  __T_mbchkacc_H_
#define  __T_mbchkacc_H_
typedef struct 
{
		char	tx_date[8+1];
		char	tx_time[6+1];
		int	serial_no;
		int	card_id;
		char	phone[30+1];
		int	amount;
		char	check_status[1+1];
		char	deal_status[1+1];
		char	deal_oper[30+1];
		char	deal_date[8+1];
		char	deal_time[6+1];
}T_t_mobile_chkacc;
int DB_t_mobile_chkacc_add(T_t_mobile_chkacc *pt_mobile_chkacc);
int DB_t_mobile_chkacc_read_lock_by_c0_and_tx_date_and_serial_no_and_card_id(char *v_tx_date,int v_serial_no,int v_card_id,T_t_mobile_chkacc *pt_mobile_chkacc);
int DB_t_mobile_chkacc_update_lock_by_c0(T_t_mobile_chkacc *pt_mobile_chkacc);
#endif
