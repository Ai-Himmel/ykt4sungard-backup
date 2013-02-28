#ifndef  __T_cardaccdiff_H_
#define  __T_cardaccdiff_H_
typedef struct 
{
		int	cardno;
		int	custid;
		char	custname[120+1];
		char	areacode[4+1];
		double	diffamt;
		double	availbal;
		double	lastcardbal;
		int	lastcardcnt;
		char	statdate[8+1];
		char	stattime[6+1];
		char	startdate[8+1];
		char	enddate[8+1];
		int	maxcardcnt;
		double	cardaftbal;
		double	paylossamt;
		double	dpslossamt;
		double	totallossamt;
		int	totallosscnt;
		char	dealdate[8+1];
		char	opercode[8+1];
		char	status[1+1];
		char	remark[480+1];
}T_t_cardaccdiff;
int DB_t_cardaccdiff_add(T_t_cardaccdiff *pt_cardaccdiff);
int DB_t_cardaccdiff_read_by_cardno_and_startdate(int v_cardno,const char *v_startdate,T_t_cardaccdiff *pt_cardaccdiff);
int DB_t_cardaccdiff_update_by_cardno_and_startdate(int v_cardno,char *v_startdate,T_t_cardaccdiff *pt_cardaccdiff);
int DB_t_cardaccdiff_del_by_cardno_and_startdate(int v_cardno,const char *v_startdate);
int DB_t_cardaccdiff_read_lock_by_c0_and_cardno_and_startdate(int v_cardno,const char *v_startdate,T_t_cardaccdiff *pt_cardaccdiff);
int DB_t_cardaccdiff_update_lock_by_c0(T_t_cardaccdiff *pt_cardaccdiff);
int DB_t_cardaccdiff_free_lock_by_c0();
#endif
