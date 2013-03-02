#ifndef  __T_drdtl_H_
#define  __T_drdtl_H_
typedef struct 
{
		char	transdate[8+1];
		char	transtime[6+1];
		int	deviceid;
		char	devphyid[30+1];
		int	devseqno;
		char	coldate[8+1];
		char	coltime[6+1];
		int	cardno;
		char	cardphyid[8+1];
		int	custid;
		int	transmark;
		int	sysid;
}T_t_doordtl;
int DB_t_doordtl_add(T_t_doordtl *pt_doordtl);
int DB_t_doordtl_read_by_transdate_and_deviceid_and_devseqno(char *v_transdate,int v_deviceid,int v_devseqno,T_t_doordtl *pt_doordtl);
int DB_t_doordtl_update_by_transdate_and_deviceid_and_devseqno(char *v_transdate,int v_deviceid,int v_devseqno,T_t_doordtl *pt_doordtl);
int DB_t_doordtl_del_by_transdate_and_deviceid_and_devseqno(char *v_transdate,int v_deviceid,int v_devseqno);
int DB_t_doordtl_read_lock_by_c0_and_transdate_and_deviceid_and_devseqno(char *v_transdate,int v_deviceid,int v_devseqno,T_t_doordtl *pt_doordtl);
int DB_t_doordtl_update_lock_by_c0(T_t_doordtl *pt_doordtl);
int DB_t_doordtl_free_lock_by_c0();
#endif
