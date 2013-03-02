#ifndef _KSG_PUBFUNC_H_
#define _KSG_PUBFUNC_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>

//! 获取系统参数
/*!
 \param param 系统参数号
 \param value 系统参数值
 \return 成功返回0, 失败返回 -1
 */
int KsgGetSystemParam(int param,std::string& value);
//! mafiar one 卡物理ID转 wiegand 卡物理ID
/*!
 \param m1_no mafiar one 卡物理ID
 \param wg_no wiegand 卡物理ID
 \return 失败返回 
 */
int KsgCardID_M1_2_WG(const char *m1_no,char *wg_no,int wg_len = 8);

int KsgCardPhyNo_dec2hex(unsigned long card_no,char phyno[9]);


#endif // _KSG_PUBFUNC_H_
