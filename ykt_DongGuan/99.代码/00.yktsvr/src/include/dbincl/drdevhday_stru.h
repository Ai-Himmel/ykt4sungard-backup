#ifndef  __T_drdevhday_H_
#define  __T_drdevhday_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	holidayid;
		int	seqno;
		int	adddelflag;
		int	downstatus;
		char	downtime[30+1];
		int	refcnt;
		char	updatetime[30+1];
}T_t_doordevholiday;
int DB_t_doordevholiday_add(T_t_doordevholiday *pt_doordevholiday);
int DB_t_doordevholiday_read_by_majordevid_and_minordevid_and_holidayid(int v_majordevid,int v_minordevid,int v_holidayid,T_t_doordevholiday *pt_doordevholiday);
int DB_t_doordevholiday_update_by_majordevid_and_minordevid_and_holidayid(int v_majordevid,int v_minordevid,int v_holidayid,T_t_doordevholiday *pt_doordevholiday);
int DB_t_doordevholiday_del_by_majordevid_and_minordevid_and_holidayid(int v_majordevid,int v_minordevid,int v_holidayid);
int DB_t_doordevholiday_read_lock_by_c0_and_majordevid_and_minordevid_and_holidayid(int v_majordevid,int v_minordevid,int v_holidayid,T_t_doordevholiday *pt_doordevholiday);
int DB_t_doordevholiday_update_lock_by_c0(T_t_doordevholiday *pt_doordevholiday);
int DB_t_doordevholiday_free_lock_by_c0();
int DB_t_doordevholiday_open_select_by_c1_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevholiday_fetch_select_by_c1(T_t_doordevholiday *pt_doordevholiday);
int DB_t_doordevholiday_close_select_by_c1();
#endif
