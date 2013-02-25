#ifndef  __T_subject_H_
#define  __T_subject_H_
typedef struct {
    char	subjno[20+1];
    char	subjname[60+1];
    int	subjtype;
    int	balflag;
    char	fsubjno[20+1];
    int	subjlevel;
    char	endflag[1+1];
} T_t_subject;
int DB_t_subject_read_by_subjno(char *v_subjno,T_t_subject *pt_subject);
int DB_t_subject_open_select_by_c0();
int DB_t_subject_fetch_select_by_c0(T_t_subject *pt_subject);
int DB_t_subject_close_select_by_c0();
int DB_t_subject_open_select_by_c1_and_fsubjno(char *v_fsubjno);
int DB_t_subject_fetch_select_by_c1(T_t_subject *pt_subject);
int DB_t_subject_close_select_by_c1();
#endif
