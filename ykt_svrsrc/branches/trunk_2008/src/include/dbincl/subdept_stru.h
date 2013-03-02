#ifndef  __T_subdept_H_
#define  __T_subdept_H_
typedef struct 
{
		char	balance_date[8+1];
		char	subno[20+1];
		int	seri_type;
		int	outorin;
		int	op_count;
		double	fee_change;
}T_t_tif_subject_dept;
int DB_t_tif_subject_dept_add(T_t_tif_subject_dept *pt_tif_subject_dept);
int DB_t_tif_subject_dept_del_by_balance_date(char *v_balance_date);
#endif
