#ifndef  __T_cmfunclist_H_
#define  __T_cmfunclist_H_
typedef struct 
{
		int	cu_serices_type;
		char	cu_serices_no[30+1];
		char	cu_card_no[30+1];
		int	cu_client_no;
		char	cu_date[10+1];
		char	cu_time[10+1];
		int	cu_count;
		int	cu_state;
}T_custem_functions;
int DB_custem_functions_add(T_custem_functions *pcustem_functions);
int DB_custem_functions_read_by_cu_card_no(char *v_cu_card_no,T_custem_functions *pcustem_functions);
int DB_custem_functions_open_select_by_c1_and_cu_card_no(char *v_cu_card_no);
int DB_custem_functions_fetch_select_by_c1(T_custem_functions *pcustem_functions);
int DB_custem_functions_close_select_by_c1();
#endif
