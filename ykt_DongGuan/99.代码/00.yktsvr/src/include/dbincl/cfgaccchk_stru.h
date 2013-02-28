#ifndef  __T_cfgaccchk_H_
#define  __T_cfgaccchk_H_
typedef struct 
{
		int	accchktype;
		char	accchktypename[30+1];
		char	accchkfilepath[150+1];
		char	accchkexcname[30+1];
		int	bccdrtpno;
		int	bccfuncno;
		int	bcctimeout;
		char	delflag[1+1];
}T_t_cfgaccchk;
int DB_t_cfgaccchk_add(T_t_cfgaccchk *pt_cfgaccchk);
int DB_t_cfgaccchk_read_by_accchktype(int v_accchktype,T_t_cfgaccchk *pt_cfgaccchk);
#endif
