#ifndef _BANK_ACCOUNT_H_
#define _BANK_ACCOUNT_H_

typedef struct {
	// 银行标志
	int bank_code;
	FILE *fp;
	// bank account
	// 银行账号
	char bank_account[21];
	// 账户名
	char account_name[101];
	// 清算起始时间
	char account_date[9];
	// 金额
	double account_money;
	// 
	char comments[101];
	// 借贷标志
	int debit_flag;
}settle_account_t;

typedef struct {
	// 银行标志
	int bank_code;
	// 文件指针
	FILE *fp;
	// 银行账号
	char bank_account[21];
	// 账户名称
	char account_name[101];
	// 清算日期
	char account_date[9];
	// 借贷标志
	int debit_flag;
	// 清算流水号
	int serial_no;
	// 业务代码
	int trans_code;
	// 委托代码
	char trans_no[21];
	// 借总笔数
	int debit_count;
	// 借总金额
	double debit_money;
	// 贷总笔数
	int credit_count;
	// 贷总金额
	double credit_money;
}settle_account_head_t;

#define BANK_CODE_ICBC_SH	1000

int bank_account_write_head(settle_account_head_t *head);
int bank_account_write_detail(settle_account_t *detail);

#endif // _BANK_ACCOUNT_H_

