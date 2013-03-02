#ifndef  __T_operright_H_
#define  __T_operright_H_
typedef struct 
{
		char	device_id[8+1];
		char	oper_no[10+1];
}T_t_door_oper_right;
int DB_t_door_oper_right_add(T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_read_by_oper_no_and_device_id(char *v_oper_no,char *v_device_id,T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_del_by_oper_no(char *v_oper_no);
int DB_t_door_oper_right_del_by_device_id(char *v_device_id);
int DB_t_door_oper_right_del_by_oper_no_and_device_id(char *v_oper_no,char *v_device_id);
int DB_t_door_oper_right_open_select_by_c0_and_oper_no(char *v_oper_no);
int DB_t_door_oper_right_fetch_select_by_c0(T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_close_select_by_c0();
int DB_t_door_oper_right_open_select_by_c1_and_device_id(char *v_device_id);
int DB_t_door_oper_right_fetch_select_by_c1(T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_close_select_by_c1();
#endif
