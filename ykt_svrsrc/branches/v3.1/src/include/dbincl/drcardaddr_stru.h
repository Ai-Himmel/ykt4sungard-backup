#ifndef  __T_drcardaddr_H_
#define  __T_drcardaddr_H_
typedef struct 
{
		int	cardaddr;
		int	cardno;
		char	useflag[1+1];
		int	adddelflag;
		int	listid;
		int	ctrlid;
}T_t_doorcardaddr;
int DB_t_doorcardaddr_add(T_t_doorcardaddr *pt_doorcardaddr);
int DB_t_doorcardaddr_read_lock_by_c0_and_cardno_and_ctrlid(int v_cardno,int v_ctrlid,T_t_doorcardaddr *pt_doorcardaddr);
int DB_t_doorcardaddr_update_lock_by_c0(T_t_doorcardaddr *pt_doorcardaddr);
int DB_t_doorcardaddr_free_lock_c0();
#endif
