#ifndef  __T_operator_H_
#define  __T_operator_H_
typedef struct 
{
		char	opercode[8+1];
		char	opertype[1+1];
		int	branchno;
		int	cardno;
		char	opername[60+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	email[60+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	operpwd[32+1];
		char	status[1+1];
		char	lasttransdate[8+1];
		char	menuset[800+1];
		char	funcset[600+1];
		char	sitelimit[1+1];
		char	loginflag[1+1];
		int	loginsiteno;
		char	logintime[30+1];
		char	logouttime[30+1];
		int	failnumber;
		char	opendate[8+1];
		char	closedate[8+1];
}T_t_operator;
int DB_t_operator_add(T_t_operator *pt_operator);
int DB_t_operator_read_by_opercode(char *v_opercode,T_t_operator *pt_operator);
int DB_t_operator_update_by_opercode(char *v_opercode,T_t_operator *pt_operator);
int DB_t_operator_del_by_opercode(char *v_opercode);
int DB_t_operator_read_lock_by_c0_and_opercode(char *v_opercode,T_t_operator *pt_operator);
int DB_t_operator_update_lock_by_c0(T_t_operator *pt_operator);
int DB_t_operator_free_lock_by_c0();
#endif
