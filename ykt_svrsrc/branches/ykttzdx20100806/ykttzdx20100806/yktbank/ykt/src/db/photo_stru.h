#ifndef  __T_photo_H_
#define  __T_photo_H_
typedef struct 
{
		char	stuemp_no[20+1];
		char	stuemp_name[60+1];
		char	cut_type[50+1];
		char	dept_code[10+1];
		char	dept_name[100+1];
		char	s_code[100+1];
		char	s_name[90+1];
		char	cur_grade[20+1];
		char	sex[1+1];
		char	man_id[20+1];
		int	is_inschool;
		int	status;
		char	batch_no[14+1];
}T_t_cif_photo;
int DB_t_cif_photo_add(T_t_cif_photo *pt_cif_photo);
#endif
