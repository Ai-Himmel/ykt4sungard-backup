#ifndef  __T_rptfile_H_
#define  __T_rptfile_H_
typedef struct 
{
		char	bala_date[8+1];
		int	flag;
		int	serial_no;
		int	status;
}T_t_tif_report_file;
int DB_t_tif_report_file_add(T_t_tif_report_file *pt_tif_report_file);
int DB_t_tif_report_file_read_lock_by_cur_and_bala_date_and_flag(char *v_bala_date,int v_flag,T_t_tif_report_file *pt_tif_report_file);
int DB_t_tif_report_file_update_lock_by_cur(T_t_tif_report_file *pt_tif_report_file);
int DB_t_tif_report_file_free_lock_by_cur();
#endif
