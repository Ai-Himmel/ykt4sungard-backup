#ifndef  __T_thirdpartsys_H_
#define  __T_thirdpartsys_H_
typedef struct 
{
		int	sub_system_id;
		char	des_ip[20+1];
		int	des_bcc_func;
		int	des_port;
		int	des_drtp_node;
		int	des_func;
		char	bu_name[60+1];
}T_t_pif_third_part_system;
int DB_t_pif_third_part_system_add(T_t_pif_third_part_system *pt_pif_third_part_system);
int DB_t_pif_third_part_system_read_lock_by_cur0_and_sub_system_id(int v_sub_system_id,T_t_pif_third_part_system *pt_pif_third_part_system);
int DB_t_pif_third_part_system_update_lock_by_cur0(T_t_pif_third_part_system *pt_pif_third_part_system);
int DB_t_pif_third_part_system_free_lock_cur0();
#endif
