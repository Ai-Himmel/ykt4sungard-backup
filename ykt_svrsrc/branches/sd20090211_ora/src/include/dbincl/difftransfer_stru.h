#ifndef  __T_difftransfer_H_
#define  __T_difftransfer_H_
typedef struct 
{
		char	op_date[8+1];
		char	op_time[6+1];
		int	local_sn;
		char	bank_sn[40+1];
		double	local_amt;
		double	bank_amt;
		int	card_id;
		char	bankcard[40+1];
		double	diff_amt;
		int	status;
}T_t_tif_diff_transfer;
int DB_t_tif_diff_transfer_add(T_t_tif_diff_transfer *pt_tif_diff_transfer);
int DB_t_tif_diff_transfer_read_lock_by_c0_and_op_date_and_local_sn(char *v_op_date,int v_local_sn,T_t_tif_diff_transfer *pt_tif_diff_transfer);
int DB_t_tif_diff_transfer_update_lock_by_c0(T_t_tif_diff_transfer *pt_tif_diff_transfer);
int DB_t_tif_diff_transfer_free_lock_by_c0();
#endif
