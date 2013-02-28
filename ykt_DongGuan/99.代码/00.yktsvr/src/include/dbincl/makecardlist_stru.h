#ifndef  __T_makecardlist_H_
#define  __T_makecardlist_H_
typedef struct 
{
		char	batchno[14+1];
		int	cardno;
		char	cardasno[20+1];
		int	expdate;
		int	issueunit;
		char	custname[90+1];
		char	idtype[2+1];
		char	idno[60+1];
}T_t_makecardlist;
int DB_t_makecardlist_add(T_t_makecardlist *pt_makecardlist);
int DB_t_makecardlist_read_by_batchno_and_cardno(const char *v_batchno,int v_cardno,T_t_makecardlist *pt_makecardlist);
int DB_t_makecardlist_update_by_batchno_and_cardno(char *v_batchno,int v_cardno,T_t_makecardlist *pt_makecardlist);
int DB_t_makecardlist_del_by_batchno_and_cardno(const char *v_batchno,int v_cardno);
int DB_t_makecardlist_read_lock_by_c0_and_batchno_and_cardno(const char *v_batchno,int v_cardno,T_t_makecardlist *pt_makecardlist);
int DB_t_makecardlist_update_lock_by_c0(T_t_makecardlist *pt_makecardlist);
int DB_t_makecardlist_del_lock_by_c0();
int DB_t_makecardlist_free_lock_by_c0();
int DB_t_makecardlist_read_lock_by_c1_and_cardasno(const char *v_cardasno,T_t_makecardlist *pt_makecardlist);
int DB_t_makecardlist_update_lock_by_c1(T_t_makecardlist *pt_makecardlist);
int DB_t_makecardlist_del_lock_by_c1();
int DB_t_makecardlist_free_lock_by_c1();
#endif
