#ifndef	__BANK_H__
#define	__BANK_H__

#include "tcp.h"
#include "mac.h"
#include "typdef.h"

//批量编号组成：09＋银行行部号＋058＋4位顺序号，如果学校一天仅一批，则可以将顺序号写死
//则需要维护顺序号的使用情况。编号由银行提供一个或一段（看是否一天一批）
#define BATCH_NO		"09*****0580001"	//批量编号
#define UNIT_NAME		"fudan university"	//单位名称
#define UNIT_ACCOUNT	"987564343"			//单位帐号

#define	BANK_TRADE_CODE_LEN 		2			//银行端交易代码长度
#define	LEN_MAC				8			//mac字段长度
#define	BANK_IP				"10.83.28.17"		//银行前置机IP地址
#define BANK_PORT			3501			//银行前置机服务端口
#define BANK_DELAY_TIME			3000			//接收银行返回数据包的超时时间－单位为毫秒
#define	UNQUE_KEY_TYPE			"trans"			//生成唯一索引号的函数的第一个参数，用于区别于不同系统
#define WORKSTATION_NO			167			//工作站标实，安装时分配，暂时定167
#define	AGRICULTURE_BANK_CODE		1			//应耿刚要求，填写外部系统类别，标识农业银行
#define	AUTO_TRANS			1			//自动转帐
#define	SELF_TRANS			2			//自助转帐
#define	SCHOOL_ACCOUNT_NO		"9876543210"		//学校一卡通在农行开户的帐号
#define	TRANS_INI_FILE 			"./trans.ini"		//ini文件


 /////////////////////////// inter return value      ///////////////////////////////

#define  SUCCEED			000000	//成功
#define  E_TRANS_BANKCARD_LOST         	108001	//银行卡挂失
#define  E_TRANS_BANKACC_STATERR        108002	//银行帐户状态不对
#define  E_TRANS_BANKACC_NOMONEY        108003	//银行卡余额不足
#define  E_TRANS_BANKCARD_PWDERR        108005	//银行卡密码错误
#define  E_TRANS_SCHCARD_LOST         	108101	//校园卡挂失
#define  E_TRANS_SCHCARD_FREEZE         108102	//校园卡冻结
#define  E_TRANS_SCHCARD_UNLOSTING      108103	//持卡人已经为解挂状态
#define  E_TRANS_SCHCARD_LOSTING        108104	//持卡人已经为挂失状态
#define  E_TRANS_SCHACC_NOEXIT         	108105	//该校园卡帐户不存在
#define  E_TRANS_SCHACC_DESTORY         108106	//持卡人已经销户
#define  E_TRANS_RELATION_ERR         	108107	//对应关系不符
#define  E_TRANS_SCHCARD_PWDERR         108108	//校园卡密码错
#define  E_TRANS_TRANSMONEY_OUTRANGE    108109	//转帐金额超出范围
#define  E_TRANS_ACCMONEY_OUTRANGE      108110	//校园卡余额超出范围
#define  E_TRANS_BANK_NODECIDE         	108111	//银行未决交易
#define  E_TRANS_BANK_NOANSWER         	108112	//银行超时，无应答
#define  E_TRANS_BANK_NETERR         	108113	//银行网络故障
#define  E_TRANS_BANK_SERVICE_NOEXIT    108114	//服务没有启动
#define  E_TRANS_RELATION_NOEXIT        108115	//没有对应关系
#define  E_TRANS_FUNC_NONSUPPORT        108116	//此功能暂不被支持
#define  E_TRANS_BANK_RECVERR         	108117	//银行返回数据错误
#define  E_TRANS_SCHOOL_NETERR         	108118	//校园端网络故障
#define  E_TRANS_INNER_TIMEOUT         	108119	//内部超时
#define  E_TRANS_TERM_NOLOGIN         	108120	//终端未登陆
#define  E_TRANS_SCHCARD_TWICE		108121	//客户有多张卡
#define  E_TRANS_SCHCARD_WFAIL	108122	// 校园卡写卡失败

