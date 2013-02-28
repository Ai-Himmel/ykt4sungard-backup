#ifndef  __T_bookset_H_
#define  __T_bookset_H_
typedef struct 
{
		int	booksetno;
		char	booksetname[60+1];
		char	deptname[60+1];
		char	deptshortname[60+1];
		int	supervisor;
		int	voucherclass;
		int	periodyear;
		int	periodmonth;
		int	enabledate;
}T_t_bookset;
int DB_t_bookset_add(T_t_bookset *pt_bookset);
int DB_t_bookset_read_by_booksetno(int v_booksetno,T_t_bookset *pt_bookset);
int DB_t_bookset_update_by_booksetno(int v_booksetno,T_t_bookset *pt_bookset);
int DB_t_bookset_del_by_booksetno(int v_booksetno);
int DB_t_bookset_read_lock_by_c0_and_booksetno(int v_booksetno,T_t_bookset *pt_bookset);
int DB_t_bookset_update_lock_by_c0(T_t_bookset *pt_bookset);
int DB_t_bookset_free_lock_by_c0();
#endif
