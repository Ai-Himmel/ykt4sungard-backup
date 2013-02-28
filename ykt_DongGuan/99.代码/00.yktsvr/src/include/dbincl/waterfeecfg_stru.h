#ifndef  __T_waterfeecfg_H_
#define  __T_waterfeecfg_H_
typedef struct 
{
		int	feeid;
		char	feename[60+1];
		int	purseno;
		int	feemode;
		int	feetypecnt;
}T_t_waterfeecfg;
int DB_t_waterfeecfg_add(T_t_waterfeecfg *pt_waterfeecfg);
int DB_t_waterfeecfg_read_by_feeid(int v_feeid,T_t_waterfeecfg *pt_waterfeecfg);
int DB_t_waterfeecfg_del_by_feeid(int v_feeid);
#endif
