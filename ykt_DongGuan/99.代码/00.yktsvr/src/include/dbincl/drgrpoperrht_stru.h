#ifndef  __T_drgrpoperrht_H_
#define  __T_drgrpoperrht_H_
typedef struct 
{
		int	groupid;
		char	opercode[8+1];
		char	updatetime[30+1];
}T_t_doorgrpoperright;
int DB_t_doorgrpoperright_add(T_t_doorgrpoperright *pt_doorgrpoperright);
int DB_t_doorgrpoperright_read_by_groupid_and_opercode(int v_groupid,const char *v_opercode,T_t_doorgrpoperright *pt_doorgrpoperright);
int DB_t_doorgrpoperright_update_by_groupid_and_opercode(int v_groupid,char *v_opercode,T_t_doorgrpoperright *pt_doorgrpoperright);
int DB_t_doorgrpoperright_del_by_groupid_and_opercode(int v_groupid,const char *v_opercode);
int DB_t_doorgrpoperright_read_lock_by_c0_and_groupid_and_opercode(int v_groupid,const char *v_opercode,T_t_doorgrpoperright *pt_doorgrpoperright);
int DB_t_doorgrpoperright_update_lock_by_c0(T_t_doorgrpoperright *pt_doorgrpoperright);
int DB_t_doorgrpoperright_free_lock_by_c0();
#endif
