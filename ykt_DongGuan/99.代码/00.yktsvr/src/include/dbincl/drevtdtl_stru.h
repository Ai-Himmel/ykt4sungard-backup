#ifndef  __T_drevtdtl_H_
#define  __T_drevtdtl_H_
typedef struct 
{
		int	deviceid;
		char	transdate[8+1];
		char	transtime[6+1];
		int	eventcode;
		char	eventmsg[240+1];
		int	sysid;
		char	coldate[8+1];
		char	coltime[6+1];
}T_t_dooreventdtl;
int DB_t_dooreventdtl_add(T_t_dooreventdtl *pt_dooreventdtl);
int DB_t_dooreventdtl_read_by_deviceid_and_transdate_and_transtime_and_eventcode(int v_deviceid,const char *v_transdate,const char *v_transtime,int v_eventcode,T_t_dooreventdtl *pt_dooreventdtl);
int DB_t_dooreventdtl_update_by_deviceid_and_transdate_and_transtime_and_eventcode(int v_deviceid,char *v_transdate,char *v_transtime,int v_eventcode,T_t_dooreventdtl *pt_dooreventdtl);
int DB_t_dooreventdtl_del_by_deviceid_and_transdate_and_transtime_and_eventcode(int v_deviceid,const char *v_transdate,const char *v_transtime,int v_eventcode);
int DB_t_dooreventdtl_read_lock_by_c0_and_deviceid_and_transdate_and_transtime_and_eventcode(int v_deviceid,const char *v_transdate,const char *v_transtime,int v_eventcode,T_t_dooreventdtl *pt_dooreventdtl);
int DB_t_dooreventdtl_update_lock_by_c0(T_t_dooreventdtl *pt_dooreventdtl);
int DB_t_dooreventdtl_free_lock_by_c0();
#endif
