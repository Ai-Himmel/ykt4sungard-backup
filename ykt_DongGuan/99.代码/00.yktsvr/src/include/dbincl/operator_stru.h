#ifndef  __T_operator_H_
#define  __T_operator_H_
typedef struct 
{
		int	operid;
		int	operseqno;
		char	opercode[8+1];
		int	opertype;
		int	branchid;
		int	cardno;
		char	opername[90+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	email[60+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	operpwd[32+1];
		int	status;
		int	lasttransdate;
		char	menuset[800+1];
		char	funcset[600+1];
		int	rightflag;
		int	sitelimit;
		int	loginflag;
		int	loginsiteno;
		char	logintime[14+1];
		char	logouttime[14+1];
		int	failnumber;
		int	opendate;
		int	closedate;
}T_t_operator;
int DB_t_operator_add(T_t_operator *pt_operator);
int DB_t_operator_read_by_opercode(const char *v_opercode,T_t_operator *pt_operator);
int DB_t_operator_update_by_opercode(char *v_opercode,T_t_operator *pt_operator);
int DB_t_operator_del_by_opercode(const char *v_opercode);
int DB_t_operator_read_lock_by_c0_and_opercode(const char *v_opercode,T_t_operator *pt_operator);
int DB_t_operator_update_lock_by_c0(T_t_operator *pt_operator);
int DB_t_operator_del_lock_by_c0();
int DB_t_operator_free_lock_by_c0();
#endif
