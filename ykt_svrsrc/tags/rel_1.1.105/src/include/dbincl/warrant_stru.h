#ifndef  __T_warrant_H_
#define  __T_warrant_H_
typedef struct 
{
		char	warrant_no[20+1];
		int	wtype;
		char	wname[60+1];
		char	cur_no[20+1];
		char	begin_no[20+1];
		char	end_no[20+1];
		char	comments[150+1];
}T_t_tif_warrant;
int DB_t_tif_warrant_add(T_t_tif_warrant *pt_tif_warrant);
int DB_t_tif_warrant_del_by_wtype(int v_wtype);
int DB_t_tif_warrant_read_by_wtype(int v_wtype,T_t_tif_warrant *pt_tif_warrant);
int DB_t_tif_warrant_read_lock_by_cur_and_wtype(int v_wtype,T_t_tif_warrant *pt_tif_warrant);
int DB_t_tif_warrant_update_by_wtype(int v_wtype,T_t_tif_warrant *pt_tif_warrant);
int DB_t_tif_warrant_update_lock_by_cur(T_t_tif_warrant *pt_tif_warrant);
int DB_t_tif_warrant_free_lock_cur();
#endif
