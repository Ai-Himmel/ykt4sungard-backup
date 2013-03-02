/* ----------------------------------------------------------
 * �������ƣ�balance.h
 * �������ڣ�2004-8-13 9:34
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ʴ���
 * ----------------------------------------------------------
 * �޸�����: 2004-09-08
 * �޸���Ա: ������
 * �޸�����: ͳһ�淶����
 * �汾��Ϣ��1.0.0.1
 * ��ע��Ϣ
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/



#ifdef __cplusplus
extern "C" {
#endif


int StopInBalance(void);
int BackupData();
int BackupAccount();
int CalculateMngFee();
int WithdrowMngFee();
int CardDBNotBalance();
int CheckPersonAccount();
int CheckTotalAccount();
int CreateBankTransFile();
int CommitTransFile();
int ReceiveBankRet();
int CreateActiveReport();
int CreateOperReport();
int CreateShopReport();
int CreateRichDebtReport();
int CreateSubjectBalanceReport();
int CreateBankCompReport();
int CreateTransReport();
int ChangeConfigPara();
int AccountCarryForward1();
int AccountCarryForward();
int DelTradeDate();
int Startup();
int DoFrozenCustomer();
int  PayInCashForOperateGroup();


#ifdef __cplusplus
}
#endif


