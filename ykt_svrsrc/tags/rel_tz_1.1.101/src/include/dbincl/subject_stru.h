#ifndef  __T_subject_H_
#define  __T_subject_H_
typedef struct 
{
		char	subno[20+1];
		char	subname[50+1];
		int	subtype;
		int	direct;
		int	kind;
		char	father[20+1];
		int	level;
		int	endflag;
}T_t_tif_subject;
int DB_t_tif_subject_read_by_subno(char *v_subno,T_t_tif_subject *pt_tif_subject);
int DB_t_tif_subject_open_select_by_c0();
int DB_t_tif_subject_fetch_select_by_c0(T_t_tif_subject *pt_tif_subject);
int DB_t_tif_subject_close_select_by_c0();
#endif
