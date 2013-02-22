#ifndef	__BANK_H__

#define	__BANK_H__



//#ifdef __cplusplus

//extern "C" {

//#endif



 /*****************************************************************************

 交易类型说明(用于Packet_Buf_Transform函数)

 *****************************************************************************/

#define		BANK_TRADE_CODE_QUERYBALANCE	1		//查询余额

#define		BANK_TRADE_CODE_TRANS		2			//转账

#define		BANK_TRADE_CODE_DETRANS		3			//冲正

#define		BANK_TRADE_CODE_COMPARE		4			//对帐

 

 /*****************************************************************************

  银行类别

 *****************************************************************************/

#define		BANK_ZGYH							3

#define		BANK_GSYH							1

#define		BANK_YNXH							4

#define		BANK_YNNH							5



 /////////////////////////程序常用数据块/////////////////////////////////////

#define MAX_RANGE 20

#define MAX_BANK 5

#define	TRANS_INI_FILE 			"./trans.ini"		//ini文件

#define SPLIT_VL				"|"

#define PACKET_TO_BUF			0					// packet to buf

#define BUF_TO_PACKET			1					// buf to packet



typedef struct

{

   char szBankIP[20];  // 银行端的ip地址

   int  iBankPort;         // 银行端的端口号

   int  iBankTimeout;    // 银行端的连接超时时间

   int  iBankID;		//银行标识号，需要与后台数据字典保持一致

   char  szBankCardRange[MAX_RANGE][20];  // 银行卡号范围

   int	  iAuthMode;		//认证方式，输入银行卡密码还是校园卡密码

   char  szBankAccountNO[17];

   char compare_time[6]; // 银行对账时间

   char sendcompreq_time[6]; // 往银行端发起对账请求的时间

   int compare_flag;	// 银行当日对账标志, 0标识未开始对账, 1标识已经完成了当日对账, 2标识不需要对账的银行

   int sendcompreq_flag;	// 发送请求标识0不发送, 1标识已经发送了请求

   int compare_count;		// 控制效验对账文件的次数

   char comp_file_path[256]; // 对账文件路径

} ST_BANK;  



typedef struct

{

	int 	DRTP_BRANCH;

	int 	BCC_BASEFUNCNO;

	int 	TIMEOUT;

	char COMPACC_TIME[2+1];

	char SENDCOMPREQ_TIME[2 + 1];		// 有的银行需要对对账文件进行请求

	int	LOGIN_MODE;

	int	AUTH_MODE;

	int 	LOG_MODE;

	char	DRTP_IP[20];

	int	DRTP_PORT;	

	int 	BankCount;

	int	cur_bankid;

	char SERV_TIME[20];

	ST_BANK	BankUnit[MAX_BANK];

	int trans_money;

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

	char		AccountPwd[9];		//semp_pwd		//校园账户密码

	char		AccountNewPwd[9];	//semp_pwd2		//校园账户新密码

	char		BankCardPwd[16];		//sstation0		//银行账户密码

	char		BankCardNewPwd[16];	//sstation1		//银行账户新密码

	char		TerminalId[10];		//sorder2		//终端编号

	char	 	Reserve1[256]; 	//vsvarstr0         //密文MAC与密钥, 长度不超过, 最长512字节	

	char	 	Reserve2[256]; 	//vsvarstr1 	

	char		Reserve3[256]; 	//vsvarstr2

	char	 	SencodMagTune[38]; //sbank_acc 	//第二磁道数据

	char		ThirdMagTune[105]; //scusttypes		//第三磁道数据

}INNER_TRANS_REQUEST;



#define	INNER_TRANS_PACKLEN	sizeof(INNER_TRANS_REQUEST)



// 对账文件数据结构

typedef struct

{

	char		file_name[6];			// 文件名

	char 		date[9];				// 日期	

	char 		time[7];				// 时间

	char 		file_path[256];			// 文件路径, 包含文件名

	int 		flag;					// 对账标识, 0标识未有对账成功, 1表示对账成功

	int 		bank_id;				// 对账银行ID号

}BANK_COMPARE_FILE;					



// 对账文件内容

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
	char transtype;		//交易类型
	char stuempno[31];	//学号
	char custname[31];	//姓名
	char idno[31];		//身份证号
	char bankcardno[21];//银行卡号
	int  retcode;		//返回码
	char retmsg[256];	//错误码

}tagBankCardRelation;


// 文件效验数据结构(存在需要文件效验的银行需要用到此结构)

typedef struct

{

	char liq_money[13];				// 清算金额

	char trade_deal_time[11];		// 交易传输时间

	char system_id[7];				// 系统跟踪号

	char shop_type[5];				// 商户类型

	char service_terms_code[3];		// 服务条件代码

	char proxy_node_code[14];		// 代理节点代码

	char send_node_code[14];		// 发送节点代码

	char answser_code[3];			// 应答码

	char device_phy[9];				// 受卡机终端标识码

	char mark[16];					// 受卡方标识

	char append_trade_info[104];	// 附加交易信息(信合文件名)

	char transfer_count[11];		// 转帐笔数

	char packet_identity_code[9];	// 识别吗

	char file_path_name[256];		// 文件路径

}BANK_FILE_ADJUST;





