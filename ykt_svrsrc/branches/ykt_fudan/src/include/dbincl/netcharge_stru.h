#ifndef  __T_netcharge_H_
#define  __T_netcharge_H_
typedef struct 
{
		int	id;
		int	shop_id;
		char	croom_id[8+1];
		int	operate_flag;
		int	bcc_branchno;
		int	bcc_mainfunc;
}T_t_cif_netcharge_shop;
int DB_t_cif_netcharge_shop_add(T_t_cif_netcharge_shop *pt_cif_netcharge_shop);
int DB_t_cif_netcharge_shop_read_by_croom_id(char *v_croom_id,T_t_cif_netcharge_shop *pt_cif_netcharge_shop);
int DB_t_cif_netcharge_shop_read_lock_by_cur0_and_croom_id(char *v_croom_id,T_t_cif_netcharge_shop *pt_cif_netcharge_shop);
int DB_t_cif_netcharge_shop_update_lock_by_cur0(T_t_cif_netcharge_shop *pt_cif_netcharge_shop);
int DB_t_cif_netcharge_shop_free_lock_cur0();
#endif
