#ifndef  __T_sbparams_H_
#define  __T_sbparams_H_
typedef struct 
{
		int	sysid;
		int	heartbeat_intval;
		int	heartbeat_limit;
		int	heartbeat_funcno;
		int	drpt_no;
		int	qrytask_intval;
		int	exec_timeout;
		char	devtype[20+1];
		char	work_mode[1+1];
		int	collect_intval;
		int	devprofile_funcno;
		int	task_limit;
		int	resp_func;
}T_t_subsysparams;
int DB_t_subsysparams_add(T_t_subsysparams *pt_subsysparams);
int DB_t_subsysparams_read_by_sysid(int v_sysid,T_t_subsysparams *pt_subsysparams);
#endif
