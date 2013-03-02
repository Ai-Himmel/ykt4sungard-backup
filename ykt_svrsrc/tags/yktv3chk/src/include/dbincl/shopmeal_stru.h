#ifndef  __T_shopmeal_H_
#define  __T_shopmeal_H_
typedef struct 
{
		int	shopid;
		int	mealid;
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_shopmeal;
int DB_t_shopmeal_add(T_t_shopmeal *pt_shopmeal);
int DB_t_shopmeal_read_by_shopid_and_mealid(int v_shopid,int v_mealid,T_t_shopmeal *pt_shopmeal);
int DB_t_shopmeal_update_by_shopid_and_mealid(int v_shopid,int v_mealid,T_t_shopmeal *pt_shopmeal);
int DB_t_shopmeal_del_by_shopid(int v_shopid);
int DB_t_shopmeal_del_by_shopid_and_mealid(int v_shopid,int v_mealid);
int DB_t_shopmeal_read_lock_by_c0_and_shopid_and_mealid(int v_shopid,int v_mealid,T_t_shopmeal *pt_shopmeal);
int DB_t_shopmeal_update_lock_by_c0(T_t_shopmeal *pt_shopmeal);
int DB_t_shopmeal_free_lock_by_c0();
#endif
