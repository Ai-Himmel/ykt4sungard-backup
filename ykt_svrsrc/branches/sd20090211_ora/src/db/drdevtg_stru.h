#ifndef  __T_drdevtg_H_
#define  __T_drdevtg_H_
typedef struct 
{
		int	major_dev_id;
		int	minor_dev_id;
		int	timegrp_id;
		int	seqno;
		int	flag;
		char	update_time[14+1];
		char	download_time[14+1];
		int	ref_cnt;
}T_t_door_dev_time_group_tbl;
int DB_t_door_dev_time_group_tbl_add(T_t_door_dev_time_group_tbl *pt_door_dev_time_group_tbl);
int DB_t_door_dev_time_group_tbl_read_by_major_dev_id_and_minor_dev_id_and_timegrp_id(int v_major_dev_id,int v_minor_dev_id,int v_timegrp_id,T_t_door_dev_time_group_tbl *pt_door_dev_time_group_tbl);
int DB_t_door_dev_time_group_tbl_update_by_major_dev_id_and_minor_dev_id_and_timegrp_id(int v_major_dev_id,int v_minor_dev_id,int v_timegrp_id,T_t_door_dev_time_group_tbl *pt_door_dev_time_group_tbl);
int DB_t_door_dev_time_group_tbl_del_by_major_dev_id_and_minor_dev_id_and_timegrp_id(int v_major_dev_id,int v_minor_dev_id,int v_timegrp_id);
int DB_t_door_dev_time_group_tbl_open_select_by_c0_and_major_dev_id_and_minor_dev_id(int v_major_dev_id,int v_minor_dev_id);
int DB_t_door_dev_time_group_tbl_fetch_select_by_c0(T_t_door_dev_time_group_tbl *pt_door_dev_time_group_tbl);
int DB_t_door_dev_time_group_tbl_close_select_by_c0();
#endif
