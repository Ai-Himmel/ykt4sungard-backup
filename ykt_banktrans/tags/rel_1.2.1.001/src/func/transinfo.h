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


#ifndef	__transinfo_h__
#define	__transinfo_h__
#include "bank.h"

//////////////////////////// constant defined ///////////////////////////////
#ifndef	NULL
#define	NULL	0
#endif

#ifdef __cplusplus
extern "C" {
#endif

//圈存用到的全局配置文件参数
extern int DRTP_BRANCH;
extern int BCC_BASEFUNCNO;
extern int TIMEOUT;
extern char  COMPACC_TIME[2+1];
extern int	 LOGIN_MODE;
extern int  AUTH_MODE;
extern char	DRTP_IP[20];
extern int		DRTP_PORT;	

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
#define TRADE_INNER_UPDATE_CARDINFO 240105	//更新卡信息
#define TRADE_INNER_TRANSFER_WFAIL	240111	//转账写卡失败
#define TRADE_INNER_QUERYWATER	240201	//水控转账明细查询
#define TRADE_INNER_BUYWATER		240202	//水控转账



//////////////////////////状态检查宏////////////////////////////////////////
// 检查银行登陆状态，在需要检查状态的地方调用该宏。如果有必要，加上信号量操作
#define BANK_LOGIN	(shm[1]==1)

// 检查银行通信状态，在需要检查状态的地方调用该宏。如果有必要，加上信号量操作
#define BANK_CONNECT	(shm[3]==1)

// !!! 在取用银行密码时，一定要获取信号量 p(semid); operations...; v(semid)


 /////////////////////////程序常用数据块/////////////////////////////////////

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

//对帐过程
//int Do_Compare(BANK_TRANS_REQUEST *pBankTrans );

//农行的对帐过程，不发送交易报
int Do_Compare_file();

//手动的对帐函数，应急使用的
int Do_Compare_file_shoudong();


//划拨过程
//int Do_Transfer(BANK_TRANS_REQUEST *pBankTrans);
int SetHeadCol(ST_CPACK *in_cpack, ...);
int device_login_yes_or_no(int device_id);
int device_login_yes_or_noEx(int device_id, char *szMsg);
int verify_card_password(int card_id,char *stuemp_no,int cut_id,char *password);
int verify_card_passwordEx(int card_id,char *stuemp_no,int cut_id,char *password, char *szMsg);
int verify_sch_bank_relationship(int cut_id,int card_id,char *stuemp_no,int area_id,char *bankcard_no);

/****************************************************
银行端交易处理函数
lq, 20050310，移到bank.h去，以与bu相关代码脱离
****************************************************/
#ifdef __cplusplus
	}
#endif

 ////////////////////////////////////////////////////////////////////////////

 #endif
