#ifndef  __T_operpos_H_
#define  __T_operpos_H_
typedef struct 
{
		char	oper_code[30+1];
		char	device_id[30+1];
		char	open_oper[30+1];
		char	last_saved[30+1];
}T_t_deposit_operpos;
int DB_t_deposit_operpos_add(T_t_deposit_operpos *pt_deposit_operpos);
int DB_t_deposit_operpos_read_by_oper_code_and_device_id(char *v_oper_code,char *v_device_id,T_t_deposit_operpos *pt_deposit_operpos);
int DB_t_deposit_operpos_del_by_oper_code_and_device_id(char *v_oper_code,char *v_device_id);
int DB_t_deposit_operpos_del_by_oper_code(char *v_oper_code);
#endif
