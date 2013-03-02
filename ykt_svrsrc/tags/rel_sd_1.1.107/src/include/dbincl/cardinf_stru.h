#ifndef  __T_cardinf_H_
#define  __T_cardinf_H_
typedef struct 
{
		char	card_id[8+1];
		char	pers_id[9+1];
		int	card_type_id;
		char	bank_card_id[30+1];
		char	ic_chip_no[20+1];
		int	card_state;
		char	issu_date[10+1];
		char	issu_oper_id[4+1];
		char	invalid_date[10+1];
		char	del_date[10+1];
		char	del_oper_id[4+1];
		char	lib_no[11+1];
		char	up_time[10+1];
		double	fee;
		int	fee_type;
		char	lockdate[10+1];
		char	locktype[10+1];
		int	printnum;
		char	isneedpay[1+1];
}T_tab_card_info;
int DB_tab_card_info_open_select_by_c1_and_ic_chip_no(char *v_ic_chip_no);
int DB_tab_card_info_fetch_select_by_c1(T_tab_card_info *ptab_card_info);
int DB_tab_card_info_close_select_by_c1();
#endif
