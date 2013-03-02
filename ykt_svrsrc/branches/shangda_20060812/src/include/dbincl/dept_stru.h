#ifndef  __T_dept_H_
#define  __T_dept_H_
typedef struct 
{
		char	dept_code[10+1];
		char	is_academy[1+1];
		char	dept_name[100+1];
		char	e_name[100+1];
		char	parentdept_code[10+1];
		int	dept_level;
		char	is_availability[1+1];
		char	comments[150+1];
}T_t_cif_dept;
int DB_t_cif_dept_add(T_t_cif_dept *pt_cif_dept);
int DB_t_cif_dept_read_by_dept_code(char *v_dept_code,T_t_cif_dept *pt_cif_dept);
int DB_t_cif_dept_del_by_dept_code(char *v_dept_code);
int DB_t_cif_dept_read_lock_by_c0_and_dept_code(char *v_dept_code,T_t_cif_dept *pt_cif_dept);
int DB_t_cif_dept_update_lock_by_c0(T_t_cif_dept *pt_cif_dept);
int DB_t_cif_dept_update_by_dept_code(char *v_dept_code,T_t_cif_dept *pt_cif_dept);
int DB_t_cif_dept_free_lock_c0();
#endif
