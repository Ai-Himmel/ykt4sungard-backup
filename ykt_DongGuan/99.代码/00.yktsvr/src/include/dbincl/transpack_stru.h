#ifndef  __T_transpack_H_
#define  __T_transpack_H_
typedef struct 
{
		char	packetid[20+1];
		char	reqid[20+1];
		int	reqsno;
		int	funcno;
		char	transdate[8+1];
		char	transtime[6+1];
		int	revflag;
		int	retrycnt;
		char	status[1+1];
		int	errcode;
		char	errmsg[240+1];
		char	lastupdtime[30+1];
		int	datalen;
		char	reqdata[2000+1];
		int	termid;
		int	termseqno;
		char	accdate[8+1];
}T_t_transpack;
int DB_t_transpack_add(T_t_transpack *pt_transpack);
int DB_t_transpack_read_by_packetid_and_reqid(const char *v_packetid,const char *v_reqid,T_t_transpack *pt_transpack);
int DB_t_transpack_read_lock_by_c0_and_packetid_and_reqid(const char *v_packetid,const char *v_reqid,T_t_transpack *pt_transpack);
int DB_t_transpack_update_lock_by_c0(T_t_transpack *pt_transpack);
int DB_t_transpack_free_lock_by_c0();
#endif
