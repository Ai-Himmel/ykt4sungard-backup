#ifndef  __T_drdevweek_H_
#define  __T_drdevweek_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	weekid;
		int	seqno;
		int	adddelflag;
		int	downstatus;
		char	downtime[30+1];
		int	refcnt;
		int	linkcnt;
		char	updatetime[30+1];
}T_t_doordevweek;
int DB_t_doordevweek_add(T_t_doordevweek *pt_doordevweek);
int DB_t_doordevweek_read_by_majordevid_and_minordevid_and_weekid(int v_majordevid,int v_minordevid,int v_weekid,T_t_doordevweek *pt_doordevweek);
int DB_t_doordevweek_update_by_majordevid_and_minordevid_and_weekid(int v_majordevid,int v_minordevid,int v_weekid,T_t_doordevweek *pt_doordevweek);
int DB_t_doordevweek_del_by_majordevid_and_minordevid_and_weekid(int v_majordevid,int v_minordevid,int v_weekid);
int DB_t_doordevweek_read_lock_by_c0_and_majordevid_and_minordevid_and_weekid(int v_majordevid,int v_minordevid,int v_weekid,T_t_doordevweek *pt_doordevweek);
int DB_t_doordevweek_update_lock_by_c0(T_t_doordevweek *pt_doordevweek);
int DB_t_doordevweek_free_lock_by_c0();
int DB_t_doordevweek_open_select_by_c1_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevweek_fetch_select_by_c1(T_t_doordevweek *pt_doordevweek);
int DB_t_doordevweek_close_select_by_c1();
#endif
