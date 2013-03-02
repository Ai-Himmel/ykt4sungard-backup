#ifndef  __T_shoptree_H_
#define  __T_shoptree_H_
typedef struct 
{
		int	shop_id;
		char	shop_name[50+1];
		int	dept_id;
		int	leaf_id;
		char	leaf_name[50+1];
		char	is_indep[1+1];
		char	is_leaf[1+1];
		int	depth;
}T_v_cif_shop_tree;
int DB_v_cif_shop_tree_open_select_by_c1_and_shop_id(int v_shop_id);
int DB_v_cif_shop_tree_fetch_select_by_c1(T_v_cif_shop_tree *pv_cif_shop_tree);
int DB_v_cif_shop_tree_close_select_by_c1();
#endif
