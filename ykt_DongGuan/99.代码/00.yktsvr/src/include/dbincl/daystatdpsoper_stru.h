#ifndef  __T_daystatdpsoper_H_
#define  __T_daystatdpsoper_H_
typedef struct 
{
		int	settledate;
		int	transcode;
		char	opercode[8+1];
		char	merchantno[20+1];
		int	cardtype;
		int	periodyear;
		int	periodmonth;
		int	statdate;
		int	transcnt;
		int	transamt;
		int	feeamt;
}T_t_daystatdpsoper;
int DB_t_daystatdpsoper_add(T_t_daystatdpsoper *pt_daystatdpsoper);
int DB_t_daystatdpsoper_read_by_settledate_and_transcode_and_opercode_and_merchantno_and_cardtype(int v_settledate,int v_transcode,const char *v_opercode,const char *v_merchantno,int v_cardtype,T_t_daystatdpsoper *pt_daystatdpsoper);
int DB_t_daystatdpsoper_update_by_settledate_and_transcode_and_opercode_and_merchantno_and_cardtype(int v_settledate,int v_transcode,char *v_opercode,char *v_merchantno,int v_cardtype,T_t_daystatdpsoper *pt_daystatdpsoper);
int DB_t_daystatdpsoper_del_by_settledate_and_transcode_and_opercode_and_merchantno_and_cardtype(int v_settledate,int v_transcode,const char *v_opercode,const char *v_merchantno,int v_cardtype);
int DB_t_daystatdpsoper_read_lock_by_c0_and_settledate_and_transcode_and_opercode_and_merchantno_and_cardtype(int v_settledate,int v_transcode,const char *v_opercode,const char *v_merchantno,int v_cardtype,T_t_daystatdpsoper *pt_daystatdpsoper);
int DB_t_daystatdpsoper_update_lock_by_c0(T_t_daystatdpsoper *pt_daystatdpsoper);
int DB_t_daystatdpsoper_del_lock_by_c0();
int DB_t_daystatdpsoper_free_lock_by_c0();
int DB_t_daystatdpsoper_open_select_by_c1_and_settledate(int v_settledate);
int DB_t_daystatdpsoper_fetch_select_by_c1(T_t_daystatdpsoper *pt_daystatdpsoper);
int DB_t_daystatdpsoper_update_select_by_c1(T_t_daystatdpsoper *pt_daystatdpsoper);
int DB_t_daystatdpsoper_close_select_by_c1();
#endif
