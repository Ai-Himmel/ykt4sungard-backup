/* ----------------------------------------------------------
 * 程序名称：bank_abc_swust.h
 * 创建日期：2011-06-20
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：西科大农业银行接口的头文件定义
 * ----------------------------------------------------------*/


#ifndef	__BANK_ABC_SWUST_H__
#define	__BANK_ABC_SWUST_H__

#define QUERY_BALA		"8920"						//查询银行帐户余额
#define TRANS_CODE   		"8914"						//转账（圈存）
#define REV_TRANS_CODE   	"8915"						//转账（圈存）冲正
#define BIND_BANK		"8912"						//签约
#define UN_BIND_BANK		"8913"						//解约
#define BANK_SIGN_IN		"8910"						// 向银行签到
#define BANK_ACCCHECK      "8918"						//对账

#define FIXKEY			"12345678"					// 初始密钥

#define SCHOOLCODE	"MXYK05"						// 西科大（绵阳）公司编码
#define XML_HEAD		"<?xml version=\"1.0\"  encoding=\"gb2312\" ?>"


#endif

