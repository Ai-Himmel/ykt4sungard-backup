#ifndef  __T_savdtl_H_
#define  __T_savdtl_H_
typedef struct 
{
		int	seqno;
		char	tx_date[8+1];
		char	tx_time[6+1];
		int	card_no;
		int	billtype;
		char	billno[20+1];
		int	cnt;
		double	amount;
		int	tx_code;
		char	oper_no[10+1];
		char	comments[150+1];
}T_t_tif_savdtl;
int DB_t_tif_savdtl_add(T_t_tif_savdtl *pt_tif_savdtl);
int DB_t_tif_savdtl_read_by_card_no(int v_card_no,T_t_tif_savdtl *pt_tif_savdtl);
int DB_t_tif_savdtl_read_lock_by_cur_and_tx_date_and_seqno(char *v_tx_date,int v_seqno,T_t_tif_savdtl *pt_tif_savdtl);
int DB_t_tif_savdtl_update_lock_by_cur(T_t_tif_savdtl *pt_tif_savdtl);
int DB_t_tif_savdtl_free_lock_cur();
#endif
