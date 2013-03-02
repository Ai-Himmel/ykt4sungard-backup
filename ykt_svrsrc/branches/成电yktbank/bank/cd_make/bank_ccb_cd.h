/* ----------------------------------------------------------
 * 程序名称：bank_ccb_cd.h
 * 创建日期：2010-10-26
 * 程序作者：xlh
 * 版本信息：1.0.0.0
 * 程序功能：成电建行接口的头文件定义
 * ----------------------------------------------------------*/

#define _CI_DEGUG_DES_
#ifndef	__BANK_BCC_CD_H__
#define	__BANK_BCC_CD_H__
#define REQ_PACK_LEN 157
#define ANS_PACK_LEN 56

#define REV_REQ_PACK_LEN 107
#define REV_ANS_PACK_LEN 40

#define REGISTRATION_CODE      	 "100001"     //签到签退
#define SIGNED_CODE   		        "100002"     //签约
#define BATCHSIGNE_CODE   		 "100003"     //批量签约
#define SIGNED_RESULTS_CODE   	 "100004"    //签约结果
#define TRANS_CODE   		        "100005"     //圈存交易
#define REV_TRANS_CODE   	        "100006"     //圈存交易冲正
#define DOWNLOAD_TRANS_CODE    "100007"    //交易记录下载

#pragma pack(1)
typedef struct{
	char Txcode[6];				// 交易码
	char TxDate[8];				// 交易日期
	char TxTime[8];				// 交易时间
	char Operator[12];			//操作员
	char Checker[12];		      		 //  复核员
	char TxChannel[4];			// 发起方标示(学校代码)
	char TxOrgNo[9];				// 身份证号
	char  BankSerial[16];			// 银行流水号
	char Serial[16];				// 第三方流水
	char FileNames[50];                 //文件名称
	char RespCode[5];                    //响应码
	char RespMess[64];                  //响应信息
}PACKHEAD;

typedef struct{
	char SignInOut[1];				// 签到签退标志1,0
}SignInOut_body_REQ;
typedef struct{
	PACKHEAD head;                              //包头
	SignInOut_body_REQ body;				
}SignInOut_REQ;

typedef struct{	                         
	char Func[1];						//功能号
	char SchoolCard[32];				//校园一卡通卡号
	char  SchoolName[40];                    //一卡通户名
	char SchoolNo[18];				//一卡通身份证号
	char BankCard[32];				// 银行卡卡号
}ToRegister_body_REQ;

typedef struct{
	PACKHEAD head;                              //包头
	ToRegister_body_REQ body;			// 银行卡卡号
}ToRegister_REQ;


typedef struct{
	char SchoolCard[32];				// 一卡通卡号
	char SchoolName[10];				//一卡通户名
	char SchoolNo[18];				//一卡通身份证号
	char RopAmt[20];					// 圈存额度
	char BankCard[32];				// 银行卡卡号
}TRANS_body_REQ;

typedef struct{
	PACKHEAD head;                              //包头
	TRANS_body_REQ body;
}TRANS_REQ;

typedef struct{
	char Counts[16];				// 人数
}BatchRegister_body_REQ;

typedef struct{
	PACKHEAD head;                              //包头
	BatchRegister_body_REQ body;
}BatchRegister_REQ;

typedef struct{
	char RegisterDate[8];				// 批量签约日期
	char OldTransBankId[16];                //原学校业务流水号
}BatchRegisterResult_body_REQ;
typedef struct{
	PACKHEAD head;                              //包头
	BatchRegisterResult_body_REQ body;
}BatchRegisterResult_REQ;

typedef struct{
	char Counts[16];              			  //人数
}BatchRegisterResult_body_ANS;

typedef struct{
	PACKHEAD head;                              //包头
	BatchRegisterResult_body_ANS body;   			 
}BatchRegisterResult_ANS;

typedef struct{
	char OldTxdate[8];				// 原交易日期
	char OldTransBankId[16];			//原学校业务流水号
	char OldRopAmt[20];				//原圈存额度
}REVTRANS_body_REQ;
typedef struct{
	PACKHEAD head;                              //包头
	REVTRANS_body_REQ body;
}REVTRANS_REQ;

typedef struct{
	char CompareDate[8];				// 对帐日期
}ListDown_body_REQ;
typedef struct{
	PACKHEAD head;                              //包头
	ListDown_body_REQ body;
}ListDown_REQ;

typedef struct{
	char CompareDate[8];				// 对帐日期
	char AnsNumSuc[8];                        //成功
	char AnsNumFal[8];                        //失败
	char RopeCntAmt[20];                     //总金额
}ListDown_body_ans;
typedef struct{
	PACKHEAD head;                              //包头
	ListDown_body_ans body;
}ListDown_ans;

#pragma pack()

#endif

