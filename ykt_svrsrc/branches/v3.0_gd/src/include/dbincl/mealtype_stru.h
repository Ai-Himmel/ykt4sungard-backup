#ifndef  __T_mealtype_H_
#define  __T_mealtype_H_
typedef struct 
{
		int	mealtype;
		char	mealname[30+1];
		char	endtime[6+1];
		char	lastsaved[30+1];
}T_t_mealtype;
int DB_t_mealtype_read_by_mealtype(int v_mealtype,T_t_mealtype *pt_mealtype);
int DB_t_mealtype_update_by_mealtype(int v_mealtype,T_t_mealtype *pt_mealtype);
int DB_t_mealtype_read_lock_by_c0_and_mealtype(int v_mealtype,T_t_mealtype *pt_mealtype);
int DB_t_mealtype_update_lock_by_c0(T_t_mealtype *pt_mealtype);
int DB_t_mealtype_free_lock_by_c0();
#endif
