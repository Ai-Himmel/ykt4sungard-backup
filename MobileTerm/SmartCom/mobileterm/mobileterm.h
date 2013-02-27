// mobileterm.h : main header file for the mobileterm DLL
//
#ifndef _MOBILETERM_H_
#define _MOBILETERM_H_
/** 
 * ģ����					39�ֳֻ���װ��
 * �ļ���					mobileterm.h
 * �ļ�ʵ�ֹ���				��װ39������
 * ����						����
 * �汾						V0.1
 * ����						2005-10-17
 * ��ע
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
 * @brief ��ˮ�ṹ����
 */
typedef struct {
	uchar8 phyid[4];				// �豸����ID��HEX��ʽ
	int ver;						// ͨѶ�汾
	int runreason;					// ����ԭ��
	int serial_no;					// ��ˮ��
	int card_id;					// ���׿���
	char tx_datetime[13];			// ��������ʱ�䣬yymmddHHnnss
	int tx_cnt;						// �ÿ��ۼƽ��״���
	int out_card_amount;			// ����ֵ����λ��
	int in_card_amount;				// �뿨ֵ����λ��
	int tx_trade_amount;			// ���ν��׽���λ��
	uchar8 tx_mark;					// ���״���
	uchar8 crc[2];					// CRCУ����
}MBL_TRADE_LOG;

/** 
 * @brief �ֳֻ�������Ϣ�ṹ����
 */
typedef struct {
	int port;			// ���ں�
	int termno;			// ����
	uchar8 commision[4];// �豸��Ȩ�ţ�Ĭ��Ϊ����ID
	uchar8 phyid[4];	// �豸����ID
	uchar8 level_array[5];// ���� , ȫ��Ϊ0
	int level;			  // ���ã�Ϊ0
	uchar8 termtype[2];	// ���ʹ��� hex ��λ��ǰ
	char verdate[9];	// �ֳֻ��������� yymmddhh
}SMART_TERMINAL_T;

#endif // _MOBILETERM_H_