#define  E_TRANS_UNKNOW_ERROR         	109000	//其他未知错误

#define	RET_OK					0			//交易成功
#define	RET_CANCEL				1			//交易取消
#define	RET_TIMEOUT			2			//交易超时
#define	RET_FAILED				-1			//交易失败(与网络无关)
#define	RET_NETERR				-2			//网络失败

 /////////////////////////// bank return value      ///////////////////////////////
#define	RET_BANK_OK			"00"		//成功
#define	RET_BANK_LOST			"01"		//挂失
#define	RET_BANK_ERRSTAT		"02"		//帐户状态不对
#define	RET_BANK_NOBAL		"03"		//余额不足
#define	RET_BANK_OTHER		"04"		//其他错误
#define	RET_BANK_PASSERR		"05"		//密码错误


 /////////////////////////// 上海农业银行交易代码  ///////////////////////////////
 #define	TRADE_BANK_LOGIN		"31"		//签到
 #define	TRADE_BANK_LOGOUT	"32"		//签退
 #define	TRADE_BANK_TRANS		"01"		//转账
 #define	TRADE_BANK_DETRANS	"11"		//转账冲正
 #define	TRADE_BANK_QUERY		"05" 		//查询余额
 #define	TRADE_BANK_COMP		"33"		//对帐
 #define	TRADE_BANK_FEE		"02"		//缴费
 #define	TRADE_BANK_DEFEE		"12"		//缴费冲正
 #define	TRADE_BANK_CHGKEY	"34"		//密钥交换
 #define	TRADE_BANK_CHECKLINE	"35"		//线路测试
 #define	TRADE_BANK_BALANCE	"36"		//清算
 #define	TRADE_BANK_RETURN	"37"		//结果返回


//上海农行银行接口数据结构
 typedef struct
{
//								  CPACK字断		内容
//----------------------------------------------------------------------
	char		TradeCode[2];		//scust_type	交易代码：  见下文
	char		RetCode[2];			//scust_type2	交易结果：  见下文
	char		TradeDate[8];		//sdate0		交易日期	 YYYYMMDD
	char		TradeTime[6];		//semp			交易时间	 HHMMSS
	char		CustAccountNo[10];	//sorder0		校园卡帐号，后补空格
	char		BankCardNo[20];		//scust_auth	银行卡号,	 后补空格
	char		MercAccount[10];		//sorder1		商户号	圈存时为学校商户号，缴费或清算时
								//为各商户的商户号
	char		TransMoney[9];		//sorder2		转账金额，  以分为单位，前补空格
	char		Balance[9];			//scust_no		借记卡余额，以分为单位，前补空格
	char		BankCardPwd[16];	//sstation0		银行卡密码
	char		CustSn[8];			//sdate1		校园端流水号， 后补空格
	char		BankSn[20];			//scust_auth2	银行流水号，	后补空格
	char		CustNo[16];			//sstation1		学校代号，		后补空格
	char		AutoFlag;			//sstatus0		自动转账标志,'0':自助，'1':自动
	char		MAC[8];				//sdate2		校验
}BANK_TRANS_REQUEST;

#define BANK_TRANS_PACKLEN	sizeof(BANK_TRANS_REQUEST)

struct SockNode
{
	CTcpSocket	hSock;
	char   		Buf[1024];
	int	  	HaveRead;
	int	  	TotalRead;
};

typedef struct
{
	char		TradeCode[2];		//交易代码
	char 	GDCAccount[10];		//校园卡帐号，	后补空格
	char		BankCard[20];		//银行卡号码，	后补空格
	char		LocalSn[8];			//校园端流水号，	后补空格
	char		BankSn[20];			//银行方流水号，	后补空格
	char		TransMomoy[9];	//交易金额，		前补零，以分为单位
	char 	LineChange[2];	//'\r\n'
}BANK_COMPARE_RECODE;

