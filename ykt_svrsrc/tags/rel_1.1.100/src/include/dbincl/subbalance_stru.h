#ifndef  __T_subbalance_H_
#define  __T_subbalance_H_
typedef struct 
{
		char	txdate[10+1];
		char	subno[9+1];
		char	subname[50+1];
		double	bbala;
		int	bbala_flag;
		double	dramnt;
		double	cramt;
		double	endbala;
		int	endbala_flag;
		char	spare1[25+1];
		char	spare2[25+1];
		char	spare3[25+1];
}T_t_tif_subject_balance;
int DB_t_tif_subject_balance_add(T_t_tif_subject_balance *pt_tif_subject_balance);
int DB_t_tif_subject_balance_del_by_txdate(char *v_txdate);
int DB_t_tif_subject_balance_open_select_between_c1_and_txdate_and_txdate(char *v_txdate_2,char *v_txdate_3);
int DB_t_tif_subject_balance_fetch_select_by_c1(T_t_tif_subject_balance *pt_tif_subject_balance);
int DB_t_tif_subject_balance_close_select_by_c1();
int DB_t_tif_subject_balance_read_by_txdate_and_subno(char *v_txdate,char *v_subno,T_t_tif_subject_balance *pt_tif_subject_balance);
#endif
