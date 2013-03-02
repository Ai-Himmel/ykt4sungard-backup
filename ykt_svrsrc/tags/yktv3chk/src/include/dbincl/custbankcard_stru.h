#ifndef  __T_custbankcard_H_
#define  __T_custbankcard_H_
typedef struct 
{
		int	custid;
		char	bankcardno[30+1];
		char	bankcode[2+1];
		char	lastsaved[30+1];
		char	opercode[8+1];
}T_t_custbankcard;
int DB_t_custbankcard_add(T_t_custbankcard *pt_custbankcard);
int DB_t_custbankcard_read_by_custid_and_bankcardno(int v_custid,char *v_bankcardno,T_t_custbankcard *pt_custbankcard);
int DB_t_custbankcard_update_by_custid_and_bankcardno(int v_custid,char *v_bankcardno,T_t_custbankcard *pt_custbankcard);
int DB_t_custbankcard_del_by_custid(int v_custid);
int DB_t_custbankcard_del_by_custid_and_bankcardno(int v_custid,char *v_bankcardno);
int DB_t_custbankcard_read_lock_by_c0_and_custid_and_bankcardno(int v_custid,char *v_bankcardno,T_t_custbankcard *pt_custbankcard);
int DB_t_custbankcard_update_lock_by_c0(T_t_custbankcard *pt_custbankcard);
int DB_t_custbankcard_free_lock_by_c0();
#endif
