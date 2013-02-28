#ifndef  __T_dpsoperpos_H_
#define  __T_dpsoperpos_H_
typedef struct 
{
		char	opercode[8+1];
		int	deviceid;
		char	openoper[8+1];
		char	lastsaved[30+1];
}T_t_dpsoperpos;
int DB_t_dpsoperpos_add(T_t_dpsoperpos *pt_dpsoperpos);
int DB_t_dpsoperpos_read_by_opercode_and_deviceid(const char *v_opercode,int v_deviceid,T_t_dpsoperpos *pt_dpsoperpos);
int DB_t_dpsoperpos_update_by_opercode_and_deviceid(char *v_opercode,int v_deviceid,T_t_dpsoperpos *pt_dpsoperpos);
int DB_t_dpsoperpos_del_by_opercode_and_deviceid(const char *v_opercode,int v_deviceid);
int DB_t_dpsoperpos_del_by_opercode(const char *v_opercode);
int DB_t_dpsoperpos_read_lock_by_c0_and_opercode_and_deviceid(const char *v_opercode,int v_deviceid,T_t_dpsoperpos *pt_dpsoperpos);
int DB_t_dpsoperpos_update_lock_by_c0(T_t_dpsoperpos *pt_dpsoperpos);
int DB_t_dpsoperpos_free_lock_by_c0();
#endif
