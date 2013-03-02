#ifndef  __T_phototmp_H_
#define  __T_phototmp_H_
typedef struct 
{
		char	batch_no[14+1];
		int	seqno;
		char	stuemp_no[20+1];
		char	stuemp_name[60+1];
		char	cut_type[50+1];
		char	dept_code[10+1];
		char	dept_name[100+1];
		char	s_code[10+1];
		char	s_name[90+1];
		char	cur_grade[20+1];
		char	sex[1+1];
		char	man_id[20+1];
		int	is_inschool;
		int	status;
		int	area;
}T_t_cif_phototmp;
int DB_t_cif_phototmp_add(T_t_cif_phototmp *pt_cif_phototmp);
int DB_t_cif_phototmp_open_select_by_c0_and_batch_no(char *v_batch_no);
int DB_t_cif_phototmp_fetch_select_by_c0(T_t_cif_phototmp *pt_cif_phototmp);
int DB_t_cif_phototmp_close_select_by_c0();
#endif
