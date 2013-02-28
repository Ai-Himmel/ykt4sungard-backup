#ifndef  __T_subject_H_
#define  __T_subject_H_
typedef struct 
{
		int	subjid;
		unsigned int	subjno;
		char	subjname[60+1];
		char	subjfullname[240+1];
		int	subjclass;
		int	booktype;
		int	property;
		char	helpcode[10+1];
		int	subjlevel;
		int	endflag;
		int	personflag;
		int	companyflag;
		int	deptlag;
		int	itemflag;
		int	sysflag;
		int	cashflag;
		int	bankflag;
		int	closeflag;
		double	draccumamt;
		double	craccumamt;
		int	balflag;
		double	beginbal;
		double	monthdramt;
		double	monthcramt;
		double	yeardramt;
		double	yearcramt;
		double	drbal;
		double	crbal;
}T_t_subject;
int DB_t_subject_add(T_t_subject *pt_subject);
int DB_t_subject_read_by_subjid(int v_subjid,T_t_subject *pt_subject);
int DB_t_subject_update_by_subjid(int v_subjid,T_t_subject *pt_subject);
int DB_t_subject_del_by_subjid(int v_subjid);
int DB_t_subject_read_lock_by_c0_and_subjid(int v_subjid,T_t_subject *pt_subject);
int DB_t_subject_update_lock_by_c0(T_t_subject *pt_subject);
int DB_t_subject_del_lock_by_c0();
int DB_t_subject_free_lock_by_c0();
int DB_t_subject_read_by_subjno(unsigned int v_subjno,T_t_subject *pt_subject);
int DB_t_subject_update_by_subjno(unsigned int v_subjno,T_t_subject *pt_subject);
int DB_t_subject_del_by_subjno(unsigned int v_subjno);
int DB_t_subject_read_lock_by_c1_and_subjno(unsigned int v_subjno,T_t_subject *pt_subject);
int DB_t_subject_update_lock_by_c1(T_t_subject *pt_subject);
int DB_t_subject_del_lock_by_c1();
int DB_t_subject_free_lock_by_c1();
#endif
