#ifndef  __T_drhldtim_H_
#define  __T_drhldtim_H_
typedef struct 
{
		int	holidayid;
		char	holidaydate[8+1];
		int	timegrpid;
		int	flag;
		char	lastsaved[30+1];
}T_t_doorholidaytime;
int DB_t_doorholidaytime_add(T_t_doorholidaytime *pt_doorholidaytime);
int DB_t_doorholidaytime_read_by_holidayid_and_holidaydate(int v_holidayid,char *v_holidaydate,T_t_doorholidaytime *pt_doorholidaytime);
int DB_t_doorholidaytime_del_by_holidayid(int v_holidayid);
int DB_t_doorholidaytime_update_by_holidayid_and_holidaydate(int v_holidayid,char *v_holidaydate,T_t_doorholidaytime *pt_doorholidaytime);
int DB_t_doorholidaytime_open_select_by_c0_and_holidayid(int v_holidayid);
int DB_t_doorholidaytime_fetch_select_by_c0(T_t_doorholidaytime *pt_doorholidaytime);
int DB_t_doorholidaytime_close_select_by_c0();
#endif
