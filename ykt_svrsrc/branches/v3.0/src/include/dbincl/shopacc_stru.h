#ifndef  __T_shopacc_H_
#define  __T_shopacc_H_
typedef struct 
{
		char	accno[20+1];
		int	acctype;
		int	shopid;
		char	accname[240+1];
		char	subjno[20+1];
		char	accpwd[64+1];
		char	stoppayflag[1+1];
		char	status[1+1];
		double	ydaybal;
		double	balance;
		double	availbal;
		double	frozebal;
		char	lasttransdate[8+1];
		char	lastaccdate[8+1];
		char	opendate[8+1];
		char	closedate[8+1];
}T_t_shopacc;
int DB_t_shopacc_add(T_t_shopacc *pt_shopacc);
int DB_t_shopacc_read_by_accno(char *v_accno,T_t_shopacc *pt_shopacc);
int DB_t_shopacc_update_by_accno(char *v_accno,T_t_shopacc *pt_shopacc);
int DB_t_shopacc_del_by_accno(char *v_accno);
int DB_t_shopacc_read_lock_by_c0_and_accno(char *v_accno,T_t_shopacc *pt_shopacc);
int DB_t_shopacc_update_lock_by_c0(T_t_shopacc *pt_shopacc);
int DB_t_shopacc_free_lock_by_c0();
#endif
