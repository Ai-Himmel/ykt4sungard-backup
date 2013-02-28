#ifndef  __T_bankchkdtl_H_
#define  __T_bankchkdtl_H_
typedef struct 
{
		int	bankid;
		int	bankdate;
		int	recordno;
		double	amount;
		int	transdate;
		char	chkresult[1+1];
		char	resolved[1+1];
		char	remark[240+1];
		char	localsno[20+1];
		char	banksno[20+1];
		char	bankcardno[20+1];
		int	cardno;
		int	custid;
		char	stuempno[20+1];
		char	opercode[8+1];
}T_t_bankchkdtl;
int DB_t_bankchkdtl_add(T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_read_by_bankid_and_bankdate_and_recordno(int v_bankid,int v_bankdate,int v_recordno,T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_update_by_bankid_and_bankdate_and_recordno(int v_bankid,int v_bankdate,int v_recordno,T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_del_by_bankid_and_bankdate_and_recordno(int v_bankid,int v_bankdate,int v_recordno);
int DB_t_bankchkdtl_read_lock_by_c0_and_bankid_and_bankdate_and_recordno(int v_bankid,int v_bankdate,int v_recordno,T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_update_lock_by_c0(T_t_bankchkdtl *pt_bankchkdtl);
int DB_t_bankchkdtl_del_lock_by_c0();
int DB_t_bankchkdtl_free_lock_by_c0();
#endif
