#ifndef  __T_histrlog_H_
#define  __T_histrlog_H_
typedef struct 
{
		char	bak_date[10+1];
		char	bak_time[8+1];
		int	serino;
		int	seri_type;
		int	fee_type;
		char	act_id[16+1];
		char	subno[20+1];
		char	other_actid[16+1];
		char	other_subno[20+1];
		int	outorin;
		double	op_fee;
		double	new_fee;
		double	cur_frozebala;
		int	warrant_type;
		char	warrant_no[20+1];
		char	operate_date[10+1];
		char	operate_time[8+1];
		char	collect_date[10+1];
		char	collect_time[8+1];
		char	enteract_date[10+1];
		char	enteract_time[8+1];
		int	maindevice_id;
		int	device_id;
		int	annex;
		char	record_oper[10+1];
		char	check_oper[10+1];
		char	write_oper[10+1];
		char	reserve_1[20+1];
		char	reserve_2[20+1];
		char	reserve_3[20+1];
		char	comments[150+1];
}T_t_tif_tradelog_his;
int DB_t_tif_tradelog_his_add(T_t_tif_tradelog_his *pt_tif_tradelog_his);
#endif
