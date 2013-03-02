#ifndef  __T_speciality_H_
#define  __T_speciality_H_
typedef struct 
{
		char	s_code[10+1];
		char	s_name[100+1];
		char	comments[100+1];
}T_t_cif_speciality;
int DB_t_cif_speciality_read_by_s_code(char *v_s_code,T_t_cif_speciality *pt_cif_speciality);
#endif
