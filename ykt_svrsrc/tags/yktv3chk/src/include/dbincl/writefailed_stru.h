#ifndef  __T_writefailed_H_
#define  __T_writefailed_H_
typedef struct 
{
		int	id;
		int	cardno;
		int	serial_no;
		char	tx_date[8+1];
		int	purese_no;
		int	serial_type;
		char	deal_flag[1+1];
		int	deal_serial_no;
		char	deal_date[8+1];
		char	deal_time[6+1];
		char	comments[255+1];
		double	deal_bala;
}T_t_tif_writefailed;
int DB_t_tif_writefailed_add(T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_read_by_cardno_and_purese_no_and_deal_flag(int v_cardno,int v_purese_no,char *v_deal_flag,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_read_by_cardno_and_deal_flag(int v_cardno,char *v_deal_flag,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_read_by_cardno_and_serial_no(int v_cardno,int v_serial_no,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_read_by_cardno_and_serial_type(int v_cardno,int v_serial_type,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_read_by_cardno_and_purese_no_and_deal_serial_no(int v_cardno,int v_purese_no,int v_deal_serial_no,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_update_by_cardno_and_purese_no_and_deal_serial_no(int v_cardno,int v_purese_no,int v_deal_serial_no,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_read_lock_by_cur_and_cardno_and_serial_type(int v_cardno,int v_serial_type,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_update_lock_by_cur(T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_free_lock_by_cur();
int DB_t_tif_writefailed_read_lock_by_c1_and_cardno_and_purese_no_and_deal_flag(int v_cardno,int v_purese_no,char *v_deal_flag,T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_update_lock_by_c1(T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_free_lock_by_c1();
int DB_t_tif_writefailed_open_select_for_update_by_c4_and_cardno_and_serial_type(int v_cardno,int v_serial_type);
int DB_t_tif_writefailed_fetch_select_by_c4(T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_update_lock_by_c4(T_t_tif_writefailed *pt_tif_writefailed);
int DB_t_tif_writefailed_close_select_by_c4();
#endif
