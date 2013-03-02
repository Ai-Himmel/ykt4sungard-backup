#ifndef  __T_subsidy_H_
#define  __T_subsidy_H_
typedef struct 
{
		char	batchno[30+1];
		int	seqno;
		char	stuempno[30+1];
		int	custid;
		int	subsidyno;
		int	cardno;
		char	summary[60+1];
		char	brokername[60+1];
		char	brokeridno[60+1];
		int	paytype;
		char	voucherno[30+1];
		double	amount;
		char	subsidytype[1+1];
		char	impdate[8+1];
		char	imptime[6+1];
		char	putdate[8+1];
		char	puttime[6+1];
		char	getdate[8+1];
		char	gettime[6+1];
		char	status[1+1];
		char	errmsg[240+1];
		char	opercode[8+1];
}T_t_subsidy;
int DB_t_subsidy_add(T_t_subsidy *pt_subsidy);
int DB_t_subsidy_read_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_subsidy *pt_subsidy);
int DB_t_subsidy_read_by_batchno_and_stuempno(char *v_batchno,char *v_stuempno,T_t_subsidy *pt_subsidy);
int DB_t_subsidy_update_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_subsidy *pt_subsidy);
int DB_t_subsidy_del_by_batchno_and_seqno(char *v_batchno,int v_seqno);
int DB_t_subsidy_del_by_batchno_and_status(char *v_batchno,char *v_status);
int DB_t_subsidy_del_by_batchno_and_custid(char *v_batchno,int v_custid);
int DB_t_subsidy_read_lock_by_c0_and_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_subsidy *pt_subsidy);
int DB_t_subsidy_update_lock_by_c0(T_t_subsidy *pt_subsidy);
int DB_t_subsidy_free_lock_by_c0();
int DB_t_subsidy_open_select_by_c1_and_batchno(char *v_batchno);
int DB_t_subsidy_fetch_select_by_c1(T_t_subsidy *pt_subsidy);
int DB_t_subsidy_close_select_by_c1();
int DB_t_subsidy_open_select_for_update_by_c2_and_cardno_and_status(int v_cardno,char *v_status);
int DB_t_subsidy_fetch_select_by_c2(T_t_subsidy *pt_subsidy);
int DB_t_subsidy_update_select_by_c2(T_t_subsidy *pt_subsidy);
int DB_t_subsidy_close_select_by_c2();
#endif
