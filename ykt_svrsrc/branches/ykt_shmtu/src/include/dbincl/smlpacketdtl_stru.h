#ifndef  __T_smlpacketdtl_H_
#define  __T_smlpacketdtl_H_
typedef struct 
{
		int	seqno;
		char	transdate[8+1];
		char	transtime[8+1];
		int	custid;
		int	packettype;
		int	outcardno;
		int	incardno;
		double	smlcardbal;
		int	status;
		char	operatedate[8+1];
		char	operatetime[6+1];
		char	operate[10+1];
}T_t_smlpacketdtl;
int DB_t_smlpacketdtl_add(T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_del_by_seqno(int v_seqno);
int DB_t_smlpacketdtl_read_by_seqno(int v_seqno,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_read_by_custid(int v_custid,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_read_by_incardno_and_status(int v_incardno,int v_status,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_read_by_outcardno(int v_outcardno,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_update_by_outcardno(int v_outcardno,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_read_by_incardno(int v_incardno,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_read_lock_by_cur_and_seqno(int v_seqno,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_update_by_seqno(int v_seqno,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_update_by_incardno(int v_incardno,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_update_by_custid(int v_custid,T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_update_lock_by_cur(T_t_smlpacketdtl *pt_smlpacketdtl);
int DB_t_smlpacketdtl_free_lock_cur();
#endif
