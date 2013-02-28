#ifndef  __T_operdtl_H_
#define  __T_operdtl_H_
typedef struct 
{
		int	accdate;
		char	refno[20+1];
		int	operid;
		int	operseqno;
		int	hostdate;
		int	hosttime;
		int	cardno;
		int	amount;
		int	otheramt;
		int	transcode;
		char	transdesc[480+1];
		int	termid;
		char	samno[12+1];
		int	termseqno;
		int	branchid;
		int	chkoperid;
		int	status;
		char	reqdata[1000+1];
}T_t_operdtl;
int DB_t_operdtl_add(T_t_operdtl *pt_operdtl);
int DB_t_operdtl_read_by_accdate_and_refno(int v_accdate,const char *v_refno,T_t_operdtl *pt_operdtl);
int DB_t_operdtl_update_by_accdate_and_refno(int v_accdate,char *v_refno,T_t_operdtl *pt_operdtl);
int DB_t_operdtl_del_by_accdate_and_refno(int v_accdate,const char *v_refno);
int DB_t_operdtl_read_lock_by_c0_and_accdate_and_refno(int v_accdate,const char *v_refno,T_t_operdtl *pt_operdtl);
int DB_t_operdtl_update_lock_by_c0(T_t_operdtl *pt_operdtl);
int DB_t_operdtl_del_lock_by_c0();
int DB_t_operdtl_free_lock_by_c0();
#endif
