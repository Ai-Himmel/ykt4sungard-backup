#ifndef   __CALLBU_H_
#define __CALLBU_H_

#pragma once

#include "cpack.h"
#include "svrlink.h"

/*
#ifdef __cplusplus
extern "C" {
#endif
*/

/** 
 * @brief KSBCC之间远程传送数据模块结构
 */
typedef struct 
{
	/** 
	 * @brief DRTP通讯平台节点号
	 */
	int drtp_node;
	/** 
	 * @brief KSBCC功能号
	 */
	int bcc_main_func;
	 /** 
	 * @brief 第三方请求功能号
	 */
	int request_func_no;
	/** 
	 * @brief 发送包字段(含有包头)
	 */
	ST_CPACK sPack;
	/** 
	 * @brief 接受包字段(含有包头), 可以做传出参数
	 */
	ST_CPACK aPack;
	/** 
	 * @brief 接受的后续包(没有包头), 最大100个数组
	 */
	ST_PACK ArrayPack;
	/** 
	 * @brief 超时时间设置
	 */
	int time_out;
}BCC_EXT_PACK;

class CBccExtPack
{
public:
//    BCC_EXT_PACK m_bcc_ext_pack;
    
public:
    CBccExtPack();
    CBccExtPack(BCC_EXT_PACK *pack);
    virtual ~CBccExtPack();
    
    int SetHeadCol(int handle, ...);
//    int ExtSetHeadCol(ST_CPACK *in_cpack, ...);
    int InitExtPack();
    int SetExtPack(BCC_EXT_PACK *pack);
    int SetExtPack(int drtp_node, int main_func, int request_func_no, BCC_EXT_PACK *ext_pack);
    int ExtCallBu();
    int SetTimeOut(int time_out = 4);
    int GetLastErr(int *error_code, char *error_msg);
    int GetOutPack(ST_PACK *out_cpack);    
    
private:
    int ExtSetHeadCol(ST_CPACK *in_cpack, ...);

private:
    BCC_EXT_PACK m_bcc_ext_pack;
    int m_error_code;
    char m_error_msg[256];
};

/*
#ifdef __cplusplus
}
#endif
*/
#endif

