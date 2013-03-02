#ifndef  __T_cfgsplit_H_
#define  __T_cfgsplit_H_
typedef struct 
{
		int	txtype;
		char	txname[60+1];
		int	dbflag;
		int	crflag;
		char	dbsubno[20+1];
		char	crsubno[20+1];
		char	dbactno[30+1];
		char	cractno[30+1];
		int	fundtype;
}T_t_tif_cfgsplit;
int DB_t_tif_cfgsplit_open_select_by_c0();
int DB_t_tif_cfgsplit_fetch_select_by_c0(T_t_tif_cfgsplit *pt_tif_cfgsplit);
int DB_t_tif_cfgsplit_close_select_by_c0();
#endif
