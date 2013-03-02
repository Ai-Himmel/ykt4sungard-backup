#ifndef  __T_custtmp_H_
#define  __T_custtmp_H_
typedef struct 
{
		char	stuempno[30+1];
		int	custtype;
		int	feetype;
		char	custname[60+1];
		char	areacode[30+1];
		char	deptcode[30+1];
		char	deptname[240+1];
		char	specialtycode[30+1];
		char	classcode[30+1];
		char	idtype[1+1];
		char	idno[60+1];
		char	sex[1+1];
		char	country[3+1];
		char	nation[2+1];
		char	email[60+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	extattr[10+1];
		char	indate[8+1];
		char	outdate[8+1];
		char	batchno[30+1];
		char	impdate[8+1];
		int	impseqno;
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_custtmp;
int DB_t_custtmp_add(T_t_custtmp *pt_custtmp);
int DB_t_custtmp_read_by_stuempno(char *v_stuempno,T_t_custtmp *pt_custtmp);
int DB_t_custtmp_update_by_stuempno(char *v_stuempno,T_t_custtmp *pt_custtmp);
int DB_t_custtmp_del_by_stuempno(char *v_stuempno);
int DB_t_custtmp_read_lock_by_c0_and_stuempno(char *v_stuempno,T_t_custtmp *pt_custtmp);
int DB_t_custtmp_update_lock_by_c0(T_t_custtmp *pt_custtmp);
int DB_t_custtmp_free_lock_by_c0();
#endif
