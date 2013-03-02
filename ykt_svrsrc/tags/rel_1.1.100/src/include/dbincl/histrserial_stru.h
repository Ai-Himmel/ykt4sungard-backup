#ifndef  __T_histrserial_H_
#define  __T_histrserial_H_
typedef struct 
{
		char	bak_date[10+1];
		char	bak_time[8+1];
		int	serial_no;
		int	other_seri_no;
		int	serial_type;
		int	serial_state;
		char	operate_date[10+1];
		char	operate_time[8+1];
		char	collect_date[10+1];
		char	collect_time[8+1];
		char	enteract_date[10+1];
		char	enteract_time[8+1];
		int	maindevice_id;
		int	device_id;
		char	devphy999_id[8+1];
		char	showid[10+1];
		int	card_id;
		int	purse_id;
		int	trade_count;
		double	trade_fee;
		double	in_balance;
		double	out_balance;
		double	deposit_fee;
		double	in_fee;
		double	cost_fee;
		double	boardfee;
		char	oldpwd[32+1];
		char	newpwd[32+1];
		int	customer_id;
		char	oper_code[10+1];
		char	out_account_id[16+1];
		char	in_account_id[16+1];
		char	b_act_id[40+1];
		int	sys_id;
		int	condition_id;
		char	is_online[1+1];
		int	tmark;
		char	dev_auth[8+1];
		int	comu_ver;
		int	run_reason;
		char	crc[5+1];
		int	ecode;
		int	reviseserial_no;
		char	reserve_1[40+1];
		char	reserve_2[40+1];
		char	reserve_3[40+1];
}T_t_tif_tradeserial_his;
int DB_t_tif_tradeserial_his_open_select_by_cur1_and_serial_type_and_card_id(int v_serial_type,int v_card_id);
int DB_t_tif_tradeserial_his_fetch_select_by_cur1(T_t_tif_tradeserial_his *pt_tif_tradeserial_his);
int DB_t_tif_tradeserial_his_close_select_by_cur1();
int DB_t_tif_tradeserial_his_add(T_t_tif_tradeserial_his *pt_tif_tradeserial_his);
int DB_t_tif_tradeserial_his_read_by_enteract_date_and_serial_no(char *v_enteract_date,int v_serial_no,T_t_tif_tradeserial_his *pt_tif_tradeserial_his);
#endif
