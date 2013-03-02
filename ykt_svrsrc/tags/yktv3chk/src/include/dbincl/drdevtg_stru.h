#ifndef  __T_drdevtg_H_
#define  __T_drdevtg_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	timegrpid;
		int	seqno;
		int	flag;
		char	lastsaved[30+1];
		char	downloadtime[30+1];
		int	refcnt;
}T_t_doordevtimegrptbl;
int DB_t_doordevtimegrptbl_add(T_t_doordevtimegrptbl *pt_doordevtimegrptbl);
int DB_t_doordevtimegrptbl_read_by_majordevid_and_minordevid_and_timegrpid(int v_majordevid,int v_minordevid,int v_timegrpid,T_t_doordevtimegrptbl *pt_doordevtimegrptbl);
int DB_t_doordevtimegrptbl_update_by_majordevid_and_minordevid_and_timegrpid(int v_majordevid,int v_minordevid,int v_timegrpid,T_t_doordevtimegrptbl *pt_doordevtimegrptbl);
int DB_t_doordevtimegrptbl_del_by_majordevid_and_minordevid_and_timegrpid(int v_majordevid,int v_minordevid,int v_timegrpid);
int DB_t_doordevtimegrptbl_open_select_by_c0_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevtimegrptbl_fetch_select_by_c0(T_t_doordevtimegrptbl *pt_doordevtimegrptbl);
int DB_t_doordevtimegrptbl_close_select_by_c0();
#endif
