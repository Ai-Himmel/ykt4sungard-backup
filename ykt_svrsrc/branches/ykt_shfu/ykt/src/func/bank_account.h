#ifndef _BANK_ACCOUNT_H_
#define _BANK_ACCOUNT_H_

typedef struct {
	// ���б�־
	int bank_code;
	FILE *fp;
	// bank account
	// �����˺�
	char bank_account[21];
	// �˻���
	char account_name[101];
	// ������ʼʱ��
	char account_date[9];
	// ���
	double account_money;
	// 
	char comments[101];
	// �����־
	int debit_flag;
}settle_account_t;

typedef struct {
	// ���б�־
	int bank_code;
	// �ļ�ָ��
	FILE *fp;
	// �����˺�
	char bank_account[21];
	// �˻�����
	char account_name[101];
	// ��������
	char account_date[9];
	// �����־
	int debit_flag;
	// ������ˮ��
	int serial_no;
	// ҵ�����
	int trans_code;
	// ί�д���
	char trans_no[21];
	// ���ܱ���
	int debit_count;
	// ���ܽ��
	double debit_money;
	// ���ܱ���
	int credit_count;
	// ���ܽ��
	double credit_money;
}settle_account_head_t;

#define BANK_CODE_ICBC_SH	1000

int bank_account_write_head(settle_account_head_t *head);
int bank_account_write_detail(settle_account_t *detail);

#endif // _BANK_ACCOUNT_H_

