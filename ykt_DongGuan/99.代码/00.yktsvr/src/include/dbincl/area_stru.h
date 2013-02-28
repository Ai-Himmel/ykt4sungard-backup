#ifndef  __T_area_H_
#define  __T_area_H_
typedef struct 
{
		char	areacode[3+1];
		char	areaname[60+1];
		char	fareacode[3+1];
		int	arealevel;
		char	addr[240+1];
		char	remark[240+1];
}T_t_area;
int DB_t_area_add(T_t_area *pt_area);
int DB_t_area_read_by_areacode(const char *v_areacode,T_t_area *pt_area);
int DB_t_area_update_by_areacode(char *v_areacode,T_t_area *pt_area);
int DB_t_area_del_by_areacode(const char *v_areacode);
int DB_t_area_read_lock_by_c0_and_areacode(const char *v_areacode,T_t_area *pt_area);
int DB_t_area_update_lock_by_c0(T_t_area *pt_area);
int DB_t_area_free_lock_by_c0();
#endif
