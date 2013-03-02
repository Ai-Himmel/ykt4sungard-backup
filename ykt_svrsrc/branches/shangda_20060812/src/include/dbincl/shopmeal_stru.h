#ifndef  __T_shopmeal_H_
#define  __T_shopmeal_H_
typedef struct 
{
		int	shop_id;
		int	meal_id;
		char	update_date[8+1];
		char	update_oper[8+1];
		char	comment[200+1];
}T_t_cif_shop_meal;
int DB_t_cif_shop_meal_add(T_t_cif_shop_meal *pt_cif_shop_meal);
int DB_t_cif_shop_meal_del_by_shop_id(int v_shop_id);
#endif
