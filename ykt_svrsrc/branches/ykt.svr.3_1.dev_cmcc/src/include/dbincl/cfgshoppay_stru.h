#ifndef  __T_cfgshoppay_H_
#define  __T_cfgshoppay_H_
typedef struct 
{
		int	shopid;
		int	feetype;
		int	flag;
		float	payamt;
}T_t_cfgshoppay;
int DB_t_cfgshoppay_read_by_shopid_and_feetype(int v_shopid,int v_feetype,T_t_cfgshoppay *pt_cfgshoppay);
#endif
