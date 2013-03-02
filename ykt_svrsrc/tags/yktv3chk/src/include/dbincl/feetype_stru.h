#ifndef  __T_feetype_H_
#define  __T_feetype_H_
typedef struct 
{
		int	feetype;
		char	feename[60+1];
		char	boardfeeflag[1+1];
		char	useflag[1+1];
		char	remark[240+1];
}T_t_feetype;
int DB_t_feetype_add(T_t_feetype *pt_feetype);
int DB_t_feetype_read_by_feetype(int v_feetype,T_t_feetype *pt_feetype);
int DB_t_feetype_update_by_feetype(int v_feetype,T_t_feetype *pt_feetype);
int DB_t_feetype_del_by_feetype(int v_feetype);
int DB_t_feetype_read_lock_by_c0_and_feetype(int v_feetype,T_t_feetype *pt_feetype);
int DB_t_feetype_update_lock_by_c0(T_t_feetype *pt_feetype);
int DB_t_feetype_free_lock_by_c0();
#endif
