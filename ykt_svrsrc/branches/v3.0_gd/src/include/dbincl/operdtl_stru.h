#ifndef  __T_operdtl_H_
#define  __T_operdtl_H_
typedef struct 
{
		char	accdate[8+1];
		int	termid;
		int	termseqno;
		char	opercode[8+1];
		char	transdate[8+1];
		char	transtime[6+1];
		int	transcode;
		char	chkoper[8+1];
		char	status[1+1];
		char	transinfo[500+1];
		char	reqdata[1000+1];
}T_t_operdtl;
int DB_t_operdtl_add(T_t_operdtl *pt_operdtl);
int DB_t_operdtl_read_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_operdtl *pt_operdtl);
int DB_t_operdtl_update_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_operdtl *pt_operdtl);
int DB_t_operdtl_del_by_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno);
int DB_t_operdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(char *v_accdate,int v_termid,int v_termseqno,T_t_operdtl *pt_operdtl);
int DB_t_operdtl_update_lock_by_c0(T_t_operdtl *pt_operdtl);
int DB_t_operdtl_free_lock_by_c0();
#endif
