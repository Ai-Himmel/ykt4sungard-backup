#ifndef  __T_cardistdtl_H_
#define  __T_cardistdtl_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		int	cardno;
		int	oldcardtype;
		char	oldcardphyid[16+1];
		char	oldshowcardno[10+1];
		int	oldcardcnt;
		double	oldcardbal;
		int	oldsubsidyno;
		char	cardphyid[16+1];
		char	showcardno[10+1];
		char	revflag[1+1];
		char	status[1+1];
}T_t_cardinsteaddtl;
int DB_t_cardinsteaddtl_add(T_t_cardinsteaddtl *pt_cardinsteaddtl);
int DB_t_cardinsteaddtl_read_by_cardno(int v_cardno,T_t_cardinsteaddtl *pt_cardinsteaddtl);
int DB_t_cardinsteaddtl_del_by_cardno(int v_cardno);
int DB_t_cardinsteaddtl_read_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno,T_t_cardinsteaddtl *pt_cardinsteaddtl);
int DB_t_cardinsteaddtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_cardinsteaddtl *pt_cardinsteaddtl);
int DB_t_cardinsteaddtl_del_by_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno);
int DB_t_cardinsteaddtl_read_lock_by_c0_and_cardno(int v_cardno,T_t_cardinsteaddtl *pt_cardinsteaddtl);
int DB_t_cardinsteaddtl_update_lock_by_c0(T_t_cardinsteaddtl *pt_cardinsteaddtl);
int DB_t_cardinsteaddtl_free_lock_by_c0();
int DB_t_cardinsteaddtl_open_select_by_c1_and_accdate_and_termid_and_termseqno(const char *v_accdate,int v_termid,int v_termseqno);
int DB_t_cardinsteaddtl_fetch_select_by_c1(T_t_cardinsteaddtl *pt_cardinsteaddtl);
int DB_t_cardinsteaddtl_close_select_by_c1();
#endif
