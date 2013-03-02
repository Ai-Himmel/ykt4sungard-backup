#ifndef  __T_mealtype_H_
#define  __T_mealtype_H_
typedef struct 
{
		int	meal_id;
		char	meal_name[60+1];
		char	begin_time[6+1];
		char	end_time[6+1];
		char	comment[200+1];
}T_t_pif_meal_type;
int DB_t_pif_meal_type_add(T_t_pif_meal_type *pt_pif_meal_type);
int DB_t_pif_meal_type_del_by_meal_id(int v_meal_id);
int DB_t_pif_meal_type_read_by_meal_id(int v_meal_id,T_t_pif_meal_type *pt_pif_meal_type);
int DB_t_pif_meal_type_read_lock_by_cur_and_meal_id(int v_meal_id,T_t_pif_meal_type *pt_pif_meal_type);
int DB_t_pif_meal_type_update_lock_by_cur(T_t_pif_meal_type *pt_pif_meal_type);
int DB_t_pif_meal_type_free_lock_cur();
#endif
