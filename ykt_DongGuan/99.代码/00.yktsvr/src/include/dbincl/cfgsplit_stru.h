#ifndef  __T_cfgsplit_H_
#define  __T_cfgsplit_H_
typedef struct 
{
		int	transcode;
		int	transtype;
		unsigned int	drsubjno;
		unsigned int	crsubjno;
		int	drflag;
		int	crflag;
		char	drdesc[60+1];
		char	crdesc[60+1];
}T_t_cfgsplit;
int DB_t_cfgsplit_add(T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_read_by_transcode(int v_transcode,T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_update_by_transcode(int v_transcode,T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_del_by_transcode(int v_transcode);
int DB_t_cfgsplit_read_lock_by_c0_and_transcode(int v_transcode,T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_update_lock_by_c0(T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_del_lock_by_c0();
int DB_t_cfgsplit_free_lock_by_c0();
#endif
