#ifndef  __T_transcode_H_
#define  __T_transcode_H_
typedef struct 
{
		int	transcode;
		char	transname[60+1];
		int	logflag;
		int	limitflag;
		int	feeflag;
		int	transflag;
		int	disableflag;
}T_t_transcode;
int DB_t_transcode_add(T_t_transcode *pt_transcode);
int DB_t_transcode_read_by_transcode(int v_transcode,T_t_transcode *pt_transcode);
int DB_t_transcode_update_by_transcode(int v_transcode,T_t_transcode *pt_transcode);
int DB_t_transcode_del_by_transcode(int v_transcode);
int DB_t_transcode_read_lock_by_c0_and_transcode(int v_transcode,T_t_transcode *pt_transcode);
int DB_t_transcode_update_lock_by_c0(T_t_transcode *pt_transcode);
int DB_t_transcode_free_lock_by_c0();
#endif
