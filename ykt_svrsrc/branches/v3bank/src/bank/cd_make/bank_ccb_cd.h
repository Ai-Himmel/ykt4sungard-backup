/* ----------------------------------------------------------
 * 程序名称：bank_ccb_cd.h
 * 创建日期：2010-10-26
 * 程序作者：xlh
 * 版本信息：1.0.0.0
 * 程序功能：成电建行接口的头文件定义
 * ----------------------------------------------------------*/


#ifndef	__BANK_CCB_CD_H__
#define	__BANK_CCB_CD_H__

#define REGISTRATION_CODE      	 "100001"     //签到签退
#define SIGNED_CODE   		        "100002"     //签约
#define BATCHSIGNE_CODE   		 "100003"     //批量签约
#define SIGNED_RESULTS_CODE   	 "100004"    //签约结果
#define TRANS_CODE   		        "100005"     //圈存交易
#define REV_TRANS_CODE   	        "100006"     //圈存交易冲正
#define DOWNLOAD_TRANS_CODE    "100007"    //交易记录下载

#pragma pack(1)
typedef struct{
       char  packlen[5];				// 报文长度
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
	PACKHEAD head;                              //包头
	char SignInOut[1];				// 签到签退标志1,0
}SignInOut_REQ;

typedef struct{
	PACKHEAD head;                              //包头
	char Func[1];						//功能号
	char SchoolCard[32];				//校园一卡通卡号
	char  SchoolName[40];                    //一卡通户名
	char SchoolNo[18];				//一卡通身份证号
	char BankCard[32];				// 银行卡卡号
}ToRegister_REQ;


typedef struct{
	PACKHEAD head;                              //包头
	char SchoolCard[32];				// 一卡通卡号
	char SchoolName[10];				//一卡通户名
	char SchoolNo[18];				//一卡通身份证号
	char RopAmt[20];					// 圈存额度
	char BankCard[32];				// 银行卡卡号
}TRANS_REQ;


typedef struct{
	PACKHEAD head;                              //包头
	char Counts[16];				// 人数
}BatchRegister_REQ;


typedef struct{
	PACKHEAD head;                              //包头
	char RegisterDate[8];				// 批量签约日期
	char OldTransBankId[16];                //原学校业务流水号
}BatchRegisterResult_REQ;

typedef struct{
	PACKHEAD head;                              //包头
	char Counts[16];              			  //人数
}BatchRegisterResult_ANS;

typedef struct{
	PACKHEAD head;                              //包头
	char OldTxdate[8];				// 原交易日期
	char OldTransBankId[16];			//原学校业务流水号
	char OldRopAmt[20];				//原圈存额度
}REVTRANS_REQ;

typedef struct{
	PACKHEAD head;                              //包头
	char CompareDate[8];				// 对帐日期
}ListDown_REQ;
typedef struct{
	PACKHEAD head;                              //包头
	char CompareDate[8];				// 对帐日期
	char AnsNumSuc[8];                        //成功
	char AnsNumFal[8];                        //失败
	char RopeCntAmt[20];                     //总金额
}ListDown_ans;

#pragma pack()
#endif

