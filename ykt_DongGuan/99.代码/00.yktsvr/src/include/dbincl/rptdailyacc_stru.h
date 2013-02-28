#ifndef  __T_rptdailyacc_H_
#define  __T_rptdailyacc_H_
typedef struct 
{
		char	accdate[8+1];
		char	accno[20+1];
		int	transcnt;
		double	dramt;
		double	cramt;
		int	balflag;
		double	balance;
}T_t_rptdailyacc;
int DB_t_rptdailyacc_add(T_t_rptdailyacc *pt_rptdailyacc);
int DB_t_rptdailyacc_read_by_accdate_and_accno(const char *v_accdate,const char *v_accno,T_t_rptdailyacc *pt_rptdailyacc);
int DB_t_rptdailyacc_update_by_accdate_and_accno(char *v_accdate,char *v_accno,T_t_rptdailyacc *pt_rptdailyacc);
int DB_t_rptdailyacc_del_by_accdate_and_accno(const char *v_accdate,const char *v_accno);
int DB_t_rptdailyacc_read_lock_by_c0_and_accdate_and_accno(const char *v_accdate,const char *v_accno,T_t_rptdailyacc *pt_rptdailyacc);
int DB_t_rptdailyacc_update_lock_by_c0(T_t_rptdailyacc *pt_rptdailyacc);
int DB_t_rptdailyacc_free_lock_by_c0();
#endif
