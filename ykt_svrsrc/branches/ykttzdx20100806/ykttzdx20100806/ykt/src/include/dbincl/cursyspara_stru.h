#ifndef  __T_cursyspara_H_
#define  __T_cursyspara_H_
typedef struct 
{
		int	id;
		char	para_name[20+1];
		char	value[50+1];
		char	usetime[27+1];
		char	optime[27+1];
		char	unit[10+1];
		char	comments[100+1];
}T_t_pif_cur_syspara;
int DB_t_pif_cur_syspara_add(T_t_pif_cur_syspara *pt_pif_cur_syspara);
int DB_t_pif_cur_syspara_del_by_id(int v_id);
int DB_t_pif_cur_syspara_read_by_id(int v_id,T_t_pif_cur_syspara *pt_pif_cur_syspara);
int DB_t_pif_cur_syspara_update_by_id(int v_id,T_t_pif_cur_syspara *pt_pif_cur_syspara);
#endif
