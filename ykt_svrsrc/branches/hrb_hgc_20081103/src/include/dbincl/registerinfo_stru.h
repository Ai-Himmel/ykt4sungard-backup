#ifndef  __T_registerinfo_H_
#define  __T_registerinfo_H_
typedef struct 
{
		int	register_flag;
		char	register_info[60+1];
}T_t_tif_register_info;
int DB_t_tif_register_info_add(T_t_tif_register_info *pt_tif_register_info);
int DB_t_tif_register_info_read_by_register_flag(int v_register_flag,T_t_tif_register_info *pt_tif_register_info);
#endif
