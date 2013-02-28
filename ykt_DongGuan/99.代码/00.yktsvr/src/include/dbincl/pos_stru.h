#ifndef  __T_pos_H_
#define  __T_pos_H_
typedef struct 
{
		int	posid;
		char	posno[20+1];
		int	merchid;
		char	areacode[2+1];
		char	devphyid[20+1];
		char	samno[12+1];
		char	termsn[20+1];
		int	termmodel;
		char	termtype[2+1];
		char	termname[60+1];
		int	usage;
		char	status[1+1];
		int	enabledate;
		int	regdate;
		int	deldate;
		char	updtime[14+1];
		char	remark[240+1];
}T_t_pos;
int DB_t_pos_add(T_t_pos *pt_pos);
int DB_t_pos_read_by_posid(int v_posid,T_t_pos *pt_pos);
int DB_t_pos_update_by_posid(int v_posid,T_t_pos *pt_pos);
int DB_t_pos_del_by_posid(int v_posid);
int DB_t_pos_read_lock_by_c0_and_posid(int v_posid,T_t_pos *pt_pos);
int DB_t_pos_update_lock_by_c0(T_t_pos *pt_pos);
int DB_t_pos_del_lock_by_c0();
int DB_t_pos_free_lock_by_c0();
int DB_t_pos_read_lock_by_c1_and_posno(const char *v_posno,T_t_pos *pt_pos);
int DB_t_pos_update_lock_by_c1(T_t_pos *pt_pos);
int DB_t_pos_del_lock_by_c1();
int DB_t_pos_free_lock_by_c1();
#endif
