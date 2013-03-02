/* ----------------------------------------------------------
 * 程序名称：transinfo.h
 * 创建日期：2004-08-24
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：银行转帐头文件
 * ----------------------------------------------------------
 * 修改日期: 2004-09-09
 * 修改人员: 韩海东
 * 修改描述: 统一规范代码
 * 版本信息：1.0.0.1
 * 备注信息
 * ----------------------------------------------------------
 * 修改日期: 2005-03-10
 * 修改人员: 林钦
 * 修改描述: 将与银行通信部分移到bank.h，以与bu代码分离，供bankguard调用
 * 版本信息：1.0.1.1
 * 备注信息
 * ----------------------------------------------------------*/

#include "bank.h"

#ifndef	__transinfo_h__
#define	__transinfo_h__
//////////////////////////// constant defined ///////////////////////////////
#ifndef	NULL
#define	NULL	0
#endif

#ifdef __cplusplus
extern "C" {
#endif


 /////////////////////////// 内部交易代码  ///////////////////////////////
#define TRADE_INNER_QUERYBANK		240007	//查询银行卡
#define TRADE_INNER_TRANS			240001	//自助转帐
#define TRADE_INNER_AUTOTRANS		240002	//批量转帐
#define TRADE_INNER_FEE			240005	//缴费
#define TRADE_INNER_ADDRELATION	240008	//增加对应关系
#define TRADE_INNER_DELRELATION	240009 	//5、删除对应关系
#define TRADE_INNER_POSLOGIN		240101 	//6、登陆
#define TRADE_INNER_QUERYINNER	240102 	//7、查询校园卡
#define TRADE_INNER_CHANGEPWD	930003 	//8、修改消费密码
#define TRADE_INNER_LOST			930001 	//9、校园卡挂失
#define TRADE_INNER_UNLOST		930002 	//10、校园卡解挂
#define TRADE_INNER_QUERYSERIAL	240106	//查询转帐流水
#define TRADE_INNER_LOGIN			241031	//前置机到银行签到
#define TRADE_INNER_DETRANS		241011	//转帐冲正
#define TRADE_INNER_WRITEERRCARD 240107	//写卡失败更新卡状态
#define TRADE_INNER_QUERYSUBSIDY	240103	//查询补助
#define TRADE_INNER_GETSUBSIDY	240104	//领取补助

#define TRADE_INNER_QUERYWATER	240201	//水控转账明细查询
#define TRADE_INNER_BUYWATER		240202	//水控转账
#define TRADE_INNER_BIND_METER	240203	//绑定水表
#define TRADE_INNER_UNBIND_METER	240204   //取消水表绑定
#define TRADE_INNER_WATER_WFAIL	240111	//水控转账写卡失败

#define TRADE_INNER_POWER_TRANS	240206	//电控转账
#define TRADE_INNER_POWER_QUERY	240207	//电控转账查询
#define TRADE_INNER_POWER_WFAIL	240209	//电控转账失败
#define TRADE_INNER_POWER_QUERY_DORM 240208 //电控转账宿舍信息查询


 /////////////////////////////////////////////////////////////////////////////

 #define	PIN_TYPE_GDC					0x01	//输入校园卡密码
 #define	PIN_TYPE_BC					0x02	//输入银行卡密码
 #define	PIN_TYPE_BOTH					0x04	//输入校园卡+银行卡密码

 #define	TRANSFER_MODE_SINGLE_GDC	0x01	//single card (  )
 #define	TRANSFER_MODE_SINGLE_BC		0x02	//single card ( BC )
 #define	TRANSFER_MODE_DUAL			0x04	//dual card

/////////////////////////////////////////////////////////////////////////////

//定义服务的运行状态
#define	TRADECORE_STATE_STOP				0
#define	TRADECORE_STATE_INITRUN			1
#define	TRADECORE_STATE_PRERUN			2
#define	TRADECORE_STATE_RUNNING			3
#define	TRADECORE_STATE_PRESTOP			4

//定义任务宏
#define	TRADECORE_TASK_NONE				0	//没有任务
#define	TRADECORE_TASK_TRANS				1	//自助转帐	require bank
#define	TRADECORE_TASK_AGENTFEE			2	//代收费	require bank
#define	TRADECORE_TASK_QUERYBANKBALANCE 3	//查询银行卡余额	require bank
#define	TRADECORE_TASK_QUERYCARDBALANCE  4	//查询校园卡余额
#define	TRADECORE_TASK_CHGCARDPWD		5	//修改校园卡密码
#define	TRADECORE_TASK_BUILDRELATION	6	//建立对应关系		may require bank
#define	TRADECORE_TASK_CANCELRELATION	7	//取消对应关系		may require bank
#define	TRADECORE_TASK_DETRANS			8	//自助转帐冲正		require bank
#define	TRADECORE_TASK_AUTOTRANS		9	//自动转帐require bank
#define	TRADECORE_TASK_CARDLOST			10	//挂失
#define	TRADECORE_TASK_CARDUNLOST		11	//解挂
#define	TRADECORE_TASK_BANKLOST			12	//银行卡挂失

//定义任务执行步骤
#define	TRADECORE_STEP_QUERYCARD		1		//查询校园卡
#define	TRADECORE_STEP_BANKTRANS		2		//银行转账
#define	TRADECORE_STEP_BANKDETRANS		3		//银行冲正
#define	TRADECORE_STEP_CARDACC			4		//入账
#define	TRADECORE_STEP_NOTIFYPOS		5		//通知POS
#define	TRADECORE_STEP_CHGPWD			6		//校园卡改密码
#define	TRADECORE_STEP_QUERYBANKBALANCE	7		//查询银行卡余额
#define	TRADECORE_STEP_BANKAGENTFEE		8		//代收费
#define	TRADECORE_STEP_CARDLOST			9		//校园卡挂失
#define	TRADECORE_STEP_CARDUNLOST		10		//校园卡解挂
#define	TRADECORE_STEP_BANKLOST			11		//银行卡挂失
//交易种类及交易代码
#define	TRADE_CODE_POSLOGIN		801	//pos登陆
#define	TRADE_CODE_NOSYNCNOTIFY	803	//不同步通知
#define	TRADE_CODE_POSTRANS		201	//自助转账
#define	TRADE_CODE_POSCHARGE	203	//代收费
#define	TRADE_CODE_QUERYBANK	351	//查询银行卡余额
#define	TRADE_CODE_QUERYCARD	353	//查询校园卡余额
#define	TRADE_CODE_CARDLOST		357	//校园卡挂失
#define	TRADE_CODE_CHANGEPASS	355	//校园卡更改密码
#define	TRADE_CODE_CARDUNLOST	359	//校园卡解除挂失
#define	TRADE_CODE_CREATECORR	321	//POS生成对应关系
#define	TRADE_CODE_DELCORR		323	//pos删除对应关系
#define	TRADE_CODE_AUTOTRANS	205	//自动转账


//////////////////////////状态检查宏////////////////////////////////////////
// 检查银行登陆状态，在需要检查状态的地方调用该宏。如果有必要，加上信号量操作
#define BANK_LOGIN	(shm[1]==1)

// 检查银行通信状态，在需要检查状态的地方调用该宏。如果有必要，加上信号量操作
#define BANK_CONNECT	(shm[3]==1)

// !!! 在取用银行密码时，一定要获取信号量 p(semid); operations...; v(semid)


 /////////////////////////程序常用数据块/////////////////////////////////////

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


/****************************************************
校园端交易处理函数
****************************************************/

//POS登陆	240101
int Pos_Login(INNER_TRANS_REQUEST * pNode);

//查询校园卡余额
int Pos_QuerySchool(INNER_TRANS_REQUEST * pNode);

//查询银行卡余额
int Pos_QueryBank(INNER_TRANS_REQUEST * pNode);

//修改校园卡密码
int Pos_ChangePwd(INNER_TRANS_REQUEST * pNode);

//挂失校园卡
int Pos_LostCard(INNER_TRANS_REQUEST * pNode);

//解挂校园卡
int Pos_UnlostCard(INNER_TRANS_REQUEST * pNode);

//POS转帐
int Pos_Transfer(INNER_TRANS_REQUEST * pNode);

//POS缴费
int Pos_Fee(INNER_TRANS_REQUEST * pNode);

//增加对应关系
int Pos_AddRelation(INNER_TRANS_REQUEST * pNode);

//删除对应关系
int Pos_DelRelation(INNER_TRANS_REQUEST * pNode);

//银行失败进行冲正，冲正添加流水
int DelTrans(INNER_TRANS_REQUEST * pnode,int other_serial_no);

//圈存机写卡失败冲正(实际并不冲正，只是改写卡状态)
int Pos_WriteErrCard(INNER_TRANS_REQUEST * pNode);

/****************************************************
银行端交易处理函数
lq, 20050310，移到bank.h去，以与bu相关代码脱离
****************************************************/
#ifdef __cplusplus
	}
#endif

 ////////////////////////////////////////////////////////////////////////////

 #endif
