#ifndef  __T_cardstrut_H_
#define  __T_cardstrut_H_
typedef struct 
{
		int	id;
		int	phytype;
		int	sectorno;
		int	blockno;
		int	begin_addr;
		int	end_addr;
		int	bytenum;
		char	define[100+1];
		char	comments[100+1];
}T_t_pif_cardstrut;
int DB_t_pif_cardstrut_add(T_t_pif_cardstrut *pt_pif_cardstrut);
int DB_t_pif_cardstrut_read_by_id(int v_id,T_t_pif_cardstrut *pt_pif_cardstrut);
int DB_t_pif_cardstrut_update_by_id(int v_id,T_t_pif_cardstrut *pt_pif_cardstrut);
int DB_t_pif_cardstrut_del_by_id(int v_id);
int DB_t_pif_cardstrut_open_select_by_c1();
int DB_t_pif_cardstrut_fetch_select_by_c1(T_t_pif_cardstrut *pt_pif_cardstrut);
int DB_t_pif_cardstrut_close_select_by_c1();
#endif
