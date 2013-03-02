#ifndef  __T_customer_H_
#define  __T_customer_H_
typedef struct 
{
		int	custid;
		char	stuempno[30+1];
		int	custtype;
		int	feetype;
		char	status[1+1];
		char	custname[60+1];
		char	areacode[30+1];
		char	deptcode[30+1];
		char	deptfullname[1000+1];
		char	specialtycode[30+1];
		char	classcode[30+1];
		char	idtype[1+1];
		char	idno[60+1];
		char	sex[1+1];
		char	country[3+1];
		char	nation[2+1];
		char	email[60+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	custattr[10+1];
		char	indate[8+1];
		char	outdate[8+1];
		char	opendate[8+1];
		char	closedate[8+1];
		char	batchno[30+1];
		int	holdcardcnt;
		char	useflag[1+1];
		int	openflag;
		char	eaccflag[1+1];
		char	lastsaved[30+1];
}T_t_customer;
int DB_t_customer_add(T_t_customer *pt_customer);
int DB_t_customer_del_by_custid(int v_custid);
int DB_t_customer_read_by_custid(int v_custid,T_t_customer *pt_customer);
int DB_t_customer_read_lock_by_cur_and_custid(int v_custid,T_t_customer *pt_customer);
int DB_t_customer_update_lock_by_cur(T_t_customer *pt_customer);
int DB_t_customer_free_lock_cur();
int DB_t_customer_open_select_by_cur1_and_custid(int v_custid);
int DB_t_customer_fetch_select_by_cur1(T_t_customer *pt_customer);
int DB_t_customer_close_select_by_cur1();
int DB_t_customer_read_by_stuempno_and_status(char *v_stuempno,char *v_status,T_t_customer *pt_customer);
int DB_t_customer_read_by_stuempno_and_areacode(char *v_stuempno,char *v_areacode,T_t_customer *pt_customer);
#endif
