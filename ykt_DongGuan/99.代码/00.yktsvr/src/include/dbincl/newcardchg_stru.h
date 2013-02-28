#ifndef  __T_newcardchg_H_
#define  __T_newcardchg_H_
typedef struct 
{
		char	showcardno[10+1];
		char	stuempno[20+1];
		char	expiredate[8+1];
		int	status;
		char	batchno[30+1];
		int	seqno;
		char	cardphyid[16+1];
		char	oldcardphyid[16+1];
		char	lastsaved[30+1];
}T_t_newcardchange;
int DB_t_newcardchange_add(T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_read_by_stuempno(const char *v_stuempno,T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_read_by_showcardno(const char *v_showcardno,T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_update_by_showcardno(char *v_showcardno,T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_del_by_showcardno(const char *v_showcardno);
int DB_t_newcardchange_del_by_batchno(const char *v_batchno);
int DB_t_newcardchange_read_lock_by_c0_and_stuempno(const char *v_stuempno,T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_update_lock_by_c0(T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_free_lock_by_c0();
int DB_t_newcardchange_read_lock_by_c1_and_showcardno(const char *v_showcardno,T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_update_lock_by_c1(T_t_newcardchange *pt_newcardchange);
int DB_t_newcardchange_del_lock_by_c1();
int DB_t_newcardchange_free_lock_by_c1();
#endif
