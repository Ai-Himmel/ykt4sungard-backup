#ifndef  __T_customtmp_H_
#define  __T_customtmp_H_
typedef struct 
{
		char	batch_no[14+1];
		int	seqno;
		char	stuemp_no[20+1];
		char	cut_name[60+1];
		int	cut_type;
		int	fee_type;
		char	sex[1+1];
		char	man_id[20+1];
		char	phone[20+1];
		int	area;
		char	dept_no[10+1];
		char	s_code[10+1];
		char	in_school_date[8+1];
		char	out_school_date[8+1];
		int	card_type;
		char	oper_code[10+1];
		char	status[1+1];
		char	class_no[10+1];
}T_t_cif_customer_tmp;
int DB_t_cif_customer_tmp_add(T_t_cif_customer_tmp *pt_cif_customer_tmp);
int DB_t_cif_customer_tmp_open_select_by_c0_and_batch_no(char *v_batch_no);
int DB_t_cif_customer_tmp_fetch_select_by_c0(T_t_cif_customer_tmp *pt_cif_customer_tmp);
int DB_t_cif_customer_tmp_close_select_by_c0();
int DB_t_cif_customer_tmp_del_by_oper_code(char *v_oper_code);
int DB_t_cif_customer_tmp_del_all();
#endif
