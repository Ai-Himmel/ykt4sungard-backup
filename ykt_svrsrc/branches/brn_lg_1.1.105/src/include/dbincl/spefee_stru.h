#ifndef  __T_spefee_H_
#define  __T_spefee_H_
typedef struct 
{
		char	dept_code[10+1];
		int	cut_type;
		int	fee_type;
}T_t_pif_spefee;
int DB_t_pif_spefee_read_by_dept_code_and_cut_type(char *v_dept_code,int v_cut_type,T_t_pif_spefee *pt_pif_spefee);
#endif
