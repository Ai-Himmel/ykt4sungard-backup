#ifndef  __T_msglist_H_
#define  __T_msglist_H_
typedef struct 
{
		int	msgid;
		int	msgtype;
		int	msglevel;
		int	sysid;
		int	deviceid;
		int	cardno;
		char	transdate[8+1];
		char	createdtime[30+1];
		char	starttime[30+1];
		char	endtime[30+1];
		char	reqdata[1000+1];
		char	respdata[1000+1];
		int	funcno;
		int	pfuncno;
		int	maxsendcnt;
		int	sendcnt;
		int	recvcnt;
		int	status;
		int	seqno;
		char	opercode[8+1];
		int	errcode;
		char	errmsg[240+1];
		char	delflag[1+1];
}T_t_msglist;
int DB_t_msglist_add(T_t_msglist *pt_msglist);
int DB_t_msglist_read_by_msgid(int v_msgid,T_t_msglist *pt_msglist);
int DB_t_msglist_update_by_msgid(int v_msgid,T_t_msglist *pt_msglist);
int DB_t_msglist_del_by_msgid(int v_msgid);
int DB_t_msglist_read_lock_by_c0_and_msgid(int v_msgid,T_t_msglist *pt_msglist);
int DB_t_msglist_update_lock_by_c0(T_t_msglist *pt_msglist);
int DB_t_msglist_free_lock_by_c0();
int DB_t_msglist_open_select_by_c1_and_msgid(int v_msgid);
int DB_t_msglist_fetch_select_by_c1(T_t_msglist *pt_msglist);
int DB_t_msglist_close_select_by_c1();
#endif
