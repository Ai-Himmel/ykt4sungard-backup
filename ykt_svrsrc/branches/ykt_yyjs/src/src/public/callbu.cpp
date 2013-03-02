/********************************************************
* ʵ��BCC֮��Զ���໥��������
* �ļ���: callbu.cpp
* ˵��: �Դ�������ֱ�ӵĺ����ͽṹ���з�װ
* ����: ����
* ʱ��: 2007-07-02
* �޸�ԭ��: 
**********************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "callbu.h"
#include "pubfunc.h"
#include "svrlink.h"
#include "pubfunc.h"

extern CSvrLink g_SvrLink;

CBccExtPack::CBccExtPack()
{
	ResetNormalCPack(&(m_bcc_ext_pack.sPack), 0, 1);
	ResetNormalCPack(&(m_bcc_ext_pack.aPack), 0, 1);
	memset(&(m_bcc_ext_pack.ArrayPack), 0, sizeof(m_bcc_ext_pack.ArrayPack));
	m_bcc_ext_pack.time_out = 4;
	m_error_code = 0;
	memset(m_error_msg, 0, sizeof(m_error_msg));
}

CBccExtPack::CBccExtPack(BCC_EXT_PACK *ext_pack)
{
	ResetNormalCPack(&(m_bcc_ext_pack.sPack), 0, 1);
	ResetNormalCPack(&(m_bcc_ext_pack.aPack), 0, 1);
	memset(&(m_bcc_ext_pack.ArrayPack), 0, sizeof(m_bcc_ext_pack.ArrayPack));
	memcpy(&m_bcc_ext_pack.sPack.pack, &(ext_pack->sPack.pack), 
	sizeof(m_bcc_ext_pack.sPack.pack));
	m_bcc_ext_pack.sPack.head.RequestType = ext_pack->request_func_no;	// �����ܺ�
	m_bcc_ext_pack.drtp_node = ext_pack->drtp_node;						// drtp�ڵ��
	m_bcc_ext_pack.bcc_main_func = ext_pack->bcc_main_func;				// bcc�����ܺ�
	m_bcc_ext_pack.time_out = 4;
	m_error_code = 0;
	memset(m_error_msg, 0, sizeof(m_error_msg));
//	writelog(LOG_ERR,"drtp_node=[%d], bcc_main_func=[%d], request_func=[%d]",m_bcc_ext_pack.drtp_node, 
//	m_bcc_ext_pack.bcc_main_func, m_bcc_ext_pack.sPack.head.RequestType);
}

CBccExtPack::~CBccExtPack()
{

}

/*================================================================ 
* ��������    SetHeadCol
* ������      [in]  (int handle)����λͼ���, Ĭ������Ϊ0
* ������      [in]  (...)������Ҫ���͵����ݰ�λͼ
* ��������:   ������Ҫ���͵����ݰ�λͼ
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������
================================================================*/
int CBccExtPack::SetHeadCol(int handle, ...)
{
	va_list ap;
	int arg;
	va_start(ap, handle);
	while ((arg = va_arg(ap, int)) != 0)
	{
		SetParmBit(&(m_bcc_ext_pack.sPack.head), arg);
	}
	va_end(ap);
    return(g_SvrLink.SetCol(0, m_bcc_ext_pack.sPack.head.ParmBits));
}

/*================================================================ 
* ��������    ExtSetHeadCol
* ������      [in]  (ST_CPACK *in_cpack)����λͼ���
* ������      [in]  (...)������Ҫ���͵����ݰ�λͼ
* ��������:   ������Ҫ���͵����ݰ�λͼ
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������
================================================================*/
int CBccExtPack::ExtSetHeadCol(ST_CPACK *in_cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, in_cpack);
	while ((arg = va_arg(ap, int)) != 0)
	{
//		writelog(LOG_ERR,"bitmap_arg=[%d]", arg);
		SetParmBit(&(in_cpack->head), arg);
	}
//	writelog(LOG_ERR,"bitmap_arg=[%d]", arg);
	va_end(ap);
    return(g_SvrLink.SetCol(0, in_cpack->head.ParmBits));
}

