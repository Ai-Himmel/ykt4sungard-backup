#ifndef __BANK_TYPE_H_
#define __BANK_TYPE_H_

/******************************统一银行数据结构********************************
* 文件内容: 圈存银行端数据结构说明
* 文件名:	banktype.h
* 说明:		实现银行通讯数据结构和对账结构
* 创建:		李翔
* 时间:		2008-05-23
* 修改原因:
*****************************************************************************/

#pragma pack(1)

// 上海工行对账文件数据结构
typedef struct	
{
	char	device_id[27];					// 设备ID号
	char    cmp_date[8];					// 交易发生时间
	char    bank_account[25];				// 银行卡号
	char    trans_money[17];				// 转帐金额
	char    line_split[4];					// \r\n
}BANK_SHGH_TRADE_COMP_STRUCT;


// 哈尔滨工程大学注册缴费文件格式
typedef struct	
{
	char	stuemp_no[22];					// 学工号
	char 	split1[1];						// ','
	char    name[20];						// 姓名
	char 	split2[1];						// ','
	char    flag[1];						// 转卡标志
	char 	split3[1];						// ','
	char    log_flag[1];					// 缴费登陆标志
	char       split4[1];                               // ','
	char    semeseter[30];                                //学期标识
	char    line_split[4];					// \r\n
}HRBGC_ZCJF_FILE;


#pragma pack()

#endif

