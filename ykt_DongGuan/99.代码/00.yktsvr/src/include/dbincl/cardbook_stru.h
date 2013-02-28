#ifndef  __T_cardbook_H_
#define  __T_cardbook_H_
typedef struct 
{
		char	showcardno[10+1];
		int	cardtype;
		char	cardphyid[16+1];
		char	opercode[8+1];
		char	putopercode[8+1];
		char	batchno[30+1];
		char	getdate[8+1];
		char	usedate[8+1];
		char	reclaimdate[8+1];
		int	usestatus;
}T_t_cardbook;
int DB_t_cardbook_add(T_t_cardbook *pt_cardbook);
int DB_t_cardbook_read_by_showcardno(const char *v_showcardno,T_t_cardbook *pt_cardbook);
int DB_t_cardbook_update_by_showcardno(char *v_showcardno,T_t_cardbook *pt_cardbook);
int DB_t_cardbook_del_by_showcardno(const char *v_showcardno);
int DB_t_cardbook_read_lock_by_c0_and_showcardno(const char *v_showcardno,T_t_cardbook *pt_cardbook);
int DB_t_cardbook_update_lock_by_c0(T_t_cardbook *pt_cardbook);
int DB_t_cardbook_free_lock_by_c0();
#endif
