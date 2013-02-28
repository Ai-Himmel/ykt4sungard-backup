#ifndef  __T_modifyinfo_H_
#define  __T_modifyinfo_H_
typedef struct 
{
		int	custid;
		char	stuempno[20+1];
		char	enrollno[20+1];
		char	modifydate[8+1];
		char	modifytime[6+1];
		char	opercode[8+1];
}T_t_modifyinfo;
int DB_t_modifyinfo_add(T_t_modifyinfo *pt_modifyinfo);
int DB_t_modifyinfo_read_by_custid_and_stuempno(int v_custid,const char *v_stuempno,T_t_modifyinfo *pt_modifyinfo);
#endif
