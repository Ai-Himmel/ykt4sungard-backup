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
using namespace std;

#define LOGFLAG_NONE 0		//不记录流水
#define LOGFLAG_SUCC 1		//只记录成功交易流水
#define LOGFLAG_FAIL 2		//只记录失败交易流水
#define LOGFLAG_ALL  3		//全部记录(包含成功和失败)

#define ACCTYPE_CARD  1			//持卡人卡帐户
#define ACCTYPE_SHOP  2			//商户账号
#define ACCTYPE_EACC  3			//电子钱包账户
#define ACCTYPE_INNER 4			//内部帐户

#define TYPE_INPUT  1
#define TYPE_CONFIG 2
#define ACCFLAG_CARD   'C'		//卡账户
#define ACCFLAG_EACC   'E'		//电子账户
#define ACCFLAG_SHOP   'S'		//商户
#define ACCFLAG_INNER  'N'		//内部固定账户
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
#define TRANSTYPE_CARDSAVING			201	//持卡人存款
#define TRANSTYPE_CARDSHOPSAVING		202	//持卡人存款(充值商户)
#define TRANSTYPE_CARDSUBSIDY			203 //卡户补助
#define TRANSTYPE_BANKTRANS				204 //银行圈存转账

#define TRANSTYPE_CARDDRAW				231	//持卡人取款
#define TRANSTYPE_POSPAYMENT			232	//POS消费
#define TRANSTYPE_CARDPAYMENT			233	//支付交易
#define TRANSTYPE_WATERTRANS			234	//水控转账
#define TRANSTYPE_MOBILETRANS   		235 //手机转账

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
#define TRANSTYPE_SHOPPAYMENT			290	 //商户解款

#define TRANSTYPE_RETURNBOARDFEE		291	 //商户退搭伙费
#define TRANSTYPE_SHOPRAKEOFF			292	 //收商户佣金
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
//短款处理651-660
#define TRANSTYPE_LESS_CARDBAL			651	//退卡损益转-卡余额
#define TRANSTYPE_LESS_POSPAYMENT		652  //消费流水发生额短款(针对挂失或注销卡)
#define TRANSTYPE_LESS_SHOPBOARDFEE		653  //消费流水搭伙费短款(针对挂失或注销卡),如果是商户收搭伙费的情况
#define TRANSTYPE_LESS_SCHOOLBOARDFEE	654  //消费流水搭伙费短款(针对挂失或注销卡),如果是学校收搭伙费的情况
#define TRANSTYPE_LESSOUT2MOREIN		655  //在商户和卡户都注销的情况下,流水从营业外支出到营业外收入
//其他80-98
#define TRANSTYPE_MANDRCR				700	//手工借贷

#define OPERRIGHT_SYSTEM				0 //只有系统操作员才能使用
#define OPERRIGHT_CHECK					1 //审核操作员才能使用
#define OPERRIGHT_OPER					2 //操作员才能使用

const int  SEQNO_BANK = -1;
const int  SEQNO_REFNO = -10;

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
//	char cardphyid[9];	//卡物理ID
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
    char refno[21];		//电子凭证号
    int  revflag;		//0-正常交易1-冲正交易
    int  termid;		//终端编号
	int  termseqno; 	//终端主机流水号
    char sysdate[9];	//系统日期
    char systime[7];	//系统时间
    char transdate[9];	//交易日期
    char transtime[7];	//交易时间
    int  branchno;		//操作员网点号
    int  loginsiteno;	//当前登录的站点
    char opercode[9];	//操作员号
    char chkopercode[9];//审核操作员
    int  offlineflag;	//是否联机交易1-脱机交易0-联机交易
    int  usecardflag;	//1与卡有关系的交易0-与卡无关系的交易
    int  cardflag;		//有无卡标志(1有卡交易0无卡交易)
    int  cardtype;		//卡类型
    char cardphyid[11];	//物理卡号
    int  cardno;		//卡号
    int  purseno;		//钱包号
    int  cardcnt;		//卡交易次数
    int  cardsubsidyno;	//卡补助批次号
    double  cardbefbal;	//交易前卡余额
    double  cardaftbal;	//交易后卡余额
    char showcardno[11];//显示卡号
    int  feetype;		//卡收费类型
    int  custid;		//客户号
    char custname[61];	//客户名
    char stuempno[31];	//学工号    
    int  shopid;		//商户号
    char cardaccno[21];	//卡帐户号
    char eaccno[21];	//电子钱包账号
    char shopaccno[21]; //商户账号
    char draccno[21];	//输入值:借方账号
    char craccno[21];	//输入值:贷方账号
    int  fundtype;		//资金类型 1-现金2-支票3-经费本4-个人帐户存款5-银行存款
    char voucherno[21];	//凭证号
    char drsubjno[21];	//输出值:借方科目
    char crsubjno[21];	//输出值:贷方科目
    char draccname[241];//输出值:借方账户名
    char craccname[241];//输出值:贷方账户名
    int  transtype;			//交易类型
    int  subseqno;			//子流水号
    double  inputamt;		//输入金额
    double  transamt;		//交易金额
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
    int  iPosdtlMaxDayCnt;		//POS脱机流水最大未上传天数
    char sSettleDate[9];		//结算日期
    char sPreSettleDate[9];		//上一个结算日期
    char sNextSettleDate[9];		//下一个结算日期
    char sPosdtlExpireDate[9];	//POS流水过期日期
    char sRenewAccDate[9];		//补帐日期
    double dAutoRenewAccMaxAmt;	//自动补帐最大限额
    int  iLossEffectTime;		//挂失生效间隔时间(分钟)
    int  iShopBoardFeeFlag;		//是否是商户收搭伙费
    int  bEnableCardMgr;		//是否启用卡片库存管理
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
	int _freeflag;	//免卡成本费或押金标志
    string _errmsg;
	string _errtip;
	string _tip;
	char  right; //0-只能系统操作员1-审核操作员2-业务操作员3-不显示
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
        return _pSelf;
    };
    int Reset();
    int end();
    int GetCfgVerNo(int& cfgverno);
    int UpdateCfgVerNo(char* opercode);
    int CheckCfgUpdate();
	int LoadCfg();
    int LoadInitCfg();
	int LoadDynCfg();
	int LoadErrInfo();
	int SetErrMsg(int errcode,const char *paraval,const char *paraval2=NULL);
	int SetErrMsg(int errcode,int paraval=-9999,int paraval2=-9999);
	int SetErrMsg(int errcode,double paraval=-9999,double paraval2=-9999);
	void SetErrTip(char *errtip);	
	void SetFreeFlag();
	
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
//    int updAcc(char *accno,int dcflag,T_t_cfgsplit& cfgsplit,T_t_account& account);
	int UpdCardAcc(char *accno,int dcflag,int calccardbalflag);
	int UpdShopAcc(char *accno,int dcflag);	
	int UpdNetAcc(char *accno,int dcflag);
	int UpdInnerAcc(char *accno,int dcflag);
    int AddAccDtl(int dcflag);
    int DoSplitTrans();
    int DoTransByTransType();
    int InitTrans();
    virtual int doTrans();
    int doFeeTrans();
    int doMainTrans();
	int doTransEnd();
    int doReverseTrans(char *accdate,int termid,int termseqno);
};
#endif
