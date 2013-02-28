#ifndef  __T_specialty_H_
#define  __T_specialty_H_
typedef struct 
{
		char	specialtycode[30+1];
		char	specialtyname[60+1];
		char	useflag[1+1];
		char	lastsaved[30+1];
}T_t_specialty;
int DB_t_specialty_add(T_t_specialty *pt_specialty);
int DB_t_specialty_read_by_specialtycode(const char *v_specialtycode,T_t_specialty *pt_specialty);
int DB_t_specialty_update_by_specialtycode(char *v_specialtycode,T_t_specialty *pt_specialty);
int DB_t_specialty_del_by_specialtycode(const char *v_specialtycode);
int DB_t_specialty_read_lock_by_c0_and_specialtycode(const char *v_specialtycode,T_t_specialty *pt_specialty);
int DB_t_specialty_update_lock_by_c0(T_t_specialty *pt_specialty);
int DB_t_specialty_free_lock_by_c0();
#endif
