#ifndef  __T_mbchkdtl_H_
#define  __T_mbchkdtl_H_
typedef struct 
{
		char	transdate[8+1];
		char	refno[14+1];
		int	cardno;
		char	mobile[30+1];
		double	amount;
		int	chkstatus;
		int	chkflag;
		char	chkoper[8+1];
		char	chkdate[8+1];
		char	chktime[6+1];
}T_t_mobilechkdtl;
int DB_t_mobilechkdtl_add(T_t_mobilechkdtl *pt_mobilechkdtl);
int DB_t_mobilechkdtl_read_by_refno(const char *v_refno,T_t_mobilechkdtl *pt_mobilechkdtl);
int DB_t_mobilechkdtl_update_by_refno(char *v_refno,T_t_mobilechkdtl *pt_mobilechkdtl);
int DB_t_mobilechkdtl_del_by_refno(const char *v_refno);
int DB_t_mobilechkdtl_read_lock_by_c0_and_refno(const char *v_refno,T_t_mobilechkdtl *pt_mobilechkdtl);
int DB_t_mobilechkdtl_update_lock_by_c0(T_t_mobilechkdtl *pt_mobilechkdtl);
int DB_t_mobilechkdtl_free_lock_by_c0();
int DB_t_mobilechkdtl_open_select_by_c1_and_cardno(int v_cardno);
int DB_t_mobilechkdtl_fetch_select_by_c1(T_t_mobilechkdtl *pt_mobilechkdtl);
int DB_t_mobilechkdtl_close_select_by_c1();
#endif
