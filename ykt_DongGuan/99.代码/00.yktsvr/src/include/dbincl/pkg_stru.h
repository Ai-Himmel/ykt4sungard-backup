#ifndef  __T_pkg_H_
#define  __T_pkg_H_
typedef struct 
{
		int	pkgid;
		int	unitno;
		char	pkgfilename[240+1];
		char	pkgno[30+1];
		int	citycode;
		int	recvdate;
		int	recvtime;
		int	filenum;
		int	processdate;
		int	processtime;
		char	status[1+1];
		int	errcode;
		char	remark[240+1];
		int	feedback;
}T_t_pkg;
int DB_t_pkg_add(T_t_pkg *pt_pkg);
int DB_t_pkg_read_by_unitno_and_pkgfilename(int v_unitno,const char *v_pkgfilename,T_t_pkg *pt_pkg);
int DB_t_pkg_read_by_pkgid(int v_pkgid,T_t_pkg *pt_pkg);
int DB_t_pkg_update_by_pkgid(int v_pkgid,T_t_pkg *pt_pkg);
int DB_t_pkg_del_by_pkgid(int v_pkgid);
int DB_t_pkg_read_lock_by_c0_and_pkgid(int v_pkgid,T_t_pkg *pt_pkg);
int DB_t_pkg_update_lock_by_c0(T_t_pkg *pt_pkg);
int DB_t_pkg_del_lock_by_c0();
int DB_t_pkg_free_lock_by_c0();
int DB_t_pkg_read_by_pkgno(const char *v_pkgno,T_t_pkg *pt_pkg);
int DB_t_pkg_read_lock_by_c1_and_pkgno(const char *v_pkgno,T_t_pkg *pt_pkg);
int DB_t_pkg_update_lock_by_c1(T_t_pkg *pt_pkg);
int DB_t_pkg_del_lock_by_c1();
int DB_t_pkg_free_lock_by_c1();
#endif
