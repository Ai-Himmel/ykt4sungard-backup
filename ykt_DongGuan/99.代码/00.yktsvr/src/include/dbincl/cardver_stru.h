#ifndef  __T_cardver_H_
#define  __T_cardver_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		char	cardverno[12+1];
		int	cardno;
		char	cardphyid[16+1];
		char	stuempno[30+1];
		int	cardvertype;
		int	adddelflag;
		char	status[1+1];
}T_t_cardver;
int DB_t_cardver_add(T_t_cardver *pt_cardver);
int DB_t_cardver_read_by_cardverno(const char *v_cardverno,T_t_cardver *pt_cardver);
int DB_t_cardver_update_by_cardverno(char *v_cardverno,T_t_cardver *pt_cardver);
int DB_t_cardver_del_by_cardverno(const char *v_cardverno);
int DB_t_cardver_read_lock_by_c0_and_cardverno(const char *v_cardverno,T_t_cardver *pt_cardver);
int DB_t_cardver_update_lock_by_c0(T_t_cardver *pt_cardver);
int DB_t_cardver_free_lock_by_c0();
int DB_t_cardver_open_select_by_c1_and_cardverno(const char *v_cardverno);
int DB_t_cardver_fetch_select_by_c1(T_t_cardver *pt_cardver);
int DB_t_cardver_close_select_by_c1();
#endif
