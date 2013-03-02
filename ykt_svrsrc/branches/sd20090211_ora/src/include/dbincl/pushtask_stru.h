#ifndef  __T_pushtask_H_
#define  __T_pushtask_H_
typedef struct 
{
		int	task_id;
		int	task_seq;
		int	function_id;
		int	func_group;
		int	sys_id;
		int	device_id;
		char	add_time[14+1];
		char	begin_time[12+1];
		char	invalid_time[14+1];
		char	exec_time[24+1];
		int	exec_cnt;
		int	max_exec;
		int	next_interval;
		int	status;
		char	flag[10+1];
		int	send_type;
		int	route_id;
		char	content_str[1000+1];
		char	ret_code[20+1];
		char	ret_msg[500+1];
}T_t_tif_push_task;
int DB_t_tif_push_task_add(T_t_tif_push_task *pt_tif_push_task);
int DB_t_tif_push_task_read_by_task_id(int v_task_id,T_t_tif_push_task *pt_tif_push_task);
int DB_t_tif_push_task_update_by_task_id(int v_task_id,T_t_tif_push_task *pt_tif_push_task);
int DB_t_tif_push_task_del_by_task_id(int v_task_id);
#endif
