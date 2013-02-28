#ifndef  __T_dept_H_
#define  __T_dept_H_
typedef struct 
{
		char	deptcode[30+1];
		char	areacode[2+1];
		char	deptname[480+1];
		char	deptename[240+1];
		char	deptfullname[1000+1];
		char	fdeptcode[30+1];
		int	deptlevel;
		char	olddeptcode[30+1];
		char	useflag[1+1];
		char	lastsaved[30+1];
}T_t_dept;
int DB_t_dept_add(T_t_dept *pt_dept);
int DB_t_dept_read_by_deptcode(const char *v_deptcode,T_t_dept *pt_dept);
int DB_t_dept_update_by_deptcode(char *v_deptcode,T_t_dept *pt_dept);
int DB_t_dept_del_by_deptcode(const char *v_deptcode);
int DB_t_dept_read_lock_by_c0_and_deptcode(const char *v_deptcode,T_t_dept *pt_dept);
int DB_t_dept_update_lock_by_c0(T_t_dept *pt_dept);
int DB_t_dept_free_lock_by_c0();
#endif
