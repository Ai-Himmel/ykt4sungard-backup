#ifndef  __T_branch_H_
#define  __T_branch_H_
typedef struct 
{
		int	branchno;
		char	areacode[3+1];
		char	branchname[240+1];
		char	branchtype[1+1];
		char	bankcode[2+1];
		char	bankaccno[30+1];
		char	bankaccname[240+1];
		char	contactman[60+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	fax[30+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	status[1+1];
		char	opendate[8+1];
		char	closedate[8+1];
}T_t_branch;
int DB_t_branch_add(T_t_branch *pt_branch);
int DB_t_branch_read_by_branchno(int v_branchno,T_t_branch *pt_branch);
int DB_t_branch_update_by_branchno(int v_branchno,T_t_branch *pt_branch);
int DB_t_branch_del_by_branchno(int v_branchno);
int DB_t_branch_read_lock_by_c0_and_branchno(int v_branchno,T_t_branch *pt_branch);
int DB_t_branch_update_lock_by_c0(T_t_branch *pt_branch);
int DB_t_branch_free_lock_by_c0();
#endif
