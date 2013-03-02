#ifndef  __T_rptbanktransfer_H_
#define  __T_rptbanktransfer_H_
typedef struct 
{
		char	rmb_batch_no1[14+1];
		char	rmb_seq_no[6+1];
		char	rmb_acc_status1[1+1];
		char	rmb_tran_kind[1+1];
		char	rmb_cust_name[50+1];
		char	rmb_acc_no[20+1];
		char	rmb_cb_cr[1+1];
		double	rmb_tran_amt;
		char	rmb_cur_code[3+1];
		char	rmb_host_no[8+1];
		char	rmb_ret_code[4+1];
		char	rmb_acc_date[11+1];
		char	rmb_tran_no[9+1];
		char	rmb_open_branch[7+1];
		char	rmb_vcho_kind[2+1];
		char	rmb_vcho_bat_no[2+1];
		char	rmb_vcho_no[9+1];
		char	rmb_memo[22+1];
		char	rmb_tran_info[200+1];
}T_t_tif_report_bank_transfer;
int DB_t_tif_report_bank_transfer_add(T_t_tif_report_bank_transfer *pt_tif_report_bank_transfer);
int DB_t_tif_report_bank_transfer_del_by_rmb_acc_date(char *v_rmb_acc_date);
int DB_t_tif_report_bank_transfer_open_select_between_c1_and_rmb_acc_date_and_rmb_acc_date(char *v_rmb_acc_date_2,char *v_rmb_acc_date_3);
int DB_t_tif_report_bank_transfer_fetch_select_by_c1(T_t_tif_report_bank_transfer *pt_tif_report_bank_transfer);
int DB_t_tif_report_bank_transfer_close_select_by_c1();
#endif
