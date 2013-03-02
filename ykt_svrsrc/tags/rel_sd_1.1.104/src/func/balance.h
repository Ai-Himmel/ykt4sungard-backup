/* ----------------------------------------------------------
 * 程序名称：balance.h
 * 创建日期：2004-8-13 9:34
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：结帐处理
 * ----------------------------------------------------------
 * 修改日期: 2004-09-08
 * 修改人员: 韩海东
 * 修改描述: 统一规范代码
 * 版本信息：1.0.0.1
 * 备注信息
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


