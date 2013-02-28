#ifndef  __T_authcard_H_
#define  __T_authcard_H_
typedef struct 
{
		int	cardno;
		char	opercode[8+1];
		char	showcardno[10+1];
		char	cardphyid[16+1];
		int	privilege;
		char	expiredate[8+1];
		char	status[1+1];
		char	lossflag[1+1];
		char	lossdate[8+1];
		char	opendate[8+1];
		char	closedate[8+1];
}T_t_authcard;
int DB_t_authcard_add(T_t_authcard *pt_authcard);
int DB_t_authcard_read_by_cardno(int v_cardno,T_t_authcard *pt_authcard);
int DB_t_authcard_read_by_opercode_and_status(const char *v_opercode,const char *v_status,T_t_authcard *pt_authcard);
int DB_t_authcard_read_by_cardphyid_and_status(const char *v_cardphyid,const char *v_status,T_t_authcard *pt_authcard);
int DB_t_authcard_update_by_cardno(int v_cardno,T_t_authcard *pt_authcard);
int DB_t_authcard_del_by_cardno(int v_cardno);
int DB_t_authcard_read_lock_by_c0_and_cardno(int v_cardno,T_t_authcard *pt_authcard);
int DB_t_authcard_update_lock_by_c0(T_t_authcard *pt_authcard);
int DB_t_authcard_free_lock_by_c0();
#endif
