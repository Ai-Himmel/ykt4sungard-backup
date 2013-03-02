#ifndef  __T_drdevwk_H_
#define  __T_drdevwk_H_
typedef struct 
{
		int	majordevid;
		int	minordevid;
		int	weekid;
		int	seqno;
		int	refcnt;
		int	flag;
		char	downdate[30+1];
		char	lastsaved[30+1];
}T_t_doordevweektbl;
int DB_t_doordevweektbl_add(T_t_doordevweektbl *pt_doordevweektbl);
int DB_t_doordevweektbl_read_by_majordevid_and_minordevid_and_weekid(int v_majordevid,int v_minordevid,int v_weekid,T_t_doordevweektbl *pt_doordevweektbl);
int DB_t_doordevweektbl_del_by_majordevid_and_minordevid_and_weekid(int v_majordevid,int v_minordevid,int v_weekid);
int DB_t_doordevweektbl_update_by_majordevid_and_minordevid_and_weekid(int v_majordevid,int v_minordevid,int v_weekid,T_t_doordevweektbl *pt_doordevweektbl);
int DB_t_doordevweektbl_open_select_by_c0_and_majordevid_and_minordevid(int v_majordevid,int v_minordevid);
int DB_t_doordevweektbl_fetch_select_by_c0(T_t_doordevweektbl *pt_doordevweektbl);
int DB_t_doordevweektbl_close_select_by_c0();
#endif
