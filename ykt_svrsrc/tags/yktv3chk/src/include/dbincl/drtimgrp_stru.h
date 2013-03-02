#ifndef  __T_drtimgrp_H_
#define  __T_drtimgrp_H_
typedef struct 
{
		int	timesectgrpid;
		char	timesectgrpname[60+1];
		int	timesectid1;
		int	timesectid2;
		int	timesectid3;
		int	timesectid4;
		int	timesectid5;
		int	timesectid6;
		int	timesectid7;
		int	timesectid8;
		int	flag;
		char	lastsaved[30+1];
}T_t_doortimesectgrp;
int DB_t_doortimesectgrp_add(T_t_doortimesectgrp *pt_doortimesectgrp);
int DB_t_doortimesectgrp_read_by_timesectgrpid(int v_timesectgrpid,T_t_doortimesectgrp *pt_doortimesectgrp);
int DB_t_doortimesectgrp_update_by_timesectgrpid(int v_timesectgrpid,T_t_doortimesectgrp *pt_doortimesectgrp);
int DB_t_doortimesectgrp_del_by_timesectgrpid(int v_timesectgrpid);
#endif
