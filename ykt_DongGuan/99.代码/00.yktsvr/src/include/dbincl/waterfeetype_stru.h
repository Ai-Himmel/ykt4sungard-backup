#ifndef  __T_waterfeetype_H_
#define  __T_waterfeetype_H_
typedef struct 
{
		int	feeid;
		int	feetype;
		int	feecnt;
		int	starttime1;
		int	feetime1;
		int	feeamt1;
		int	starttime2;
		int	feetime2;
		int	feeamt2;
		int	starttime3;
		int	feetime3;
		int	feeamt3;
}T_t_waterfeetype;
int DB_t_waterfeetype_add(T_t_waterfeetype *pt_waterfeetype);
int DB_t_waterfeetype_read_by_feeid_and_feetype(int v_feeid,int v_feetype,T_t_waterfeetype *pt_waterfeetype);
int DB_t_waterfeetype_del_by_feeid_and_feetype(int v_feeid,int v_feetype);
int DB_t_waterfeetype_del_by_feeid(int v_feeid);
int DB_t_waterfeetype_open_select_by_c0_and_feeid(int v_feeid);
int DB_t_waterfeetype_fetch_select_by_c0(T_t_waterfeetype *pt_waterfeetype);
int DB_t_waterfeetype_close_select_by_c0();
#endif
