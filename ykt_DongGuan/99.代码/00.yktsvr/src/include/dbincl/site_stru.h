#ifndef  __T_site_H_
#define  __T_site_H_
typedef struct 
{
		int	siteno;
		char	sitename[60+1];
		char	ip[15+1];
		char	machinecode[60+1];
		char	remark[240+1];
		char	lastsaved[30+1];
}T_t_site;
int DB_t_site_add(T_t_site *pt_site);
int DB_t_site_read_by_siteno(int v_siteno,T_t_site *pt_site);
int DB_t_site_read_by_ip(const char *v_ip,T_t_site *pt_site);
int DB_t_site_update_by_siteno(int v_siteno,T_t_site *pt_site);
int DB_t_site_del_by_siteno(int v_siteno);
int DB_t_site_read_lock_by_c0_and_siteno(int v_siteno,T_t_site *pt_site);
int DB_t_site_update_lock_by_c0(T_t_site *pt_site);
int DB_t_site_free_lock_by_c0();
#endif
