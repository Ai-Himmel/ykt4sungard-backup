#ifndef  __T_bankcomp_H_
#define  __T_bankcomp_H_
typedef struct 
{
		char	op_date[8+1];
		char	tx_code[6+1];
		int	card_id;
		char	bankcard[40+1];
		int	local_sn;
		char	bank_sn[20+1];
		char	trans_money[9+1];
}T_t_tif_bank_comp;
int DB_t_tif_bank_comp_add(T_t_tif_bank_comp *pt_tif_bank_comp);
int DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(char *v_op_date);
int DB_t_tif_bank_comp_fetch_select_by_cur1(T_t_tif_bank_comp *pt_tif_bank_comp);
int DB_t_tif_bank_comp_close_select_by_cur1();
#endif
