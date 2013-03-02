#ifndef  __T_cuttypefee_H_
#define  __T_cuttypefee_H_
typedef struct 
{
		int	cut_type;
		char	type_name[50+1];
		char	is_outfee[1+1];
		double	ratio;
		int	validdate;
		double	deposit_fee;
		double	cost_fee;
		double	in_fee;
		int	is_firstcostfee;
		int	is_returncostfee;
		double	max_bala;
}T_t_cif_cuttypefee;
int DB_t_cif_cuttypefee_add(T_t_cif_cuttypefee *pt_cif_cuttypefee);
int DB_t_cif_cuttypefee_read_by_cut_type(int v_cut_type,T_t_cif_cuttypefee *pt_cif_cuttypefee);
int DB_t_cif_cuttypefee_del_by_cut_type(int v_cut_type);
int DB_t_cif_cuttypefee_open_select_by_c0();
int DB_t_cif_cuttypefee_fetch_select_by_c0(T_t_cif_cuttypefee *pt_cif_cuttypefee);
int DB_t_cif_cuttypefee_close_select_by_c0();
#endif
