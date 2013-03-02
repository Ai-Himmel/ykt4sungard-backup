#ifndef  __T_meslist_H_
#define  __T_meslist_H_
typedef struct 
{
		int	mesid;
		int	funid;
		int	stateid;
		int	sendcount;
		int	level;
		int	device_id;
		char	devphy999_id[8+1];
		char	indt[26+1];
		char	startdt[26+1];
		char	enddt[26+1];
		int	ecode;
		char	emsg[100+1];
		char	incontent[800+1];
		char	outcontent[800+1];
		int	pfunid;
		int	card_no;
		int	max_send_cnt;
		char	del_flag[1+1];
}T_t_tif_meslist;
int DB_t_tif_meslist_read_by_mesid(int v_mesid,T_t_tif_meslist *pt_tif_meslist);
int DB_t_tif_meslist_del_by_card_no_and_devphy999_id_and_funid(int v_card_no,char *v_devphy999_id,int v_funid);
int DB_t_tif_meslist_del_by_devphy999_id_and_funid(char *v_devphy999_id,int v_funid);
int DB_t_tif_meslist_del_by_del_flag(char *v_del_flag);
int DB_t_tif_meslist_del_all();
#endif
