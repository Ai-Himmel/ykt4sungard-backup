#ifndef  __T_mealtype_H_
#define  __T_mealtype_H_
typedef struct 
{
		int	mealid;
		char	mealname[60+1];
		char	starttime[6+1];
		char	endtime[6+1];
		char	remark[240+1];
}T_t_mealtype;
int DB_t_mealtype_add(T_t_mealtype *pt_mealtype);
int DB_t_mealtype_read_by_mealid(int v_mealid,T_t_mealtype *pt_mealtype);
int DB_t_mealtype_update_by_mealid(int v_mealid,T_t_mealtype *pt_mealtype);
int DB_t_mealtype_del_by_mealid(int v_mealid);
int DB_t_mealtype_read_lock_by_c0_and_mealid(int v_mealid,T_t_mealtype *pt_mealtype);
int DB_t_mealtype_update_lock_by_c0(T_t_mealtype *pt_mealtype);
int DB_t_mealtype_free_lock_by_c0();
#endif
