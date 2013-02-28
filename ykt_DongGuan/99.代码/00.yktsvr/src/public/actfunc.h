/* --------------------------------------------
 * 创建日期: 2010-08-10
 * 程序作者: 闻剑
 * 版本信息: 3.0.0.0
 * 程序功能: 财务管理函数模块
 * --------------------------------------------*/
#ifndef ACTFUNC_H_
#define ACTFUNC_H_
#include "cpack.h"
#include "pubdb.h"
#include "acctrans.h"

#define VTSTATUS_MAKE		1	//凭证录入
#define VTSTATUS_CHECK		2	//凭证复核
#define VTSTATUS_ENTRY		3	//凭证入账

#define VTSOURCE_SYSTEM		0	//系统
#define VTSOURCE_MANMADE	1	//手工

#define AUTH_VOUCHERMAKE 	100	//凭证录入
#define AUTH_VOUCHERCHECK 	110	//凭证复核及取消
#define AUTH_VOUCHERBOOK 	120	//凭证入账
#define AUTH_SHOPSUBJECT	130	//科目映射

#define MAPTYPE_CARDACCNO	1	//卡账户
#define MAPTYPE_FORGIFT		2	//押金账户
#define MAPTYPE_INCOMING	8	//收入科目
#define MAPTYPE_PAYMENT		9	//支出科目
int CheckOperAuth(char *opercode,int authtype);
//获取新的凭证号
int GetNewVoucherNo(int periodyear,int periodmonth,int vouchertype,int* voucherno);
//取无效凭证的最小的凭证号
int GetInvalidMinVoucherNo(int vouchertype,int periodyear,int periodmonth,int& voucherno,int& voucherid);
//凭证入账
int VoucherAcctProcess(int voucherid);
int CheckExistUnEntryVoucher(int settledate,int& existflag);
//int GenSuperSubjSubjectMonthData(unsigned int superSubjno);
//int BatchGenSubjectMonth();
int LogoutOper();
//int GetAccShopid(int leafshopid,int* accshopid);
//int GetShopSubjnoByShopid(int shopid,char *subjno);
//int GetSubjnoByMapType(int maptype,char *subjno);
//int UpdShopaccSubjno(int accshopid,char *subjno);
//如果是系统第一次使用，则检查期初余额与当前余额是否相同
int CheckFirstSubjBalBalance();
int VoucherEntryBaseCheck(int vouchertype, int periodyear, int periodmonth, int voucherno);
//凭证号重置
int VouchernoReset(int periodmonth);
int MakeDayStatVoucher();

#endif
