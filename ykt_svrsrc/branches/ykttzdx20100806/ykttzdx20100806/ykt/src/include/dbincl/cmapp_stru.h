#ifndef  __T_cmapp_H_
#define  __T_cmapp_H_
typedef struct 
{
		char	cm_date[10+1];
		char	cm_time[10+1];
		char	cm_card_no[30+1];
		char	cm_serices_no[30+1];
		int	cm_count;
		int	cm_pro;
		int	cm_type;
}T_c_m_applications;
int DB_c_m_applications_add(T_c_m_applications *pc_m_applications);
int DB_c_m_applications_del_by_cm_card_no(char *v_cm_card_no);
int DB_c_m_applications_read_by_cm_card_no_and_cm_pro(char *v_cm_card_no,int v_cm_pro,T_c_m_applications *pc_m_applications);
int DB_c_m_applications_open_select_by_c1_and_cm_pro(int v_cm_pro);
int DB_c_m_applications_fetch_select_by_c1(T_c_m_applications *pc_m_applications);
int DB_c_m_applications_close_select_by_c1();
#endif
