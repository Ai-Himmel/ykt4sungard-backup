#ifndef  __T_custtmp_H_
#define  __T_custtmp_H_
typedef struct 
{
		char	stuemp_no[30+1];
		char	cut_name[60+1];
		int	cut_type;
		char	sex[1+1];
		int	id_type;
		char	id_no[60+1];
		char	country[30+1];
		int	people;
		char	addr[240+1];
		char	tel[30+1];
		char	email[60+1];
		int	area_no;
		char	dept_no[30+1];
		char	specialty_no[30+1];
		char	class_no[30+1];
		char	at_school_status[1+1];
		char	in_school_date[8+1];
		char	out_school_date[8+1];
		char	imp_date[8+1];
		char	imp_oper[10+1];
		int	imp_seqno;
		char	imp_batchno[14+1];
		char	imp_status[1+1];
}T_t_customertmp;
int DB_t_customertmp_add(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_read_by_stuemp_no(char *v_stuemp_no,T_t_customertmp *pt_customertmp);
int DB_t_customertmp_read_lock_by_c0_and_stuemp_no(char *v_stuemp_no,T_t_customertmp *pt_customertmp);
int DB_t_customertmp_update_lock_by_c0(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_free_lock_by_c0();
int DB_t_customertmp_open_select_by_c1_and_imp_batchno(char *v_imp_batchno);
int DB_t_customertmp_fetch_select_by_c1(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_close_select_by_c1();
int DB_t_customertmp_del_by_stuemp_no(char *v_stuemp_no);
#endif
