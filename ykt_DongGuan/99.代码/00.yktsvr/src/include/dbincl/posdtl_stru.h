#ifndef  __T_posdtl_H_
#define  __T_posdtl_H_
typedef struct 
{
		int	fileid;
		int	rowno;
		int	hostdate;
		int	hosttime;
		int	citycode;
		int	merchid;
		char	posno[20+1];
		int	posseqno;
		char	samno[12+1];
		int	samseqno;
		char	cardasno[20+1];
		int	cardno;
		int	cardtype;
		int	transcode;
		int	termdate;
		int	termtime;
		int	lockflag;
		int	lineno;
		int	integral;
		int	transtype;
		int	cardcnt;
		int	amount;
		int	befcardbal;
		int	aftcardbal;
		char	lasttermsno[12+1];
		int	lasttermdate;
		int	lasttranstime;
		int	lasttranstype;
		int	lastamount;
		char	tac[8+1];
		int	accdate;
		char	refno[14+1];
		char	status[1+1];
		char	remark[240+1];
		int	errcode;
}T_t_posdtl;
int DB_t_posdtl_add(T_t_posdtl *pt_posdtl);
int DB_t_posdtl_read_by_fileid_and_rowno(int v_fileid,int v_rowno,T_t_posdtl *pt_posdtl);
int DB_t_posdtl_update_by_fileid_and_rowno(int v_fileid,int v_rowno,T_t_posdtl *pt_posdtl);
int DB_t_posdtl_del_by_fileid_and_rowno(int v_fileid,int v_rowno);
int DB_t_posdtl_read_lock_by_c0_and_fileid_and_rowno(int v_fileid,int v_rowno,T_t_posdtl *pt_posdtl);
int DB_t_posdtl_update_lock_by_c0(T_t_posdtl *pt_posdtl);
int DB_t_posdtl_del_lock_by_c0();
int DB_t_posdtl_free_lock_by_c0();
#endif
