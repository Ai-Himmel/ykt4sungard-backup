#ifndef  __T_spefee_H_
#define  __T_spefee_H_
typedef struct 
{
		char	deptcode[10+1];
		int	custtype;
		int	feetype;
}T_t_spefee;
int DB_t_spefee_read_by_deptcode_and_custtype(char *v_deptcode,int v_custtype,T_t_spefee *pt_spefee);
#endif
