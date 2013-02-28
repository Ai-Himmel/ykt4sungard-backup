#ifndef  __T_devicetmp_H_
#define  __T_devicetmp_H_
typedef struct 
{
		char	batchno[30+1];
		int	seqno;
		char	transdate[8+1];
		char	transtime[6+1];
		char	opercode[8+1];
		char	areacode[3+1];
		char	devicename[60+1];
		char	devphyid[30+1];
		int	devphytype;
		char	devtypecode[30+1];
		int	deviceno;
		int	fdeviceid;
		char	cardphytype[2+1];
		int	commtype;
		char	ip[15+1];
		int	portno;
		int	svrportno;
		int	svrportcnt;
		int	sysid;
		int	devusage;
		char	errmsg[240+1];
}T_t_devicetmp;
int DB_t_devicetmp_add(T_t_devicetmp *pt_devicetmp);
int DB_t_devicetmp_read_by_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_devicetmp *pt_devicetmp);
int DB_t_devicetmp_update_by_batchno_and_seqno(char *v_batchno,int v_seqno,T_t_devicetmp *pt_devicetmp);
int DB_t_devicetmp_del_by_batchno(const char *v_batchno);
int DB_t_devicetmp_del_by_batchno_and_seqno(const char *v_batchno,int v_seqno);
int DB_t_devicetmp_read_lock_by_c0_and_batchno_and_seqno(const char *v_batchno,int v_seqno,T_t_devicetmp *pt_devicetmp);
int DB_t_devicetmp_update_lock_by_c0(T_t_devicetmp *pt_devicetmp);
int DB_t_devicetmp_free_lock_by_c0();
#endif
