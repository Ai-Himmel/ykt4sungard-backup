#ifndef  __T_cutrelation_H_
#define  __T_cutrelation_H_
typedef struct 
{
		int	cut_id;
		char	outside_no[60+1];
		int	outside_type;
		char	comment[150+1];
}T_t_pif_cut_relation;
int DB_t_pif_cut_relation_add(T_t_pif_cut_relation *pt_pif_cut_relation);
int DB_t_pif_cut_relation_read_by_cut_id_and_outside_type(int v_cut_id,int v_outside_type,T_t_pif_cut_relation *pt_pif_cut_relation);
int DB_t_pif_cut_relation_read_by_cut_id_and_outside_no(int v_cut_id,char *v_outside_no,T_t_pif_cut_relation *pt_pif_cut_relation);
int DB_t_pif_cut_relation_read_lock_by_cur_and_cut_id_and_outside_type(int v_cut_id,int v_outside_type,T_t_pif_cut_relation *pt_pif_cut_relation);
int DB_t_pif_cut_relation_update_lock_by_cur(T_t_pif_cut_relation *pt_pif_cut_relation);
int DB_t_pif_cut_relation_free_lock_by_cur();
int DB_t_pif_cut_relation_del_by_cut_id_and_outside_type(int v_cut_id,int v_outside_type);
#endif
