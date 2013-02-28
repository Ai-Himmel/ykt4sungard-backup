#ifndef  __T_customer_H_
#define  __T_customer_H_
typedef struct 
{
		int	custid;
		int	cardid;
		int	cardno;
		int	cardtype;
		int	issueunit;
		int	expmonths;
		int	applydate;
		int	applystatus;
		int	prepaidamt;
		char	custname[90+1];
		char	idtype[2+1];
		char	idno[60+1];
		int	birthday;
		int	height;
		char	sex[2+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	email[60+1];
		char	unitname[240+1];
		char	grpsrvno[20+1];
		char	married[2+1];
		char	education[2+1];
		char	politics[2+1];
		char	incomesrc[2+1];
		char	country[3+1];
		char	nation[2+1];
		char	native[60+1];
		char	domiciletype[2+1];
		char	domicile[240+1];
		char	livereason[2+1];
		char	addr[240+1];
		int	livedate;
		int	arrivaldate;
		char	updtime[14+1];
		int	delflag;
		int	deldate;
}T_t_customer;
int DB_t_customer_add(T_t_customer *pt_customer);
int DB_t_customer_read_by_custid(int v_custid,T_t_customer *pt_customer);
int DB_t_customer_update_by_custid(int v_custid,T_t_customer *pt_customer);
int DB_t_customer_del_by_custid(int v_custid);
int DB_t_customer_read_lock_by_c0_and_custid(int v_custid,T_t_customer *pt_customer);
int DB_t_customer_update_lock_by_c0(T_t_customer *pt_customer);
int DB_t_customer_del_lock_by_c0();
int DB_t_customer_free_lock_by_c0();
#endif
