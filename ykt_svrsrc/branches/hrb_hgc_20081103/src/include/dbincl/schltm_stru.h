#ifndef  __T_schltm_H_
#define  __T_schltm_H_
typedef struct 
{
		int	reg_id;
		int	cuttype;
		char	schoolterm_name[150+1];
		char	reg_begin[8+1];
		char	reg_end[8+1];
		char	reg_extra_date[8+1];
		char	reg_delay[8+1];
		int	reg_flag;
}T_t_tif_register_schoolterm;
int DB_t_tif_register_schoolterm_add(T_t_tif_register_schoolterm *pt_tif_register_schoolterm);
int DB_t_tif_register_schoolterm_read_by_reg_id(int v_reg_id,T_t_tif_register_schoolterm *pt_tif_register_schoolterm);
int DB_t_tif_register_schoolterm_read_by_cuttype_and_reg_flag(int v_cuttype,int v_reg_flag,T_t_tif_register_schoolterm *pt_tif_register_schoolterm);
#endif
