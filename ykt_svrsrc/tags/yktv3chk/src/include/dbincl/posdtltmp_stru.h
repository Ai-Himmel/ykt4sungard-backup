#ifndef  __T_posdtltmp_H_
#define  __T_posdtltmp_H_
typedef struct 
{
		char	transdate[8+1];
		char	transtime[6+1];
		char	devphyid[30+1];
		int	devseqno;
		int	shopcardno;
		int	transcode;
		int	cardno;
		int	purseno;
		int	cardcnt;
		int	cardbefbal;
		int	cardaftbal;
		int	amount;
		int	managefee;
		int	transmark;
		char	batchno[30+1];
		int	seqno;
		char	impdate[8+1];
		char	imptime[6+1];
		char	impoper[8+1];
		int	termseqno;
		char	status[1+1];
		char	errmsg[240+1];
		char	chkoper[8+1];
}T_t_posdtltmp;
int DB_t_posdtltmp_add(T_t_posdtltmp *pt_posdtltmp);
int DB_t_posdtltmp_read_by_cardno_and_purseno_and_cardcnt(int v_cardno,int v_purseno,int v_cardcnt,T_t_posdtltmp *pt_posdtltmp);
int DB_t_posdtltmp_update_by_cardno_and_purseno_and_cardcnt(int v_cardno,int v_purseno,int v_cardcnt,T_t_posdtltmp *pt_posdtltmp);
int DB_t_posdtltmp_del_by_cardno_and_purseno_and_cardcnt(int v_cardno,int v_purseno,int v_cardcnt);
int DB_t_posdtltmp_read_lock_by_c0_and_cardno_and_purseno_and_cardcnt(int v_cardno,int v_purseno,int v_cardcnt,T_t_posdtltmp *pt_posdtltmp);
int DB_t_posdtltmp_update_lock_by_c0(T_t_posdtltmp *pt_posdtltmp);
int DB_t_posdtltmp_free_lock_by_c0();
#endif
