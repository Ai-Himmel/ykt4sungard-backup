#ifndef  __T_drcard_H_
#define  __T_drcard_H_
typedef struct 
{
		int	deviceid;
		int	custid;
		int	cardno;
		char	cardphyid[16+1];
		char	cardverno[12+1];
		int	status;
		char	insertdate[14+1];
}T_t_doorcard;
int DB_t_doorcard_add(T_t_doorcard *pt_doorcard);
int DB_t_doorcard_read_by_deviceid_and_cardno(int v_deviceid,int v_cardno,T_t_doorcard *pt_doorcard);
int DB_t_doorcard_read_lock_by_c0_and_deviceid_and_cardno(int v_deviceid,int v_cardno,T_t_doorcard *pt_doorcard);
int DB_t_doorcard_update_lock_by_c0(T_t_doorcard *pt_doorcard);
int DB_t_doorcard_free_lock_by_c0();
int DB_t_doorcard_update_by_deviceid_and_cardno(int v_deviceid,int v_cardno,T_t_doorcard *pt_doorcard);
#endif