typedef struct
{
	 char rmb_batch_no[14];//批量编号
	 char rmb_start_seq[6];//填000000
	 char rmb_acc_status;//记帐状态（填0）
	 char rmb_chk_status;//检查状态（填2）
	 char rmb_total_amount[13];//总金额(11位整数2位小数，无小数点)
	 char rmb_total_num[6];//总笔数
	 char rmb_enter_amount[13];//入帐金额(11位整数2位小数，无小数点)
	 char rmb_enter_num[6];//入帐笔数
	 char rmb_unit_name[40];//单位名称
	 char rmb_unit_account[20];//单位帐号
	 char rmb_apply_date[8];//申请入帐日期（当天日期）
	 char rmb_send_date[8];//上传日期（当天日期）
}BANK_TRANSFER_HEAD;

typedef struct
{
  	 char rmb_batch_no1[14];         //批量编号
        char rmb_seq_no[6];                     //记录序号（从1累计）
        char rmb_acc_status1;           //记帐状态（填0）
        char rmb_tran_kind;             //交易种类（1.现金支票、2.贷记凭证、3.信汇、4.汇票、5.本票）
        char rmb_cust_name[40];         //帐户名称
        char rmb_acc_no[19];                    //帐号
        char rmb_cb_cr;                 //借贷标志（填0）
        char rmb_tran_amt[13];                  //交易金额
        char rmb_cur_code[3];                   //币种（0＋2位币种代码）
        char rmb_host_no[8];                    //传票号（填00000000）
        char rmb_ret_code[4];                   //记帐结果（填"    "）
        char rmb_acc_date[8];                   //入帐日期（填00000000）
        char rmb_host_no1[9];                   //主机流水号（填000000000）
        char rmb_open_branch[7];        //开户行所号（填0000000）
 	 char rmb_vcho_kind[2];                  //凭证种类（填"  "）
        char rmb_vcho_bat_no[2];        //凭证批次号（填00）
        char rmb_vcho_no[9];                    //凭证号（按业务要求）
        char rmb_memo[22];              //摘要/用途
        char rmb_tran_info[200];                //交易信息
}BANK_TRANSFER_RECORD;



#ifdef __cplusplus
extern "C" {
#endif

extern int debug;

// 字符串拷贝，填充空格，为银行接口使用
char * strnscpy(char *dst, char* src, int len);	//拷贝子串，填充空格

//通用函数
int send_to_and_recv_from_bank(char* pSend, int send_len,char* pRecv,int recv_len,int delay_time);
int send_to_and_recv_from_bank_of_boc(char* pSend, int send_len,char* pRecv,int *recv_len,int max_recv_len,int delay_time);
int device_login_yes_or_no(int device_id);
void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage);
int BOC_RET_NO(char ret_code[3]);

/****************************************************
银行端交易处理函数
lq, 20050310，从transinfo.cpp移过来，以与bu相关代码脱离
****************************************************/
//检查线路处理过程
int Do_CheckLine(BANK_TRANS_REQUEST *pBankTrans );

//签到交易处理过程
int Do_Login  (BANK_TRANS_REQUEST *pBankTrans );

//签退交易处理过程
int Do_Quit	(BANK_TRANS_REQUEST *pBankTrans );

//自动转账交易处理过程
int Do_AutoTrans  (BANK_TRANS_REQUEST *pBankTrans );

//冲正交易处理过程
int Do_DeTrans  (BANK_TRANS_REQUEST *pBankTrans );

//对帐过程
int Do_Compare(BANK_TRANS_REQUEST *pBankTrans );

//农行的对帐过程，不发送交易报
int Do_Compare_file();

//手动的对帐函数，应急使用的
int Do_Compare_file_shoudong();


//划拨过程
int Do_Transfer(BANK_TRANS_REQUEST *pBankTrans);


#ifdef __cplusplus
}
#endif

#endif
