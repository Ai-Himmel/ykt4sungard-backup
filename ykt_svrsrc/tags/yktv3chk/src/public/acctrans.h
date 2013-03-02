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
//#include <sstream>
#include <map>
#include <list>
using namespace std;

#define ACCTYPE_CARD  1			//持卡人卡帐户
#define ACCTYPE_SHOP  2			//商户账号
#define ACCTYPE_EACC  3			//电子钱包账户
#define ACCTYPE_INNER 4			//内部帐户

#define TYPE_INPUT  1
#define TYPE_CONFIG 2

typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short	WORD;
#define MAKELONG(feetype,funtype)   ((LONG)(((WORD)(feetype)) | ((DWORD)((WORD)(funtype))) << 16))

typedef struct {
	int  cardflag;		//有无卡标志
	int  cardtype;		//卡类型	
	int  feetype;		//收费类型
	int  cardno;		//卡号
	int  purseno;		//钱包号
	int  cardcnt;		//卡交易次数
	double  cardbefbal;	//交易前卡余额
	double  cardaftbal;	//交易后卡余额
	int  befbalflag;	//0-无入卡值1-有入卡值
	int  aftbalflag;	//0-无出卡值，1-有出卡值
	int  calaftbalflag;	//是否需要计算出卡值0-不计算1-计算
	double  transamt;	//交易金额
	double  managefee;	//管理费
	char transdate[9];	//交易日期
	char transtime[7];	//交易时间
	char collectdate[9];//采集日期
	char collecttime[7];//采集时间
	char cardphyid[9];	//卡物理ID
	char devphyid[31];  //设备物理ID
	int  devseqno;		//设备流水号
	char cardaccno[21];	//卡账号
}CARDTRANSINFO;


typedef struct 
{
	int cardtype;
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

typedef struct {
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
typedef struct {
	int  transcode;		//交易码
	int  termid;		//终端编号
	int  termseqno; 	//终端流水号
	char accdate[9];	//记账日期
	char acctime[7];	//记账时间
	char transdate[9];	//交易日期
	char transtime[7];	//交易时间		
	int  loginsiteno;	//当前登录的站点
	char opercode[9];	//操作员号
	int  offlineflag;	//是否联机交易1-脱机交易0-联机交易
	int  usecardflag;	//1与卡有关系的交易0-与卡无关系的交易
	int cardno;			//卡号
	int  custid;		//客户号
	int  shopid;		//商户号
	int  feetype;		//客户收费类型
	int  fundtype;		//资金类型 1-现金2-支票3-经费本4-个人帐户存款5-银行存款
	double  inputamt;		//输入金额
	char voucherno[21];	//凭证号
	char dbaccno[21];	//借方账号
	char dbaccname[241];	//借方账户名
	char craccno[21];	//贷方方账号	
	char craccname[241];	//贷方账户名
	int  dbacctype;		//借方帐户类型
	int  cracctype;		//贷方帐户类型
//////////////////////以下为输出///////////////////	
	int  transtype;		//交易类型
	int  subseqno;		//子流水号
	double  transamt;		//交易金额
	double  unusedamt; 	//剩余金额
	double  forgift;		//押金金额
	char dbsubjno[21];	//借方科目
	char crsubjno[21];	//贷方科目	
	double  dbaccbal;		//借方帐户余额
	double  craccbal;		//贷方帐户余额	
	double  dbcardaftbal;	//借方卡余额
	double  crcardaftbal;	//贷方卡余额
	double  cardaftbal;	//卡余额
	char summary[61];	//摘要
}TRANS;


typedef map<int,list<CfgFee> > MAPCFGFEELIST;
typedef map<int,list<CfgTrans> >  MAPCFGTRANSLIST;

typedef map<int,T_t_cfgsplit>  MAPCFGSPLIT;


class CAccTrans
{
private:
	MAPCFGTRANSLIST mapTransList;
	MAPCFGSPLIT  mapSplit;
    static CAccTrans *_pSelf;	
	int  _cfgverno;
public:
	MAPCFGFEELIST  mapFeeList;
	CARDTRANSINFO cti;
	TRANS trans;
	string remark;		
	char  cpackdata[2001];
	CAccTrans();
	virtual ~CAccTrans(){};
	static CAccTrans * getInstance() {return _pSelf;};
	void clear();
	int getCfgVerNo(int& cfgverno);
	int checkCfgUpdate();
	int loadCfg();
	int loadCfgFeeList();
	int loadCfgTransList();
	int loadCfgSplit();
	int initOperDtl(char *opercode);
	int addOperDtl(char *opercode=NULL);
	int doForegift(char *cardaccno,int foregiftamt);
	int updAcc(char *accno,char dbcrflag,T_t_cfgsplit& cfgsplit);
    int addAccDtl(char dbcrflag);
	int doSplitTrans();
	int doTransByTransType();
	int doFeeTrans();
	int doMainTrans();
	virtual int doAccTrans();
	int doReverseTrans(char *accdate,int termid,int termseqno);
	//int doReverseTrans(char *accdate,int termid,int termseqno);
};
#endif
