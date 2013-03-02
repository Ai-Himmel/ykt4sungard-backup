#ifndef  __T_dpsoper_H_
#define  __T_dpsoper_H_
typedef struct 
{
		char	opercode[8+1];
		char	status[1+1];
		char	devlimitflag[1+1];
		char	shopoperflag[1+1];
		char	opendate[8+1];
		char	closedate[8+1];
		double	maxdepositamt;
		int	depositcnt;
		double	depositamt;
		char	lasttransdate[8+1];
		char	lastdevphyid[30+1];
		int	lastdevseqno;
		char	lastsaved[30+1];
}T_t_dpsoper;
int DB_t_dpsoper_add(T_t_dpsoper *pt_dpsoper);
int DB_t_dpsoper_read_by_opercode(char *v_opercode,T_t_dpsoper *pt_dpsoper);
int DB_t_dpsoper_update_by_opercode(char *v_opercode,T_t_dpsoper *pt_dpsoper);
int DB_t_dpsoper_del_by_opercode(char *v_opercode);
int DB_t_dpsoper_read_lock_by_c0_and_opercode(char *v_opercode,T_t_dpsoper *pt_dpsoper);
int DB_t_dpsoper_update_lock_by_c0(T_t_dpsoper *pt_dpsoper);
int DB_t_dpsoper_free_lock_by_c0();
#endif
