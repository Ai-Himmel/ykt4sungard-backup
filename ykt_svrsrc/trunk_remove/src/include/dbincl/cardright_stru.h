#ifndef  __T_cardright_H_
#define  __T_cardright_H_
typedef struct 
{
		int	cardtype;
		int	feetype;
		char	opercode[8+1];
		char	lastsaved[30+1];
}T_t_cardtyperight;
int DB_t_cardtyperight_add(T_t_cardtyperight *pt_cardtyperight);
int DB_t_cardtyperight_read_by_cardtype_and_feetype(int v_cardtype,int v_feetype,T_t_cardtyperight *pt_cardtyperight);
int DB_t_cardtyperight_update_by_cardtype_and_feetype(int v_cardtype,int v_feetype,T_t_cardtyperight *pt_cardtyperight);
int DB_t_cardtyperight_del_by_cardtype_and_feetype(int v_cardtype,int v_feetype);
int DB_t_cardtyperight_read_lock_by_c0_and_cardtype_and_feetype(int v_cardtype,int v_feetype,T_t_cardtyperight *pt_cardtyperight);
int DB_t_cardtyperight_update_lock_by_c0(T_t_cardtyperight *pt_cardtyperight);
int DB_t_cardtyperight_free_lock_by_c0();
int DB_t_cardtyperight_open_select_by_c1_and_cardtype_and_feetype(int v_cardtype,int v_feetype);
int DB_t_cardtyperight_fetch_select_by_c1(T_t_cardtyperight *pt_cardtyperight);
int DB_t_cardtyperight_close_select_by_c1();
#endif
