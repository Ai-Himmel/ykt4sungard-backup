#ifndef  __T_area_H_
#define  __T_area_H_
typedef struct 
{
		int	area_no;
		int	father_area_no;
		char	area_name[50+1];
		int	arealevel;
		char	address[100+1];
		char	comments[100+1];
}T_t_pif_area;
int DB_t_pif_area_read_by_area_no(int v_area_no,T_t_pif_area *pt_pif_area);
#endif
