/* --------------------------------------------
 * 创建日期: 2008-06-15
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 账务处理
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#ifndef ACCTRANS_H_
#define ACCTRANS_H_
#include "transcode.h"
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include "compare.h"
using namespace std;

#define TERMID_WEB			1 //web
#define TERMID_TEL			2 //电话终端
#define TERMID_SVR		    4 //管理中心
#define TERMID_SYSTEM		5//结算中心

#define LOGFLAG_NONE 0		//不记录流水
#define LOGFLAG_SUCC 1		//只记录成功交易流水
#define LOGFLAG_FAIL 2		//只记录失败交易流水
#define LOGFLAG_ALL  3		//全部记录(包含成功和失败)

#define ACCTYPE_CARD  1			//持卡人卡帐户
#define ACCTYPE_SHOP  2			//商户账号
#define ACCTYPE_EACC  3			//电子钱包账户
#define ACCTYPE_INNER 4			//内部帐户

typedef enum {
	CS_NORMAL=1,	     // 卡状态正常 
	CS_LOST,    	     // 卡状态挂失
	CS_FROZEN,  	     // 卡状态冻结
	CS_BAD,     	     // 卡状态坏卡
	CS_LOCKED,  	     // 卡状态锁定
                	                     
	CS_CLOSED,  	     // 卡状态注销
	CS_UNLOST,  	     // 卡状态未挂失
	CS_UNFROZEN,	     // 卡状态未冻结
	CS_UNBAD,   	     // 卡状态非坏卡
	CS_UNLOCKED, 	     // 卡状态未锁定

	CS_EXPIREDATE,		// 卡有效期
	CS_LOSSDATE,		// 卡挂失时间
	CS_FROZEDATE,		// 卡冻结时间
	CS_BADDATE,			// 卡登记坏卡时间
	CS_LOCKDATE,		// 卡锁定时间
	CS_OPENDATE,		// 开卡时间
	CS_CLOSEDATE,		// 注销时间

}CARD_STATUS;

#define TYPE_INPUT  1
#define TYPE_CONFIG 2
#define ACCFLAG_CARD   'C'		//卡账户
#define ACCFLAG_EACC   'E'		//电子账户
#define ACCFLAG_SHOP   'S'		//商户
#define ACCFLAG_INNER  'N'		//内部固定账户
#define ACCFLAG_INNER_INPUT  'X' //内部固定账户
#define ACCFLAG_FIX    'F'		//固定账户
#define ACCFLAG_INPUT  'I'		//输入账户

#define SUBJECT_CASH				"1001"			//现金
#define SUBJECT_BANKACC				"1002"			//银行存款
#define SUBJECT_SHEET				"1121"			//应收票据
#define SUBJECT_SHEET_BILL			"112101"		//应收票据-支票
#define SUBJECT_SHEET_OUTLAY		"112102"		//应收票据-经费本
#define SUBJECT_CARDSAVING			"2001"			//卡户存款
#define SUBJECT_CARDFOREGIFT		"2002"			//卡户押金
#define SUBJECT_ESAVING				"2003"			//电子帐户存款
#define SUBJECT_SHOPINCOME			"2004"			//商户营业收入
#define SUBJECT_SHOPSAVING			"2005"			//商户存款
#define SUBJECT_PROFIT  			"4001"			//本年利润
#define SUBJECT_INCOME  			"6001"          //营业外收入 
#define SUBJECT_INCOME_FEE  		"6002"          //手续费收入
#define SUBJECT_INCOME_RAKEOFF 	 	"6003"          //佣金收入 
#define SUBJECT_INCOME_BOARD  		"6004"          //搭伙费收入
#define SUBJECT_INCOME_CARDCOST  	"6005"          //卡成本费收入
#define SUBJECT_INCOME_BACKCARDBAL  "6006"          //退卡盈余收入
#define SUBJECT_INCOME_DEPRFEE  	"6007"          //折旧费收入
#define SUBJECT_OUT   				"6201"			//营业外支出 
#define SUBJECT_OUT_SHOP_DISCOUNT   "6202"			//商户提成支出

//201-204 持卡人交易类-
#define TRANSTYPE_ISSUESAVING			200	//发卡充值
#define TRANSTYPE_CARDSAVING			201	//持卡人存款
#define TRANSTYPE_CARDSHOPSAVING		202	//持卡人存款(充值商户)
#define TRANSTYPE_CARDSUBSIDY			203 //卡户补助
#define TRANSTYPE_BANKTRANS				204 //银行圈存转账
#define TRANSTYPE_WATERREFUND			205	//水控退款
#define TRANSTYPE_ACCSUBSIDY			206 //补助，下发到待领补助
#define TRANSTYPE_GETSUBSIDY			207 //从待领补助领取
#define TRANSTYPE_BANKSUBSIDY			208	//网银补助
#define TRANSTYPE_WATERNOBALAREFUND		209	//水控不平金额退款
#define TRANSTYPE_BANKCHKADD			210	//圈存补帐

#define TRANSTYPE_CARDDRAW				231	//持卡人取款
#define TRANSTYPE_POSPAYMENT			232	//POS消费
#define TRANSTYPE_CARDPAYMENT			233	//支付交易
#define TRANSTYPE_CLOSEDRAW		   		234 //消费退款
#define TRANSTYPE_WATERTRANS			235	//水控转账
#define TRANSTYPE_POSPAYCANCEL			236	//消费取消
#define TRANSTYPE_CARD2CARD				237	//卡卡转账
#define TRANSTYPE_WATERDEPOSIT			238	//水控充值
#define TRANSTYPE_WATERDRAW				239	//水控消费
#define TRANSTYPE_WATERPAY				240 //后付费补扣

//电子账户类41-50				
#define TRANSTYPE_EACCSAVING    		241  //电子账户存款
#define TRANSTYPE_CARD2EACC     		242  //电子账户转账(卡到电子账户)
#define TRANSTYPE_BANK2EACC     		243  //电子账户圈存(银行卡到电子账户)

#define TRANSTYPE_EACCDRAW				251  //电子账户取款
#define TRANSTYPE_EACC2CARD				252  //电子账户转账到卡(电子账户到卡)
#define TRANSTYPE_EACCPAYMENT			253  //支付交易

//充值商户类51-59
#define TRANSTYPE_DEPOSITSHOPSAV		261  //充值商户存款
#define TRANSTYPE_DEPOSITSHOPSAVDISCNT	262  //充值商户存款提成
#define TRANSTYPE_DEPOSITSHOPDRAW		271  //充值商户取款
#define TRANSTYPE_DEPOSITSHOPDRAWDISCNT	272  //充值商户退提成
//收费商户类61-70
#define TRANSTYPE_SHOPBOARDFEE			281	 //商户收搭伙费
#define TRANSTYPE_SHOPBOARDFEE2			283	// 商户收搭伙费(预收模式，流水上来后结算给商户)
#define TRANSTYPE_SHOPPAYMENT			290	 //商户解款

#define TRANSTYPE_RETURNBOARDFEE		291	 //商户退搭伙费
#define TRANSTYPE_SHOPREFUND			292	 //商户退款
#define TRANSTYPE_SHOPDRAW				293  //商户取款

//利润
#define TRANSTYPE_PROFIT				401	//本年利润
//601-620
#define TRANSTYPE_FOREGIFT				601	//收押金
#define TRANSTYPE_CARDCOSTFEE   		602	//收卡成本费
#define TRANSTYPE_POUNDAGE				603	//收手续费
#define TRANSTYPE_BOARDFEE				604	//学校收搭伙费
#define TRANSTYPE_DEPRFEE				605 //收折旧费
//621-640
#define TRANSTYPE_RETURNFOREGIFT		621	//退还押金
#define TRANSTYPE_RETURNCARDCOSTFEE		622 //退卡成本费
#define TRANSTYPE_RETURNPOUNDAGE		623 //退手续费
#define TRANSTYPE_RETURNADVBOARDFEE     624 //退学校搭伙费
#define TRANSTYPE_RETURNDEPRFEE			625 //退折旧费

#define TRANSTYPE_FOREGIFT2COSTFEE		631	//卡押金转成本费收入
#define TRANSTYPE_CARDBAL2COSTFEE		632 //卡余额转卡成本费收入
#define TRANSTYPE_CARDBAL2FORGIFT		633 //卡余额转卡押金
//长款处理-641-650
#define TRANSTYPE_MORE_CARDBAL			641  //卡余额转退卡盈余
#define TRANSTYPE_MORE_POSPAYMENT		642  //消费流水发生额长款(针对无商户流水)
#define TRANSTYPE_MORE_SHOPBOARDFEE		643  //消费流水搭伙费长款(针对无商户流水)
#define TRANSTYPE_MORE_CARDBALINCOME	644  //卡余额转营业外收入
#define TRANSTYPE_DEDUCTMONEY			645  //扣款补助

//短款处理651-660
#define TRANSTYPE_LESS_CARDBAL			651	//退卡损益转-卡余额
#define TRANSTYPE_LESS_POSPAYMENT		652  //消费流水发生额短款(针对挂失或注销卡)
#define TRANSTYPE_LESS_SHOPBOARDFEE		653  //消费流水搭伙费短款(针对挂失或注销卡),如果是商户收搭伙费的情况
#define TRANSTYPE_LESS_SCHOOLBOARDFEE	654  //消费流水搭伙费短款(针对挂失或注销卡),如果是学校收搭伙费的情况
#define TRANSTYPE_LESSOUT2MOREIN		655  //在商户和卡户都注销的情况下,流水从营业外支出到营业外收入
//其他80-98
#define TRANSTYPE_MANDRCR				700	//手工借贷
#define TRANSTYPE_SHOPRAKEOFF			900	//佣金划拨

#define OPERRIGHT_SYSTEM				0 //只有系统操作员才能使用
#define OPERRIGHT_CHECK					1 //审核操作员才能使用
#define OPERRIGHT_OPER					2 //操作员才能使用

const int  SEQNO_BANK = -1;				//银行圈存
const int  SEQNO_RECORD= -2;			//记录号
const int  SEQNO_HOSTNO = -5;			//主机流水号
const int  SEQNO_REFNO = -10;			//一卡通使用
const int  SEQNO_MEDICAL=-20;			//医疗系统

const int MAXAMT_CARDGTACC=200;			//卡比库大不平允许最大金额
#define RS_INIT			0		//初始状态
#define RS_FAIL			1		//交易失败状态
#define RS_SUCC			2		//交易成功
#define RS_WAITREV  	3		//一卡通后台待冲正
#define RS_YKTREVSUCC	4		//银行方待冲正
#define RS_REVSUCC		5		//全部冲正成功

typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short	WORD;
#define MAKELONG(feetype,funtype)   ((LONG)(((WORD)(feetype)) | ((DWORD)((WORD)(funtype))) << 16))
#define TIPINFO 	CAccTrans::getInstance()->SetTip
#define ERRTIP 		CAccTrans::getInstance()->SetErrTip
#define ERRINFO 	getpos(__FILE__,__LINE__),CAccTrans::getInstance()->SetErrMsg
//typedef struct {
//	int  cardflag;		//有无卡标志
//	int  cardtype;		//卡类型
//	int  feetype;		//收费类型
//	int  cardno;		//卡号
//	int  purseno;		//钱包号
//	int  cardcnt;		//卡交易次数
//	double  cardbefbal;	//交易前卡余额
//	double  cardaftbal;	//交易后卡余额
//	int  befbalflag;	//0-无入卡值1-有入卡值
//	int  aftbalflag;	//0-无出卡值，1-有出卡值
//	int  calaftbalflag;	//是否需要计算出卡值0-不计算1-计算
//	double  transamt;	//交易金额
//	double  managefee;	//管理费
//	char transdate[9];	//交易日期
//	char transtime[7];	//交易时间
//	char collectdate[9];//采集日期
//	char collecttime[7];//采集时间
//	char cardphyid[17];	//卡物理ID
//	char devphyid[31];  //设备物理ID
//	int  devseqno;		//设备流水号
//	char cardaccno[21];	//卡账号
//}CARDTRANSINFO;


typedef struct
{
    int feetype;
    int transtype;
    int ratetype;
    double rateamt;
    char remark[241];
}CfgFee;
typedef struct
{
    int	transtype;
    int	ratetype;
    double	rateamt;
    char remark[241];
}CfgTrans;

typedef struct
{
    int transcode;		//交易码
    int  termid;		//终端编号
    int  termseqno; 	//终端流水号
    char accdate[9];	//记账日期
    char acctime[7];	//记账时间
    char transdate[9];	//交易日期
    char transtime[7];	//交易时间
    char opercode[9];	//操作员号
    int  cardno;		//交易卡号
    int  cardflag;		//有无卡标志 1-有卡交易0-无卡交易

}BASETRANSINFO;
typedef struct
{
    int  transcode;		//交易码
    char refno[21];		//交易参考号
    int  revflag;		//0-正常交易1-冲正交易
    int  termid;		//终端编号
    int  termsno;		//终端发送方流水号
	int  termseqno; 	//终端主机流水号
    char accdate[9];	//记账日期
    char acctime[7];	//记账时间
    char transdate[9];	//交易日期
    char transtime[7];	//交易时间
    char sysdatetime[15];//系统时间 yyyymmddhhmiss
    int  branchno;		//操作员网点号
    int  loginsiteno;	//当前登录的站点
    char opercode[9];	//操作员号
    char chkopercode[9];//审核操作员
    int  offlineflag;	//是否联机交易1-脱机交易0-联机交易
    int  usecardflag;	//1与卡有关系的交易0-与卡无关系的交易
    int  cardflag;		//有无卡标志(1有卡交易0无卡交易)
    int  calccardbalflag;//计算卡余额标志
    int  cardtype;		//卡类型
    int  cardphytype;	//卡物理类型
    char cardphyid[17];	//物理卡号
    char cardpwd[9];	//卡密码
    int  cardno;		//卡号
    int  purseno;		//钱包号
    int  dpscnt;		//卡充值次数
    int  paycnt;		//卡消费次数
    int  aftdpscnt;		//卡充值后次数
    int  aftpaycnt;		//卡消费后次数
    int  transflag;		//次数类型，1充值2消费
    int  cardsubsidyno;	//卡补助批次号
    double  cardbefbal;	//交易前卡余额
    double  cardaftbal;	//交易后卡余额
    char showcardno[11];//显示卡号
    int  feetype;		//卡收费类型
    int  custid;		//客户号
    char custname[61];	//客户名
    char stuempno[21];	//学工号
    char deptcode[31];	//部门号
    int  shopid;		//商户号
    char cardaccno[11];	//卡帐户号
    char eaccno[11];	//电子钱包账号
    char shopaccno[11]; //商户账号
    char draccno[21];	//输入值:借方账号
    char craccno[21];	//输入值:贷方账号
    int  fundtype;		//资金类型 1-现金2-支票3-经费本4-个人帐户存款5-银行存款
    char voucherno[21];	//凭证号
    char drsubjno[21];	//输出值:借方科目
    char crsubjno[21];	//输出值:贷方科目
    char draccname[61];	//输出值:借方账户名
    char craccname[61];	//输出值:贷方账户名
    int  transtype;			//交易类型
    int  subseqno;			//子流水号
    double  inputamt;		//输入金额
    double  transamt;		//交易金额
    double  addamt;			//补写金额
    double  unusedamt; 		//剩余金额
    double  totalfeeamt;	//总收费金额(输出)
    double  totaltransamt;	//总交易金额(输出)
    double  forgift;		//押金金额
    double  draccbefbal;	//交易前借方帐户余额
    double  craccbefbal;	//交易前贷方帐户余额
    double  draccaftbal;	//交易后借方帐户余额
    double  craccaftbal;	//交易后贷方帐户余额
    char summary[61];		//摘要
    int  errcode;			//错误码
    char remark[241];		//备注
}TRANS;
typedef struct
{
    int  iRenewCardDayCnt;		//补办卡天数
    char sSettleDate[9];		//结算日期
    char sPreSettleDate[9];		//上一个结算日期
    char sNextSettleDate[9];		//下一个结算日期
    char sPosdtlExpireDate[9];	//POS流水过期日期
    char sRenewAccDate[9];		//补办卡日期
    double dAutoRenewAccMaxAmt;	//自动补帐最大限额
    int  iShopBoardFeeFlag;		//是否是商户收搭伙费
    int  bEnableCardMgr;		//是否启用卡片库存管理
    int  iQryMaxCnt;			//查询最大条数
//    double dCardMaxBal;			//最大充值金额
}SYSPARA;


typedef map<int,list<CfgFee> > MAPCFGFEELIST;
typedef map<int,list<CfgTrans> >  MAPCFGTRANSLIST;

typedef map<int,T_t_cfgsplit>  MAPCFGSPLIT;
typedef map<int,T_t_transcode> MAPCFGTRANSCODE;
typedef map<int,string> MAPERRINFO;
inline string ltos(long l)
{
	char a[20];
	sprintf(a, "%ld", l);
	return string(a);
}
inline string dtos(double l)
{
	char a[32];
	sprintf(a, "%.2lf", l);
	return string(a);
}
inline void split2list(const char *str,const char delim,vector<string>& strlist)
{
    strlist.clear();
    stringstream ss(str);
    while(1)
    {
        string token;
        getline(ss,token,delim);
        if(ss.fail()) 
            break;
        strlist.push_back(token);
    }
}
//去除两端的空格字符
inline string& string_trim(string &str)
{
    const string &delim =" \t\n" ;
    str=str.erase(str.find_last_not_of(delim)+1);
    str=str.erase(0,str.find_first_not_of(delim));
    return str;
}
inline void string_replace(string & strBig, const string & strsrc, const string &strdst) {
    string::size_type pos=0;
    string::size_type srclen=strsrc.size();
    string::size_type dstlen=strdst.size();
    while( (pos=strBig.find(strsrc, pos)) != string::npos){
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}
//生成唯一流水号
int GetUniqSno(char *serialno,int type);
//生成唯一记录号
int GetRecordNo(char *recordno);
//生成主机唯一流水号
int GetHostSno(char *serialno);

//生成新的交易参考号
int GetNewRefno(char *refno);

class CAccTrans
{
private:
	MAPERRINFO   mapErrInfo;
    MAPCFGTRANSLIST mapTransList;
    MAPCFGSPLIT  mapSplit;
    static CAccTrans *_pSelf;
    int _cfgverno;		//配置版本号
    int _CalcCardBalCnt;//计算卡余额次数
    int _errcode;
	int _freeflag;		//免卡成本费或押金标志
	int _summaryflag;	//摘要标志
    string _errmsg;
	string _errtip;
	string _tip;
	char  right; //0-只能系统操作员1-审核操作员2-业务操作员3-不显示
	ST_CPACK* _ReqCpack;
public:
    SYSPARA   	   sysPara;
    MAPCFGTRANSCODE mapCfgTransCode;
    MAPCFGFEELIST  mapFeeList;
    T_t_transcode *_pCfgTransCode;
    TRANS trans;
    string remark;
    char  cpackdata[2001];
    CAccTrans();
    virtual ~CAccTrans(){};
    static CAccTrans * getInstance()
    {
		if(NULL==_pSelf)
		{
			_pSelf=new CAccTrans();
		}
        return _pSelf;
    };
	int Reset(ST_CPACK* rPack=NULL);
    int end();
    int GetCfgVerNo(int& cfgverno);
    int UpdateCfgVerNo(char* opercode);
    int CheckCfgUpdate();
	int LoadCfg();
    int LoadInitCfg();
	int LoadDynCfg();
	int LoadErrInfo();
	int SetErrMsg(const char *errmsg,...);
	int SetErrMsg(int errcode,const char *paraval,const char *paraval2=NULL);
	int SetErrMsg(int errcode,int paraval=-9999,int paraval2=-9999);
	int SetErrMsg(int errcode,double paraval,double paraval2=-9999);
	void SetErrTip(char *errtip,...);	
	void SetFreeFlag();
	void SetSummary(const char *summary);
	void SetTip(char *tip);
	string& GetTip();
	string& GetErrTip();
	string& GetErrMsg(int errcode=0);
	string& GetErrMsgTip(int errcode=0);
    int LoadCfgTransCode();
    int LoadCfgFeeList();
    int LoadCfgTransList();
    int LoadCfgSplit();
    int LoadSysPara(bool lockflag=false);
    int GetTermSeqno(int termid=0);
    T_t_transcode* getCfgTranscode(int transcode=0);
    int doForegift(char *cardaccno,double foregiftamt);
	int UpdCardAcc(char *accno,int dcflag,int calccardbalflag);
	int UpdShopAcc(char *accno,int dcflag);	
	int UpdNetAcc(char *accno,int dcflag);
	int UpdInnerAcc(char *accno,int dcflag);
    int AddAccDtl(int dcflag);
    int DoSplitTrans();
    int DoTransByTransType();
	void SetCardCntAndCardBal(int dpscnt,int paycnt,double cardbal);		
	void SetCardCntAndCardBal(int dpscnt,int paycnt,int cardbal);
	void SetInputAmt(double amount);
    int InitTrans();
    virtual int doTrans();
    int doFeeTrans();
    int doMainTrans();
	int doTransEnd();
    int doTodayReverseTrans(char *accdate,int termid,int termseqno);
	int doHistoryReverseTrans(char *accdate,int termid,int termseqno);
public:
	// 辅助函数
	CAccTrans& CardExpect(CARD_STATUS idx)
	{
		// 不需要检查了
		if(checkResult != 0)
			return *this;

		if(checkCard == NULL)
		{
			checkResult = 1;
			return *this;
		}
		switch(idx)
		{
		case CS_NORMAL:
			checkResult = (checkCard->status[0] == '1');
			break;
		case CS_LOST:
			checkResult = (checkCard->lossflag[0] == '1');
			break;
		case CS_FROZEN:
			checkResult = (checkCard->frozeflag[0] == '1');
			break;
		case CS_BAD:
			checkResult = (checkCard->badflag[0] == '1');
			break;
		case CS_LOCKED:
			checkResult = (checkCard->lockflag[0] == '1');
			break;
		case CS_CLOSED:
			checkResult = (checkCard->status[0] == '2');
			break;
		case CS_UNLOST:
			checkResult = (checkCard->lossflag[0] == '0');
			break;
		case CS_UNFROZEN:
			checkResult = (checkCard->frozeflag[0] == '0');
			break;
		case CS_UNBAD:
			checkResult = (checkCard->badflag[0] == '0');
			break;
		case CS_UNLOCKED:
			checkResult = (checkCard->lockflag[0] == '0');
			break;
		default:
			checkResult = 0;
			break;
		}
		if(checkResult)
			checkResult = 0;
		else
		{
			checkResult = 1;
			checkCardMsg<<"检查状态["<<idx<<"]错误";
		}
		return *this;
	}
	template<class T>
	CAccTrans& CardExpectEx(CARD_STATUS idx,T compare)
	{
		// 不需要检查了
		if(checkResult != 0)
			return *this;

		if(checkCard == NULL)
		{
			checkResult = 1;
			return *this;
		}
		switch(idx)
		{
		case CS_NORMAL:
		case CS_CLOSED:
			checkResult = compare.Compare(checkCard->status[0]);
			break;
		case CS_LOST:
		case CS_UNLOST:
			checkResult = compare.Compare(checkCard->lockflag[0]);
			break;
		case CS_FROZEN:
		case CS_UNFROZEN:
			checkResult = compare.Compare(checkCard->frozeflag[0]);
			break;
		case CS_BAD:
		case CS_UNBAD:
			checkResult = compare.Compare(checkCard->badflag[0]);
			break;
		case CS_LOCKED:
		case CS_UNLOCKED:
			checkResult = compare.Compare(checkCard->lockflag[0]);
			break;
		case CS_EXPIREDATE:
			checkResult = compare.Compare(checkCard->expiredate);
			break;
		case CS_LOSSDATE:
			checkResult = compare.Compare(checkCard->lossdate);
			break;
		case CS_FROZEDATE:
			checkResult = compare.Compare(checkCard->frozedate);
			break;
		case CS_LOCKDATE:
			checkResult = compare.Compare(checkCard->lockdate);
			break;
		case CS_BADDATE:
			checkResult = compare.Compare(checkCard->baddate);
			break;
		default:
			checkResult = 1;
			return *this;
		}
		if(checkResult)
			checkCardMsg<<"检查状态["<<idx<<"]错误";
		return *this;

	}
	template<class T,class U>
	CAccTrans& ExpectValue(T& v,U compare,int ErrCode,const char *errmsg = NULL)
	{
		int ret;
		if(checkResult !=0 )
			return *this;
		ret = compare.Compare(v);
		if(ret)
		{
			if(ErrCode!=0)
				checkResult = ErrCode;
			else
				checkResult = E_COMMON_ERR;
			if(errmsg)
				checkCardMsg<<errmsg;
			else
				checkCardMsg<<"检查错误";
		}
		return *this;
	}
	CAccTrans& CheckCardStatus(T_t_card *card)
	{
		checkCard = card;
		checkResult = 0;
		checkCardMsg.str("");
		return *this;
	}
	CAccTrans& CheckCardStatus(int cardno,T_t_card *card);
	int CheckExpect()
	{
		int ret = checkResult;
		checkResult = 0;
		checkCard = NULL;
		return ret;
	}
	int CheckAcc(T_t_card *card,T_t_account *account=NULL,T_t_transdtl *dtl=NULL);
	int GenTransdtl(T_t_transdtl *dtl,int status);
private:
	int checkResult;
	T_t_card *checkCard;
	std::stringstream checkCardMsg;
};

int acc_process();
#endif
