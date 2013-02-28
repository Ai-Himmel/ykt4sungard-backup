#ifndef  __T_custidctl_H_
#define  __T_custidctl_H_
typedef struct 
{
		char	areacode[3+1];
		int	startno;
		int	nextno;
		int	endno;
		char	lastsaved[30+1];
}T_t_custidctl;
int DB_t_custidctl_add(T_t_custidctl *pt_custidctl);
int DB_t_custidctl_read_by_areacode(const char *v_areacode,T_t_custidctl *pt_custidctl);
int DB_t_custidctl_update_by_areacode(char *v_areacode,T_t_custidctl *pt_custidctl);
int DB_t_custidctl_del_by_areacode(const char *v_areacode);
int DB_t_custidctl_read_lock_by_c0_and_areacode(const char *v_areacode,T_t_custidctl *pt_custidctl);
int DB_t_custidctl_update_lock_by_c0(T_t_custidctl *pt_custidctl);
int DB_t_custidctl_free_lock_by_c0();
#endif
