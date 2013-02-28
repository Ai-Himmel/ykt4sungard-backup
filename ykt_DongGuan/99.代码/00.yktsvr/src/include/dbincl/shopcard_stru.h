#ifndef  __T_shopcard_H_
#define  __T_shopcard_H_
typedef struct 
{
		int	cardno;
		int	shopid;
		char	cardphyid[16+1];
		char	showcardno[10+1];
		char	expiredate[8+1];
		char	cardpwd[32+1];
		char	status[1+1];
		char	lossflag[1+1];
		char	lossdate[8+1];
		char	opendate[8+1];
		char	closedate[8+1];
		char	lastsaved[30+1];
}T_t_shopcard;
int DB_t_shopcard_add(T_t_shopcard *pt_shopcard);
int DB_t_shopcard_read_by_shopid_and_status(int v_shopid,const char *v_status,T_t_shopcard *pt_shopcard);
int DB_t_shopcard_read_by_cardphyid_and_status(const char *v_cardphyid,const char *v_status,T_t_shopcard *pt_shopcard);
int DB_t_shopcard_read_by_cardno(int v_cardno,T_t_shopcard *pt_shopcard);
int DB_t_shopcard_update_by_cardno(int v_cardno,T_t_shopcard *pt_shopcard);
int DB_t_shopcard_del_by_cardno(int v_cardno);
int DB_t_shopcard_read_lock_by_c0_and_cardno(int v_cardno,T_t_shopcard *pt_shopcard);
int DB_t_shopcard_update_lock_by_c0(T_t_shopcard *pt_shopcard);
int DB_t_shopcard_free_lock_by_c0();
#endif
