#ifndef  __T_carddtldps_H_
#define  __T_carddtldps_H_
typedef struct 
{
		int	cardid;
		int	cardseqno;
		int	settledate;
		char	samno[12+1];
		int	samseqno;
		int	termdate;
		int	termtime;
		int	batchno;
		int	cardno;
		char	cardasno[20+1];
		int	cardtype;
		int	cardcnt;
		int	transtype;
		int	transcode;
		int	transamt;
		int	befcardbal;
		int	aftcardbal;
		int	balance;
		int	expdate;
		char	merchantno[20+1];
		int	branchno;
		int	hostdate;
		int	hosttime;
		int	operid;
		int	termid;
		char	status[1+1];
		char	wctatus[1+1];
		int	errcode;
		char	remark[240+1];
}T_t_carddtldps;
int DB_t_carddtldps_add(T_t_carddtldps *pt_carddtldps);
int DB_t_carddtldps_read_by_cardid_and_cardseqno(int v_cardid,int v_cardseqno,T_t_carddtldps *pt_carddtldps);
int DB_t_carddtldps_update_by_cardid_and_cardseqno(int v_cardid,int v_cardseqno,T_t_carddtldps *pt_carddtldps);
int DB_t_carddtldps_del_by_cardid_and_cardseqno(int v_cardid,int v_cardseqno);
int DB_t_carddtldps_read_lock_by_c0_and_cardid_and_cardseqno(int v_cardid,int v_cardseqno,T_t_carddtldps *pt_carddtldps);
int DB_t_carddtldps_update_lock_by_c0(T_t_carddtldps *pt_carddtldps);
int DB_t_carddtldps_del_lock_by_c0();
int DB_t_carddtldps_free_lock_by_c0();
#endif
