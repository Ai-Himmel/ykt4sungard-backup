#ifndef  __T_phydevice_H_
#define  __T_phydevice_H_
typedef struct 
{
		int	phytype;
		char	dname[30+1];
		char	dtype[30+1];
		char	factory[50+1];
		char	comments[100+1];
}T_t_pif_phydevice;
int DB_t_pif_phydevice_add(T_t_pif_phydevice *pt_pif_phydevice);
int DB_t_pif_phydevice_read_by_phytype(int v_phytype,T_t_pif_phydevice *pt_pif_phydevice);
int DB_t_pif_phydevice_update_by_phytype(int v_phytype,T_t_pif_phydevice *pt_pif_phydevice);
int DB_t_pif_phydevice_del_by_phytype(int v_phytype);
int DB_t_pif_phydevice_open_select_by_c1();
int DB_t_pif_phydevice_fetch_select_by_c1(T_t_pif_phydevice *pt_pif_phydevice);
int DB_t_pif_phydevice_close_select_by_c1();
#endif
