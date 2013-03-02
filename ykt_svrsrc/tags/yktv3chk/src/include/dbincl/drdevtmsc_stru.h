#ifndef  __T_drdevtmsc_H_
#define  __T_drdevtmsc_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	sectid;
		int	seqno;
		char	lastsaved[30+1];
		char	downloadtime[30+1];
		int	refcnt;
		int	flag;
}T_t_doordevtimesecttbl;
int DB_t_doordevtimesecttbl_add(T_t_doordevtimesecttbl *pt_doordevtimesecttbl);
int DB_t_doordevtimesecttbl_read_by_majordevid_and_minordevid_and_sectid(int v_majordevid,int v_minordevid,int v_sectid,T_t_doordevtimesecttbl *pt_doordevtimesecttbl);
int DB_t_doordevtimesecttbl_update_by_majordevid_and_minordevid_and_sectid(int v_majordevid,int v_minordevid,int v_sectid,T_t_doordevtimesecttbl *pt_doordevtimesecttbl);
int DB_t_doordevtimesecttbl_del_by_majordevid_and_minordevid_and_sectid(int v_majordevid,int v_minordevid,int v_sectid);
int DB_t_doordevtimesecttbl_open_select_by_c0_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevtimesecttbl_fetch_select_by_c0(T_t_doordevtimesecttbl *pt_doordevtimesecttbl);
int DB_t_doordevtimesecttbl_close_select_by_c0();
#endif
