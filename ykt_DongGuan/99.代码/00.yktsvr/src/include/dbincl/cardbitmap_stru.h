#ifndef  __T_cardbitmap_H_
#define  __T_cardbitmap_H_
typedef struct 
{
		int	cardid;
		int	baseno;
		char	bitmap0[100+1];
		char	bitmap1[100+1];
		char	bitmap2[100+1];
		char	bitmap3[100+1];
		char	bitmap4[100+1];
		char	bitmap5[100+1];
		char	bitmap6[100+1];
		char	bitmap7[100+1];
		char	bitmap8[100+1];
		char	bitmap9[100+1];
}T_t_cardbitmap;
int DB_t_cardbitmap_add(T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_del_by_cardid(int v_cardid);
int DB_t_cardbitmap_read_by_cardid(int v_cardid,T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_update_by_cardid(int v_cardid,T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_read_lock_by_c0_and_cardid(int v_cardid,T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_update_lock_by_c0(T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_free_lock_c0();
#endif
