#ifndef  __T_actdaysum_H_
#define  __T_actdaysum_H_
typedef struct 
{
		char	operate_date[10+1];
		char	operate_time[8+1];
		char	account_id[16+1];
		int	act_type;
		int	customer_id;
		char	cut_name[60+1];
		int	cut_type;
		char	stuemp_no[20+1];
		int	card_id;
		int	purse_id;
		int	card_state;
		int	card_type;
		char	subno[20+1];
		char	password[32+1];
		int	current_state;
		char	isautotra[1+1];
		double	last_bala;
		double	last_freebala;
		double	last_frozebala;
		double	cur_bala;
		double	cur_freebala;
		double	cur_frozebala;
		double	out_bala;
		double	in_bala;
		int	out_count;
		int	in_count;
		double	card_balance;
		int	nobala_num;
		int	consume_count;
		char	open_date[26+1];
		double	today_out_bala;
		double	today_in_bala;
		int	today_out_count;
		int	today_in_count;
		char	reserve_1[20+1];
		char	reserve_2[20+1];
		char	reserve_3[20+1];
		char	comments[150+1];
}T_t_tif_act_daysum;
int DB_t_tif_act_daysum_add(T_t_tif_act_daysum *pt_tif_act_daysum);
int DB_t_tif_act_daysum_del_by_operate_date(char *v_operate_date);
int DB_t_tif_act_daysum_del_by_operate_date_and_account_id(char *v_operate_date,char *v_account_id);
int DB_t_tif_act_daysum_read_by_operate_date(char *v_operate_date,T_t_tif_act_daysum *pt_tif_act_daysum);
int DB_t_tif_act_daysum_read_by_operate_date_and_account_id(char *v_operate_date,char *v_account_id,T_t_tif_act_daysum *pt_tif_act_daysum);
#endif
