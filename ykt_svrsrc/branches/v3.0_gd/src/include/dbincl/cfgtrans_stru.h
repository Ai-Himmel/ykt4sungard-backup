#ifndef  __T_cfgtrans_H_
#define  __T_cfgtrans_H_
typedef struct 
{
		int	feetype;
		int	transcode;
		int	transtype;
		int	ratetype;
		double	rateamt;
		char	remark[240+1];
}T_t_cfgtrans;
int DB_t_cfgtrans_add(T_t_cfgtrans *pt_cfgtrans);
int DB_t_cfgtrans_read_by_feetype_and_transcode_and_transtype(int v_feetype,int v_transcode,int v_transtype,T_t_cfgtrans *pt_cfgtrans);
int DB_t_cfgtrans_update_by_feetype_and_transcode_and_transtype(int v_feetype,int v_transcode,int v_transtype,T_t_cfgtrans *pt_cfgtrans);
int DB_t_cfgtrans_del_by_feetype_and_transcode_and_transtype(int v_feetype,int v_transcode,int v_transtype);
int DB_t_cfgtrans_read_lock_by_c0_and_feetype_and_transcode_and_transtype(int v_feetype,int v_transcode,int v_transtype,T_t_cfgtrans *pt_cfgtrans);
int DB_t_cfgtrans_update_lock_by_c0(T_t_cfgtrans *pt_cfgtrans);
int DB_t_cfgtrans_free_lock_by_c0();
#endif
