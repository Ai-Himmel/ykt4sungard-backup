#ifndef  __T_customtmp_H_
#define  __T_customtmp_H_
typedef struct 
{
		char	stuempno[30+1];
		int	custtype;
		int	feetype;
		char	custname[60+1];
		char	areacode[2+1];
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
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_customertmp;
int DB_t_customertmp_add(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_open_select_by_c0_and_batchno(char *v_batchno);
int DB_t_customertmp_fetch_select_by_c0(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_close_select_by_c0();
int DB_t_customertmp_del_by_opercode(char *v_opercode);
int DB_t_customertmp_del_all();
#endif
