#ifndef	__BANK_H__
#define	__BANK_H__

#ifdef __cplusplus
extern "C" {
#endif
 /////////////////////////程序常用数据块/////////////////////////////////////
#define MAX_RANGE 20
#define MAX_BANK 5
#define	TRANS_INI_FILE 			"./trans.ini"		//ini文件

typedef struct
{
   char szBankIP[20];  // 银行端的ip地址
   int  iBankPort;         // 银行端的端口号
   int  iBankTimeout;    // 银行端的连接超时时间
   int  iBankID;		//银行标识号，需要与后台数据字典保持一致
   char  szBankCardRange[MAX_RANGE][20];  // 银行卡号范围
   int	  iAuthMode;		//认证方式，输入银行卡密码还是校园卡密码
   char  szBankAccountNO[17];

} ST_BANK;  

typedef struct
{
	int 	DRTP_BRANCH;
	int 	BCC_BASEFUNCNO;
	int 	TIMEOUT;
	char COMPACC_TIME[2+1];
	int	LOGIN_MODE;
	int	AUTH_MODE;
	int 	LOG_MODE;
	char	DRTP_IP[20];
	int	DRTP_PORT;	
	int 	BankCount;
	int	cur_bankid;
	char SERV_TIME[20];
	ST_BANK	BankUnit[MAX_BANK];
}ST_BANK_CONFIG;

//extern ST_BANK  g_BankIni;  //银行的配置信息 
extern ST_BANK_CONFIG g_Bank;


typedef struct
{
	char		TradeCode[6];		//sclose_emp	//交易代码
	char		TransMoney[9];		//sorder0		//交易金额
	char		ExtraMoney[9];		//sorder1		//附加交易金额
	char		AccountMoney[11];	//sserial1		//校园卡帐户金额
	int		SendNo;				//lvol0			//发起方流水号
	int 		RecvNo;				//lvol1			//接受方流水号
	char		TradeDate[8];		//sdate0			//交易日期	 YYYYMMDD
	char		TradeTime[6];		//stime0			//交易时间	 HHMMSS
	char		BankDate[8];			//sdate1			//银行处理日期
	char		BankTime[6];			//stime1			//银行处理时间
	char		Balance[9];			//scust_no		//银行卡余额
	char		RetCode[6];			//schange_emp	//交易结果
	char		CardNo[12];			//sserial0		//校园卡卡号
	int		Notecase;			//lvol2			//校园卡对应钱包号
	char		BankCardNo[20];		//scust_auth		//银行卡号
	char		MngFeeFlag;			//sstatus1		//手续费标志
	char		AccountPwd[6];		//semp_pwd		//校园账户密码
	char		AccountNewPwd[6];	//semp_pwd2		//校园账户新密码
	char		BankCardPwd[16];		//sstation0		//银行账户密码
	char		BankCardNewPwd[16];	//sstation1		//银行账户新密码
	char		TerminalId[10];		//sorder2		//终端编号
}INNER_TRANS_REQUEST;

#define	INNER_TRANS_PACKLEN	sizeof(INNER_TRANS_REQUEST)


/////////////////////////////与新大陆约定的错误码///////////////////////////////////

//与终端约定的错误码，如果返回给新大陆的终端必须为如下的错误码
//否则圈存机无法翻译，如果需要扩充可以更新新大陆程序的配置文件
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
#define  E_DB_SUBSYSPARAMS_D               108123	//子系统参数表删除错误
#define  E_DB_SUBSYSPARAMS_I                108124	//子系统参数表插入错误
#define  E_DB_SUBSYSPARAMS_N               108125	//子系统参数表查询相关无记录
#define  E_DB_SUBSYSPARAMS_R               108126	//子系统参数表读取错误
#define  E_DB_SUBSYSPARAMS_E               108127	//子系统参数表已存在
#define  E_TRANS_BANK_FUNC_NONSUPPORT	108128	//指定银行不支持该功能
#define  E_TRANS_BANK_CARD_NONSUPPORT	108129	//转账系统目前不支持您的银行卡
#define  E_TRANS_UNKNOW_ERROR         	109000	//其他未知错误

////////////////////////////与银行接口的程序原型///////////////////////////////////////////
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance);
int Bank_Transfer(INNER_TRANS_REQUEST * pNode,int serial_no);
int Bank_Undo(INNER_TRANS_REQUEST * pNode);
int Bank_CheckLine();
int Bank_SignIn(INNER_TRANS_REQUEST *pNode);
int Bank_SignOut();


#ifdef __cplusplus
}
#endif

#endif

