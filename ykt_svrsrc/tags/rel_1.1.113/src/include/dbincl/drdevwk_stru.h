#ifndef  __T_drdevwk_H_
#define  __T_drdevwk_H_
typedef struct 
{
		int	major_dev_id;
		int	minor_dev_id;
		int	week_id;
		char	down_date[14+1];
		char	update_date[14+1];
		int	seqno;
		int	ref_cnt;
		int	flag;
}T_t_door_dev_week_tbl;
int DB_t_door_dev_week_tbl_add(T_t_door_dev_week_tbl *pt_door_dev_week_tbl);
int DB_t_door_dev_week_tbl_read_by_major_dev_id_and_minor_dev_id_and_week_id(int v_major_dev_id,int v_minor_dev_id,int v_week_id,T_t_door_dev_week_tbl *pt_door_dev_week_tbl);
int DB_t_door_dev_week_tbl_del_by_major_dev_id_and_minor_dev_id_and_week_id(int v_major_dev_id,int v_minor_dev_id,int v_week_id);
int DB_t_door_dev_week_tbl_update_by_major_dev_id_and_minor_dev_id_and_week_id(int v_major_dev_id,int v_minor_dev_id,int v_week_id,T_t_door_dev_week_tbl *pt_door_dev_week_tbl);
int DB_t_door_dev_week_tbl_open_select_by_c0_and_major_dev_id_and_minor_dev_id(int v_major_dev_id,int v_minor_dev_id);
int DB_t_door_dev_week_tbl_fetch_select_by_c0(T_t_door_dev_week_tbl *pt_door_dev_week_tbl);
int DB_t_door_dev_week_tbl_close_select_by_c0();
#endif
