#ifndef  __T_paypara_H_
#define  __T_paypara_H_
typedef struct 
{
		int	paycode;
		char	paraname[60+1];
		char	paraval[60+1];
		char	remark[240+1];
}T_t_paypara;
int DB_t_paypara_add(T_t_paypara *pt_paypara);
int DB_t_paypara_read_by_paycode_and_paraname(int v_paycode,const char *v_paraname,T_t_paypara *pt_paypara);
int DB_t_paypara_update_by_paycode_and_paraname(int v_paycode,char *v_paraname,T_t_paypara *pt_paypara);
int DB_t_paypara_del_by_paycode_and_paraname(int v_paycode,const char *v_paraname);
int DB_t_paypara_open_select_by_c1_and_paycode(int v_paycode);
int DB_t_paypara_fetch_select_by_c1(T_t_paypara *pt_paypara);
int DB_t_paypara_close_select_by_c1();
int DB_t_paypara_open_select_by_c2_and_paraname(const char *v_paraname);
int DB_t_paypara_fetch_select_by_c2(T_t_paypara *pt_paypara);
int DB_t_paypara_close_select_by_c2();
#endif
