#ifndef  __T_operright_H_
#define  __T_operright_H_
typedef struct 
{
		int	deviceid;
		char	opercode[10+1];
}T_t_door_oper_right;
int DB_t_door_oper_right_add(T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_read_by_opercode_and_deviceid(char *v_opercode,int v_deviceid,T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_del_by_opercode(char *v_opercode);
int DB_t_door_oper_right_del_by_deviceid(int v_deviceid);
int DB_t_door_oper_right_del_by_opercode_and_deviceid(char *v_opercode,int v_deviceid);
int DB_t_door_oper_right_open_select_by_c0_and_opercode(char *v_opercode);
int DB_t_door_oper_right_fetch_select_by_c0(T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_close_select_by_c0();
int DB_t_door_oper_right_open_select_by_c1_and_deviceid(int v_deviceid);
int DB_t_door_oper_right_fetch_select_by_c1(T_t_door_oper_right *pt_door_oper_right);
int DB_t_door_oper_right_close_select_by_c1();
#endif
