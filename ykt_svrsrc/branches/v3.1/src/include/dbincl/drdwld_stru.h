#ifndef  __T_drdwld_H_
#define  __T_drdwld_H_
typedef struct 
{
		int	id;
		char	cardverno[12+1];
		int	custid;
		int	ctrlid;
		int	sysid;
		int	cardno;
		char	cardphyid[16+1];
		char	rightbit[240+1];
		int	cardseqno;
		int	weekid;
		int	weekseqno;
		int	holidayid;
		int	holidayseqno;
		char	createtime[30+1];
		char	succtime[30+1];
		int	status;
		int	adddelflag;
		int	doorcount;
}T_t_doordownload;
int DB_t_doordownload_add(T_t_doordownload *pt_doordownload);
int DB_t_doordownload_read_by_id(int v_id,T_t_doordownload *pt_doordownload);
int DB_t_doordownload_read_lock_by_c0_and_id(int v_id,T_t_doordownload *pt_doordownload);
int DB_t_doordownload_update_lock_by_c0(T_t_doordownload *pt_doordownload);
int DB_t_doordownload_free_lock_by_c0();
int DB_t_doordownload_open_select_by_c1_and_ctrlid(int v_ctrlid);
int DB_t_doordownload_fetch_select_by_c1(T_t_doordownload *pt_doordownload);
int DB_t_doordownload_close_select_by_c1();
#endif
