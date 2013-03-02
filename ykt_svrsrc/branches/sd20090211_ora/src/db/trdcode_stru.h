#ifndef  __T_trdcode_H_
#define  __T_trdcode_H_
typedef struct 
{
		int	tradecode;
		char	trademsg[100+1];
		char	splitcfg[255+1];
		int	flag;
		int	rush_flag;
		int	restrict_oper;
		int	rush_max_day;
}T_t_pif_tradecode;
int DB_t_pif_tradecode_read_by_tradecode(int v_tradecode,T_t_pif_tradecode *pt_pif_tradecode);
#endif
