#ifndef  __T_voucher_H_
#define  __T_voucher_H_
typedef struct 
{
		int	voucherid;
		int	periodyear;
		int	periodmonth;
		int	vouchertype;
		int	voucherno;
		int	voucherdate;
		int	transdate;
		int	totalcnt;
		int	totalamt;
		int	attachments;
		char	summary[60+1];
		int	entrycnt;
		int	datasource;
		int	signflag;
		int	checkflag;
		int	postflag;
		int	invalidflag;
		int	editflag;
		char	preparer[8+1];
		char	cashier[8+1];
		char	checker[8+1];
		char	poster[8+1];
		int	postdate;
		int	branchid;
}T_t_voucher;
int DB_t_voucher_add(T_t_voucher *pt_voucher);
int DB_t_voucher_read_by_voucherid(int v_voucherid,T_t_voucher *pt_voucher);
int DB_t_voucher_update_by_voucherid(int v_voucherid,T_t_voucher *pt_voucher);
int DB_t_voucher_del_by_voucherid(int v_voucherid);
int DB_t_voucher_read_lock_by_c0_and_voucherid(int v_voucherid,T_t_voucher *pt_voucher);
int DB_t_voucher_update_lock_by_c0(T_t_voucher *pt_voucher);
int DB_t_voucher_del_lock_by_c0();
int DB_t_voucher_free_lock_by_c0();
#endif
