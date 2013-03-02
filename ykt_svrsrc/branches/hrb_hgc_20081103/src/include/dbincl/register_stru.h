#ifndef  __T_register_H_
#define  __T_register_H_
typedef struct 
{
		char	stuemp_no[20+1];
		char	cut_name[60+1];
		int	register_flag;
		char	register_info[60+1];
		char	operate_date[10+1];
		char	operate_time[8+1];
		int	flag;
		int	reserver_no1;
		char	reserver_no2[60+1];
		int	reserver_no3;
		int	reg_id;
}T_t_tif_register_pay;
int DB_t_tif_register_pay_add(T_t_tif_register_pay *pt_tif_register_pay);
int DB_t_tif_register_pay_del_by_stuemp_no(char *v_stuemp_no);
int DB_t_tif_register_pay_read_by_stuemp_no(char *v_stuemp_no,T_t_tif_register_pay *pt_tif_register_pay);
int DB_t_tif_register_pay_read_lock_by_cur_and_stuemp_no(char *v_stuemp_no,T_t_tif_register_pay *pt_tif_register_pay);
int DB_t_tif_register_pay_update_by_stuemp_no(char *v_stuemp_no,T_t_tif_register_pay *pt_tif_register_pay);
int DB_t_tif_register_pay_update_lock_by_cur(T_t_tif_register_pay *pt_tif_register_pay);
int DB_t_tif_register_pay_free_lock_cur();
int DB_t_tif_register_pay_open_select_by_cur1_and_stuemp_no(char *v_stuemp_no);
int DB_t_tif_register_pay_fetch_select_by_cur1(T_t_tif_register_pay *pt_tif_register_pay);
int DB_t_tif_register_pay_close_select_by_cur1();
int DB_t_tif_register_pay_open_select_by_cur2_and_operate_date(char *v_operate_date);
int DB_t_tif_register_pay_fetch_select_by_cur2(T_t_tif_register_pay *pt_tif_register_pay);
int DB_t_tif_register_pay_close_select_by_cur2();
#endif
