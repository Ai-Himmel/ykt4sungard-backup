/* ----------------------------------------------------------
 * 程序名称：bank_iccb_nd.h
 * 创建日期：2010-10-26
 * 程序作者：xlh
 * 版本信息：1.0.0.0
 * 程序功能：成电建行接口的头文件定义
 * ----------------------------------------------------------*/


#ifndef __BANK_ICBC_ND_H__
#define __BANK_ICBC_ND_H__

#define QUERY_CODE               "000201"     //余额查询
#define TRANS_CODE           "000202"     //资金转入
#define REV_TRANS_CODE       "000203"     //圈存交易冲正
#define CHECK_CODE           "000301"    //交易记录对丈帐
#define SCHOOLCODE           "CNDCD19005"    //学校代码
#pragma pack(1)
typedef struct {
    char PACKLEN[4];                // 包长度
    char RespCode[4];                    //响应码
    char RespMess[100];                  //响应信息
} PACKHEAD;

typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
    char DCC_TERM[8];               // 终端号
    char DCC_LS[6];                 // 圈存流水号
    char DCC_ID_NO[18];             // 学号
    char DCC_ACC_NO[20];            // 银行卡号
    char DCC_TYPE[1];               // 证件类型
    char DCC_NO[20];                    //证件号码
    char DCC_NAME[20];              // 姓名
    char DCC_DDP_RMRK[32];          // 备注1
    char DCC_DEP_RMRK[32];          // 备注2
    char DCC_DRW_RMRK[32];          // 备注3
} QUERY_BODY_REQ;

typedef struct {
    PACKHEAD head;
    QUERY_BODY_REQ body;
} QUERY_REQ;

typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
    char DCC_TERM[8];               // 终端号
    char DCC_LS[6];                 // 圈存流水号
    char DCC_BANK_LS[20];                   //交易流水
    char DCC_ID_NO[18];             // 学号
    char DCC_ACC_NO[20];            // 银行卡号
    char DCC_TYPE[1];               // 证件类型
    char DCC_NO[20];                    //证件号码
    char DCC_NAME[20];              // 姓名
    char DCC_BAL[18];               //帐号余额
    char DCC_AVL_BAL[18];           // 可用余额
    char DCC_MEMO[40];              // 备注
} QUERY_BODY_ANS;

typedef struct {
    PACKHEAD head;
    QUERY_BODY_ANS body;
} QUERY_ANS;

typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
    char DCC_TERM[8];               // 终端号
    char DCC_LS[6];                 // 圈存流水号
    char DCC_ID_NO[18];             // 学号
    char DCC_ACC_NO[20];            // 银行卡号
    char DCC_TYPE[1];               // 证件类型
    char DCC_NO[20];                    //证件号码
    char DCC_NAME[20];              // 姓名
    char DCC_AMT[18];                          //交易金额
    char DCC_DDP_RMRK[32];          // 备注1
    char DCC_DEP_RMRK[32];          // 备注2
    char DCC_DRW_RMRK[32];          // 备注3
} TRANS_BODY_REQ;

typedef struct {
    PACKHEAD head;
    TRANS_BODY_REQ body;
} TRANS_REQ;


typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
    char DCC_TERM[8];               // 终端号
    char DCC_LS[6];                 // 圈存流水号
    char DCC_BANK_LS[20];                   //交易流水
    char DCC_ID_NO[18];             // 学号
    char DCC_ACC_NO[20];            // 银行卡号
    char DCC_TYPE[1];               // 证件类型
    char DCC_NO[20];                    //证件号码
    char DCC_NAME[20];              // 姓名
    char DCC_AMT[18];               //帐号余额
    char DCC_MEMO[40];              // 备注
} TRANS_BODY_ANS;

typedef struct {
    PACKHEAD head;
    TRANS_BODY_ANS body;
} TRANS_ANS;

typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
    char DCC_TERM[8];               // 终端号
    char DCC_LS[6];                 // 圈存流水号
    char DCC_BANK_LS[20];           //银行流水号
    char DCC_ACC_NO[20];            // 银行原交易流水号
    char DCC_MEMO[40];              // 备注
} REVTRANS_BODY_REQ;

typedef struct {
    PACKHEAD head;
    REVTRANS_BODY_REQ body;
} RECTRANS_REQ;

typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
    char DCC_BANK_LS[20];                   //交易流水
    char DCC_MEMO[40];              // 备注
} RECTRANS_BODY_ANS;

typedef struct {
    PACKHEAD head;
    RECTRANS_BODY_ANS body;
} RECTRANS_ANS;

typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
} CHECK_BODY_REQ;

typedef struct {
    PACKHEAD head;
    CHECK_BODY_REQ body;
} CHECK_REQ;


typedef struct {
    char DCC_CODE[6];               // 圈存交易码
    char DCC_SCHID[10];             //学校代号
    char DCC_DATE[8];               //交易日期
    char DCC_COUNT[10];                      //交易流水
    char DCC_SUM[12];                          //交易流水
    char DCC_FILE[40];              // 对帐文件名
} CHECK_BODY_ANS;

typedef struct {
    PACKHEAD head;
    CHECK_BODY_ANS body;
} CHECK_ANS;

#pragma pack()
#endif

