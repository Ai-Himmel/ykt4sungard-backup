#ifndef  __T_actpara_H_
#define  __T_actpara_H_
typedef struct 
{
		int	paraid;
		int	booksetno;
}T_t_actpara;
int DB_t_actpara_add(T_t_actpara *pt_actpara);
int DB_t_actpara_read_by_paraid(int v_paraid,T_t_actpara *pt_actpara);
int DB_t_actpara_update_by_paraid(int v_paraid,T_t_actpara *pt_actpara);
int DB_t_actpara_del_by_paraid(int v_paraid);
int DB_t_actpara_read_lock_by_c0_and_paraid(int v_paraid,T_t_actpara *pt_actpara);
int DB_t_actpara_update_lock_by_c0(T_t_actpara *pt_actpara);
int DB_t_actpara_free_lock_by_c0();
#endif
