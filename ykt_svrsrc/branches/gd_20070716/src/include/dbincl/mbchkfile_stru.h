#ifndef  __T_mbchkfile_H_
#define  __T_mbchkfile_H_
typedef struct 
{
		char	tx_date[8+1];
		char	check_flag[1+1];
}T_t_mobile_chkfile;
int DB_t_mobile_chkfile_add(T_t_mobile_chkfile *pt_mobile_chkfile);
int DB_t_mobile_chkfile_read_lock_by_c0_and_tx_date(char *v_tx_date,T_t_mobile_chkfile *pt_mobile_chkfile);
int DB_t_mobile_chkfile_update_lock_by_c0(T_t_mobile_chkfile *pt_mobile_chkfile);
int DB_t_mobile_chkfile_free_lock_c0();
#endif
