#ifndef  __T_dictionary_H_
#define  __T_dictionary_H_
typedef struct 
{
		int	dicttype;
		char	dicttypename[60+1];
		char	dictval[30+1];
		char	dictcaption[60+1];
}T_t_dictionary;
int DB_t_dictionary_add(T_t_dictionary *pt_dictionary);
int DB_t_dictionary_read_by_dicttype_and_dictval(int v_dicttype,const char *v_dictval,T_t_dictionary *pt_dictionary);
int DB_t_dictionary_update_by_dicttype_and_dictval(int v_dicttype,char *v_dictval,T_t_dictionary *pt_dictionary);
int DB_t_dictionary_del_by_dicttype_and_dictval(int v_dicttype,const char *v_dictval);
int DB_t_dictionary_read_lock_by_c0_and_dicttype_and_dictval(int v_dicttype,const char *v_dictval,T_t_dictionary *pt_dictionary);
int DB_t_dictionary_update_lock_by_c0(T_t_dictionary *pt_dictionary);
int DB_t_dictionary_free_lock_by_c0();
#endif
