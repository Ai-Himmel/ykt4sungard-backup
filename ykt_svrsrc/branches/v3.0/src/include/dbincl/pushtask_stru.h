#ifndef  __T_pushtask_H_
#define  __T_pushtask_H_
typedef struct 
{
		int	taskid;
		int	taskseq;
		int	funcno;
		int	funcgroup;
		int	sysid;
		int	deviceid;
		char	addtime[30+1];
		char	begintime[30+1];
		char	invalidtime[30+1];
		char	exectime[30+1];
		int	execcnt;
		int	maxexec;
		int	nextinterval;
		int	status;
		char	flag[10+1];
		int	sendtype;
		int	routeid;
		char	contentstr[1000+1];
		char	retcode[20+1];
		char	retmsg[500+1];
}T_t_pushtask;
int DB_t_pushtask_add(T_t_pushtask *pt_pushtask);
int DB_t_pushtask_read_by_taskid(int v_taskid,T_t_pushtask *pt_pushtask);
int DB_t_pushtask_update_by_taskid(int v_taskid,T_t_pushtask *pt_pushtask);
int DB_t_pushtask_del_by_taskid(int v_taskid);
#endif
