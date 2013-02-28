#ifndef  __T_pkgfile_H_
#define  __T_pkgfile_H_
typedef struct 
{
		int	fileid;
		char	filename[240+1];
		int	pkgid;
		int	seqno;
		char	merchid[20+1];
		int	totalnum;
		int	totalamt;
		int	processdate;
		int	processtime;
		char	status[1+1];
		int	errcode;
		char	remark[240+1];
}T_t_pkgfile;
int DB_t_pkgfile_add(T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_read_by_fileid(int v_fileid,T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_update_by_fileid(int v_fileid,T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_del_by_fileid(int v_fileid);
int DB_t_pkgfile_read_lock_by_c0_and_fileid(int v_fileid,T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_update_lock_by_c0(T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_del_lock_by_c0();
int DB_t_pkgfile_free_lock_by_c0();
int DB_t_pkgfile_read_by_pkgid_and_seqno(int v_pkgid,int v_seqno,T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_read_lock_by_c1_and_pkgid_and_seqno(int v_pkgid,int v_seqno,T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_update_lock_by_c1(T_t_pkgfile *pt_pkgfile);
int DB_t_pkgfile_del_lock_by_c1();
int DB_t_pkgfile_free_lock_by_c1();
#endif
