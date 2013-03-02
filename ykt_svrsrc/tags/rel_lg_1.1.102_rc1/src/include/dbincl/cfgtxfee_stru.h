#ifndef  __T_cfgtxfee_H_
#define  __T_cfgtxfee_H_
typedef struct 
{
		int	fee_type;
		int	tx_code;
		char	fee_list[40+1];
		char	idxdbactno_list[40+1];
		char	idxcractno_list[40+1];
		char	formula_list[255+1];
}T_t_tif_cfgtxfee;
int DB_t_tif_cfgtxfee_read_by_tx_code_and_fee_type(int v_tx_code,int v_fee_type,T_t_tif_cfgtxfee *pt_tif_cfgtxfee);
int DB_t_tif_cfgtxfee_open_select_by_c0();
int DB_t_tif_cfgtxfee_fetch_select_by_c0(T_t_tif_cfgtxfee *pt_tif_cfgtxfee);
int DB_t_tif_cfgtxfee_close_select_by_c0();
#endif
