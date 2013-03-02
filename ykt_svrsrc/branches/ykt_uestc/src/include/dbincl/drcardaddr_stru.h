#ifndef  __T_drcardaddr_H_
#define  __T_drcardaddr_H_
typedef struct 
{
		int	cardaddr;
		int	cardno;
		char	useflag[1+1];
		char	adddelflag[1+1];
		int	listid;
		int	ctrlid;
}T_t_doorcard_addr;
int DB_t_doorcard_addr_add(T_t_doorcard_addr *pt_doorcard_addr);
int DB_t_doorcard_addr_read_lock_by_c0_and_cardno_and_ctrlid(int v_cardno,int v_ctrlid,T_t_doorcard_addr *pt_doorcard_addr);
int DB_t_doorcard_addr_update_lock_by_c0(T_t_doorcard_addr *pt_doorcard_addr);
int DB_t_doorcard_addr_free_lock_c0();
#endif
