#ifndef  __T_subsidy_H_
#define  __T_subsidy_H_
typedef struct 
{
		int	subsidy_no;
		int	cust_no;
		char	batch_no[14+1];
		int	seqno;
		char	oper_code[10+1];
		int	card_no;
		char	summary[60+1];
		char	expire_date[8+1];
		int	bill_type;
		char	bill_no[20+1];
		double	amount;
		char	subsidytype[1+1];
		char	tx_date[8+1];
		char	tx_time[6+1];
		char	get_date[8+1];
		char	get_time[6+1];
		char	status[1+1];
		char	broker_id[18+1];
		char	broker_name[60+1];
}T_t_tif_subsidy;
int DB_t_tif_subsidy_add(T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_subsidy_del_by_batch_no(char *v_batch_no);
int DB_t_tif_subsidy_del_by_batch_no_and_cust_no(char *v_batch_no,int v_cust_no);
int DB_t_tif_subsidy_open_select_by_c0_and_cust_no_and_status(int v_cust_no,char *v_status);
int DB_t_tif_subsidy_fetch_select_by_c0(T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_subsidy_close_select_by_c0();
int DB_t_tif_subsidy_open_select_for_update_by_c1_and_cust_no_and_status(int v_cust_no,char *v_status);
int DB_t_tif_subsidy_fetch_select_by_c1(T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_subsidy_update_lock_by_c1(T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_subsidy_close_select_by_c1();
int DB_t_tif_subsidy_open_select_by_c2_and_cust_no(int v_cust_no);
int DB_t_tif_subsidy_fetch_select_by_c2(T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_subsidy_close_select_by_c2();
int DB_t_tif_subsidy_read_lock_by_c3_and_subsidy_no_and_cust_no_and_status(char *v_subsidy_no,int v_cust_no,char *v_status,T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_subsidy_update_lock_by_c3(T_t_tif_subsidy *pt_tif_subsidy);
int DB_t_tif_subsidy_free_lock_by_c3();
#endif
