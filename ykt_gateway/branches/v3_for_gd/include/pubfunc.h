#ifndef _KSG_PUBFUNC_H_
#define _KSG_PUBFUNC_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>

//! ��ȡϵͳ����
/*!
 \param param ϵͳ������
 \param value ϵͳ����ֵ
 \return �ɹ�����0, ʧ�ܷ��� -1
 */
int KsgGetSystemParam(int param,std::string& value);
//! mafiar one ������IDת wiegand ������ID
/*!
 \param m1_no mafiar one ������ID
 \param wg_no wiegand ������ID
 \return ʧ�ܷ��� 
 */
int KsgCardID_M1_2_WG(const char *m1_no,char *wg_no,int wg_len = 8);

int KsgCardPhyNo_dec2hex(unsigned long card_no,char phyno[9]);


#endif // _KSG_PUBFUNC_H_
