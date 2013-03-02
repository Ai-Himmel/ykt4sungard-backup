#ifndef  __T_cardbook_H_
#define  __T_cardbook_H_
typedef struct 
{
		int	recordno;
		int	cardtype;
		char	startno[10+1];
		char	endno[10+1];
		char	curno[10+1];
		int	totalcnt;
		int	unusedcnt;
		char	opercode[8+1];
		char	status[1+1];
		char	lastsaved[30+1];
}T_t_cardbook;
int DB_t_cardbook_add(T_t_cardbook *pt_cardbook);
int DB_t_cardbook_read_by_recordno(int v_recordno,T_t_cardbook *pt_cardbook);
int DB_t_cardbook_update_by_recordno(int v_recordno,T_t_cardbook *pt_cardbook);
int DB_t_cardbook_del_by_recordno(int v_recordno);
int DB_t_cardbook_read_lock_by_c0_and_recordno(int v_recordno,T_t_cardbook *pt_cardbook);
int DB_t_cardbook_update_lock_by_c0(T_t_cardbook *pt_cardbook);
int DB_t_cardbook_free_lock_by_c0();
int DB_t_cardbook_open_select_by_c1_and_status(char *v_status);
int DB_t_cardbook_fetch_select_by_c1(T_t_cardbook *pt_cardbook);
int DB_t_cardbook_close_select_by_c1();
#endif
