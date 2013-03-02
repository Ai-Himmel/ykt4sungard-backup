#ifndef  __T_depositoper_H_
#define  __T_depositoper_H_
typedef struct 
{
		char	opercode[8+1];
		char	status[1+1];
		char	usedevlimitflag[1+1];
		char	shopoperflag[1+1];
		char	opendate[8+1];
		char	closedate[8+1];
		int	maxamt;
		int	totalcnt;
		int	totalamt;
		char	lastdate[8+1];
		int	lastdaycnt;
		int	lastdayamt;
		int	lastcardno;
		int	lastdevseqno;
		int	lasttermseqno;
		char	lastdevphyid[30+1];
		char	lastsaved[30+1];
}T_t_depositoper;
int DB_t_depositoper_add(T_t_depositoper *pt_depositoper);
int DB_t_depositoper_read_by_opercode(char *v_opercode,T_t_depositoper *pt_depositoper);
int DB_t_depositoper_update_by_opercode(char *v_opercode,T_t_depositoper *pt_depositoper);
int DB_t_depositoper_del_by_opercode(char *v_opercode);
int DB_t_depositoper_read_lock_by_c0_and_opercode(char *v_opercode,T_t_depositoper *pt_depositoper);
int DB_t_depositoper_update_lock_by_c0(T_t_depositoper *pt_depositoper);
int DB_t_depositoper_free_lock_by_c0();
#endif
