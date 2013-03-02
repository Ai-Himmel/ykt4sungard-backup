#ifndef  __T_cmapptmp_H_
#define  __T_cmapptmp_H_
typedef struct 
{
		char	cm_data[10+1];
		char	cm_time[8+1];
		char	cm_card_no[30+1];
		char	cm_serices_no[30+1];
		int	cm_count;
		int	cm_pro;
}T_cmapptmp;
int DB_cmapptmp_add(T_cmapptmp *pcmapptmp);
int DB_cmapptmp_del_by_cm_card_no(char *v_cm_card_no);
int DB_cmapptmp_del_all();
int DB_cmapptmp_read_by_cm_card_no_and_cm_pro(char *v_cm_card_no,int v_cm_pro,T_cmapptmp *pcmapptmp);
int DB_cmapptmp_open_select_by_c2_and_cm_pro(int v_cm_pro);
int DB_cmapptmp_fetch_select_by_c2(T_cmapptmp *pcmapptmp);
int DB_cmapptmp_close_select_by_c2();
#endif
