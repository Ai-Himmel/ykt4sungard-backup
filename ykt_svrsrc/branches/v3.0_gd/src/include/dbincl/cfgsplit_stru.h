#ifndef  __T_cfgsplit_H_
#define  __T_cfgsplit_H_
typedef struct 
{
		int	transtype;
		int	fundtype;
		int	offlineflag;
		int	usecardflag;
		int	calccardbal;
		char	draccflag[1+1];
		char	drsubjno[20+1];
		char	draccno[20+1];
		char	craccflag[1+1];
		char	crsubjno[20+1];
		char	craccno[20+1];
		char	summary[60+1];
}T_t_cfgsplit;
int DB_t_cfgsplit_add(T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_read_by_transtype_and_fundtype(int v_transtype,int v_fundtype,T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_update_by_transtype_and_fundtype(int v_transtype,int v_fundtype,T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_del_by_transtype_and_fundtype(int v_transtype,int v_fundtype);
int DB_t_cfgsplit_read_lock_by_c0_and_transtype_and_fundtype(int v_transtype,int v_fundtype,T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_update_lock_by_c0(T_t_cfgsplit *pt_cfgsplit);
int DB_t_cfgsplit_free_lock_by_c0();
#endif
