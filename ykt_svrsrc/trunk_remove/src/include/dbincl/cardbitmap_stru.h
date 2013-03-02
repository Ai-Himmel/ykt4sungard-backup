#ifndef  __T_cardbitmap_H_
#define  __T_cardbitmap_H_
typedef struct 
{
		int	cardno;
		int	baseno;
		char	bitmap[2000+1];
}T_t_cardbitmap;
int DB_t_cardbitmap_add(T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_del_by_cardno(int v_cardno);
int DB_t_cardbitmap_read_by_cardno(int v_cardno,T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_update_by_cardno(int v_cardno,T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_read_lock_by_cur_and_cardno(int v_cardno,T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_update_lock_by_cur(T_t_cardbitmap *pt_cardbitmap);
int DB_t_cardbitmap_free_lock_cur();
#endif
