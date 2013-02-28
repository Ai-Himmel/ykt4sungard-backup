#ifndef  __T_drdevtime_H_
#define  __T_drdevtime_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	timeid;
		int	seqno;
		int	adddelflag;
		int	downstatus;
		char	downtime[30+1];
		int	refcnt;
		char	updatetime[30+1];
}T_t_doordevtime;
int DB_t_doordevtime_add(T_t_doordevtime *pt_doordevtime);
int DB_t_doordevtime_read_by_majordevid_and_minordevid_and_timeid(int v_majordevid,int v_minordevid,int v_timeid,T_t_doordevtime *pt_doordevtime);
int DB_t_doordevtime_update_by_majordevid_and_minordevid_and_timeid(int v_majordevid,int v_minordevid,int v_timeid,T_t_doordevtime *pt_doordevtime);
int DB_t_doordevtime_del_by_majordevid_and_minordevid_and_timeid(int v_majordevid,int v_minordevid,int v_timeid);
int DB_t_doordevtime_read_lock_by_c0_and_majordevid_and_minordevid_and_timeid(int v_majordevid,int v_minordevid,int v_timeid,T_t_doordevtime *pt_doordevtime);
int DB_t_doordevtime_update_lock_by_c0(T_t_doordevtime *pt_doordevtime);
int DB_t_doordevtime_free_lock_by_c0();
int DB_t_doordevtime_open_select_by_c1_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevtime_fetch_select_by_c1(T_t_doordevtime *pt_doordevtime);
int DB_t_doordevtime_close_select_by_c1();
#endif
