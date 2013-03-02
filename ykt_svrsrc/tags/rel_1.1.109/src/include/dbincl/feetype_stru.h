#ifndef  __T_feetype_H_
#define  __T_feetype_H_
typedef struct 
{
		int	fee_type;
		char	fee_name[120+1];
		char	comments[150+1];
		char	is_outfee[1+1];
}T_t_pif_feetype;
int DB_t_pif_feetype_open_select_by_cur1();
int DB_t_pif_feetype_fetch_select_by_cur1(T_t_pif_feetype *pt_pif_feetype);
int DB_t_pif_feetype_close_select_by_cur1();
int DB_t_pif_feetype_add(T_t_pif_feetype *pt_pif_feetype);
int DB_t_pif_feetype_read_lock_by_cur_and_fee_type(int v_fee_type,T_t_pif_feetype *pt_pif_feetype);
int DB_t_pif_feetype_update_lock_by_cur(T_t_pif_feetype *pt_pif_feetype);
int DB_t_pif_feetype_free_lock_cur();
int DB_t_pif_feetype_del_by_fee_type(int v_fee_type);
#endif
