#ifndef  __T_chkdate_H_
#define  __T_chkdate_H_
typedef struct 
{
		int	accchktype;
		char	chkdate[8+1];
		char	accdate[8+1];
		int	chkflag;
		int	chktype;
		char	opercode[8+1];
		int	yktcnt;
		double	yktbala;
		int	thirdcnt;
		double	thirdbala;
		char	remark[240+1];
		char	lastchktime[30+1];
}T_t_cfgchkdate;
int DB_t_cfgchkdate_add(T_t_cfgchkdate *pt_cfgchkdate);
int DB_t_cfgchkdate_read_by_accchktype_and_chkdate(int v_accchktype,char *v_chkdate,T_t_cfgchkdate *pt_cfgchkdate);
int DB_t_cfgchkdate_update_by_accchktype_and_chkdate(int v_accchktype,char *v_chkdate,T_t_cfgchkdate *pt_cfgchkdate);
int DB_t_cfgchkdate_read_lock_by_c0_and_accchktype_and_chkdate(int v_accchktype,char *v_chkdate,T_t_cfgchkdate *pt_cfgchkdate);
int DB_t_cfgchkdate_update_lock_by_c0(T_t_cfgchkdate *pt_cfgchkdate);
int DB_t_cfgchkdate_free_lock_by_c0();
#endif
