#ifndef  __T_rpttranscomp_H_
#define  __T_rpttranscomp_H_
typedef struct 
{
		char	cmp_date[10+1];
		int	cmp_flag;
		int	adjust_flag;
		int	localself_num;
		double	localself_amt;
		int	localauto_num;
		double	localauto_amt;
		int	localfee_num;
		double	localfee_amt;
		int	bankself_num;
		double	bankself_amt;
		int	bankauto_num;
		double	bankauto_amt;
		int	bankfee_num;
		double	bankfee_amt;
		char	date_sign[8+1];
		char	reserve1[20+1];
		char	reserve2[20+1];
}T_t_tif_report_trans_comp;
int DB_t_tif_report_trans_comp_add(T_t_tif_report_trans_comp *pt_tif_report_trans_comp);
int DB_t_tif_report_trans_comp_del_by_cmp_date(char *v_cmp_date);
int DB_t_tif_report_trans_comp_open_select_between_c1_and_cmp_date_and_cmp_date(char *v_cmp_date_2,char *v_cmp_date_3);
int DB_t_tif_report_trans_comp_fetch_select_by_c1(T_t_tif_report_trans_comp *pt_tif_report_trans_comp);
int DB_t_tif_report_trans_comp_close_select_by_c1();
#endif
