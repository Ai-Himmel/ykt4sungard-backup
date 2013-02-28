#ifndef  __T_custtmp_H_
#define  __T_custtmp_H_
typedef struct 
{
		char	batchno[30+1];
		int	seqno;
		char	transdate[8+1];
		char	opercode[8+1];
		char	stuempno[30+1];
		int	custtype;
		char	custtypename[60+1];
		int	feetype;
		char	custname[60+1];
		char	areacode[3+1];
		char	deptcode[30+1];
		char	deptname[240+1];
		char	specialtycode[30+1];
		char	classname[60+1];
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
		char	indate[8+1];
		char	outdate[8+1];
		int	syncflag;
		int	chkflag;
		char	errmsg[240+1];
}T_t_customertmp;
int DB_t_customertmp_add(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_read_by_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_customertmp *pt_customertmp);
int DB_t_customertmp_update_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_customertmp *pt_customertmp);
int DB_t_customertmp_del_by_batchno_and_seqno(const char *v_batchno,int v_seqno);
int DB_t_customertmp_read_lock_by_c0_and_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_customertmp *pt_customertmp);
int DB_t_customertmp_update_lock_by_c0(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_del_lock_by_c0();
int DB_t_customertmp_free_lock_by_c0();
int DB_t_customertmp_read_by_idtype_and_idno(const char *v_idtype,const char *v_idno,T_t_customertmp *pt_customertmp);
int DB_t_customertmp_read_by_stuempno(const char *v_stuempno,T_t_customertmp *pt_customertmp);
int DB_t_customertmp_del_by_batchno(const char *v_batchno);
int DB_t_customertmp_open_select_by_c1_and_batchno(const char *v_batchno);
int DB_t_customertmp_fetch_select_by_c1(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_close_select_by_c1();
int DB_t_customertmp_open_select_for_update_by_c2_and_syncflag_and_chkflag(int v_syncflag,int v_chkflag);
int DB_t_customertmp_fetch_select_by_c2(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_update_select_by_c2(T_t_customertmp *pt_customertmp);
int DB_t_customertmp_close_select_by_c2();
#endif
