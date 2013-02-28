#ifndef  __T_apply_H_
#define  __T_apply_H_
typedef struct 
{
		int	applyid;
		int	cardno;
		int	oldcardid;
		int	newcardid;
		int	cardstatus;
		int	applydate;
		int	applytype;
		char	applyreason[60+1];
		int	status;
		int	handledate;
		char	updtime[14+1];
		char	remark[60+1];
}T_t_apply;
int DB_t_apply_add(T_t_apply *pt_apply);
int DB_t_apply_read_by_applyid(int v_applyid,T_t_apply *pt_apply);
int DB_t_apply_update_by_applyid(int v_applyid,T_t_apply *pt_apply);
int DB_t_apply_del_by_applyid(int v_applyid);
int DB_t_apply_read_lock_by_c0_and_applyid(int v_applyid,T_t_apply *pt_apply);
int DB_t_apply_update_lock_by_c0(T_t_apply *pt_apply);
int DB_t_apply_del_lock_by_c0();
int DB_t_apply_free_lock_by_c0();
int DB_t_apply_read_lock_by_c1_and_cardno_and_status(int v_cardno,int v_status,T_t_apply *pt_apply);
int DB_t_apply_update_lock_by_c1(T_t_apply *pt_apply);
int DB_t_apply_del_lock_by_c1();
int DB_t_apply_free_lock_by_c1();
#endif
