#ifndef  __T_attenddtl_H_
#define  __T_attenddtl_H_
typedef struct 
{
		char	transdate[8+1];
		char	transtime[6+1];
		int	deviceid;
		char	devphyid[20+1];
		int	devseqno;
		char	coldate[8+1];
		char	coltime[6+1];
		int	cardno;
		char	cardphyid[8+1];
		char	showcardno[10+1];
		char	stuempno[20+1];
		int	custid;
		char	custname[60+1];
		int	transmark;
		int	status;
}T_t_attenddtl;
int DB_t_attenddtl_add(T_t_attenddtl *pt_attenddtl);
int DB_t_attenddtl_read_by_devphyid(char *v_devphyid,T_t_attenddtl *pt_attenddtl);
int DB_t_attenddtl_update_by_devphyid(char *v_devphyid,T_t_attenddtl *pt_attenddtl);
int DB_t_attenddtl_del_by_devphyid(char *v_devphyid);
int DB_t_attenddtl_read_lock_by_c0_and_devphyid(char *v_devphyid,T_t_attenddtl *pt_attenddtl);
int DB_t_attenddtl_update_lock_by_c0(T_t_attenddtl *pt_attenddtl);
int DB_t_attenddtl_free_lock_by_c0();
#endif
