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

#endif // _KSG_PUBFUNC_H_
