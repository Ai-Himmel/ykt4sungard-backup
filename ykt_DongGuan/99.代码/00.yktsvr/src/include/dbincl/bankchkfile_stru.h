#ifndef  __T_bankchkfile_H_
#define  __T_bankchkfile_H_
typedef struct 
{
		int	bankid;
		int	bankdate;
		char	bankchkfile[240+1];
		char	localchkfile[240+1];
		char	localcvtfile[240+1];
		char	filesource[1+1];
		char	status[1+1];
		char	resolved[1+1];
		char	remark[240+1];
		int	bankcnt;
		double	bankamt;
		int	localcnt;
		double	localamt;
		char	crttime[14+1];
		char	updtime[14+1];
}T_t_bankchkfile;
int DB_t_bankchkfile_add(T_t_bankchkfile *pt_bankchkfile);
int DB_t_bankchkfile_read_by_bankid_and_bankdate(int v_bankid,int v_bankdate,T_t_bankchkfile *pt_bankchkfile);
int DB_t_bankchkfile_update_by_bankid_and_bankdate(int v_bankid,int v_bankdate,T_t_bankchkfile *pt_bankchkfile);
int DB_t_bankchkfile_del_by_bankid_and_bankdate(int v_bankid,int v_bankdate);
int DB_t_bankchkfile_read_lock_by_c0_and_bankid_and_bankdate(int v_bankid,int v_bankdate,T_t_bankchkfile *pt_bankchkfile);
int DB_t_bankchkfile_update_lock_by_c0(T_t_bankchkfile *pt_bankchkfile);
int DB_t_bankchkfile_del_lock_by_c0();
int DB_t_bankchkfile_free_lock_by_c0();
#endif
