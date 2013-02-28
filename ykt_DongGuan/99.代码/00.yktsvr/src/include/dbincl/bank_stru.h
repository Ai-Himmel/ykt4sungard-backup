#ifndef  __T_bank_H_
#define  __T_bank_H_
typedef struct 
{
		int	bankid;
		char	bankcode[12+1];
		char	bankname[60+1];
		int	enabled;
		int	svrbegintime;
		int	svrendtime;
		int	frontid;
		char	bankip[15+1];
		int	bankport;
		int	banktimeout;
}T_t_bank;
int DB_t_bank_add(T_t_bank *pt_bank);
int DB_t_bank_read_by_bankid(int v_bankid,T_t_bank *pt_bank);
int DB_t_bank_update_by_bankid(int v_bankid,T_t_bank *pt_bank);
int DB_t_bank_del_by_bankid(int v_bankid);
int DB_t_bank_read_lock_by_c0_and_bankid(int v_bankid,T_t_bank *pt_bank);
int DB_t_bank_update_lock_by_c0(T_t_bank *pt_bank);
int DB_t_bank_del_lock_by_c0();
int DB_t_bank_free_lock_by_c0();
#endif
