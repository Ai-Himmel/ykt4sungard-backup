/********************************************************
* 实现BCC之间远程相互传送数据
* 文件名: callbu.cpp
* 说明: 对传送数据直接的函数和结构进行封装
* 创建: 李翔
* 时间: 2007-07-02
* 修改原因: 
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
	m_bcc_ext_pack.sPack.head.RequestType = ext_pack->request_func_no;	// 请求功能号
	m_bcc_ext_pack.drtp_node = ext_pack->drtp_node;						// drtp节点号
	m_bcc_ext_pack.bcc_main_func = ext_pack->bcc_main_func;				// bcc主功能号
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
* 函数名：    SetHeadCol
* 参数：      [in]  (int handle)设置位图句柄, 默认设置为0
* 参数：      [in]  (...)设置需要发送的数据包位图
* 功能描述:   设置需要发送的数据包位图
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
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
* 函数名：    ExtSetHeadCol
* 参数：      [in]  (ST_CPACK *in_cpack)设置位图句柄
* 参数：      [in]  (...)设置需要发送的数据包位图
* 功能描述:   设置需要发送的数据包位图
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
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
* 函数名：    SetExtPack
* 参数：      [in]  (bcc_ext_pack *ext_pack)传送的数据包
* 功能描述:   初始化需要进行远程传送的BCC数据包
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int CBccExtPack::SetExtPack(BCC_EXT_PACK *ext_pack)
{
	m_bcc_ext_pack.sPack.head.RequestType = ext_pack->request_func_no;	// 请求功能号
	m_bcc_ext_pack.drtp_node = ext_pack->drtp_node;						// drtp节点号
	m_bcc_ext_pack.bcc_main_func = ext_pack->bcc_main_func;				// bcc主功能号
	memcpy(&m_bcc_ext_pack.sPack.pack, &(ext_pack->sPack.pack), 
	sizeof(m_bcc_ext_pack.sPack.pack));
	
	return 0;
}

/*================================================================ 
* 函数名：    SetExtPack
* 参数：      [in]  (int drtp_node)DRTP节点号
* 参数：      [in]  (int main_func)BCC服务功能号
* 参数：      [in]  (int request_func_no)远程BU的业务功能号
* 参数：      [in]  (bcc_ext_pack *ext_pack)传送的数据包
* 功能描述:   设置需要进行远程传送的BCC数据包
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int CBccExtPack::SetExtPack(int drtp_node, int main_func, int request_func_no, BCC_EXT_PACK *ext_pack)
{
	return 0;
}

/*================================================================ 
* 函数名：    ExtCallBu
* 参数：      [in]  (bcc_ext_pack *ext_pack)传送的数据包
* 参数：      [in]  (int time_out)设置远程连接BU的超时时间(默认4秒)
* 功能描述:   远程呼叫BU
* 返回值：    int, 正确返回0, 失败可以返回其他错误码, 同ExtCall
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
* 函数名：    SetTimeOut
* 参数：      [in]  (int time_out = 4)设置超时时间
* 功能描述:   获取错误码和错误信息
* 返回值：    int, 正确返回0, 失败可以返回其他错误码, 同ExtCall
================================================================*/
int CBccExtPack::SetTimeOut(int time_out)
{
	m_bcc_ext_pack.time_out = time_out;
	return 0;
}

/*================================================================ 
* 函数名：    GetLastErr
* 参数：      [in]  (int *error_code)获取错误码
* 参数：      [in]  (char *error_msg)获取错误信息
* 功能描述:   获取错误码和错误信息
* 返回值：    int, 正确返回0, 失败可以返回其他错误码, 同ExtCall
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
* 函数名：    GetOutPack
* 参数：      [in]  (ST_PACK *out_cpack)返回的pack包
* 功能描述:   获取第三方BU返回的pack包
* 返回值：    int, 正确返回0, 失败可以返回其他错误码, 同ExtCall
================================================================*/
int CBccExtPack::GetOutPack(ST_PACK *out_cpack)
{
	memcpy(out_cpack, &m_bcc_ext_pack.aPack.pack, sizeof(m_bcc_ext_pack.aPack.pack));
	return 0;
}

