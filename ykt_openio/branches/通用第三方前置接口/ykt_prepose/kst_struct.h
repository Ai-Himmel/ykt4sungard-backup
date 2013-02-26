//********************************************************
//kst_struct.h
//********************************************************
#ifndef _KST_STRUCT_H
#define _KST_STRUCT_H
/////////////////////////////////////////////////////////
//     艾利的查询
/////////////////////////////////////////////////////////
typedef struct kst_ald_sqr
{
	char idf[8];              //标识码
	char trcd[4];             //交易码
	char roomname[30];         //收款帐号
	char stdu[20];            //学工号
	char name[60];            //姓名
	char tmlid[12];           //终端
	char  amt[30] ;           //金额
    char area[30];            //附加信息
}ald_sqr;

typedef struct kst_ald_sqrrec
{
	char idf[8];              //标识码
	char trcd[4];             //交易码
	char roomname[30];         //收款帐号
	char accountmsg[100];     //帐号信息
	char addamt[30] ;         //附加金额
    char msg[4];              //信息
}ald_sqrrec;

////////////////////////////////////////////////////
//           艾利的转账
////////////////////////////////////////////////////

typedef struct kst_ald_pay
{
	char idf[8];              //标识码
	char trcd[4];             //交易码
	char account[30];         //收款帐号
    char payaccount[30];      //支付帐号
	char customerid[30];      //客户号
	char stdu[20];            //学工号
	char name[60];            //姓名
	char schid[3];            //学校号
	char tmlid[12];           //交易终端号
	char  bfamt[30];          //交易前金额
	char  payamt[30] ;        //支付金额
    char datetime[14];        //交易时间
	char rfn[14];             //交易参考号
	char paycode[30];         //支付代码
	char paytype[4];          //交易类型
	char remark[100];         //备注
    char code[32];            //验证码
}ald_pay;

typedef struct kst_ald_payrec
{
	char idf[8];              //标识码
	char trcd[4];             //交易码
	char account[30];         //收款帐号
	char accountmsg[100];     //帐号信息
	char addamt[30] ;         //附加金额
	char rfn[14];             //交易参考号
	char result[4];          //交易结果
	char remark[100];            //附加信息
	char code[32];            //验证码
}ald_payrec;
/////////////////////////////////////////////////////////////
//                    冲正交易
/////////////////////////////////////////////////////////////

typedef struct  kst_ald_rvs
{
	char idf[8];              //标识码
	char trcd[4];             //交易码
	char account[30];         //收款帐号
	char tmlid[12];           //交易终端号
	char payamt[30] ;        //支付金额
	char rfn[14];             //交易参考号
	char remark[100];         //备注
    char code[32];            //验证码
}ald_rvs;

typedef struct kst_ald_rvsrec
{
	char idf[8];              //标识码
	char trcd[4];             //交易码
	char account[30];         //收款帐号
	char accountmsg[100];     //帐号信息
	char addamt[30] ;         //附加金额
	char rfn[14];             //交易参考号
	char result[30];          //交易结果
	char area[30];            //附加信息
	char code[32];            //验证码
}ald_rvsrec;
#endif