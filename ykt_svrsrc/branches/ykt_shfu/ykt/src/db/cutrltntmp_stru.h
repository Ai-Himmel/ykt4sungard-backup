#ifndef  __T_cutrltntmp_H_
#define  __T_cutrltntmp_H_
typedef struct 
{
		char	batch_no[14+1];
		int	seqno;
		int	cut_id;
		char	outside_no[60+1];
		int	outside_type;
		char	comment[150+1];
}T_t_pif_cut_relation_tmp;
int DB_t_pif_cut_relation_tmp_add(T_t_pif_cut_relation_tmp *pt_pif_cut_relation_tmp);
int DB_t_pif_cut_relation_tmp_open_select_by_c1_and_batch_no(char *v_batch_no);
int DB_t_pif_cut_relation_tmp_fetch_select_by_c1(T_t_pif_cut_relation_tmp *pt_pif_cut_relation_tmp);
int DB_t_pif_cut_relation_tmp_close_select_by_c1();
#endif
