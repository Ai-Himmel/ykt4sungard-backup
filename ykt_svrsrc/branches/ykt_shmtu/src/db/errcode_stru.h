#ifndef  __T_errcode_H_
#define  __T_errcode_H_
typedef struct 
{
		int	ecode;
		char	emsg[100+1];
}T_t_pif_errcode;
int DB_t_pif_errcode_add(T_t_pif_errcode *pt_pif_errcode);
int DB_t_pif_errcode_read_by_ecode(int v_ecode,T_t_pif_errcode *pt_pif_errcode);
#endif
