#ifndef  __T_fixcardlog_H_
#define  __T_fixcardlog_H_
typedef struct 
{
		int	cardno;
		int	tradecnt;
		char	operate_date[8+1];
		char	physicalno[8+1];
		char	fix_date[8+1];
		double	fix_amt;
		char	oper_code[10+1];
}T_t_pif_fixcard;
int DB_t_pif_fixcard_add(T_t_pif_fixcard *pt_pif_fixcard);
int DB_t_pif_fixcard_read_by_cardno_and_tradecnt_and_operate_date(int v_cardno,int v_tradecnt,char *v_operate_date,T_t_pif_fixcard *pt_pif_fixcard);
#endif
