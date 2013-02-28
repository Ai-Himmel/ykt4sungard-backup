#ifndef  __T_cfgfee_H_
#define  __T_cfgfee_H_
typedef struct 
{
		int	feetype;
		int	transcode;
		int	cardtype;
		int	transtype;
		int	ratetype;
		double	rateamt;
		char	remark[240+1];
}T_t_cfgfee;
int DB_t_cfgfee_add(T_t_cfgfee *pt_cfgfee);
int DB_t_cfgfee_read_by_feetype_and_transcode_and_cardtype_and_transtype(int v_feetype,int v_transcode,int v_cardtype,int v_transtype,T_t_cfgfee *pt_cfgfee);
int DB_t_cfgfee_update_by_feetype_and_transcode_and_cardtype_and_transtype(int v_feetype,int v_transcode,int v_cardtype,int v_transtype,T_t_cfgfee *pt_cfgfee);
int DB_t_cfgfee_del_by_feetype_and_transcode_and_cardtype_and_transtype(int v_feetype,int v_transcode,int v_cardtype,int v_transtype);
int DB_t_cfgfee_read_lock_by_c0_and_feetype_and_transcode_and_cardtype_and_transtype(int v_feetype,int v_transcode,int v_cardtype,int v_transtype,T_t_cfgfee *pt_cfgfee);
int DB_t_cfgfee_update_lock_by_c0(T_t_cfgfee *pt_cfgfee);
int DB_t_cfgfee_free_lock_by_c0();
#endif