/*================================================================ 
* ��������    SetExtPack
* ������      [in]  (bcc_ext_pack *ext_pack)���͵����ݰ�
* ��������:   ��ʼ����Ҫ����Զ�̴��͵�BCC���ݰ�
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������
================================================================*/
int CBccExtPack::SetExtPack(BCC_EXT_PACK *ext_pack)
{
	m_bcc_ext_pack.sPack.head.RequestType = ext_pack->request_func_no;	// �����ܺ�
	m_bcc_ext_pack.drtp_node = ext_pack->drtp_node;						// drtp�ڵ��
	m_bcc_ext_pack.bcc_main_func = ext_pack->bcc_main_func;				// bcc�����ܺ�
	memcpy(&m_bcc_ext_pack.sPack.pack, &(ext_pack->sPack.pack), 
	sizeof(m_bcc_ext_pack.sPack.pack));
	
	return 0;
}

/*================================================================ 
* ��������    SetExtPack
* ������      [in]  (int drtp_node)DRTP�ڵ��
* ������      [in]  (int main_func)BCC�����ܺ�
* ������      [in]  (int request_func_no)Զ��BU��ҵ���ܺ�
* ������      [in]  (bcc_ext_pack *ext_pack)���͵����ݰ�
* ��������:   ������Ҫ����Զ�̴��͵�BCC���ݰ�
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������
================================================================*/
int CBccExtPack::SetExtPack(int drtp_node, int main_func, int request_func_no, BCC_EXT_PACK *ext_pack)
{
	return 0;
}

/*================================================================ 
* ��������    ExtCallBu
* ������      [in]  (bcc_ext_pack *ext_pack)���͵����ݰ�
* ������      [in]  (int time_out)����Զ������BU�ĳ�ʱʱ��(Ĭ��4��)
* ��������:   Զ�̺���BU
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������, ͬExtCall
================================================================*/
int CBccExtPack::ExtCallBu()
{
//	writelog(LOG_ERR,"drtp_node=[%d], bcc_main_func=[%d], time_out=[%d]",m_bcc_ext_pack.drtp_node, 
//	m_bcc_ext_pack.bcc_main_func, m_bcc_ext_pack.time_out);
	return (m_error_code = ExtCall(0, m_bcc_ext_pack.drtp_node, m_bcc_ext_pack.bcc_main_func, 0, 
	m_bcc_ext_pack.time_out, &(m_bcc_ext_pack.sPack), &(m_bcc_ext_pack.aPack), 
	&(m_bcc_ext_pack.ArrayPack)));
}

/*================================================================ 
* ��������    SetTimeOut
* ������      [in]  (int time_out = 4)���ó�ʱʱ��
* ��������:   ��ȡ������ʹ�����Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������, ͬExtCall
================================================================*/
int CBccExtPack::SetTimeOut(int time_out)
{
	m_bcc_ext_pack.time_out = time_out;
	return 0;
}

/*================================================================ 
* ��������    GetLastErr
* ������      [in]  (int *error_code)��ȡ������
* ������      [in]  (char *error_msg)��ȡ������Ϣ
* ��������:   ��ȡ������ʹ�����Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������, ͬExtCall
================================================================*/
int CBccExtPack::GetLastErr(int *error_code, char *error_msg)
{
	if (m_error_code < 0) 
	{ 
		*error_code = m_error_code;
		writelog(LOG_ERR,"error_code=[%d]",m_error_code);
	}
	else
	{
		*error_code = m_bcc_ext_pack.aPack.head.retCode;
		writelog(LOG_ERR,"error_code=[%d]",m_error_code);
	}
	
	return 0;
}

/*================================================================ 
* ��������    GetOutPack
* ������      [in]  (ST_PACK *out_cpack)���ص�pack��
* ��������:   ��ȡ������BU���ص�pack��
* ����ֵ��    int, ��ȷ����0, ʧ�ܿ��Է�������������, ͬExtCall
================================================================*/
int CBccExtPack::GetOutPack(ST_PACK *out_cpack)
{
	memcpy(out_cpack, &m_bcc_ext_pack.aPack.pack, sizeof(m_bcc_ext_pack.aPack.pack));
	return 0;
}

