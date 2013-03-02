#ifndef  __T_drgrprht_H_
#define  __T_drgrprht_H_
typedef struct 
{
		int	groupid;
		char	opercode[8+1];
}T_t_doorgrpoperright;
int DB_t_doorgrpoperright_add(T_t_doorgrpoperright *pt_doorgrpoperright);
int DB_t_doorgrpoperright_read_by_groupid_and_opercode(int v_groupid,char *v_opercode,T_t_doorgrpoperright *pt_doorgrpoperright);
int DB_t_doorgrpoperright_del_by_groupid_and_opercode(int v_groupid,char *v_opercode);
#endif
