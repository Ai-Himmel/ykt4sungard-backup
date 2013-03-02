#ifndef  __T_subsidytmp_H_
#define  __T_subsidytmp_H_
typedef struct 
{
		int	subsidy_no;
		int	custid;
		char	batchno[14+1];
		int	seqno;
		char	opercode[10+1];
		int	cardno;
		char	summary[60+1];
		char	expiredate[8+1];
		int	billtype;
		char	billno[20+1];
		double	amount;
		char	subsidytype[1+1];
		char	tx_date[8+1];
		char	tx_time[6+1];
		char	get_date[8+1];
		char	get_time[6+1];
		char	status[1+1];
		char	broker_id[18+1];
		char	broker_name[60+1];
}T_t_tif_subsidytmp;
int DB_t_tif_subsidytmp_add(T_t_tif_subsidytmp *pt_tif_subsidytmp);
int DB_t_tif_subsidytmp_del_by_opercode(char *v_opercode);
int DB_t_tif_subsidytmp_open_select_by_c0_and_batchno(char *v_batchno);
int DB_t_tif_subsidytmp_fetch_select_by_c0(T_t_tif_subsidytmp *pt_tif_subsidytmp);
int DB_t_tif_subsidytmp_close_select_by_c0();
#endif
