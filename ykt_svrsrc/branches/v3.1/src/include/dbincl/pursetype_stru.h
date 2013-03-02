#ifndef  __T_pursetype_H_
#define  __T_pursetype_H_
typedef struct 
{
		int	pursetype;
		char	pursetypename[60+1];
		double	pursemaxbal;
		int	onlineflag;
		int	shopid;
		int	refundflag;
		int	primaryflag;
		int	enableflag;
		char	remark[240+1];
		char	lastsaved[30+1];
}T_t_pursetype;
int DB_t_pursetype_add(T_t_pursetype *pt_pursetype);
int DB_t_pursetype_read_by_pursetype(int v_pursetype,T_t_pursetype *pt_pursetype);
int DB_t_pursetype_update_by_pursetype(int v_pursetype,T_t_pursetype *pt_pursetype);
int DB_t_pursetype_del_by_pursetype(int v_pursetype);
int DB_t_pursetype_read_lock_by_c0_and_pursetype(int v_pursetype,T_t_pursetype *pt_pursetype);
int DB_t_pursetype_update_lock_by_c0(T_t_pursetype *pt_pursetype);
int DB_t_pursetype_free_lock_by_c0();
#endif
