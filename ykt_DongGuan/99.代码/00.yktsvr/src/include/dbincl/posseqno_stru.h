#ifndef  __T_posseqno_H_
#define  __T_posseqno_H_
typedef struct 
{
		int	deviceid;
		int	devseqno;
		char	transdate[8+1];
}T_t_posseqno;
int DB_t_posseqno_add(T_t_posseqno *pt_posseqno);
int DB_t_posseqno_read_by_deviceid_and_devseqno_and_transdate(int v_deviceid,int v_devseqno,const char *v_transdate,T_t_posseqno *pt_posseqno);
int DB_t_posseqno_update_by_deviceid_and_devseqno_and_transdate(int v_deviceid,int v_devseqno,char *v_transdate,T_t_posseqno *pt_posseqno);
int DB_t_posseqno_del_by_deviceid_and_devseqno_and_transdate(int v_deviceid,int v_devseqno,const char *v_transdate);
int DB_t_posseqno_read_lock_by_c0_and_deviceid_and_devseqno_and_transdate(int v_deviceid,int v_devseqno,const char *v_transdate,T_t_posseqno *pt_posseqno);
int DB_t_posseqno_update_lock_by_c0(T_t_posseqno *pt_posseqno);
int DB_t_posseqno_free_lock_by_c0();
int DB_t_posseqno_open_select_by_c1_and_deviceid_and_devseqno_and_transdate(int v_deviceid,int v_devseqno,const char *v_transdate);
int DB_t_posseqno_fetch_select_by_c1(T_t_posseqno *pt_posseqno);
int DB_t_posseqno_close_select_by_c1();
#endif
