#ifndef  __T_subupd_H_
#define  __T_subupd_H_
typedef struct 
{
		int	sub_id;
		char	sub_volume[12+1];
		int	sub_flag;
}T_t_pif_sub_update;
int DB_t_pif_sub_update_add(T_t_pif_sub_update *pt_pif_sub_update);
int DB_t_pif_sub_update_read_lock_by_cur0_and_sub_id_and_sub_flag(int v_sub_id,int v_sub_flag,T_t_pif_sub_update *pt_pif_sub_update);
int DB_t_pif_sub_update_update_lock_by_cur0(T_t_pif_sub_update *pt_pif_sub_update);
int DB_t_pif_sub_update_free_lock_cur0();
#endif
