#ifndef  __T_psamcard_H_
#define  __T_psamcard_H_
typedef struct 
{
		int	cardno;
		int	cardtype;
		int	cardver;
		char	termno[12+1];
		int	status;
		char	startdate[8+1];
		char	expiredate[8+1];
		int	keyindex;
		int	deviceid;
		char	devjointime[30+1];
		char	publishid[8+1];
		char	userid[8+1];
		char	opendate[8+1];
		char	closedate[8+1];
		char	disabledate[8+1];
		char	lastsaved[30+1];
}T_t_psamcard;
int DB_t_psamcard_add(T_t_psamcard *pt_psamcard);
int DB_t_psamcard_read_by_cardno(int v_cardno,T_t_psamcard *pt_psamcard);
int DB_t_psamcard_read_by_termno(const char *v_termno,T_t_psamcard *pt_psamcard);
int DB_t_psamcard_update_by_cardno(int v_cardno,T_t_psamcard *pt_psamcard);
int DB_t_psamcard_del_by_cardno(int v_cardno);
int DB_t_psamcard_read_lock_by_c0_and_cardno(int v_cardno,T_t_psamcard *pt_psamcard);
int DB_t_psamcard_update_lock_by_c0(T_t_psamcard *pt_psamcard);
int DB_t_psamcard_free_lock_by_c0();
int DB_t_psamcard_read_lock_by_c1_and_termno(const char *v_termno,T_t_psamcard *pt_psamcard);
int DB_t_psamcard_update_lock_by_c1(T_t_psamcard *pt_psamcard);
int DB_t_psamcard_free_lock_by_c1();
#endif
