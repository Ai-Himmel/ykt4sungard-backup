#ifndef  __T_drdevhld_H_
#define  __T_drdevhld_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	holidayid;
		int	seqno;
		int	flag;
		char	lastsaved[30+1];
		char	downloadtime[30+1];
		int	refcnt;
}T_t_doordevholidaytbl;
int DB_t_doordevholidaytbl_add(T_t_doordevholidaytbl *pt_doordevholidaytbl);
int DB_t_doordevholidaytbl_read_by_majordevid_and_minordevid_and_holidayid(int v_majordevid,int v_minordevid,int v_holidayid,T_t_doordevholidaytbl *pt_doordevholidaytbl);
int DB_t_doordevholidaytbl_del_by_majordevid_and_minordevid_and_holidayid(int v_majordevid,int v_minordevid,int v_holidayid);
int DB_t_doordevholidaytbl_update_by_majordevid_and_minordevid_and_holidayid(int v_majordevid,int v_minordevid,int v_holidayid,T_t_doordevholidaytbl *pt_doordevholidaytbl);
int DB_t_doordevholidaytbl_open_select_by_c0_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevholidaytbl_fetch_select_by_c0(T_t_doordevholidaytbl *pt_doordevholidaytbl);
int DB_t_doordevholidaytbl_close_select_by_c0();
#endif
