#ifndef  __T_vthdprm_H_
#define  __T_vthdprm_H_
typedef struct 
{
		char	thirdname[20+1];
		char	paraname[20+1];
		char	paraval[128+1];
		char	remark[128+1];
		int	paraflag;
}T_v_thirdpara;
int DB_v_thirdpara_read_by_thirdname_and_paraname(char *v_thirdname,char *v_paraname,T_v_thirdpara *pv_thirdpara);
int DB_v_thirdpara_open_select_by_c0_and_thirdname(char *v_thirdname);
int DB_v_thirdpara_fetch_select_by_c0(T_v_thirdpara *pv_thirdpara);
int DB_v_thirdpara_close_select_by_c0();
#endif
