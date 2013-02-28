#ifndef __DAYSETTLE_H
#define __DAYSETTLE_H
#define SQLCA_STORAGE_CLASS extern
#include <sqlca.h>
#include "actfunc.h"
EXEC SQL BEGIN DECLARE SECTION;
	typedef struct
	{
		int 	voucherid;		//返回值
		int 	voucherdate;	//凭证日期
		int 	transdate;		//发生日期
		char	drdesc[61]; 	//摘要
		unsigned int subjno;	//科目号
		unsigned int oppsubjno; //对方科目
		int 	transtype;		//交易类型
		int 	transcnt;		//交易次数
		int 	transamt;		//交易金额
		char	crdesc[61]; 	//摘要2
	} DB_VOUCHERDATA;
	typedef struct
	{
		unsigned int subjno;		//科目号
		char subjname[61];
		int balflag;
		int subjclass;
		int subjlevel;
		int endflag;
		int beginbal;
		int dramt;
		int cramt;
		int monthdramt;
		int monthcramt;
		int yeardramt;
		int yearcramt;
		int drbal;
		int crbal;
	} DB_SUBJECT;
EXEC SQL END DECLARE SECTION;
typedef struct
{
	int transcode;
	int merchid;
	int transdate;
	int transcnt;
	int transamt;
	int feeamt;
} tagDAYSTAT;
typedef vector<tagDAYSTAT> DAYSTATVECT;

typedef vector<DB_VOUCHERDATA>	VECTVOUCHERDATA;
typedef vector<DB_SUBJECT> VECTSUBJECT;
class CDaySettle
{
private:
	EXEC SQL BEGIN DECLARE SECTION;
		int  _hostdate;
		int  _statdate;
		int  _batchdate;
		int  _accdate;		
		int   _settledate;
		int   _periodyear;
		int   _periodmonth;
		int   _merchid;
		char  _merchno[21];
		char  _merchname[91];
		double _feerate;
		sqlint16 _indicator;
	EXEC SQL END DECLARE SECTION;
	char _errmsg[256];
public:
	CDaySettle();
	bool IsSettled(int allowflag=0);
     	bool IsStated();
	bool IsEnableSettle();
	bool CanStat();
	char* GetErrMsg(){ return _errmsg;}; 
	int  SetSettleFlag();
	int ResetSettleFlag();
	int CheckForgitBalance();
	int CheckMerchBala();
	int CheckCardBala();
	int CheckSubjBalBalance();
	int CheckBala();
	int StatDayData();
//	int GetVoucherEntryVect(int voucherid, VECTVOUENTRY* VectVoucherEntry);
//	int VoucherEntryBatchAcc(const T_t_voucher& tVoucher,const  VECTVOUENTRY& VectVoucherEntry);
//	int VoucherAcctProcess(int voucherid);
	int SysVoucherMake(DB_VOUCHERDATA& VoucherData);
	int GenVoucher();
	int MakeDayStatVoucher();
	int GetSubjectVect(VECTSUBJECT* VectSubject, int endflag);
	int GetDayAccSubjVect(DAYSTATVECT* daystatvect);
	int GetDayAccMerchVect(DAYSTATVECT* daystatvect);
	int StatSubjDrAmtAndCrAmt(unsigned int subjno, int settledate, int* dramt,int* cramt);
	int GenEndSubjSubjectDayData(const DB_SUBJECT& dbSubject, T_t_subjectday* subjectday);
	int GenSuperSubjSubjectDayData(unsigned int superSubjno);
	int BatchGenMerchDay(T_t_subjectday* merchdaySum);
	int BatchGenSubjectDay();
	int StatSubjMonthDrAmtAndCrAmt(unsigned int subjno, int periodyear, int periodmonth, double* dramt, double* cramt);
	int GenEndSubjSubjectMonthData(const DB_SUBJECT& dbSubject, T_t_subjectmonth* subjectmonth);
	int GenSuperSubjSubjectMonthData(unsigned int superSubjno);
	int BatchGenSubjectMonth();
	int BatchMakeVoucher();
	int GetMerchVect(VECTSUBJECT* VectMerch);
	int GenMerchDayData(const DB_SUBJECT& dbSubject, T_t_merchday* merchday);
	int BatchGenMerchDay(T_t_merchday* merchdaySum);
	int VouchernoReset(int periodmonth);
	int SettleProcess();
	int LogoutOper();
};
#endif
