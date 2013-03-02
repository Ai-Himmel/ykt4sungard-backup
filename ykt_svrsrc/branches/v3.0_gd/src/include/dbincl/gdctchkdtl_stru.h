#ifndef  __T_gdctchkdtl_H_
#define  __T_gdctchkdtl_H_
typedef struct 
{
		char	refno[32+1];
		char	transdate[8+1];
		char	transtime[6+1];
		char	mobile[20+1];
		double	amount;
		double	amount2;
		int	reverse1;
		int	chkresult;
		char	chkdate[8+1];
		char	chktime[6+1];
}T_t_gdctchkdtl;
int DB_t_gdctchkdtl_add(T_t_gdctchkdtl *pt_gdctchkdtl);
int DB_t_gdctchkdtl_del_by_transdate(char *v_transdate);
#endif
