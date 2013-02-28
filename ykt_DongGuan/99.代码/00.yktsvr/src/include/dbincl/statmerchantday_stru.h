#ifndef  __T_statmerchantday_H_
#define  __T_statmerchantday_H_
typedef struct 
{
		int	merchantid;
		int	transcode;
		int	settledate;
		int	cardtype;
		int	validtype;
		int	settleyear;
		int	settlemonth;
		int	statdate;
		int	transnum;
		int	transamt;
		int	feeamt;
}T_t_statmerchantday;
int DB_t_statmerchantday_add(T_t_statmerchantday *pt_statmerchantday);
int DB_t_statmerchantday_read_by_merchantid_and_transcode_and_settledate_and_cardtype_and_validtype(int v_merchantid,int v_transcode,int v_settledate,int v_cardtype,int v_validtype,T_t_statmerchantday *pt_statmerchantday);
int DB_t_statmerchantday_update_by_merchantid_and_transcode_and_settledate_and_cardtype_and_validtype(int v_merchantid,int v_transcode,int v_settledate,int v_cardtype,int v_validtype,T_t_statmerchantday *pt_statmerchantday);
int DB_t_statmerchantday_del_by_merchantid_and_transcode_and_settledate_and_cardtype_and_validtype(int v_merchantid,int v_transcode,int v_settledate,int v_cardtype,int v_validtype);
int DB_t_statmerchantday_read_lock_by_c0_and_merchantid_and_transcode_and_settledate_and_cardtype_and_validtype(int v_merchantid,int v_transcode,int v_settledate,int v_cardtype,int v_validtype,T_t_statmerchantday *pt_statmerchantday);
int DB_t_statmerchantday_update_lock_by_c0(T_t_statmerchantday *pt_statmerchantday);
int DB_t_statmerchantday_del_lock_by_c0();
int DB_t_statmerchantday_free_lock_by_c0();
#endif
