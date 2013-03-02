#ifndef  __T_doorholiday_H_
#define  __T_doorholiday_H_
typedef struct 
{
		int	holidayid;
		char	holidayname[150+1];
		int	flag;
		char	lastsaved[30+1];
		int	daycnt;
}T_t_doorholiday;
int DB_t_doorholiday_add(T_t_doorholiday *pt_doorholiday);
int DB_t_doorholiday_read_by_holidayid(int v_holidayid,T_t_doorholiday *pt_doorholiday);
int DB_t_doorholiday_update_by_holidayid(int v_holidayid,T_t_doorholiday *pt_doorholiday);
#endif
