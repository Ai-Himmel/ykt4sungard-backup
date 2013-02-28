#ifndef  __T_branch_H_
#define  __T_branch_H_
typedef struct 
{
		int	branchid;
		char	areacode[3+1];
		char	towncode[20+1];
		char	branchno[20+1];
		char	branchname[60+1];
		char	branchtype[1+1];
		int	merchid;
		char	contactman[90+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	fax[30+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	status[1+1];
		int	opendate;
		int	closedate;
}T_t_branch;
int DB_t_branch_add(T_t_branch *pt_branch);
int DB_t_branch_read_by_branchid(int v_branchid,T_t_branch *pt_branch);
int DB_t_branch_update_by_branchid(int v_branchid,T_t_branch *pt_branch);
int DB_t_branch_del_by_branchid(int v_branchid);
int DB_t_branch_read_lock_by_c0_and_branchid(int v_branchid,T_t_branch *pt_branch);
int DB_t_branch_update_lock_by_c0(T_t_branch *pt_branch);
int DB_t_branch_del_lock_by_c0();
int DB_t_branch_free_lock_by_c0();
int DB_t_branch_read_lock_by_c1_and_branchno(const char *v_branchno,T_t_branch *pt_branch);
int DB_t_branch_update_lock_by_c1(T_t_branch *pt_branch);
int DB_t_branch_del_lock_by_c1();
int DB_t_branch_free_lock_by_c1();
#endif
