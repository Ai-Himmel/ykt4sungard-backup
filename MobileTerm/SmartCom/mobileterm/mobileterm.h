// mobileterm.h : main header file for the mobileterm DLL
//
#ifndef _MOBILETERM_H_
#define _MOBILETERM_H_
/** 
 * 模块名					39手持机封装库
 * 文件名					mobileterm.h
 * 文件实现功能				封装39函数库
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-10-17
 * 备注
 * $Id$
 */

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CmobiletermApp
// See mobileterm.cpp for the implementation of this class
//

class CmobiletermApp : public CWinApp
{
public:
	CmobiletermApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#ifndef CALLAPI
#define CALLAPI __stdcall
#endif

#ifndef uchar8
#define uchar8 unsigned char
#endif

#define E_COM_NOT_OPEN 99
#define E_LOAD_SMARTCOM 100
#define E_COM_BAND 101
#define E_SMART_TERM_NO 102
#define E_NOT_HAS_KEY 103
#define E_SMART_TERM_INFO 104

/** 
 * @brief 流水结构定义
 */
typedef struct {
	uchar8 phyid[4];				// 设备物理ID，HEX格式
	int ver;						// 通讯版本
	int runreason;					// 启动原因
	int serial_no;					// 流水号
	int card_id;					// 交易卡号
	char tx_datetime[13];			// 交易日期时间，yymmddHHnnss
	int tx_cnt;						// 该卡累计交易次数
	int out_card_amount;			// 出卡值，单位分
	int in_card_amount;				// 入卡值，单位分
	int tx_trade_amount;			// 本次交易金额，单位分
	uchar8 tx_mark;					// 交易代码
	uchar8 crc[2];					// CRC校验码
}MBL_TRADE_LOG;

/** 
 * @brief 手持机物理信息结构定义
 */
typedef struct {
	int port;			// 串口号
	int termno;			// 机号
	uchar8 commision[4];// 设备授权号，默认为物理ID
	uchar8 phyid[4];	// 设备物理ID
	uchar8 level_array[5];// 不用 , 全部为0
	int level;			  // 不用，为0
	uchar8 termtype[2];	// 机型代码 hex 高位在前
	char verdate[9];	// 手持机程序日期 yymmddhh
}SMART_TERMINAL_T;

#endif // _MOBILETERM_H_
