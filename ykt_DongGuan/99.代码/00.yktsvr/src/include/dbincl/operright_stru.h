#ifndef  __T_operright_H_
#define  __T_operright_H_
typedef struct 
{
		int	deviceid;
		char	opercode[10+1];
}T_t_dooroperright;
int DB_t_dooroperright_add(T_t_dooroperright *pt_dooroperright);
int DB_t_dooroperright_read_by_opercode_and_deviceid(const char *v_opercode,int v_deviceid,T_t_dooroperright *pt_dooroperright);
int DB_t_dooroperright_del_by_opercode(const char *v_opercode);
int DB_t_dooroperright_del_by_deviceid(int v_deviceid);
int DB_t_dooroperright_del_by_opercode_and_deviceid(const char *v_opercode,int v_deviceid);
int DB_t_dooroperright_open_select_by_c0_and_opercode(const char *v_opercode);
int DB_t_dooroperright_fetch_select_by_c0(T_t_dooroperright *pt_dooroperright);
int DB_t_dooroperright_close_select_by_c0();
int DB_t_dooroperright_open_select_by_c1_and_deviceid(int v_deviceid);
int DB_t_dooroperright_fetch_select_by_c1(T_t_dooroperright *pt_dooroperright);
int DB_t_dooroperright_close_select_by_c1();
#endif
