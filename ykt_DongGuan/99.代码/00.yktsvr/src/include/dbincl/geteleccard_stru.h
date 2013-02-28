#ifndef  __T_geteleccard_H_
#define  __T_geteleccard_H_
typedef struct 
{
		int	cardno;
		char	cardphyid[16+1];
		int	usetype;
		int	adddelflag;
		int	deviceid;
		char	downtime[30+1];
}T_t_geteleccard;
int DB_t_geteleccard_add(T_t_geteleccard *pt_geteleccard);
int DB_t_geteleccard_read_by_cardno_and_deviceid(int v_cardno,int v_deviceid,T_t_geteleccard *pt_geteleccard);
int DB_t_geteleccard_del_by_cardno_and_deviceid(int v_cardno,int v_deviceid);
int DB_t_geteleccard_update_by_cardno_and_deviceid(int v_cardno,int v_deviceid,T_t_geteleccard *pt_geteleccard);
int DB_t_geteleccard_read_lock_by_c0_and_cardno_and_deviceid(int v_cardno,int v_deviceid,T_t_geteleccard *pt_geteleccard);
int DB_t_geteleccard_update_lock_by_c0(T_t_geteleccard *pt_geteleccard);
int DB_t_geteleccard_free_lock_by_c0();
#endif
