#ifndef  __T_shop_H_
#define  __T_shop_H_
typedef struct 
{
		int	shopid;
		int	fshopid;
		char	areacode[3+1];
		char	deptcode[30+1];
		char	shopname[60+1];
		int	shoptype;
		char	accflag[1+1];
		char	status[1+1];
		char	accno[10+1];
		char	contactman[60+1];
		char	idtype[1+1];
		char	idno[60+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	email[60+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	boardfeeflag[1+1];
		char	rakeofftype[1+1];
		double	rakeoffrate;
		double	depositagio;
		int	depositcnt;
		double	depositamt;
		double	discountamt;
		char	bankcode[2+1];
		char	bankaccno[20+1];
		char	bankaccname[60+1];
		char	opendate[8+1];
		char	closedate[8+1];
		char	useflag[1+1];
}T_t_shop;
int DB_t_shop_add(T_t_shop *pt_shop);
int DB_t_shop_read_by_shopid(int v_shopid,T_t_shop *pt_shop);
int DB_t_shop_update_by_shopid(int v_shopid,T_t_shop *pt_shop);
int DB_t_shop_del_by_shopid(int v_shopid);
int DB_t_shop_read_lock_by_c0_and_shopid(int v_shopid,T_t_shop *pt_shop);
int DB_t_shop_update_lock_by_c0(T_t_shop *pt_shop);
int DB_t_shop_free_lock_by_c0();
#endif
