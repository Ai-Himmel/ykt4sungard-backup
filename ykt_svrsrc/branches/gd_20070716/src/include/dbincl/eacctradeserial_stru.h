#ifndef  __T_eacctradeserial_H_
#define  __T_eacctradeserial_H_
typedef struct 
{
		int	serial_no;
		char	ordercode[16+1];
		char	logic_date[10+1];
		char	opcode[10+1];
		char	operate_date[10+1];
		char	operate_time[10+1];
		double	frozenmoney;
		double	paymoney;
		char	payacc[16+1];
		char	payname[60+1];
		char	rcvacc[16+1];
		char	rcvname[60+1];
		char	tradestatus[1+1];
		char	frozencode[1+1];
		char	backoff_flag[1+1];
}T_t_tif_eacctradeserial;
int DB_t_tif_eacctradeserial_add(T_t_tif_eacctradeserial *pt_tif_eacctradeserial);
int DB_t_tif_eacctradeserial_read_by_logic_date_and_ordercode_and_opcode(char *v_logic_date,char *v_ordercode,char *v_opcode,T_t_tif_eacctradeserial *pt_tif_eacctradeserial);
int DB_t_tif_eacctradeserial_update_by_logic_date_and_ordercode_and_opcode(char *v_logic_date,char *v_ordercode,char *v_opcode,T_t_tif_eacctradeserial *pt_tif_eacctradeserial);
int DB_t_tif_eacctradeserial_read_lock_by_cur_and_logic_date_and_ordercode_and_opcode(char *v_logic_date,char *v_ordercode,char *v_opcode,T_t_tif_eacctradeserial *pt_tif_eacctradeserial);
int DB_t_tif_eacctradeserial_update_lock_by_cur(T_t_tif_eacctradeserial *pt_tif_eacctradeserial);
int DB_t_tif_eacctradeserial_free_lock_cur();
#endif
