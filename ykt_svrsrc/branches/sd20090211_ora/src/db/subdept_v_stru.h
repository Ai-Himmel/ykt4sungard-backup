#ifndef  __T_subdept_v_H_
#define  __T_subdept_v_H_
typedef struct 
{
		char	subno[20+1];
		int	seri_type;
		int	outorin;
		int	op_count;
		double	fee_change;
}T_v_tif_subject_dept;
int DB_v_tif_subject_dept_open_select_by_cur1();
int DB_v_tif_subject_dept_fetch_select_by_cur1(T_v_tif_subject_dept *pv_tif_subject_dept);
int DB_v_tif_subject_dept_close_select_by_cur1();
#endif
