#ifndef  __T_drdevcardlist_H_
#define  __T_drdevcardlist_H_
typedef struct 
{
		int	deviceid;
		int	custid;
		int	weekid;
		int	holidayid;
		int	cardno;
		char	cardphyid[16+1];
		char	cardverno[12+1];
		int	adddelflag;
		int	downstatus;
		char	downtime[30+1];
		char	updatetime[30+1];
}T_t_doordevcardlist;
int DB_t_doordevcardlist_add(T_t_doordevcardlist *pt_doordevcardlist);
int DB_t_doordevcardlist_read_by_deviceid_and_weekid_and_custid(int v_deviceid,int v_weekid,int v_custid,T_t_doordevcardlist *pt_doordevcardlist);
int DB_t_doordevcardlist_update_by_deviceid_and_custid_and_weekid(int v_deviceid,int v_custid,int v_weekid,T_t_doordevcardlist *pt_doordevcardlist);
int DB_t_doordevcardlist_del_by_deviceid_and_custid_and_weekid(int v_deviceid,int v_custid,int v_weekid);
int DB_t_doordevcardlist_read_lock_by_c0_and_deviceid_and_custid_and_weekid(int v_deviceid,int v_custid,int v_weekid,T_t_doordevcardlist *pt_doordevcardlist);
int DB_t_doordevcardlist_update_lock_by_c0(T_t_doordevcardlist *pt_doordevcardlist);
int DB_t_doordevcardlist_free_lock_by_c0();
int DB_t_doordevcardlist_open_select_by_c1_and_deviceid_and_custid(int v_deviceid,int v_custid);
int DB_t_doordevcardlist_fetch_select_by_c1(T_t_doordevcardlist *pt_doordevcardlist);
int DB_t_doordevcardlist_close_select_by_c1();
#endif
