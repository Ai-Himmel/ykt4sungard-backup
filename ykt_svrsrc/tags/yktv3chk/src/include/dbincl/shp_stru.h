#ifndef  __T_shp_H_
#define  __T_shp_H_
typedef struct 
{
		int	shopid;
		char	areacode[2+1];
		char	deptcode[30+1];
		char	shopname[60+1];
		int	shoptype;
		char	openaccflag[1+1];
		char	accflag[1+1];
		char	status[1+1];
		char	accno[30+1];
		char	linkman[60+1];
		char	sex[1+1];
		char	idtype[1+1];
		char	idno[60+1];
		char	tel[30+1];
		char	mobile[30+1];
		char	email[60+1];
		char	addr[240+1];
		char	zipcode[6+1];
		char	opendate[8+1];
		char	closedate[8+1];
		char	rakeofftype[1+1];
		int	rakeoffrate;
		int	depositagio;
}T_t_shop;
int DB_t_shop_add(T_t_shop *pt_shop);
int DB_t_shop_del_by_shopid(int v_shopid);
int DB_t_shop_read_by_shopid(int v_shopid,T_t_shop *pt_shop);
int DB_t_shop_read_lock_by_cur1_and_shopid(int v_shopid,T_t_shop *pt_shop);
int DB_t_shop_update_by_shopid(int v_shopid,T_t_shop *pt_shop);
int DB_t_shop_update_lock_by_cur1(T_t_shop *pt_shop);
int DB_t_shop_free_lock_cur1();
int DB_t_shop_open_select_by_cur2_and_deptcode(char *v_deptcode);
int DB_t_shop_fetch_select_by_cur2(T_t_shop *pt_shop);
int DB_t_shop_close_select_by_cur2();
int DB_t_shop_open_select_by_cur3_and_openaccflag(char *v_openaccflag);
int DB_t_shop_fetch_select_by_cur3(T_t_shop *pt_shop);
int DB_t_shop_close_select_by_cur3();
int DB_t_shop_open_select_by_cur4();
int DB_t_shop_fetch_select_by_cur4(T_t_shop *pt_shop);
int DB_t_shop_close_select_by_cur4();
int DB_t_shop_del_all();
#endif
