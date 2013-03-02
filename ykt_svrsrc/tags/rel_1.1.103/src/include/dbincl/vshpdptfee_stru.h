#ifndef  __T_vshpdptfee_H_
#define  __T_vshpdptfee_H_
typedef struct 
{
		int	shop_id;
		char	shop_name[50+1];
		int	shop_type;
		int	shop_state;
		int	dept_id;
		char	is_indep[1+1];
		int	seri_type;
		int	fee_type;
		int	outorin;
		int	opcount;
		double	fee_change;
}T_v_tif_shopdeptfee;
int DB_v_tif_shopdeptfee_open_select_by_c1();
int DB_v_tif_shopdeptfee_fetch_select_by_c1(T_v_tif_shopdeptfee *pv_tif_shopdeptfee);
int DB_v_tif_shopdeptfee_close_select_by_c1();
int DB_v_tif_shopdeptfee_open_select_by_c2_and_shop_id(int v_shop_id);
int DB_v_tif_shopdeptfee_fetch_select_by_c2(T_v_tif_shopdeptfee *pv_tif_shopdeptfee);
int DB_v_tif_shopdeptfee_close_select_by_c2();
int DB_v_tif_shopdeptfee_open_select_by_c3_and_dept_id(int v_dept_id);
int DB_v_tif_shopdeptfee_fetch_select_by_c3(T_v_tif_shopdeptfee *pv_tif_shopdeptfee);
int DB_v_tif_shopdeptfee_close_select_by_c3();
int DB_v_tif_shopdeptfee_open_select_by_c4_and_fee_type(int v_fee_type);
int DB_v_tif_shopdeptfee_fetch_select_by_c4(T_v_tif_shopdeptfee *pv_tif_shopdeptfee);
int DB_v_tif_shopdeptfee_close_select_by_c4();
int DB_v_tif_shopdeptfee_open_select_by_c6_and_is_indep(char *v_is_indep);
int DB_v_tif_shopdeptfee_fetch_select_by_c6(T_v_tif_shopdeptfee *pv_tif_shopdeptfee);
int DB_v_tif_shopdeptfee_close_select_by_c6();
#endif
