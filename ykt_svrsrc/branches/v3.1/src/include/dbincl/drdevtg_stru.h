#ifndef  __T_drdevtg_H_
#define  __T_drdevtg_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	timegrpid;
		int	seqno;
		int	adddelflag;
		int	downstatus;
		char	downtime[30+1];
		int	refcnt;
		char	updatetime[30+1];
}T_t_doordevtimegrp;
int DB_t_doordevtimegrp_add(T_t_doordevtimegrp *pt_doordevtimegrp);
int DB_t_doordevtimegrp_read_by_majordevid_and_minordevid_and_timegrpid(int v_majordevid,int v_minordevid,int v_timegrpid,T_t_doordevtimegrp *pt_doordevtimegrp);
int DB_t_doordevtimegrp_update_by_majordevid_and_minordevid_and_timegrpid(int v_majordevid,int v_minordevid,int v_timegrpid,T_t_doordevtimegrp *pt_doordevtimegrp);
int DB_t_doordevtimegrp_del_by_majordevid_and_minordevid_and_timegrpid(int v_majordevid,int v_minordevid,int v_timegrpid);
int DB_t_doordevtimegrp_read_lock_by_c0_and_majordevid_and_minordevid_and_timegrpid(int v_majordevid,int v_minordevid,int v_timegrpid,T_t_doordevtimegrp *pt_doordevtimegrp);
int DB_t_doordevtimegrp_update_lock_by_c0(T_t_doordevtimegrp *pt_doordevtimegrp);
int DB_t_doordevtimegrp_free_lock_by_c0();
int DB_t_doordevtimegrp_open_select_by_c1_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevtimegrp_fetch_select_by_c1(T_t_doordevtimegrp *pt_doordevtimegrp);
int DB_t_doordevtimegrp_close_select_by_c1();
#endif