/////////////////////////////ISO8583FIELDS///////////////////////////////////

typedef struct ISO8583 

{ 

	int bit_flag; 			/*域数据类型0 -- string, 1 -- int, 2 -- binary*/ 

	char *data_name; 		/*域名*/ 

	int length; 			/*数据域长度*/ 

	int length_in_byte;		/*实际长度（如果是变长）*/ 

	int variable_flag; 		/*是否变长标志0：否 2：2位变长, 3：3位变长*/ 

	int datatyp; 			/*0 -- string, 1 -- int, 2 -- binary*/ 

	char *data; 			/*存放具体值*/ 

	int attribute; 			/*保留*/ 

} ISO8583; 

ISO8583 Tbl8583[128] = 
{ 
/* FLD 1 */ {0,"BIT MAP,EXTENDED ", 8, 0, 0, 2, NULL,0}, 
/* FLD 2 */ {0,"RIMARY ACCOUNT NUMBER ", 30, 0, 2, 0, NULL,0}, 
/* FLD 3 */ {0,"ROCESSING CODE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 4 */ {0,"AMOUNT, TRANSACTION ", 12, 0, 0, 1, NULL,0}, 
/* FLD 5 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 6 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 7 */ {0,"TRANSACTION DATE AND TIME ", 10, 0, 0, 0, NULL,0}, 
/* FLD 8 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 9 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 10 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 11 */ {0,"SYSTEM TRACE AUDIT NUMBER ", 20, 0, 0, 1, NULL,0}, 
/* FLD 12 */ {0,"TIME, LOCAL TRANSACTION ", 6, 0, 0, 0, NULL,0}, 
/* FLD 13 */ {0,"DATE, LOCAL TRANSACTION ", 8, 0, 0, 0, NULL,0}, 
/* FLD 14 */ {0,"DATE, EXPIRATION ", 4, 0, 0, 0, NULL,0}, 
/* FLD 15 */ {0,"DATE, SETTLEMENT ", 4, 0, 0, 0, NULL,0}, 
/* FLD 16 */ {0,"NO USE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 17 */ {0,"DATE, CAPTURE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 18 */ {0,"MERCHANT'S TYPE ", 4, 0, 0, 0, NULL,0}, 
/* FLD 19 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 20 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 21 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 22 */ {0,"OINT OF SERVICE ENTRY MODE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 23 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 24 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 25 */ {0,"OINT OF SERVICE CONDITION CODE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 26 */ {0,"NO USE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 27 */ {0,"NO USE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 28 */ {0,"field27 ", 9, 0, 0, 0, NULL,0}, 
/* FLD 29 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 30 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 31 */ {0,"NO USE ", 8, 0, 1, 0, NULL,0}, 
/* FLD 32 */ {0,"ACQUIRER INSTITUTION ID. CODE ", 6, 0, 2, 0, NULL,0}, 
/* FLD 33 */ {0,"FORWARDING INSTITUTION ID. CODE ", 11, 0, 2, 0, NULL,0}, 
/* FLD 34 */ {0,"NO USE ", 28, 0, 2, 0, NULL,0}, 
/* FLD 35 */ {0,"TRACK 2 DATA ", 37, 0, 2, 0, NULL,0}, 
/* FLD 36 */ {0,"TRACK 3 DATA ",104, 0, 3, 0, NULL,0}, 
/* FLD 37 */ {0,"RETRIEVAL REFERENCE NUMBER ", 20, 0, 0, 0, NULL,0}, 
/* FLD 38 */ {0,"AUTH. IDENTIFICATION RESPONSE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 39 */ {0,"RESPONSE CODE ", 2, 0, 0, 0, NULL,0}, 
/* FLD 40 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 41 */ {0,"CARD ACCEPTOR TERMINAL ID. ", 8, 0, 0, 0, NULL,0}, 
/* FLD 42 */ {0,"CARD ACCEPTOR IDENTIFICATION CODE ", 15, 0, 0, 0, NULL,0}, 
/* FLD 43 */ {0,"CARD ACCEPTOR NAME LOCATION ", 40, 0, 0, 0, NULL,0}, 
/* FLD 44 */ {0,"ADDITIONAL RESPONSE DATA ", 25, 0, 2, 0, NULL,0}, 
/* FLD 45 */ {0,"NO USE ", 76, 0, 2, 0, NULL,0}, 
/* FLD 46 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 47 */ {0,"field47 ",999, 0, 3, 0, NULL,0}, 
/* FLD 48 */ {0,"ADDITIONAL DATA --- PRIVATE ",999, 0, 3, 0, NULL,0}, 
/* FLD 49 */ {0,"CURRENCY CODE,TRANSACTION ", 3, 0, 0, 0, NULL,0}, 
/* FLD 50 */ {0,"CURRENCY CODE,SETTLEMENT ", 3, 0, 0, 0, NULL,0}, 
/* FLD 51 */ {0,"NO USE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 52 */ {0,"ERSONAL IDENTIFICATION NUMBER DATA ", 8, 0, 0, 2, NULL,0}, 
/* FLD 53 */ {0,"SECURITY RELATED CONTROL INformATION", 16, 0, 0, 0, NULL,0}, 
/* FLD 54 */ {0,"ADDITIONAL AMOUNTS ",120, 0, 3, 0, NULL,0}, 
/* FLD 55 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 56 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 57 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 58 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 59 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 60 */ {0,"NO USE ", 5, 0, 3, 0, NULL,0}, 
/* FLD 61 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 62 */ {0,"NO USE ", 11, 0, 3, 0, NULL,0}, 
/* FLD 63 */ {0,"NO USE ", 11, 0, 3, 0, NULL,0}, 
/* FLD 64 */ {0,"MESSAGE AUTHENTICATION CODE FIELD ", 8, 0, 0, 2, NULL,0}, 
/* FLD 65 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 66 */ {0,"NO USE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 67 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 68 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 69 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 70 */ {0,"SYSTEM MANAGEMENT INformATION CODE ", 3, 0, 0, 0, NULL,0}, 
/* FLD 71 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 72 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 73 */ {0,"NO USE ", 6, 0, 0, 0, NULL,0}, 
/* FLD 74 */ {0,"NUMBER OF CREDITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 75 */ {0,"REVERSAL NUMBER OF CREDITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 76 */ {0,"NUMBER OF DEBITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 77 */ {0,"REVERSAL NUMBER OF DEBITS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 78 */ {0,"NUMBER OF TRANSFER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 79 */ {0,"REVERSAL NUMBER OF TRANSFER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 80 */ {0,"NUMBER OF INQUIRS ", 10, 0, 0, 0, NULL,0}, 
/* FLD 81 */ {0,"AUTHORIZATION NUMBER ", 10, 0, 0, 0, NULL,0}, 
/* FLD 82 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 83 */ {0,"CREDITS,TRANSCATION FEEAMOUNT ", 12, 0, 0, 0, NULL,0}, 
/* FLD 84 */ {0,"NO USE ", 12, 0, 0, 0, NULL,0}, 
/* FLD 85 */ {0,"DEBITS,TRANSCATION FEEAMOUNT ", 12, 0, 0, 0, NULL,0}, 
/* FLD 86 */ {0,"AMOUNT OF CREDITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 87 */ {0,"REVERSAL AMOUNT OF CREDITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 88 */ {0,"AMOUNT OF DEBITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 89 */ {0,"REVERSAL AMOUNT OF DEBITS ", 16, 0, 0, 0, NULL,0}, 
/* FLD 90 */ {0,"ORIGINAL DATA ELEMENTS ", 42, 0, 0, 0, NULL,0}, 
/* FLD 91 */ {0,"FILE UPDATE CODE ", 1, 0, 0, 0, NULL,0}, 
/* FLD 92 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 93 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 94 */ {0,"SERVICE INDICATOR ", 7, 0, 0, 0, NULL,0}, 
/* FLD 95 */ {0,"REPLACEMENT AMOUNTS ", 42, 0, 0, 0, NULL,0}, 
/* FLD 96 */ {0,"NO USE ", 8, 0, 0, 0, NULL,0}, 
/* FLD 97 */ {0,"AMOUNT OF NET SETTLEMENT ", 16, 0, 0, 0, NULL,0}, 
/* FLD 98 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 99 */ {0,"SETTLEMENT INSTITUTION ID ", 11, 0, 2, 0, NULL,0}, 
/* FLD 100 */ {0,"RECVEING INSTITUTION ID ", 11, 0, 2, 0, NULL,0}, 
/* FLD 101 */ {0,"FILENAME ", 17, 0, 2, 0, NULL,0}, 
/* FLD 102 */ {0,"ACCOUNT IDENTIFICATION1 ", 28, 0, 2, 0, NULL,0}, 
/* FLD 103 */ {0,"ACCOUNT IDENTIFICATION2 ", 28, 0, 2, 0, NULL,0}, 
/* FLD 104 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 105 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 106 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 107 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 108 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 109 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 110 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 111 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 112 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 113 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 114 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 115 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 116 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 117 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 118 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 119 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 120 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 121 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 122 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 123 */ {0,"NEW PIN DATA ", 8, 0, 3, 2, NULL,0}, 
/* FLD 124 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 125 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 126 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 127 */ {0,"NO USE ",999, 0, 3, 0, NULL,0}, 
/* FLD 128 */ {0,"MESSAGE AUTHENTICATION CODE FIELD ", 8, 0, 0, 2, NULL,0}, 
}; 


extern ISO8583 Tbl8583[128];



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

int Bank_AdjustCompareFile(INNER_TRANS_REQUEST *pNode, ST_BANK *bank, void *var_object1, void * var_object2, void *var_object3);

int Bank_GetRecvPacket(INNER_TRANS_REQUEST * pNode, ST_BANK *bank, void *recv_packet);





//#ifdef __cplusplus

//}

//#endif



#endif


