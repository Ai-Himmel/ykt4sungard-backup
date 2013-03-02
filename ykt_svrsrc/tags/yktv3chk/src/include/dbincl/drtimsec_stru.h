#ifndef  __T_drtimsec_H_
#define  __T_drtimsec_H_
typedef struct 
{
		int	sectid;
		char	sectname[60+1];
		char	starttime[6+1];
		char	endtime[6+1];
		int	flag;
		char	lastsaved[30+1];
}T_t_doortimesect;
int DB_t_doortimesect_add(T_t_doortimesect *pt_doortimesect);
int DB_t_doortimesect_update_by_sectid(int v_sectid,T_t_doortimesect *pt_doortimesect);
int DB_t_doortimesect_read_by_sectid(int v_sectid,T_t_doortimesect *pt_doortimesect);
int DB_t_doortimesect_del_by_sectid(int v_sectid);
int DB_t_doortimesect_open_select_by_cur0();
int DB_t_doortimesect_fetch_select_by_cur0(T_t_doortimesect *pt_doortimesect);
int DB_t_doortimesect_close_select_by_cur0();
#endif
