#ifndef  __T_shoppostmp_H_
#define  __T_shoppostmp_H_
typedef struct 
{
		char	batchno[30+1];
		int	seqno;
		char	transdate[8+1];
		char	transtime[6+1];
		char	opercode[8+1];
		int	deviceid;
		char	devphyid[30+1];
		int	shopid;
		char	endtime[6+1];
		char	startdate[8+1];
		char	enddate[8+1];
		char	errmsg[240+1];
}T_t_shoppostmp;
int DB_t_shoppostmp_add(T_t_shoppostmp *pt_shoppostmp);
int DB_t_shoppostmp_read_by_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_shoppostmp *pt_shoppostmp);
int DB_t_shoppostmp_update_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_shoppostmp *pt_shoppostmp);
int DB_t_shoppostmp_del_by_batchno(const char *v_batchno);
int DB_t_shoppostmp_del_by_batchno_and_seqno(const char *v_batchno,int v_seqno);
int DB_t_shoppostmp_read_lock_by_c0_and_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_shoppostmp *pt_shoppostmp);
int DB_t_shoppostmp_update_lock_by_c0(T_t_shoppostmp *pt_shoppostmp);
int DB_t_shoppostmp_free_lock_by_c0();
int DB_t_shoppostmp_open_select_by_c1_and_batchno(const char *v_batchno);
int DB_t_shoppostmp_fetch_select_by_c1(T_t_shoppostmp *pt_shoppostmp);
int DB_t_shoppostmp_close_select_by_c1();
#endif
