#ifndef  __T_drhday_H_
#define  __T_drhday_H_
typedef struct 
{
		int	holidayid;
		char	holidayname[60+1];
		int	daycnt;
		int	adddelflag;
		int	downstatus;
		char	updatetime[30+1];
}T_t_doorholiday;
int DB_t_doorholiday_add(T_t_doorholiday *pt_doorholiday);
int DB_t_doorholiday_read_by_holidayid(int v_holidayid,T_t_doorholiday *pt_doorholiday);
int DB_t_doorholiday_update_by_holidayid(int v_holidayid,T_t_doorholiday *pt_doorholiday);
int DB_t_doorholiday_del_by_holidayid(int v_holidayid);
int DB_t_doorholiday_read_lock_by_c0_and_holidayid(int v_holidayid,T_t_doorholiday *pt_doorholiday);
int DB_t_doorholiday_update_lock_by_c0(T_t_doorholiday *pt_doorholiday);
int DB_t_doorholiday_free_lock_by_c0();
#endif
