#ifndef  __T_drdevtmsc_H_
#define  __T_drdevtmsc_H_
typedef struct 
{
		int	major_dev_id;
		int	minor_dev_id;
		int	sect_id;
		int	seqno;
		char	update_time[14+1];
		char	download_time[14+1];
		int	ref_cnt;
}T_t_door_dev_timesect_tbl;
int DB_t_door_dev_timesect_tbl_add(T_t_door_dev_timesect_tbl *pt_door_dev_timesect_tbl);
int DB_t_door_dev_timesect_tbl_read_by_major_dev_id_and_minor_dev_id_and_sect_id(int v_major_dev_id,int v_minor_dev_id,int v_sect_id,T_t_door_dev_timesect_tbl *pt_door_dev_timesect_tbl);
int DB_t_door_dev_timesect_tbl_update_by_major_dev_id_and_minor_dev_id_and_sect_id(int v_major_dev_id,int v_minor_dev_id,int v_sect_id,T_t_door_dev_timesect_tbl *pt_door_dev_timesect_tbl);
int DB_t_door_dev_timesect_tbl_del_by_major_dev_id_and_minor_dev_id_and_sect_id(int v_major_dev_id,int v_minor_dev_id,int v_sect_id);
int DB_t_door_dev_timesect_tbl_open_select_by_c0_and_major_dev_id_and_minor_dev_id(int v_major_dev_id,int v_minor_dev_id);
int DB_t_door_dev_timesect_tbl_fetch_select_by_c0(T_t_door_dev_timesect_tbl *pt_door_dev_timesect_tbl);
int DB_t_door_dev_timesect_tbl_close_select_by_c0();
#endif
